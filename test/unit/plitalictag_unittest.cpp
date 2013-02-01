#include "payload_testfixture"
class PayloadItalicTag : public PayloadTest {};

/*
 * Verifies that a italic cue text tag is parsed correctly.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-italics-span (11/27/2012)
 *  Italic tags consist of:
 *    1. A cue span start tag "i" that disallows an annotation.
 *    2. Possible cue internal text representing the italicized text.
 *    3. A cue span end tag.
 */
TEST_F(PayloadItalicTag, ItalicTag)
{
  loadVtt( "payload/i-tag/i-tag.vtt" );

  const InternalNode *head = getHeadOfCue( 0 );

  ASSERT_TRUE( head->childCount() == 3 );
  ASSERT_EQ( Node::Italic, head->child( 1 )->kind() );
}

/*
 * Verifies that a italic tag with an annotation is parsed correctly but does not contain the annotation.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-italics-span (11/27/2012)
 *  Italic tags consist of:
 *    1. A cue span start tag "i" that disallows an annotation.
 *    2. Possible cue internal text representing the italicized text.
 *    3. A cue span end tag.
 */
TEST_F(PayloadItalicTag, ItalicAnnotation)
{
  loadVtt( "payload/i-tag/i-tag-annotation.vtt" );

  const InternalNode *head = getHeadOfCue( 0 );

  ASSERT_TRUE( head->childCount() == 3 );
  ASSERT_EQ( Node::Italic, head->child( 1 )->kind() );
  ASSERT_TRUE( head->child( 1 )->toInternalNode()->annotation().text() == NULL );
}

/*
 * Verifies that a single subclass can be attached to a cue text italic start tag.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-span-start-tag (11/27/2012)
 *  Cue span start tags consist of the following:
 *    1. A "<" character representing the beginning of the start tag.
 *    2. The tag name.
 *    3. Zero or more the following sequence representing a subclasses of the start tag
 *      3.1. A full stop "." character.
 *      3.2. A sequence of non-whitespace characters.
 *    4. If the start tag requires an annotation then a space or tab character followed by a sequence of
 *       non-whitespace characters representing the annotation.
 *    5. A ">" character repsenting the end of the start tag.
 */
TEST_F(PayloadItalicTag, ItalicTagSingleSubclass)
{
  loadVtt( "payload/i-tag/i-tag-single-subclass.vtt" );

  const InternalNode *head = getHeadOfCue( 0 );

  ASSERT_TRUE( head->childCount() == 3 );
  ASSERT_EQ( Node::Italic, head->child( 1 )->kind() );

  StringList cssClasses = head->child( 1 )->toInternalNode()->cssClasses();
  String expectedString = String( (const byte *)"class", 5 );

  ASSERT_TRUE( cssClasses.length() == 1 );
  ASSERT_EQ(  expectedString.text(), cssClasses.stringAt( 0 ).text() );
}

/*
 * Verifies that multiple subclasses can be attached to a cue text italic start tag.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-span-start-tag (11/27/2012)
 *  Cue span start tags consist of the following:
 *    1. A "<" character representing the beginning of the start tag.
 *    2. The tag name.
 *    3. Zero or more the following sequence representing a subclasses of the start tag
 *      3.1. A full stop "." character.
 *      3.2. A sequence of non-whitespace characters.
 *    4. If the start tag requires an annotation then a space or tab character followed by a sequence of
 *       non-whitespace characters representing the annotation.
 *    5. A ">" character repsenting the end of the start tag.
 */
TEST_F(PayloadItalicTag, ItalicTagMultiSubclass)
{
  loadVtt( "payload/i-tag/i-tag-multi-subclass.vtt" );

  const InternalNode *head = getHeadOfCue( 0 );

  ASSERT_TRUE( head->childCount() == 3 );
  ASSERT_EQ( Node::Italic, head->child( 1 )->kind() );

  StringList cssClasses = head->child( 1 )->toInternalNode()->cssClasses();
  String expectedString = String( (const byte *)"class", 5 );

  ASSERT_TRUE( cssClasses.length() == 1 );
  ASSERT_EQ(  expectedString.text(), cssClasses.stringAt( 0 ).text() );

  expectedString = String( (const byte *)"subclass", 8 );
  ASSERT_EQ( expectedString.text(), cssClasses.stringAt( 1 ).text() );
}
