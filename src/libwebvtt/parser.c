#include "parser_internal.h"
#include "cuetext_internal.h"
#include "cue_internal.h"
#include <string.h>
#include <assert.h>

#define _ERROR(X) do { if( skip_error == 0 ) { ERROR(X); } } while(0)

/**
 * ASCII characters
 */
#define  ASCII_PERIOD (0x2E)
#define  ASCII_CR     (0x0D)
#define  ASCII_LF     (0x0A)
#define  ASCII_SPACE  (0x20)
#define  ASCII_TAB    (0x09)
#define  ASCII_DASH   (0x2D)
#define  ASCII_GT     (0x3E)
#define  ASCII_DASH   (0x2D)
#define  ASCII_COLON  (0x3A)

#define FINISH_TOKEN self->token_pos = 0;

static const webvtt_byte separator[] = {
  ASCII_DASH, ASCII_DASH, ASCII_GT
};

#define MSECS_PER_HOUR (3600000)
#define MSECS_PER_MINUTE (60000)
#define MSECS_PER_SECOND (1000)
#define BUFFER (self->buffer + self->position)
#define MALFORMED_TIME ((webvtt_timestamp_t)-1.0)

/**
 * Helpers to figure out what state we're on
 */
#define SP (self->top)
#define AT_BOTTOM (self->top == self->stack)
#define ON_HEAP (self->stack_alloc == sizeof(p->astack) / sizeof(p->astack[0]))
#define STACK_SIZE ((webvtt_uint)(self->top - self->stack))
#define FRAME(i) (self->top - (i))
#define FRAMEUP(i) (self->top + (i))
#define RECHECK goto _recheck;
#define BACK (SP->back)

static void finish_cue( webvtt_parser self, webvtt_cue **pcue );

/**
 * More state stack helpers
 */
static webvtt_status
do_push( webvtt_parser self, webvtt_uint token, webvtt_parse_callback callback,
  void *data, webvtt_state_value_type type, webvtt_uint line,
  webvtt_uint column )
{
  if( STACK_SIZE + 1 >= self->stack_alloc ) {
    webvtt_state *stack = ( webvtt_state * )webvtt_alloc0(
      sizeof( webvtt_state ) * ( self->stack_alloc << 1 ) );
    webvtt_state *tmp;
    if( !stack ) {
      ERROR( WEBVTT_ALLOCATION_FAILED );
      return WEBVTT_OUT_OF_MEMORY;
    }
    memcpy( stack, self->stack, sizeof( webvtt_state ) * self->stack_alloc );
    tmp = self->stack;
    self->stack = stack;
    self->top = stack + ( self->top - tmp );
    if( tmp != self->astack ) {
      webvtt_free( tmp );
    }
  }
  ++self->top;
  self->top->callback = callback;
  self->top->type = type;
  self->top->token = ( webvtt_token )token;
  self->top->line = line;
  self->top->column = column;
  self->top->flags = 0;
  if( type == V_TEXT && data != 0 ) {
    self->top->v.text.d = ( ( webvtt_string *)data )->d;
  }
  else {
    self->top->v.cue = ( webvtt_cue * )data;
  }
  return WEBVTT_SUCCESS;
}
static int
do_pop( webvtt_parser self )
{
  int count = 1;
  self->top -= count;
  return count;
}

#define PUSH(S,V,T) \
do { \
  self->popped = 0; \
  if( do_push(self,token,(S),(void*)(V),T,last_line, last_column) \
    == WEBVTT_OUT_OF_MEMORY ) \
    return WEBVTT_OUT_OF_MEMORY; \
  } while(0)

#define POP() \
do \
{ \
  --(self->top); \
  self->popped = 1; \
} while(0)
#define POPBACK() do_pop(self)

static int find_bytes( const webvtt_byte *buffer, webvtt_uint len,
  const webvtt_byte *sbytes, webvtt_uint slen );
static webvtt_int64 parse_int( const webvtt_byte **pb, int *pdigits );
static int parse_timestamp( webvtt_parser self, const webvtt_byte *b,
  webvtt_timestamp *result );

static webvtt_status
webvtt_get_separator( webvtt_parser self, const webvtt_byte *text,
  webvtt_uint *pos, webvtt_uint len )
{
  webvtt_uint last_column;
  webvtt_token token;

  last_column = self->column;
  token = webvtt_lex( self, text, pos, len, 1 );

  if( token == SEPARATOR ) {
    ERROR_AT_COLUMN( WEBVTT_EXPECTED_WHITESPACE, last_column );
  } else if( token != WHITESPACE ) {
    /* TODO: flag this as more serious error */
    ERROR_AT_COLUMN( WEBVTT_EXPECTED_WHITESPACE, last_column );
  }

  FINISH_TOKEN
  last_column = self->column;
  token = webvtt_lex( self, text, pos, len, 1 );

  if( token != SEPARATOR ) {
    if( token == TIMESTAMP ) {
      ERROR_AT_COLUMN( WEBVTT_MISSING_CUETIME_SEPARATOR, last_column );
    } else {
      ERROR_AT_COLUMN( WEBVTT_EXPECTED_CUETIME_SEPARATOR, last_column );
    }
  }

  FINISH_TOKEN
  last_column = self->column;
  token = webvtt_lex( self, text, pos, len, 1 );

  if( token == SEPARATOR ) {
    ERROR_AT_COLUMN( WEBVTT_EXPECTED_WHITESPACE, last_column );
  } else if( token != WHITESPACE ) {
    /* TODO: flag this as more serious error */
    ERROR_AT_COLUMN( WEBVTT_EXPECTED_WHITESPACE, last_column );
  }

  FINISH_TOKEN
  return WEBVTT_SUCCESS;
}

static webvtt_status
webvtt_get_timestamp( webvtt_parser self, webvtt_timestamp *result,
  const webvtt_byte *text, webvtt_uint *pos, webvtt_uint len,
  webvtt_bool finish )
{
  webvtt_uint last_column;
  webvtt_token token;
retry:
  last_column = self->column;
  token = webvtt_lex( self, text, pos, len, finish );
  if( token == TIMESTAMP ) {
    if( !parse_timestamp( self, self->token, result ) ) {
      if( BAD_TIMESTAMP( *result ) ) {
        ERROR_AT_COLUMN( WEBVTT_EXPECTED_TIMESTAMP, last_column );
      } else {
        ERROR_AT_COLUMN( WEBVTT_MALFORMED_TIMESTAMP, last_column );
      }
      if( !ASCII_ISDIGIT( self->token[self->token_pos - 1] ) ) {
        while( *pos < len && text[*pos] != 0x09 && text[*pos] != 0x20 ) {
          ++pos; 
        }
      }
      FINISH_TOKEN
    } else {
      FINISH_TOKEN
      return WEBVTT_SUCCESS;
    }
  } else if( token == WHITESPACE ) {
    FINISH_TOKEN
    ERROR_AT_COLUMN( WEBVTT_UNEXPECTED_WHITESPACE, last_column );
    goto retry;
  } else {
    FINISH_TOKEN
    ERROR_AT_COLUMN( WEBVTT_EXPECTED_TIMESTAMP, last_column );
  }
  return WEBVTT_PARSE_ERROR;
}

