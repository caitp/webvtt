#include "payload_testfixture"
class PayloadFormat : public PayloadTest {};

/*
 * Verifies that a cue text span with no tags will parse correctly.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-text-span (11/27/2012)
 */
TEST_F(PayloadFormat, BasicCueText)
{
  loadVtt( "payload/payload-format/basic-cue-text.vtt", 1 );
  ASSERT_EQ( Node::Text, getHeadOfCue( 0 )->child( 0 )->kind() );
}

/*
 * Verifies that multiple cue components can be put in one line.
 * http://dev.w3.org/html5/webvtt/#webvtt-cue-components
 */
TEST_F(PayloadFormat, MultipleCueTextTag)
{
  loadVtt( "payload/payload-format/multiple-cue-tag.vtt", 1 );
  ASSERT_TRUE( getHeadOfCue( 0 )->toInternalNode()->childCount() == 5 );
}

/*
 * Verifies that multiple cue components can be put in one line, one after
 * the other.
 * http://dev.w3.org/html5/webvtt/#webvtt-cue-components
 */
TEST_F(PayloadFormat, MultipleCueTextTagTogether)
{
  loadVtt( "payload/payload-format/multiple-cue-tag-together.vtt", 1 );
  ASSERT_TRUE( getHeadOfCue( 0 )->toInternalNode()->childCount() == 5 );
}

/*
 * Verifies that a cue text span with multiple lines will work.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-text (11/27/2012)
 *  Cue text text consists of one or more cue text components optionally separated by a single line terminator which can be:
 *    1. CR (U+000D)
 *    2. LF (U+000A)
 *    3. CRLF pair
 */
TEST_F(PayloadFormat, MultilineBasicCueText)
{
  loadVtt( "payload/payload-format/multiline-basic-cue-text.vtt", 1 );
  ASSERT_EQ( Node::Text, getHeadOfCue( 0 )->child( 0 )->kind() );
}

/*
 * Verifies that cue text with single line feed characters will be parsed.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-text (11/27/2012)
 *  Cue text text consists of one or more cue text components optionally separated by a single line terminator which can be:
 *    1. CR (U+000D)
 *    2. LF (U+000A)
 *    3. CRLF pair
 */
TEST_F(PayloadFormat, MultilineCueText)
{
  loadVtt( "payload/payload-format/multiline-cue-text.vtt", 1 );
  ASSERT_TRUE( getHeadOfCue( 0 )->toInternalNode()->childCount() == 4 );
}

/*
 * Verifies that cue text with single carriage return characters will be parsed.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-text (11/27/2012)
 *  Cue text text consists of one or more cue text components optionally separated by a single line terminator which can be:
 *    1. CR (U+000D)
 *    2. LF (U+000A)
 *    3. CRLF pair
 */
TEST_F(PayloadFormat, MultilineCueTextCR)
{
  loadVtt( "payload/payload-format/multiline-cue-text-cr.vtt", 1 );
  ASSERT_TRUE( getHeadOfCue( 0 )->toInternalNode()->childCount() == 4 );
}

/*
 * Verifies that cue text with single CRLF pair characters will be parsed.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-text (11/27/2012)
 *  Cue text text consists of one or more cue text components optionally separated by a single line terminator which can be:
 *    1. CR (U+000D)
 *    2. LF (U+000A)
 *    3. CRLF pair
 */
TEST_F(PayloadFormat, MultilineCueTextCRLF)
{
  loadVtt( "payload/payload-format/multiline-cue-text-crlf.vtt", 1 );
  ASSERT_TRUE( getHeadOfCue( 0 )->toInternalNode()->childCount() == 4 );
}

/*
 * Verifies that a file with payload text containing a line feed in between the text
 * will finish the parsing attempt gracefully.
 * From http://dev.w3.org/html5/webvtt/#parsing (12/10/2012):
 *
 * ...
 * 50. Bad cue: Discard cue.
 * 51. Bad cue loop: If position is past the end of input, then jump to the step labeled end.
 */
TEST_F(PayloadFormat, MultilineCueTextExtraNewline)
{
  loadVtt( "payload/payload-format/multiline-cue-text-extra-newline.vtt", 1 );
  ASSERT_TRUE( getHeadOfCue( 0 )->toInternalNode()->childCount() == 2 );
}

