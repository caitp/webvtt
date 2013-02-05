#include "parser_internal.h"
#include "cuetext_internal.h"
#include "cue_internal.h"
#include <string.h>

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

#define ASCII_DASH (0x2D)
#define ASCII_COLON  (0x3A)

#define MSECS_PER_HOUR (3600000)
#define MSECS_PER_MINUTE (60000)
#define MSECS_PER_SECOND (1000)
#define BUFFER (self->buffer + self->position)
#define MALFORMED_TIME ((webvtt_timestamp_t)-1.0)

static int find_bytes( const webvtt_byte *buffer, webvtt_uint len, const webvtt_byte *sbytes, webvtt_uint slen );
static webvtt_int64 parse_int( const webvtt_byte **pb, int *pdigits );
static int parse_timestamp( webvtt_parser self, const webvtt_byte *b, webvtt_timestamp *result );

WEBVTT_INTERN webvtt_status
webvtt_read_id( webvtt_parser self, webvtt_state *st, const webvtt_byte *text,
  webvtt_uint *pos, webvtt_uint length )
{
}

WEBVTT_INTERN webvtt_status
webvtt_read_settings( webvtt_parser self, webvtt_state *st, const webvtt_byte *text,
  webvtt_uint *pos, webvtt_uint length )
{
}

WEBVTT_INTERN webvtt_status
webvtt_read_cuetext( webvtt_parser self, webvtt_state *st, const webvtt_byte *text,
  webvtt_uint *pos, webvtt_uint length )
{
}

WEBVTT_INTERN webvtt_status
webvtt_parse_settings( webvtt_parser self, webvtt_state *st, const webvtt_byte *text,
  webvtt_uint *pos, webvtt_uint length )
{
}

/**
 * Read a WEBVTT header
 */
WEBVTT_INTERN webvtt_status
webvtt_parse_header( webvtt_parser self, webvtt_state *st, const webvtt_byte *text,
  webvtt_uint *pos, webvtt_uint len )
{
  int v;
  webvtt_token token;
  while( *pos < len )
  {
    CALLBACK_DATA
    switch( st->flags )
    {
    case 0:
      token = webvtt_lex( self, text, pos, len, 0 );
      switch( token ) {
        case UNFINISHED:
          return WEBVTT_SUCCESS;
    
        case WEBVTT:
          st->flags = WEBVTT_HEADER_TAG;
          break;

        default:
          ERROR(WEBVTT_MALFORMED_TAG);
          return WEBVTT_PARSE_ERROR;
      }
      break;
    case WEBVTT_HEADER_TAG:
      token = webvtt_lex( self, text, pos, len, 0 );
      switch( token ) {
        case WHITESPACE:
          st->flags = WEBVTT_HEADER_COMMENT;
          break;

        case NEWLINE:
          st->flags = 0;
          st->callback = &webvtt_parse_body;
          return WEBVTT_SUCCESS;

        default:
          ERROR(WEBVTT_MALFORMED_TAG);
          return WEBVTT_PARSE_ERROR;
      }
      break;

    case WEBVTT_HEADER_COMMENT:
      st->type = V_TEXT;
      webvtt_init_string( &st->v.text );
      v = webvtt_string_getline( &st->v.text, text, pos, len, 0, 0, 0 );
      if( v < 0 ) {
        webvtt_release_string( &st->v.text );
        ERROR( WEBVTT_ALLOCATION_FAILED );
        return WEBVTT_OUT_OF_MEMORY;
      }
      if( v > 0 ) {
        if( webvtt_lex( self, text, pos, len, 0 ) == NEWLINE ) {
          webvtt_release_string( &st->v.text );
          st->flags = WEBVTT_HEADER_EOL;
        }
      }
      break;

    case WEBVTT_HEADER_EOL:
      token = webvtt_lex( self, text, pos, len, 0 );
      switch( token ) {
        case NEWLINE:
          st->flags = 0;
          st->callback = &webvtt_parse_body;
          return WEBVTT_SUCCESS;

        default:
          *pos -= self->token_pos;
        case BADTOKEN:
          /* error, expected eol */
          ERROR(WEBVTT_EXPECTED_EOL);
          st->callback = &webvtt_parse_body;
          return WEBVTT_SUCCESS;
      }
    }
  }
}

/**
 * Parse Cue ID
 */
