#include "cue_testfixture"
class CueIdGeneral : public CueTest { };

/**
 * Test to determine if the most basic one-character cue id passes
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-identifier (11/24/2012)
 * A WebVTT cue identifier is any sequence of one or more characters not containing the substring "-->"
 * (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN), nor containing any U+000A LINE FEED (LF)
 * characters or U+000D CARRIAGE RETURN (CR) characters.
 *
 * Note: A WebVTT cue identifier can be used to reference a specific cue, for example from script or CSS.
 */
TEST_F(CueIdGeneral, BasicPass) //C++ exception: "std::bad_alloc"
{
  loadVtt( "cue-ids/basic_pass.vtt" );

  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

/**
 * Test to determine if a WEBVTT Cue Id allows a *very* large character input.
 * This test floods the cue ID with characters, but should pass
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-identifier (11/24/2012)
 * A WebVTT cue identifier is any sequence of one or more characters not containing the substring "-->"
 * (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN), nor containing any U+000A LINE FEED (LF)
 * characters or U+000D CARRIAGE RETURN (CR) characters.
 *
 * Note: A WebVTT cue identifier can be used to reference a specific cue, for example from script or CSS.
 */
TEST_F(CueIdGeneral, LongString) //Test currently throws a webvtt cue incomplete error, however it should pass
{
  loadVtt( "cue-ids/long_string.vtt" );
  const Error &err = getError( 0 );
  //ASSERT_EQ( WEBVTT_CUE_INCOMPLETE, err.error() );

  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

/**
 * Test if parser fails if the webvtt file only has a cue id (no timestamp or payload)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-identifier (11/24/2012)
 * A WebVTT cue identifier is any sequence of one or more characters not containing the substring "-->"
 * (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN), nor containing any U+000A LINE FEED (LF)
 * characters or U+000D CARRIAGE RETURN (CR) characters.
 *
 * Note: A WebVTT cue identifier can be used to reference a specific cue, for example from script or CSS.
 */
TEST_F(CueIdGeneral, IdOnly)
{
  loadVtt( "cue-ids/id_only.vtt" );
  const Error &err = getError( 0 );

  ASSERT_EQ( WEBVTT_CUE_INCOMPLETE, err.error() );
  ASSERT_EQ( 4, err.line() );
  ASSERT_EQ( 0, err.column() );
}
