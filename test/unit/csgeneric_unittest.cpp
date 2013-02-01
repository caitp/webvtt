#include "cue_testfixture"
class CueSetting : public CueTest { };
#if 0
/**
 * Verifies that the parser correctly parses a combination of 2 cue settings of different types,
 * delimited by U+0009 (tab)
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * 1. Let settings be the result of splitting input on spaces.
 *
 * From http://dev.w3.org/html5/spec//common-microsyntaxes.html#space-separated-tokens (11/27/2012):
 * 5.1. Collect a sequence of characters that are not space characters.
 *
 * From http://dev.w3.org/html5/spec//common-microsyntaxes.html#space-character (11/27/2012):
 * The space characters, for the purposes of this specification, are U+0020 SPACE, "tab" (U+0009), "LF" (U+000A), "FF" (U+000C), and "CR" (U+000D).
 */
TEST_F(CueSetting, MultipleCueSettings2Tab)
{
  loadVtt( "cue-settings/2-cue-settings-0x09.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_TRUE( getCue( 0 ).isVerticalLeftToRight() );
  ASSERT_EQ( 50, getCue( 0 ).relativeLinePositionPercentage() );
}

/**
 * Verifies that the parser correctly parses a combination of 2 cue settings of different types,
 * delimited by U+0020 (space)
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * 1. Let settings be the result of splitting input on spaces.
 *
 * From http://dev.w3.org/html5/spec//common-microsyntaxes.html#space-separated-tokens (11/27/2012):
 * 5.1. Collect a sequence of characters that are not space characters.
 *
 * From http://dev.w3.org/html5/spec//common-microsyntaxes.html#space-character (11/27/2012):
 * The space characters, for the purposes of this specification, are U+0020 SPACE, "tab" (U+0009), "LF" (U+000A), "FF" (U+000C), and "CR" (U+000D).
 */
TEST_F(CueSetting, MultipleCueSettings2Space)
{
  loadVtt( "cue-settings/2-cue-settings-0x20.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_TRUE( getCue( 0 ).isVerticalLeftToRight() );
  ASSERT_EQ( 50, getCue( 0 ).relativeLinePositionPercentage() );
}

/**
 * Verifies that the parser correctly parses a combination of 2 cue settings of different types,
 * delimited by a combination of U+0020 (space) and U+0009 (tab)
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * 1. Let settings be the result of splitting input on spaces.
 *
 * From http://dev.w3.org/html5/spec//common-microsyntaxes.html#space-separated-tokens (11/27/2012):
 * 5.1. Collect a sequence of characters that are not space characters.
 *
 * From http://dev.w3.org/html5/spec//common-microsyntaxes.html#space-character (11/27/2012):
 * The space characters, for the purposes of this specification, are U+0020 SPACE, "tab" (U+0009), "LF" (U+000A), "FF" (U+000C), and "CR" (U+000D).
 */
TEST_F(CueSetting, MultipleCueSettings2Mixed)
{
  loadVtt( "cue-settings/2-cue-settings-mixed.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_TRUE( getCue( 0 ).isVerticalLeftToRight() );
  ASSERT_EQ( 50, getCue( 0 ).relativeLinePositionPercentage() );
}

/**
 * Verifies that the parser can deal with the U+0020 delimiter
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * 1. Let settings be the result of splitting input on spaces.
 *
 * From http://dev.w3.org/html5/spec//common-microsyntaxes.html#space-separated-tokens (11/27/2012):
 * 4. Skip whitespace
 *
 * From http://dev.w3.org/html5/spec//common-microsyntaxes.html#skip-whitespace (11/27/2012):
 * The step skip whitespace means that the user agent must collect a sequence of characters that are space characters. ...the collected characters are not used.
 *
 * From http://dev.w3.org/html5/spec//common-microsyntaxes.html#space-character (11/27/2012):
 * The space characters, for the purposes of this specification, are U+0020 SPACE, "tab" (U+0009), "LF" (U+000A), "FF" (U+000C), and "CR" (U+000D).
 */
TEST_F(CueSetting, Delimiter0x20)
{
  loadVtt( "cue-settings/delimiter-0x20.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_TRUE( getCue( 0 ).isVerticalLeftToRight() );
}

/**
 * Verifies that the parser can deal with the U+0020 delimiter
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * 1. Let settings be the result of splitting input on spaces.
 *
 * From http://dev.w3.org/html5/spec//common-microsyntaxes.html#space-separated-tokens (11/27/2012):
 * 4. Skip whitespace
 *
 * From http://dev.w3.org/html5/spec//common-microsyntaxes.html#skip-whitespace (11/27/2012):
 * The step skip whitespace means that the user agent must collect a sequence of characters that are space characters. ...the collected characters are not used.
 *
 * From http://dev.w3.org/html5/spec//common-microsyntaxes.html#space-character (11/27/2012):
 * The space characters, for the purposes of this specification, are U+0020 SPACE, "tab" (U+0009), "LF" (U+000A), "FF" (U+000C), and "CR" (U+000D).
 */
TEST_F(CueSetting, Delimiter0x20Sequence)
{
  loadVtt( "cue-settings/delimiter-0x20-sequence.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_TRUE( getCue( 0 ).isVerticalLeftToRight() );
}

/**
 * Verifies that the parser can deal with the U+0020 delimiter
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * 1. Let settings be the result of splitting input on spaces.
 *
 * From http://dev.w3.org/html5/spec//common-microsyntaxes.html#space-separated-tokens (11/27/2012):
 * 4. Skip whitespace
 *
 * From http://dev.w3.org/html5/spec//common-microsyntaxes.html#skip-whitespace (11/27/2012):
 * The step skip whitespace means that the user agent must collect a sequence of characters that are space characters. ...the collected characters are not used.
 *
 * From http://dev.w3.org/html5/spec//common-microsyntaxes.html#space-character (11/27/2012):
 * The space characters, for the purposes of this specification, are U+0020 SPACE, "tab" (U+0009), "LF" (U+000A), "FF" (U+000C), and "CR" (U+000D).
 */
TEST_F(CueSetting, Delimiter0x09)
{
  loadVtt( "cue-settings/delimiter-0x09.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_TRUE( getCue( 0 ).isVerticalLeftToRight() );
}

/**
 * Verifies that the parser can deal with the U+0020 delimiter
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * 1. Let settings be the result of splitting input on spaces.
 *
 * From http://dev.w3.org/html5/spec//common-microsyntaxes.html#space-separated-tokens (11/27/2012):
 * 4. Skip whitespace
 *
 * From http://dev.w3.org/html5/spec//common-microsyntaxes.html#skip-whitespace (11/27/2012):
 * The step skip whitespace means that the user agent must collect a sequence of characters that are space characters. ...the collected characters are not used.
 *
 * From http://dev.w3.org/html5/spec//common-microsyntaxes.html#space-character (11/27/2012):
 * The space characters, for the purposes of this specification, are U+0020 SPACE, "tab" (U+0009), "LF" (U+000A), "FF" (U+000C), and "CR" (U+000D).
 */
TEST_F(CueSetting, Delimiter0x09Sequence)
{
  loadVtt( "cue-settings/delimiter-0x09-sequence.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_TRUE( getCue( 0 ).isVerticalLeftToRight() );
}

/**
 * Verifies that the parser can deal with the U+0020 delimiter
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * 1. Let settings be the result of splitting input on spaces.
 *
 * From http://dev.w3.org/html5/spec//common-microsyntaxes.html#space-separated-tokens (11/27/2012):
 * 4. Skip whitespace
 *
 * From http://dev.w3.org/html5/spec//common-microsyntaxes.html#skip-whitespace (11/27/2012):
 * The step skip whitespace means that the user agent must collect a sequence of characters that are space characters. ...the collected characters are not used.
 *
 * From http://dev.w3.org/html5/spec//common-microsyntaxes.html#space-character (11/27/2012):
 * The space characters, for the purposes of this specification, are U+0020 SPACE, "tab" (U+0009), "LF" (U+000A), "FF" (U+000C), and "CR" (U+000D).
 */
TEST_F(CueSetting, DelimiterMixed)
{
  loadVtt( "cue-settings/delimiter-mixed.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_TRUE( getCue( 0 ).isVerticalLeftToRight() );
}

/**
 * Verify the parser accepts duplicate settings.
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * 1. Let settings be the result of splitting input on spaces.
 * 2. For each token setting in the list settings...
 */
TEST_F(CueSetting, SameCueSetting)
{
  loadVtt( "cue-settings/2-same-settings.vtt", 1 );
  const Error &err = getError( 0 );
  /**
   * Parser will successfully parse duplicate settings so there will be no error.
     * The settings are parsed in order so that the right most (last in the list) one is used.
   */
  ASSERT_TRUE( getCue( 0 ).isVerticalRightToLeft() );
  /**
  * We're expecting a WEBVTT_VERTICAL_ALREADY_SET error on the 37th column of the 3rd line
  * We can probably make this smarter, like WEBVTT_EXPECTED_CUESETTING_DELIMITER or something
  */
  ASSERT_EQ( WEBVTT_VERTICAL_ALREADY_SET, err.error() );
  ASSERT_EQ( 3, err.line() );
  ASSERT_EQ( 37, err.column() );
}

/**
 * Test that the parser takes everything to the right of the first colon in a setting.
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * 1. Let settings be the result of splitting input on spaces.
 * 2. For each token setting in the list settings...
 * 2.3. Let value be the trailing substring of setting starting from the character immediately after the first U+003A COLON character (:) in that string.
 */
#endif
TEST_F(CueSetting, BadDelimiter)
{
  loadVtt( "cue-settings/bad-delimiter.vtt", 1 );
  const Error &err = getError( 0 );
  /**
   * The parser should try to use "vertical" as keyword and "lr;line:50%" as value.
     * Writing direction should "horizontal" because the malformed setting should be skipped
     * and "horizontal" is default.
   */
  ASSERT_TRUE( getCue( 0 ).isHorizontal() );
  /**
   * We're expecting a WEBVTT_EXPECTED_WHITESPACE error on the 36th column of the 3rd line
   */
  ASSERT_EQ( WEBVTT_INVALID_CUESETTING_DELIMITER, err.error() );
  ASSERT_EQ( 3, err.line() );
  ASSERT_EQ( 36, err.column() );
}

/**
 * Test that the parser does not require a spacing character between cue end time
 * timestamp and settings. There cannot be four digits in a row after the cue end time
 * timestamp decimal.
 *
 * From http://dev.w3.org/html5/webvtt/#collect-webvtt-cue-timings-and-settings (11/21/2012):
 * 10. Collect a WebVTT timestamp.
 * 11. Let remainder be the trailing substring of input starting at position.
 * 12. Parse the WebVTT settings given by remainder for cue.
 *
 * From http://dev.w3.org/html5/webvtt/#collect-a-webvtt-timestamp (11/21/2012):
 * 14. Collect a sequence of characters that are ASCII digits, and let string be the collected substring.
 * 15. If string is not exactly three characters in length, return an error and abort these steps.
 */
TEST_F(CueSetting, BadDelimiter2)
{
  loadVtt( "cue-settings/bad-delimiter2.vtt", 1 );
  const Error &err = getError( 0 );
  /**
   * The parser does not require a spacing character between cue end time timestamp and
     * settings. The parser should try to use "^line" for the keyword.
     * Line should "auto" because the malformed setting should be skipped
     * and "auto" is default.
   */
  ASSERT_TRUE( getCue( 0 ).isLinePositionAuto() );
  /**
   * We're expecting a WEBVTT_EXPECTED_WHITESPACE error on the 24th column of the 3rd line
   */
  ASSERT_EQ( WEBVTT_INVALID_CUESETTING_DELIMITER, err.error() );
  ASSERT_EQ( 3, err.line() );
  ASSERT_EQ( 24, err.column() );
}

/**
 * Test that the parser does not require a spacing character between cue end time
 * timestamp and settings. There cannot be four digits in a row after the cue end time
 * timestamp decimal.
 *
 * From http://dev.w3.org/html5/webvtt/#collect-webvtt-cue-timings-and-settings (11/21/2012):
 * 10. Collect a WebVTT timestamp.
 * 11. Let remainder be the trailing substring of input starting at position.
 * 12. Parse the WebVTT settings given by remainder for cue.
 *
 * From http://dev.w3.org/html5/webvtt/#collect-a-webvtt-timestamp (11/21/2012):
 * 14. Collect a sequence of characters that are ASCII digits, and let string be the collected substring.
 * 15. If string is not exactly three characters in length, return an error and abort these steps.
 */
TEST_F(CueSetting, NoDelimiter)
{
  loadVtt( "cue-settings/no-delimiter.vtt", 1 );
  const Error &err = getError( 0 );
  /**
   * The parser does not require a spacing character between cue end time timestamp and
     * settings. The parser should try to use "line" for the keyword.
     * The line setting should be valid.
   */
  ASSERT_EQ( 68, getCue( 0 ).relativeLinePositionPercentage() );
  /**
   * We're expecting a WEBVTT_EXPECTED_WHITESPACE error on the 24th column of the 3rd line
   */
  ASSERT_EQ( WEBVTT_EXPECTED_WHITESPACE, err.error() );
  ASSERT_EQ( 3, err.line() );
  ASSERT_EQ( 24, err.column() );
}

/**
 * Test that the parser does not require a spacing character between cue end time
 * timestamp and settings. There cannot be four digits in a row after the cue end time
 * timestamp decimal.
 *
 * From http://dev.w3.org/html5/webvtt/#collect-webvtt-cue-timings-and-settings (11/21/2012):
 * 10. Collect a WebVTT timestamp.
 * 11. Let remainder be the trailing substring of input starting at position.
 * 12. Parse the WebVTT settings given by remainder for cue.
 *
 * From http://dev.w3.org/html5/webvtt/#collect-a-webvtt-timestamp (11/21/2012):
 * 14. Collect a sequence of characters that are ASCII digits, and let string be the collected substring.
 * 15. If string is not exactly three characters in length, return an error and abort these steps.
 */
TEST_F(CueSetting, DigitDelimiter)
{
  loadVtt( "cue-settings/digit-delimiter.vtt" );
  const Error &err = getError( 0 );
  /**
   * We're expecting a WEBVTT_MALFORMED_TIMESTAMP error on the 24th column of the 3rd line.
     * It might be on column 21 depending on how the parser parses the fractions of a second.
   */
  ASSERT_EQ( WEBVTT_MALFORMED_TIMESTAMP, err.error() );
  ASSERT_EQ( 3, err.line() );
  ASSERT_EQ( 24, err.column() );
}