/**
 * Read a line for a skipped cue
 */
WEBVTT_INTERN webvtt_status
webvtt_skip_cue_line( webvtt_parser self, webvtt_state *st,
  const webvtt_byte *text, webvtt_uint *pos, webvtt_uint len )
{
  int v;
  if( self->finish ) {
    POP();
    return WEBVTT_SUCCESS;
  }
  
  if( st->type != V_TEXT ) {
    webvtt_init_string( &st->v.text );
    st->type = V_TEXT;
  }

  v = webvtt_string_getline( &st->v.text, text, pos, len, 0, 0, 0 );
  if( v < 0 ) {
    st->type = V_NONE;
    webvtt_release_string( &st->v.text );
    ERROR( WEBVTT_ALLOCATION_FAILED );
    POP();
    return WEBVTT_OUT_OF_MEMORY;
  } else if( v > 0 ) {
    POP();
  }
  return WEBVTT_SUCCESS;
}

WEBVTT_INTERN webvtt_status
webvtt_skip_cue( webvtt_parser self, webvtt_state *st,
  const webvtt_byte *text, webvtt_uint *pos, webvtt_uint len )
{
  webvtt_uint last_line = self->line;
  webvtt_uint last_column = self->column;
  webvtt_token token = UNFINISHED;
  webvtt_state *up = FRAMEUP(1);

  if( self->finish ) {
    if( up->type == V_TEXT ) {
      webvtt_release_string( &up->v.text );
      up->type = V_NONE;
    }
    POP();
    return WEBVTT_SUCCESS;
  }

  if( st->type != V_INTEGER ) {
    st->type = V_INTEGER;
    st->v.value = 0;
  } else if( up->type == V_TEXT ) {
    /* End of line was found */
    webvtt_status status;
    webvtt_uint pos = 0;
    if( find_bytes( webvtt_string_text( &up->v.text ),
      webvtt_string_length( &up->v.text ), separator, 3 ) ) {
      if( st->v.value < 2 ) {
        ERROR( WEBVTT_EXPECTED_EOL );
      }

      status = webvtt_parse_settings( self, st,
            webvtt_string_text( &st->v.text ), &pos,
            webvtt_string_length( &st->v.text ) );;
      st->v.text.d = up->v.text.d;
      st->type = V_TEXT;
      up->type = V_NONE;
      up->v.text.d = 0;
    } else {
      up->type = V_NONE;
      webvtt_release_string( &up->v.text );
    }
  }

  if( up->type == V_NONE ) {
    webvtt_uint last_pos = *pos;
    last_column = self->column;
    if( webvtt_lex( self, text, pos, len, 0 ) == NEWLINE ) {
      st->v.value++;
      return WEBVTT_SUCCESS;
    } else {
      *pos = last_pos;
      self->column = last_column;
    }
  }

  PUSH( &webvtt_skip_cue_line, 0, V_NONE );
  return WEBVTT_SUCCESS;
}

WEBVTT_INTERN webvtt_status
webvtt_read_settings( webvtt_parser self, webvtt_state *st,
  const webvtt_byte *text, webvtt_uint *pos, webvtt_uint len )
{
  int v;
  webvtt_uint last_column = self->column;
  webvtt_uint last_line = self->line;
  webvtt_token token = UNFINISHED;
  if( st->type == V_NONE ) {
    webvtt_init_string( &st->v.text );
    st->type = V_TEXT;
  }

  if( self->finish ) {
    goto check_settings;
  }

  v = webvtt_string_getline( &st->v.text, text, pos, len, 0, 0, 0 );
  
  if( v < 0 ) {
    ERROR( WEBVTT_ALLOCATION_FAILED );
    return WEBVTT_OUT_OF_MEMORY;
  }

  if( v > 0 ) {
    check_settings:
    if( webvtt_string_length( &st->v.text ) == 0 ) {
      ERROR( WEBVTT_CUE_INCOMPLETE );
      /* TODO: skip this cue. */
      return WEBVTT_PARSE_ERROR;
    }

    if( find_bytes( webvtt_string_text( &st->v.text ), webvtt_string_length( &st->v.text ),
          separator, sizeof( separator ) ) ) {
      st->callback = webvtt_parse_settings;
      return WEBVTT_SUCCESS;
    } else {
      ERROR( WEBVTT_CUE_INCOMPLETE );
      /* TODO: skip this cue */
      if( st->type == V_TEXT ) {
        webvtt_release_string( &st->v.text );
        st->v.text.d = 0;
      }
      st->type = V_NONE;
      POP();
      if( SP->type == V_CUE ) {
        webvtt_release_cue( &SP->v.cue );
        SP->type = V_NONE;
      }
      PUSH( &webvtt_skip_cue, 0, V_NONE );
    }
    /* skip EOL sequence */
    webvtt_lex( self, text, pos, len, self->finish );
    FINISH_TOKEN
  }
  return WEBVTT_SUCCESS;
}

WEBVTT_INTERN webvtt_status
webvtt_parse_settings( webvtt_parser self, webvtt_state *st,
  const webvtt_byte *text_, webvtt_uint *pos_, webvtt_uint length )
{
  /* parse settings deals with text in a webvtt_string --
     because of this, 'finish' means nothing (it should already be
     finished) */
  webvtt_uint pos = 0;
  webvtt_state *up = FRAME(1);
  const webvtt_byte *text;
  webvtt_cue *cue;
  webvtt_uint len;
  webvtt_status status;
  assert( st->type == V_TEXT );
  text = webvtt_string_text( &st->v.text );
  len = webvtt_string_length( &st->v.text );
  
  if( up->type == V_NONE ) {
    up->type = V_CUE;
    webvtt_create_cue( &up->v.cue );
  }

  assert( up->type == V_CUE );
  cue = up->v.cue;

  if( WEBVTT_FAILED( status = webvtt_get_timestamp( self, &cue->from, text,
    &pos, len, 1 ) ) ) {
    goto finish;
  }
  
  if( WEBVTT_FAILED( status = webvtt_get_separator( self, text, &pos,
    len ) ) ) {
    goto finish;
  }

  if( WEBVTT_FAILED( status = webvtt_get_timestamp( self, &cue->until, text,
    &pos, len, 1 ) ) ) {
    goto finish;
  }

  if( WEBVTT_FAILED( status = webvtt_parse_params( self, cue, text,
    &pos, len ) ) ) {
    goto finish;
  }

  /* Mark that we've read cue params */
  up->v.cue->flags |= CUE_HAVE_CUEPARAMS;
  
  /* Cleanup */
finish:
  webvtt_release_string( &st->v.text );
  st->type = V_NONE;
  POP();
  return status;
}

