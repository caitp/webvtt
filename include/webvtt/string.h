#ifndef __WEBVTT_STRING_H__
#	define __WEBVTT_STRING_H__
#	include "util.h"

#define UTF16_AMPERSAND					(0x0026)
#define UTF16_LESS_THAN					(0x003C)
#define UTF16_GREATER_THAN				(0x003E)
#define UTF16_LEFT_TO_RIGHT				(0x200E)
#define UTF16_RIGHT_TO_LEFT				(0x200F)
#define UTF16_NO_BREAK_SPACE			(0x00A0)
#define UTF16_NULL_BYTE					(0x0000)
#define UTF16_SEMI_COLON				(0x003B)
#define UTF16_TAB						(0x0009)
#define UTF16_FORM_FEED					(0x000C)
#define UTF16_LINE_FEED					(0x000A)
#define UTF16_CARRIAGE_RETURN			(0x000D)
#define UTF16_FULL_STOP					(0x002E)
#define UTF16_SOLIDUS					(0x002F)
#define UTF16_SPACE						(0x0020)
#define UTF16_DIGIT_ZERO				(0x0030)
#define UTF16_DIGIT_NINE				(0x0039)

#define UTF16_CAPITAL_A					(0x0041)
#define UTF16_CAPITAL_Z					(0x005A)

#define UTF16_A								(0x0061)
#define UTF16_B								UTF16_A + 1
#define UTF16_C								UTF16_A + 2
#define UTF16_D								UTF16_A + 3
#define UTF16_E								UTF16_A + 4
#define UTF16_F								UTF16_A + 5
#define UTF16_G								UTF16_A + 6
#define UTF16_H								UTF16_A + 7
#define UTF16_I								UTF16_A + 8
#define UTF16_J								UTF16_A + 9
#define UTF16_K								UTF16_A + 10
#define UTF16_L								UTF16_A + 11
#define UTF16_M								UTF16_A + 12
#define UTF16_N								UTF16_A + 13
#define UTF16_O								UTF16_A + 14
#define UTF16_P								UTF16_A + 15
#define UTF16_Q								UTF16_A + 16
#define UTF16_R								UTF16_A + 17
#define UTF16_S								UTF16_A + 18
#define UTF16_T								UTF16_A + 19
#define UTF16_U								UTF16_A + 20
#define UTF16_V								UTF16_A + 21
#define UTF16_W								UTF16_A + 22
#define UTF16_X								UTF16_A + 23
#define UTF16_Y								UTF16_A + 24
#define UTF16_Z								UTF16_A + 25

/**
 * webvtt_wchar - A utf16 surrogate/character
 */
typedef webvtt_uint16 webvtt_wchar, *webvtt_wchar_ptr;

/**
 * webvtt_string - A buffer of utf16 characters
 */
typedef struct webvtt_string_t *webvtt_string;
typedef struct webvtt_utf8_reader_t *webvtt_utf8_reader;
typedef struct webvtt_string_list_t webvtt_string_list, *webvtt_string_list_ptr;

/**
 * These objects are NOT reference counted, they
 * are not meant to be shared.
 *
 * If this is required by mozilla, it can be added.
 */
struct
webvtt_string_t
{
	webvtt_uint32 alloc;
	webvtt_uint32 length;
	webvtt_wchar *text;
	webvtt_wchar array[1];
};

struct
webvtt_utf8_reader_t
{
	webvtt_uint32 uc; /* ucs4 character */
	webvtt_uint32 bytes_left; /* remaining bytes in utf8 character sequence */
	webvtt_uint32 min_uc; /* minimum allowed codepoint given the number of bytes */
	webvtt_uint32 nc; /* number of non-characters encountered */
};

struct
webvtt_string_list_t
{
	webvtt_uint alloc;
	webvtt_uint list_count;
	webvtt_string *items;
};

WEBVTT_EXPORT webvtt_status webvtt_create_string( webvtt_uint32 alloc, webvtt_string *ppstr );
WEBVTT_EXPORT void webvtt_delete_string( webvtt_string pstr );

WEBVTT_EXPORT webvtt_status webvtt_create_string_list( webvtt_string_list_ptr *string_list_pptr );
WEBVTT_EXPORT void webvtt_delete_string_list( webvtt_string_list_ptr string_list_ptr );
WEBVTT_EXPORT webvtt_status webvtt_add_to_string_list( webvtt_string_list_ptr string_list_ptr, webvtt_string string );

/**
 * Methods for appending data to strings.
 */
WEBVTT_EXPORT webvtt_status webvtt_string_append_utf8( webvtt_string *ppstr, const webvtt_byte *buffer,
	webvtt_uint *pos, webvtt_uint len, webvtt_utf8_reader reader );

WEBVTT_EXPORT webvtt_status append_wchar_to_wchar( webvtt_wchar *append_to, webvtt_uint len, webvtt_wchar *to_append, webvtt_uint start, webvtt_uint stop );
WEBVTT_EXPORT webvtt_status webvtt_string_append_wchar( webvtt_string *append_to, webvtt_wchar *to_append, webvtt_uint len );
WEBVTT_EXPORT webvtt_status webvtt_string_append_single_wchar( webvtt_string *append_to, webvtt_wchar to_append );
WEBVTT_EXPORT webvtt_status webvtt_string_append_string( webvtt_string *append_to, webvtt_string to_append );

/**
 * Compare two strings.
 * Return 1 if equal 0 if not equal.
 */
WEBVTT_EXPORT webvtt_status webvtt_compare_strings( webvtt_string one, webvtt_string two );

/**
 * Compare two wchars.
 * Return 1 if equal 0 if not.
 */
WEBVTT_EXPORT webvtt_status webvtt_compare_wchars( webvtt_wchar  *one, webvtt_uint one_len, webvtt_wchar *two, webvtt_uint two_len );

/**
 * Returns successful if the character is a alphanumeric.
 */
WEBVTT_EXPORT webvtt_status webvtt_is_alphanumeric( webvtt_wchar character );

/**
 * Returns successful if the character is a digit.
 */
WEBVTT_EXPORT webvtt_status webvtt_is_digit( webvtt_wchar character );

/**
 * Advances a pointer past one LF or CR(LF) line ending.
 */
WEBVTT_EXPORT webvtt_status webvtt_advance_past_line_ending( webvtt_wchar_ptr *position_pptr );

#endif
