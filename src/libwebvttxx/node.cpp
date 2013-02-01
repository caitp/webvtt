#include <webvttxx/node>
#include <webvttxx/nodefactory>

namespace WebVTT
{

InternalNode::InternalNode( webvtt_node *otherNode )
  : Node( otherNode ) 
{
  Node *temp_node;
  for( uint i = 0; i < otherNode->data.internal_data->length; i++ )
  {
    temp_node = NodeFactory::createNode( node->data.internal_data->children[i] );
    children.push_back( temp_node );
  }
}

const Node *Node::parent() const
{
  return parentNode;
}

const Node *InternalNode::child( uint index ) const
{
  if( index <= node->data.internal_data->length )
  { return children.at(index); }
  else
  { return 0; }
}

const InternalNode *Node::toInternalNode() const
{
  if( WEBVTT_IS_VALID_INTERNAL_NODE( this->kind() ) )
  { return ( const InternalNode * )this; }
  else
  { throw "Invalid cast to InternalNode."; }
}

const TextNode *Node::toTextNode() const
{
  if( this->kind() == Node::Text )
  { return ( const TextNode * )this; }
  else
  { throw "Invalid cast to TextNode."; }
}

const TimeStampNode *Node::toTimeStampNode() const
{
  if( this->kind() == Node::TimeStamp )
  { return ( const TimeStampNode * )this; }
  else
  { throw "Invalid cast to TimeStampNode."; }
}

}