/*
 * Verifies that a file with payload text containing a carriage return in between the text
 * will finish the parsing attempt gracefully.
 * From http://dev.w3.org/html5/webvtt/#parsing (12/10/2012):
 *
 * ...
 * 50. Bad cue: Discard cue.
 * 51. Bad cue loop: If position is past the end of input, then jump to the step labeled end.
 */
TEST_F(PayloadFormat, MultilineCueTextExtraNewlineCR)
{
  loadVtt( "payload/payload-format/multiline-cue-text-extra-newline-cr.vtt", 1 );
  ASSERT_TRUE( getHeadOfCue( 0 )->toInternalNode()->childCount() == 2 );
}

/*
 * Verifies that a file with payload text containing a CRLF pair in between the text
 * will finish the parsing attempt gracefully.
 * From http://dev.w3.org/html5/webvtt/#parsing (12/10/2012):
 *
 * ...
 * 50. Bad cue: Discard cue.
 * 51. Bad cue loop: If position is past the end of input, then jump to the step labeled end.
 */
TEST_F(PayloadFormat, MultilineCueTextExtraNewlineCRLF)
{
  loadVtt( "payload/payload-format/multiline-cue-text-extra-newline-crlf.vtt", 1 );
  ASSERT_TRUE( getHeadOfCue( 0 )->toInternalNode()->childCount() == 2 );
}

/*
 * Verifies that multiple cue component are parsed correctly.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-text (11/27/2012)
 *  Cue text text consists of one or more cue text components optionally separated by a single line terminator which can be:
 *    1. CR (U+000D)
 *    2. LF (U+000A)
 *    3. CRLF pair
 */
TEST_F(PayloadFormat, MultilineMultipleCueTextTag)
{
  loadVtt( "payload/payload-format/multiline-multiple-cue-text-tag.vtt" );

  const InternalNode *node = getHeadOfCue( 0 );
  ASSERT_EQ( Node::Underline, node->kind() );

  node = node->child( 0 )->toInternalNode();
  ASSERT_EQ( Node::Italic, node->kind() );

  node = node->child( 0 )->toInternalNode();
  ASSERT_EQ( Node::Bold, node->kind() );
}

/*
 * WebVTT Escape Character Specification being Tested:
 *
 * U+003B SEMICOLON character (;)
 *  First, examine the value of buffer:
 *  If buffer is the string "&amp", then append a U+0026 AMPERSAND character (&) to result.
 *  If buffer is the string "&lt", then append a U+003C LESS-THAN SIGN character (<) to result.
 *  If buffer is the string "&gt", then append a U+003E GREATER-THAN SIGN character (>) to result.
 *  If buffer is the string "&lrm", then append a U+200E LEFT-TO-RIGHT MARK character to result.
 *  If buffer is the string "&rlm", then append a U+200F RIGHT-TO-LEFT MARK character to result.
 *  If buffer is the string "&nbsp", then append a U+00A0 NO-BREAK SPACE character to result.
 *  Otherwise, append buffer followed by a U+003B SEMICOLON character (;) to result.
 *  Then, in any case, set tokenizer state to the WebVTT data state, and jump to the step labeled next.
 *
*/

