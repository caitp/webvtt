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


```C
webvtt_status webvtt_create_parser(webvtt_cue_fn on_read, webvtt_error_fn on_error, void* userdata, webvtt_parser *ppout );
```
**Returns:** webvtt_status - status code of the webvtt parser <br /><br />
**Parameters:** <br /><br />
	**webvtt_cue_fn** - pointer to function used to read cue.<br />
	**webvtt_error_fn** - pointer to function used for error handling.<br />
	**void* userdata** - pointer to an input file that constains the user data to parse.<br />
	**webvtt_parser** - instance of the webvtt_parser object.<br />
	<br />
**Description:** <br /><br />
	Initializes a webvtt parser instance with the arguments supplied.
	<br /><br />
**Code Example:**<br />
```C	
	if( ( result = webvtt_create_parser( &cue, &error, (void *)input_file, &vtt ) ) != WEBVTT_SUCCESS ) {
		fprintf( stderr, "error: failed to create VTT parser.\n" );
		fclose( fh );
		return 1;
	}
```

```C
void webvtt_delete_parser( webvtt_parser parser );
```
**Returns:** webvtt_status - status code of the webvtt parser<br /><br />
**Parameters:**<br /><br />
	**webvtt_parser parser** - instance of the webvtt_parser object.<br />
	<br />
**Description:**<br /><br />
	Deletes the supplied webvtt_parser object.<br /><br />
**Code Example:**
```C
	webvtt_parser vtt;
			
	/* Code that uses webvtt_parser Here */
			
	// clean up
	webvtt_delete_parser( vtt );
```
```C
webvtt_status webvtt_parse_chunk( webvtt_parser self, const void *buffer, webvtt_uint len );
```
**Returns:** webvtt_status - status code of the webvtt parser <br /><br />
**Parameters:**<br /><br />
	**webvtt_parser self** - instance of the webvtt_parser object. <br />
	**const void *buffer** - buffer of cue text to be parsed.<br />
	**webvtt_uint len** - unsigned int length of the buffer of cue text. <br />
<br />
**Description:**<br /><br />
Parses cuetext that is supplied in the buffer parameter.<br /><br />
**Code Example:** <br />
```C
			char buffer[0x1000];
			webvtt_uint n_read = (webvtt_uint)fread( buffer, 1, sizeof(buffer), fh );
			finished = feof( fh );
			if( WEBVTT_FAILED(result = webvtt_parse_chunk( vtt, buffer, n_read )) ) {
			  return 1;
			}
```

```C
webvtt_status webvtt_finish_parsing( webvtt_parser self );
```
**Returns:** webvtt_status - status code of the webvtt parser<br /><br />
**Parameters:**<br /><br />
	**webvtt_parser self** - instance of the webvtt_parser object.<br /><br />
**Description:**<br /><br />
Finishes parsing and cleans up the parse state stack<br /><br />
**Code Example:**<br />
```C
			  do {
				char buffer[0x1000];
				webvtt_uint n_read = (webvtt_uint)fread( buffer, 1, sizeof(buffer), fh );
				finished = feof( fh );
				if( WEBVTT_FAILED(result = webvtt_parse_chunk( vtt, buffer, n_read )) ) {
				  return 1;
				}
			} while( !finished && result == WEBVTT_SUCCESS );
	  webvtt_finish_parsing( vtt );
```
### WebVTT Cues
```C
webvtt_status webvtt_create_cue( webvtt_cue **pcue );
```
**Returns:** webvtt_status - status code of the webvtt parser <br /><br />
**Parameters:** <br /><br />
	**webvtt_cue **pcue** - a cue object that represents a webvtt cue in a .vtt file.<br />
<br />
**Description:** <br /><br />
	initializes a supplied webvtt_cue instance.<br /><br />
**Code Example:**<br />
```C	
webvtt_create_cue( &self->top->v.cue );
```
```C
void webvtt_ref_cue( webvtt_cue *cue );
```
**Returns:** void<br /><br />
**Parameters:** <br />
<br />
	**webvtt_cue cue** - a cue object that represents a webvtt cue in a .vtt file.<br />
