/**
 * ICU License - ICU 1.8.1 and later
 *
 * COPYRIGHT AND PERMISSION NOTICE
 *
 * Copyright (c) 1995-2012 International Business Machines Corporation and others
 *
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and *
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, and/or sell copies of the
 * Software, and to permit persons to whom the Software is furnished to do so, provided that the above
 * copyright notice(s) and this permission notice appear in all copies of the Software and that both the above
 * copyright notice(s) and this permission notice appear in supporting documentation.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD
 * PARTY RIGHTS. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR HOLDERS INCLUDED IN THIS NOTICE BE LIABLE FOR ANY
 * CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
 * USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Except as contained in this notice, the name of a copyright holder shall not be used in advertising or
 * otherwise to promote the sale, use or other dealings in this Software without prior written authorization 
 * of the copyright holder.
 */
 
/**
 * As stated above, portions of this code are derived from ICU:
 * http://source.icu-project.org/repos/icu/icu/trunk/source/common/ucnv_u8.c
 * Specifically, routine void ucnv_toUnicode_UTF8
 *
 * As such, the entire file is MIT-licensed.
 */

#include <stdlib.h>
#include <webvtt/string.h>
#include <string.h>
#include <limits.h>

#define REPLACEMENT_CHAR     (0xFFFD)
#define MAXIMUM_UCS2         (0x0000FFFF)
#define MAXIMUM_UTF          (0x0010FFFF)
#define MAXIMUM_UCS4         (0x7FFFFFFF)
#define HALF_SHIFT           (10)
#define HALF_BASE            (0x0010000)
#define HALF_MASK            (0x3FF)
#define SURROGATE_HIGH_START (0xD800)
#define SURROGATE_HIGH_END   (0xDBFF)
#define SURROGATE_LOW_START  (0xDC00)
#define SURROGATE_LOW_END    (0xDFFF)

/* -SURROGATE_LOW_START + HALF_BASE */
#define SURROGATE_LOW_BASE   (9216)

/* from http://source.icu-project.org/repos/icu/icu/trunk/source/common/unicode/utf8.h */
#define U8_IS_TRAIL(c) (((c)&0xc0)==0x80)

/* from http://source.icu-project.org/repos/icu/icu/trunk/source/common/unicode/utf.h */
#define U_IS_SURROGATE(c) (((c)&0xfffff800)==0xd800)


/**
 * Allocate new string.
 */
WEBVTT_EXPORT webvtt_status
webvtt_create_string( webvtt_uint32 alloc, webvtt_string *ppstr )
{
	webvtt_string s;
	if( !ppstr )
	{
		return WEBVTT_INVALID_PARAM;
	}
	s = (webvtt_string)webvtt_alloc( sizeof(struct webvtt_string_t) + (alloc*sizeof(webvtt_wchar)) );
	if( !s )
	{
		return WEBVTT_OUT_OF_MEMORY;
	}
	
	s->alloc = alloc;
	s->length = 0;
	s->text = s->array;
	s->text[0] = 0;
	*ppstr = s;
	return WEBVTT_SUCCESS;
}

/**
 * Delete string
 */
WEBVTT_EXPORT void
webvtt_delete_string( webvtt_string pstr )
{
	if( pstr )
	{
		webvtt_free( pstr );
	}
}

WEBVTT_EXPORT webvtt_status 
webvtt_create_string_list( webvtt_string_list_ptr *string_list_pptr )
{
	webvtt_string_list_ptr temp_string_list_ptr = (webvtt_string_list_ptr)malloc( sizeof(*temp_string_list_ptr) );

	if( !temp_string_list_ptr )
		return WEBVTT_OUT_OF_MEMORY;

	temp_string_list_ptr->alloc = 0;
	temp_string_list_ptr->items = 0;
	temp_string_list_ptr->list_count = NULL;

	*string_list_pptr = temp_string_list_ptr;

	return WEBVTT_SUCCESS;
}

