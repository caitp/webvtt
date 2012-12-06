#include "payload_testfixture"
class PayloadEscapeCharacter : public PayloadTest {};

/*
 * Verifies that greater than escape characters in the cue text payload are parsed.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-gt-escape (11/27/2012)
 */
TEST_F(PayloadEscapeCharacter,DISABLED_GT)
{
	loadVtt( "payload/escape-character/gt-escape-character.vtt", 1 );

	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();

	String expectedText = String( (const byte *)">", 1 );
	ASSERT_EQ( expectedText.text(), node->content().text() );
}

/*
 * Verifies that less than escape characters in the cue text payload are parsed.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-lt-escape (11/27/2012)
 */
TEST_F(PayloadEscapeCharacter,DISABLED_LT)
{
	loadVtt( "payload/escape-character/lt-escape-character.vtt", 1 );

	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	String expectedText = String( (const byte *)"<", 1 );

	ASSERT_EQ( expectedText.text(), node->content().text() );
}

/*
 * Verifies that ampersand escape characters in the cue text payload are parsed correctly.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-amp-escape (11/27/2012)
 */
TEST_F(PayloadEscapeCharacter,DISABLED_Ampersand)
{
	loadVtt( "payload/escape-character/ampersand-escape-character.vtt", 1 );

	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	String expectedText = String( (const byte *)"&", 1 );

	ASSERT_EQ( expectedText.text(), node->content().text() );
}

/*
 * Verifies that left to right escape characters are parsed.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-lrm-escape (11/27/2012)
 */
TEST_F(PayloadEscapeCharacter,DISABLED_LRM)
{
	loadVtt( "payload/escape-character/lrm-escape-character.vtt", 1 );

	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	
	ASSERT_EQ( UTF16_LEFT_TO_RIGHT, node->content().text()[0] );
}

/*
 * Verifies that right to left escape characters are parsed.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-rlm-escape (11/27/2012)
 */
TEST_F(PayloadEscapeCharacter,DISABLED_RLM)
{
	loadVtt( "payload/escape-character/rlm-escape-character.vtt", 1 );

	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	
	ASSERT_EQ( UTF16_RIGHT_TO_LEFT, node->content().text()[0] );
}

/*
 * Verifies that non breaking space characters are parsed.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-nbsp-escape (11/27/2012)
 */ 
TEST_F(PayloadEscapeCharacter,DISABLED_NBSP)
{
	loadVtt( "payload/escape-character/nbsp-escape-character.vtt", 1 );

	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	
	ASSERT_EQ( UTF16_NO_BREAK_SPACE, node->content().text()[0] );
}

/*
 * Verifies that multiple escape characters are parsed.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-text (11/27/2012)
 */
TEST_F(PayloadEscapeCharacter,DISABLED_MultipleEscapeCharacter)
{
	loadVtt( "payload/escape-character/multiple-escape-character.vtt", 1 );

	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	
	ASSERT_EQ( UTF16_NO_BREAK_SPACE, node->content().text()[0] );
	ASSERT_EQ( UTF16_NO_BREAK_SPACE, node->content().text()[1] );
}

/*
 * Verifies that multiple escape characters on multiple lines are parsed.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-text (11/27/2012)
 *	Cue text text consists of one or more cue text components optionally separated by a single line terminator which can be: 
 *		1. CR (U+000D)
 *		2. LF (U+000A)
 *		3. CRLF pair
 */
TEST_F(PayloadEscapeCharacter,DISABLED_MultilineMultipleEscapeCharacter)
{
	loadVtt( "payload/escape-character/multiline-multiple-escape-character.vtt", 1 );

	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	
	ASSERT_EQ( UTF16_NO_BREAK_SPACE, node->content().text()[0] );
	ASSERT_EQ( UTF16_NO_BREAK_SPACE, node->content().text()[1] );
}

/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012
 
 Relates to: 
  Cue Text Escape Characters: 
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 
 Description:
 Incorrect Space Character Escape : '&nsp;' instead of '&nbsp;'
 Expected Output: '&nsp;'
