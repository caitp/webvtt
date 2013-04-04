#include <gtest/gtest.h>
#include <string>
extern "C" {
#include "libwebvtt/parser_internal.h"
}

class ParseCuesetting : public ::testing::Test
{
public:
  ParseCuesetting() : self(0), cue(0) {}
  virtual void SetUp() {
    ASSERT_FALSE( WEBVTT_FAILED( webvtt_create_parser( &dummyread, &dummyerr,
                                                       0, &self ) ) )
      << "Failed to create parser";
    ASSERT_FALSE( WEBVTT_FAILED( webvtt_create_cue( &cue ) ) )
      << "Failed to allocate cue";
  }

  virtual void TearDown() {
    webvtt_release_cue( &cue );
    webvtt_delete_parser( self );
    self = 0;
  }

  webvtt_status parseAlign( const std::string &str, webvtt_uint &pos ) {
    return ::webvtt_parse_align( self, cue,
                                 reinterpret_cast<const webvtt_byte *>(
                                 str.c_str() ), &pos, str.size() );
  }

  webvtt_status parseLine( const std::string &str, webvtt_uint &pos ) {
    return ::webvtt_parse_line( self, cue,
                                reinterpret_cast<const webvtt_byte *>(
                                str.c_str() ), &pos, str.size() );
  }


  webvtt_align_type align() const { return cue->settings.align; }
  int line() const { return cue->settings.line; }
  bool snapToLines() const { return cue->snap_to_lines; }
private:
  static int WEBVTT_CALLBACK dummyerr( void *userdata, webvtt_uint
                                       line, webvtt_uint col,
                                       webvtt_error error ) {
    return 0;
  }
  static void WEBVTT_CALLBACK dummyread( void *userdata, webvtt_cue *cue ) {}
  webvtt_parser self;
  webvtt_cue *cue;
};

class ParseAlign : public ParseCuesetting {};
class ParseLine : public ParseCuesetting {};

/**
 * Align cuesetting parser tests
 */

TEST_F(ParseAlign,Start)
{
  webvtt_uint pos = 0;
  EXPECT_EQ( WEBVTT_SUCCESS, parseAlign( "align:start", pos ) );
  EXPECT_EQ( 11, pos );
  EXPECT_EQ( WEBVTT_ALIGN_START, align() );
}

TEST_F(ParseAlign,Middle)
{
  webvtt_uint pos = 0;
  EXPECT_EQ( WEBVTT_SUCCESS, parseAlign( "align:middle", pos ) );
  EXPECT_EQ( 12, pos );
  EXPECT_EQ( WEBVTT_ALIGN_MIDDLE, align() );
}

TEST_F(ParseAlign,End)
{
  webvtt_uint pos = 0;
  EXPECT_EQ( WEBVTT_SUCCESS, parseAlign( "align:end", pos ) );
  EXPECT_EQ( 9, pos );
  EXPECT_EQ( WEBVTT_ALIGN_END, align() );
}

TEST_F(ParseAlign,Left)
{
  webvtt_uint pos = 0;
  EXPECT_EQ( WEBVTT_SUCCESS, parseAlign( "align:left", pos ) );
  EXPECT_EQ( 10, pos );
  EXPECT_EQ( WEBVTT_ALIGN_LEFT, align() );
}

TEST_F(ParseAlign,Right)
{
  webvtt_uint pos = 0;
  EXPECT_EQ( WEBVTT_SUCCESS, parseAlign( "align:right", pos ) );
  EXPECT_EQ( 11, pos );
  EXPECT_EQ( WEBVTT_ALIGN_RIGHT, align() );
}

TEST_F(ParseAlign,BadKeyword)
{
  webvtt_uint pos = 0;
  EXPECT_EQ( WEBVTT_PARSE_ERROR, parseAlign( "foo:left", pos ) );
  EXPECT_EQ( 8, pos );
}

TEST_F(ParseAlign,BadValue)
{
  webvtt_uint pos = 0;
  EXPECT_EQ( WEBVTT_PARSE_ERROR, parseAlign( "align:lfet", pos ) );
  EXPECT_EQ( 10, pos );
}

TEST_F(ParseAlign,BadValueAfter)
{
  webvtt_uint pos = 0;
  EXPECT_EQ( WEBVTT_PARSE_ERROR, parseAlign( "align:leftt", pos ) );
  EXPECT_EQ( 11, pos );
}

