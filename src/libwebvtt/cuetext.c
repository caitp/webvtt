#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "cuetext.h"
#include "cue.h"

/**
 * ERROR macro used for webvtt_parse_cuetext
 */
#undef ERROR
#define ERROR(code) \
do \
{ \
	if( self->error ) \
		if( self->error( self->userdata, line, col, code ) < 0 ) \
			return WEBVTT_PARSE_ERROR; \
} while(0)

/**
 * Macros for return statuses based on memory operations.
 * This is to avoid many if statements checking for multiple memory operation return statuses in functions.
 */
#define CHECK_MEMORY_OP(status) \
	if( status != WEBVTT_SUCCESS ) \
		return status; \

#define CHECK_MEMORY_OP_JUMP(status_var, returned_status) \
	if( returned_status != WEBVTT_SUCCESS) \
	{ \
		status_var = returned_status; \
		goto dealloc; \
	} \

WEBVTT_INTERN webvtt_status
webvtt_create_cue_text_token( webvtt_cue_text_token_ptr *token_pptr, void *concrete_token, webvtt_cue_text_token_type token_type )
{
	webvtt_cue_text_token_ptr temp_token_ptr = (webvtt_cue_text_token_ptr)malloc(sizeof(*temp_token_ptr));

	if( !temp_token_ptr ) 
		return WEBVTT_OUT_OF_MEMORY;

	temp_token_ptr->concrete_token = concrete_token;
	temp_token_ptr->token_type = token_type;
	*token_pptr = temp_token_ptr;

	return WEBVTT_SUCCESS;
}

WEBVTT_INTERN webvtt_status
webvtt_create_cue_text_start_tag_token( webvtt_cue_text_token_ptr *token_pptr, webvtt_string tag_name, 
	webvtt_string_list_ptr css_classes_ptr, webvtt_string annotation )
{
	webvtt_cue_text_start_tag_token_ptr start_token_ptr = (webvtt_cue_text_start_tag_token_ptr)malloc(sizeof(*start_token_ptr));

	if( !start_token_ptr )
		return WEBVTT_OUT_OF_MEMORY;

	start_token_ptr->tag_name = tag_name;
	start_token_ptr->css_classes_ptr = css_classes_ptr;
	start_token_ptr->annotations = annotation;

	return webvtt_create_cue_text_token( token_pptr, (void *)start_token_ptr, START_TOKEN );	
}

WEBVTT_INTERN webvtt_status
webvtt_create_cue_text_end_tag_token( webvtt_cue_text_token_ptr *token_pptr, webvtt_string tag_name )
{
	webvtt_cue_text_end_tag_token_ptr end_token_ptr = (webvtt_cue_text_end_tag_token_ptr)malloc(sizeof(*end_token_ptr));

	if( !end_token_ptr )
		return WEBVTT_OUT_OF_MEMORY;

	end_token_ptr->tag_name = tag_name;

	return webvtt_create_cue_text_token( token_pptr, (void *)end_token_ptr, END_TOKEN );
}

WEBVTT_INTERN webvtt_status 
webvtt_create_cue_text_text_token( webvtt_cue_text_token_ptr *token_pptr, webvtt_string text )
{
	webvtt_cue_text_text_token_ptr text_token_ptr = (webvtt_cue_text_text_token_ptr)malloc(sizeof(*text_token_ptr));

	if( !text_token_ptr )
		return WEBVTT_OUT_OF_MEMORY;

	text_token_ptr->text = text;

	return webvtt_create_cue_text_token( token_pptr, (void *)text_token_ptr, TEXT_TOKEN );
}

WEBVTT_INTERN webvtt_status
webvtt_create_cue_text_time_stamp_token( webvtt_cue_text_token_ptr *token_pptr, webvtt_timestamp time_stamp )
{
	webvtt_cue_text_time_stamp_token_ptr time_stamp_token_ptr = (webvtt_cue_text_time_stamp_token_ptr)malloc(sizeof(*time_stamp_token_ptr));

	if( !time_stamp_token_ptr )
		return WEBVTT_OUT_OF_MEMORY;

	time_stamp_token_ptr->time_stamp = time_stamp;

	return webvtt_create_cue_text_token( token_pptr, (void *)time_stamp_token_ptr, TIME_STAMP_TOKEN );
}