/*
 WebVTT - Living Standard Last Updated 2 October 2012

 Relates to:
 Cue Text Escape Characters and Cue Text Tags:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 cue text to be parsed: <i>Test Ampersand escape within i tag: &amp; </i>
 correct Ampersand Character Escape : within a cue i tag
*/
TEST_F(PayloadFormat, AmpersandWithinTag)
{
  loadVtt( "payload/escape-character/i-tag-with-ampersand.vtt", 1 );

  const InternalNode *node = getHeadOfCue(0);

  /* Check to see if the Italic node has been correctly formed */
  ASSERT_EQ( Node::Italic, node->kind() );

  /* verify the text within the i tag */
  const TextNode *textNode = getHeadOfCue( 0 )->child( 0 )->toInternalNode()->child(0)->toTextNode();
  String expectedText = String( (const byte *)"Test Ampersand escape within i tag: &amp;", 40 );
  ASSERT_EQ( expectedText.text(), textNode->content().text() );
}
/*
 Version:
 WebVTT - Living Standard Last Updated 2 October 2012

 Relates To:
 Cue Text Escape Characters and Cue Text Tags:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Cue Text to be Parsed: <b><i>Test Ampersand escape within i tag: &amp; </i></b>
 correct Ampersand Character Escape : cue b tag within a cue i tag
*/
TEST_F(PayloadFormat, AmpersandWithinMultipleTags)
{
  loadVtt( "payload/escape-character/i-tag-within-b-tag-with-ampersand.vtt", 1 );

  /* verify bold tag */
  const InternalNode *boldTag = getHeadOfCue(0);
  ASSERT_EQ(Node::Bold, boldTag->kind() );

  /* verify italic tag within bold tag */
  const InternalNode *italicTag = getHeadOfCue(0)->child(0)->toInternalNode();
  ASSERT_EQ(Node::Italic, italicTag->kind() );

  /* verify the text within the italic tag */
  const TextNode *textNode = getHeadOfCue( 0 )->child( 0 )->toInternalNode()->child(0)->toInternalNode()->child(0)->toTextNode();
  String expectedText = String( (const byte *)"Test Ampersand escape within i tag: &amp; ", 40 );
  ASSERT_EQ( expectedText.text(), textNode->content().text() );
}
/*
 Version:
 WebVTT - Living Standard Last Updated 2 October 2012

  Relates To:
  Cue Text Escape Characters and Cue Text Tags:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Cue Text to be Parsed: <b><i> some filler text </i></b> &amp;
 correct Ampersand Character Escape outside cue b tag within a cue i tag
*/
TEST_F(PayloadFormat, AmpersandOutsideTwoTags)
{
  loadVtt( "payload/escape-character/i-tag-within-b-tag-with-ampersand-outside.vtt", 1 );

  /* verify bold tag */
  const InternalNode *boldTag = getHeadOfCue(0);
  ASSERT_EQ(Node::Bold, boldTag->kind() );

  /* verify italic tag within bold tag */
  const InternalNode *italicTag = getHeadOfCue(0)->child(0)->toInternalNode();
  ASSERT_EQ(Node::Italic, italicTag->kind() );

  /* verify the escape character text within the i tag */
  const TextNode *textNode = getHeadOfCue( 0 )->child( 1 )->toTextNode();
  String expectedText = String( (const byte *)" &amp;", 6 );
  ASSERT_EQ( expectedText.text(), textNode->content().text() );
}
/*
 Version:
 WebVTT - Living Standard Last Updated 2 October 2012

 Relates To:
 Cue Text Escape Characters and Cue Text Tags:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Cue Text to be Parsed:
 <i.class> Some Filler Text </i>
 &amp;
 correct Ampersand Character Escape on new line after two encapsulated tags with class
*/
TEST_F(PayloadFormat, AmpersandOnNewLineAfterTwoTagsWithClass)
{
  loadVtt( "payload/escape-character/ampersand-outside-tag-on-newline-with-class.vtt", 1 );

  /* verify italic tag */
  const InternalNode *italicTag = getHeadOfCue(0);
  ASSERT_EQ(Node::Italic, italicTag->kind() );

  /* verify class inside italic tag*/
  StringList cssClass = getHeadOfCue(0)->child(0)->toInternalNode()->cssClasses();
  String cssClassExpected = String((const byte *)"class", 5);
  ASSERT_EQ(cssClassExpected.text(), cssClass.stringAt(0).text());

  /* verify the escape character text within i tag */
  const TextNode *textNode = getHeadOfCue( 0 )->child( 1 )->toTextNode();
  String expectedText = String( (const byte *)"&amp;", 5 );
  ASSERT_EQ( expectedText.text(), textNode->content().text() );
}
/*
 Version:
 WebVTT - Living Standard Last Updated 2 October 2012

  Relates To:
  Cue Text Escape Characters and Cue Text Tags:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Cue Text to be Parsed: <i.class> ampersand escape: &amp; </i>
 correct Ampersand Character Escape inside tag with a class
*/
TEST_F(PayloadFormat, AmpersandInsideOneTagWithClass)
{
  loadVtt( "payload/escape-character/ampersand-within-tag-with-class.vtt", 1 );

  /* verify italic tag */
  const InternalNode *italicTag = getHeadOfCue(0);
  ASSERT_EQ(Node::Italic, italicTag->kind() );

  /* verify class inside italic tag*/
  StringList cssClass = getHeadOfCue(0)->child(0)->toInternalNode()->cssClasses();
  String cssClassExpected = String((const byte *)"class", 5);
  ASSERT_EQ(cssClassExpected.text(), cssClass.stringAt(0).text());

  /* verify escape character text within i tag */
  const TextNode *textNode = getHeadOfCue( 0 )->child( 0 )->toInternalNode()->child( 0 )->toTextNode();
  String expectedText = String( (const byte *)" ampersand escape: &amp; ", 25 );
  ASSERT_EQ( expectedText.text(), textNode->content().text() );
}
/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012

  Relates To:
  Cue Text Escape Characters and Cue Text Tags:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Cue Text to be Parsed:
 <b><i> some filler text </i></b>
 &amp;
 correct Ampersand Character Escape outside two encapsulates tags
