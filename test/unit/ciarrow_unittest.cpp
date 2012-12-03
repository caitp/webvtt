#include "cue_testfixture"
class CueIdArrow : public CueTest { };

/**
 * Test to determine if random arrows other than "-->" do not fail during parsing
 * 
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-identifier (11/24/2012)
 * A WebVTT cue identifier is any sequence of one or more characters not containing the substring "-->" 
 * (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN), nor containing any U+000A LINE FEED (LF) 
 * characters or U+000D CARRIAGE RETURN (CR) characters.
 * 
 * Note: A WebVTT cue identifier can be used to reference a specific cue, for example from script or CSS.
 */
TEST_F(CueIdArrow,MalformedArrows)
{
  loadVtt( "cue-ids/arrows/malformed_arrows.vtt" );

  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

/**
 * Test if parser fails when it encounters a cue id containing the substring "-->"
 * 
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-identifier (11/24/2012)
 * A WebVTT cue identifier is any sequence of one or more characters not containing the substring "-->" 
 * (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN), nor containing any U+000A LINE FEED (LF) 
 * characters or U+000D CARRIAGE RETURN (CR) characters.
 * 
 * Note: A WebVTT cue identifier can be used to reference a specific cue, for example from script or CSS.
 */
TEST_F(CueIdArrow,DISABLED_Arrow)//C++ exception: "std::bad_alloc"
{
  loadVtt( "cue-ids/arrows/arrow.vtt" );
  const Error& err = getError( 0 );

  ASSERT_EQ( WEBVTT_ID_TRUNCATED, err.error() );
  ASSERT_EQ( 3, err.line() );
  ASSERT_EQ( 4, err.column() );
}

/**
 * Test if parser fails when it encounters a cue id containing the substring "-->" with an extra ">"
 * 
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-identifier (11/24/2012)
 * A WebVTT cue identifier is any sequence of one or more characters not containing the substring "-->" 
 * (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN), nor containing any U+000A LINE FEED (LF) 
 * characters or U+000D CARRIAGE RETURN (CR) characters.
 * 
 * Note: A WebVTT cue identifier can be used to reference a specific cue, for example from script or CSS.
 */
TEST_F(CueIdArrow,DISABLED_ExtraArrowhead)//C++ exception: "std::bad_alloc"
{
  loadVtt( "cue-ids/arrows/extra_arrowhead.vtt" );
  const Error& err = getError( 0 );

  ASSERT_EQ( WEBVTT_ID_TRUNCATED, err.error() );
  ASSERT_EQ( 3, err.line() );
  ASSERT_EQ( 4, err.column() );
}

/**
 * Test if parser fails when it encounters a cue id containing the substring "-->" with an extra "-"
 * 
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-identifier (11/24/2012)
 * A WebVTT cue identifier is any sequence of one or more characters not containing the substring "-->" 
 * (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN), nor containing any U+000A LINE FEED (LF) 
 * characters or U+000D CARRIAGE RETURN (CR) characters.
 * 
 * Note: A WebVTT cue identifier can be used to reference a specific cue, for example from script or CSS.
 */
TEST_F(CueIdArrow,DISABLED_ExtraMinusSign)//C++ exception: "std::bad_alloc"
{
  loadVtt( "cue-ids/arrows/extra_minus_sign.vtt" );
  const Error& err = getError( 0 );

  ASSERT_EQ( WEBVTT_ID_TRUNCATED, err.error() );
  ASSERT_EQ( 3, err.line() );
  ASSERT_EQ( 5, err.column() );
}

/**
 * Test to determine if a very large WEBVTT Cue Id allows a *very* large character input. 
 * This test floods the cue ID with characters, and should fail with a --> mixed in with the random  
 * 2500+ character cue id.
 * 
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-identifier (11/24/2012)
 * A WebVTT cue identifier is any sequence of one or more characters not containing the substring "-->" 
 * (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN), nor containing any U+000A LINE FEED (LF) 
 * characters or U+000D CARRIAGE RETURN (CR) characters.
 * 
 * Note: A WebVTT cue identifier can be used to reference a specific cue, for example from script or CSS.
 */
TEST_F(CueIdArrow,DISABLED_LongStringWithArrow)//C++ exception: "std::bad_alloc"
{
  loadVtt( "cue-ids/arrows/long_string_with_arrow.vtt" );
  const Error& err = getError( 0 );

  ASSERT_EQ( WEBVTT_ID_TRUNCATED, err.error() );
  ASSERT_EQ( 3, err.line() );
  ASSERT_EQ( 1350, err.column() );
}