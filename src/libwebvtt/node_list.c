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

static webvtt_node_list_data empty = {
  { 1 }, /* ref count */
  0, /* alloc */
  0, /* size */
  { 0 },
};

WEBVTT_EXPORT void
webvtt_init_node_list( webvtt_node_list *out ) {
  if( out ) {
    /**
     * Assume that out list doesn't point to a valid
     * list. Don't attempt to dereference it.
     */
    out->d = &empty;
    webvtt_ref_node_list( out );
  }
}

WEBVTT_EXPORT void
webvtt_ref_node_list( webvtt_node_list *list )
{
  if( list ) {
    webvtt_ref( &list->d->refs );
  }
}

static void
webvtt_node_list_cleanup( webvtt_node_list_data *d )
{
  if( webvtt_deref( &d->refs ) == 0 ) {
    int i;
    for( i=0; i<d->size; ++i ) {
      webvtt_release_node( &d->array[i] );
    }
    webvtt_free( d );
  }
}

WEBVTT_EXPORT void
webvtt_release_node_list( webvtt_node_list *list )
{
  if( !list || !list->d ) {
    return;
  }
  webvtt_node_list_cleanup( list->d );
  list->d = 0;
}

WEBVTT_EXPORT void
webvtt_copy_node_list( webvtt_node_list *dest, const webvtt_node_list *src )
{
  if( dest && src ) {
    dest->d = src->d;
    webvtt_ref_node_list( dest );
  }
}

static int
webvtt_node_list_grow( int nodes )
{
  static const int page = 0x1000;
  int grow = sizeof(webvtt_node_list_data)
           + sizeof(webvtt_node *) * nodes;
  int n;
  if( grow < page ) {
    n = page;
    do {
      n = n / 2;
    } while( n > grow );
    if( n < 1 << 6 ) {
      n = 1 << 6;
    } else {
      n = n * 2;
    }
  } else {
    n = page;
    do {
      n = n * 2;
    } while ( n < grow );
  }

  return n;
}

static webvtt_status
webvtt_node_list_detach( webvtt_node_list *list, int grow )
{
  /**
   * detach() is internal
   * Parameters are expected to be correct and are not checked
   */
  if( list->d->refs.value != 1
      || ( list->d->size + grow ) <= list->d->alloc ) {
    int i;
    int size = webvtt_node_list_grow( list->d->size + grow );
    int alloc = ( size - sizeof(webvtt_node_list_data) )
              / sizeof(webvtt_node *);
    webvtt_node_list_data *x = webvtt_alloc0( size );
    webvtt_node_list_data *p;
    if( !x ) {
      /**
       * Failed to allocate memory for whatever reason
       */
      return WEBVTT_OUT_OF_MEMORY;
    }

    /* Reset reference count to '1' */
    webvtt_ref( &x->refs );
    x->alloc = alloc;
    x->size = list->d->size;
    for( i=0; i<list->d->size; ++i ) {
      /**
       * Copy existing nodes over
       */
      x->array[i] = list->d->array[i];
      webvtt_ref_node( x->array[i] );
    }
    p = list->d;
    list->d = x;
    /**
     * deref and cleanup old list
     */
    webvtt_node_list_cleanup( p );
  }
  return WEBVTT_SUCCESS;
}

WEBVTT_EXPORT webvtt_status
webvtt_node_list_push( webvtt_node_list *list, const webvtt_node *node )
{
  webvtt_status s;
  if( !list || !node ) {
    return WEBVTT_INVALID_PARAM;
  }

  if( WEBVTT_FAILED( s = webvtt_node_list_detach( list, 1 ) ) ) {
    return s;
  }

  list->d->array[list->d->size++] = (webvtt_node *)node;
  webvtt_ref_node( (webvtt_node *)node );

  return WEBVTT_SUCCESS;
}

WEBVTT_EXPORT webvtt_bool
webvtt_node_list_pop( webvtt_node_list *list, webvtt_node **out )
{
  webvtt_node *last;
  if( !list || !list->d || !list->d->size ) {
    return 0; /* Can't pop */
  }

  /* Detach shared list */
  if( WEBVTT_FAILED( webvtt_node_list_detach( list, 0 ) ) ) {
    return 0;
  }

  last = list->d->array[--list->d->size];
  list->d->array[list->d->size] = 0;
  if( out ) {
    /**
     * Warning: This is potentially unsafe, in a multi-threaded
     * environment. Client applications should perform their own
     * locking, if needed.
     */
    webvtt_copy_node( out, last );
  }
  webvtt_release_node( &last );
  return 1;
}

/**
 * Perform same actions as pop(), but do not release the node
 * and change the 'size'
 */
WEBVTT_EXPORT webvtt_bool
webvtt_node_list_top( const webvtt_node_list *list, webvtt_node **out )
{
  if( !list || !out || !list->d || !list->d->size ) {
    return 0; /* Can't get top/back of list */
  }
  webvtt_copy_node( out, list->d->array[list->d->size - 1] );
  return 1;
}

/**
 * Less efficient than an append/push!
 * Prepend a node to the list
 */
WEBVTT_EXPORT webvtt_status
webvtt_node_list_unshift( webvtt_node_list *list, const webvtt_node *node )
{
  webvtt_status s;
  int i;

  if( !list || !node ) {
    return WEBVTT_INVALID_PARAM;
  }

  /* Detach shared list */
  if( WEBVTT_FAILED( s = webvtt_node_list_detach( list, 1 ) ) ) {
    return s;
  }

  /**
   * Move each list node forward by 1 index
   */
  for( i=list->d->size++; i>0; --i ) {
    list->d->array[i] = list->d->array[i-1];
  }
  list->d->array[0] = (webvtt_node *)node;
  webvtt_ref_node( (webvtt_node *)node );
  return WEBVTT_SUCCESS;
}

/**
 * Less efficient than pop!
 * Remove node from front of list, and return it
 * in 'out'
 */
WEBVTT_EXPORT webvtt_bool
webvtt_node_list_shift( webvtt_node_list *list, webvtt_node **out )
{
  int i;

  if( !list ) {
    return 0;
  }

  /* Detach shared list */
  if( WEBVTT_FAILED( webvtt_node_list_detach( list, 0 ) ) ) {
    return 0;
  }

  /* Copy first node, if we're asked to */
  if( out ) {
    webvtt_copy_node( out, list->d->array[0] );
  }

  webvtt_release_node( &list->d->array[0] );

  /**
   * Move each list node backward by 1 index
   */
  for( i=1; i<list->d->size; ++i ) {
    list->d->array[i-1] = list->d->array[i];
  }
  list->d->array[--list->d->size] = 0;
  return 1;
}

/**
 * Get the front/head of the list, return non-zero if successful
 */
WEBVTT_EXPORT webvtt_bool
webvtt_node_list_front( const webvtt_node_list *list, webvtt_node **out )
{
  if( !list || !out || !list->d->size ) {
    return 0;
  }
  webvtt_copy_node( out, list->d->array[list->d->size - 1] );
  return 1;
}