<br />
**Description:** <br /><br />
Adds the supplied webvtt_cue reference to the reference count of webvtt_cue instances. Manages the lifetime of the webvtt_cue object.
	<br /><br />
**Code Example:**<br />
```C	
Cue( webvtt_cue *pcue ) {
    webvtt_ref_cue(pcue);
    cue = pcue;
  }
```		
```C
void webvtt_release_cue( webvtt_cue **pcue );
```
**Returns:** void <br /><br />
**Parameters:** <br /><br />
	**webvtt_cue **pcue** - a cue object that represents a webvtt cue in a .vtt file.<br />
<br />
**Description:** <br /><br />
Releases supplied cue instance from internel memory and increases cue reference count.
	<br /><br />
**Code Example:**<br />
```C	
Cue cue(pcue);
  /**
   * Cue object increases the reference count of pcue, so we can dereference it
   */
  webvtt_release_cue( &pcue );
```      

```C
int webvtt_validate_cue( webvtt_cue *cue );
```
**Returns:** webvtt_status - status code of the webvtt parser <br /><br />
**Parameters:** <br /><br />
	**webvtt_cue *cue** - a cue object that represents a webvtt cue in a .vtt file.<br />
<br />
**Description:** <br /><br />
Validates a cue. If valid, notifies the application that a cue has been read.
	<br /><br />
**Code Example:**<br />
```C	
if( cue ) {
      if( webvtt_validate_cue( cue ) ) {
        self->read( self->userdata, cue );
      } else {
        webvtt_release_cue( &cue );
      }
      *pcue = 0;
    }
```    
        

### WebVTT Nodes

```C
 void webvtt_init_node( webvtt_node **node );
```
**Returns:** void <br /><br />
**Parameters:** <br /><br />
	**webvtt_node **node** - pointer to webvtt_node type.<br />
<br />
**Description:** <br /><br />
Initializes the supplied webvtt_node** reference.
	<br /><br />
**Code Example:**<br />
```C	
webvtt_node **node;

webvtt_init_node(node);

```
```C
void webvtt_ref_node( webvtt_node *node );
```
**Returns:** void<br /><br />
**Parameters:** <br /><br />
	**webvtt_node node** - represents a webvtt node object <br />
<br />
**Description:**<br /><br />
Adds the supplied webvtt_node reference and increments the reference count of the nodes managed.
	<br /><br />
**Code Example:**<br />
```C	
if( *node != &empty_node ) {
    if( node && *node ) { 
      webvtt_release_node( node );
    }
    *node = &empty_node;
    webvtt_ref_node( *node );
  }
```
```C
void webvtt_release_node( webvtt_node **node );
```
**Returns:** void <br /><br />
**Parameters:** <br /><br />
	**webvtt_node node** - represents a webvtt node object<br />
<br />
**Description:** <br /><br />
Un-tracks the webvtt_node and decrements the reference count.
	<br /><br />
**Code Example:**<br />
```C	
  for( i = 0; i < n->data.internal_data->length; i++ ) {
        webvtt_release_node( n->data.internal_data->children + i );
      }
```
        
        

### Application Callbacks
        typedef int ( WEBVTT_CALLBACK *webvtt_error_fn )( void *userdata, webvtt_uint line, webvtt_uint col, webvtt_error error );
        typedef void ( WEBVTT_CALLBACK *webvtt_cue_fn )( void *userdata, webvtt_cue *cue );
        
### Strings
```C
void webvtt_init_string( webvtt_string *result );
```
**Returns:** void<br /><br />
**Parameters:** <br /><br />
	**webvtt_string result** - a character string used in webvtt files<br />
<br />
**Description:** <br /><br />
Initializes supplied webvtt_string reference.
	<br /><br />
**Code Example:**<br />
```C	
webvtt_string temp_annotation;

  webvtt_init_string( &temp_annotation );
```
```C
webvtt_status webvtt_create_string( webvtt_uint32 alloc, webvtt_string *result );
```
**Returns:** webvtt_status - status code of the webvtt parser <br /><br />
**Parameters:** <br /><br />
	**webvtt_uint32 alloc** - 32-bit webvtt unsigned int type.<br />
	**webvtt_string *result** - character string type referenced used in webvtt files. <br />