/**
 * parse optional cue-parameters
 */
WEBVTT_INTERN webvtt_status
webvtt_parse_params( webvtt_parser self, webvtt_cue *cue,
  const webvtt_byte *text, webvtt_uint *pos, webvtt_uint len ) {
  enum {
    PARAMS_LEADING_SPACE,
    PARAMS_KEYWORD,
  } mode = PARAMS_LEADING_SPACE;
  webvtt_status status = WEBVTT_SUCCESS;
  
  if( !len && text ) {
    len = strlen( text );
  }

  while( *pos < len && status == WEBVTT_SUCCESS ) {
    if( mode == PARAMS_LEADING_SPACE ) {
      webvtt_uint last_column = self->column;
      webvtt_uint last_line = self->line;
      webvtt_token tk = webvtt_lex( self, text, pos, len, 1 );
      if( tk == NEWLINE ) {
        FINISH_TOKEN
        break;
      }
      else if( tk != WHITESPACE ) {
        FINISH_TOKEN
        ERROR_AT( WEBVTT_EXPECTED_WHITESPACE, last_column, last_line );
        while( *pos < len 
          && text[ *pos ] != 0x20 
          && text[ *pos ] != 0x09 ) {
          ++( *pos );
        }
      } else {
        FINISH_TOKEN
        mode = PARAMS_KEYWORD;
      }
    } else if( mode == PARAMS_KEYWORD && *pos < len ) {
      webvtt_byte ch = text[ *pos ];
      webvtt_status (*func)( webvtt_parser, webvtt_cue *, const webvtt_byte *,
        webvtt_uint *, webvtt_uint ) = 0;
      switch( ch ) {
        /* 'a' */ case 0x61: func = &webvtt_parse_align; break;
        /* 'l' */ case 0x6C: func = &webvtt_parse_line; break;
        /* 'p' */ case 0x70: func = &webvtt_parse_position; break;
        /* 's' */ case 0x73: func = &webvtt_parse_size; break;
        /* 'v' */ case 0x76: func = &webvtt_parse_vertical; break;
        default:
          ERROR( WEBVTT_INVALID_CUESETTING );
skip_setting:
          while( *pos < len 
            && text[ *pos ] != 0x20 
            && text[ *pos ] != 0x09 ) {
            if( text[ *pos ] == 0x0D || text[ *pos ] == 0x0A ) {
              return WEBVTT_FINISH_LINE;
            }
            ++( *pos );
            ++self->column;
          }
          continue;
      }
      status = func( self, cue, text, pos, len );
      if( status == WEBVTT_INVALID_TAG_NAME ) {
        ERROR( WEBVTT_INVALID_CUESETTING );
        status = WEBVTT_SUCCESS;
        goto skip_setting;
      } else if( status == WEBVTT_SUCCESS ) {
        mode = PARAMS_LEADING_SPACE;
      } else if( status == WEBVTT_CONTINUE_LINE ) {
        status = WEBVTT_SUCCESS;
      } else if( status == WEBVTT_FINISH_LINE ) {
        return WEBVTT_SUCCESS;
      }
    }
  }

  return status;
}

enum webvtt_param_mode
{
  P_KEYWORD,
  P_COLON,
  P_VALUE
};

typedef
enum webvtt_token_flags_t
{
  POSITIVE = 0x80000000,
  NEGATIVE = 0x40000000,
  SIGN_MASK = ( POSITIVE | NEGATIVE ),
  FLAGS_MASK = SIGN_MASK,
  TOKEN_MASK = ( 0xFFFFFFFF & ~FLAGS_MASK ),
} webvtt_token_flags;

static webvtt_bool
token_in_list( webvtt_token tk, const webvtt_token nt[] )
{
  int i = 0;
  webvtt_token t;
  while( ( t = nt[ i++ ] ) != 0 ) {
    if( tk == t ) {
      return 1;
    }
  }
  return 0;
}

static int
find_token( webvtt_token tk, const webvtt_token nt[] )
{
  int i = 0;
  webvtt_token t;
  while( ( t = nt[ i ] ) != 0 ) {
    webvtt_token masked = t & TOKEN_MASK;
    if( tk == masked ) {
      return i;
    }
    ++i;
  }
  return -1;
}

