#include <webvttxx/nodefactory>

namespace WebVTT
{

Node *NodeFactory::createNode( webvtt_node *otherNode )
{
  if( !otherNode )
  { throw "Attemp to create Node from non-pointer."; }

  if ( WEBVTT_IS_VALID_INTERNAL_NODE( otherNode->kind ) )
  { return new InternalNode( otherNode ); }
  else if ( otherNode->kind == WEBVTT_TEXT )
  { return new TextNode( otherNode ); }
  else if ( otherNode->kind == WEBVTT_TIME_STAMP )
  { return new TimeStampNode( otherNode ); }
  return 0;
}

}