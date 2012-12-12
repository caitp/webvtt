#include "cue_testfixture"
class FileStructure : public CueTest { };
/* Covers the tests for general file structure. 
 * #1001-1019
 *
 */

/*
 * Verifies that a file with only the WebVTT signature will parse correctly.
 * From http://dev.w3.org/html5/webvtt/#webvtt-file-body (12/02/2012):
 *
 * A WebVTT file body consists of the following components, in the following order:
 * 1. An optional U+FEFF BYTE ORDER MARK (BOM) character.
 * 2. The string "WEBVTT".
 * 3. Optionally, either a U+0020 SPACE character or a U+0009 CHARACTER TABULATION (tab) character followed by any number of characters that are not U+000A LINE FEED (LF) or U+000D CARRIAGE RETURN (CR) characters.
 * 4. Two or more WebVTT line terminators.
 * 5. Zero or more WebVTT cues and/or WebVTT comments separated from each other by two or more WebVTT line terminators.
 * 6. Zero or more WebVTT line terminators.
 */
TEST_F(FileStructure,WebVTTNoBOM)
{
	loadVtt( "filestructure/webvtt-no-bom.vtt", 0 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors";
}

/*
 * Verifies that a file with a BOM character and the WebVTT signature will parse correctly.
 * From http://dev.w3.org/html5/webvtt/#webvtt-file-body (12/02/2012):
 *
 * A WebVTT file body consists of the following components, in the following order:
 * 1. An optional U+FEFF BYTE ORDER MARK (BOM) character.
 * 2. The string "WEBVTT".
 * 3. Optionally, either a U+0020 SPACE character or a U+0009 CHARACTER TABULATION (tab) character followed by any number of characters that are not U+000A LINE FEED (LF) or U+000D CARRIAGE RETURN (CR) characters.
 * 4. Two or more WebVTT line terminators.
 * 5. Zero or more WebVTT cues and/or WebVTT comments separated from each other by two or more WebVTT line terminators.
 * 6. Zero or more WebVTT line terminators.
 */
TEST_F(FileStructure,WebVTTWithBOM)
{
	loadVtt( "filestructure/webvtt-with-bom.vtt", 0 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors";
}

/*
 * Verifies that a file with the WebVTT signature and a space character will parse correctly.
 * From http://dev.w3.org/html5/webvtt/#webvtt-file-body (12/02/2012):
 *
 * A WebVTT file body consists of the following components, in the following order:
 * 1. An optional U+FEFF BYTE ORDER MARK (BOM) character.
 * 2. The string "WEBVTT".
 * 3. Optionally, either a U+0020 SPACE character or a U+0009 CHARACTER TABULATION (tab) character followed by any number of characters that are not U+000A LINE FEED (LF) or U+000D CARRIAGE RETURN (CR) characters.
 * 4. Two or more WebVTT line terminators.
 * 5. Zero or more WebVTT cues and/or WebVTT comments separated from each other by two or more WebVTT line terminators.
 * 6. Zero or more WebVTT line terminators.
 */
TEST_F(FileStructure,WebVTTSpace)
{
	loadVtt( "filestructure/webvtt-space.vtt", 0 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

/*
 * Verifies that a file with the WebVTT signature and a tab character will parse correctly.
 * From http://dev.w3.org/html5/webvtt/#webvtt-file-body (12/02/2012):
 *
 * A WebVTT file body consists of the following components, in the following order:
 * 1. An optional U+FEFF BYTE ORDER MARK (BOM) character.
 * 2. The string "WEBVTT".
 * 3. Optionally, either a U+0020 SPACE character or a U+0009 CHARACTER TABULATION (tab) character followed by any number of characters that are not U+000A LINE FEED (LF) or U+000D CARRIAGE RETURN (CR) characters.
 * 4. Two or more WebVTT line terminators.
 * 5. Zero or more WebVTT cues and/or WebVTT comments separated from each other by two or more WebVTT line terminators.
 * 6. Zero or more WebVTT line terminators.
 */
TEST_F(FileStructure,WebVTTTab)
{
	loadVtt( "filestructure/webvtt-tab.vtt", 0 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

/*
 * Verifies that a file with the WebVTT signature, a tab character, and non-line terminating
 * characters will parse correctly.
 * From http://dev.w3.org/html5/webvtt/#webvtt-file-body (12/02/2012):
 *
 * A WebVTT file body consists of the following components, in the following order:
 * 1. An optional U+FEFF BYTE ORDER MARK (BOM) character.
 * 2. The string "WEBVTT".
 * 3. Optionally, either a U+0020 SPACE character or a U+0009 CHARACTER TABULATION (tab) character followed by any number of characters that are not U+000A LINE FEED (LF) or U+000D CARRIAGE RETURN (CR) characters.
 * 4. Two or more WebVTT line terminators.
 * 5. Zero or more WebVTT cues and/or WebVTT comments separated from each other by two or more WebVTT line terminators.
 * 6. Zero or more WebVTT line terminators.
 */
TEST_F(FileStructure,WebVTTTabText)
{
	loadVtt( "filestructure/webvtt-tab-text.vtt", 0 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

/*
 * Verifies that a file with the WebVTT signature, a space, and non-line terminating
 * characters will parse correctly.
 * From http://dev.w3.org/html5/webvtt/#webvtt-file-body (12/02/2012):
 *
 * A WebVTT file body consists of the following components, in the following order:
 * 1. An optional U+FEFF BYTE ORDER MARK (BOM) character.
 * 2. The string "WEBVTT".
 * 3. Optionally, either a U+0020 SPACE character or a U+0009 CHARACTER TABULATION (tab) character followed by any number of characters that are not U+000A LINE FEED (LF) or U+000D CARRIAGE RETURN (CR) characters.
 * 4. Two or more WebVTT line terminators.
 * 5. Zero or more WebVTT cues and/or WebVTT comments separated from each other by two or more WebVTT line terminators.
 * 6. Zero or more WebVTT line terminators.
 */
TEST_F(FileStructure,WebVTTSpaceText)
{
	loadVtt( "filestructure/webvtt-space-text.vtt", 0 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

/*
 * Verifies that a file with text before the WebVTT signature will fail parsing and finish gracefully.
 * From http://dev.w3.org/html5/webvtt/#webvtt-file-body (12/02/2012):
 *
 * A WebVTT file body consists of the following components, in the following order:
 * 1. An optional U+FEFF BYTE ORDER MARK (BOM) character.
 * 2. The string "WEBVTT".
 * 3. Optionally, either a U+0020 SPACE character or a U+0009 CHARACTER TABULATION (tab) character followed by any number of characters that are not U+000A LINE FEED (LF) or U+000D CARRIAGE RETURN (CR) characters.
 * 4. Two or more WebVTT line terminators.
 * 5. Zero or more WebVTT cues and/or WebVTT comments separated from each other by two or more WebVTT line terminators.
 * 6. Zero or more WebVTT line terminators.
 */
TEST_F(FileStructure,TextBeforeHeader)
{
	loadVtt( "filestructure/text-before-header.vtt", false, 0 );
	ASSERT_EQ( 1, errorCount() );
	assertEquals( getError( 0 ), WEBVTT_MALFORMED_TAG, 1, 1 );
}

/*
 * Verifies that a blank file will finish the parsing attempt gracefully.
 * From http://dev.w3.org/html5/webvtt/#webvtt-file-body (12/02/2012):
 *
 * A WebVTT file body consists of the following components, in the following order:
 * 1. An optional U+FEFF BYTE ORDER MARK (BOM) character.
 * 2. The string "WEBVTT".
 * 3. Optionally, either a U+0020 SPACE character or a U+0009 CHARACTER TABULATION (tab) character followed by any number of characters that are not U+000A LINE FEED (LF) or U+000D CARRIAGE RETURN (CR) characters.
 * 4. Two or more WebVTT line terminators.
 * 5. Zero or more WebVTT cues and/or WebVTT comments separated from each other by two or more WebVTT line terminators.
 * 6. Zero or more WebVTT line terminators.
 */
TEST_F(FileStructure,BlankFile)
{
	loadVtt( "filestructure/blank-file.vtt", 0 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

/*
 * Verifies that a file with only a BOM character will finish the parsing attempt gracefully.
 * From http://dev.w3.org/html5/webvtt/#webvtt-file-body (12/02/2012):
 *
 * A WebVTT file body consists of the following components, in the following order:
 * 1. An optional U+FEFF BYTE ORDER MARK (BOM) character.
 * 2. The string "WEBVTT".
 * 3. Optionally, either a U+0020 SPACE character or a U+0009 CHARACTER TABULATION (tab) character followed by any number of characters that are not U+000A LINE FEED (LF) or U+000D CARRIAGE RETURN (CR) characters.
 * 4. Two or more WebVTT line terminators.
 * 5. Zero or more WebVTT cues and/or WebVTT comments separated from each other by two or more WebVTT line terminators.
 * 6. Zero or more WebVTT line terminators.
 */
TEST_F(FileStructure,BlankFileWithBOM)
{
	loadVtt( "filestructure/blank-file-with-bom.vtt", 0 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

/*
 * Verifies that a file with a BOM character, a tab, and the WebVTT signature will fail parsing and
 * finish gracefully.
 * From http://dev.w3.org/html5/webvtt/#webvtt-file-body (12/02/2012):
 *
 * A WebVTT file body consists of the following components, in the following order:
 * 1. An optional U+FEFF BYTE ORDER MARK (BOM) character.
 * 2. The string "WEBVTT".
 * 3. Optionally, either a U+0020 SPACE character or a U+0009 CHARACTER TABULATION (tab) character followed by any number of characters that are not U+000A LINE FEED (LF) or U+000D CARRIAGE RETURN (CR) characters.
 * 4. Two or more WebVTT line terminators.
 * 5. Zero or more WebVTT cues and/or WebVTT comments separated from each other by two or more WebVTT line terminators.
 * 6. Zero or more WebVTT line terminators.
 */
TEST_F(FileStructure,TabAfterBOMBeforeHeader)
{
	loadVtt( "filestructure/tab-after-bom-before-header.vtt", false, 0 );
	ASSERT_EQ( 1, errorCount() ) << "This file should contain 1 error.";
	assertEquals( getError( 0 ), WEBVTT_MALFORMED_TAG, 1, 1 );
}

/*
 * Verifies that a file with no line terminator between the WebVTT signature and a cue
 * will parse correctly.
 * From http://dev.w3.org/html5/webvtt/#webvtt-file-body (12/02/2012):
 *
 * A WebVTT file body consists of the following components, in the following order:
 * 1. An optional U+FEFF BYTE ORDER MARK (BOM) character.
 * 2. The string "WEBVTT".
 * 3. Optionally, either a U+0020 SPACE character or a U+0009 CHARACTER TABULATION (tab) character followed by any number of characters that are not U+000A LINE FEED (LF) or U+000D CARRIAGE RETURN (CR) characters.
 * 4. Two or more WebVTT line terminators.
 * 5. Zero or more WebVTT cues and/or WebVTT comments separated from each other by two or more WebVTT line terminators.
 * 6. Zero or more WebVTT line terminators.
 */
TEST_F(FileStructure,HeaderNoNewLine)
{
	loadVtt( "filestructure/header-no-new-line.vtt", 1 );
	ASSERT_EQ( 1, errorCount() );
	assertEquals( getError( 0 ), WEBVTT_EXPECTED_EOL, 2, 1 );
	assertEquals( getCue( 0 ).startTime(), 0, 11, 0 );
	assertEquals( getCue( 0 ).endTime(), 0, 13, 0 );
}

/*
 * Verifies that a file with a cue containing no payload will parse correctly.
 * From http://dev.w3.org/html5/webvtt/#webvtt-file-body (12/02/2012):
 *
 * A WebVTT file body consists of the following components, in the following order:
 * 1. An optional U+FEFF BYTE ORDER MARK (BOM) character.
 * 2. The string "WEBVTT".
 * 3. Optionally, either a U+0020 SPACE character or a U+0009 CHARACTER TABULATION (tab) character followed by any number of characters that are not U+000A LINE FEED (LF) or U+000D CARRIAGE RETURN (CR) characters.
 * 4. Two or more WebVTT line terminators.
 * 5. Zero or more WebVTT cues and/or WebVTT comments separated from each other by two or more WebVTT line terminators.
 * 6. Zero or more WebVTT line terminators.
 */
TEST_F(FileStructure,NoPayloadText)
{
	loadVtt( "filestructure/no-payload-text.vtt", 1 );
	ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

/*
 * Verifies that a file with a malformed cue will parse correctly.
 * From http://dev.w3.org/html5/webvtt/#webvtt-file-body (12/02/2012):
 *
 * A WebVTT file body consists of the following components, in the following order:
 * 1. An optional U+FEFF BYTE ORDER MARK (BOM) character.
 * 2. The string "WEBVTT".
 * 3. Optionally, either a U+0020 SPACE character or a U+0009 CHARACTER TABULATION (tab) character followed by any number of characters that are not U+000A LINE FEED (LF) or U+000D CARRIAGE RETURN (CR) characters.
 * 4. Two or more WebVTT line terminators.
 * 5. Zero or more WebVTT cues and/or WebVTT comments separated from each other by two or more WebVTT line terminators.
 * 6. Zero or more WebVTT line terminators.
 */
TEST_F(FileStructure,MissingCueIdentifier)
{
	loadVtt( "filestructure/missing-cue-identifier.vtt", 0 );
	ASSERT_EQ( 1, errorCount() ) << "This file should contain no errors";
	assertEquals( getError( 0 ), WEBVTT_CUE_INCOMPLETE, 3, 13 );
}