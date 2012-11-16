#ifndef __WEBVTT_CUE_H__
#	define __WEBVTT_CUE_H__
#	include "util.h"
#	include "string.h"

typedef struct webvtt_cue_t *webvtt_cue;
typedef double webvtt_timestamp_t, webvtt_timestamp;
typedef struct webvtt_cue_settings_t webvtt_cue_settings;
typedef struct webvtt_node_t webvtt_node, *webvtt_node_ptr;
typedef struct webvtt_leaf_node_t webvtt_leaf_node, *webvtt_leaf_node_ptr;
typedef struct webvtt_internal_node_t webvtt_internal_node, *webvtt_internal_node_ptr;
typedef enum webvtt_node_kind_t webvtt_node_kind;
typedef enum webvtt_vertical_type webvtt_vertical_type;
typedef enum webvtt_align_type webvtt_align_type;

#define WEBVTT_AUTO (0xFFFFFFFF)
	
enum
webvtt_node_kind_t
{
	WEBVTT_NODE_LEAF = 0x80000000,
	WEBVTT_NODE_INTERNAL = 0x00000000,
	
	/**
	 * Internal Node objects
	 */
	WEBVTT_NODE_INTERNAL_START = 0,
	WEBVTT_CLASS = 0 | WEBVTT_NODE_INTERNAL,
	WEBVTT_ITALIC = 1 | WEBVTT_NODE_INTERNAL,
	WEBVTT_BOLD = 2 | WEBVTT_NODE_INTERNAL,
	WEBVTT_UNDERLINE = 3 | WEBVTT_NODE_INTERNAL,
	WEBVTT_RUBY = 4 | WEBVTT_NODE_INTERNAL,
	WEBVTT_RUBY_TEXT = 5 | WEBVTT_NODE_INTERNAL,
	WEBVTT_VOICE = 6 | WEBVTT_NODE_INTERNAL,

	/**
	 * This type of node has should not be rendered.
	 * It is the top of the node list and only contains a list of nodes.
	 */
	WEBVTT_HEAD_NODE = 7,

	WEBVTT_NODE_INTERNAL_END = 7,

	/**
	 * Leaf Node objects
	 */
	WEBVTT_NODE_LEAF_START = 256,
	WEBVTT_TEXT = 256 | WEBVTT_NODE_LEAF,
	WEBVTT_TIME_STAMP = 257 | WEBVTT_NODE_LEAF,

	WEBVTT_NODE_LEAF_END = 257
};

/**
 * Macros to assist in validating node kinds, so that C++ compilers don't complain (as long as they provide reinterpret_cast, which they should)
 */
#if defined(__cplusplus) || defined(__cplusplus_cli) || defined(__embedded_cplusplus) || defined(c_plusplus) 
#	define WEBVTT_CAST(Type,Val) (reinterpret_cast<Type>(Val))
#else
#	define WEBVTT_CAST(Type,Val) ((Type)(Val))
#endif

#define WEBVTT_IS_LEAF(Kind) ( (Kind) & WEBVTT_NODE_LEAF != 0 )
#define WEBVTT_NODE_INDEX(Kind) ( (Kind) & ~WEBVTT_NODE_LEAF )
#define WEBVTT_IS_VALID_LEAF_NODE(Kind) ( WEBVTT_IS_LEAF(Kind) && (WEBVTT_NODE_INDEX(Kind) >= WEBVTT_NODE_LEAF_START && WEBVTT_NODE_INDEX(Kind) <= WEBVTT_NODE_LEAF_END ) )
#define WEBVTT_IS_VALID_INTERNAL_NODE(Kind) ( (!WEBVTT_IS_LEAF(Kind)) && (WEBVTT_NODE_INDEX(Kind) >= WEBVTT_NODE_INTERNAL_START && WEBVTT_NODE_INDEX(Kind) <= WEBVTT_NODE_INTERNAL_END) )
#define WEBVTT_IS_VALID_NODE_KIND(Kind) ( WEBVTT_IS_VALID_INTERNAL_NODE(Kind) || WEBVTT_IS_VALID_LEAF_NODE(Kind) )

/**
 * Casting helpers
 */
#define WEBVTT_GET_INTERNAL_NODE(Node) ( WEBVTT_IS_VALID_INTERNAL_NODE(WEBVTT_CAST(webvtt_node,Node)->kind) ? WEBVTT_CAST(webvtt_internal_node,Node) : 0 )
#define WEBVTT_GET_LEAF_NODE(Node) ( WEBVTT_IS_VALID_LEAF_NODE((WEBVTT_CAST(webvtt_node,Node))->kind) ? WEBVTT_CAST(webvtt_leaf_node,Node) : 0 )

struct
webvtt_node_t
{
	/**
	 * The specification asks for uni directional linked list, but we have added a parent 
	 * node in order to facilitate an iterative cue text parsing solution.
	 */
	webvtt_node *parent;

	webvtt_node_kind kind;
	void *concrete_node;
};

struct
webvtt_internal_node_t
{
	webvtt_string annotation;
	webvtt_string_list_ptr css_classes_ptr;

	webvtt_uint alloc;
	webvtt_uint child_node_count;
	webvtt_node_ptr *children;
};

struct
webvtt_leaf_node_t
{
	/**
	 * Can contain text or a time stamp based on what type of leaf node it is.
	 */
	union {
		webvtt_string text;
		webvtt_timestamp time_stamp;
	};
};

enum webvtt_vertical_type
{
	WEBVTT_HORIZONTAL = 0,
	WEBVTT_VERTICAL_LR = 1,
	WEBVTT_VERTICAL_RL = 2
};

enum webvtt_align_type
{
	WEBVTT_ALIGN_START = 0,
	WEBVTT_ALIGN_MIDDLE,
	WEBVTT_ALIGN_END
};

struct
webvtt_cue_settings_t
{
	webvtt_vertical_type vertical;
	webvtt_bool line_is_relative;
	union
	{
		webvtt_int no; /* line.no */
		webvtt_uint relative_position; /* line.relative_position */
	} line;
	webvtt_uint position;
	webvtt_uint size;
	webvtt_align_type align;
};

struct
webvtt_cue_t
{
	webvtt_timestamp_t from;
	webvtt_timestamp_t until;
	webvtt_cue_settings settings;
	webvtt_bool snap_to_lines;
	webvtt_string id;

	/**
	 * Unparsed cue-text
	 */
	webvtt_string payload;

	/**
	 * Parsed cue-text (NULL if has not been parsed)
	 */
	webvtt_node_ptr node_head;
};

WEBVTT_EXPORT webvtt_status webvtt_create_cue( webvtt_cue *pcue );
WEBVTT_EXPORT void webvtt_delete_cue( webvtt_cue *pcue );
WEBVTT_EXPORT int webvtt_validate_cue( webvtt_cue cue );

#endif