<br />
**Description:** <br /><br />
Creates a webvtt_string using supplied reference and length.
	<br /><br />
**Code Example:**<br />
```C	
if(WEBVTT_FAILED(webvtt_create_string( 0x100, str ))) {
      return -1;
    }
```        
```C
webvtt_status webvtt_create_string_with_text( webvtt_string *result, const char *init_text, int len );
```
**Returns:** webvtt_status - status code of the webvtt parser <br /><br />
**Parameters:** <br /><br />
	**webvtt_string** - character string type referenced used in webvtt files.<br />
	**const char init_text ** - the initialization text.
	**int** - The length of the initialization text.
<br />
**Description:** <br /><br />
Creates a webvtt string supplied in result. Appends text supplied by init_text with the length of len to the webvtt string referenced by result. 
	<br /><br />
**Code Example:**<br />
```C	
	if( WEBVTT_FAILED( status = webvtt_create_string_with_text( &tk,
            self->token, self->token_pos ) ) ) {
            if( sta**webvtt_string *str ** - character string type referenced used in webvtt files.<br />tus == WEBVTT_OUT_OF_MEMORY ) {
              ERROR( WEBVTT_ALLOCATION_FAILED );
            }
            webvtt_release_cue( &cue );
            goto _finish;
          }
```       
```C
void webvtt_ref_string( webvtt_string *str );
```
**Returns:** void <br /><br />
**Parameters:** <br /><br />
	**webvtt_string str** - character string type referenced used in webvtt files.<br />
<br />
**Description:** <br /><br />
Adds webvtt string reference supplied in *str. Increases reference count.
	<br /><br />
**Code Example:**<br />
```C	
if(WEBVTT_FAILED(webvtt_create_string( 0x100, str ))) {
	return -1;
}else
	webvtt_ref_string(str);

```        
```C
void webvtt_release_string( webvtt_string *str );
```
**Returns:** void <br /><br />
**Parameters:** <br /><br />
	**webvtt_string str ** - character string type referenced used in webvtt files.<br />
<br />
**Description:** <br /><br />
Releases webvtt_string referenced by *str and decrements reference count.
	<br /><br />
**Code Example:**<br />
```C	
if( self->line_buffer.d->length == 0 ) {
          webvtt_release_string( &self->line_buffer );
          finished = 1;
}
```        
```C
webvtt_status webvtt_string_detach( webvtt_string *str );
```
**Returns:** webvtt_status - status code of the webvtt parser <br /><br />
**Parameters:** <br /><br />
	**webvtt_string str ** - character string type referenced used in webvtt files.<br />
<br />
**Description:** <br /><br />
Detached a webvtt_string supplied by *str so that it can be safely mutable.
	<br /><br />
**Code Example:**<br />
```C

webvtt_string_detach(str);

if( WEBVTT_FAILED( status = webvtt_create_string_with_text( &str,
            self->token, self->token_pos ) ) ) {
            if( status == WEBVTT_OUT_OF_MEMORY ) {
              ERROR( WEBVTT_ALLOCATION_FAILED );
            }
            webvtt_release_cue( &cue );
            goto _finish;
          }

```            
```C
 void webvtt_copy_string( webvtt_string *destination, const webvtt_string *source );
```
**Returns:**void <br /><br />
**Parameters:** <br /><br />
	**webvtt_string destination ** - character string type referenced used in webvtt files.<br />
	**webvtt_string source ** - character string type referenced used in webvtt files.<br />
<br />
**Description:** <br /><br />
Copies the supplied webvtt_string pointed by *source to the supplied *destination webvtt_string.
	<br /><br />
**Code Example:**<br />
```C	
webvtt_copy_string( &SP->v.text, &self->line_buffer );
webvtt_release_string( &self->line_buffer );
SP->type = V_TEXT;
POP();
finished = 1;
```        
```C
webvtt_uint webvtt_string_is_empty( const webvtt_string *str );
```
**Returns:** webvtt_uint - unsigned int 0 if empty and 1 if not. <br /><br />
**Parameters:** <br /><br />
	**const webvtt_string str ** - constant character string type referenced used in webvtt files.<br />