static webvtt_status
webvtt_parse_param( webvtt_parser self, const webvtt_byte *text,
  webvtt_uint *pos, webvtt_uint len, webvtt_error bv, webvtt_token
  keyword, webvtt_token values[], webvtt_uint *value_column ) {
  int i;
  webvtt_bool precws = 0;
  webvtt_bool prevws = 0;
  static const webvtt_token value_tokens[] = {
    INTEGER, RL, LR, START, MIDDLE, END, LEFT, RIGHT, PERCENTAGE, 0
  };
  static const webvtt_token keyword_tokens[] = {
    ALIGN, SIZE, LINE, POSITION, VERTICAL, 0
  };
  enum webvtt_param_mode mode = P_KEYWORD;
  webvtt_uint keyword_column = 0;
  while( *pos < len ) {
    webvtt_uint last_line = self->line;
    webvtt_uint last_column = self->column;
    webvtt_uint last_pos = *pos;
    webvtt_token tk = webvtt_lex( self, text, pos, len, 1 );
    webvtt_uint tp = self->token_pos;
    FINISH_TOKEN

    switch( mode ) {
      case P_KEYWORD:
        switch( tk ) {
          case ALIGN:
          case SIZE:
          case POSITION:
          case VERTICAL:
          case LINE:
            if( tk != keyword ) {
              *pos -= tp;
              self->column -= tp;
              return WEBVTT_CONTINUE_LINE;
            }
            if( *pos < len ) {
              webvtt_byte ch = text[ *pos ];
              if( ch != 0x3A && ch != 0x20 && ch != 0x09 && ch != 0x0A
                && ch != 0x0D ) {
                ERROR_AT_COLUMN( WEBVTT_INVALID_CUESETTING, last_column );
                goto skip_param;
              }
            }
            mode = P_COLON;
            keyword_column = last_column;
            break;
          case WHITESPACE:
            break;
          case NEWLINE:
            return WEBVTT_FINISH_LINE;
            break;
          default:
            ERROR_AT( WEBVTT_INVALID_CUESETTING, last_line,
              last_column );
            *pos = *pos + tp + 1;
 skip_param:
            while( *pos < len && text[ *pos ] != 0x20
              && text[ *pos ] != 0x09 ) {
              if( text[ *pos ] == 0x0A || text[ *pos ] == 0x0D ) {
                return WEBVTT_FINISH_LINE;
              }
              ++( *pos );
              ++self->column;
            }
            break;
        }
        break;
      case P_COLON:
        if( tk == WHITESPACE && !precws ) {
          ERROR_AT( WEBVTT_UNEXPECTED_WHITESPACE, last_line,
            last_column
          );
          precws = 1;
        }  else if( tk == COLON ) {
          mode = P_VALUE;
        } else if( token_in_list( tk, value_tokens ) ) {
          ERROR_AT( WEBVTT_MISSING_CUESETTING_DELIMITER, last_line,
            last_column );
          mode = P_VALUE;
          goto get_value;
        } else if( token_in_list( tk, keyword_tokens ) ) {
          ERROR_AT( WEBVTT_INVALID_CUESETTING, last_line,
            keyword_column );
        } else {
          ERROR_AT( WEBVTT_INVALID_CUESETTING_DELIMITER, last_line,
            last_column );
          *pos = last_pos + tp + 1;
        }
        break;
      case P_VALUE:
get_value:
        if( tk == WHITESPACE && !prevws ) {
          ERROR_AT( WEBVTT_UNEXPECTED_WHITESPACE, last_line,
            last_column );
        } else if( ( i = find_token( tk, values ) ) >= 0 ) {
          webvtt_token t = values[ i ] & TOKEN_MASK;
          int flags = values[ i ] & FLAGS_MASK;
          *value_column = last_column;
          if( *pos < len ) {
            webvtt_byte ch = text[ *pos ];
            if( ch != 0x20 && ch != 0x09 
              && ch != 0x0D && ch != 0x0A ) {
              goto bad_value;
            }
          }
          switch( t ) {
            case INTEGER:
            case PERCENTAGE:
              if( ( flags & SIGN_MASK ) != SIGN_MASK ) {
                const webvtt_byte p = self->token[ 0 ];
                if( ( ( flags & NEGATIVE ) && p != ASCII_DASH ) 
                  || ( ( flags & POSITIVE ) && p == ASCII_DASH ) ) {
                  goto bad_value;
                }
              }
          }
          return i;
        } else {
bad_value:
          ERROR_AT( bv, last_line, last_column );
bad_value_eol:
          while( *pos < len && text[ *pos ] != 0x20
            && text[ *pos ] != 0x09 ) {
            if( text[ *pos ] == 0x0A || text[ *pos ] == 0x0D ) {
              return WEBVTT_FINISH_LINE;
            }
            ++( *pos );
            ++self->column;
          }
          if( *pos >= len ) {
            return WEBVTT_FINISH_LINE;
          }
        }
        break;
    }
  }
  if( mode == P_VALUE && *pos >= len ) {
    ERROR( bv );
    goto bad_value_eol;
  }
  return WEBVTT_CONTINUE_LINE;
}


WEBVTT_INTERN webvtt_status
webvtt_parse_size( webvtt_parser self, webvtt_cue *cue, const webvtt_byte *text,
  webvtt_uint *pos, webvtt_uint len )
{
  webvtt_uint last_line = self->line;
  webvtt_uint last_column = self->column;
  webvtt_uint vc;
  webvtt_status v;
  webvtt_token values[] = { PERCENTAGE|POSITIVE, 0 };
  if( ( v = webvtt_parse_param( self, text, pos, len,
    WEBVTT_SIZE_BAD_VALUE, SIZE, values, &vc ) ) >= 0 ) {
    if( cue->flags & CUE_HAVE_SIZE ) {
      ERROR_AT( WEBVTT_SIZE_ALREADY_SET, last_line, last_column );
    }
    cue->flags |= CUE_HAVE_SIZE;
    if( values[ v ] ) {
      int digits;
      const webvtt_byte *t = self->token;
      webvtt_uint value = (webvtt_uint)parse_int( &t, &digits );
      if( value > 100 ) {
        ERROR_AT_COLUMN( WEBVTT_SIZE_BAD_VALUE, vc );
      } else {
        cue->settings.size = value;
      }
      FINISH_TOKEN
    }
  }
  return v; 
}

WEBVTT_INTERN webvtt_status
webvtt_parse_align( webvtt_parser self, webvtt_cue *cue, const webvtt_byte *text,
  webvtt_uint *pos, webvtt_uint len )
{
  webvtt_uint last_line = self->line;
  webvtt_uint last_column = self->column;
  webvtt_status v;
  webvtt_uint vc;
  webvtt_token values[] = { START, MIDDLE, END, LEFT, RIGHT, 0 };
  if( ( v = webvtt_parse_param( self, text, pos, len,
    WEBVTT_ALIGN_BAD_VALUE, ALIGN, values, &vc ) ) >= 0 ) {
    if( cue->flags & CUE_HAVE_ALIGN ) {
      ERROR_AT( WEBVTT_ALIGN_ALREADY_SET, last_line, last_column );
    }
    cue->flags |= CUE_HAVE_ALIGN;
    switch( values[ v ] ) {
      case START: cue->settings.align = WEBVTT_ALIGN_START; break;
      case MIDDLE: cue->settings.align = WEBVTT_ALIGN_MIDDLE; break;
      case END: cue->settings.align = WEBVTT_ALIGN_END; break;
      case LEFT: cue->settings.align = WEBVTT_ALIGN_LEFT; break;
      case RIGHT: cue->settings.align = WEBVTT_ALIGN_RIGHT; break;
    }
  }
  return v >= 0 ? WEBVTT_SUCCESS : v;
}

WEBVTT_INTERN webvtt_status
webvtt_parse_position( webvtt_parser self, webvtt_cue *cue, const webvtt_byte *text,
  webvtt_uint *pos, webvtt_uint len )
{
  webvtt_uint last_line = self->line;
  webvtt_uint last_column = self->column;
  webvtt_status v;
  webvtt_uint vc;
  webvtt_bool first_flag = 0;
  webvtt_token values[] = { PERCENTAGE|POSITIVE, 0 };
  if( ( v = webvtt_parse_param( self, text, pos, len,
    WEBVTT_POSITION_BAD_VALUE, POSITION, values, &vc ) ) >= 0 ) {
    webvtt_uint digits;
    webvtt_int64 value; 
    const webvtt_byte *t = self->token; 
    if( cue->flags & CUE_HAVE_POSITION ) {
      ERROR_AT( WEBVTT_POSITION_ALREADY_SET, last_line, last_column );
    } else {
      first_flag = 1;
    }
    cue->flags |= CUE_HAVE_POSITION;
    value = parse_int( &t, &digits );
    switch( values[ v ] & TOKEN_MASK ) {
      case INTEGER: {
        cue->snap_to_lines = 1;
        cue->settings.line.no = (int)value;
      }
      break;

      case PERCENTAGE: {
        if( value < 0 || value > 100 ) {
          if( first_flag ) {
            cue->flags &= ~CUE_HAVE_POSITION;
          }
          ERROR_AT_COLUMN( WEBVTT_POSITION_BAD_VALUE, vc );
          return WEBVTT_SUCCESS;
        }
        cue->settings.position = (webvtt_uint)value;
      } break;
    }
  }
  return v >= 0 ? WEBVTT_SUCCESS : v;
}