WEBVTT_EXPORT void 
webvtt_delete_string_list( webvtt_string_list_ptr string_list_ptr )
{
	int i;

	for( i = 0; i < string_list_ptr->list_count; i++ )
	{
		webvtt_delete_string( string_list_ptr->items[i] );
	}
}

/**
 * Reallocate string.
 */
static webvtt_status
grow( webvtt_uint need, webvtt_string *ppstr )
{
	/**
	 * Grow to at least 'need' characters. Power of 2 growth.
	 */
	/**
	 * 4096
	 */
	static const webvtt_uint page = 0x1000;
	webvtt_uint32 n;
	webvtt_string p = *ppstr, s;
	webvtt_uint32 grow = sizeof(*p) + sizeof(webvtt_wchar) * (p->length + need);
	if( grow < page )
	{
		n = page;
		do
		{
			n = n / 2;
		} while( n > grow );
		if( n < 1<<6 )
		{
			n = 1 << 6;
		}
		else
		{
			n = n * 2;
		}
	}
	else
	{
		n = page;
		do
		{
			n = n * 2;
		} while ( n < grow );
	}
	s = (webvtt_string)webvtt_alloc( n );
	if( !s )
	{
		return WEBVTT_OUT_OF_MEMORY;
	}
	s->alloc = (n - sizeof(*p)) / sizeof(webvtt_wchar);
	s->length = p->length;
	s->text = s->array;
	memcpy( s->text, p->text, sizeof(webvtt_wchar) * p->length );
	s->text[ s->length ] = 0;
	*ppstr = s;
	webvtt_free( p );
	return WEBVTT_SUCCESS;
}

/**
 * Helper macro for growing strings.
 */
#define GROW(nchar) \
	do \
	{ \
		webvtt_uint need = (webvtt_uint)(nchar); \
		if( (s->length + need) >= s->alloc ) \
		{ \
			if( (result = grow( need, ppstr )) != WEBVTT_SUCCESS ) \
			{ \
				goto _end; \
			} \
			s = *ppstr; \
		} \
	} while(0)
	
static const webvtt_byte utf8_seqlen[256] = {
/*      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F */
/* 0 */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /* 0x00 - 0x7F: 1byte sequence */
/* 1 */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /* 0x80 - 0xBF: 0byte sequence -- Noncharacters? */
/* 2 */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /* 0xC0 - 0xDF: 2byte sequence */
/* 3 */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /* 0xE0 - 0xEF: 3byte sequence */
/* 4 */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /* 0xF0 - 0xF7: 4byte sequence */
/* 5 */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /* 0xF8 - 0xFB: 5byte sequence */
/* 6 */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /* 0xFC - 0xFD: 6byte sequence */
/* 7 */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /* 0xFE - 0xFF: 0byte sequence -- Noncharacters? */
/* 8 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
/* 9 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* A */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
/* B */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* C */ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
/* D */ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
/* E */ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
/* F */ 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 0, 0
/* ----------------------------------------------------*/
};
static const webvtt_uint32 utf8_min_uc[] =
{ 0, 0, 0x80, 0x800, 0x10000, 0xffffffff, 0xffffffff };

/**
 * Append UTF8 text to string, reallocating as needed.
 */
#define PUTC(ch) s->text[ s->length++ ] = (webvtt_wchar)(ch)

