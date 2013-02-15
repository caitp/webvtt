#include "cue_testfixture"
class CueSettingPosition : public CueTest { };

/**
 * Successfully parse a properly formatted single digit percentage 'position:5%'
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * If name is a case-sensitive match for "position"
 * 5. Ignoring the trailing percent sign, interpret value as an integer, and let number be that number.
 * 7. Let cue's text track cue text position be number.
 */
TEST_F(CueSettingPosition, SingleDigitPercentage)
{
  loadVtt( "cue-settings/position/single-digit-pct.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 5, getCue( 0 ).textPositionPercentage() );
}

/**
 * Successfully parse a properly formatted single digit percentage 'position:9%'
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * If name is a case-sensitive match for "position"
 * 5. Ignoring the trailing percent sign, interpret value as an integer, and let number be that number.
 * 7. Let cue's text track cue text position be number.
 */
TEST_F(CueSettingPosition, SingleDigitPercentageHighBoundary)
{
  loadVtt( "cue-settings/position/single-digit-pct-high-boundary.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 9, getCue( 0 ).textPositionPercentage() );
}

/**
 * Successfully parse a properly formatted single digit percentage 'position:0%'
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * If name is a case-sensitive match for "position"
 * 5. Ignoring the trailing percent sign, interpret value as an integer, and let number be that number.
 * 7. Let cue's text track cue text position be number.
 */
TEST_F(CueSettingPosition, SingleDigitPercentageLowBoundary)
{
  loadVtt( "cue-settings/position/single-digit-pct-low-boundary.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 0, getCue( 0 ).textPositionPercentage() );
}

/**
 * Successfully parse a properly formatted double digit percentage 'position:50%'
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * If name is a case-sensitive match for "position"
 * 5. Ignoring the trailing percent sign, interpret value as an integer, and let number be that number.
 * 7. Let cue's text track cue text position be number.
 */
TEST_F(CueSettingPosition, DoubleDigitPercentage)
{
  loadVtt( "cue-settings/position/double-digit-pct.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 50, getCue( 0 ).textPositionPercentage() );
}

/**
 * Successfully parse a properly formatted double digit percentage 'position:99%'
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * If name is a case-sensitive match for "position"
 * 5. Ignoring the trailing percent sign, interpret value as an integer, and let number be that number.
 * 7. Let cue's text track cue text position be number.
 */
TEST_F(CueSettingPosition, DoubleDigitPercentageHighBoundary)
{
  loadVtt( "cue-settings/position/double-digit-pct-high-boundary.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 99, getCue( 0 ).textPositionPercentage() );
}

/**
 * Successfully parse a properly formatted double digit percentage 'position:00%'
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * If name is a case-sensitive match for "position"
 * 5. Ignoring the trailing percent sign, interpret value as an integer, and let number be that number.
 * 7. Let cue's text track cue text position be number.
 */
TEST_F(CueSettingPosition, DoubleDigitPercentageLowBoundary)
{
  loadVtt( "cue-settings/position/double-digit-pct-low-boundary.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 0, getCue( 0 ).textPositionPercentage() );
}

/**
 * Successfully parse a properly formatted triple digit percentage 'position:555%'
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * If name is a case-sensitive match for "position"
 * 5. Ignoring the trailing percent sign, interpret value as an integer, and let number be that number.
 * 7. Let cue's text track cue text position be number.
 */
TEST_F(CueSettingPosition, TripleDigitPercentage)
{
  loadVtt( "cue-settings/position/triple-digit-pct.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 55, getCue( 0 ).textPositionPercentage() );
}

/**
 * Successfully parse a properly formatted triple digit percentage 'position:999%'
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * If name is a case-sensitive match for "position"
 * 5. Ignoring the trailing percent sign, interpret value as an integer, and let number be that number.
 * 7. Let cue's text track cue text position be number.
 */
TEST_F(CueSettingPosition, TripleDigitPercentageHighBoundary)
{
  loadVtt( "cue-settings/position/triple-digit-pct-high-boundary.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 100, getCue( 0 ).textPositionPercentage() );
}

/**
 * Successfully parse a properly formatted triple digit percentage 'position:000%'
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * If name is a case-sensitive match for "position"
 * 5. Ignoring the trailing percent sign, interpret value as an integer, and let number be that number.
 * 7. Let cue's text track cue text position be number.
 */
TEST_F(CueSettingPosition, TripleDigitPercentageLowBoundary)
{
  loadVtt( "cue-settings/position/double-digit-pct-low-boundary.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 0, getCue( 0 ).textPositionPercentage() );
}

/**
 * Test that the parser requires a colon.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * 1. If setting does not contain a U+003A COLON character (:), or if the first
 *    U+003A COLON character (:) in setting is either the first or last
 *    character of setting, then jump to the step labeled next setting.
 * 5. Next setting: Continue to the next token, if any.
 */
TEST_F(CueSettingPosition, NoDelimiter)
{
  loadVtt( "cue-settings/position/no-delimiter.vtt", 1 );
  ASSERT_EQ( 2, errorCount() );

  /**
   * Position should be 50 because the malformed setting should be skipped and
   * 50 is default.
   */
  ASSERT_EQ( 50, getCue( 0 ).textPositionPercentage() );
  
  /**
   * We're expecting a WEBVTT_UNEXPECTED_WHITESPACE on the 33rd column of the
   * 3rd line, and a WEBVTT_MISSING_CUESETTING_DELIMITER error on the 34th
   * column of the 3rd line
   */
  assertEquals( getError( 0 ), WEBVTT_UNEXPECTED_WHITESPACE, 3, 33 );
  assertEquals( getError( 1 ), WEBVTT_MISSING_CUESETTING_DELIMITER, 3, 34 );
}

/**
 * Test that the parser does not allow a setting to start with a colon.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * 1. If setting does not contain a U+003A COLON character (:), or if the first
 *    U+003A COLON character (:) in setting is either the first or last
 *    character of setting, then jump to the step labeled next setting.
 * 5. Next setting: Continue to the next token, if any.
 */
TEST_F(CueSettingPosition, NoKeyword)
{
  loadVtt( "cue-settings/position/no-keyword.vtt", 1 );
  ASSERT_EQ( 1, errorCount() );

  /**
   * Position should be 50 because the malformed setting should be skipped and
   * 50 is default.
   */
  ASSERT_EQ( 50, getCue( 0 ).textPositionPercentage() );

  /**
   * We're expecting a WEBVTT_INVALID_CUESETTING error on the 25th column of the
   * 3rd line
   */
  assertEquals( getError( 0 ), WEBVTT_INVALID_CUESETTING, 3, 25 );
}

/**
 * Test that the parser does not allow a setting to end with a colon.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * 1. If setting does not contain a U+003A COLON character (:), or if the first U+003A COLON character (:) in setting is either the first or last character of setting, then jump to the step labeled next setting.
 * 5. Next setting: Continue to the next token, if any.
 */
TEST_F(CueSettingPosition, NoValue)
{
  loadVtt( "cue-settings/position/no-value.vtt", 1 );
  const Error &err = getError( 0 );
  /**
   * Position should be 50 because the malformed setting should be skipped
     * and 50 is default.
   */
  ASSERT_EQ( 50, getCue( 0 ).textPositionPercentage() );
  /**
   * We're expecting a WEBVTT_POSITION_BAD_VALUE error on the 34th column of the 3rd line
   * We can probably make this smarter, like WEBVTT_EXPECTED_CUESETTING_VALUE or something
   */
  ASSERT_EQ( WEBVTT_POSITION_BAD_VALUE, err.error() );
  ASSERT_EQ( 3, err.line() );
  ASSERT_EQ( 34, err.column() );
}

/**
 * Test that a percent sign is required.
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * If name is a case-sensitive match for "position"
 * 3. If any character in value other than the last character is a U+0025 PERCENT SIGN character (%), then jump to the step labeled next setting.
 */
TEST_F(CueSettingPosition, NoPercentSign)
{
  loadVtt( "cue-settings/position/no-percent-sign.vtt", 1 );
  const Error &err = getError( 0 );
  /**
   * Position should be 50 because the malformed setting should be skipped
     * and 50 is default.
   */
  ASSERT_EQ( 50, getCue( 0 ).textPositionPercentage() );
  /**
   * We're expecting a WEBVTT_POSITION_BAD_VALUE error on the 34th column of the 3rd line
   * We can probably make this smarter, like WEBVTT_EXPECTED_PERCENTAGE or something
   */
  ASSERT_EQ( WEBVTT_POSITION_BAD_VALUE, err.error() );
  ASSERT_EQ( 3, err.line() );
  ASSERT_EQ( 34, err.column() );
}

/**
 * Test that the parser requires a colon.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * 1. If setting does not contain a U+003A COLON character (:), or if the first
 *    U+003A COLON character (:) in setting is either the first or last character
 *    of setting, then jump to the step labeled next setting.
 * 5. Next setting: Continue to the next token, if any.
 */
TEST_F(CueSettingPosition, BadDelimiter)
{
  loadVtt( "cue-settings/position/bad-delimiter.vtt", 1 );
  ASSERT_EQ( 1, errorCount() );

  /**
   * Position should be 50 because the malformed setting should be skipped and
   * 50 is default.
   */
  ASSERT_EQ( 50, getCue( 0 ).textPositionPercentage() );

  /**
   * We're expecting a WEBVTT_INVALID_CUESETTING error on the 25rd column of the
   * 3rd line
   */
  assertEquals( getError( 0 ), WEBVTT_INVALID_CUESETTING, 3, 25 );
}

/**
 * Test that the parser does not change position if the keyword matches nothing.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * 4. Run the appropriate substeps that apply for the value of name, as follows:
 * If name is a case-sensitive match for "vertical" ...
 * If name is a case-sensitive match for "line" ...
 * If name is a case-sensitive match for "position" ...
 * If name is a case-sensitive match for "size" ...
 * If name is a case-sensitive match for "align" ...
 * 5. Next setting: Continue to the next token, if any.
 */
TEST_F(CueSettingPosition, BadKeyword)
{
  loadVtt( "cue-settings/position/bad-keyword.vtt", 1 );
  const Error &err = getError( 0 );
  /**
   * Position should be 50 because the malformed setting should be skipped
     * and 50 is default.
   */
  ASSERT_EQ( 50, getCue( 0 ).textPositionPercentage() );
  /**
   * We're expecting a WEBVTT_INVALID_CUESETTING error on the 25th column of the 3rd line
   */
  ASSERT_EQ( WEBVTT_INVALID_CUESETTING, err.error() );
  ASSERT_EQ( 3, err.line() );
  ASSERT_EQ( 25, err.column() );
}

/**
 * Test that a percent sign is required.
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * If name is a case-sensitive match for "position"
 * 1. If value contains any characters other than U+0025 PERCENT SIGN characters (%) and ASCII digits, then jump to the step labeled next setting.
 */
TEST_F(CueSettingPosition, AsciiDigitBeyondHighBoundary)
{
  loadVtt( "cue-settings/position/above-0x39.vtt", 1 );
  const Error &err = getError( 0 );
  /**
   * Position should be 50 because the malformed setting should be skipped
     * and 50 is default.
   */
  ASSERT_EQ( 50, getCue( 0 ).textPositionPercentage() );
  /**
   * We're expecting a WEBVTT_POSITION_BAD_VALUE error on the 34th column of the 3rd line
   */
  ASSERT_EQ( WEBVTT_POSITION_BAD_VALUE, err.error() );
  ASSERT_EQ( 3, err.line() );
  ASSERT_EQ( 34, err.column() );
}

/**
 * Test that a percent sign is required.
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * If name is a case-sensitive match for "position"
 * 1. If value contains any characters other than U+0025 PERCENT SIGN characters (%) and ASCII digits, then jump to the step labeled next setting.
 */
TEST_F(CueSettingPosition, AsciiDigitBeyondLowBoundary)
{
  loadVtt( "cue-settings/position/below-0x30.vtt", 1 );
  const Error &err = getError( 0 );
  /**
   * Position should be 50 because the malformed setting should be skipped
     * and 50 is default.
   */
  ASSERT_EQ( 50, getCue( 0 ).textPositionPercentage() );
  /**
   * We're expecting a WEBVTT_POSITION_BAD_VALUE error on the 34th column of the 3rd line
   */
  ASSERT_EQ( WEBVTT_POSITION_BAD_VALUE, err.error() );
  ASSERT_EQ( 3, err.line() );
  ASSERT_EQ( 34, err.column() );
}

/**
 * Test that negative values are not allowed.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * If name is a case-sensitive match for "position"
 *  6. If number is not in the range 0 <= number <= 100, then jump to the step labeled next setting.
 */
TEST_F(CueSettingPosition, PercentNegative)
{
  loadVtt( "cue-settings/position/bad-pct-negative.vtt", 1 );
  const Error &err = getError( 0 );
  /**
   * Position should be 50 because the malformed setting should be skipped
     * and 50 is default.
   */
  ASSERT_EQ( 50, getCue( 0 ).textPositionPercentage() );
  /**
   * We're expecting a WEBVTT_POSITION_BAD_VALUE error on the 34th column of the 3rd line
   */
  ASSERT_EQ( WEBVTT_POSITION_BAD_VALUE, err.error() );
  ASSERT_EQ( 3, err.line() );
  ASSERT_EQ( 34, err.column() );
}

/**
 * Test that values over 100 are not allowed.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * If name is a case-sensitive match for "position"
 *  6. If number is not in the range 0 <= number <= 100, then jump to the step labeled next setting.
 */
TEST_F(CueSettingPosition, PercentOver100)
{
  loadVtt( "cue-settings/position/bad-pct-over-100.vtt", 1 );
  const Error &err = getError( 0 );
  /**
   * Position should be 50 because the malformed setting should be skipped
     * and 50 is default.
   */
  ASSERT_EQ( 50, getCue( 0 ).textPositionPercentage() );
  /**
   * We're expecting a WEBVTT_POSITION_BAD_VALUE error on the 34th column of the 3rd line
   */
  ASSERT_EQ( WEBVTT_POSITION_BAD_VALUE, err.error() );
  ASSERT_EQ( 3, err.line() );
  ASSERT_EQ( 34, err.column() );
}

/**
 * Test that the keyword is case-sensitive.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * 4. Run the appropriate substeps that apply for the value of name, as follows:
 * If name is a case-sensitive match for "vertical" ...
 * If name is a case-sensitive match for "line" ...
 * If name is a case-sensitive match for "position" ...
 * If name is a case-sensitive match for "size" ...
 * If name is a case-sensitive match for "align" ...
 * 5. Next setting: Continue to the next token, if any.
 */
TEST_F(CueSettingPosition, UppercaseKeyword)
{
  loadVtt( "cue-settings/position/uppercase-keyword.vtt", 1 );
  const Error &err = getError( 0 );
  /**
   * Position should be 50 because the malformed setting should be skipped
     * and 50 is default.
   */
  ASSERT_EQ( 50, getCue( 0 ).textPositionPercentage() );
  /**
   * We're expecting a WEBVTT_INVALID_CUESETTING error on the 25th column of the 3rd line
   */
  ASSERT_EQ( WEBVTT_INVALID_CUESETTING, err.error() );
  ASSERT_EQ( 3, err.line() );
  ASSERT_EQ( 25, err.column() );
}
