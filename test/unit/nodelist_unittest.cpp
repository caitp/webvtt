#include <gtest/gtest.h>
#include "webvttxx/node_list"
extern "C" {
#include "libwebvtt/node_internal.h"
}

// Test Fixture for the NodeList C api
class NodeListC : public ::testing::Test
{
public:
  void SetUp()
  {
    webvtt_init_node_list( &list );
    ASSERT_EQ(WEBVTT_SUCCESS,webvtt_create_head_node( &a ));
    ASSERT_EQ(WEBVTT_SUCCESS,webvtt_create_head_node( &b ));
    ASSERT_EQ(WEBVTT_SUCCESS,webvtt_create_head_node( &c ));
    a->kind=static_cast<webvtt_node_kind>(1);
    b->kind=static_cast<webvtt_node_kind>(2);
    c->kind=static_cast<webvtt_node_kind>(3);
    ASSERT_FALSE(WEBVTT_FAILED(webvtt_node_list_push(&list,a)));
  }

  void TearDown()
  {
    c->kind=WEBVTT_HEAD_NODE;
    b->kind=WEBVTT_HEAD_NODE;
    a->kind=WEBVTT_HEAD_NODE;
    webvtt_release_node( &c );
    webvtt_release_node( &b );
    webvtt_release_node( &a );
    webvtt_release_node_list( &list );
  }

  int size() const { return list.d->size; }
  webvtt_status push(const webvtt_node *n) {
    int c=size();
    webvtt_status ret=webvtt_node_list_push( &list, n );
    EXPECT_EQ(c+1,size());
    return ret;
  }

  webvtt_bool pop(webvtt_node **n) {
    int c=size();
    webvtt_bool ret=webvtt_node_list_pop( &list, n );
    EXPECT_EQ(c-1, size());
    return ret;
  }

  webvtt_bool top(webvtt_node **n) const {
    int c=size();
    webvtt_bool ret=webvtt_node_list_top( &list, n );
    EXPECT_EQ(c,size());
    return ret;
  }

  webvtt_status unshift(const webvtt_node *n) {
    int c=size();
    webvtt_status ret=webvtt_node_list_unshift( &list, n );
    EXPECT_EQ(c+1,size());
    return ret;
  }

  webvtt_bool shift(webvtt_node **n) {
    int c=size();
    webvtt_bool ret=webvtt_node_list_shift( &list, n );
    EXPECT_EQ(c-1,size());
    return ret;
  }
  webvtt_bool front(webvtt_node **n) const {
    int c=size();
    webvtt_bool ret=webvtt_node_list_front( &list, n );
    EXPECT_EQ(c, size());
    return ret;
  }

  int kindAt( int idx ) {
    if( idx < list.d->size ) {
      return static_cast<int>(list.d->array[ idx ]->kind);
    }
    return -1;
  }

protected:
  ::webvtt_node *a;
  ::webvtt_node *b;
  ::webvtt_node *c;

private:
  webvtt_node_list list;
};

class NodeListCXX : public ::testing::Test
{
public:
  int size() const { return list.size(); }
  bool push(const WebVTT::Node &n) { return list.push(n); }
  bool pop(WebVTT::Node &n) { return list.pop(n); }
  bool top(WebVTT::Node &n) const { return list.top(n); }
  bool unshift(const WebVTT::Node &n) { return list.unshift(n); }
  bool shift(WebVTT::Node &n) { return list.shift(n); }
  bool front(WebVTT::Node &n) const { return list.front(n); }
private:
  WebVTT::NodeList list;
};

TEST_F(NodeListC,Push)
{
  EXPECT_FALSE( WEBVTT_FAILED( push( b ) ) );
  EXPECT_EQ( 2, a->refs.value );
  EXPECT_EQ( 2, b->refs.value );
  EXPECT_EQ( 1, kindAt(0) );
  EXPECT_EQ( 2, kindAt(1) );
}

TEST_F(NodeListC,Pop)
{
  ::webvtt_node *n = 0;
  EXPECT_FALSE( WEBVTT_FAILED( push( b ) ) );
  EXPECT_TRUE( pop( &n ) );
  EXPECT_EQ( 2, n->refs.value );
  EXPECT_EQ( n, b );
  webvtt_release_node( &n );
}

TEST_F(NodeListC,Top)
{
  ::webvtt_node *n = 0;
  EXPECT_TRUE( top( &n ) );
  EXPECT_EQ( 3, n->refs.value );
  EXPECT_EQ( n, a );
  ::webvtt_release_node( &n );
}

TEST_F(NodeListC,Unshift)
{
  EXPECT_FALSE( WEBVTT_FAILED( unshift( b ) ) );
  EXPECT_EQ( 2, a->refs.value );
  EXPECT_EQ( 2, b->refs.value );
  EXPECT_EQ( 2, kindAt(0) );
  EXPECT_EQ( 1, kindAt(1) );
}

TEST_F(NodeListC,Shift)
{
  ::webvtt_node *n = 0;
  EXPECT_FALSE( WEBVTT_FAILED( push( b ) ) );
  EXPECT_TRUE( shift( &n ) );
  EXPECT_EQ( 2, n->refs.value );
  EXPECT_EQ( n, a );
  webvtt_release_node( &n );
}

TEST_F(NodeListC,Front)
{
  ::webvtt_node *n = 0;
  EXPECT_TRUE( front( &n ) );
  EXPECT_EQ( 3, n->refs.value );
  EXPECT_EQ( n, a );
  ::webvtt_release_node( &n );
}