WEBVTT_INTERN void 
webvtt_delete_cue_text_start_tag_token( webvtt_cue_text_start_tag_token_ptr start_token_ptr )
{
	if( start_token_ptr )
	{
		webvtt_delete_string_list( start_token_ptr->css_classes_ptr );

		if( start_token_ptr->annotations )
			webvtt_delete_string( start_token_ptr->annotations );

		if( start_token_ptr->tag_name)
			webvtt_delete_string( start_token_ptr->tag_name );
		free( start_token_ptr );
	}
}

WEBVTT_INTERN void 
webvtt_delete_cue_text_end_tag_token( webvtt_cue_text_end_tag_token_ptr end_token_ptr)
{
	if( end_token_ptr )
	{
		if( end_token_ptr->tag_name )
			webvtt_delete_string( end_token_ptr->tag_name );
		free( end_token_ptr );
	}
}

WEBVTT_INTERN void 
webvtt_delete_cue_text_text_token(  webvtt_cue_text_text_token_ptr text_token_ptr )
{
	if( text_token_ptr )
	{
		if( text_token_ptr->text )
			webvtt_delete_string( text_token_ptr->text );
		free( text_token_ptr );
	}
}

WEBVTT_INTERN void 
webvtt_delete_cue_text_token( webvtt_cue_text_token_ptr cue_text_token_ptr )
{
	if( cue_text_token_ptr )
	{
		switch( cue_text_token_ptr->token_type )
		{
		case START_TOKEN:
			webvtt_delete_cue_text_start_tag_token( (webvtt_cue_text_start_tag_token_ptr)cue_text_token_ptr->concrete_token );
			break;
		case END_TOKEN:
			webvtt_delete_cue_text_end_tag_token( (webvtt_cue_text_end_tag_token_ptr)cue_text_token_ptr->concrete_token );
			break;
		case TEXT_TOKEN:
			webvtt_delete_cue_text_text_token( (webvtt_cue_text_text_token_ptr)cue_text_token_ptr->concrete_token );
			break;
		case TIME_STAMP_TOKEN:
			/* Not implemented because it does not use dynamic memory allocation. */
			break;
		}
		free( cue_text_token_ptr );
	}
}

/** 
 * Definitions for tag tokens that are more then one character long.
 */
#define RUBY_TAG_LENGTH 4
#define RUBY_TEXT_TAG_LENGTH 2

webvtt_wchar ruby_tag[RUBY_TAG_LENGTH] = { UTF16_R, UTF16_U, UTF16_B, UTF16_Y };
webvtt_wchar rt_tag[RUBY_TEXT_TAG_LENGTH] = { UTF16_R, UTF16_T };

WEBVTT_INTERN webvtt_status
webvtt_get_node_kind_from_tag_name( webvtt_string tag_name, webvtt_node_kind *kind )
{
	if( !tag_name || !kind )
	{
		return WEBVTT_INVALID_PARAM;
	}

	if( tag_name->length == 1 )
	{
		switch( tag_name->text[0] )
		{
		case( UTF16_B ):
			*kind = WEBVTT_BOLD;
			break;
		case( UTF16_I ):
			*kind = WEBVTT_ITALIC;
			break;
		case( UTF16_U ):
			*kind = WEBVTT_UNDERLINE;
			break;
		case( UTF16_C ):
			*kind = WEBVTT_CLASS;
			break;
		case( UTF16_V ):
			*kind = WEBVTT_VOICE;
			break;
		}
	}
	else if( webvtt_compare_wchars( tag_name->text, tag_name->length, ruby_tag, RUBY_TAG_LENGTH ) == WEBVTT_SUCCESS )
	{
		*kind = WEBVTT_RUBY;
	}
	else if( webvtt_compare_wchars( tag_name->text, tag_name->length, rt_tag, RUBY_TEXT_TAG_LENGTH ) == WEBVTT_SUCCESS )
	{
		*kind = WEBVTT_RUBY_TEXT;
	}
	else
	{
		return WEBVTT_INVALID_TAG_NAME;
	}

	return WEBVTT_SUCCESS;
}

