#ifndef __INTERN_PARSER_H__
# define __INTERN_PARSER_H__
# include <webvtt/parser.h>
# include "string_internal.h"

#define ASCII_0 (0x30)
#define ASCII_9 (0x39)
#define ASCII_ISDIGIT(c) ( ((c) >= ASCII_0) && ((c) <= ASCII_9) )

typedef enum
webvtt_token_t {
  BADTOKEN = -2,
  UNFINISHED = -1, /* not-token */
  BOM,
  WEBVTT, /* 'WEBVTT' */
  NOTE, /* 'NOTE' */
  INTEGER, /* /-?\d+/ */
  NEWLINE, /* /[\r\n]|(\r\n)/ */
  WHITESPACE, /* /[\t ]/ */
  FULL_STOP, /* '.' */
  POSITION, /* 'position:' */
  ALIGN, /* 'align:' */
  SIZE, /* 'size:' */
  LINE, /* 'line:' */
  VERTICAL, /* 'vertical:' */
  RL, /* 'rl' */
  LR, /* 'lr' */
  START, /* 'start' */
  MIDDLE, /* 'middle' */
  END, /* 'end' */
  LEFT, /* 'left' */
  RIGHT, /* 'right' */
  SEPARATOR, /* '-->' */
  TIMESTAMP,
  PERCENTAGE, /* '\d+%' */
  COLON, /* ':' */
} webvtt_token;

typedef enum
webvtt_state_value_type_t {
  V_NONE,
  V_POINTER,
  V_INTEGER,
  V_CUE,
  V_TEXT,
  V_LNODE,
  V_INODE,
  V_TOKEN,
} webvtt_state_value_type;

typedef enum
webvtt_parse_mode_t {
  M_WEBVTT = 0,
  M_CUETEXT,
  M_SKIP_CUE,
  M_READ_LINE,
} webvtt_parse_mode;


typedef enum
webvtt_parse_state_t {
  /**
   * WEBVTT parse states
   */
  T_INITIAL = 0,
  T_TAG,
  T_TAGCOMMENT,
  T_EOL,
  T_BODY,

  T_CUEREAD, /* Read a line of text for a cue */
  T_CUE, /* T_CUEID T_CUEPARAMS T_CUETEXT NEWLINE */
  T_CUEID, /* T_LINE !~ SEPARATOR && LINE !~ ^NOTE NEWLINE */
  T_CUEPARAMS, /* TIMESTAMP WHITESPACE? SEPARATOR WHITESPACE? T_CUESETTING* NEWLINE */
  T_CUETEXT, /* T_LINE !~ SEPARATOR NEWLINE NEWLINE */

  T_TIMESTAMP, /* This looked like a timestamp to the lexer, may or may not be valid. */

  /**
   * NOTE comments
   */
  T_COMMENT,

  /**
   * Cue times
   */
  T_FROM,
  T_SEP_LEFT,
  T_SEP,
  T_SEP_RIGHT,
  T_UNTIL,

  /**
   * Cue settings
   */
  T_PRECUESETTING,
  T_CUESETTING,
  T_CUESETTING_DELIMITER,
  T_CUESETTING_VALUE,
  T_SKIP_SETTING /* We have to skip a cue-setting because of an error. */

  /**
   * Cue text parse states
   */
} webvtt_parse_state;

/**
 * lexer state
 */
typedef enum
webvtt_lexer_state_t {
  L_START = 0, L_BOM0, L_BOM1, L_WEBVTT0, L_WEBVTT1, L_WEBVTT2, L_WEBVTT3, L_WEBVTT4, L_WEBVTT5, L_DASH0, L_SEP1,
  L_DIGIT0, L_NEWLINE0, L_WHITESPACE, L_POSITION0, L_POSITION1, L_POSITION2, L_POSITION3, L_POSITION4, L_POSITION5,
  L_POSITION6, L_ALIGN0, L_ALIGN1, L_ALIGN2, L_ALIGN3, L_L0, L_LINE1, L_LINE2, L_LINE3,
  L_VERTICAL0, L_VERTICAL1, L_VERTICAL2, L_VERTICAL3, L_VERTICAL4, L_VERTICAL5, L_VERTICAL6, L_RL0,
  L_S0, L_SIZE1, L_SIZE2, L_START1, L_START2, L_START3, L_MIDDLE0, L_MIDDLE1, L_MIDDLE2, L_MIDDLE3,
  L_MIDDLE4, L_END0, L_END1, L_TIMESTAMP1, L_TIMESTAMP2, L_TIMESTAMP3, L_RIGHT1, L_RIGHT2,
  L_RIGHT3, L_NOTE1, L_NOTE2, L_NOTE3, L_LEFT1, L_LEFT2,
} webvtt_lexer_state;

typedef struct webvtt_state webvtt_state;

typedef webvtt_status (*webvtt_parse_callback)( webvtt_parser self,
  webvtt_state *state, const webvtt_byte *text, webvtt_uint *pos, webvtt_uint length );

WEBVTT_INTERN webvtt_status webvtt_read_cuetext_line( webvtt_parser self,
  webvtt_state *st, const webvtt_byte *text, webvtt_uint *pos, webvtt_uint len );

WEBVTT_INTERN webvtt_status webvtt_read_cuetext( webvtt_parser self,
  webvtt_state *st, const webvtt_byte *text, webvtt_uint *pos, webvtt_uint length );

