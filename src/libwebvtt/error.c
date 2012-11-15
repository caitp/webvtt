#include <webvtt/error.h>
#include <webvtt/parser.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "parser.h"

static const char *errstr[] =
{
	/* WEBVTT_ALLOCATION_FAILED */ "error allocating object",
	/* WEBVTT_MALFORMED_TAG */ "malformed 'WEBVTT' tag",
	/* WEBVTT_EXPECTED_EOL */ "expected newline",
	/* WEBVTT_EXPECTED_WHITESPACE */ "expected whitespace",
	/* WEBVTT_LONG_COMMENT */ "very long tag-comment",
	/* WEBVTT_ID_TRUNCATED */ "webvtt-cue-id truncated",
	/* WEBVTT_MALFORMED_TIMESTAMP */ "malformed webvtt-timestamp",
	/* WEBVTT_EXPECTED_TIMESTAMP */ "expected webvtt-timestamp",
	/* WEBVTT_MISSING_CUETIME_SEPARATOR */ "missing webvtt-cuetime-separator `-->'",
	/* WEBVTT_MISSING_CUESETTING_DELIMITER */ "missing whitespace before webvtt-cuesetting",
	/* WEBVTT_INVALID_ENDTIME */ "webvtt-cue end-time must have value greater than start-time",
	/* WEBVTT_INVALID_CUESETTING */ "unrecognized webvtt-cue-setting",
	/* WEBVTT_VERTICAL_ALREADY_SET */ "'vertical' cue-setting already used",
	/* WEBVTT_VERTICAL_BAD_VALUE */ "'vertical' setting must have a value of either 'lr' or 'rl'",
	/* WEBVTT_LINE_ALREADY_SET */ "'line' cue-setting already used",
	/* WEBVTT_LINE_BAD_VALUE */ "'line' cue-setting must have a value that is an integer (signed) line number, or percentage (%) from top of video display",
	/* WEBVTT_POSITION_ALREADY_SET */ "'position' cue-setting already used",
	/* WEBVTT_POSITION_BAD_VALUE */ "'position' cue-setting must be a percentage (%) value representing the position in the direction orthogonal to the 'line' setting",
	/* WEBVTT_SIZE_ALREADY_SET */ "'size' cue-setting already used",
	/* WEBVTT_SIZE_BAD_VALUE */ "'size' cue-setting must have percentage (%) value",
	/* WEBVTT_ALIGN_ALREADY_SET */ "'align' cue-setting already used",
	/* WEBVTT_ALIGN_BAD_VALUE */ "'align' cue-setting must have a value of either 'start', 'middle', or 'end'",
	/* WEBVTT_CUE_CONTAINS_SEPARATOR */ "cue-text line contains unescaped timestamp separator '-->'",
	/* WEBVTT_CUE_INCOMPLETE */ "cue contains cue-id, but is missing cuetimes or cue text",
};

/**
 * TODO:
 * Add i18n localized error strings with support for glibc and msvcrt locale identifiers
 * (This might be too much work!)
 */
WEBVTT_EXPORT const char *
webvtt_strerror( webvtt_error errno )
{
	if( errno >= (sizeof(errstr) / sizeof(*errstr)) )
	{
		return "";
	}
	return errstr[ errno ];
}
void create_error(webvtt_parser self, char *code, char *message, char *vtt, int vtt_line) {
	/* 
	 * Create and initialize the error structure.
	 * Error messages are represented with ASCII character strings
	 */
	vtt_error_t *er = (vtt_error_t *)malloc(sizeof(vtt_error_t));
	er->error_code = (char *)malloc(sizeof(char) * strlen(code));
	strcpy(er->error_code, code);
	er->error_message = (char *)malloc(sizeof(char) * strlen(message));
	strcpy(er->error_message, message);

	if (vtt) {
		er->webvtt_file_name = (char *)malloc(sizeof(char) * strlen(vtt));
		strcpy(er->webvtt_file_name, vtt );
	}
	er->webvtt_line_number = vtt_line;

	/* Add to the end of the error array. */
	add_to_error_list(self, er);
}

void add_to_error_list(webvtt_parser self, vtt_error_t *er) {
	/*  Make use of the first allocated element before reallocating. */
	if(self->error_list_size == 0)
		self->error_list[0] = *er;
	else {
		self->error_list = (vtt_error_t*)realloc(self->error_list, sizeof(vtt_error_t) + sizeof(self->error_list));
		self->error_list[self->error_list_size] = *er;
	}
	self->error_list++;
}

void print_error_list(webvtt_parser self) {
	FILE *fp = NULL;
	int i;

	fp = fopen("errorlog.txt", "w");
	for (i = 0; i < self->error_list_size; i++) {

	    /* Try to add entry to the log file. */
		if (fp) {
			/* save to file */
			fprintf(fp, "Error Code: %s %s: VTT File: %s Line: %d\n",
				self->error_list[i].error_code, self->error_list[i].error_message, self->error_list[i].webvtt_file_name, self->error_list[i].webvtt_line_number);
			/* print to stderr */
			fprintf(stderr, "Error Code: %s %s: VTT File: %s Line: %d\n", 
				self->error_list[i].error_code, self->error_list[i].error_message, self->error_list[i].webvtt_file_name, self->error_list[i].webvtt_line_number);
		} else {
			fprintf(stderr, "Error could not be logged!\n");
		}

		/* Deallocate the current Error Object in the list. */
		free(self->error_list[i].error_code);
		free(self->error_list[i].error_message);
		free(self->error_list[i].webvtt_file_name);
	}
	fclose(fp);
}