WEBVTT_INTERN webvtt_status
webvtt_create_node_from_token( webvtt_cue_text_token_ptr token_ptr, webvtt_node_ptr *node_pptr,
	webvtt_node_ptr parent_ptr )
{
	webvtt_node_kind kind;
	webvtt_cue_text_start_tag_token_ptr temp_start_token_ptr;

	if( !token_ptr || !node_pptr || !parent_ptr )
	{
		return WEBVTT_INVALID_PARAM;
	}
	
	switch ( token_ptr->token_type )
	{
	case( TEXT_TOKEN ):
		 return webvtt_create_text_leaf_node( node_pptr, parent_ptr, 
					((webvtt_cue_text_text_token_ptr)token_ptr->concrete_token)->text );
		break;
	case( START_TOKEN ):
		temp_start_token_ptr = (webvtt_cue_text_start_tag_token_ptr)token_ptr->concrete_token;

		CHECK_MEMORY_OP( webvtt_get_node_kind_from_tag_name( temp_start_token_ptr->tag_name, &kind) );
			
		return webvtt_create_internal_node( node_pptr, parent_ptr, kind,
				temp_start_token_ptr->css_classes_ptr, temp_start_token_ptr->annotations );

		break;
	case ( TIME_STAMP_TOKEN ):
		 return webvtt_create_time_stamp_leaf_node( node_pptr, parent_ptr,
				((webvtt_cue_text_time_stamp_token_ptr)token_ptr->concrete_token)->time_stamp );
		break;
	default:
		return WEBVTT_INVALID_TOKEN_TYPE;
	}
}

WEBVTT_INTERN webvtt_status 
webvtt_cue_text_tokenizer_data_state( webvtt_wchar_ptr *position_pptr, 
	webvtt_cue_text_token_state_ptr token_state_ptr, webvtt_string *result )
{
	for ( ; *token_state_ptr == DATA; (*position_pptr)++ )
	{
		switch( **position_pptr )
		{
		case UTF16_AMPERSAND:		
			*token_state_ptr = ESCAPE;
			break;
		case UTF16_LESS_THAN:
			if( (*result)->length == 0 )
				*token_state_ptr = TAG;
			else 
				return WEBVTT_SUCCESS;
			break;
		case UTF16_NULL_BYTE:
			return WEBVTT_SUCCESS;
			break;
		default:
			CHECK_MEMORY_OP( webvtt_string_append_wchar( result, *position_pptr, 1 ) );
			break;
		}
	}

	return WEBVTT_UNFINISHED;
}

/**
 * Definitions for valid escape values. 
 * The semicolon is implicit in the comparison.
 */
#define AMP_ESCAPE_LENGTH			4
#define LT_ESCAPE_LENGTH			3
#define GT_ESCAPE_LENGTH			3
#define RLM_ESCAPE_LENGTH			4
#define LRM_ESCAPE_LENGTH			4
#define NBSP_ESCAPE_LENGTH			5

webvtt_wchar amp_escape[AMP_ESCAPE_LENGTH] = { UTF16_AMPERSAND, UTF16_A, UTF16_M, UTF16_P };
webvtt_wchar lt_escape[LT_ESCAPE_LENGTH] = { UTF16_AMPERSAND, UTF16_L, UTF16_T };
webvtt_wchar gt_escape[GT_ESCAPE_LENGTH] = { UTF16_AMPERSAND, UTF16_G, UTF16_T };
webvtt_wchar rlm_escape[RLM_ESCAPE_LENGTH] = { UTF16_AMPERSAND, UTF16_R, UTF16_L, UTF16_M };
webvtt_wchar lrm_escape[LRM_ESCAPE_LENGTH] = { UTF16_AMPERSAND, UTF16_L, UTF16_R, UTF16_M };
webvtt_wchar nbsp_escape[NBSP_ESCAPE_LENGTH] = { UTF16_AMPERSAND, UTF16_N, UTF16_B, UTF16_S, UTF16_P };