WEBVTT_INTERN webvtt_status
webvtt_parse_vertical( webvtt_parser self, webvtt_cue *cue, const webvtt_byte *text,
  webvtt_uint *pos, webvtt_uint len )
{
  webvtt_uint last_line = self->line;
  webvtt_uint last_column = self->column;
  webvtt_status v;
  webvtt_uint vc;
  webvtt_bool first_flag = 0;
  webvtt_token values[] = { RL, LR, 0 };
  if( ( v = webvtt_parse_param( self, text, pos, len,
    WEBVTT_VERTICAL_BAD_VALUE, VERTICAL, values, &vc ) ) >= 0 ) {
    webvtt_token t = values[ v ]; 
    if( cue->flags & CUE_HAVE_VERTICAL ) {
      ERROR_AT( WEBVTT_VERTICAL_ALREADY_SET, last_line, last_column );
    } else {
      first_flag = 1;
    }
    cue->flags |= CUE_HAVE_VERTICAL;
    cue->settings.vertical = ( t == LR )
                           ? WEBVTT_VERTICAL_LR
                           : WEBVTT_VERTICAL_RL
                           ;
  }

  return v >= 0 ? WEBVTT_SUCCESS : v;
}

WEBVTT_INTERN webvtt_status
webvtt_parse_line( webvtt_parser self, webvtt_cue *cue, const webvtt_byte *text,
  webvtt_uint *pos, webvtt_uint len )
{
  webvtt_uint last_line = self->line;
  webvtt_uint last_column = self->column;
  webvtt_status v;
  webvtt_uint vc;
  webvtt_bool first_flag = 0;
  webvtt_token values[] = { INTEGER, PERCENTAGE|POSITIVE, 0 };
  if( ( v = webvtt_parse_param( self, text, pos, len,
    WEBVTT_LINE_BAD_VALUE, LINE, values, &vc ) ) >= 0 ) {
    webvtt_uint digits;
    webvtt_int64 value; 
    const webvtt_byte *t = self->token; 
    if( cue->flags & CUE_HAVE_LINE ) {
      ERROR_AT( WEBVTT_LINE_ALREADY_SET, last_line, last_column );
    } else {
      first_flag = 1;
    }
    cue->flags |= CUE_HAVE_LINE;
    value = parse_int( &t, &digits );
    switch( values[ v ] & TOKEN_MASK ) {
      case INTEGER: {
        cue->snap_to_lines = 1;
        cue->settings.line.no = (int)value;
      }
      break;

      case PERCENTAGE: {
        if( value < 0 || value > 100 ) {
          if( first_flag ) {
            cue->flags &= ~CUE_HAVE_LINE;
          }
          ERROR_AT_COLUMN( WEBVTT_LINE_BAD_VALUE, vc );
          return WEBVTT_SUCCESS;
        }
        cue->snap_to_lines = 0;
        cue->settings.line.relative_position = (webvtt_uint)value;
      } break;
    }
  }
  return v >= 0 ? WEBVTT_SUCCESS : v;
}


/**
 * Read a WEBVTT header
 */
WEBVTT_INTERN webvtt_status
webvtt_parse_header( webvtt_parser self, webvtt_state *st,
  const webvtt_byte *text, webvtt_uint *pos, webvtt_uint len )
{
  int v;
  webvtt_token token;
  webvtt_uint last_line;
  webvtt_uint last_column;
  if( self->finish ) {
    goto __final;
  }

  while( *pos < len )
  {
__final:
    last_line = self->line;
    last_column = self->column;
    switch( st->flags )
    {
    case 0:
      token = webvtt_lex( self, text, pos, len, self->finish );
      switch( token ) {
        case UNFINISHED:
          return WEBVTT_SUCCESS;
    
        case WEBVTT:
          st->flags = WEBVTT_HEADER_TAG;
          FINISH_TOKEN
          break;

        default:
          if( ( self->flags & HAVE_MALFORMED_TAG ) == 0 ) {
            self->flags |= HAVE_MALFORMED_TAG;
            ERROR_AT( WEBVTT_MALFORMED_TAG, last_line, last_column );
          }
          *pos += self->token_pos ? self->token_pos : 1;
          FINISH_TOKEN
      }
      break;
    case WEBVTT_HEADER_TAG:
      token = webvtt_lex( self, text, pos, len, self->finish );
      switch( token ) {
        case UNFINISHED:
          return WEBVTT_SUCCESS;

        case WHITESPACE:
          st->flags = WEBVTT_HEADER_COMMENT;
          break;

        case NEWLINE:
          st->flags = WEBVTT_HEADER_EOL;
          FINISH_TOKEN
          break;

        default:
          ERROR(WEBVTT_MALFORMED_TAG);
          return WEBVTT_PARSE_ERROR;
      }
      break;

    case WEBVTT_HEADER_COMMENT:
      if( self->finish ) {
        if( st->type == V_TEXT ) {
          webvtt_release_string( &st->v.text );
          st->type = V_NONE;
        }
        return WEBVTT_SUCCESS;
      }
      if( st->type != V_TEXT ) {
        st->type = V_TEXT;
        webvtt_init_string( &st->v.text );
      }
      v = webvtt_string_getline( &st->v.text, text, pos, len, 0, 0, 0 );
      if( v < 0 ) {
        webvtt_release_string( &st->v.text );
        ERROR( WEBVTT_ALLOCATION_FAILED );
        return WEBVTT_OUT_OF_MEMORY;
      }
      if( v > 0 ) {
        if( webvtt_lex( self, text, pos, len,  self->finish  ) == NEWLINE ) {
          webvtt_release_string( &st->v.text );
          st->flags = WEBVTT_HEADER_EOL;
        }
      }
      break;

    case WEBVTT_HEADER_EOL:
      if( self->finish ) {
        return WEBVTT_SUCCESS;
      }
      token = webvtt_lex( self, text, pos, len, self->finish  );
      switch( token ) {
        case NEWLINE:
          FINISH_TOKEN
          st->flags = 0;
          st->callback = &webvtt_parse_body;
          return WEBVTT_SUCCESS;

        default:
          *pos = *pos - self->token_pos;
          FINISH_TOKEN
        case BADTOKEN:
          /* error, expected eol */
          ERROR_AT_COLUMN(WEBVTT_EXPECTED_EOL,last_column);
          st->callback = &webvtt_parse_body;
          return WEBVTT_SUCCESS;
      }
    }
  }
  return WEBVTT_SUCCESS;
}

