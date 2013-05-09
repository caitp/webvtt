/**
 * Copyright (c) 2013 Mozilla Foundation and Contributors
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *  - Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <string.h>
#include <webvtt/node_list.h>

static webvtt_node_list empty_node_list = {
  { 1 }, /* ref count */
  0, /* alloc */
  0, /* length */
  0 /* children */
};

WEBVTT_EXPORT void
webvtt_init_node_list( webvtt_node_list **out ) {
  if( !out || *out == &empty_node_list ) {
    return;
  }
  if( *out ) {
    webvtt_release_node_list( out );
  }
  *out = &empty_node_list;
  webvtt_ref_node_list( *out );
}

WEBVTT_EXPORT webvtt_status
webvtt_create_node_list( webvtt_node_list **out )
{
  webvtt_node_list *nl;

  if( !out ) {
    return WEBVTT_INVALID_PARAM;
  }

  nl = ( webvtt_node_list * )webvtt_alloc0( sizeof( *nl ) );

  if( !nl ) {
    return WEBVTT_OUT_OF_MEMORY;
  }

  nl->alloc = 0;
  nl->length = 0;
  webvtt_ref_node_list( nl );

  *out = nl;

  return WEBVTT_SUCCESS;
}

WEBVTT_EXPORT void
webvtt_ref_node_list( webvtt_node_list *list )
{
  if( list ) {
    webvtt_ref( &list->refs );
  }
}

WEBVTT_EXPORT void
webvtt_release_node_list( webvtt_node_list **list )
{
  webvtt_uint i;
  webvtt_node_list *nl;

  if( !list || !*list ) {
    return;
  }

  nl = *list;
  if( webvtt_deref( &nl->refs ) == 0 ) {
    if( nl->children ) {
      for( i = 0; i < nl->length; i++ ) {
        webvtt_release_node( nl->children + i );
      }
      webvtt_free( nl->children );
    }
    webvtt_free( nl );
  }
  *list = 0;
}

WEBVTT_EXPORT webvtt_status
webvtt_node_list_push( webvtt_node_list *list, webvtt_node *to_attach )
{
  webvtt_node **new_children = 0;

  if( !list || !to_attach ) {
    return WEBVTT_INVALID_PARAM;
  }

  if( list->alloc == 0 ) {
    new_children = (webvtt_node **)webvtt_alloc0( sizeof( webvtt_node * ) * 8 );

    if( !new_children ) {
      return WEBVTT_OUT_OF_MEMORY;
    }

    list->children = new_children;
    list->alloc = 8;
  }

  if( list->length + 1 >= ( list->alloc / 3 ) * 2 ) {

    new_children = (webvtt_node **)webvtt_alloc0( sizeof( *new_children ) * 
                                                          list->alloc * 2 );

    if( !new_children ) {
      return WEBVTT_OUT_OF_MEMORY;
    }

    list->alloc *= 2;
    memcpy( new_children, list->children, 
            list->length * sizeof( webvtt_node * ) );
    webvtt_free( list->children );
    list->children = new_children;
  }

  list->children[ list->length++ ] = to_attach;
  webvtt_ref_node( to_attach );

  return WEBVTT_SUCCESS;
}