WEBVTT_INTERN webvtt_status 
webvtt_cue_text_tokenizer_escape_state( webvtt_wchar_ptr *position_pptr, 
	webvtt_cue_text_token_state_ptr token_state_ptr, webvtt_string *result )
{
	webvtt_string buffer;
	webvtt_status status = WEBVTT_SUCCESS;

	CHECK_MEMORY_OP_JUMP( status, webvtt_create_string( 1, &buffer ) );
	
	/**
	 * Append ampersand here because the algorithm is not able to add it to the buffer when it reads it in the DATA state tokenizer.
	 */
	CHECK_MEMORY_OP_JUMP( status, webvtt_string_append_single_wchar( &buffer, UTF16_AMPERSAND ) );

	for( ; *token_state_ptr == ESCAPE; (*position_pptr)++ )
	{
		/**
		 * We have encountered a token termination point.
		 * Append buffer to result and return success.
		 */
		if( **position_pptr == UTF16_NULL_BYTE || **position_pptr == UTF16_LESS_THAN )
		{
			CHECK_MEMORY_OP_JUMP( status, webvtt_string_append_string( result, buffer ) ); 
			goto dealloc;
		}
		/**
		 * This means we have enocuntered a malformed escape character sequence.
		 * This means that we need to add that malformed text to the result and recreate the buffer
		 * to prepare for a new escape sequence.
		 */
		else if( **position_pptr == UTF16_AMPERSAND )
		{
			CHECK_MEMORY_OP_JUMP( status, webvtt_string_append_string( result, buffer ) );
			webvtt_delete_string( buffer );
			CHECK_MEMORY_OP_JUMP( status, webvtt_create_string( 1, &buffer ) ); 
			CHECK_MEMORY_OP_JUMP( status, webvtt_string_append_wchar( &buffer, *position_pptr, 1 ) );
		}
		/**
		 * We've encountered the semicolon which is the end of an escape sequence.
		 * Check if buffer contains a valid escape sequence and if it does append the
		 * interpretation to result and change the state to DATA.
		 */
		else if( **position_pptr == UTF16_SEMI_COLON )
		{
			if( webvtt_compare_wchars( buffer->text, buffer->length, amp_escape, AMP_ESCAPE_LENGTH ) == WEBVTT_SUCCESS )
			{
				CHECK_MEMORY_OP_JUMP( status, webvtt_string_append_single_wchar( result, UTF16_AMPERSAND ) );
			}
			else if( webvtt_compare_wchars( buffer->text, buffer->length, lt_escape, LT_ESCAPE_LENGTH ) == WEBVTT_SUCCESS )
			{
				CHECK_MEMORY_OP_JUMP( status, webvtt_string_append_single_wchar( result, UTF16_LESS_THAN ) );
			}
			else if( webvtt_compare_wchars( buffer->text, buffer->length, gt_escape, GT_ESCAPE_LENGTH ) == WEBVTT_SUCCESS )
			{
				CHECK_MEMORY_OP_JUMP( status, webvtt_string_append_single_wchar( result, UTF16_GREATER_THAN ) );
			}
			else if( webvtt_compare_wchars( buffer->text, buffer->length, rlm_escape, RLM_ESCAPE_LENGTH ) == WEBVTT_SUCCESS )
			{
				CHECK_MEMORY_OP_JUMP( status, webvtt_string_append_single_wchar( result, UTF16_RIGHT_TO_LEFT ) );
			}
			else if( webvtt_compare_wchars( buffer->text, buffer->length, lrm_escape, LRM_ESCAPE_LENGTH ) == WEBVTT_SUCCESS )
			{
				CHECK_MEMORY_OP_JUMP( status, webvtt_string_append_single_wchar( result, UTF16_LEFT_TO_RIGHT ) );
			}
			else if( webvtt_compare_wchars( buffer->text, buffer->length, nbsp_escape, NBSP_ESCAPE_LENGTH ) == WEBVTT_SUCCESS )
			{
				CHECK_MEMORY_OP_JUMP( status, webvtt_string_append_single_wchar( result, UTF16_NO_BREAK_SPACE ) );
			}
			else
			{
				CHECK_MEMORY_OP_JUMP( status, webvtt_string_append_string( result, buffer ) );
				CHECK_MEMORY_OP_JUMP( status, webvtt_string_append_wchar( result, *position_pptr, 1 ) );
			}

			*token_state_ptr = DATA;
		}
		/**
		 * Character is alphanumeric. This means we are in the body of the escape sequence. 
		 */
		else if( webvtt_is_alphanumeric( **position_pptr ) == WEBVTT_SUCCESS )
		{
			CHECK_MEMORY_OP_JUMP( status, webvtt_string_append_wchar( &buffer, *position_pptr, 1 ) );
		}
		/**
		 * If we have not found an alphanumeric character then we have encountered
		 * a malformed escape sequence. Add buffer to result and continue to parse in DATA state.
		 */
		else
		{
			CHECK_MEMORY_OP_JUMP( status, webvtt_string_append_string( result, buffer ) );
			CHECK_MEMORY_OP_JUMP( status, webvtt_string_append_wchar( result, *position_pptr, 1 ) );
			*token_state_ptr = DATA;
		}
	}

	dealloc:
	webvtt_delete_string( buffer );

	return status;
}

