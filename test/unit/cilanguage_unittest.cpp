#include "cue_testfixture"
class CueIdLanguage : public CueTest { };

/**
 * Test to determine if random junk characters are able to pass as part of the cue id in the parser
 * 
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-identifier (11/24/2012)
 * A WebVTT cue identifier is any sequence of one or more characters not containing the substring "-->" 
 * (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN), nor containing any U+000A LINE FEED (LF) 
 * characters or U+000D CARRIAGE RETURN (CR) characters.
 * 
 * Note: A WebVTT cue identifier can be used to reference a specific cue, for example from script or CSS.
 */
TEST_F(CueIdLanguage,JunkCharacters)
{
  loadVtt( "cue-ids/languages/junk_characters.vtt" );

  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

/**
 * Test to determine if Arabic characters are able to pass as part of the cue id in the parser
 * 
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-identifier (11/24/2012)
 * A WebVTT cue identifier is any sequence of one or more characters not containing the substring "-->" 
 * (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN), nor containing any U+000A LINE FEED (LF) 
 * characters or U+000D CARRIAGE RETURN (CR) characters.
 * 
 * Note: A WebVTT cue identifier can be used to reference a specific cue, for example from script or CSS.
 */
TEST_F(CueIdLanguage,Arabic)
{
  loadVtt( "cue-ids/languages/arabic.vtt" );

  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

/**
 * Test to determine if Japanese characters are able to pass as part of the cue id in the parser
 * 
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-identifier (11/24/2012)
 * A WebVTT cue identifier is any sequence of one or more characters not containing the substring "-->" 
 * (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN), nor containing any U+000A LINE FEED (LF) 
 * characters or U+000D CARRIAGE RETURN (CR) characters.
 * 
 * Note: A WebVTT cue identifier can be used to reference a specific cue, for example from script or CSS.
 */
TEST_F(CueIdLanguage,Japanese)
{
  loadVtt( "cue-ids/languages/japanese.vtt" );

  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

/**
 * Test to determine if Russian characters are able to pass as part of the cue id in the parser
 * 
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-identifier (11/24/2012)
 * A WebVTT cue identifier is any sequence of one or more characters not containing the substring "-->" 
 * (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN), nor containing any U+000A LINE FEED (LF) 
 * characters or U+000D CARRIAGE RETURN (CR) characters.
 * 
 * Note: A WebVTT cue identifier can be used to reference a specific cue, for example from script or CSS.
 */
TEST_F(CueIdLanguage,Russian)
{
  loadVtt( "cue-ids/languages/russian.vtt" );

  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}