/**
 * Parse Cue ID
 */
WEBVTT_INTERN webvtt_status
webvtt_parse_id( webvtt_parser self, webvtt_state *st, const webvtt_byte *text,
  webvtt_uint *pos, webvtt_uint len )
{
  webvtt_status status = WEBVTT_SUCCESS;
  int v;
  if( st->type == V_NONE ) {
    webvtt_init_string( &st->v.text );
    st->type = V_TEXT;
  }
  
  assert( st->type == V_TEXT );
  v = webvtt_string_getline( &st->v.text, text, pos, len, 0, self->finish, 0 );
  
  if( v < 0 ) {
    ERROR( WEBVTT_ALLOCATION_FAILED );
    return WEBVTT_OUT_OF_MEMORY;
  }

  if( v > 0 ) {
    if( find_bytes( webvtt_string_text( &st->v.text ),
          webvtt_string_length( &st->v.text ),
          separator, sizeof( separator ) ) ) {
      webvtt_uint pos = 0;
      status = webvtt_parse_settings( self, st,
        webvtt_string_text( &st->v.text ), &pos,
        webvtt_string_length( &st->v.text ) );

      /* This is not really the right way to do this. */
      self->column += webvtt_string_length( &st->v.text );
      self->bytes += webvtt_string_length( &st->v.text );

    } else {
      webvtt_state *up = FRAME(1);
      if( up->type == V_NONE ) {
        webvtt_create_cue( &up->v.cue );
        up->type = V_CUE;
      }
      /* This is not really the right way to do this. */
      self->column += webvtt_string_length( &st->v.text );
      self->bytes += webvtt_string_length( &st->v.text );

      up->v.cue->id.d = st->v.text.d;
      up->v.cue->flags |= CUE_HAVE_ID;
      st->type = V_NONE;
      st->v.text.d = 0;
      st->callback = 0;
      POP();
    }
    /* skip EOL */
    webvtt_lex( self, text, pos, len, self->finish );
    FINISH_TOKEN
  }
  return status;
}

/**
 * Read line of cuetext
 */
WEBVTT_INTERN webvtt_status
webvtt_read_cuetext_line( webvtt_parser self, webvtt_state *st,
  const webvtt_byte *text, webvtt_uint *pos, webvtt_uint len )
{
  int v;
  if( st->type == V_NONE ) {
    webvtt_init_string( &st->v.text );
    st->type = V_TEXT;
  } else if( self->finish ) {
    POP();
    return WEBVTT_SUCCESS;
  }

  assert( st->type == V_TEXT );
  v = webvtt_string_getline( &st->v.text, text, pos, len, 0, self->finish, 0 );
  if( v < 0 ) {
    /* probably needs adjustment */
    ERROR( WEBVTT_ALLOCATION_FAILED );
    return WEBVTT_OUT_OF_MEMORY;
  } else if( v > 0 ) {
    /* skip EOL sequence */
    if( self->finish || webvtt_lex( self, text, pos, len, self->finish ) == NEWLINE ) {
      FINISH_TOKEN
      POP();
    }
  }
  
  return WEBVTT_SUCCESS;
}

/**
 * Read cuetext
 */
WEBVTT_INTERN webvtt_status
webvtt_read_cuetext( webvtt_parser self, webvtt_state *st,
  const webvtt_byte *text, webvtt_uint *pos, webvtt_uint len )
{
  webvtt_uint last_line = self->line;
  webvtt_uint last_column = self->column;
  webvtt_token token = UNFINISHED;
  int finished_cue = 0;
  webvtt_state *up = FRAMEUP(1);
  webvtt_status status;
  if( st->type == V_NONE ) {
    webvtt_init_string( &st->v.text );
    st->type = V_TEXT;
  }

  assert( FRAME(1)->type == V_CUE );
  assert( st->type == V_TEXT );

  if( up->type == V_TEXT ) {
    if( webvtt_string_length( &up->v.text ) == 0 ) {
      /* This cue is finished, a 0-length line indicates 2 sequential EOLs */
      webvtt_release_string( &up->v.text );
      up->type = V_NONE;
      finished_cue = 1;
    } else {
      if( find_bytes( webvtt_string_text( &up->v.text ),
        webvtt_string_length( &up->v.text ), separator,
        sizeof( separator ) ) ) {
        if( webvtt_string_length( &st->v.text ) == 0 ) {
          webvtt_uint pos = 0;
          webvtt_release_string( &st->v.text );
          /* This error is probably not correct. */
          ERROR( WEBVTT_CUE_INCOMPLETE );
          webvtt_release_cue( &FRAME(1)->v.cue );
          FRAME(1)->type = V_NONE;
          st->v.text.d = up->v.text.d;
          up->v.text.d = 0;
          up->type = V_NONE;
          status = webvtt_parse_settings( self, st,
            webvtt_string_text( &st->v.text ), &pos,
            webvtt_string_length( &st->v.text ) );
        } else {
          webvtt_uint pos = 0;
          ERROR_AT( WEBVTT_EXPECTED_EOL, up->line, up->column );
          /* If a separator is found, we need to move onto the next cue. */
          status = webvtt_parse_cuetext( self, FRAME(1)->v.cue, &st->v.text, 
            self->finish );
          webvtt_release_string( &st->v.text );
          st->v.text.d = up->v.text.d;
          up->v.text.d = 0;
          up->type = V_NONE;
          finish_cue( self, &FRAME(1)->v.cue );
          FRAME(1)->type = V_NONE;
          FRAME(1)->v.cue = 0;
          status = webvtt_parse_settings( self, st,
            webvtt_string_text( &st->v.text ), &pos,
            webvtt_string_length( &st->v.text ) );
          return status;
        }
        return WEBVTT_SUCCESS;;
      } else {
        if( WEBVTT_FAILED( status = webvtt_string_append_string( &st->v.text, 
          &up->v.text ) ) ) {
          webvtt_release_string( &up->v.text );
          webvtt_release_string( &st->v.text );
          up->type = st->type = V_NONE;
          if( status == WEBVTT_OUT_OF_MEMORY ) {
            ERROR( WEBVTT_ALLOCATION_FAILED );
          }
          return status;
        } else {
          webvtt_release_string( &up->v.text );
          up->type = V_NONE;
          if( WEBVTT_FAILED( status = webvtt_string_putc( &st->v.text,
            ASCII_LF ) ) ) {
            webvtt_release_string( &st->v.text );
            st->type = V_NONE;
            if( status == WEBVTT_OUT_OF_MEMORY ) {
              ERROR( WEBVTT_ALLOCATION_FAILED );
            }
            return status;
          }
          if( !self->finish ) {
            PUSH( &webvtt_read_cuetext_line, 0, V_NONE );
          } else {
            finished_cue = 1;
          }
        }
      }
    }
  }

  if( finished_cue ) {
    /* If a separator is found, we need to move onto the next cue. */
    status = webvtt_parse_cuetext( self, FRAME(1)->v.cue, &st->v.text, 
      self->finish );
    webvtt_release_string( &st->v.text );
    st->v.text.d = up->v.text.d;
    up->v.text.d = 0;
    up->type = V_NONE;
    finish_cue( self, &FRAME(1)->v.cue );
    FRAME(1)->type = V_NONE;
    FRAME(1)->v.cue = 0;
    POP();
    return status;
  }

  return WEBVTT_SUCCESS;
}

