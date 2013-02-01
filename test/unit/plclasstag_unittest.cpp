#include "payload_testfixture"
class PayloadClassTag : public PayloadTest {};

/*
 * Verifies that a class cue text tag is parsed correctly.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-class-span (11/27/2012)
 *  Class tags consist of:
 *    1. A cue span start tag "c" that disallows an annotation.
 *    2. Possible cue internal text representing the cue text.
 *    3. A cue span end tag.
 */
TEST_F(PayloadClassTag, ClassTag)
{
  loadVtt( "payload/c-tag/c-tag.vtt" );

  const InternalNode *head = getHeadOfCue( 0 );

  ASSERT_TRUE( head->childCount() == 3 );
  ASSERT_EQ( Node::Class, head->child( 1 )->kind() );
}

/*
 * Verifies that a class tag with an annotation is parsed correctly but does not contain the annotation.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-class-span (11/27/2012)
 *  Class tags consist of:
 *    1. A cue span start tag "c" that disallows an annotation.
 *    2. Possible cue internal text representing the cue text.
 *    3. A cue span end tag.
 */
TEST_F(PayloadClassTag, ClassTagAnnotation)
{
  loadVtt( "payload/c-tag/c-tag-annotation.vtt" );

  const InternalNode *head = getHeadOfCue( 0 );

  ASSERT_TRUE( head->childCount() == 3 );
  ASSERT_EQ( Node::Class, head->child( 1 )->kind() );
  ASSERT_TRUE( head->child( 1 )->toInternalNode()->annotation().text() == NULL );
}

/*
 * Verifies that a single subclass can be attached to a cue text class start tag.
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
TEST_F(PayloadClassTag, ClassTagSingleSubclass)
{
  loadVtt( "payload/c-tag/c-tag-single-subclass.vtt" );

  const InternalNode *head = getHeadOfCue( 0 );

  ASSERT_TRUE( head->childCount() == 3 );
  ASSERT_EQ( Node::Class, head->child( 1 )->kind() );

  StringList cssClasses = head->child( 1 )->toInternalNode()->cssClasses();
  String expectedString = String( (const byte *)"class", 5 );

  ASSERT_TRUE( cssClasses.length() == 1 );
  ASSERT_EQ(  expectedString.text(), cssClasses.stringAt( 0 ).text() );
}

/*
 * Verifies that multiple subclasses can be attached to a cue text class start tag.
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
TEST_F(PayloadClassTag, ClassTagMultiSubclass)
{
  loadVtt( "payload/c-tag/c-tag-multi-subclass.vtt" );

  const InternalNode *head = getHeadOfCue( 0 );

  ASSERT_TRUE( head->childCount() == 3 );
  ASSERT_EQ( Node::Class, head->child( 1 )->kind() );

  StringList cssClasses = head->child( 1 )->toInternalNode()->cssClasses();
  String expectedString = String( (const byte *)"class", 5 );

  ASSERT_TRUE( cssClasses.length() == 1 );
  ASSERT_EQ(  expectedString.text(), cssClasses.stringAt( 0 ).text() );

  expectedString = String( (const byte *)"subclass", 8 );
  ASSERT_EQ( expectedString.text(), cssClasses.stringAt( 1 ).text() );
}
