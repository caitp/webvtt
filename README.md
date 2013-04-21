#libwebvtt
The library for interpreting and authoring conformant WebVTT content
WebVTT is a caption and subtitle format designed for use with HTML5
audio and video elements.

See: [W3C WebVTT Draft](http://dev.w3.org/html5/webvtt/)

[![Build Status](https://travis-ci.org/mozilla/webvtt.png?branch=dev)](https://travis-ci.org/mozilla/webvtt)

##Build Instructions:

In Unix-like environments, we use autotools:

```
./bootstrap.sh && ./configure && make
```

On Windows, we use a Visual Studio Project, see files in build/msvc2010

##Running Tests:

All tests are written using Google Test, and run using `make check`. You can configure the tests to run with our without valgrind, for memory checking.

Without valgrind:

```
./configure
make
make check
```

With valgrind:

```
./configure --enable-valgrind-testing
make
make check
```

When running tests with valgrind, any test that fails valgrind (even if it passes Google Test) will fail. See `test/unit/Makefile.am` for info on known test failures, and how to add/remove them.

##Routines available to application:
### Parser Object
		
        ####webvtt_status webvtt_create_parser( webvtt_cue_fn on_read, webvtt_error_fn on_error, void *userdata, webvtt_parser *ppout );
		####Returns: webvtt_status
		####Parameters: 
				webvtt_cue_fn - pointer to function used to read cue.
				webvtt_error_fn - pointer to function used for error handling.
				void* - pointer to an input file that constains the user data to parse.
				webvtt_parser - instance of the webvtt_parser object.
		####Description:
			Initializes a webvtt parser instance with the arguments supplied.
		####Code Example:
		
			  if( ( result = webvtt_create_parser( &cue, &error, (void *)input_file, &vtt ) ) != WEBVTT_SUCCESS ) {
				fprintf( stderr, "error: failed to create VTT parser.\n" );
				fclose( fh );
				return 1;
			  }
		  
        ####void webvtt_delete_parser( webvtt_parser parser );
		####Returns: webvtt_status
		####Parameters:
			webvtt_parser - instance of the webvtt_parser object.
		####Description:
			Deletes the supplied webvtt_parser object.
		####Code Example:
			webvtt_parser vtt;
			
			/* Code that uses webvtt_parser Here */
			
			// clean up
			webvtt_delete_parser( vtt );
			
        ####webvtt_status webvtt_parse_chunk( webvtt_parser self, const void *buffer, webvtt_uint len );
		####Returns: webvtt_status
		####Parameters:
			webvtt_parser - instance of the webvtt_parser object.
			const void* - buffer of cue text to be parsed.
			webvtt_uint - unsigned int length of the buffer of cue text.
		####Description:
			Parses cuetext that is supplied in the buffer parameter.
		####Code Example:
			char buffer[0x1000];
			webvtt_uint n_read = (webvtt_uint)fread( buffer, 1, sizeof(buffer), fh );
			finished = feof( fh );
			if( WEBVTT_FAILED(result = webvtt_parse_chunk( vtt, buffer, n_read )) ) {
			  return 1;
			}
			
        ####webvtt_status webvtt_finish_parsing( webvtt_parser self );
		####Returns: webvtt_status
		####Parameters:
			webvtt_parser - instance of the webvtt_parser object.
		####Description:
			Finishes parsing and cleans up the parse state stack
		###Code Example:
			  do {
				char buffer[0x1000];
				webvtt_uint n_read = (webvtt_uint)fread( buffer, 1, sizeof(buffer), fh );
				finished = feof( fh );
				if( WEBVTT_FAILED(result = webvtt_parse_chunk( vtt, buffer, n_read )) ) {
				  return 1;
				}
			} while( !finished && result == WEBVTT_SUCCESS );
	  webvtt_finish_parsing( vtt );
### WebVTT Cues
        ####webvtt_status webvtt_create_cue( webvtt_cue **pcue );
		####Returns: webvtt_status
		####Parameters:
			webvtt_cue - a cue object that represents a webvtt cue in a .vtt file.
	    ####Description:
		
        void webvtt_ref_cue( webvtt_cue *cue );
        void webvtt_release_cue( webvtt_cue **pcue );
        int webvtt_validate_cue( webvtt_cue *cue );

### WebVTT Nodes
        void webvtt_init_node( webvtt_node **node );
        void webvtt_ref_node( webvtt_node *node );
        void webvtt_release_node( webvtt_node **node );

### Application Callbacks
        typedef int ( WEBVTT_CALLBACK *webvtt_error_fn )( void *userdata, webvtt_uint line, webvtt_uint col, webvtt_error error );
        typedef void ( WEBVTT_CALLBACK *webvtt_cue_fn )( void *userdata, webvtt_cue *cue );
        
### Strings
        void webvtt_init_string( webvtt_string *result );
        webvtt_status webvtt_create_string( webvtt_uint32 alloc, webvtt_string *result );
        webvtt_status webvtt_create_string_with_text( webvtt_string *result, const char *init_text, int len );
        void webvtt_ref_string( webvtt_string *str );
        void webvtt_release_string( webvtt_string *str );     
        webvtt_status webvtt_string_detach( webvtt_string *str );
        void webvtt_copy_string( webvtt_string *left, const webvtt_string *right );    
        webvtt_uint webvtt_string_is_empty( const webvtt_string *str );
        const char *webvtt_string_text( const webvtt_string *str );
        webvtt_uint32 webvtt_string_length( const webvtt_string *str );
        webvtt_uint32 webvtt_string_capacity( const webvtt_string *str );
        int webvtt_string_getline( webvtt_string *str, const char *buffer, webvtt_uint *pos, int len, int *truncate, webvtt_bool finish );
        webvtt_status webvtt_string_putc( webvtt_string *str, char to_append );
        webvtt_bool webvtt_string_is_equal( const webvtt_string *str, const char *to_compare, int len );
        webvtt_status webvtt_string_append( webvtt_string *str, const char *buffer, int len );
        webvtt_status webvtt_string_append_string( webvtt_string *str, const webvtt_string *other );

### UTF8 And UTF16 Conversion
        webvtt_bool webvtt_next_utf8( const char **begin, const char *end );
        webvtt_bool webvtt_skip_utf8( const char **begin, const char *end, int n_chars );
        webvtt_uint16 webvtt_utf8_to_utf16( const char *utf8, const char *end, webvtt_uint16 *high_surrogate );
        int webvtt_utf8_chcount( const char *utf8, const char *end );
        int webvtt_utf8_length( const char *utf8 );

### String List
        webvtt_status webvtt_create_stringlist( webvtt_stringlist **result );
        void webvtt_ref_stringlist( webvtt_stringlist *list );
        void webvtt_copy_stringlist( webvtt_stringlist **left, webvtt_stringlist *right );
        void webvtt_release_stringlist( webvtt_stringlist **list );
        webvtt_status webvtt_stringlist_push( webvtt_stringlist *list, webvtt_string *str );
        
### Memory Allocation
        void *webvtt_alloc( webvtt_uint nb );
        void *webvtt_alloc0( webvtt_uint nb );
        void webvtt_free( void *data );
        void webvtt_set_allocator( webvtt_alloc_fn_ptr alloc, webvtt_free_fn_ptr free, void *userdata );

### Memory Application Callbacks
        typedef void *(WEBVTT_CALLBACK *webvtt_alloc_fn_ptr)( void *userdata, webvtt_uint nbytes );
        typedef void (WEBVTT_CALLBACK *webvtt_free_fn_ptr)( void *userdata, void *pmem );

### Error handling
	const char *webvtt_strerror( webvtt_error );

## Current Users
  * Mozilla Firefox
  
##License
> Copyright (c) 2013 Mozilla Foundation and Contributors
> All rights reserved.
>
> Redistribution and use in source and binary forms, with or without
> modification, are permitted provided that the following conditions are
> met:
>
> - Redistributions of source code must retain the above copyright
> notice, this list of conditions and the following disclaimer.
> - Redistributions in binary form must reproduce the above copyright
> notice, this list of conditions and the following disclaimer in the
> documentation and/or other materials provided with the distribution.
>
> THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
> ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
> LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
> A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
> HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
> SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
> LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
> DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
> THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
> (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
> OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