/**
 * Parse a Cue
 */
WEBVTT_INTERN webvtt_status
webvtt_parse_cue( webvtt_parser self, webvtt_state *st, const webvtt_byte *text,
  webvtt_uint *pos, webvtt_uint len )
{
  webvtt_token token = UNFINISHED;
  webvtt_uint last_line = self->line;
  webvtt_uint last_column = self->column;

  if( st->type == V_CUE ) {
    if( ( st->v.cue->flags & CUE_HAVE_CUEPARAMS ) == 0 ) {
      if( self->finish ) {
        ERROR( WEBVTT_CUE_INCOMPLETE );
        webvtt_release_cue( &st->v.cue );
        st->type = V_NONE;
        st->callback = 0;
        POP();
        return WEBVTT_SUCCESS;
      }
      PUSH( &webvtt_read_settings, 0, V_NONE );
      return WEBVTT_SUCCESS;
    } else {
      /* read cuetext */
      if( !self->finish ) {
        PUSH( &webvtt_read_cuetext, 0, V_NONE );
        PUSH( &webvtt_read_cuetext_line, 0, V_NONE );
      } else {
        finish_cue( self, &st->v.cue );
        st->type = V_NONE;
        POP();
      }
    }
  } else {
    POP();
  }
  return WEBVTT_SUCCESS;
}

/**
 * Parse body of webvtt file
 */
WEBVTT_INTERN webvtt_status
webvtt_parse_body( webvtt_parser self, webvtt_state *st, const webvtt_byte *text,
  webvtt_uint *pos, webvtt_uint len )
{
  webvtt_token token;
  webvtt_uint last_line;
  webvtt_uint last_column;

  if( self->finish ) {
    goto __final;
  }

  while( *pos < len ) {
__final:
    last_line = self->line;
    last_column = self->column;
    token = webvtt_lex( self, text, pos, len, self->finish );
    switch( token ) {
    case NEWLINE:
      break;

    default:
       self->column -= self->token_pos;
       self->bytes -= self->token_pos;
       *pos -= self->token_pos;
       FINISH_TOKEN
       if( !self->finish ) {
         PUSH( &webvtt_parse_cue, 0, V_NONE );
         PUSH( &webvtt_parse_id, 0, V_NONE );
       }
       return WEBVTT_SUCCESS;
    }
  }
  return WEBVTT_SUCCESS;
}

WEBVTT_EXPORT webvtt_status
webvtt_create_parser( webvtt_cue_fn on_read,
                      webvtt_error_fn on_error, void *
                      userdata,
                      webvtt_parser *ppout )
{
  webvtt_parser p;
  if( !on_read || !on_error || !ppout ) {
    return WEBVTT_INVALID_PARAM;
  }

  if( !( p = ( webvtt_parser )webvtt_alloc0( sizeof * p ) ) ) {
    return WEBVTT_OUT_OF_MEMORY;
  }

  memset( p->astack, 0, sizeof( p->astack ) );
  p->stack = p->astack;
  p->top = p->stack;
  p->top->callback = &webvtt_parse_header;
  p->stack_alloc = sizeof( p->astack ) / sizeof( p->astack[0] );

  p->read = on_read;
  p->error = on_error;
  p->column = p->line = 1;
  p->userdata = userdata;
  *ppout = p;

  return WEBVTT_SUCCESS;
}

/**
 * Helper to validate a cue and, if valid, notify the application that a cue has
 * been read.
 * If it fails to validate, silently delete the cue.
 *
 * ( This might not be the best way to go about this, and additionally,
 * webvtt_validate_cue has no means to report errors with the cue, and we do
 * nothing with its return value )
 */
static void
finish_cue( webvtt_parser self, webvtt_cue **pcue )
{
  if( pcue ) {
    webvtt_cue *cue = *pcue;
    if( cue ) {
      if( webvtt_validate_cue( cue ) ) {
        self->read( self->userdata, cue );
      } else {
        webvtt_release_cue( &cue );
      }
      *pcue = 0;
    }
  }
}

/**
 * This routine tries to clean up the stack
 * for us, to prevent leaks.
 *
 * It should also help find errors in stack management.
 */
WEBVTT_INTERN void
cleanup_stack( webvtt_parser self )
{
  webvtt_state *st = self->top;
  while( st >= self->stack ) {
    switch( st->type ) {
      case V_CUE:
        webvtt_release_cue( &st->v.cue );
        break;
      case V_TEXT:
        webvtt_release_string( &st->v.text );
        break;
        /**
         * TODO: Clean up cuetext nodes as well.
         * Eventually the cuetext parser will probably be making use
         * of this stack, and will need to manage it well also.
         */
    }
    st->type = V_NONE;
    st->line = st->column = st->token = 0;
    st->v.cue = NULL;
    if( st > self->stack ) {
      --self->top;
    }
    --st;
  }
  if( self->stack != self->astack ) {
    /**
     * If the stack is dynamically allocated (probably not),
     * then point it to the statically allocated one (and zeromem it),
     * then finally delete the old dynamically allocated stack
     */
    webvtt_state *pst = self->stack;
    memset( self->astack, 0, sizeof( self->astack ) );
    self->stack = self->astack;
    self->stack_alloc = sizeof( self->astack ) / sizeof( *( self->astack ) );
    webvtt_free( pst );
  }
}

WEBVTT_EXPORT void
webvtt_delete_parser( webvtt_parser self )
{
  if( self ) {
    cleanup_stack( self );

    webvtt_release_string( &self->line_buffer );
    webvtt_free( self );
  }
}


#define BEGIN_STATE(State) case State: {
#define END_STATE } break;
#define IF_TOKEN(Token,Actions) case Token: { Actions } break;
#define BEGIN_DFA switch(top->state) {
#define END_DFA }
#define BEGIN_TOKEN switch(token) {
#define END_TOKEN }
#define IF_TRANSITION(Token,State) if( token == Token ) { self->state = State;
#define ELIF_TRANSITION(Token,State) } else IF_TRANSITION(Token,State)
#define ENDIF }
#define ELSE } else {

static int
find_newline( const webvtt_byte *buffer, webvtt_uint *pos, webvtt_uint len )
{
  while( *pos < len ) {
    if( buffer[ *pos ] == ASCII_CR || buffer[ *pos ] == ASCII_LF ) {
      return 1;
    } else {
      ( *pos )++;
    }
  }
  return -1;
}

