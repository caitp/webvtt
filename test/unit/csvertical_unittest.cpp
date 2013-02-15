#include "cue_testfixture"
class CueSettingVertical : public CueTest { };

/**
 * Verifies that the parser correctly parses a "vertical" key, followed by U+003A ':',
 * followed by 'rl' (indicating that the text be positioned vertically, and grows towards the left)
 *
 * This cue should have a Vertical orientation with direction RightToLeft
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 *  If name is a case-sensitive match for "vertical"
 *  1. If value is a case-sensitive match for the string "rl", then let cue's text track cue writing direction be vertical growing left.
 */
TEST_F(CueSettingVertical, RL)
{
  loadVtt( "cue-settings/vertical/rl.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_TRUE( getCue( 0 ).isVerticalRightToLeft() );
}

/**
 * Verifies that the parser correctly parses a "vertical" key, followed by U+003A ':',
 * followed by 'lr' (indicating that the text be positioned vertically, and grows towards the right)
 *
 * This cue should have a Vertical orientation with direction RightToLeft
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 *  If name is a case-sensitive match for "vertical"
 *  2. Otherwise, if value is a case-sensitive match for the string "lr", then let cue's text track cue writing direction be vertical growing right.
 */
TEST_F(CueSettingVertical, LR)
{
  loadVtt( "cue-settings/vertical/lr.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_TRUE( getCue( 0 ).isVerticalLeftToRight() );
}

/**
 * Test that the parser does not change vertical if the keyword matches nothing.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * 4. Run the appropriate substeps that apply for the value of name, as follows:
 *    If name is a case-sensitive match for "vertical" ...
 *    If name is a case-sensitive match for "line" ...
 *    If name is a case-sensitive match for "position" ...
 *    If name is a case-sensitive match for "size" ...
 *    If name is a case-sensitive match for "align" ...
 * 5. Next setting: Continue to the next token, if any.
 */
TEST_F(CueSettingVertical, BadKeyword)
{
  loadVtt( "cue-settings/vertical/bad-keyword.vtt", 1 );
  ASSERT_EQ( 1, errorCount() );

  /**
   * Writing direction should be horizontal because the malformed setting should
   * be skipped because horiztonal is default.
   */
  ASSERT_EQ( true, getCue( 0 ).isHorizontal() );

  /**
   * We're expecting a WEBVTT_INVALID_CUESETTING error on the 25th column of the
   * 3rd line
   */
  assertEquals( getError( 0 ), WEBVTT_INVALID_CUESETTING, 3, 25 );
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
TEST_F(CueSettingVertical, BadDelimiter)
{
  loadVtt ( "cue-settings/vertical/bad-delimiter.vtt", 1 );
  ASSERT_EQ( 1, errorCount() );

  /**
   * Writing direction should be horizontal because the malformed setting should
   * be skipped because horiztonal is default.
   */
  ASSERT_TRUE( getCue( 0 ).isHorizontal() );

  /**
   * We're expecting a WEBVTT_INVALID_CUESETTING error on the 25th column of the
   * 3rd line
   */
  assertEquals( getError( 0 ), WEBVTT_INVALID_CUESETTING, 3, 25 );
}

/**
 * Test what happens when there isn't a matching value for the setting vertical.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * 4. Run the appropriate substeps that apply for the value of name, as follows:
 * If name is a case-sensitive match for "vertical"
 * 1. If value is a case-sensitive match for the string "rl", ...
 * 2. Otherwise, if value is a case-sensitive match for the string "lr", ...
 * 5. Next setting: Continue to the next token, if any.
 */
TEST_F(CueSettingVertical, BadValue)
{
  loadVtt( "cue-settings/vertical/bad-value.vtt", 1 );
  const Error &err = getError( 0 );
  /**
   * Writing direction should be horizontal because the malformed setting should be skipped
     * because horiztonal is default.
   */
  ASSERT_EQ( 50, getCue( 0 ).isHorizontal() );
  /**
   * We're expecting a WEBVTT_VERTICAL_BAD_VALUE error on the 34th column of the 3rd line
   */
  ASSERT_EQ( WEBVTT_VERTICAL_BAD_VALUE, err.error() );
  ASSERT_EQ( 3, err.line() );
  ASSERT_EQ( 34, err.column() );
}

/**
 * Test that the parser does not allow a setting to start with a colon
 * and that it requires a colon in the other setting.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * 1. If setting does not contain a U+003A COLON character (:), or if the first
 *    U+003A COLON character (:) in setting is either the first or last character
 *    of setting, then jump to the step labeled next setting.
 * 5. Next setting: Continue to the next token, if any.
 */
TEST_F(CueSettingVertical, BadWhitespaceBeforeDelimiter)
{
  loadVtt( "cue-settings/vertical/bad-whitespace-before-delimiter.vtt", 1 );
  ASSERT_EQ( 1, errorCount() );

  /**
   * Writing direction should be horizontal because the malformed setting should
   * be skipped because horiztonal is default.
   */
  ASSERT_TRUE( getCue( 0 ).isVerticalLeftToRight() );
  
  /**
   * We're expecting a WEBVTT_UNEXPECTED_WHITESPACE error on the 33rd column of
   * the 3rd line
   */
  assertEquals( getError( 0 ), WEBVTT_UNEXPECTED_WHITESPACE, 3, 33 );
}

/**
 * Test that the parser does not allow a setting to end with a colon
 * and that it requires a colon in the other setting.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * 1. If setting does not contain a U+003A COLON character (:), or if the first
 *    U+003A COLON character (:) in setting is either the first or last character
 *    of setting, then jump to the step labeled next setting.
 * 5. Next setting: Continue to the next token, if any.
 */
TEST_F(CueSettingVertical, BadWhitespaceAfterDelimiter)
{
  loadVtt( "cue-settings/vertical/bad-whitespace-after-delimiter.vtt", 1 );
  ASSERT_EQ( 1, errorCount() );

  /**
   * Writing direction should be left-to-right because we are not skipping this
   * setting in this lenient run
   */
  ASSERT_TRUE( getCue( 0 ).isVerticalLeftToRight() );
 
  /**
   * We're expecting a WEBVTT_UNEXPECTED_WHITESPACE error on the 34th column of the
   * 3rd line
   */
  assertEquals( getError( 0 ), WEBVTT_UNEXPECTED_WHITESPACE, 3, 34 );
}

/**
 * Test that the parser does not allow a setting to start with a colon.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * 1. If setting does not contain a U+003A COLON character (:), or if the first
 *    U+003A COLON character (:) in setting is either the first or last character
 *    of setting, then jump to the step labeled next setting.
 * 5. Next setting: Continue to the next token, if any.
 */
TEST_F(CueSettingVertical, NoKeyword)
{
  loadVtt( "cue-settings/vertical/no-keyword.vtt", 1 );
  ASSERT_EQ( 1, errorCount() );

  /**
   * Writing direction should be horizontal because the malformed setting should
   * be skipped because horiztonal is default.
   */
  ASSERT_TRUE( getCue( 0 ).isHorizontal() );

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
 * 1. If setting does not contain a U+003A COLON character (:), or if the first
 *    U+003A COLON character (:) in setting is either the first or last character
 *    of setting, then jump to the step labeled next setting.
 * 5. Next setting: Continue to the next token, if any.
 */
TEST_F(CueSettingVertical, NoValue)
{
  loadVtt( "cue-settings/vertical/no-value.vtt", 1 );
  ASSERT_EQ( 1, errorCount() );

  /**
   * Writing direction should be horizontal because the malformed setting should
   * be skipped because horiztonal is default.
   */
  ASSERT_TRUE( getCue( 0 ).isHorizontal() );
 
  /**
   * We're expecting a WEBVTT_VERTICAL_BAD_VALUE error on the 34th column of the
   * 3rd line
   */
  assertEquals( getError( 0 ), WEBVTT_VERTICAL_BAD_VALUE, 3, 34 );
}

/**
 * Test that the parser requires a colon.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * 1. If setting does not contain a U+003A COLON character (:), or if the first U+003A COLON character (:) in setting is either the first or last character of setting, then jump to the step labeled next setting.
 * 5. Next setting: Continue to the next token, if any.
 */
TEST_F(CueSettingVertical, NoDelimiter)
{
  loadVtt( "cue-settings/vertical/no-delimiter.vtt", 1 );
  const Error &err = getError( 0 );
  /**
   * Writing direction should be horizontal because the malformed setting should be skipped
     * because horiztonal is default.
   */
  ASSERT_EQ( 50, getCue( 0 ).isHorizontal() );
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
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * 4. Run the appropriate substeps that apply for the value of name, as follows:
 *    If name is a case-sensitive match for "vertical" ...
 *    If name is a case-sensitive match for "line" ...
 *    If name is a case-sensitive match for "position" ...
 *    If name is a case-sensitive match for "size" ...
 *    If name is a case-sensitive match for "align" ...
 * 5. Next setting: Continue to the next token, if any.
 */
TEST_F(CueSettingVertical, UppercaseKeyword)
{
  loadVtt( "cue-settings/vertical/uppercase-keyword.vtt", 1 );
  ASSERT_EQ( 1, errorCount() );

  /**
   * Writing direction should be horizontal because the malformed setting should
   * be skipped because horiztonal is default.
   */
  ASSERT_TRUE( getCue( 0 ).isHorizontal() );

  /**
   * We're expecting a WEBVTT_INVALID_CUESETTING error on the 25th column of the
   * 3rd line
   */
  assertEquals( getError( 0 ), WEBVTT_INVALID_CUESETTING, 3, 25 );
}

/**
 * Test that that value is case-sensitive.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * 4. Run the appropriate substeps that apply for the value of name, as follows:
 * If name is a case-sensitive match for "vertical"
 * 1. If value is a case-sensitive match for the string "rl", ...
 * 2. Otherwise, if value is a case-sensitive match for the string "lr", ...
 * 5. Next setting: Continue to the next token, if any.
 */
TEST_F(CueSettingVertical, UppercaseValue)
{
  loadVtt( "cue-settings/vertical/uppercase-value.vtt", 1 );
  const Error &err = getError( 0 );
  /**
   * Writing direction should be horizontal because the malformed setting should be skipped
     * because horiztonal is default.
   */
  ASSERT_EQ( 50, getCue( 0 ).isHorizontal() );
  /**
   * We're expecting a WEBVTT_UNEXPECTED_WHITESPACE error on the 34th column of the 3rd line
   */
  ASSERT_EQ( WEBVTT_UNEXPECTED_WHITESPACE, err.error() );
  ASSERT_EQ( 3, err.line() );
  ASSERT_EQ( 34, err.column() );
}