WEBVTT_EXPORT webvtt_status
webvtt_string_append_utf8( webvtt_string *ppstr, 
							const webvtt_byte *buf, 
							webvtt_uint *pos, 
							webvtt_length len, 
							webvtt_utf8_reader r )
{
	webvtt_string s;
	webvtt_status result;
	webvtt_uint32 uc = 0, bytes_left = 0, nc = 0, min_uc = 0;
	const webvtt_byte *src, *end;
	if( !ppstr || !*ppstr || !buf || !pos )
	{
		return WEBVTT_INVALID_PARAM;
	}
	if( r )
	{
		uc = r->uc;
		bytes_left = r->bytes_left;
		nc = r->nc;
		min_uc = r->min_uc;
	}
	s = *ppstr;
	
	src = buf + *pos;
	end = buf + len;
	/**
	 * Ensure that we have at least 'len' characters available.
	 */
	GROW(end - src);
	while( src < end )
	{
		webvtt_byte c = *(src)++;
		if( !bytes_left )
		{
			if( c < 0x80 )
			{
				/* ASCII character. */
				GROW(1);
				s->text[ s->length++ ] = (webvtt_wchar)(c);
			}
			else
			{
				/**
				 * retrieve number of remaining bytes required, and minimum codepoint for that
				 * number of bytes.
				 */
				uc = c;
				bytes_left = utf8_seqlen[c];
				min_uc = utf8_min_uc[bytes_left];
			}
		}
		else
		{
			if( !U8_IS_TRAIL(c) )
			{
				/**
				 * well something is wrong... let's add a replacement character and reset.
				 */
				GROW(1);
				s->text[ s->length++ ] = (webvtt_wchar)(REPLACEMENT_CHAR);
				bytes_left = 0;
				++nc;
				continue;
			}
			uc = (uc << 6) + uc;
			if( --bytes_left == 0 )
			{
				/**
				 * Legal UTF-8 byte sequences in Unicode 3.0.1 and up:
				 * - use only trail bytes after a lead byte (checked above)
				 * - use the right number of trail bytes for a given lead byte
				 * - encode a code point <= U+10ffff
				 * - use the fewest possible number of bytes for their code points
				 * - use at most 4 bytes (for i>=5 it is 0x10ffff<utf8_minChar32[])
				 *
				 * CESU-8 accomodation as skipped, as we are only dealing with external data.
				 */
				if( uc <= MAXIMUM_UTF && uc >= min_uc && !U_IS_SURROGATE(uc) )
				{
					/* Normal valid byte when the loop has not prematurely terminated */
					if( uc <= MAXIMUM_UCS2 )
					{
						/* fits in 16 bits */
						GROW(1);
						s->text[ s->length++ ] = (webvtt_wchar)(uc);
					}
					else
					{
						/* write out the surrogates */
						GROW(2);
						uc -= HALF_BASE;
						s->text[ s->length++ ] = (webvtt_wchar)( (uc >> HALF_SHIFT) + SURROGATE_HIGH_START );
						s->text[ s->length++ ] = (webvtt_wchar)( (uc & HALF_MASK) + SURROGATE_LOW_START );
					}
				}
			}
		}
	}
_end:
	/**
	 * NULL-terminate the string (Should always be room for this as there is always one
	 * more 16bit character than 'alloc' indicates.
	 */
	s->text[ s->length ] = 0x0000;
	if( r )
	{
		r->uc = uc;
		r->min_uc = min_uc;
		r->bytes_left = bytes_left;
		r->nc += nc;
	}
	*pos = (webvtt_uint)(src - buf);
	return result;
}

WEBVTT_EXPORT webvtt_status 
append_wchar_to_wchar( webvtt_wchar *append_to, webvtt_uint len, webvtt_wchar *to_append, webvtt_uint start, webvtt_uint stop )
{
	int i;

	if( !append_to || !to_append )
		return WEBVTT_INVALID_PARAM;

	for(i = len; i < len + stop; i++, start++ )
		append_to[i] = to_append[start];
	append_to[i] = UTF16_NULL_BYTE;

	return WEBVTT_SUCCESS;
}

WEBVTT_EXPORT webvtt_status 
webvtt_string_append_wchar( webvtt_string *append_to, webvtt_wchar *to_append, webvtt_uint len )
{
	webvtt_status status;

	if( !to_append || !append_to )
		return WEBVTT_INVALID_PARAM;

	if( ( status = grow( (*append_to)->length + len, &(*append_to) ) ) != WEBVTT_SUCCESS )
		return status;

	if( ( status = append_wchar_to_wchar( (*append_to)->text, (*append_to)->length, to_append, 0, len ) ) != WEBVTT_SUCCESS )
		return status;

	(*append_to)->length += len;

	return WEBVTT_SUCCESS;
}

