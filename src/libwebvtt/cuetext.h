#ifndef __WEBVTT_CUETEXT_H__
#	define __WEBVTT_CUETEXT_H__
#	include <webvtt/util.h>
#	include <webvtt/string.h>
#	include <webvtt/cue.h>

typedef enum webvtt_cue_text_token_type_t webvtt_cue_text_token_type;
typedef enum webvtt_cue_text_token_state_t webvtt_cue_text_token_state, *webvtt_cue_text_token_state_ptr;

typedef struct webvtt_cue_text_token_t webvtt_cue_text_token, *webvtt_cue_text_token_ptr;
typedef struct webvtt_cue_text_start_tag_token_t webvtt_cue_text_start_tag_token, *webvtt_cue_text_start_tag_token_ptr;
typedef struct webvtt_cue_text_end_tag_token_t webvtt_cue_text_end_tag_token, *webvtt_cue_text_end_tag_token_ptr;
typedef struct webvtt_cue_text_text_token_t webvtt_cue_text_text_token, *webvtt_cue_text_text_token_ptr;
typedef struct webvtt_cue_text_time_stamp_token_t webvtt_cue_text_time_stamp_token, *webvtt_cue_text_time_stamp_token_ptr;

/**
 * Enumerates token types.
 */
enum
webvtt_cue_text_token_type_t 
{
	START_TOKEN, /* Identifies a webvtt_cue_text_start_tag_token. */
	END_TOKEN, /* Identifies a webvtt_cue_text_end_tag_token. */
	TIME_STAMP_TOKEN, /* Identifies a webvtt_cue_text_time_stamp_token. */
	TEXT_TOKEN /* Identifies a webvtt_cue_text_text_token. */
};

/**
 * Enumerates possible states that the cue text tokenizer can be in.
 */
enum 
webvtt_cue_text_token_state_t
{
	DATA, /* Initial state. */
	ESCAPE, /* Parsing an escape value. */
	TAG, /* Reached a '<' character, about to start parsing a tag. */
	START_TAG, /* Parsing the beginning of a tag i.e. the tag name. */
	START_TAG_CLASS, /* Parsing a tag class. Reached when the tokenizer in the START_TAG 
									   state reaches a '.' character. */
	START_TAG_ANNOTATION, /* Parsing a tag annotation. Reached when the tokenizer in the 
												START_TAG_CLASS state reaches a TAB, SPACE, or FORM FEED character. */
	END_TAG, /* Parsing an end tag. Reached when a '<' character is follwed by a '/' character. */
	TIME_STAMP_TAG /* Parsing a time stamp tag. Reached when a '<' character is follwed by an integer character. */
};

/**
 * Contains a void pointer to a concrete token as well as a token type enum that identifies what kind of token it is.
 */
struct
webvtt_cue_text_token_t
{
	webvtt_cue_text_token_type token_type;
	void *concrete_token;
};

/**
 * Represents a start tag in the cue text.
 * These take the form of <[TAG_NAME].[CLASSES] [POSSIBLE_ANNOTATION]> in the cue text.
 */
struct 
webvtt_cue_text_start_tag_token_t 
{
	webvtt_string tag_name;
	webvtt_string_list_ptr css_classes_ptr;
	webvtt_string annotations;
};

/**
 * Represents an end tag in the cue text.
 * These take the form of </[TAG_NAME]> in the cue text.
 */
struct 
webvtt_cue_text_end_tag_token_t
{
	webvtt_string tag_name;
};

/**
 * Represents a plain text block in the cue text.
 */
struct
webvtt_cue_text_text_token_t
{
	webvtt_string text;
};

/**
 * Represents a time stamp tag in the cue text.
 * These take the form of <[XX:XX.XXXX]> where X is an integer from 0 - 9.
 */
struct
webvtt_cue_text_time_stamp_token_t
{
	webvtt_timestamp time_stamp;
};

/**
 * Routines for creating cue text tokens.
 * Sets the passed token_ptr to the new token.
 */
WEBVTT_INTERN webvtt_status webvtt_create_cue_text_token( webvtt_cue_text_token_ptr *token_pptr, void *concrete_token, 
	webvtt_cue_text_token_type token_type );

WEBVTT_INTERN webvtt_status webvtt_create_cue_text_start_tag_token( webvtt_cue_text_token_ptr *token_pptr, webvtt_string tag_name, 
	webvtt_string_list_ptr css_classes_ptr, webvtt_string annotation );

WEBVTT_INTERN webvtt_status webvtt_create_cue_text_end_tag_token( webvtt_cue_text_token_ptr *token_pptr, webvtt_string tag_name );
WEBVTT_INTERN webvtt_status webvtt_create_cue_text_text_token( webvtt_cue_text_token_ptr *token_pptr, webvtt_string text );
WEBVTT_INTERN webvtt_status webvtt_create_cue_text_time_stamp_token( webvtt_cue_text_token_ptr *token_pptr, 
	webvtt_timestamp time_stamp );

