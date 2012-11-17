#ifndef __CUE_H__
#	define __CUE_H__
#	include <webvtt/string.h>

/**
 * Routines for creating nodes.
 */
WEBVTT_INTERN webvtt_status webvtt_create_node( webvtt_node_ptr *node_pptr, void *concrete_node, webvtt_node_kind kind, webvtt_node_ptr parent_ptr );
WEBVTT_INTERN webvtt_status webvtt_create_internal_node( webvtt_node_ptr *node_pptr, webvtt_node_ptr parent_ptr, webvtt_node_kind kind, webvtt_string_list_ptr css_classes_ptr, webvtt_string annotation );
WEBVTT_INTERN webvtt_status webvtt_create_head_node( webvtt_node_ptr *node_pptr );
WEBVTT_INTERN webvtt_status webvtt_create_time_stamp_leaf_node( webvtt_node_ptr *node_pptr, webvtt_node_ptr parent_ptr, webvtt_timestamp time_stamp );
WEBVTT_INTERN webvtt_status webvtt_create_text_leaf_node( webvtt_node_ptr *node_pptr, webvtt_node_ptr parent_ptr, webvtt_string text );

/**
 * Attaches a node to the internal node list of another node.
 */
WEBVTT_INTERN webvtt_status webvtt_attach_internal_node( webvtt_internal_node_ptr current, webvtt_node_ptr to_attach );

/**
 * Routines for deleting nodes.
 */
WEBVTT_INTERN void webvtt_delete_node( webvtt_node_ptr node_ptr );
WEBVTT_INTERN void webvtt_delete_leaf_node( webvtt_leaf_node_ptr leaf_node_prt );

/**
 * Deletes an internal node as well as it's child nodes. 
 */
WEBVTT_INTERN void webvtt_delete_internal_node( webvtt_internal_node_ptr internal_node_ptr );

#endif