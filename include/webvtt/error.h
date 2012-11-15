#ifndef __WEBVTT_ERROR_H__
#	define __WEBVTT_ERROR_H__
#	include "util.h"


typedef enum webvtt_error_t webvtt_error;

enum
webvtt_error_t
{
	/* There was a problem allocating something */
	WEBVTT_ALLOCATION_FAILED = 0,
	/* 'WEBVTT' is not the first 6 characters in the file (not counting UTF8 BOM) */
	WEBVTT_MALFORMED_TAG, 
	/* An end-of-line sequence was expected, but not found. */
	WEBVTT_EXPECTED_EOL,
	/* A string of whitespace was expected, but not found. */
	WEBVTT_EXPECTED_WHITESPACE,
	/* Long WEBVTT comment, decide whether to abort parsing or not */
	WEBVTT_LONG_COMMENT,
	/* A cue-id was too long to fit in the buffer. */
	WEBVTT_ID_TRUNCATED,
	/* A timestamp is malformed */
	WEBVTT_MALFORMED_TIMESTAMP,
	/* Expected a timestamp, but didn't find one */
	WEBVTT_EXPECTED_TIMESTAMP,
	/* Missing timestamp separator */
	WEBVTT_MISSING_CUETIME_SEPARATOR,
	/* Missing cuesetting delimiter */
	WEBVTT_MISSING_CUESETTING_DELIMITER,
	/* End-time is less than or equal to start time */
	WEBVTT_INVALID_ENDTIME,
	/* Invalid cue-setting */
	WEBVTT_INVALID_CUESETTING,
	/* 'vertical' setting already exists for this cue. */
	WEBVTT_VERTICAL_ALREADY_SET,
	/* Bad 'vertical' value */
	WEBVTT_VERTICAL_BAD_VALUE,
	/* 'line' setting already exists for this cue. */
	WEBVTT_LINE_ALREADY_SET,
	/* Bad 'line' value */
	WEBVTT_LINE_BAD_VALUE,
	/* 'position' setting already exists for this cue. */
	WEBVTT_POSITION_ALREADY_SET,
	/* Bad 'position' value */
	WEBVTT_POSITION_BAD_VALUE,
	/* 'size' setting already exists for this cue. */
	WEBVTT_SIZE_ALREADY_SET,
	/* Bad 'size' value */
	WEBVTT_SIZE_BAD_VALUE,
	/* 'align' setting already exists for this cue. */
	WEBVTT_ALIGN_ALREADY_SET,
	/* Bad 'align' value */
	WEBVTT_ALIGN_BAD_VALUE,
	/* A cue-text object contains the string "-->", which needs to be escaped */
	WEBVTT_CUE_CONTAINS_SEPARATOR,
	/* A webvtt cue contains only a cue-id, and no cuetimes or payload. */
	WEBVTT_CUE_INCOMPLETE,
};

WEBVTT_EXPORT const char *webvtt_strerror( webvtt_error );

/* Represents an Error Logging Type and follows GNU style error logging standards:
 * http://www.gnu.org/prep/standards/html_node/Errors.html
 * These error standards are followed for source files and webVTT files.
 */

typedef struct {
	char *error_code;
	char *error_message;

	webvtt_uint webvtt_line_number;

	char *webvtt_file_name;

	/* columns the error occurred on */
	webvtt_uint start_col;
	webvtt_uint end_col;

} vtt_error_t;



#endif