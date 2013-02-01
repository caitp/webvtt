#include "payload_testfixture"
class PayloadVoiceTag : public PayloadTest {};

/*
 * Verifies that a voice cue text tag that does not have an end tag is parsed correctly.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-voice-span (11/27/2012)
 *  Voice tags consist of:
 *    1. A cue span start tag "v" that requires an annotation.
 *    2. Cue internal text representing the voice text.
 *    3. A cue span end tag that can be ommitted for brevity if the voice span is the only tag in this webvtt cue text sequence.
 */
TEST_F(PayloadVoiceTag, VoiceTag)
{
  loadVtt( "payload/v-tag/v-tag.vtt" );

  const InternalNode *head = getHeadOfCue( 0 );

  ASSERT_TRUE( head->childCount() == 1 );
  ASSERT_EQ( Node::Voice, head->child( 0 )->kind() );
}

/*
 * Verifies that a voice cue text tag that has an end tag is parsed correctly.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-voice-span (11/27/2012)
 *  Voice tags consist of:
 *    1. A cue span start tag "v" that requires an annotation.
 *    2. Cue internal text representing the voice text.
 *    3. A cue span end tag that can be ommitted for brevity if the voice span is the only tag in this webvtt cue text sequence.
 */
TEST_F(PayloadVoiceTag, VoiceInternalTextTag)
{
  loadVtt( "payload/v-tag/v-tag-internal-text.vtt" );

  const InternalNode *head = getHeadOfCue( 0 );

  ASSERT_TRUE( head->childCount() == 1 );
  ASSERT_EQ( Node::Voice, head->child( 0 )->kind() );
  ASSERT_TRUE( head->child( 0 )->toInternalNode()->childCount() == 1 );
}

/*
 * Verifies that a voice cue text tag that has an annotation is parsed correctly and contains the annotation.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-voice-span (11/27/2012)
 *  Voice tags consist of:
 *    1. A cue span start tag "v" that requires an annotation.
 *    2. Cue internal text representing the voice text.
 *    3. A cue span end tag that can be ommitted for brevity if the voice span is the only tag in this webvtt cue text sequence.
 */
TEST_F(PayloadVoiceTag, VoiceTagAnnotation)
{
  loadVtt( "payload/v-tag/v-tag-annotation.vtt" );

  const InternalNode *head = getHeadOfCue( 0 );

  ASSERT_TRUE( head->childCount() == 3 );
  ASSERT_EQ( Node::Voice, head->child( 1 )->kind() );

  String expectedString = String( (const byte *)"Annotation", 10 );
  ASSERT_EQ( expectedString.text(), head->child( 1 )->toInternalNode()->annotation().text() );
}

/*
 * Verifies that a single subclass can be attached to a cue text voice start tag.
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
TEST_F(PayloadVoiceTag, VoiceTagSingleSubclass)
{
  loadVtt( "payload/v-tag/v-tag-single-subclass.vtt" );

  const InternalNode *head = getHeadOfCue( 0 );

  ASSERT_TRUE( head->childCount() == 3 );
  ASSERT_EQ( Node::Voice, head->child( 1 )->kind() );

  StringList cssClasses = head->child( 1 )->toInternalNode()->cssClasses();
  String expectedString = String( (const byte *)"class", 5 );

  ASSERT_TRUE( cssClasses.length() == 1 );
  ASSERT_EQ(  expectedString.text(), cssClasses.stringAt( 0 ).text() );
}

/*
 * Verifies that multiple subclasses can be attached to a cue text voice start tag.
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
TEST_F(PayloadVoiceTag, VoiceTagMultiSubclass)
{
  loadVtt( "payload/v-tag/v-tag-multi-subclass.vtt" );

  const InternalNode *head = getHeadOfCue( 0 );

  ASSERT_TRUE( head->childCount() == 3 );
  ASSERT_EQ( Node::Voice, head->child( 1 )->kind() );

  StringList cssClasses = head->child( 1 )->toInternalNode()->cssClasses();
  String expectedString = String( (const byte *)"class", 5 );

  ASSERT_TRUE( cssClasses.length() == 1 );
  ASSERT_EQ(  expectedString.text(), cssClasses.stringAt( 0 ).text() );

  expectedString = String( (const byte *)"subclass", 8 );
  ASSERT_EQ( expectedString.text(), cssClasses.stringAt( 1 ).text() );
}
