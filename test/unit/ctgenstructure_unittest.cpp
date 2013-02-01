#include "cue_testfixture"
class CueTimingsGeneralStructure : public CueTest { };

/*
 Test expecting parser to succeed when a cue's timestamp separator surrounded by mix of U+0009
 CHARACTER TABULATION characters and U+0020 SPACE characters
 characters

 From http://dev.w3.org/html5/webvtt/#webvtt-cue-timings (10/15/2012):
 The WebVTT cue timings part of a WebVTT cue consists of the following components, in the given order:

 1. A WebVTT timestamp representing the start time offset of the cue. The time represented by this
 WebVTT timestamp must be greater than or equal to the start time offsets of all previous cues in the file.

 2. One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.

 3. The string "-->" (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN).

 4. One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.

 5. A WebVTT timestamp representing the end time offset of the cue. The time represented by this
 WebVTT timestamp must be greater than the start time offset of the cue.
 */

TEST_F(CueTimingsGeneralStructure, CueTimingsSeperator1LeftMix)
{
  loadVtt( "cue-times/separator/cuetimings_separator_1l_mix_good.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

/*
 Test expecting parser to succeed when a cue's timestamp separator surrounded by mix of U+0009
 CHARACTER TABULATION characters and U+0020 SPACE characters
 characters

 From http://dev.w3.org/html5/webvtt/#webvtt-cue-timings (10/15/2012):
 The WebVTT cue timings part of a WebVTT cue consists of the following components, in the given order:

 1. A WebVTT timestamp representing the start time offset of the cue. The time represented by this
 WebVTT timestamp must be greater than or equal to the start time offsets of all previous cues in the file.

 2. One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.

 3. The string "-->" (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN).

 4. One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.

 5. A WebVTT timestamp representing the end time offset of the cue. The time represented by this
 WebVTT timestamp must be greater than the start time offset of the cue.
 */
TEST_F(CueTimingsGeneralStructure, CueTimingsSeperator1RightMix)
{
  loadVtt( "cue-times/separator/cuetimings_separator_1r_mix_good.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

/*
 Test expecting parser to succeed when a cue's timestamp separator surrounded by multiple U+0020 SPACE
 characters

 From http://dev.w3.org/html5/webvtt/#webvtt-cue-timings (10/15/2012):
 The WebVTT cue timings part of a WebVTT cue consists of the following components, in the given order:

 1. A WebVTT timestamp representing the start time offset of the cue. The time represented by this
 WebVTT timestamp must be greater than or equal to the start time offsets of all previous cues in the file.

 2. One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.

 3. The string "-->" (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN).

 4. One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.

 5. A WebVTT timestamp representing the end time offset of the cue. The time represented by this
 WebVTT timestamp must be greater than the start time offset of the cue.
 */
TEST_F(CueTimingsGeneralStructure, CueTimingsSeperatorNSpace)
{
  loadVtt( "cue-times/separator/cuetimings_separator_n_space_good.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

/*
 Test expecting parser to succeed when a cue's timestamp separator surrounded by multiple U+0009
 CHARACTER TABULATION characters
 characters

 From http://dev.w3.org/html5/webvtt/#webvtt-cue-timings (10/15/2012):
 The WebVTT cue timings part of a WebVTT cue consists of the following components, in the given order:

 1. A WebVTT timestamp representing the start time offset of the cue. The time represented by this
 WebVTT timestamp must be greater than or equal to the start time offsets of all previous cues in the file.

 2. One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.

 3. The string "-->" (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN).

 4. One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.

 5. A WebVTT timestamp representing the end time offset of the cue. The time represented by this
 WebVTT timestamp must be greater than the start time offset of the cue.
 */
TEST_F(CueTimingsGeneralStructure, CueTimingsSeperatorNTab)
{
  loadVtt( "cue-times/separator/cuetimings_separator_n_tab_good.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

/*
 Test expecting parser to succeed when a cue's timestamp separator surrounded by mix of U+0009
 CHARACTER TABULATION characters and U+0020 SPACE characters
 characters

 From http://dev.w3.org/html5/webvtt/#webvtt-cue-timings (10/15/2012):
 The WebVTT cue timings part of a WebVTT cue consists of the following components, in the given order:

 1. A WebVTT timestamp representing the start time offset of the cue. The time represented by this
 WebVTT timestamp must be greater than or equal to the start time offsets of all previous cues in the file.

 2. One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.

 3. The string "-->" (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN).

 4. One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.

 5. A WebVTT timestamp representing the end time offset of the cue. The time represented by this
 WebVTT timestamp must be greater than the start time offset of the cue.
*/
TEST_F(CueTimingsGeneralStructure, CueTimingsSeperatorNLMix)
{
  loadVtt( "cue-times/separator/cuetimings_separator_nl_mix_good.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

/*
 Test expecting parser to succeed when a cue's timestamp separator surrounded by mix of U+0009
 CHARACTER TABULATION characters and U+0020 SPACE characters
 characters

 From http://dev.w3.org/html5/webvtt/#webvtt-cue-timings (10/15/2012):
 The WebVTT cue timings part of a WebVTT cue consists of the following components, in the given order:

 1. A WebVTT timestamp representing the start time offset of the cue. The time represented by this
 WebVTT timestamp must be greater than or equal to the start time offsets of all previous cues in the file.

 2. One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.

 3. The string "-->" (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN).

 4. One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.

 5. A WebVTT timestamp representing the end time offset of the cue. The time represented by this
 WebVTT timestamp must be greater than the start time offset of the cue.
*/
TEST_F(CueTimingsGeneralStructure, CueTimingsSeperatorNRMix)
{
  loadVtt( "cue-times/separator/cuetimings_separator_nr_mix_good.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

/*
 Test expecting parser to succeed when a cue's timestamp separator surrounded by mix of U+0009
 CHARACTER TABULATION characters and U+0020 SPACE characters
 characters

 From http://dev.w3.org/html5/webvtt/#webvtt-cue-timings (10/15/2012):
 The WebVTT cue timings part of a WebVTT cue consists of the following components, in the given order:

 1. A WebVTT timestamp representing the start time offset of the cue. The time represented by this
 WebVTT timestamp must be greater than or equal to the start time offsets of all previous cues in the file.

 2. One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.

 3. The string "-->" (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN).

 4. One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.

 5. A WebVTT timestamp representing the end time offset of the cue. The time represented by this
 WebVTT timestamp must be greater than the start time offset of the cue.
*/
TEST_F(CueTimingsGeneralStructure, CueTimingsSeperatorXMix)
{
  loadVtt( "cue-times/separator/cuetimings_separator_x_mix_good.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}