static void
find_next_whitespace( const webvtt_byte *buffer, webvtt_uint *ppos, webvtt_uint len )
{
  webvtt_uint pos = *ppos;
  while( pos < len ) {
    webvtt_byte c = buffer[pos];
    if( c == ASCII_CR || c == ASCII_LF || c == ASCII_SPACE || c == ASCII_TAB ) {
      break;
    }

    ++pos;
  }
  *ppos = pos;
}

/**
 * basic strnstr-ish routine
 */
WEBVTT_INTERN int
find_bytes( const webvtt_byte *buffer, webvtt_uint len, const webvtt_byte *sbytes, webvtt_uint slen )
{
  webvtt_uint slen2 = slen - 1;
  do {
    if( *buffer == *sbytes && memcmp( buffer + 1, sbytes + 1, slen2 ) == 0 ) {
      return 1;
    }
  } while( len-- >= slen && *buffer++ );
  return 0;
}

WEBVTT_EXPORT webvtt_status
webvtt_parse_chunk( webvtt_parser self, const void *buffer, webvtt_uint len )
{
  webvtt_status status = WEBVTT_SUCCESS;
  webvtt_uint pos = 0;
  const webvtt_byte *b = ( const webvtt_byte * )buffer;

  while( pos < len && !WEBVTT_FAILED(status) ) {
    status = SP->callback( self, SP, b, &pos, len );
  }

  return status;
}

WEBVTT_EXPORT webvtt_status
webvtt_finish_parsing( webvtt_parser self )
{
  webvtt_status status = WEBVTT_SUCCESS;
  webvtt_byte buffer[] = { '\0' };
  webvtt_uint pos = 0;
  if( !self ) {
    return WEBVTT_INVALID_PARAM;
  }
  self->finish = 1;
  while( !WEBVTT_FAILED(status) ) {
    webvtt_state *st = SP;
    webvtt_parse_callback cb = st->callback;
    status = st->callback( self, st, buffer, &pos, 0 );
    if( cb == &webvtt_read_cuetext ) {
      if( st->type == V_TEXT ) {
        st->type = V_NONE;
        webvtt_release_string( &st->v.text );
      }
      st->type = V_NONE;
      --self->top;
    } else if( cb == &webvtt_parse_body
      || cb == &webvtt_parse_header ) {
      break;
    }
  }

  return status;
}

#undef SP
#undef AT_BOTTOM
#undef ON_HEAP
#undef STACK_SIZE
#undef FRAME
#undef PUSH
#undef POP

/**
 * Get an integer value from a series of digits.
 */
static webvtt_int64
parse_int( const webvtt_byte **pb, int *pdigits )
{
  int digits = 0;
  webvtt_int64 result = 0;
  webvtt_int64 mul = 1;
  const webvtt_byte *b = *pb;
  while( *b ) {
    webvtt_byte ch = *b;
    if( ASCII_ISDIGIT( ch ) ) {
      /**
       * Digit character, carry on
       */
      result = result * 10 + ( ch - ASCII_0 );
      ++digits;
    } else if( mul == 1 && digits == 0 && ch == ASCII_DASH ) {
      mul = -1;
    } else {
      break;
    }
    ++b;
  }
  *pb = b;
  if( pdigits ) {
    *pdigits = digits;
  }
  return result * mul;
}

/**
 * Turn the token of a TIMESTAMP tag into something useful, and returns non-zero
 * returns 0 if it fails
 */
static int
parse_timestamp( webvtt_parser self, const webvtt_byte *b, webvtt_timestamp *result )
{
  webvtt_int64 tmp;
  int have_hours = 0;
  int digits;
  int malformed = 0;
  webvtt_int64 v[4];
  if ( !ASCII_ISDIGIT( *b ) ) {
    goto _malformed;
  }

  /* get sequence of digits */
  v[0] = parse_int( &b, &digits );

  /**
   * assume v[0] contains hours if more or less than 2 digits, or value is
   * greater than 59
   */
  if ( digits != 2 || v[0] > 59 ) {
    have_hours = 1;
  }

  /* fail if missing colon ':' character */
  if ( !*b || *b++ != ASCII_COLON ) {
    malformed = 1;
  }

  /* fail if end of data reached, or byte is not an ASCII digit */
  if ( !*b || !ASCII_ISDIGIT( *b ) ) {
    malformed = 1;
  }

  /* get another integer value, fail if digits is not equal to 2 */
  v[1] = parse_int( &b, &digits );
  if( digits != 2 ) {
    malformed = 1;
  }

  /* if we already know there's an hour component, or if the next byte is a 
     colon ':', read the next value */
  if ( have_hours || ( *b == ASCII_COLON ) ) {
    if( *b++ != ASCII_COLON ) {
      goto _malformed;
    }
    if( !*b || !ASCII_ISDIGIT( *b ) ) {
      malformed = 1;
    }
    v[2] = parse_int( &b, &digits );
    if( digits != 2 ) {
      malformed = 1;
    }
  } else {
    /* Otherwise, if there is no hour component, shift everything over */
    v[2] = v[1];
    v[1] = v[0];
    v[0] = 0;
  }

  /* collect the manditory seconds-frac component. fail if there is no FULL_STOP
     '.' or if there is no ascii digit following it */
  if( *b++ != ASCII_PERIOD || !ASCII_ISDIGIT( *b ) ) {
    goto _malformed;
  }
  v[3] = parse_int( &b, &digits );
  if( digits != 3 ) {
    malformed = 1;
  }

  /* Ensure that minutes and seconds are acceptable values */
  if( v[3] > 999 ) {
#define MILLIS_PER_SEC (1000)
    tmp = v[3];
    v[2] += tmp / MILLIS_PER_SEC;
    v[3] = tmp % MILLIS_PER_SEC;
    malformed = 1;
  }
  if( v[2] > 59 ) {
#define SEC_PER_MIN (60)
    tmp = v[2];
    v[1] += tmp / SEC_PER_MIN;
    v[2] = tmp % SEC_PER_MIN;
    malformed = 1;
  }
  if( v[1] > 59 ) {
#define MIN_PER_HOUR (60)
    tmp = v[1];
    v[0] += tmp / MIN_PER_HOUR;
    v[1] = tmp % MIN_PER_HOUR;
    malformed = 1;
  }

  *result = ( webvtt_timestamp )( v[0] * MSECS_PER_HOUR )
            + ( v[1] * MSECS_PER_MINUTE )
            + ( v[2] * MSECS_PER_SECOND )
            + ( v[3] );

  if( malformed ) {
    return 0;
  }
  return 1;
_malformed:
  *result = 0xFFFFFFFFFFFFFFFF;
  return 0;
}
