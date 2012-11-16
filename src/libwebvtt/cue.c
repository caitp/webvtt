#include <stdlib.h>
#include <webvtt/cue.h>
#include "cue.h"

WEBVTT_EXPORT webvtt_status
webvtt_create_cue( webvtt_cue *pcue )
{
	webvtt_cue cue;
	if( !pcue )
	{
		return WEBVTT_INVALID_PARAM;
	}
	cue = (webvtt_cue)webvtt_alloc0( sizeof(*cue) );
	if( !cue )
	{
		return WEBVTT_OUT_OF_MEMORY;
	}
	/**
	 * From http://dev.w3.org/html5/webvtt/#parsing (10/25/2012)
	 *
	 * Let cue's text track cue snap-to-lines flag be true.
	 *
	 * Let cue's text track cue line position be auto.
	 *
	 * Let cue's text track cue text position be 50.
	 *
	 * Let cue's text track cue size be 100.
	 *
	 * Let cue's text track cue alignment be middle alignment.
	 */
	cue->snap_to_lines = 1;
	cue->settings.position = 50;
	cue->settings.size = 100;
	cue->settings.align = WEBVTT_ALIGN_MIDDLE;
	cue->settings.line.no = WEBVTT_AUTO;
	cue->settings.vertical = WEBVTT_HORIZONTAL;

	*pcue = cue;
	return WEBVTT_SUCCESS;
}

WEBVTT_EXPORT void
webvtt_delete_cue( webvtt_cue *pcue )
{
	if( pcue && *pcue )
	{
		webvtt_cue cue = *pcue;
		*pcue = 0;
		webvtt_delete_string( cue->id );
		webvtt_delete_string( cue->payload );
		webvtt_free( cue );
		webvtt_delete_node( cue->node_head );
	}
}

WEBVTT_EXPORT int
webvtt_validate_cue( webvtt_cue cue )
{
	if( cue )
	{
		/**
		 * validate cue-times (Can't do checks against previously parsed cuetimes. That's the applications responsibility
		 */
		if( cue->until <= cue->from )
		{
			goto error;
		}

		/**
		 * Don't do any payload validation, because this would involve parsing the payload, which is optional.
		 */
		return 1;
	}

error:
	return 0;
}

WEBVTT_INTERN webvtt_status  
webvtt_create_node( webvtt_node_ptr *node_pptr, void *concrete_node, webvtt_node_kind kind, webvtt_node_ptr parent_ptr )
{
	webvtt_node_ptr temp_node_ptr = (webvtt_node_ptr)malloc(sizeof(*temp_node_ptr));

	if( !temp_node_ptr )
		return WEBVTT_OUT_OF_MEMORY;

	temp_node_ptr->concrete_node = concrete_node;
	temp_node_ptr->kind = kind;
	temp_node_ptr->parent = parent_ptr;
	*node_pptr = temp_node_ptr;
		
	return WEBVTT_SUCCESS;
}

WEBVTT_INTERN webvtt_status  
webvtt_create_internal_node( webvtt_node_ptr *node_pptr, webvtt_node_ptr parent_ptr, webvtt_node_kind kind, webvtt_string_list_ptr css_classes_ptr, webvtt_string annotation )
{
	webvtt_internal_node_ptr internal_node_ptr = (webvtt_internal_node_ptr)malloc(sizeof(*internal_node_ptr));

	if( !internal_node_ptr )
		return WEBVTT_OUT_OF_MEMORY;

	internal_node_ptr->css_classes_ptr = css_classes_ptr;
	internal_node_ptr->annotation = annotation;
	internal_node_ptr->children = NULL;
	internal_node_ptr->child_node_count = 0;
	internal_node_ptr->alloc = 0;

	return webvtt_create_node( node_pptr, (void *)internal_node_ptr, kind, parent_ptr );
}