WEBVTT_INTERN webvtt_status 
webvtt_cue_text_tokenizer_tag_state( webvtt_wchar_ptr *position_pptr,
	webvtt_cue_text_token_state_ptr token_state_ptr, webvtt_string *result )
{
	for( ; *token_state_ptr == TAG; (*position_pptr)++ )
	{
		if( **position_pptr == UTF16_TAB || **position_pptr == UTF16_LINE_FEED ||
			**position_pptr == UTF16_CARRIAGE_RETURN || **position_pptr == UTF16_FORM_FEED ||
			**position_pptr == UTF16_SPACE )
		{
			*token_state_ptr = START_TAG_ANNOTATION;
		}
		else if( webvtt_is_digit( **position_pptr ) == WEBVTT_SUCCESS )
		{
			CHECK_MEMORY_OP( webvtt_string_append_wchar( result, *position_pptr, 1 ) );
			*token_state_ptr = TIME_STAMP_TAG;
		}
		else 
		{
			switch( **position_pptr )
			{
			case UTF16_FULL_STOP:
				*token_state_ptr = START_TAG_CLASS;
				break;
			case UTF16_SOLIDUS:
				*token_state_ptr = END_TAG;
				break;
			case UTF16_GREATER_THAN:
				return WEBVTT_SUCCESS;
				break;
			case UTF16_NULL_BYTE:
				return WEBVTT_SUCCESS;
				break;
			default:
				CHECK_MEMORY_OP( webvtt_string_append_wchar( result, *position_pptr, 1 ) );
				*token_state_ptr = START_TAG;
			}
		}
	}

	return WEBVTT_UNFINISHED;
}