TEST_F(ParseAlign,LFAfter)
{
  webvtt_uint pos = 0;
  EXPECT_EQ( WEBVTT_SUCCESS, parseAlign( "align:left\n", pos ) );
  EXPECT_EQ( 10, pos );
}

TEST_F(ParseAlign,CRAfter)
{
  webvtt_uint pos = 0;
  EXPECT_EQ( WEBVTT_SUCCESS, parseAlign( "align:left\r", pos ) );
  EXPECT_EQ( 10, pos );
}

TEST_F(ParseAlign,SpaceAfter)
{
  webvtt_uint pos = 0;
  EXPECT_EQ( WEBVTT_SUCCESS, parseAlign( "align:left ", pos ) );
  EXPECT_EQ( 10, pos );
}

TEST_F(ParseAlign,TabAfter)
{
  webvtt_uint pos = 0;
  EXPECT_EQ( WEBVTT_SUCCESS, parseAlign( "align:left\t", pos ) );
  EXPECT_EQ( 10, pos );
}

/**
 * Line cuesetting parser tests
 */
TEST_F(ParseLine,NegativeLine)
{
  webvtt_uint pos = 0;
  EXPECT_EQ( WEBVTT_SUCCESS, parseLine( "line:-50", pos ) );
  EXPECT_EQ( 8, pos );
  EXPECT_EQ( -50, line() );
  EXPECT_TRUE( snapToLines() );
}

TEST_F(ParseLine,PositiveLine)
{
  webvtt_uint pos = 0;
  EXPECT_EQ( WEBVTT_SUCCESS, parseLine( "line:50", pos ) );
  EXPECT_EQ( 7, pos );
  EXPECT_EQ( 50, line() );
  EXPECT_TRUE( snapToLines() );
}

TEST_F(ParseLine,PositiveSnap)
{
  webvtt_uint pos = 0;
  EXPECT_EQ( WEBVTT_SUCCESS, parseLine( "line:50%", pos ) );
  EXPECT_EQ( 8, pos );
  EXPECT_EQ( 50, line() );
  EXPECT_FALSE( snapToLines() );
}

TEST_F(ParseLine,NegativeSnap)
{
  webvtt_uint pos = 0;
  EXPECT_EQ( WEBVTT_PARSE_ERROR, parseLine( "line:-50%", pos ) );
  EXPECT_EQ( 9, pos );
}

TEST_F(ParseLine,OverflowSnap)
{
  webvtt_uint pos = 0;
  EXPECT_EQ( WEBVTT_PARSE_ERROR, parseLine( "line:150%", pos ) );
  EXPECT_EQ( 9, pos );
}

TEST_F(ParseLine,BadValue)
{
  webvtt_uint pos = 0;
  EXPECT_EQ( WEBVTT_PARSE_ERROR, parseLine( "line:5f%", pos ) );
  EXPECT_EQ( 8, pos );
}

TEST_F(ParseLine,BadValueAfter)
{
  webvtt_uint pos = 0;
  EXPECT_EQ( WEBVTT_PARSE_ERROR, parseLine( "line:50f", pos ) );
  EXPECT_EQ( 8, pos );
}

TEST_F(ParseLine,LFAfter)
{
  webvtt_uint pos = 0;
  EXPECT_EQ( WEBVTT_SUCCESS, parseLine( "line:100\n", pos ) );
  EXPECT_EQ( 8, pos );
}

TEST_F(ParseLine,CRAfter)
{
  webvtt_uint pos = 0;
  EXPECT_EQ( WEBVTT_SUCCESS, parseLine( "line:100\r", pos ) );
  EXPECT_EQ( 8, pos );
}

TEST_F(ParseLine,SpaceAfter)
{
  webvtt_uint pos = 0;
  EXPECT_EQ( WEBVTT_SUCCESS, parseLine( "line:100 ", pos ) );
  EXPECT_EQ( 8, pos );
}

TEST_F(ParseLine,TabAfter)
{
  webvtt_uint pos = 0;
  EXPECT_EQ( WEBVTT_SUCCESS, parseLine( "line:100\t", pos ) );
  EXPECT_EQ( 8, pos );
}


