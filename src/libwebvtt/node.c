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
#include "node_internal.h"

static webvtt_node empty_node = {
  { 1 }, /* init ref count */
  0, /* parent */
  WEBVTT_EMPTY_NODE, /* node kind */
  { { 0 } } /* value */
};

WEBVTT_EXPORT void
webvtt_ref_node( webvtt_node *node )
{
  if( node ) {
    webvtt_ref( &node->refs );
    if( !WEBVTT_IS_LEAF(node->kind) && node->data.internal_data ) {
      webvtt_internal_node_data *d = node->data.internal_data; 
      /*webvtt_ref_node_list( &d->node_list );*/
    }
  }
}

WEBVTT_EXPORT void
webvtt_init_node( webvtt_node **node )
{
  if( *node != &empty_node ) {
    if( node && *node ) {
      webvtt_release_node( node );
    }
    *node = &empty_node;
    webvtt_ref_node( *node );
  }
}

WEBVTT_EXPORT void
webvtt_copy_node( webvtt_node **dest, const webvtt_node *src )
{
  if( dest && src ) {
    webvtt_ref_node( (webvtt_node *)src );
    *dest = (webvtt_node *)src;
  }
}

WEBVTT_INTERN webvtt_status
webvtt_create_node( webvtt_node **node, webvtt_node_kind kind,
                    webvtt_node *parent )
{
  webvtt_node *temp_node;

  if( !node ) {
    return WEBVTT_INVALID_PARAM;
  }

  if( !( temp_node = (webvtt_node *)webvtt_alloc0(sizeof(*temp_node)) ) )
  {
    return WEBVTT_OUT_OF_MEMORY;
  }

  webvtt_ref_node( temp_node );
  temp_node->kind = kind;
  temp_node->parent = parent;
  *node = temp_node;

  return WEBVTT_SUCCESS;
}

WEBVTT_INTERN webvtt_status
webvtt_create_internal_node( webvtt_node **node, webvtt_node *parent,
                             webvtt_node_kind kind,
                             webvtt_stringlist *css_classes,
                             webvtt_string *annotation )
{
  webvtt_status status;
  webvtt_internal_node_data *node_data;

  if( WEBVTT_FAILED( status = webvtt_create_node( node, kind, parent ) ) ) {
    return status;
  }

  if ( !( node_data =
         (webvtt_internal_node_data *)webvtt_alloc0( sizeof(*node_data) ) ) )
  {
    return WEBVTT_OUT_OF_MEMORY;
  }

  webvtt_copy_stringlist( &node_data->css_classes, css_classes );
  webvtt_copy_string( &node_data->annotation, annotation );
  webvtt_init_node_list( &node_data->node_list );

  (*node)->data.internal_data = node_data;

  return WEBVTT_SUCCESS;
}

WEBVTT_INTERN webvtt_status
webvtt_create_head_node( webvtt_node **node )
{
  webvtt_status status;
  webvtt_string temp_annotation;

  webvtt_init_string( &temp_annotation );
  if( WEBVTT_FAILED( status =
                     webvtt_create_internal_node( node, NULL, WEBVTT_HEAD_NODE,
                                                  NULL, &temp_annotation ) ) ) {
    return status;
  }

  return WEBVTT_SUCCESS;
}

WEBVTT_INTERN webvtt_status
webvtt_create_timestamp_node( webvtt_node **node, webvtt_node *parent,
                              webvtt_timestamp time_stamp )
{
  webvtt_status status;

  if( WEBVTT_FAILED( status = webvtt_create_node( node,
                                                  WEBVTT_TIME_STAMP,
                                                  parent ) ) ) {
    return status;
  }

  (*node)->data.timestamp = time_stamp;

  return WEBVTT_SUCCESS;
}

WEBVTT_INTERN webvtt_status
webvtt_create_text_node( webvtt_node **node, webvtt_node *parent,
                         webvtt_string *text )
{
  webvtt_status status;

  if( WEBVTT_FAILED( status = webvtt_create_node( node, WEBVTT_TEXT,
                                                  parent ) ) ) {
    return status;
  }

  webvtt_copy_string( &(*node)->data.text, text );

  return WEBVTT_SUCCESS;

}

WEBVTT_EXPORT void
webvtt_release_node( webvtt_node **node )
{
  webvtt_node *n;

  if( !node || !*node ) {
    return;
  }
  n = *node;

  if( webvtt_deref( &n->refs )  == 0 ) {
    if( n->kind == WEBVTT_TEXT ) {
        webvtt_release_string( &n->data.text );
    } else if( !WEBVTT_IS_LEAF( n->kind ) &&
               n->data.internal_data ) {
      webvtt_release_stringlist( &n->data.internal_data->css_classes );
      webvtt_release_string( &n->data.internal_data->annotation );
      webvtt_release_node_list( &n->data.internal_data->node_list );
      webvtt_free( n->data.internal_data );
    }
    webvtt_free( n );
  }
  *node = 0;
}

WEBVTT_INTERN webvtt_status
webvtt_attach_node( webvtt_node *parent, webvtt_node *to_attach )
{
  /**
   * Don't allow attaching to LEAF nodes!
   */
  if( !parent || !to_attach || WEBVTT_IS_LEAF(parent->kind) ) {
    return WEBVTT_INVALID_PARAM;
  }
  return webvtt_node_list_push( &parent->data.internal_data->node_list,
                                to_attach );
}