WEBVTT_INTERN webvtt_status webvtt_parse_cue( webvtt_parser self,
  webvtt_state *st, const webvtt_byte *text, webvtt_uint *pos, webvtt_uint len );

WEBVTT_INTERN webvtt_status webvtt_read_settings( webvtt_parser self,
  webvtt_state *st, const webvtt_byte *text, webvtt_uint *pos, webvtt_uint len );

WEBVTT_INTERN webvtt_status webvtt_parse_settings( webvtt_parser self,
  webvtt_state *st, const webvtt_byte *text, webvtt_uint *pos, webvtt_uint length );

WEBVTT_INTERN webvtt_status webvtt_parse_params( webvtt_parser self,
  webvtt_cue *st, const webvtt_byte *text, webvtt_uint *pos, webvtt_uint len );

WEBVTT_INTERN webvtt_status webvtt_parse_size( webvtt_parser self,
  webvtt_cue *st, const webvtt_byte *text, webvtt_uint *pos, webvtt_uint len );
WEBVTT_INTERN webvtt_status webvtt_parse_align( webvtt_parser self,
  webvtt_cue *st, const webvtt_byte *text, webvtt_uint *pos, webvtt_uint len );
WEBVTT_INTERN webvtt_status webvtt_parse_position( webvtt_parser self,
  webvtt_cue *st, const webvtt_byte *text, webvtt_uint *pos, webvtt_uint len );
WEBVTT_INTERN webvtt_status webvtt_parse_vertical( webvtt_parser self,
  webvtt_cue *st, const webvtt_byte *text, webvtt_uint *pos, webvtt_uint len );
WEBVTT_INTERN webvtt_status webvtt_parse_line( webvtt_parser self,
  webvtt_cue *st, const webvtt_byte *text, webvtt_uint *pos, webvtt_uint len );

WEBVTT_INTERN webvtt_status webvtt_parse_header( webvtt_parser self,
  webvtt_state *st, const webvtt_byte *text, webvtt_uint *pos, webvtt_uint length );

WEBVTT_INTERN webvtt_status webvtt_parse_body( webvtt_parser self,
  webvtt_state *st, const webvtt_byte *text, webvtt_uint *pos, webvtt_uint len );

enum
webvtt_header_flags {
  WEBVTT_HEADER_START = 0,
  WEBVTT_HEADER_TAG,
  WEBVTT_HEADER_COMMENT,
  WEBVTT_HEADER_EOL,
};

struct
webvtt_state {
  webvtt_parse_callback callback;
  webvtt_token token;
  webvtt_state_value_type type;
  webvtt_uint line;
  webvtt_uint column;
  webvtt_uint flags;
  union {
    /**
     * cue value
     */
    webvtt_cue *cue;

    /**
     * string value
     */
    webvtt_string text;

    /**
     * The cuetext parser is not currently using the state stack, and
     * because of this, 'node' is never actually used.
     *
     * It is here if the cuetext parser begins to use the/a state stack
     * in the future.
     */
    webvtt_node *node;

    /**
     * unsigned integer value
     */
    webvtt_uint value;
  } v;
};

typedef enum
webvtt_parser_flags_t {
  HAVE_MALFORMED_TAG = 0x80000000,
} webvtt_parser_flags;

struct
webvtt_parser_t {
  webvtt_uint flags;
  webvtt_bool finish;
  webvtt_uint bytes; /* number of bytes read. */
  webvtt_uint line;
  webvtt_uint column;
  webvtt_cue_fn read;
  webvtt_error_fn error;
  void *userdata;

  /**
   * 'mode' can have several states, it is not boolean.
   */
  webvtt_parse_mode mode;

  webvtt_state *top; /* Top parse state */
  webvtt_state astack[0x100];
  webvtt_state *stack; /* dynamically allocated stack, if 'astack' fills up */
  webvtt_uint stack_alloc; /* item capacity in 'stack' */
  webvtt_bool popped;

  /**
   * line (cue payload also stored here)
   */
  int truncate;
  webvtt_uint line_pos;
  webvtt_string line_buffer;

  /**
   * tokenizer
   */
  webvtt_lexer_state tstate;
  webvtt_uint token_pos;
  webvtt_byte token[0x100];
};

WEBVTT_INTERN webvtt_token webvtt_lex( webvtt_parser self, const webvtt_byte *buffer, webvtt_uint *pos, webvtt_uint length, webvtt_bool finish );
WEBVTT_INTERN webvtt_status webvtt_lex_word( webvtt_parser self, webvtt_string *pba, const webvtt_byte *buffer, webvtt_uint *pos, webvtt_uint length, webvtt_bool finish );

#define BAD_TIMESTAMP(ts) ( ( ts ) == 0xFFFFFFFFFFFFFFFF )

#define ERROR_AT(Code,Line, Column) \
do \
{ \
  if( !self->error || self->error(self->userdata,(Line),(Column),Code) < 0 ) \
    return WEBVTT_PARSE_ERROR; \
} while(0)

#define ERROR(Code) ERROR_AT( ( Code ), self->line, self->column )

#define ERROR_AT_COLUMN(Code,Column) ERROR_AT( ( Code ), self->line, ( Column ) )

#endif
