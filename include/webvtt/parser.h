#ifndef __WEBVTT_PARSER_H__
#	define __WEBVTT_PARSER_H__
#	include "string.h"
#	include "cue.h"
#	include "error.h"

typedef struct webvtt_parser_t *webvtt_parser;
typedef struct webvtt_struct_params_t webvtt_struct_params;

/**
 * Allows application to request error reporting
 */
typedef int (WEBVTT_CALLBACK *webvtt_error_fn_ptr)( void *userdata, webvtt_uint line, webvtt_uint col, 
	webvtt_error error );
typedef void (WEBVTT_CALLBACK *webvtt_cue_fn_ptr)( void *userdata, webvtt_cue cue );

	
WEBVTT_EXPORT webvtt_status webvtt_create_parser( webvtt_cue_fn_ptr on_read, webvtt_error_fn_ptr on_error, void *
									userdata, webvtt_parser *ppout );

void webvtt_delete_parser( webvtt_parser parser );
webvtt_status webvtt_parse_chunk( webvtt_parser self, const void *buffer, webvtt_uint len );
webvtt_status webvtt_finish_parsing( webvtt_parser self );

WEBVTT_EXPORT void webvtt_delete_parser( webvtt_parser parser );
WEBVTT_EXPORT webvtt_status webvtt_parse_chunk( webvtt_parser self, const void *buffer, webvtt_uint len );
WEBVTT_EXPORT webvtt_status webvtt_finish_parsing( webvtt_parser self );
WEBVTT_EXPORT webvtt_status webvtt_parse_cuetext( webvtt_wchar *cue_text, webvtt_node_ptr node_ptr );

#endif
