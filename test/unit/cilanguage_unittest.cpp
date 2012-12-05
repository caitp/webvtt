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

/**
 * Test to determine if Chinese characters are able to pass as part of the cue id in the parser
 * 
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-identifier (11/24/2012)
 * A WebVTT cue identifier is any sequence of one or more characters not containing the substring "-->" 
 * (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN), nor containing any U+000A LINE FEED (LF) 
 * characters or U+000D CARRIAGE RETURN (CR) characters.
 * 
 * Note: A WebVTT cue identifier can be used to reference a specific cue, for example from script or CSS.
 */
TEST_F(CueIdLanguage,Chinese)
{
  loadVtt( "cue-ids/languages/chinese.vtt" );

  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

/**
 * Test to determine if Greek characters are able to pass as part of the cue id in the parser
 * 
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-identifier (11/24/2012)
 * A WebVTT cue identifier is any sequence of one or more characters not containing the substring "-->" 
 * (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN), nor containing any U+000A LINE FEED (LF) 
 * characters or U+000D CARRIAGE RETURN (CR) characters.
 * 
 * Note: A WebVTT cue identifier can be used to reference a specific cue, for example from script or CSS.
 */
TEST_F(CueIdLanguage,Greek)
{
  loadVtt( "cue-ids/languages/greek.vtt" );

  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

/**
 * Test to determine if Hebrew characters are able to pass as part of the cue id in the parser
 * 
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-identifier (11/24/2012)
 * A WebVTT cue identifier is any sequence of one or more characters not containing the substring "-->" 
 * (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN), nor containing any U+000A LINE FEED (LF) 
 * characters or U+000D CARRIAGE RETURN (CR) characters.
 * 
 * Note: A WebVTT cue identifier can be used to reference a specific cue, for example from script or CSS.
 */
TEST_F(CueIdLanguage,Hebrew)
{
  loadVtt( "cue-ids/languages/hebrew.vtt" );

  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

/**
 * Test to determine if Korean characters are able to pass as part of the cue id in the parser
 * 
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-identifier (11/24/2012)
 * A WebVTT cue identifier is any sequence of one or more characters not containing the substring "-->" 
 * (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN), nor containing any U+000A LINE FEED (LF) 
 * characters or U+000D CARRIAGE RETURN (CR) characters.
 * 
 * Note: A WebVTT cue identifier can be used to reference a specific cue, for example from script or CSS.
 */
TEST_F(CueIdLanguage,Korean)
{
  loadVtt( "cue-ids/languages/korean.vtt" );

  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

/**
 * Test to determine if Thai characters are able to pass as part of the cue id in the parser
 * 
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-identifier (11/24/2012)
 * A WebVTT cue identifier is any sequence of one or more characters not containing the substring "-->" 
 * (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN), nor containing any U+000A LINE FEED (LF) 
 * characters or U+000D CARRIAGE RETURN (CR) characters.
 * 
 * Note: A WebVTT cue identifier can be used to reference a specific cue, for example from script or CSS.
 */
TEST_F(CueIdLanguage,Thai)
{
  loadVtt( "cue-ids/languages/thai.vtt" );

  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

/**
 * Test to determine if Thai characters are able to pass as part of the cue id in the parser
 * 
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-identifier (11/24/2012)
 * A WebVTT cue identifier is any sequence of one or more characters not containing the substring "-->" 
 * (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN), nor containing any U+000A LINE FEED (LF) 
 * characters or U+000D CARRIAGE RETURN (CR) characters.
 * 
 * Note: A WebVTT cue identifier can be used to reference a specific cue, for example from script or CSS.
 */
TEST_F(CueIdLanguage,MultipleLanguages)
{
  loadVtt( "cue-ids/languages/multiple_languages.vtt" );

  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

/**
 * Test to determine if an extremely long string (5000+) of Arabic characters are able to pass as part of the cue id in the parser
 * 
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-identifier (11/24/2012)
 * A WebVTT cue identifier is any sequence of one or more characters not containing the substring "-->" 
 * (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN), nor containing any U+000A LINE FEED (LF) 
 * characters or U+000D CARRIAGE RETURN (CR) characters.
 * 
 * Note: A WebVTT cue identifier can be used to reference a specific cue, for example from script or CSS.
 */
TEST_F(CueIdLanguage,DISABLED_LongStringArabic) //currently truncating characters below the 65535 byte limit
{
  loadVtt( "cue-ids/languages/long_string_arabic.vtt" );

  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

/**
 * Test to determine if an extremely long string (5000+) Japanese characters are able to pass as part of the cue id in the parser
 * 
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-identifier (11/24/2012)
 * A WebVTT cue identifier is any sequence of one or more characters not containing the substring "-->" 
 * (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN), nor containing any U+000A LINE FEED (LF) 
 * characters or U+000D CARRIAGE RETURN (CR) characters.
 * 
 * Note: A WebVTT cue identifier can be used to reference a specific cue, for example from script or CSS.
 */
TEST_F(CueIdLanguage,DISABLED_LongStringJapanese) //currently truncating characters below the 65535 byte limit
{
  loadVtt( "cue-ids/languages/long_string_japanese.vtt" );

  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

/**
 * Test to determine if an extremely long string (5000+) Russian characters are able to pass as part of the cue id in the parser
 * 
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-identifier (11/24/2012)
 * A WebVTT cue identifier is any sequence of one or more characters not containing the substring "-->" 
 * (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN), nor containing any U+000A LINE FEED (LF) 
 * characters or U+000D CARRIAGE RETURN (CR) characters.
 * 
 * Note: A WebVTT cue identifier can be used to reference a specific cue, for example from script or CSS.
 */
TEST_F(CueIdLanguage,DISABLED_LongStringRussian) //currently truncating characters below the 65535 byte limit
{
  loadVtt( "cue-ids/languages/long_string_russian.vtt" );

  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

/**
 * Test to determine if an extremely long string (5000+) Chinese characters are able to pass as part of the cue id in the parser
 * 
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-identifier (11/24/2012)
 * A WebVTT cue identifier is any sequence of one or more characters not containing the substring "-->" 
 * (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN), nor containing any U+000A LINE FEED (LF) 
 * characters or U+000D CARRIAGE RETURN (CR) characters.
 * 
 * Note: A WebVTT cue identifier can be used to reference a specific cue, for example from script or CSS.
 */
TEST_F(CueIdLanguage,DISABLED_LongStringChinese) //currently truncating characters below the 65535 byte limit
{
  loadVtt( "cue-ids/languages/long_string_chinese.vtt" );

  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

/**
 * Test to determine if an extremely long string (5000+) Greek characters are able to pass as part of the cue id in the parser
 * 
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-identifier (11/24/2012)
 * A WebVTT cue identifier is any sequence of one or more characters not containing the substring "-->" 
 * (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN), nor containing any U+000A LINE FEED (LF) 
 * characters or U+000D CARRIAGE RETURN (CR) characters.
 * 
 * Note: A WebVTT cue identifier can be used to reference a specific cue, for example from script or CSS.
 */
TEST_F(CueIdLanguage,DISABLED_LongStringGreek) //currently truncating characters below the 65535 byte limit
{
  loadVtt( "cue-ids/languages/long_string_greek.vtt" );

  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

/**
 * Test to determine if an extremely long string (5000+) Hebrew characters are able to pass as part of the cue id in the parser
 * 
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-identifier (11/24/2012)
 * A WebVTT cue identifier is any sequence of one or more characters not containing the substring "-->" 
 * (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN), nor containing any U+000A LINE FEED (LF) 
 * characters or U+000D CARRIAGE RETURN (CR) characters.
 * 
 * Note: A WebVTT cue identifier can be used to reference a specific cue, for example from script or CSS.
 */
TEST_F(CueIdLanguage,DISABLED_LongStringHebrew) //currently truncating characters below the 65535 byte limit
{
  loadVtt( "cue-ids/languages/long_string_hebrew.vtt" );

  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

/**
 * Test to determine if an extremely long string (5000+) Korean characters are able to pass as part of the cue id in the parser
 * 
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-identifier (11/24/2012)
 * A WebVTT cue identifier is any sequence of one or more characters not containing the substring "-->" 
 * (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN), nor containing any U+000A LINE FEED (LF) 
 * characters or U+000D CARRIAGE RETURN (CR) characters.
 * 
 * Note: A WebVTT cue identifier can be used to reference a specific cue, for example from script or CSS.
 */
TEST_F(CueIdLanguage,DISABLED_LongStringKorean) //currently truncating characters below the 65535 byte limit
{
  loadVtt( "cue-ids/languages/long_string_korean.vtt" );

  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

/**
 * Test to determine if an extremely long string (5000+) Thai characters are able to pass as part of the cue id in the parser
 * 
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-identifier (11/24/2012)
 * A WebVTT cue identifier is any sequence of one or more characters not containing the substring "-->" 
 * (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN), nor containing any U+000A LINE FEED (LF) 
 * characters or U+000D CARRIAGE RETURN (CR) characters.
 * 
 * Note: A WebVTT cue identifier can be used to reference a specific cue, for example from script or CSS.
 */
TEST_F(CueIdLanguage,DISABLED_LongStringThai) //currently truncating characters below the 65535 byte limit
{
  loadVtt( "cue-ids/languages/long_string_thai.vtt" );

  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

/**
 * Test to determine if an extremely long string (5000+) of multiple characters (Left and right aligned) are able to pass as part of the cue id in the parser
 * 
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-identifier (11/24/2012)
 * A WebVTT cue identifier is any sequence of one or more characters not containing the substring "-->" 
 * (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN), nor containing any U+000A LINE FEED (LF) 
 * characters or U+000D CARRIAGE RETURN (CR) characters.
 * 
 * Note: A WebVTT cue identifier can be used to reference a specific cue, for example from script or CSS.
 */
TEST_F(CueIdLanguage,DISABLED_LongStringMultipleLanguages) //currently truncating characters below the 65535 byte limit
{
  loadVtt( "cue-ids/languages/long_string_multiple_languages.vtt" );

  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

/**
 * Test to determine if an extremely long string (5000+) of junk characters are able to pass as part of the cue id in the parser
 * 
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-identifier (11/24/2012)
 * A WebVTT cue identifier is any sequence of one or more characters not containing the substring "-->" 
 * (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN), nor containing any U+000A LINE FEED (LF) 
 * characters or U+000D CARRIAGE RETURN (CR) characters.
 * 
 * Note: A WebVTT cue identifier can be used to reference a specific cue, for example from script or CSS.
 */
TEST_F(CueIdLanguage,DISABLED_LongStringJunkCharacters) //currently truncating characters below the 65535 byte limit
{
  loadVtt( "cue-ids/languages/long_string_junk_characters.vtt" );

  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}