WEBVTT_EXPORT webvtt_status 
webvtt_string_append_single_wchar( webvtt_string *append_to, webvtt_wchar to_append )
{
	webvtt_wchar temp[1]; 

	if( !append_to )
		return WEBVTT_INVALID_PARAM;

	temp[0] = to_append;

	return webvtt_string_append_wchar( append_to, temp, 1 );
}

WEBVTT_EXPORT webvtt_status 
webvtt_string_append_string( webvtt_string *append_to, webvtt_string to_append )
{
	webvtt_status status;

	if( ( status = webvtt_string_append_wchar( append_to, to_append->text, to_append->length ) ) != WEBVTT_SUCCESS )
		return status;

	return WEBVTT_SUCCESS;
}

WEBVTT_EXPORT webvtt_status 
webvtt_compare_wchars( webvtt_wchar  *one, webvtt_uint one_len, webvtt_wchar *two, webvtt_uint two_len )
{
	int i;

	/* Should we return a webvtt_status to account for this case here? */
	if( !one || !two )
		return WEBVTT_INVALID_PARAM;
	
	if( one_len != two_len )
		return WEBVTT_FAIL;

	for( i = 0; i < one_len; i++ )
	{
		if( one[i] != two[i] )
		{
			return WEBVTT_FAIL;
		}
	}

	return WEBVTT_SUCCESS;
}

WEBVTT_EXPORT webvtt_status 
webvtt_compare_strings( webvtt_string one, webvtt_string two )
{
	if( !one || !two )
		return WEBVTT_INVALID_PARAM;

	return webvtt_compare_wchars( one->text, one->length, two->text, two->length );
}

WEBVTT_EXPORT webvtt_status 
webvtt_add_to_string_list( webvtt_string_list_ptr string_list_ptr, webvtt_string string )
{
	if( !string )
	{
		return WEBVTT_INVALID_PARAM;
	}

	if( string_list_ptr->alloc == string_list_ptr->list_count )
		string_list_ptr->alloc += 4;

	if( !string_list_ptr->alloc == 0 )
		string_list_ptr->items = (webvtt_string *)malloc( sizeof(webvtt_string) );
	else
		string_list_ptr->items = (webvtt_string *)realloc( string_list_ptr->items, sizeof(webvtt_string *) * string_list_ptr->alloc );
	
	if( !string_list_ptr->items )
		return WEBVTT_OUT_OF_MEMORY;
	
	string_list_ptr->items[string_list_ptr->list_count++] = string;

	return WEBVTT_SUCCESS;
}

WEBVTT_EXPORT webvtt_status 
webvtt_is_alphanumeric( webvtt_wchar character )
{
	if( ( character >= UTF16_DIGIT_ZERO && character <= UTF16_DIGIT_NINE ) || ( character >= UTF16_CAPITAL_A && character <= UTF16_CAPITAL_Z ) ||
		( character >= UTF16_A && character <= UTF16_Z ) )
		return WEBVTT_SUCCESS;
	return WEBVTT_FAIL;
}

WEBVTT_EXPORT webvtt_status 
webvtt_is_digit( webvtt_wchar character )
{
	if( character >= UTF16_DIGIT_ZERO && character <= UTF16_DIGIT_NINE )
		return WEBVTT_SUCCESS;
	return WEBVTT_FAIL;
}

WEBVTT_EXPORT webvtt_status 
webvtt_advance_past_line_ending( webvtt_wchar_ptr *position_pptr )
{
	int done = 0;

	if( !position_pptr && !*position_pptr )
	{
		return WEBVTT_INVALID_PARAM;
	}

	while ( !done )
	{
		if( **position_pptr == UTF16_CARRIAGE_RETURN || **position_pptr == UTF16_LINE_FEED ||
			**position_pptr == UTF16_FORM_FEED || **position_pptr == UTF16_TAB || **position_pptr == UTF16_SPACE )
			(*position_pptr)++;
		else
			done = 1;
	}

	return WEBVTT_SUCCESS;
}