<br />
**Description:** <br /><br />
Determines if constant webvtt_string supplied in *str is empty. Returns 0 if empty 1 otherwise.
	<br /><br />
**Code Example:**<br />
```C	
if(webvtt_string_is_empty(str) == 1)
	/* Do something if it is empty */
else
	/* Do something else if string is not empty */
	
```           
```C
const char *webvtt_string_text( const webvtt_string *str );
```
**Returns:** const char* - 0 if empty or string referenced in 'str->d->text' <br /><br />
**Parameters:** <br /><br />
	**const webvtt_string str** - constant character string type referenced used in webvtt files.<br />
<br />
**Description:** <br /><br />
Getter that returns the const char* C-string stored within the supplied webvtt_string in *str.
	<br /><br />
**Code Example:**<br />
```C	
const char *text;
webvtt_uint length;
DIE_IF( line == NULL );
length = webvtt_string_length( line );
text = webvtt_string_text( line );
```
```C
webvtt_uint32 webvtt_string_length( const webvtt_string *str );
```
**Returns:** webvtt_uint32 - webvtt unsigned int 32-bit representation of webvtt string length<br /><br />
**Parameters:** <br /><br />
	**const webvtt_string str** - constant character string type referenced used in webvtt files.<br />
<br />
**Description:** <br /><br />
Returns the string length in the form of a 32 bit webvtt unsigned integer of the webvtt string supplied in *str.
	<br /><br />
**Code Example:**<br />
```C	
if( self->line_buffer.d->length == 0 ) {
          webvtt_release_string( &self->line_buffer );
          finished = 1;
} else if( find_bytes( webvtt_string_text( &self->line_buffer ),
          webvtt_string_length( &self->line_buffer ), separator,
          sizeof( separator ) ) == WEBVTT_SUCCESS ) {
          /**
           * Line contains cue-times separator, and thus we treat it as a
           * separate cue. Trick program into thinking that T_CUEREAD had read
           * this line.
           */
```        
```C
webvtt_uint32 webvtt_string_capacity( const webvtt_string *str );
```
**Returns:** webvtt_uint32 - webvtt unsigned int 32-bit representation of webvtt string length<br /><br />
**Parameters:** <br /><br />
	**const webvtt_string str** - constant character string type referenced used in webvtt files.<br />
<br />
**Description:** <br /><br />
Getter which returns the capacity in the supplied constant webvtt string supplied in str. Returns 0 if empty.
	<br /><br />
**Code Example:**<br />
```C
webvtt_uint32 alloc = webvtt_string_capacity(str);

if (alloc != 0)
	webvtt_create_string( webvtt_uint32 alloc, webvtt_string *str );	

```        
```C
int webvtt_string_getline( webvtt_string *str, const char *buffer, webvtt_uint *pos, int len, int *truncate, webvtt_bool finish );
```
**Returns:** webvtt_status - status code of the webvtt parser <br /><br />
**Parameters:** <br /><br />
	**webvtt_string str ** -  character string type referenced used in webvtt files.<br />
	**const char* buffer** - C-String buffer to store a line of text.<br />
	**webvtt_uint pos** - webvtt unsigned integer reference which stores character position in buffer.<br />
	**int len** - length in integer of buffer.<br />
	**int *truncate** - The integer reference of the position to which the buffer is truncated for overflow management.<br />
	**webvtt_bool** - webvtt boolean variable.<br />
<br />
**Description:** <br /><br />
<p>
Gets a C String line from the buffer and stores it in *src. It also updates the *pos variable with the correct character position.
 If the string exceeds the maximum allowable length then *truncate is updated.
 Returns 0 if the function succeeds. -1 if it fails and 1 if it encounters an EOF.

</p>
	<br /><br />