/**
 * Routines for deleting cue text tokens.
 */
WEBVTT_INTERN void webvtt_delete_cue_text_token( webvtt_cue_text_token_ptr token_ptr ); 
WEBVTT_INTERN void webvtt_delete_cue_text_start_tag_token( webvtt_cue_text_start_tag_token_ptr start_token_ptr );
WEBVTT_INTERN void webvtt_delete_cue_text_end_tag_token( webvtt_cue_text_end_tag_token_ptr end_token_ptr);
WEBVTT_INTERN void webvtt_delete_cue_text_text_token(  webvtt_cue_text_text_token_ptr text_token_ptr );

/**
 * Converts the textual representation of a node kind into a particular kind.
 * I.E. tag_name of 'ruby' would create a ruby kind, etc.
 * Returns a WEBVTT_NOT_SUPPORTED if it does not find a valid tag name.
 */
WEBVTT_INTERN webvtt_status webvtt_get_node_kind_from_tag_name( webvtt_string tag_name, webvtt_node_kind *kind );

/**
 * Creates a node from a valid token.
 * Returns WEBVTT_NOT_SUPPORTED if it does not find a valid tag name.
 */
WEBVTT_INTERN webvtt_status webvtt_create_node_from_token( webvtt_cue_text_token_ptr token_ptr, webvtt_node_ptr *node_ptr, 
	webvtt_node_ptr parent_ptr );

/**
 * Tokenizes the cue text into something that can be easily understood by the cue text parser.
 * Referenced from - http://dev.w3.org/html5/webvtt/#webvtt-cue-text-tokenizer
 */
WEBVTT_INTERN webvtt_status webvtt_cue_text_tokenizer( webvtt_wchar_ptr *position_pptr, webvtt_cue_text_token_ptr *token_ptr );

/**
 * Routines that take care of certain states in the webvtt cue text tokenizer.
 */

/**
 * Referenced from http://dev.w3.org/html5/webvtt/#webvtt-data-state
 */
WEBVTT_INTERN webvtt_status webvtt_cue_text_tokenizer_data_state( webvtt_wchar_ptr *position_pptr, 
	webvtt_cue_text_token_state_ptr token_state_ptr, webvtt_string *result );

/**
 * Referenced from http://dev.w3.org/html5/webvtt/#webvtt-escape-state
 */
WEBVTT_INTERN webvtt_status webvtt_cue_text_tokenizer_escape_state( webvtt_wchar_ptr *position_pptr, 
	webvtt_cue_text_token_state_ptr token_state_ptr, webvtt_string *result );

/**
 * Referenced from http://dev.w3.org/html5/webvtt/#webvtt-tag-state
 */
WEBVTT_INTERN webvtt_status webvtt_cue_text_tokenizer_tag_state( webvtt_wchar_ptr *position_pptr,
	webvtt_cue_text_token_state_ptr token_state_ptr, webvtt_string *result );

/**
 * Referenced from http://dev.w3.org/html5/webvtt/#webvtt-start-tag-state
 */
WEBVTT_INTERN webvtt_status webvtt_cue_text_tokenizer_start_tag_state( webvtt_wchar_ptr *position_pptr,
	webvtt_cue_text_token_state_ptr token_state_ptr, webvtt_string *result );

/**
 * Referenced from http://dev.w3.org/html5/webvtt/#webvtt-start-tag-class-state
 */
WEBVTT_INTERN webvtt_status webvtt_cue_text_tokenizer_start_tag_class_state( webvtt_wchar_ptr *position_pptr,
	webvtt_cue_text_token_state_ptr token_state_ptr, webvtt_string_list_ptr css_classes_ptr );

/**
 * Referenced from http://dev.w3.org/html5/webvtt/#webvtt-start-tag-annotation-state
 */
WEBVTT_INTERN webvtt_status webvtt_cue_text_tokenizer_start_tag_annotation_state( webvtt_wchar_ptr *position_pptr,
	webvtt_cue_text_token_state_ptr token_state_ptr, webvtt_string *annotation );

/**
 * Referenced from http://dev.w3.org/html5/webvtt/#webvtt-end-tag-state
 */
WEBVTT_INTERN webvtt_status webvtt_cue_text_tokenizer_end_tag_state( webvtt_wchar_ptr *position_pptr,
	webvtt_cue_text_token_state_ptr token_state_ptr, webvtt_string *result );

/**
 * Referenced from http://dev.w3.org/html5/webvtt/#webvtt-timestamp-tag-state
 */
WEBVTT_INTERN webvtt_status webvtt_cue_text_tokenizer_time_stamp_tag_state( webvtt_wchar_ptr *position_pptr,
	webvtt_cue_text_token_state_ptr token_state_ptr, webvtt_string *result );

#endif