WEBVTT_INTERN webvtt_status 
webvtt_create_head_node( webvtt_node_ptr *node_pptr )
{
	webvtt_internal_node_ptr internal_node_ptr = (webvtt_internal_node_ptr)malloc(sizeof(*internal_node_ptr));

	if ( !internal_node_ptr )
		return WEBVTT_OUT_OF_MEMORY;

	internal_node_ptr->annotation = NULL;
	internal_node_ptr->children = NULL;
	internal_node_ptr->child_node_count = 0;
	internal_node_ptr->alloc = 0;

	return webvtt_create_node( node_pptr, (void *)internal_node_ptr, WEBVTT_HEAD_NODE, NULL );	
}

WEBVTT_INTERN webvtt_status  
webvtt_create_time_stamp_leaf_node( webvtt_node_ptr *node_pptr, webvtt_node_ptr parent_ptr, webvtt_timestamp time_stamp )
{
	webvtt_leaf_node_ptr leaf_node_ptr = (webvtt_leaf_node_ptr)malloc(sizeof(*leaf_node_ptr));

	if( !leaf_node_ptr )
		return WEBVTT_OUT_OF_MEMORY;

	leaf_node_ptr->time_stamp = time_stamp;

	return webvtt_create_node( node_pptr, (void *)leaf_node_ptr, WEBVTT_TIME_STAMP, parent_ptr );		
}

WEBVTT_INTERN webvtt_status  
webvtt_create_text_leaf_node( webvtt_node_ptr *node_pptr, webvtt_node_ptr parent_ptr, webvtt_string text )
{
	webvtt_leaf_node_ptr leaf_node_ptr = (webvtt_leaf_node_ptr)malloc(sizeof(*leaf_node_ptr));

	if( leaf_node_ptr )
		return WEBVTT_OUT_OF_MEMORY;

	leaf_node_ptr->text = text;
	webvtt_create_node( node_pptr, (void *)leaf_node_ptr, WEBVTT_TEXT, parent_ptr );

	return WEBVTT_SUCCESS;

}

WEBVTT_INTERN void 
webvtt_delete_node( webvtt_node_ptr node_ptr )
{
	if( node_ptr )
	{
		if( WEBVTT_IS_VALID_LEAF_NODE( node_ptr->kind ) )
		{
			webvtt_delete_leaf_node( (webvtt_leaf_node_ptr)node_ptr->concrete_node );
		}
		else if( WEBVTT_IS_VALID_INTERNAL_NODE( node_ptr->kind ) )
		{
			webvtt_delete_internal_node( (webvtt_internal_node_ptr)node_ptr->concrete_node );
		}
		free( node_ptr );
	}
}

WEBVTT_INTERN void 
webvtt_delete_internal_node( webvtt_internal_node_ptr internal_node_ptr )
{
	webvtt_uint i ;

	if( internal_node_ptr )
	{
		webvtt_delete_string_list( internal_node_ptr->css_classes_ptr );

		if( internal_node_ptr->annotation )
			webvtt_delete_string( internal_node_ptr->annotation );

		for( i = 0; i < internal_node_ptr->child_node_count; i++ )
			webvtt_delete_node( *(internal_node_ptr->children + i) );
		free( internal_node_ptr );
	}
}

WEBVTT_INTERN void 
webvtt_delete_leaf_node( webvtt_leaf_node_ptr leaf_node_ptr )
{
	if( leaf_node_ptr )
	{
		if( leaf_node_ptr->text )
			webvtt_delete_string( leaf_node_ptr->text );
		free( leaf_node_ptr );
	}
}

WEBVTT_INTERN webvtt_status 
webvtt_attach_internal_node( webvtt_internal_node_ptr current_ptr, webvtt_node_ptr to_attach_ptr )
{
	if( !current_ptr || !to_attach_ptr )
	{
		return WEBVTT_INVALID_PARAM;
	}

	if( current_ptr->alloc == current_ptr->child_node_count )
	{
		current_ptr->alloc += 4;
		current_ptr->children = (webvtt_node_ptr *)realloc(current_ptr->children, sizeof(webvtt_node_ptr *) * (current_ptr->alloc));
		
		if( !current_ptr->children )
			return WEBVTT_OUT_OF_MEMORY;
	}

	current_ptr->children[current_ptr->child_node_count++] = to_attach_ptr;

	return WEBVTT_SUCCESS;
}