*/
TEST_F(PayloadEscapeCharacter,DISABLED_NBSP)
{
	loadVtt( "payload/escape-character/space-character-escape-nsp.vtt", 1 );
	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	String expectedText = String( (const byte *)"&nsp;", 1 );

	ASSERT_EQ( expectedText.text(), node->content().text() );
}
/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012
 
 Relates To:
 Cue Text Escape Characters: 
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 
 Description:
 The Parser currently allows incorrect escapes to be outputted in the cue text string
 Expected Output: '&nbp'
*/
TEST_F(PayloadEscapeCharacter,DISABLED_NBSP)
{
	loadVtt( "payload/escape-character/space-character-escape-nbp.vtt", 1 );

	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	String expectedText = String( (const byte *)"&nbp", 1 );

	ASSERT_EQ( expectedText.text(), node->content().text() );

}
/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012
 
 Relates to: 
  Cue Text Escape Characters: 
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 
 Description:
 Incorrect Space Character Escape : '&bsp;' instead of '&nbsp;'
 Expected Output: '&bsp;'
*/
TEST_F(PayloadEscapeCharacter,DISABLED_NBSP)
{
	loadVtt( "payload/escape-character/space-character-escape-bsp.vtt", 1 );
	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	String expectedText = String( (const byte *)"&bsp;", 1 );

	ASSERT_EQ( expectedText.text(), node->content().text() );
}
/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012
 
 Relates to: 
 Cue Text Escape Characters: 
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 
 Description:
 Incorrect Space Character Escape : '&bp;' instead of '&nbsp;'
 Expected Output: '&bp;'
