#include "cue_testfixture"
class CueSettingAlign : public CueTest { };

/**
 * Test properly formatted align start cue setting
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * If name is a case-sensitive match for "align"
 * If value is a case-sensitive match for the string "start", then let cue's text track cue alignment be start alignment.
 */
TEST_F(CueSettingAlign, Start)
{
  loadVtt( "cue-settings/align/start.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_TRUE( getCue( 0 ).isAlignedToStart() );
}

/**
 * Test properly formatted align middle cue setting
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * If name is a case-sensitive match for "align"
 * If value is a case-sensitive match for the string "middle", then let cue's text track cue alignment be middle alignment.
 */
TEST_F(CueSettingAlign, Middle)
{
  loadVtt( "cue-settings/align/middle.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_TRUE( getCue( 0 ).isAlignedToMiddle() );
}

/**
 * Test properly formatted align end cue setting
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * If name is a case-sensitive match for "align"
 * If value is a case-sensitive match for the string "end", then let cue's text track cue alignment be end alignment.
 */
TEST_F(CueSettingAlign, End)
{
  loadVtt( "cue-settings/align/end.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_TRUE( getCue( 0 ).isAlignedToEnd() );
}

/**
 * Test properly formatted align end cue setting
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * If name is a case-sensitive match for "align"
 * If value is a case-sensitive match for the string "left", then let cue's text track cue alignment be left alignment.
 */
TEST_F(CueSettingAlign, Left)
{
  loadVtt( "cue-settings/align/left.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_TRUE( getCue( 0 ).isAlignedToLeft() );
}

/**
 * Test properly formatted align end cue setting
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * If name is a case-sensitive match for "align"
 * If value is a case-sensitive match for the string "right", then let cue's text track cue alignment be right alignment.
 */
TEST_F(CueSettingAlign, Right)
{
  loadVtt( "cue-settings/align/right.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_TRUE( getCue( 0 ).isAlignedToRight() );
}

/**
 * Test that the parser does not change align if the keyword matches nothing.
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
TEST_F(CueSettingAlign, BadKeyword)
{
  loadVtt( "cue-settings/align/bad-keyword.vtt", 1 );
  const Error &err = getError( 0 );
  /**
   * Align should be "middle" because the malformed setting should be skipped
     * and "middle" is default.
   */
  ASSERT_TRUE( getCue( 0 ).isAlignedToMiddle() );
  /**
   * We're expecting a WEBVTT_INVALID_CUESETTING error on the 25th column of the 3rd line
   * We could return a smarter error, after a little bit of refactoring, perhaps.
   */
  ASSERT_EQ( WEBVTT_INVALID_CUESETTING, err.error() );
  ASSERT_EQ( 3, err.line() );
  ASSERT_EQ( 25, err.column() );
}

/**
 * Test that the parser does not allow a setting to start with a colon.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * 1. If setting does not contain a U+003A COLON character (:), or if the first U+003A COLON character (:) in setting is either the first or last character of setting, then jump to the step labeled next setting.
 * 5. Next setting: Continue to the next token, if any.
 */
TEST_F(CueSettingAlign, NoKeyword)
{
  loadVtt( "cue-settings/align/no-keyword.vtt", 1 );
  const Error &err = getError( 0 );
  /**
   * Align should be "middle" because the malformed setting should be skipped
     * and "middle" is default.
   */
  ASSERT_TRUE( getCue( 0 ).isAlignedToMiddle() );
  /**
   * We're expecting a WEBVTT_MISSING_CUESETTING_KEYWORD error on the 25th column of the 3rd line
   */
  ASSERT_EQ( WEBVTT_MISSING_CUESETTING_KEYWORD, err.error() );
  ASSERT_EQ( 3, err.line() );
  ASSERT_EQ( 25, err.column() );
}

/**
 * Test what happens when there isn't a matching value for the setting align.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * 4. Run the appropriate substeps that apply for the value of name, as follows:
 * If name is a case-sensitive match for "align"
 * 1. If value is a case-sensitive match for the string "start", ...
 * 2. If value is a case-sensitive match for the string "middle", ...
 * 3. If value is a case-sensitive match for the string "end", ...
 * 4. If value is a case-sensitive match for the string "left", ...
 * 5. If value is a case-sensitive match for the string "right", ...
 * 5. Next setting: Continue to the next token, if any.
 */
TEST_F(CueSettingAlign, BadValue)
{
  loadVtt( "cue-settings/align/bad-value.vtt", 1 );
  const Error &err = getError( 0 );
  /**
   * Align should be "middle" because the malformed setting should be skipped
     * and "middle" is default.
   */
  ASSERT_TRUE( getCue( 0 ).isAlignedToMiddle() );
  /**
   * We're expecting a WEBVTT_ALIGN_BAD_VALUE error on the 31st column of the 3rd line
   */
  ASSERT_EQ( WEBVTT_ALIGN_BAD_VALUE, err.error() );
  ASSERT_EQ( 3, err.line() );
  ASSERT_EQ( 31, err.column() );
}

/**
 * Test that the parser does not allow a setting to end with a colon.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * 1. If setting does not contain a U+003A COLON character (:), or if the first U+003A COLON character (:) in setting is either the first or last character of setting, then jump to the step labeled next setting.
 * 5. Next setting: Continue to the next token, if any.
 */
TEST_F(CueSettingAlign, NoValue)
{
  loadVtt( "cue-settings/align/no-value.vtt", 1 );
  const Error &err = getError( 0 );
  /**
   * Align should be "middle" because the malformed setting should be skipped
     * and "middle" is default.
   */
  ASSERT_TRUE( getCue( 0 ).isAlignedToMiddle() );
  /**
   * We're expecting a WEBVTT_ALIGN_BAD_VALUE error on the 31st column of the 3rd line
   */
  ASSERT_EQ( WEBVTT_ALIGN_BAD_VALUE, err.error() );
  ASSERT_EQ( 3, err.line() );
  ASSERT_EQ( 31, err.column() );
}

/**
 * Test that the parser requires a colon.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * 1. If setting does not contain a U+003A COLON character (:), or if the first U+003A COLON character (:) in setting is either the first or last character of setting, then jump to the step labeled next setting.
 * 5. Next setting: Continue to the next token, if any.
 */
TEST_F(CueSettingAlign, BadDelimiter)
{
  loadVtt( "cue-settings/align/bad-delimiter.vtt", 1 );
  const Error &err = getError( 0 );
  /**
   * Align should be "middle" because the malformed setting should be skipped
     * and "middle" is default.
   */
  ASSERT_TRUE( getCue( 0 ).isAlignedToMiddle() );
  /**
   * We're expecting a WEBVTT_INVALID_CUESETTING_DELIMITER error on the 30th column of the 3rd line
   */
  ASSERT_EQ( WEBVTT_INVALID_CUESETTING_DELIMITER, err.error() );
  ASSERT_EQ( 3, err.line() );
  ASSERT_EQ( 30, err.column() );
}

/**
 * Test that the parser requires a colon.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * 1. If setting does not contain a U+003A COLON character (:), or if the first U+003A COLON character (:) in setting is either the first or last character of setting, then jump to the step labeled next setting.
 * 5. Next setting: Continue to the next token, if any.
 */
TEST_F(CueSettingAlign, NoDelimiter)
{
  loadVtt( "cue-settings/align/no-delimiter.vtt", 1 );
  const Error &err = getError( 0 );
  /**
   * Align should be "middle" because the malformed setting should be skipped
     * and "middle" is default.
   */
  ASSERT_TRUE( getCue( 0 ).isAlignedToMiddle() );
  /**
   * We're expecting a WEBVTT_INVALID_CUESETTING error on the 25th column of the 3rd line
   */
  ASSERT_EQ( WEBVTT_INVALID_CUESETTING, err.error() );
  ASSERT_EQ( 3, err.line() );
  ASSERT_EQ( 25, err.column() );
}

/**
 * Test that the keyword is case-sensitive.
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
TEST_F(CueSettingAlign, UppercaseKeyword)
{
  loadVtt( "cue-settings/align/uppercase-keyword.vtt", 1 );
  const Error &err = getError( 0 );
  /**
   * Align should be "middle" because the malformed setting should be skipped
     * and "middle" is default.
   */
  ASSERT_TRUE( getCue( 0 ).isAlignedToMiddle() );
  /**
   * We're expecting a WEBVTT_INVALID_CUESETTING error on the 25th column of the 3rd line
   */
  ASSERT_EQ( WEBVTT_MISSING_CUESETTING_DELIMITER, err.error() );
  ASSERT_EQ( 3, err.line() );
  ASSERT_EQ( 30, err.column() );
}

/**
 * Test that that value is case-sensitive.
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
TEST_F(CueSettingAlign, UppercaseValue)
{
  loadVtt( "cue-settings/align/uppercase-value.vtt", 1 );
  const Error &err = getError( 0 );
  /**
   * Align should be "middle" because the malformed setting should be skipped
     * and "middle" is default.
   */
  ASSERT_TRUE( getCue( 0 ).isAlignedToMiddle() );
  /**
   * We're expecting a WEBVTT_ALIGN_BAD_VALUE error on the 31st column of the 3rd line
   */
  ASSERT_EQ( WEBVTT_ALIGN_BAD_VALUE, err.error() );
  ASSERT_EQ( 3, err.line() );
  ASSERT_EQ( 31, err.column() );
}