WEBVTT_INTERN webvtt_status
webvtt_parse_id( webvtt_parser self, webvtt_state *st, const webvtt_byte *text,
  webvtt_uint *pos, webvtt_uint len )
{
  int v;
  if( st->type == V_NONE ) {
    webvtt_init_string( &st->v.text );
  }
  
  v = webvtt_string_getline( &st->v.text, text, pos, len, 0, 0, 0 );
  
  if( v < 0 ) {
    ERROR( WEBVTT_ALLOCATION_FAILED );
    return WEBVTT_OUT_OF_MEMORY;
  }

  if( v > 0 ) {
    static const webvtt_byte separator[] = {
      ASCII_DASH, ASCII_DASH, ASCII_GT
    };
    if( find_bytes( webvtt_string_text( &st->v.text ), webvtt_string_length( &st->v.text ),
          separator, sizeof( separator ) ) ) {
      st->callback = webvtt_parse_settings;
      return WEBVTT_SUCCESS;
    }
  } else {
    /**
     * TODO: Create new Cue object if none exists, and
     * give ownership of the cue id string to it.
     * FRAME(1)->
     */
  }
}

/**
 * Parse a Cue
 */
WEBVTT_INTERN webvtt_status
webvtt_parse_cue( webvtt_parser self, webvtt_state *st, const webvtt_byte *text,
  webvtt_uint *pos, webvtt_uint len )
{
}

/**
 * Parse body of webvtt file
 */