*/
TEST_F(PayloadFormat, AmpersandInsideTagWithSubclasses)
{
  loadVtt( "payload/escape-character/ampersand-outside-encapsulated-tags.vtt", 1 );

  /* verify bold tag */
  const InternalNode *boldTag = getHeadOfCue(0);
  ASSERT_EQ(Node::Bold, boldTag->kind() );

  /* verify italic tag within bold tag */
  const InternalNode *italicTag = getHeadOfCue(0)->child(0)->toInternalNode();
  ASSERT_EQ(Node::Italic, italicTag->kind() );

  /* verify character escape outside i tag */
  const TextNode *textNode = getHeadOfCue( 0 )->child( 1 )->toTextNode();
  String expectedText = String( (const byte *)"&amp;", 5 );
  ASSERT_EQ( expectedText.text(), textNode->content().text() );
}
/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012

 Relates To:
 Cue Text Escape Characters and Cue Text Tags:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Cue Text to be Parsed: <i.class.subclass> ampersand escape: &amp; </i>
 correct Ampersand Character Escape on line after a tag with a class
 and subclass
*/
TEST_F(PayloadFormat, AmpersandOnLineWithClassAndSubClass)
{
  loadVtt( "payload/escape-character/ampersand-inside-tag-with-subclass.vtt", 1 );

  /* verify italic tag */
  const InternalNode *italicTag = getHeadOfCue(0);
  ASSERT_EQ(Node::Italic, italicTag->kind() );

  /* verify class inside italic tag*/
  StringList cssClass = getHeadOfCue(0)->child(0)->toInternalNode()->cssClasses();
  String cssClassExpected = String((const byte *)"class", 5);
  ASSERT_EQ(cssClassExpected.text(), cssClass.stringAt(0).text());

  /* verify subclass within the i tag */
  String cssSubClassExpected = String((const byte *)"subclass", 8);
  ASSERT_EQ(cssSubClassExpected.text(), cssClass.stringAt(1).text());

  /* verify escape character text within i tag*/
  const TextNode *textNode = getHeadOfCue( 0 )->child( 0 )->toTextNode();
  String expectedText = String( (const byte *)" ampersand escape: &amp; ", 25 );
  ASSERT_EQ( expectedText.text(), textNode->content().text() );
}
/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012

  Relates To:
  Cue Text Escape Characters and Cue Text Tags:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Cue Text To be Parsed:
 <i.class.subclass> Some Filler Text </i>
 &amp;
 correct Ampersand Character Escape on new line after a tag with a class
 and subclass
*/
TEST_F(PayloadFormat, AmpersandOnNewlineWithClassAndSubclass)
{
  loadVtt( "payload/escape-character/ampersand-outside-tag-on-newline-with-subclass.vtt", 1 );

  /* verify italic tag */
  const InternalNode *italicTag = getHeadOfCue(0);
  ASSERT_EQ(Node::Italic, italicTag->kind() );

  /* verify class inside italic tag*/
  StringList cssClass = getHeadOfCue(0)->child(0)->toInternalNode()->cssClasses();
  String cssClassExpected = String((const byte *)"class", 5);
  ASSERT_EQ(cssClassExpected.text(), cssClass.stringAt(0).text());

  /* verify subclass within the i tag */
  String cssSubClassExpected = String((const byte *)"subclass", 8);
  ASSERT_EQ(cssSubClassExpected.text(), cssClass.stringAt(1).text());

  /* verify character escape outside i tag */
  const TextNode *textNode = getHeadOfCue( 0 )->child( 1 )->toTextNode();
  String expectedText = String( (const byte *)"&amp;", 5 );
  ASSERT_EQ( expectedText.text(), textNode->content().text() );
}
/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012

  Relates To:
  Cue Text Escape Characters and Cue Text Tags:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Cue Text To be Parsed: <i.class.subclass> Some Filler Text </i> &amp;
 correct Ampersand Character Escape on line outsidetag with a class
 and subclass
