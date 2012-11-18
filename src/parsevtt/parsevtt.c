#include "parsevtt.h"
#include <errno.h>
#include <string.h>

static int WEBVTT_CALLBACK
report_error( void *userdata, webvtt_uint line, webvtt_uint col, webvtt_error errcode )
{
#	if 0
	fprintf(stderr, "`%s' at %u:%u -- error: %s\n", (const char *)userdata, line, col, webvtt_strerror( errcode ) );
	return -1; /* Die on all errors */
#	else
	/**
	 * We don't want to die on errors apparently, because we're weird? Instead we're keeping a dynamic array of errors?
	 */
	parsevtt_t *self = (parsevtt_t *)userdata;
	parsevtt_error_t *err;
	if( !self->errors )
	{
		self->errors = (parsevtt_error_list_t *)webvtt_alloc0( sizeof(parsevtt_error_list_t) + (sizeof(parsevtt_error_t) * 8 ) );
		self->errors->alloc = 8;
	}
	else if( self->errors->size + 1 >= ( ( self->errors->alloc / 3 ) * 2 ) )
	{
		parsevtt_error_list_t *new_list = (parsevtt_error_list_t *)webvtt_alloc0( sizeof(parsevtt_error_list_t) 
																				+ (sizeof(parsevtt_error_t) * (self->errors->alloc * 2)) );
		if( !new_list )
		{
			/**
			 * We failed to allocate, so just die, we're going to have nothing but trouble.
			 */
			return -1;
		}
		memcpy( new_list, self->errors, sizeof( parsevtt_error_list_t ) + ( sizeof( parsevtt_error_t ) * self->errors->size ) );
		webvtt_free( self->errors );
		self->errors = new_list;
	}
	err = self->errors->array + self->errors->size++;
	err->line = line;
	err->column = col;
	err->message = webvtt_strerror( errcode );
#	endif
}

static void WEBVTT_CALLBACK 
parsed_cue( void *userdata, webvtt_cue cue )
{
	webvtt_parse_cuetext( cue->payload->text, cue->node_head );
}


webvtt_status
parsevtt_init(parsevtt_t *self, const char *file_name)
{
	webvtt_status result = WEBVTT_SUCCESS;
	if( !self || !file_name )
	{
		return WEBVTT_INVALID_PARAM;
	}

	self->file_name = file_name;

	self->fd = fopen(file_name,"rb");
	self->errors = 0;

	if( !self->fd )
	{
		fprintf( stderr, "error: failed to open `%s'"
#ifdef WEBVTT_HAVE_STRERROR
		": %s"
#endif
		"\n", file_name
#ifdef WEBVTT_HAVE_STRERROR
		, strerror(errno)
#endif
		);
		return WEBVTT_UNSUCCESSFUL;
	}

	if( ( result = webvtt_create_parser( &parsed_cue, &report_error, (void *)self, &self->parser ,0) ) != WEBVTT_SUCCESS )
	{
		fprintf( stderr, "error: failed to create VTT parser.\n" );
		fclose( self->fd );
		return WEBVTT_UNSUCCESSFUL;
	}

	return WEBVTT_SUCCESS;
}

void
parsevtt_cleanup(parsevtt_t *self)
{
	if( self )
	{
		if( self->fd )
		{
			fclose( self->fd );
		}
		if( self->errors )
		{
			webvtt_free( self->errors );
		}
		if( self->parser )
		{
			webvtt_delete_parser( self->parser );
			self->parser = 0;
		}
	}
}

webvtt_status
parsevtt_parse_file(parsevtt_t *self)
{
	/**
	 * Try to parse the file.
	 */
	webvtt_status result;
	do
	{
		char buffer[0x1000];
		webvtt_uint n_read = (webvtt_uint)fread( buffer, 1, sizeof(buffer), self->fd );
		if( !n_read && feof( self->fd ) ) 
			break; /* Read the file successfully */
		result = webvtt_parse_chunk( self->parser, buffer, n_read );
			
		if( result == WEBVTT_PARSE_ERROR )
		{
			return result;
		}
	} while( result == WEBVTT_SUCCESS );
	if( (result = webvtt_finish_parsing( self->parser )) != WEBVTT_SUCCESS )
	{
		return result;
	}
	return WEBVTT_SUCCESS;;
}