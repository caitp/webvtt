#include "cue_testfixture"
class CueSettingSize : public CueTest { };

/**
 * Successfully parse a properly formatted single digit percentage 'size:5%'
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * If name is a case-sensitive match for "size"
 * 5. Ignoring the trailing percent sign, interpret value as an integer, and let number be that number.
 * 7. Let cue's text track cue text size be number.
 */
TEST_F(CueSettingSize, SingleDigitPercentage)
{
  loadVtt( "cue-settings/size/single-digit-pct.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 5, getCue( 0 ).sizePercentage() );
}

/**
 * Successfully parse a properly formatted single digit percentage 'size:9%'
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * If name is a case-sensitive match for "size"
 * 5. Ignoring the trailing percent sign, interpret value as an integer, and let number be that number.
 * 7. Let cue's text track cue text size be number.
 */
TEST_F(CueSettingSize, SingleDigitPercentageHighBoundary)
{
  loadVtt( "cue-settings/size/single-digit-pct-high-boundary.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 9, getCue( 0 ).sizePercentage() );
}

/**
 * Successfully parse a properly formatted single digit percentage 'size:0%'
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * If name is a case-sensitive match for "size"
 * 5. Ignoring the trailing percent sign, interpret value as an integer, and let number be that number.
 * 7. Let cue's text track cue text size be number.
 */
TEST_F(CueSettingSize, SingleDigitPercentageLowBoundary)
{
  loadVtt( "cue-settings/size/single-digit-pct-low-boundary.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 0, getCue( 0 ).sizePercentage() );
}

/**
 * Successfully parse a properly formatted double digit percentage 'size:100%'
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * If name is a case-sensitive match for "size"
 * 5. Ignoring the trailing percent sign, interpret value as an integer, and let number be that number.
 * 7. Let cue's text track cue text size be number.
 */
TEST_F(CueSettingSize, DoubleDigitPercentage)
{
  loadVtt( "cue-settings/size/double-digit-pct.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 54, getCue( 0 ).sizePercentage() );
}

/**
 * Successfully parse a properly formatted double digit percentage 'size:99%'
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * If name is a case-sensitive match for "size"
 * 5. Ignoring the trailing percent sign, interpret value as an integer, and let number be that number.
 * 7. Let cue's text track cue text size be number.
 */
TEST_F(CueSettingSize, DoubleDigitPercentageHighBoundary)
{
  loadVtt( "cue-settings/size/double-digit-pct-high-boundary.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 99, getCue( 0 ).sizePercentage() );
}

/**
 * Successfully parse a properly formatted double digit percentage 'size:00%'
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * If name is a case-sensitive match for "size"
 * 5. Ignoring the trailing percent sign, interpret value as an integer, and let number be that number.
 * 7. Let cue's text track cue text size be number.
 */
TEST_F(CueSettingSize, DoubleDigitPercentageLowBoundary)
{
  loadVtt( "cue-settings/size/double-digit-pct-low-boundary.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 0, getCue( 0 ).sizePercentage() );
}

/**
 * Successfully parse a properly formatted triple digit percentage 'size:555%'
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * If name is a case-sensitive match for "size"
 * 5. Ignoring the trailing percent sign, interpret value as an integer, and let number be that number.
 * 7. Let cue's text track cue text size be number.
 */
TEST_F(CueSettingSize, TripleDigitPercentage)
{
  loadVtt( "cue-settings/size/triple-digit-pct.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 55, getCue( 0 ).sizePercentage() );
}

/**
 * Successfully parse a properly formatted triple digit percentage 'size:999%'
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * If name is a case-sensitive match for "size"
 * 5. Ignoring the trailing percent sign, interpret value as an integer, and let number be that number.
 * 7. Let cue's text track cue text size be number.
 */
TEST_F(CueSettingSize, TripleDigitPercentageHighBoundary)
{
  loadVtt( "cue-settings/size/triple-digit-pct-high-boundary.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 100, getCue( 0 ).sizePercentage() );
}

/**
 * Successfully parse a properly formatted triple digit percentage 'size:000%'
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * If name is a case-sensitive match for "size"
 * 5. Ignoring the trailing percent sign, interpret value as an integer, and let number be that number.
 * 7. Let cue's text track cue text size be number.
 */
TEST_F(CueSettingSize, TripleDigitPercentageLowBoundary)
{
  loadVtt( "cue-settings/size/double-digit-pct-low-boundary.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 0, getCue( 0 ).sizePercentage() );
}

/**
 * Test that the parser requires a colon.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * 1. If setting does not contain a U+003A COLON character (:), or if the first U+003A COLON character (:) in setting is either the first or last character of setting, then jump to the step labeled next setting.
 * 5. Next setting: Continue to the next token, if any.
 */
TEST_F(CueSettingSize, NoDelimiter)
{
  loadVtt( "cue-settings/size/no-delimiter.vtt", 1 );
  const Error &err = getError( 0 );
  /**
   * Size should be 100 because the malformed setting should be skipped
     * and 100 is default.
   */
  ASSERT_EQ( 100, getCue( 0 ).sizePercentage() );
  /**
   * We're expecting a WEBVTT_MISSING_CUESETTING_DELIMITER error on the 29th column of the 3rd line
   */
  ASSERT_EQ( WEBVTT_MISSING_CUESETTING_DELIMITER, err.error() );
  ASSERT_EQ( 3, err.line() );
  ASSERT_EQ( 25, err.column() );
}

/**
 * Test that the parser does not allow a setting to start with a colon.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * 1. If setting does not contain a U+003A COLON character (:), or if the first U+003A COLON character (:) in setting is either the first or last character of setting, then jump to the step labeled next setting.
 * 5. Next setting: Continue to the next token, if any.
 */
TEST_F(CueSettingSize, NoKeyword)
{
  loadVtt( "cue-settings/size/no-keyword.vtt",  1 );
  const Error &err = getError( 0 );
  /**
   * Size should be 100 because the malformed setting should be skipped
     * and 100 is default.
   */
  ASSERT_EQ( 100, getCue( 0 ).sizePercentage() );
  /**
   * We're expecting a WEBVTT_INVALID_CUESETTING error on the 25th column of the 3rd line
   */
  ASSERT_EQ( WEBVTT_INVALID_CUESETTING, err.error() );
  ASSERT_EQ( 3, err.line() );
  ASSERT_EQ( 25, err.column() );
}

/**
 * Test that the parser does not allow a setting to end with a colon.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * 1. If setting does not contain a U+003A COLON character (:), or if the first U+003A COLON character (:) in setting is either the first or last character of setting, then jump to the step labeled next setting.
 * 5. Next setting: Continue to the next token, if any.
 */
TEST_F(CueSettingSize, NoValue)
{
  loadVtt( "cue-settings/size/no-value.vtt", 1 );
  const Error &err = getError( 0 );
  /**
   * Size should be 100 because the malformed setting should be skipped
     * and 100 is default.
   */
  ASSERT_EQ( 100, getCue( 0 ).sizePercentage() );
  /**
   * We're expecting a WEBVTT_SIZE_BAD_VALUE error on the 30th column of the 3rd line
   */
  ASSERT_EQ( WEBVTT_SIZE_BAD_VALUE, err.error() );
  ASSERT_EQ( 3, err.line() );
  ASSERT_EQ( 30, err.column() );
}

/**
 * Test that a percent sign is required.
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * If name is a case-sensitive match for "size"
 * 3. If any character in value other than the last character is a U+0025 PERCENT SIGN character (%), then jump to the step labeled next setting.
 */
TEST_F(CueSettingSize, NoPercentSign)
{
  loadVtt( "cue-settings/size/no-percent-sign.vtt", 1 );
  const Error &err = getError( 0 );
  /**
   * Size should be 100 because the malformed setting should be skipped
     * and 100 is default.
   */
  ASSERT_EQ( 100, getCue( 0 ).sizePercentage() );
  /**
   * We're expecting a WEBVTT_SIZE_BAD_VALUE error on the 30th column of the 3rd line
   */
  ASSERT_EQ( WEBVTT_SIZE_BAD_VALUE, err.error() );
  ASSERT_EQ( 3, err.line() );
  ASSERT_EQ( 30, err.column() );
}

/**
 * Test that the parser requires a colon.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * 1. If setting does not contain a U+003A COLON character (:), or if the first U+003A COLON character (:) in setting is either the first or last character of setting, then jump to the step labeled next setting.
 * 5. Next setting: Continue to the next token, if any.
 */
TEST_F(CueSettingSize, BadDelimiter)
{
  loadVtt( "cue-settings/size/bad-delimiter.vtt", 1 );
  const Error &err = getError( 0 );
  /**
   * We're expecting a WEBVTT_INVALID_CUESETTING error on the 25th column of the 3rd line
   * We can probably make this smarter, like WEBVTT_EXPECTED_CUESETTING_DELIMITER or something
   */
  ASSERT_EQ( 100, getCue( 0 ).sizePercentage() );
  /**
   * We're expecting a WEBVTT_INVALID_CUESETTING_DELIMITER error on the 29th column of the 3rd line
   */
  ASSERT_EQ( WEBVTT_INVALID_CUESETTING_DELIMITER, err.error() );
  ASSERT_EQ( 3, err.line() );
  ASSERT_EQ( 29, err.column() );
}

/**
 * Test that the parser does not change size if the keyword matches nothing.
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
TEST_F(CueSettingSize, BadKeyword)
{
  loadVtt( "cue-settings/size/bad-keyword.vtt", 1 );
  const Error &err = getError( 0 );
  /**
   * Size should be 100 because the malformed setting should be skipped
     * and 100 is default.
   */
  ASSERT_EQ( 100, getCue( 0 ).sizePercentage() );
  /**
   * We're expecting a WEBVTT_INVALID_CUESETTING error on the 25th column of the 3rd line
   */
  ASSERT_EQ( WEBVTT_INVALID_CUESETTING, err.error() );
  ASSERT_EQ( 3, err.line() );
  ASSERT_EQ( 29, err.column() );
}

/**
 * Test that a percent sign is required.
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * If name is a case-sensitive match for "size"
 * 1. If value contains any characters other than U+0025 PERCENT SIGN characters (%) and ASCII digits, then jump to the step labeled next setting.
 */
TEST_F(CueSettingSize, AsciiDigitBeyondHighBoundary)
{
  loadVtt( "cue-settings/size/above-0x39.vtt", 1 );
  const Error &err = getError( 0 );
  /**
   * Size should be 100 because the malformed setting should be skipped
     * and 100 is default.
   */
  ASSERT_EQ( 100, getCue( 0 ).sizePercentage() );
  /**
   * We're expecting a WEBVTT_SIZE_BAD_VALUE error on the 30th column of the 3rd line
   */
  ASSERT_EQ( WEBVTT_SIZE_BAD_VALUE, err.error() );
  ASSERT_EQ( 3, err.line() );
  ASSERT_EQ( 30, err.column() );
}

/**
 * Test that a percent sign is required.
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * If name is a case-sensitive match for "size"
 * 1. If value contains any characters other than U+0025 PERCENT SIGN characters (%) and ASCII digits, then jump to the step labeled next setting.
 */
TEST_F(CueSettingSize, AsciiDigitBeyondLowBoundary)
{
  loadVtt( "cue-settings/size/below-0x30.vtt", 1 );
  const Error &err = getError( 0 );
  /**
   * Size should be 100 because the malformed setting should be skipped
     * and 100 is default.
   */
  ASSERT_EQ( 100, getCue( 0 ).sizePercentage() );
  /**
   * We're expecting a WEBVTT_SIZE_BAD_VALUE error on the 30th column of the 3rd line
   */
  ASSERT_EQ( WEBVTT_SIZE_BAD_VALUE, err.error() );
  ASSERT_EQ( 3, err.line() );
  ASSERT_EQ( 30, err.column() );
}

/**
 * Test that negative values are not allowed.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * If name is a case-sensitive match for "size"
 *  6. If number is not in the range 0 <= number <= 100, then jump to the step labeled next setting.
 */
TEST_F(CueSettingSize, PercentNegative)
{
  loadVtt( "cue-settings/size/bad-pct-negative.vtt", 1 );
  const Error &err = getError( 0 );
  /**
   * Size should be 100 because the malformed setting should be skipped
     * and 100 is default.
   */
  ASSERT_EQ( 100, getCue( 0 ).sizePercentage() );
  /**
   * We're expecting a WEBVTT_SIZE_BAD_VALUE error on the 30th column of the 3rd line
   */
  ASSERT_EQ( WEBVTT_SIZE_BAD_VALUE, err.error() );
  ASSERT_EQ( 3, err.line() );
  ASSERT_EQ( 30, err.column() );
}

/**
 * Test that values over 100 are not allowed.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * If name is a case-sensitive match for "size"
 *  6. If number is not in the range 0 <= number <= 100, then jump to the step labeled next setting.
 */
TEST_F(CueSettingSize, PercentOver100)
{
  loadVtt( "cue-settings/size/bad-pct-over-100.vtt", 1 );
  const Error &err = getError( 0 );
  /**
   * Size should be 100 because the malformed setting should be skipped
     * and 100 is default.
   */
  ASSERT_EQ( 100, getCue( 0 ).sizePercentage() );
  /**
   * We're expecting a WEBVTT_SIZE_BAD_VALUE error on the 30th column of the 3rd line
   */
  ASSERT_EQ( WEBVTT_SIZE_BAD_VALUE, err.error() );
  ASSERT_EQ( 3, err.line() );
  ASSERT_EQ( 30, err.column() );
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
TEST_F(CueSettingSize, UppercaseKeyword)
{
  loadVtt( "cue-settings/size/uppercase-keyword.vtt", 1 );
  const Error &err = getError( 0 );
  /**
   * Size should be 100 because the malformed setting should be skipped
     * and 100 is default.
   */
  ASSERT_EQ( 100, getCue( 0 ).sizePercentage() );
  /**
   * We're expecting a WEBVTT_INVALID_CUESETTING error on the 25th column of the 3rd line
   */
  ASSERT_EQ( WEBVTT_INVALID_CUESETTING, err.error() );
  ASSERT_EQ( 3, err.line() );
  ASSERT_EQ( 25, err.column() );
}