WEBVTT_INTERN webvtt_status 
webvtt_cue_text_tokenizer_start_tag_state( webvtt_wchar_ptr *position_pptr,
	webvtt_cue_text_token_state_ptr token_state_ptr, webvtt_string *result )
{
	for( ; *token_state_ptr == START_TAG; (*position_pptr)++ )
	{
		if( **position_pptr == UTF16_TAB || **position_pptr == UTF16_FORM_FEED ||
			**position_pptr == UTF16_SPACE || **position_pptr == UTF16_LINE_FEED ||
			**position_pptr == UTF16_CARRIAGE_RETURN )
		{
			*token_state_ptr = START_TAG_ANNOTATION;
		}
		else
		{
			switch( **position_pptr )
			{
			case UTF16_TAB:
				*token_state_ptr = START_TAG_ANNOTATION;
				break;
			case UTF16_FULL_STOP:
				*token_state_ptr = START_TAG_CLASS;
				break;
			case UTF16_GREATER_THAN:
				return WEBVTT_SUCCESS;
				break;
			default:
				CHECK_MEMORY_OP( webvtt_string_append_wchar( result, *position_pptr, 1 ) );
				break;
			}
		}
	}

	return WEBVTT_UNFINISHED;
}

WEBVTT_INTERN webvtt_status 
webvtt_cue_text_tokenizer_start_tag_class_state( webvtt_wchar_ptr *position_pptr,
	webvtt_cue_text_token_state_ptr token_state_ptr, webvtt_string_list_ptr css_classes_ptr )
{
	webvtt_string buffer;
	webvtt_status status = WEBVTT_SUCCESS;

	CHECK_MEMORY_OP( webvtt_create_string( 1, &buffer ) );

	for( ; *token_state_ptr == START_TAG_CLASS; (*position_pptr)++ )
	{
		if( **position_pptr == UTF16_TAB || **position_pptr == UTF16_FORM_FEED ||
			**position_pptr == UTF16_SPACE || **position_pptr == UTF16_LINE_FEED || 
			**position_pptr == UTF16_CARRIAGE_RETURN)
		{
			CHECK_MEMORY_OP_JUMP( status, webvtt_add_to_string_list( css_classes_ptr, buffer ) );
			*token_state_ptr = START_TAG_ANNOTATION;
			return WEBVTT_SUCCESS;
		}
		else if( **position_pptr == UTF16_GREATER_THAN || **position_pptr == UTF16_NULL_BYTE )
		{
			CHECK_MEMORY_OP_JUMP( status, webvtt_add_to_string_list( css_classes_ptr, buffer ) );
			return WEBVTT_SUCCESS;
		}
		else if( **position_pptr == UTF16_FULL_STOP )
		{
			CHECK_MEMORY_OP_JUMP( status, webvtt_add_to_string_list( css_classes_ptr, buffer ) );
			CHECK_MEMORY_OP( webvtt_create_string( 1, &buffer ) );
		}
		else
		{
			CHECK_MEMORY_OP_JUMP( status, webvtt_string_append_wchar( &buffer, *position_pptr, 1 ) );;
		}
	}

	dealloc:
	webvtt_delete_string( buffer );

	return status;
}

WEBVTT_INTERN webvtt_status 
webvtt_cue_text_tokenizer_start_tag_annotation_state( webvtt_wchar_ptr *position_pptr,
	webvtt_cue_text_token_state_ptr token_state_ptr, webvtt_string *annotation )
{
	for( ; *token_state_ptr == START_TAG_ANNOTATION; (*position_pptr)++ )
	{
		if( **position_pptr == UTF16_NULL_BYTE || **position_pptr == UTF16_GREATER_THAN )
		{
			return WEBVTT_SUCCESS;
		}
		CHECK_MEMORY_OP( webvtt_string_append_wchar( annotation, *position_pptr, 1 ) );
	}

	return WEBVTT_UNFINISHED;
}

WEBVTT_INTERN webvtt_status 
webvtt_cue_text_tokenizer_end_tag_state( webvtt_wchar_ptr *position_pptr,
	webvtt_cue_text_token_state_ptr token_state_ptr, webvtt_string *result )
{
	for( ; *token_state_ptr == END_TAG; (*position_pptr)++ ) 
	{
		if( **position_pptr == UTF16_GREATER_THAN || **position_pptr == UTF16_NULL_BYTE )
		{
			return WEBVTT_SUCCESS;
		}
		CHECK_MEMORY_OP( webvtt_string_append_wchar( result, *position_pptr, 1 ) );
	}

	return WEBVTT_UNFINISHED;
}

