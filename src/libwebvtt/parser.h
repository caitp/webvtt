#ifndef __PARSER_H__
#	define __PARSER_H__
#	include <webvtt/parser.h>
#	include "bytearray.h"

typedef enum webvtt_token_t webvtt_token;

#define  CR (0x0D)
#define  LF (0x0A)
#define SPC (0x20)
#define TAB (0x09)

enum
webvtt_token_t
{
	BADTOKEN = -2,
	UNFINISHED = -1, /* not-token */
	BOM,
	WEBVTT, /* 'WEBVTT' */
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
	SEPARATOR, /* '-->' */
	TIMESTAMP,
	PERCENTAGE
};

/**
 * Flags indicating which settings have been read
 */
#define READ_VERTICAL (1<<0)
#define READ_SIZE (1<<1)
#define READ_POSITION (1<<2)
#define READ_LINE (1<<3)
#define READ_ALIGN (1<<4)

struct
webvtt_parser_t
{
	webvtt_uint state;
	webvtt_uint bytes; /* number of bytes read. */
	webvtt_uint line;
	webvtt_uint column;
	webvtt_cue_fn_ptr read;
	webvtt_error_fn_ptr error;
	void *userdata;
	webvtt_bool mode;
	webvtt_bool finish;
	webvtt_uint flags;
	/**
	 * Current cue
	 */
	webvtt_cue cue;

	/**
	 * line
	 */
	int truncate;
	webvtt_uint line_pos;
	webvtt_bytearray line_buffer;

	/**
	 * tokenizer
	 */
	webvtt_uint tstate;
	webvtt_uint token_pos;
	webvtt_byte token[0x100];

	/**
	 * Error Object List
	 */
	vtt_error_t* error_list;
	webvtt_uint error_list_size;
};

WEBVTT_INTERN webvtt_token webvtt_lex( webvtt_parser self, webvtt_byte *buffer, webvtt_uint *pos, webvtt_uint length, int finish );

#define ERROR(Code) \
do \
{ \
	if( !self->error || self->error(self->userdata,self->line,self->column,Code) < 0 ) \
		return WEBVTT_PARSE_ERROR; \
} while(0)


#endif