*/
TEST_F(PayloadFormat, AmpersandOnCurrlineWithClassAndSubclass)
{
  loadVtt( "payload/escape-character/ampersand-outside-tag-on-newline-with-subclass.vtt", 1 );

  /* verify italic tag */
  const InternalNode *italicTag = getHeadOfCue(0);
  ASSERT_EQ(Node::Italic, italicTag->kind() );

  /* verify class inside italic tag*/
  StringList cssClass = getHeadOfCue(0)->child(0)->toInternalNode()->cssClasses();
  String cssClassExpected = String((const byte *)"class", 5);
  ASSERT_EQ(cssClassExpected.text(), cssClass.stringAt(0).text());

  /* verify subclass within the i tag */
  String cssSubClassExpected = String((const byte *)"subclass", 8);
  ASSERT_EQ(cssSubClassExpected.text(), cssClass.stringAt(1).text());

  /* verify character escape outside i tag */
  const TextNode *textNode = getHeadOfCue( 0 )->child( 1 )->toTextNode();
  String expectedText = String( (const byte *)" &amp;", 6 );
  ASSERT_EQ( expectedText.text(), textNode->content().text() );
}
/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012

  Relates To:
  Cue Text Escape Characters and Cue Text Tags:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Cue Text To be Parsed: <i.class> Some Filler Text </i> &amp;
 correct Ampersand Character Escape on line outsidetag with a class
 and subclass
*/
TEST_F(PayloadFormat, AmpersandOnCurrlineWithClass)
{
  loadVtt( "payload/escape-character/ampersand-outside-tag-on-newline-with-subclass.vtt", 1 );

  /* verify italic tag */
  const InternalNode *italicTag = getHeadOfCue(0);
  ASSERT_EQ(Node::Italic, italicTag->kind() );

  /* verify class inside italic tag*/
  StringList cssClass = getHeadOfCue(0)->child(0)->toInternalNode()->cssClasses();
  String cssClassExpected = String((const byte *)"class", 5);
  ASSERT_EQ(cssClassExpected.text(), cssClass.stringAt(0).text());

  /* verify character escape outside i tag */
  const TextNode *textNode = getHeadOfCue( 0 )->child( 1 )->toTextNode();
  String expectedText = String( (const byte *)" &amp;", 6 );
  ASSERT_EQ( expectedText.text(), textNode->content().text() );
}

/*
 * Verifies that cue text separated by a CR line terminator is parsed correctly.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-text (12/02/2012)
 *  Cue text consists of one or more cue text components optionally separated by a single line terminator which can be:
 *    1. CR (U+000D)
 *    2. LF (U+000A)
 *    3. CRLF pair
 */
TEST_F(PayloadFormat, MultilineBasicCueTextCR)
{
  loadVtt( "payload/payload-format/multiline-basic-cue-text-cr.vtt" );
  ASSERT_EQ( Node::Text, getHeadOfCue( 0 )->child( 0 )->kind() );
}

/*
 * Verifies that cue text separated by a CRLF line terminator is parsed correctly.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-text (12/02/2012)
 *  Cue text consists of one or more cue text components optionally separated by a single line terminator which can be:
 *    1. CR (U+000D)
 *    2. LF (U+000A)
 *    3. CRLF pair
 */
TEST_F(PayloadFormat, MultilineBasicCueTextCRLF)
{
  loadVtt( "payload/payload-format/multiline-basic-cue-text-crlf.vtt" );
  ASSERT_EQ( Node::Text, getHeadOfCue( 0 )->child( 0 )->kind() );
}

/* Verifies that cue text with a malformed line terminator is still parsed correctly.
 * From http://dev.w3.org/html5/webvtt/#webvtt-parser-algorithm (12/02/2012)
 * The WebVTT parser algorithm is as follows:
 * [...] 50. Bad cue: Discard cue.
 */
TEST_F(PayloadFormat, MultilineBasicCueTextExtraLine)
{
  loadVtt( "payload/payload-format/multiline-extra-line-terminator.vtt", 1);
  ASSERT_EQ( Node::Text, getHeadOfCue( 0 )->child( 0 )->kind() );
}