*/
TEST_F(PayloadEscapeCharacter,DISABLED_NBSP)
{
	loadVtt( "payload/escape-character/space-character-escape-bp.vtt", 1 );
	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	String expectedText = String( (const byte *)"&bp;", 1 );

	ASSERT_EQ( expectedText.text(), node->content().text() );

}
/* 
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012
 
 Relates to: 
 Cue Text Escape Characters: 
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 
 Description:
 Incorrect Space Character Escape : '&b;' instead of '&nbsp;'
 Expected Output: '&b;'
*/
TEST_F(PayloadEscapeCharacter,DISABLED_NBSP)
{
	loadVtt( "payload/escape-character/space-character-escape-b.vtt", 1 );
	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	String expectedText = String( (const byte *)"&b;", 1 );

	ASSERT_EQ( expectedText.text(), node->content().text() );
}
/* 
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012
 
 Relates to: 
 Cue Text Escape Characters: 
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 
 Description:
 Incorrect Space Character Escape : '&s;' instead of '&nbsp;'
 Expected Output: '&s;'
*/
TEST_F(PayloadEscapeCharacter,DISABLED_NBSP)
{
	loadVtt( "payload/escape-character/space-character-escape-bsp.vtt", 1 );
	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	String expectedText = String( (const byte *)"&s;", 1 );

	ASSERT_EQ( expectedText.text(), node->content().text() );
}
/* 
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012
 
 Relates to: 
 Cue Text Escape Characters: 
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 
 Description:
 Incorrect Space Character Escape : '&ns;' instead of '&nbsp;'
 Expected Output: '&ns;'
*/
TEST_F(PayloadEscapeCharacter,DISABLED_NBSP)
{
	loadVtt( "payload/escape-character/space-character-escape-ns.vtt", 1 );
	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	String expectedText = String( (const byte *)"&ns;", 1 );

	ASSERT_EQ( expectedText.text(), node->content().text() );
}
/* 
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012
 
 Relates to: 
 Cue Text Escape Characters: 
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 
 Description:
 Incorrect Space Character Escape : '&np;' instead of '&nbsp;'
 Expected Output: '&np;'
*/
TEST_F(PayloadEscapeCharacter,DISABLED_NBSP)
{
	loadVtt( "payload/escape-character/space-character-escape-np.vtt", 1 );
	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	String expectedText = String( (const byte *)"&np", 1 );

	ASSERT_EQ( expectedText.text(), node->content().text() );
}
/* 
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012
 
 Relates to: 
 Cue Text Escape Characters: 
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 
 Description:
 Incorrect Space Character Escape : '&sp;' instead of '&nbsp;'
 Expected Output: '&sp;'
*/
TEST_F(PayloadEscapeCharacter,DISABLED_NBSP)
{
	loadVtt( "payload/escape-character/space-character-escape-sp.vtt", 1 );
	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	String expectedText = String( (const byte *)"&sp;", 1 );

	ASSERT_EQ( expectedText.text(), node->content().text() );
}
/* 
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012
 
 Relates to: 
 Cue Text Escape Characters: 
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 
 Description:
 Incorrect Space Character Escape : '&p;' instead of '&nbsp;'
 Expected Output: '&p;'
*/
TEST_F(PayloadEscapeCharacter,DISABLED_NBSP)
{
	loadVtt( "payload/escape-character/space-character-escape-p.vtt", 1 );
	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	String expectedText = String( (const byte *)"&p;", 1 );

	ASSERT_EQ( expectedText.text(), node->content().text() );
}
/* 
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012
 
 Relates to: 
 Cue Text Escape Characters: 
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 
 Description:
 Incorrect Space Character Escape : '&bs;' instead of '&nbsp;'
 Expected Output: '&bs;'
*/
TEST_F(PayloadEscapeCharacter,DISABLED_NBSP)
{
	loadVtt( "payload/escape-character/space-character-escape-bs.vtt", 1 );
	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	String expectedText = String( (const byte *)"&bs;", 1 );

	ASSERT_EQ( expectedText.text(), node->content().text() );
}
/* 
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012
 
 Relates to: 
 Cue Text Escape Characters: 
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 
 Description:
 Incorrect Left to Right Character Escape : '&lr;' instead of '&lrm;'
 Expected Output: '&lr;'
*/
TEST_F(PayloadEscapeCharacter,DISABLED_LeftToRight)
{
	loadVtt( "payload/escape-character/left-to-right-character-escape-lr.vtt", 1 );
	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	String expectedText = String( (const byte *)"&lr;", 1 );

	ASSERT_EQ( expectedText.text(), node->content().text() );
}
/* 
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012
 
 Relates to: 
 Cue Text Escape Characters: 
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 
 Description:
 Incorrect Left to Right Character Escape : '&l;' instead of '&lrm;'
 Expected Output: '&l;'
*/
TEST_F(PayloadEscapeCharacter,DISABLED_LeftToRight)
{
	loadVtt( "payload/escape-character/left-to-right-character-escape-l.vtt", 1 );
	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	String expectedText = String( (const byte *)"&l;", 1 );

	ASSERT_EQ( expectedText.text(), node->content().text() );
}
/* 
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012
 
 Relates to: 
 Cue Text Escape Characters: 
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 
 Description:
 Incorrect Left to Right Character Escape : '&lm;' instead of '&lrm;'
 Expected Output: '&lm;'
*/
TEST_F(PayloadEscapeCharacter,DISABLED_LeftToRight)
{
	loadVtt( "payload/escape-character/left-to-right-character-escape-lm.vtt", 1 );
	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	String expectedText = String( (const byte *)"&lm;", 1 );

	ASSERT_EQ( expectedText.text(), node->content().text() );
}
/* 
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012
 
 Relates to: 
 Cue Text Escape Characters: 
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 
 Description:
 Incorrect Left to Right Character Escape : '&rm;' instead of '&lrm;'
 Expected Output: '&rm;'
*/
TEST_F(PayloadEscapeCharacter,DISABLED_LeftToRight)
{
	loadVtt( "payload/escape-character/left-to-right-character-escape-rm.vtt", 1 );
	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	String expectedText = String( (const byte *)"&rm;", 1 );

	ASSERT_EQ( expectedText.text(), node->content().text() );
}
/* 
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012
 
 Relates to: 
 Cue Text Escape Characters: 
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 
 Description:
 Incorrect Left to Right Character Escape : '&m;' instead of '&lrm;'
 Expected Output: '&m;'
*/
TEST_F(PayloadEscapeCharacter,DISABLED_LeftToRight)
{
	loadVtt( "payload/escape-character/left-to-right-character-escape-m.vtt", 1 );
	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	String expectedText = String( (const byte *)"&m;", 1 );

	ASSERT_EQ( expectedText.text(), node->content().text() );
}
/* 
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012
 
 Relates to: 
 Cue Text Escape Characters: 
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 
 Description:
 Incorrect Left to Right Character Escape : '&r;' instead of '&lrm;'
 Expected Output: '&r;'
*/
TEST_F(PayloadEscapeCharacter,DISABLED_LeftToRight)
{
	loadVtt( "payload/escape-character/left-to-right-character-escape-r.vtt", 1 );
	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	String expectedText = String( (const byte *)"&r;", 1 );

	ASSERT_EQ( expectedText.text(), node->content().text() );
}
/* 
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012
 
 Relates to: 
 Cue Text Escape Characters: 
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 
 Description:
 Incorrect Left to Right Character Escape : '&lm;' instead of '&lrm;'
 Expected Output: '&lm;'
*/
TEST_F(PayloadEscapeCharacter,DISABLED_LeftToRight)
{
	loadVtt( "payload/escape-character/left-to-right-character-escape-lm.vtt", 1 );
	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	String expectedText = String( (const byte *)"&lm;", 1 );

	ASSERT_EQ( expectedText.text(), node->content().text() );
}
/* 
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012
 
 Relates to: 
 Cue Text Escape Characters: 
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 
 Description:
 Incorrect Left to Right Character Escape : '&rl;' instead of '&lrm;'
 Expected Output: '&rl;'
*/
TEST_F(PayloadEscapeCharacter,DISABLED_LeftToRight)
{
	loadVtt( "payload/escape-character/left-to-right-character-escape-rl.vtt", 1 );
	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	String expectedText = String( (const byte *)"&rl;", 1 );

	ASSERT_EQ( expectedText.text(), node->content().text() );
}
/*  
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012
 
 Relates to: 
 Cue Text Escape Characters: 
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 
 Description:
 Expected Output: '&'
*/
TEST_F(PayloadEscapeCharacter,DISABLED_Ampersand)
{
	loadVtt( "payload/escape-character/ampersand-character-escape.vtt", 1 );
	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	String expectedText = String( (const byte *)"&", 1 );

	ASSERT_EQ( expectedText.text(), node->content().text() );
}
/* 
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012
 
 Relates to: 
 Cue Text Escape Characters: 
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 
 Description:
 Incorrect Ampersand Escape : '&a;' instead of '&amp;'
 Expected Output: '&a;'
*/
TEST_F(PayloadEscapeCharacter,DISABLED_Ampersand)
{
	loadVtt( "payload/escape-character/ampersand-character-escape-a.vtt", 1 );
	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	String expectedText = String( (const byte *)"&a;", 1 );

	ASSERT_EQ( expectedText.text(), node->content().text() );
}
/* 
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012
 
 Relates to: 
 Cue Text Escape Characters: 
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 
 Description:
 Incorrect Ampersand Escape : '&am;' instead of '&amp;'
 Expected Output: '&am;'
*/
TEST_F(PayloadEscapeCharacter,DISABLED_Ampersand)
{
	loadVtt( "payload/escape-character/ampersand-character-escape-a.vtt", 1 );
	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	String expectedText = String( (const byte *)"&am;", 1 );

	ASSERT_EQ( expectedText.text(), node->content().text() );
}
/* 
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012
 
 Relates to: 
 Cue Text Escape Characters: 
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 
 Description:
 Incorrect Ampersand Escape : '&mp;' instead of '&amp;'
 Expected Output: '&mp;'
*/
TEST_F(PayloadEscapeCharacter,DISABLED_Ampersand)
{
	loadVtt( "payload/escape-character/ampersand-character-escape-mp.vtt", 1 );
	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	String expectedText = String( (const byte *)"&mp;", 1 );

	ASSERT_EQ( expectedText.text(), node->content().text() );
}
/* 
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012
 
 Relates to: 
 Cue Text Escape Characters: 
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 
 Description:
 Incorrect Ampersand Escape : '&p;' instead of '&amp;'
 Expected Output: '&p;'
*/
TEST_F(PayloadEscapeCharacter,DISABLED_Ampersand)
{
	loadVtt( "payload/escape-character/ampersand-character-escape-p.vtt", 1 );
	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	String expectedText = String( (const byte *)"&p;", 1 );

	ASSERT_EQ( expectedText.text(), node->content().text() );
}
/* 
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012
 
 Relates to: 
 Cue Text Escape Characters: 
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 
 Description:
 Incorrect Ampersand Escape : '&ap;' instead of '&amp;'
 Expected Output: '&ap;'
*/
TEST_F(PayloadEscapeCharacter,DISABLED_Ampersand)
{
	loadVtt( "payload/escape-character/ampersand-character-escape-ap.vtt", 1 );
	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	String expectedText = String( (const byte *)"&ap;", 1 );

	ASSERT_EQ( expectedText.text(), node->content().text() );
}
/* 
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012
 
 Relates to: 
 Cue Text Escape Characters: 
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 
 Description:
 Incorrect Less Than Escape : '&l;' instead of '&lt;'
 Expected Output: '&l;'
*/
TEST_F(PayloadEscapeCharacter,DISABLED_LessThan)
{
	loadVtt( "payload/escape-character/less-than-character-escape-l.vtt", 1 );
	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	String expectedText = String( (const byte *)"&l;", 1 );

	ASSERT_EQ( expectedText.text(), node->content().text() );
}
/* 
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012
 
 Relates to: 
 Cue Text Escape Characters: 
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 
 Description:
 Incorrect Less Than Escape : '&t;' instead of '&lt;'
 Expected Output: '&t;'
*/
TEST_F(PayloadEscapeCharacter,DISABLED_LessThan)
{
	loadVtt( "payload/escape-character/less-than-character-escape-t.vtt", 1 );
	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	String expectedText = String( (const byte *)"&t;", 1 );

	ASSERT_EQ( expectedText.text(), node->content().text() );
}
/* 
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012
 
 Relates to: 
 Cue Text Escape Characters: 
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 
 Description:
 Incorrect Greater Than Escape : '&g;' instead of '&gt;'
 Expected Output: '&g;'
*/
TEST_F(PayloadEscapeCharacter,DISABLED_GreaterThan)
{
	loadVtt( "payload/escape-character/greater-than-character-escape-g.vtt", 1 );
	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	String expectedText = String( (const byte *)"&g;", 1 );

	ASSERT_EQ( expectedText.text(), node->content().text() );
}
/* 
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012
 
 Relates to: 
 Cue Text Escape Characters: 
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 
 Description:
 Incorrect Space Character Escape : '&nbs;' instead of '&nbsp;'
 Expected Output: '&nbs;'
*/
TEST_F(PayloadEscapeCharacter,DISABLED_NBSP)
{
	loadVtt( "payload/escape-character/space-character-escape-nbs.vtt", 1 );
	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	String expectedText = String( (const byte *)"&nbs;", 1 );

	ASSERT_EQ( expectedText.text(), node->content().text() );
}
/* 
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012
 
 Relates to: 
 Cue Text Escape Characters: 
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 
 Description:
 Incorrect Space Character Escape : '&nb;' instead of '&nbsp;'
 Expected Output: '&nb;'
*/
TEST_F(PayloadEscapeCharacter,DISABLED_NBSP)
{
	loadVtt( "payload/escape-character/space-character-escape-nb.vtt", 1 );
	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	String expectedText = String( (const byte *)"&nb;", 1 );

	ASSERT_EQ( expectedText.text(), node->content().text() );
}
/* 
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012
 
 Relates to: 
 Cue Text Escape Characters: 
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 
 Description:
 Incorrect Space Character Escape : '&n;' instead of '&nbsp;'
 Expected Output: '&n;'
*/
TEST_F(PayloadEscapeCharacter,DISABLED_NBSP)
{
	loadVtt( "payload/escape-character/space-character-escape-n.vtt", 1 );
	const TextNode *node = getHeadOfCue( 0 )->child( 0 )->toTextNode();
	String expectedText = String( (const byte *)"&n;", 1 );

	ASSERT_EQ( expectedText.text(), node->content().text() );
}