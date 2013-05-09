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

#ifndef __WEBVTT_NODE_LIST_H__
# define __WEBVTT_NODE_LIST_H__
# include <webvtt/node.h>

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

typedef struct 
webvtt_node_list_t {
  struct webvtt_refcount_t refs;
  webvtt_uint alloc;
  webvtt_uint length;
  webvtt_node **children;
} webvtt_node_list;

WEBVTT_EXPORT void
webvtt_init_node_list( webvtt_node_list **out );

WEBVTT_EXPORT webvtt_status
webvtt_create_node_list( webvtt_node_list **out );

WEBVTT_EXPORT void
webvtt_ref_node_list( webvtt_node_list *list );

WEBVTT_EXPORT void
webvtt_release_node_list( webvtt_node_list **list );

WEBVTT_EXPORT webvtt_status
webvtt_node_list_push( webvtt_node_list *list, webvtt_node *to_attach );

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
