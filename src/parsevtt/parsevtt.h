#ifndef __PARSEVTT_H__
#	define __PARSEVTT_H__

#	include <webvtt/parser.h>
#	include <stdio.h>

typedef struct parsevtt_t parsevtt_t;
typedef struct parsevtt_error_t parsevtt_error_t;
typedef struct parsevtt_error_list_t parsevtt_error_list_t;

struct
parsevtt_t
{
	const char *file_name;
	webvtt_parser parser;
	parsevtt_error_list_t *errors;
	FILE *fd;
};

struct
parsevtt_error_t
{
	webvtt_uint line;
	webvtt_uint column;
	const char *message;
};

struct
parsevtt_error_list_t
{
	webvtt_uint size;
	webvtt_uint alloc;
	parsevtt_error_t array[1];
};

webvtt_status parsevtt_init(parsevtt_t *parser, const char *file_name);
void parsevtt_cleanup(parsevtt_t *parser);
webvtt_status parsevtt_parse_file(parsevtt_t *parser);

#endif
