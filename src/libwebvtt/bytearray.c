#include <string.h>
#include "bytearray.h"

#define CR (0x0D)
#define LF (0x0A)

/**
 * Allocate new bytearray.
 */
WEBVTT_INTERN webvtt_status
webvtt_create_bytearray( webvtt_uint32 alloc, webvtt_bytearray *pba )
{
	webvtt_bytearray s;
	if( !pba )
	{
		return WEBVTT_INVALID_PARAM;
	}
	s = webvtt_alloc( sizeof(struct webvtt_bytearray_t) + (alloc*sizeof(webvtt_byte)) );
	if( !s )
	{
		return WEBVTT_OUT_OF_MEMORY;
	}
	
	s->alloc = alloc;
	s->length = 0;
	s->text = s->array;
	s->text[0] = 0;
	*pba = s;
	return WEBVTT_SUCCESS;
}

/**
 * Delete bytearray
 */
WEBVTT_INTERN void
webvtt_delete_bytearray( webvtt_bytearray *pstr )
{
	if( pstr && *pstr )
	{
		webvtt_free( *pstr );
		*pstr = 0;
	}
}

WEBVTT_INTERN static webvtt_status
grow( webvtt_bytearray *pba, webvtt_uint need )
{
	static const webvtt_uint page = 0x1000;
	webvtt_uint n;
	webvtt_bytearray ba = *pba, new_ba;
	webvtt_uint grow = sizeof(*ba) + sizeof(webvtt_byte) * (ba->length + need);
	if( grow < page )
	{
		n = page;
		do
		{
			n = n / 2;
		} while( n > grow );
		n = n * 2;
	}
	else
	{
		n = page;
		do
		{
			n = n * 2;
		} while ( n < grow );
	}
	new_ba = (webvtt_bytearray)webvtt_alloc( n );
	if( !new_ba )
	{
		return WEBVTT_OUT_OF_MEMORY;
	}
	new_ba->alloc = (grow - sizeof(*ba)) / sizeof(webvtt_byte);
	new_ba->length = ba->length;
	new_ba->text = new_ba->array;
	memcpy( new_ba->text, ba->text, sizeof(webvtt_byte) * ba->length );
	new_ba->text[ new_ba->length ] = 0;
	*pba = new_ba;
	webvtt_free( ba );
	return WEBVTT_SUCCESS;
}

WEBVTT_INTERN int
webvtt_bytearray_getline( webvtt_bytearray *pba, const webvtt_byte *buffer,
	webvtt_uint *pos, webvtt_uint len, int *truncate )
{
	int ret = 0;
	webvtt_bytearray ba = *pba;
	const webvtt_byte *s = buffer + *pos;
	const webvtt_byte *p = s;
	const webvtt_byte *n = buffer + len;
	while( p < n && *p != CR && *p != LF ) 
	{
		++p;
	}
	if( p < n )
	{
		ret = 1; /* indicate that we found EOL */
	}
	len = (webvtt_uint)( p - s );
	*pos += len;
	if( ba->length + len >= ba->alloc )
	{
		if( truncate && ba->alloc >= WEBVTT_MAX_LINE )
		{
			/* truncate. */
			(*truncate)++;
		}
		else
		{
			if( grow( pba, len ) == WEBVTT_OUT_OF_MEMORY )
			{
				ret = -1;
			}
			ba = *pba;
		}
	}

	/* Copy everything in */
	if( len && ret >= 0 && ba->length + len < ba->alloc )
	{
		memcpy( ba->text + ba->length, s, len );
		ba->length += len;
		ba->text[ ba->length ] = 0;
	}
	return ret;
}

WEBVTT_INTERN webvtt_status
webvtt_bytearray_putc( webvtt_bytearray *ppstr, webvtt_byte ch )
{
	webvtt_bytearray ba = *ppstr;
	if( ba->length + 1 >= ba->alloc )
	{
		if( grow( ppstr, 1 ) == WEBVTT_OUT_OF_MEMORY )
		{
			return WEBVTT_OUT_OF_MEMORY;
		}
		ba = *ppstr;
	}
	ba->text[ ba->length++ ] = ch;
	ba->text[ ba->length ] = 0;
	return WEBVTT_SUCCESS;
}