WEBVTT_INTERN webvtt_status
webvtt_parse_body( webvtt_parser self, webvtt_state *st, const webvtt_byte *text,
  webvtt_uint *pos, webvtt_uint len )
{
  while( *pos < len ) {
    CALLBACK_DATA
    webvtt_token token = webvtt_lex( self, text, pos, len. 0 );
    switch( token ) {
    case NEWLINE:
      break;

    default:
       self->column -= self->token_pos;
       self->bytes -= self->token_pos;
       PUSH( &webvtt_parse_cue, 0, V_NONE );
       PUSH( &webvtt_parse_id, 0, V_NONE );
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
 * Helper to validate a cue and, if valid, notify the application that a cue has been read.
 * If it fails to validate, silently delete the cue.
 *
 * ( This might not be the best way to go about this, and additionally, webvtt_validate_cue
 *   has no means to report errors with the cue, and we do nothing with its return value )
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
/**
 * More state stack helpers
 */
static webvtt_status
do_push( webvtt_parser self, webvtt_uint token, webvtt_uint back,
webvtt_parse_callback callback,
  void *data, webvtt_state_value_type type, webvtt_uint line, webvtt_uint column )
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

#define PUSH0(S,V,T) \
do { \
    self->popped = 0; \
    if( do_push(self,token,BACK+1,(S),(void*)(V),T,last_line, last_column) \
      == WEBVTT_OUT_OF_MEMORY ) \
      return WEBVTT_OUT_OF_MEMORY; \
  } while(0)

#define PUSH(S,B,V,T) \
do { \
  self->popped = 0; \
  if( do_push(self,token,(B),(S),(void*)(V),T,last_line, last_column) \
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

WEBVTT_INTERN int
parse_cueparams( webvtt_parser self, const webvtt_byte *buffer,
                 webvtt_uint len, webvtt_cue *cue )
{
  int digits;
  int have_ws = 0;
  int unexpected_whitespace = 0;
  webvtt_uint baddelim = 0;
  webvtt_uint pos = 0;
  webvtt_token last_token = 0;
  enum cp_state {
    CP_T1, CP_T2, CP_T3, CP_T4, CP_T5, /* 'start' cuetime, whitespace1,
                   'separator', whitespace2, 'end' cuetime */
    CP_CS0, /* pre-cuesetting */

    CP_SD, /* cuesettings delimiter here */

    CP_V1, /* 'vertical' cuesetting */
    CP_P1, /* 'position' cuesetting */
    CP_A1, /* 'align' cuesetting */
    CP_S1, /* 'size' cuesetting */
    CP_L1, /* 'line' cuesetting */

    CP_SV, /* cuesettings value here */

    CP_V2,
    CP_P2,
    CP_A2,
    CP_S2,
    CP_L2,
  };

  enum cp_state last_state = CP_T1;
  enum cp_state state = CP_T1;

#define SETST(X) do { baddelim = 0; last_state = state; state = (X); } while( 0 )

  self->token_pos = 0;
  while( pos < len ) {
    webvtt_uint last_column = self->column;
    webvtt_token token = webvtt_lex( self, buffer, &pos, len, 1 );
_recheck:
    switch( state ) {
        /* start timestamp */
      case CP_T1:
        if( token == WHITESPACE && !unexpected_whitespace ) {
          ERROR_AT_COLUMN( WEBVTT_UNEXPECTED_WHITESPACE, self->column );
          unexpected_whitespace = 1;
        } else if( token == TIMESTAMP )
          if( !parse_timestamp( self, self->token, &cue->from ) ) {
            ERROR_AT_COLUMN(
              ( BAD_TIMESTAMP( cue->from )
                ? WEBVTT_EXPECTED_TIMESTAMP
                : WEBVTT_MALFORMED_TIMESTAMP ), last_column  );
            if( !ASCII_ISDIGIT( self->token[self->token_pos - 1] ) ) {
              while( pos < len && buffer[pos] != 0x09 && buffer[pos] != 0x20 ) { ++pos; }
            }
            if( BAD_TIMESTAMP( cue->from ) )
            { return -1; }
            SETST( CP_T2 );
          } else {
            SETST( CP_T2 );
          }
        else {
          ERROR_AT_COLUMN( WEBVTT_EXPECTED_TIMESTAMP, last_column );
          return -1;
        }
        break;
        /* end timestamp */
      case CP_T5:
        if( token == WHITESPACE ) {
          /* no problem, just ignore it and continue */
        } else if( token == TIMESTAMP )
          if( !parse_timestamp( self, self->token, &cue->until ) ) {
            ERROR_AT_COLUMN(
              ( BAD_TIMESTAMP( cue->until )
                ? WEBVTT_EXPECTED_TIMESTAMP
                : WEBVTT_MALFORMED_TIMESTAMP ), last_column  );
            if( !ASCII_ISDIGIT( self->token[self->token_pos - 1] ) ) {
              while( pos < len && buffer[pos] != 0x09 && buffer[pos] != 0x20 ) { ++pos; }
            }
            if( BAD_TIMESTAMP( cue->until ) )
            { return -1; }
            SETST( CP_CS0 );
          } else {
            SETST( CP_CS0 );
          }
        else {
          ERROR_AT_COLUMN( WEBVTT_EXPECTED_TIMESTAMP, last_column );
          return -1;
        }
        break;

        /* whitespace 1 */
      case CP_T2:
        switch( token ) {
          case SEPARATOR:
            ERROR_AT_COLUMN( WEBVTT_EXPECTED_WHITESPACE, last_column );
            SETST( CP_T4 );
            break;
          case WHITESPACE:
            SETST( CP_T3 );
            break;
        }
        break;
      case CP_T3:
        switch( token ) {
          case WHITESPACE: /* ignore this whitespace */
            break;

          case SEPARATOR:
            SETST( CP_T4 );
            break;

          case TIMESTAMP:
            ERROR( WEBVTT_MISSING_CUETIME_SEPARATOR );
            SETST( CP_T5 );
            goto _recheck;

          default: /* some garbage */
            ERROR_AT_COLUMN( WEBVTT_EXPECTED_CUETIME_SEPARATOR, last_column );
            return -1;
        }
        break;
      case CP_T4:
        switch( token ) {
          case WHITESPACE:
            SETST( CP_T5 );
            break;
          case TIMESTAMP:
            ERROR_AT_COLUMN( WEBVTT_EXPECTED_WHITESPACE, last_column );
            goto _recheck;
          default:
            ERROR_AT_COLUMN( WEBVTT_EXPECTED_WHITESPACE, last_column );
            goto _recheck;
        }
        break;
#define CHKDELIM \
if( baddelim ) \
  ERROR_AT_COLUMN(WEBVTT_INVALID_CUESETTING_DELIMITER,baddelim); \
else if( !have_ws ) \
  ERROR_AT_COLUMN(WEBVTT_EXPECTED_WHITESPACE,last_column);

        /**
         * This section is "pre-cuesetting". We are expecting whitespace, followed by
         * a cuesetting keyword
         *
         * If we don't see a keyword, but have our whitespace, it is considered a bad keyword
         * (invalid cuesetting)
         *
         * Otherwise, if we don't have whitespace and have a bad token, it's an invalid
         * delimiter
         */
      case CP_CS0:
        switch( token ) {
          case WHITESPACE:
            have_ws = last_column;
            break;
          case COLON:
            ERROR_AT_COLUMN( WEBVTT_MISSING_CUESETTING_KEYWORD, last_column );
            break;
          case VERTICAL:
            CHKDELIM have_ws = 0;
            SETST( CP_V1 );
            break;
          case POSITION:
            CHKDELIM have_ws = 0;
            SETST( CP_P1 );
            break;
          case ALIGN:
            CHKDELIM have_ws = 0;
            SETST( CP_A1 );
            break;
          case SIZE:
            CHKDELIM have_ws = 0;
            SETST( CP_S1 );
            break;
          case LINE:
            CHKDELIM have_ws = 0;
            SETST( CP_L1 );
            break;
          default:
            if( have_ws ) {
              ERROR_AT_COLUMN( WEBVTT_INVALID_CUESETTING, last_column );
              while( pos < len && buffer[pos] != 0x09 && buffer[pos] != 0x20 ) { ++pos; }
            } else if( token == BADTOKEN ) {
              /* it was a bad delimiter... */
              if( !baddelim ) {
                baddelim = last_column;
              }
              ++pos;
            }
        }
        break;
#define CS1(S) \
  if( token == COLON ) \
  { if(have_ws) { ERROR_AT_COLUMN(WEBVTT_UNEXPECTED_WHITESPACE,have_ws); } SETST((S)); have_ws = 0; } \
  else if( token == WHITESPACE && !have_ws ) \
  { \
    have_ws = last_column; \
  } \
  else \
  { \
    switch(token) \
    { \
    case LR: case RL: case INTEGER: case PERCENTAGE: case START: case MIDDLE: case END: case LEFT: case RIGHT: \
       ERROR_AT_COLUMN(WEBVTT_MISSING_CUESETTING_DELIMITER,have_ws ? have_ws : last_column); break; \
    default: \
      ERROR_AT_COLUMN(WEBVTT_INVALID_CUESETTING_DELIMITER,last_column); \
      while( pos < len && buffer[pos] != 0x20 && buffer[pos] != 0x09 ) ++pos; \
      break; \
    } \
    have_ws = 0; \
  }

        /**
         * If we get a COLON, we advance to the next state.
         * If we encounter whitespace first, fire an "unexpected whitespace" error and continue.
         * If we encounter a cue-setting value, fire a "missing cuesetting delimiter" error
         * otherwise (eg vertical;rl), fire "invalid cuesetting delimiter" error
         *
         * this logic is performed by the CS1 macro, defined above
         */
      case CP_V1:
        CS1( CP_V2 );
        break;
      case CP_P1:
        CS1( CP_P2 );
        break;
      case CP_A1:
        CS1( CP_A2 );
        break;
      case CP_S1:
        CS1( CP_S2 );
        break;
      case CP_L1:
        CS1( CP_L2 );
        break;
#undef CS1

        /* BV: emit the BAD_VALUE error for the appropriate setting, when required */
#define BV(T) \
ERROR_AT_COLUMN(WEBVTT_##T##_BAD_VALUE,last_column); \
while( pos < len && buffer[pos] != 0x20 && buffer[pos] != 0x09 ) ++pos; \
SETST(CP_CS0);

        /* HV: emit the ALREADY_SET (have value) error for the appropriate setting, when required */
#define HV(T) \
if( cue->flags & CUE_HAVE_##T ) \
{ \
  ERROR_AT_COLUMN(WEBVTT_##T##_ALREADY_SET,last_column); \
}
        /* WS: emit the WEBVTT_UNEXPECTED_WHITESPACE error when required. */
#define WS \
case WHITESPACE: \
  if( !have_ws ) \
  { \
    ERROR_AT_COLUMN(WEBVTT_UNEXPECTED_WHITESPACE,last_column); \
    have_ws = last_column; \
  } \
break

        /* set that the cue already has a value for this */
#define SV(T) cue->flags |= CUE_HAVE_##T
      case CP_V2:
        HV( VERTICAL );
        switch( token ) {
            WS;
          case LR:
            cue->settings.vertical = WEBVTT_VERTICAL_LR;
            have_ws = 0;
            SETST( CP_CS0 );
            SV( VERTICAL );
            break;
          case RL:
            cue->settings.vertical = WEBVTT_VERTICAL_RL;
            have_ws = 0;
            SETST( CP_CS0 );
            SV( VERTICAL );
            break;
          default:
            BV( VERTICAL );
        }
        break;

      case CP_P2:
        HV( POSITION );
        switch( token ) {
            WS;
          case PERCENTAGE: {
            int digits;
            const webvtt_byte *t = self->token;
            webvtt_int64 v = parse_int( &t, &digits );
            if( v < 0 ) {
              BV( POSITION );
            }
            cue->settings.position = ( webvtt_uint )v;
            SETST( CP_CS0 );
            SV( POSITION );
          }
          break;
          default:
            BV( POSITION );
            break;
        }
        break;

      case CP_A2:
        HV( ALIGN );
        switch( token ) {
            WS;
          case START:
            cue->settings.align = WEBVTT_ALIGN_START;
            have_ws = 0;
            SETST( CP_CS0 );
            SV( ALIGN );
            break;
          case MIDDLE:
            cue->settings.align = WEBVTT_ALIGN_MIDDLE;
            have_ws = 0;
            SETST( CP_CS0 );
            SV( ALIGN );
            break;
          case END:
            cue->settings.align = WEBVTT_ALIGN_END;
            have_ws = 0;
            SETST( CP_CS0 );
            SV( ALIGN );
            break;
          case LEFT:
            cue->settings.align = WEBVTT_ALIGN_LEFT;
            have_ws = 0;
            SETST( CP_CS0 );
            SV( ALIGN );
            break;
          case RIGHT:
            cue->settings.align = WEBVTT_ALIGN_RIGHT;
            have_ws = 0;
            SETST( CP_CS0 );
            SV( ALIGN );
            break;
          default:
            BV( ALIGN );
            break;
        }
        break;

      case CP_S2:
        HV( SIZE );
        switch( token ) {
            WS;
          case PERCENTAGE: {
            int digits;
            const webvtt_byte *t = self->token;
            webvtt_int64 v = parse_int( &t, &digits );
            if( v < 0 ) {
              BV( SIZE );
            }
            cue->settings.size = ( webvtt_uint )v;
            SETST( CP_CS0 );
            SV( SIZE );
          }
          break;
          default:
            BV( SIZE );
            break;
        }
        break;

      case CP_L2:
        HV( LINE );
        switch( token ) {
            WS;
          case INTEGER: {
            const webvtt_byte *t = self->token;
            webvtt_int64 v = parse_int( &t, &digits );
            cue->settings.line_is_relative = 0;
            cue->settings.line.no = ( webvtt_int )v;
            SETST( CP_CS0 );
            SV( LINE );
          }
          break;
          case PERCENTAGE: {
            const webvtt_byte *t = self->token;
            webvtt_int64 v = parse_int( &t, &digits );
            if( v < 0 ) {
              BV( POSITION );
            }
            cue->settings.line.relative_position = ( webvtt_uint )v;
            SETST( CP_CS0 );
            SV( LINE );
          }
          break;
          default:
            BV( LINE );
            break;
        }
#undef BV
#undef HV
#undef SV
#undef WS
    }
    self->token_pos = 0;
    last_token = token;
  }
  /**
   * If we didn't finish in a good state...
   */
  if( state != CP_CS0 ) {
    /* if we never made it to the cuesettings, we didn't finish the cuetimes */
    if( state < CP_CS0 ) {
      ERROR( WEBVTT_UNFINISHED_CUETIMES );
      return -1;
    } else {
      /* if we did, we should report an error but continue parsing. */
      webvtt_error e = WEBVTT_INVALID_CUESETTING;
      switch( state ) {
        case CP_V2:
          e = WEBVTT_VERTICAL_BAD_VALUE;
          break;
        case CP_P2:
          e = WEBVTT_POSITION_BAD_VALUE;
          break;
        case CP_A2:
          e = WEBVTT_ALIGN_BAD_VALUE;
          break;
        case CP_S2:
          e = WEBVTT_SIZE_BAD_VALUE;
          break;
        case CP_L2:
          e = WEBVTT_LINE_BAD_VALUE;
          break;
      }
      ERROR( e );
    }
  } else {
    if( baddelim ) {
      ERROR_AT_COLUMN( WEBVTT_INVALID_CUESETTING_DELIMITER, baddelim );
    }
  }
#undef SETST
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

  return WEBVTT_SUCCESS;
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

  /* assume v[0] contains hours if more or less than 2 digits, or value is greater than 59 */
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

  /* if we already know there's an hour component, or if the next byte is a colon ':',
     read the next value */
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

  /* collect the manditory seconds-frac component. fail if there is no FULL_STOP '.'
     or if there is no ascii digit following it */
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