**Code Example:**<br />
```C	
	int v;
        if( ( v = webvtt_string_getline( &SP->v.text, buffer, &pos, len, 0,
                                         finish ) ) ) {
          if( v < 0 ) {
            webvtt_release_string( &SP->v.text );
            SP->type = V_NONE;
            POP();
            ERROR( WEBVTT_ALLOCATION_FAILED );
            status = WEBVTT_OUT_OF_MEMORY;
            goto _finish;
          }
          /* replace '\0' with u+fffd */
          if( WEBVTT_FAILED( status = webvtt_string_replace_all( &SP->v.text,
                                                                 "\0", 1,
                                                                 replacement,
                                                                 3 ) ) ) {
            webvtt_release_string( &SP->v.text );
            SP->type = V_NONE;
            POP();
            ERROR( WEBVTT_ALLOCATION_FAILED );
            goto _finish;
          }
          SP->flags = 1;
        }
      }
```        
```C
webvtt_status webvtt_string_putc( webvtt_string *str, char to_append );
```
**Returns:** webvtt_status - status code of the webvtt parser <br /><br />
**Parameters:** <br /><br />
	**webvtt_string str ** - character string type referenced used in webvtt files.<br />
	**char to_append** - character to append to webvtt_string reference.<br />
<br />
**Description:** <br /><br />
<p>
Appends the character supplied in to_append to the end of supplied webvtt_string *str.
</p>
	<br /><br />
**Code Example:**<br />
```C	
if( v < 0 || WEBVTT_FAILED( webvtt_string_putc( &self->line_buffer,
                                                        '\n' ) ) ) {
          ERROR( WEBVTT_ALLOCATION_FAILED );
          status = WEBVTT_OUT_OF_MEMORY;
          goto _finish;
        }
```        
```C
webvtt_bool webvtt_string_is_equal( const webvtt_string *str, const char *to_compare, int len );
```
**Returns:** webvtt_bool - a boolean value <br /><br />
**Parameters:** <br /><br />
	**const webvtt_string str ** - constant character string type referenced used in webvtt files.<br />
	**const char to_compare** - a C-String that holds the string to be compared <br />
	**int len** - The length of the string <br />
<br />
**Description:** <br /><br />
<p>
Performs a string comparison between a webvtt_string and C-string. Returns boolean 1 if there is a match 0 otherwise.
</p>
	<br /><br />
**Code Example:**<br />
```C	

if(webvtt_string_equal(str,to_compare,len))
	status = WEBVTT_SUCCESS;
else
	status = WEBVTT_FAILED;

```        
```C
webvtt_status webvtt_string_append( webvtt_string *str, const char *buffer, int len );
```
**Returns:** webvtt_status - status code of the webvtt parser <br /><br />
**Parameters:** <br /><br />
	**webvtt_string str ** - character string type referenced used in webvtt files.<br />
	**const char buffer** - C-style string buffer to be appended to string *str.<br />
<br />
**Description:** <br /><br />
<p>
Appends the C-String supplied in *buffer of integer length len to webvtt_string reference supplied in *str.
</p>
	<br /><br />
**Code Example:**<br />
```C	
if( WEBVTT_FAILED( webvtt_string_append( &cue->id, text,length ) ) ) {
        webvtt_release_string( line );
        ERROR( WEBVTT_ALLOCATION_FAILED );
        return WEBVTT_OUT_OF_MEMORY;
 }
```        
```C
webvtt_status webvtt_string_append_string( webvtt_string *str, const webvtt_string *other );
```
**Returns:** webvtt_status - status code of the webvtt parser <br /><br />
**Parameters:** <br /><br />
	**webvtt_string str ** - character string type referenced used in webvtt files.<br />
	**const webvtt_string other** - a constant webvtt_string to be appended to *str <br />
<br />
**Description:** <br /><br />
<p>
Appends a string exactly like webvtt_string_append for appending webvtt string supplied in *other to webvtt string supplied in *str.
</p>
	<br /><br />
**Code Example:**<br />
```C	
webvtt_string_append_string( &cue->body, &self->line_buffer );
```        
        

### UTF8 And UTF16 Conversion

```C
webvtt_bool webvtt_next_utf8( const char **begin, const char *end );
```
**Returns:** webvtt_status - status code of the webvtt parser <br /><br />
**Parameters:** <br /><br />
	**webvtt_cue_fn** - pointer to function used to read cue.<br />
<br />
**Description:** <br /><br />
<p>
Advances pointer supplied in **begin to the next utf8 string portion. returns 1 if this is successful 0 otherwise.
</p>
	<br /><br />
**Code Example:**<br />
```C	

```
        
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