WEBVTT_INTERN webvtt_status 
webvtt_cue_text_tokenizer_time_stamp_tag_state( webvtt_wchar_ptr *position_pptr,
	webvtt_cue_text_token_state_ptr token_state_ptr, webvtt_string *result )
{
	for( ; *token_state_ptr == TIME_STAMP_TAG; (*position_pptr)++ ) 
	{
		if( **position_pptr == UTF16_GREATER_THAN || **position_pptr == UTF16_NULL_BYTE )
		{
			return WEBVTT_SUCCESS;
		}
		CHECK_MEMORY_OP( webvtt_string_append_wchar( result, *position_pptr, 1 ) );
	}

	return WEBVTT_UNFINISHED;
}

/**
 * Need to set up differently.
 * Get a status in order to return at end and release memeory.
 */
WEBVTT_INTERN webvtt_status
webvtt_cue_text_tokenizer( webvtt_wchar_ptr *position_pptr, webvtt_cue_text_token_ptr *token_ptr ) 
{
	webvtt_cue_text_token_state token_state = DATA;
	webvtt_string result, annotation;
	webvtt_string_list_ptr css_classes_ptr;
	webvtt_timestamp time_stamp = 0;
	webvtt_status status = WEBVTT_UNFINISHED;

	webvtt_create_string( 10, &result );
	webvtt_create_string( 10, &annotation );
	webvtt_create_string_list( &css_classes_ptr );

	if( !position_pptr )
	{
		return WEBVTT_INVALID_PARAM;
	}

	/**
	 * Loop while the tokenizer is not finished.
	 * Based on the state of the tokenizer enter a function to handle that particular tokenizer state.
	 * Those functions will loop until they either change the state of the tokenizer or reach a valid token end point.
	 */
	while( status == WEBVTT_UNFINISHED )
	{
		switch( token_state )
		{
		case DATA :
			status = webvtt_cue_text_tokenizer_data_state( position_pptr, &token_state, &result ); 
			break;
		case ESCAPE:
			status = webvtt_cue_text_tokenizer_escape_state( position_pptr, &token_state, &result );
			break;
		case TAG:
			status = webvtt_cue_text_tokenizer_tag_state( position_pptr, &token_state, &result );
			break;
		case START_TAG:
			status = webvtt_cue_text_tokenizer_start_tag_state( position_pptr, &token_state, &result );
			break;
		case START_TAG_CLASS:
			status = webvtt_cue_text_tokenizer_start_tag_class_state( position_pptr, &token_state, css_classes_ptr );
			break;
		case START_TAG_ANNOTATION:
			status = webvtt_cue_text_tokenizer_start_tag_annotation_state( position_pptr, &token_state, &annotation );
			break;
		case END_TAG:
			status = webvtt_cue_text_tokenizer_end_tag_state( position_pptr, &token_state, &result );
			break;
		case TIME_STAMP_TAG:
			status = webvtt_cue_text_tokenizer_time_stamp_tag_state( position_pptr, &token_state, &result );
			break;
		}

		if( token_state == START_TAG_ANNOTATION )
			webvtt_advance_past_line_ending( position_pptr );
	}

	if( **position_pptr == UTF16_GREATER_THAN )
		(*position_pptr)++;

	/**
	 * If we have not recieved a webvtt success then that means we should not create a token and 
	 * therefore we need to deallocate result, annotation, and css classes now because no token/node
	 * struct will take care of deallocation later in the parser.
	 */
	if( status != WEBVTT_SUCCESS )
	{
		webvtt_delete_string( result );
		webvtt_delete_string( annotation );
		webvtt_delete_string_list( css_classes_ptr );
		return status;
	}

	/**
	 * The state that the tokenizer left off on will tell us what kind of token needs to be made.
	 */
	if( token_state == DATA || token_state == ESCAPE )
	{
		 return webvtt_create_cue_text_text_token( &(*token_ptr), result );
	}
	else if(token_state == TAG || token_state == START_TAG || token_state == START_TAG_CLASS || 
			token_state == START_TAG_ANNOTATION)
	{
		return webvtt_create_cue_text_start_tag_token( &(*token_ptr), result, css_classes_ptr, annotation );
	}
	else if( token_state == END_TAG )
	{
		return webvtt_create_cue_text_end_tag_token( &(*token_ptr), result );
	}
	else if( token_state == TIME_STAMP_TAG )
	{
		/**
		 * INCOMPLETE - Need to parse time stamp from token.
		 */
		return webvtt_create_cue_text_time_stamp_token( &(*token_ptr), time_stamp );
	}
	else
	{
		return WEBVTT_INVALID_TOKEN_STATE;
	}

	return WEBVTT_SUCCESS;
}

/**
 * Currently line and len are not being kept track of.
 * Don't think pnode_length is needed as nodes track there list count internally.
 */
WEBVTT_EXPORT webvtt_status
webvtt_parse_cuetext( webvtt_wchar *cue_text, webvtt_node_ptr node_ptr )
{
	webvtt_wchar_ptr position_ptr = (webvtt_wchar_ptr)cue_text;
	webvtt_node_ptr current_node_ptr = NULL, temp_node_ptr = NULL;
	webvtt_cue_text_token_ptr token_ptr = NULL;
	webvtt_node_kind kind;
	
	if( !cue_text )
			return WEBVTT_INVALID_PARAM;

	if ( webvtt_create_head_node( &node_ptr ) != WEBVTT_SUCCESS )
		return WEBVTT_OUT_OF_MEMORY;

	current_node_ptr = node_ptr;

	/**
	 * Routine taken from the W3C specification - http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
	 */
	while( *position_ptr != UTF16_NULL_BYTE ) {

		webvtt_delete_cue_text_token( token_ptr );

		/* Step 7. */
		switch( webvtt_cue_text_tokenizer( &position_ptr, &token_ptr ) )
		{
		case( WEBVTT_UNFINISHED ):
			/* Error here. */
			break;
		/* Step 8. */
		case( WEBVTT_SUCCESS ):
			
			/**
			 * If we've found an end token which has a valid end token tag name and a tag name
			 * that is equal to the current node then set current to the parent of current.
			 */
			if( token_ptr->token_type == END_TOKEN )
			{
				/**
				 * We have encountered an end token but we are at the top of the list and thus have not encountered any start tokens yet, throw away the token.
				 */
				if( current_node_ptr->kind == WEBVTT_HEAD_NODE )
					continue;

				/**
				 * We have encountered an end token but it is not in a format that is supported, throw away the token.
				 */
				if( webvtt_get_node_kind_from_tag_name( ((webvtt_cue_text_end_tag_token *) token_ptr->concrete_token)->tag_name, &kind ) == WEBVTT_INVALID_TAG_NAME )
					continue;
				
				/**
				 * We have encountered an end token and it matches the start token of the node that we are currently on.
				 * Move back up the list of nodes and continue parsing.
				 */
				if( current_node_ptr->kind == kind )
					current_node_ptr = current_node_ptr->parent;
			}
			else
			{
				
				/** 
				 * Attempt to create a valid node from the token.
				 * If successful then attach the node to the current nodes list and also set current to the newly created node
				 * if it is an internal node type.
				 */
				if( webvtt_create_node_from_token( token_ptr, &temp_node_ptr, current_node_ptr ) != WEBVTT_SUCCESS )
					/* Do something here? */
					continue;
				else
				{
					webvtt_attach_internal_node( (webvtt_internal_node_ptr)current_node_ptr->concrete_node, temp_node_ptr );

					if( WEBVTT_IS_VALID_INTERNAL_NODE( temp_node_ptr->kind ) )
						current_node_ptr = temp_node_ptr;					
				}
			}
			break;
		}

	}

	return WEBVTT_SUCCESS;
}