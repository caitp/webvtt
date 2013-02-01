#include "cue_testfixture"
class CueTimes : public CueTest { };

/**
 * 'From' timestamp'
 */

/**
 * Bounds checking - 'from' hour
 */
/**
 * Test expecting parser to report an error and skip cue
 * when a 4 component timestamp's 'hours' component consists
 * of a non-digit character (below U+0030)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, FromHourBeyondLowBoundary)
{
  loadVtt( "cue-times/from/hour-beyond-low-boundary.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_EXPECTED_TIMESTAMP, 3, 1 );
}

/**
 * Test expecting parser to fail when a 4 component timestamp's 'hours' component consists
 * of a non-digit character (above U+0039)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, FromHourBeyondHighBoundary)
{
  loadVtt( "cue-times/from/hour-beyond-high-boundary.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_EXPECTED_TIMESTAMP, 3, 1 );
}

/**
 * Test expecting parser to encounter no errors when parsing a valid, well-formed
 * cue timestamp whose 'hours' component's digits are all ASCII digits (U+0030-U+0039)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, FromHourWithinLowBoundary)
{
  loadVtt( "cue-times/from/hour-within-low-boundary.vtt", 1 );
  assertEquals( getCue( 0 ).startTime(), 9, 56, 5  );
}

/**
 * Test expecting parser to encounter no errors when parsing a valid, well-formed
 * cue timestamp whose 'hours' component's digits are all ASCII digits (U+0030-U+0039)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, FromHourWithinHighBoundary)
{
  loadVtt( "cue-times/from/hour-within-high-boundary.vtt", 1 );
  assertEquals( getCue( 0 ).startTime(), 9, 9, 56, 5  );
}

/**
 * Bounds checking - 'from' minute
 */
/**
 * Test expecting parser to report an error and skip cue
 * when a 4 component timestamp's 'minutes' component consists
 * of a non-digit character (below U+0030)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, FromMinuteBeyondLowBoundary)
{
  loadVtt( "cue-times/from/minute-beyond-low-boundary.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_EXPECTED_TIMESTAMP, 3, 1 );
}

/**
 * Test expecting parser to fail when a 4 component timestamp's 'minutes' component consists
 * of a non-digit character (above U+0039)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, FromMinuteBeyondHighBoundary)
{
  loadVtt( "cue-times/from/minute-beyond-high-boundary.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_EXPECTED_TIMESTAMP, 3, 1 );
}

/**
 * Test expecting parser to encounter no errors when parsing a valid, well-formed
 * cue timestamp whose 'minutes' component's digits are all ASCII digits (U+0030-U+0039)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, FromMinuteWithinLowBoundary)
{
  loadVtt( "cue-times/from/minute-within-low-boundary.vtt", 1 );
  assertEquals( getCue( 0 ).startTime(), 0, 56, 5  );
}

/**
 * Test expecting parser to encounter no errors when parsing a valid, well-formed
 * cue timestamp whose 'minutes' component's digits are all ASCII digits (U+0030-U+0039)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, FromMinuteWithinHighBoundary)
{
  loadVtt( "cue-times/from/minute-within-high-boundary.vtt", 1 );
  assertEquals( getCue( 0 ).startTime(), 9, 56, 005 );
}

/**
 * Bounds checking - 'from' second
 */
/**
 * Test expecting parser to report an error and skip cue
 * when a 4 component timestamp's 'seconds' component consists
 * of a non-digit character (below U+0030)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, FromSecondBeyondLowBoundary)
{
  loadVtt( "cue-times/from/second-beyond-low-boundary.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_EXPECTED_TIMESTAMP, 3, 1 );
}

/**
 * Test expecting parser to fail when a 4 component timestamp's 'seconds' component consists
 * of a non-digit character (above U+0039)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, FromSecondBeyondHighBoundary)
{
  loadVtt( "cue-times/from/second-beyond-high-boundary.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_EXPECTED_TIMESTAMP, 3, 1 );
}

/**
 * Test expecting parser to encounter no errors when parsing a valid, well-formed
 * cue timestamp whose 'seconds' component's digits are all ASCII digits (U+0030-U+0039)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, FromSecondWithinLowBoundary)
{
  loadVtt( "cue-times/from/second-within-low-boundary.vtt", 1 );
  assertEquals( getCue( 0 ).startTime(), 9, 0, 5  );
}

/**
 * Test expecting parser to encounter no errors when parsing a valid, well-formed
 * cue timestamp whose 'seconds' component's digits are all ASCII digits (U+0030-U+0039)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, FromSecondWithinHighBoundary)
{
  loadVtt( "cue-times/from/second-within-high-boundary.vtt", 1 );
  assertEquals( getCue( 0 ).startTime(), 9, 59, 5 );
}

/**
 * Bounds checking - 'from' millisecond
 */
/**
 * Test expecting parser to report an error and skip cue
 * when a 4 component timestamp's 'milliseconds' component consists
 * of a non-digit character (below U+0030)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, FromMillisecondBeyondLowBoundary)
{
  loadVtt( "cue-times/from/millisecond-beyond-low-boundary.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_EXPECTED_TIMESTAMP, 3, 1 );
}

/**
 * Test expecting parser to fail when a 4 component timestamp's 'milliseconds' component consists
 * of a non-digit character (above U+0039)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, FromMillisecondBeyondHighBoundary)
{
  loadVtt( "cue-times/from/millisecond-beyond-high-boundary.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_EXPECTED_TIMESTAMP, 3, 1 );
}

/**
 * Test expecting parser to encounter no errors when parsing a valid, well-formed
 * cue timestamp whose 'milliseconds' component's digits are all ASCII digits (U+0030-U+0039)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, FromMillisecondWithinLowBoundary)
{
  loadVtt( "cue-times/from/millisecond-within-low-boundary.vtt", 1 );
  assertEquals( getCue( 0 ).startTime(), 9, 56, 0  );
}

/**
 * Test expecting parser to encounter no errors when parsing a valid, well-formed
 * cue timestamp whose 'milliseconds' component's digits are all ASCII digits (U+0030-U+0039)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, FromMillisecondWithinHighBoundary)
{
  loadVtt( "cue-times/from/millisecond-within-high-boundary.vtt", 1 );
  assertEquals( getCue( 0 ).startTime(), 9, 56, 999 );
}

/**
 * Format - 'from' numbers of minute digits
 */

TEST_F(CueTimes, FromOneDigitMinute)
{
  loadVtt( "cue-times/from/minute-1-digit.vtt", 1 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
  assertEquals( getCue( 0 ).startTime(), 9, 22, 0 );
}

/**
 * Test expecting parser to report no error when a 4 component timestamp's 'minutes' component
 * consists of two digit between the range of allowed values (00-59)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, FromTwoDigitMinute)
{
  loadVtt( "cue-times/from/minute-2-digit.vtt", 1 );
  assertEquals( getCue( 0 ).startTime(), 0, 1, 0, 0 );
}

/**
 * Test expecting parser to report an error when a 4 component timestamp's 'minutes' component
 * consists of three (or more) digits between the range of allowed values (00-59)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, FromThreeDigitMinute)
{
  loadVtt( "cue-times/from/minute-3-digit.vtt", 1 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
  assertEquals( getCue( 0 ).startTime(), 9, 56, 0 );
}

/**
 * Format - 'from' numbers of seconds digits
 */
/**
 * Test expecting parser to report an error when a 4 component timestamp's 'seconds' component
 * consists of a single digit between the range of allowed values (00-59)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, FromOneDigitSecond)
{
  loadVtt( "cue-times/from/second-1-digit.vtt", 1 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
  assertEquals( getCue( 0 ).startTime(), 5, 3, 0 );
}

/**
 * Test expecting parser to report no error when a 4 component timestamp's 'seconds' component
 * consists of two digit between the range of allowed values (00-59)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, FromTwoDigitSecond)
{
  loadVtt( "cue-times/from/second-2-digit.vtt", 1 );
  assertEquals( getCue( 0 ).startTime(), 0, 0, 25, 0 );
}

/**
 * Test expecting parser to report an error when a 4 component timestamp's 'seconds' component
 * consists of three (or more) digits between the range of allowed values (00-59)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, FromThreeDigitSecond)
{
  loadVtt( "cue-times/from/second-3-digit.vtt", 1 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
  assertEquals( getCue( 0 ).startTime(), 2, 38, 0 );
}

/**
 * Format - 'from' numbers of milliseconds digits
 */
/**
 * Test expecting parser to report an error when a 4 component timestamp's 'milliseconds' component
 * consists of fewer than three digits between the range of allowed values (00-59)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, FromTwoDigitMillisecond)
{
  loadVtt( "cue-times/from/millisecond-2-digit.vtt", 1 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
  assertEquals( getCue( 0 ).startTime(), 9, 56, 80 );
}

/**
 * Test expecting parser to report no error when a 4 component timestamp's 'milliseconds' component
 * consists of three digits between the range of allowed values (000-999)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, FromThreeDigitMillisecond)
{
  loadVtt( "cue-times/from/millisecond-3-digit.vtt", 1 );
  assertEquals( getCue( 0 ).startTime(), 0, 0, 0, 111 );
}

/**
 * Test expecting parser to report an error when a 4 component timestamp's 'milliseconds' component
 * consists of more than three digits between the range of allowed values (000-999)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, FromFourDigitMillisecond)
{
  loadVtt( "cue-times/from/millisecond-4-digit.vtt", 1 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
  assertEquals( getCue( 0 ).startTime(), 9, 56, 5 );
}

/**
 * Range checking
 */
/**
 * Test expecting parser to fail when a 4 component timestamp's 'minutes' component
 * consists of a value greater than 59
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, FromMinuteGreaterThan59)
{
  loadVtt( "cue-times/from/minute-greater-than-59.vtt", 1 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
  assertEquals( getCue( 0 ).startTime(), 1, 6, 0, 0 );
}

/**
 * Test expecting parser to fail when a 4 component timestamp's 'seconds' component
 * consists of a value greater than 59
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, FromSecondGreaterThan59)
{
  loadVtt( "cue-times/from/second-greater-than-59.vtt", 1 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
  assertEquals( getCue( 0 ).startTime(), 10, 17, 0 );
}

/**
 * Test expecting parser to fail when a 4 component timestamp's 'milliseconds' component
 * consists of a value greater than 999
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, FromMillisecondGreaterThan999)
{
  loadVtt( "cue-times/from/millisecond-greater-than-999.vtt", 1 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 1 );
  assertEquals( getCue( 0 ).startTime(), 0, 1, 0 );
}

/**
 * Bad delimiter
 */
/**
 * Test expecting parser to fail when a 4 component timestamp's 'hour' component
 * is separated from the 'minute' component by a character other than U+003A (COLON)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, FromBadDelimiterHourMinute)
{
  loadVtt( "cue-times/from/bad-delimiter-hour-minute.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_EXPECTED_TIMESTAMP, 3, 1 );
}

/**
 * Test expecting parser to fail when a 4 component timestamp's 'minute' component
 * is separated from the 'second' component by a character other than U+003A (COLON)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 * representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, FromBadDelimiterMinuteSecond)
{
  loadVtt( "cue-times/from/bad-delimiter-minute-second.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_EXPECTED_TIMESTAMP, 3, 1 );
}

/**
 * Test expecting parser to fail when a 4 component timestamp's 'second' component
 * is separated from the 'milliseconds' component by a character other than U+002E (FULL STOP)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, FromBadDelimiterSecondMillisecond)
{
  loadVtt( "cue-times/from/bad-delimiter-second-millisecond.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_EXPECTED_TIMESTAMP, 3, 1 );
}

/**
 * 'Until' timestamp'
 */

/**
 * Bounds checking - 'until' hour
 */
/**
 * Test expecting parser to report an error and skip cue
 * when a 4 component timestamp's 'hours' component consists
 * of a non-digit character (below U+0030)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, UntilHourBeyondLowBoundary)
{
  loadVtt( "cue-times/until/hour-beyond-low-boundary.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_EXPECTED_TIMESTAMP, 3, 18 );
}

/**
 * Test expecting parser to fail when a 4 component timestamp's 'hours' component consists
 * of a non-digit character (above U+0039)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, UntilHourBeyondHighBoundary)
{
  loadVtt( "cue-times/until/hour-beyond-high-boundary.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_EXPECTED_TIMESTAMP, 3, 18 );
}

/**
 * Test expecting parser to encounter no errors when parsing a valid, well-formed
 * cue timestamp whose 'hours' component's digits are all ASCII digits (U+0030-U+0039)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, UntilHourWithinLowBoundary)
{
  loadVtt( "cue-times/until/hour-within-low-boundary.vtt", 1 );
  assertEquals( getCue( 0 ).endTime(), 10, 02, 780  );
}

/**
 * Test expecting parser to encounter no errors when parsing a valid, well-formed
 * cue timestamp whose 'hours' component's digits are all ASCII digits (U+0030-U+0039)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, UntilHourWithinHighBoundary)
{
  loadVtt( "cue-times/until/hour-within-high-boundary.vtt", 1 );
  assertEquals( getCue( 0 ).endTime(), 9, 10, 02, 780 );
}

/**
 * Bounds checking - 'until' minute
 */
/**
 * Test expecting parser to report an error and skip cue
 * when a 4 component timestamp's 'minutes' component consists
 * of a non-digit character (below U+0030)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, UntilMinuteBeyondLowBoundary)
{
  loadVtt( "cue-times/until/minute-beyond-low-boundary.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_EXPECTED_TIMESTAMP, 3, 18 );
}

/**
 * Test expecting parser to fail when a 4 component timestamp's 'minutes' component consists
 * of a non-digit character (above U+0039)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, UntilMinuteBeyondHighBoundary)
{
  loadVtt( "cue-times/until/minute-beyond-high-boundary.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_EXPECTED_TIMESTAMP, 3, 18 );
}

/**
 * Test expecting parser to encounter no errors when parsing a valid, well-formed
 * cue timestamp whose 'minutes' component's digits are all ASCII digits (U+0030-U+0039)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, UntilMinuteWithinLowBoundary)
{
  loadVtt( "cue-times/until/minute-within-low-boundary.vtt", 1 );
  assertEquals( getCue( 0 ).endTime(), 10, 02, 780 );
}

/**
 * Test expecting parser to encounter no errors when parsing a valid, well-formed
 * cue timestamp whose 'minutes' component's digits are all ASCII digits (U+0030-U+0039)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, UntilMinuteWithinHighBoundary)
{
  loadVtt( "cue-times/until/minute-within-high-boundary.vtt", 1 );
  assertEquals( getCue( 0 ).endTime(), 10, 02, 780 );
}


/**
 * Bounds checking - 'until' second
 */
/**
 * Test expecting parser to report an error and skip cue
 * when a 4 component timestamp's 'seconds' component consists
 * of a non-digit character (below U+0030)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, UntilSecondBeyondLowBoundary)
{
  loadVtt( "cue-times/until/second-beyond-low-boundary.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_EXPECTED_TIMESTAMP, 3, 18 );
}

/**
 * Test expecting parser to fail when a 4 component timestamp's 'seconds' component consists
 * of a non-digit character (above U+0039)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, UntilSecondBeyondHighBoundary)
{
  loadVtt( "cue-times/until/second-beyond-high-boundary.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_EXPECTED_TIMESTAMP, 3, 18 );
}

/**
 * Test expecting parser to encounter no errors when parsing a valid, well-formed
 * cue timestamp whose 'seconds' component's digits are all ASCII digits (U+0030-U+0039)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, UntilSecondWithinLowBoundary)
{
  loadVtt( "cue-times/until/second-within-low-boundary.vtt", 1 );
  assertEquals( getCue( 0 ).endTime(), 10, 02, 780  );
}

/**
 * Test expecting parser to encounter no errors when parsing a valid, well-formed
 * cue timestamp whose 'seconds' component's digits are all ASCII digits (U+0030-U+0039)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, UntilSecondWithinHighBoundary)
{
  loadVtt( "cue-times/until/second-within-high-boundary.vtt", 1 );
  assertEquals( getCue( 0 ).endTime(), 10, 02, 780 );
}

/**
 * Bounds checking - 'until' millisecond
 */
/**
 * Test expecting parser to report an error and skip cue
 * when a 4 component timestamp's 'milliseconds' component consists
 * of a non-digit character (below U+0030)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, UntilMillisecondBeyondLowBoundary)
{
  loadVtt( "cue-times/until/millisecond-beyond-low-boundary.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_EXPECTED_TIMESTAMP, 3, 18 );
}

/**
 * Test expecting parser to fail when a 4 component timestamp's 'milliseconds' component consists
 * of a non-digit character (above U+0039)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, UntilMillisecondBeyondHighBoundary)
{
  loadVtt( "cue-times/until/millisecond-beyond-high-boundary.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_EXPECTED_TIMESTAMP, 3, 18 );
}

/**
 * Test expecting parser to encounter no errors when parsing a valid, well-formed
 * cue timestamp whose 'milliseconds' component's digits are all ASCII digits (U+0030-U+0039)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, UntilMillisecondWithinLowBoundary)
{
  loadVtt( "cue-times/until/millisecond-within-low-boundary.vtt", 1 );
  assertEquals( getCue( 0 ).endTime(), 10, 02, 780  );
}

/**
 * Test expecting parser to encounter no errors when parsing a valid, well-formed
 * cue timestamp whose 'milliseconds' component's digits are all ASCII digits (U+0030-U+0039)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, UntilMillisecondWithinHighBoundary)
{
  loadVtt( "cue-times/until/millisecond-within-high-boundary.vtt", 1 );
  assertEquals( getCue( 0 ).endTime(), 10, 02, 780 );
}

/**
 * Format - 'until' numbers of minute digits
 */
/**
 * Test expecting parser to report an error when a 4 component timestamp's 'minutes' component
 * consists of a single digit between the range of allowed values (00-59)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, UntilOneDigitMinute)
{
  loadVtt( "cue-times/until/minute-1-digit.vtt", 1 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 18 );
  assertEquals( getCue( 0 ).endTime(), 9, 38, 0 );
}

/**
 * Test expecting parser to report no error when a 4 component timestamp's 'minutes' component
 * consists of two digit between the range of allowed values (00-59)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, UntilTwoDigitMinute)
{
  loadVtt( "cue-times/until/minute-2-digit.vtt", 1 );
  assertEquals( getCue( 0 ).endTime(), 0, 2, 0, 0 );
}

/**
 * Test expecting parser to report an error when a 4 component timestamp's 'minutes' component
 * consists of three (or more) digits between the range of allowed values (00-59)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, UntilThreeDigitMinute)
{
  loadVtt( "cue-times/until/minute-3-digit.vtt", 1 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 18 );
  assertEquals( getCue( 0 ).endTime(), 10, 02, 0 );
}

/**
 * Format - 'until' numbers of seconds digits
 */
/**
 * Test expecting parser to report an error when a 4 component timestamp's 'seconds' component
 * consists of a single digit between the range of allowed values (00-59)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, UntilOneDigitSecond)
{
  loadVtt( "cue-times/until/second-1-digit.vtt", 1 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 18 );
  assertEquals( getCue( 0 ).endTime(), 5, 8, 0 );
}

/**
 * Test expecting parser to report no error when a 4 component timestamp's 'seconds' component
 * consists of two digit between the range of allowed values (00-59)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, UntilTwoDigitSecond)
{
  loadVtt( "cue-times/until/second-2-digit.vtt", 1 );
  assertEquals( getCue( 0 ).endTime(), 0, 0, 27, 0 );
}

/**
 * Test expecting parser to report an error when a 4 component timestamp's 'seconds' component
 * consists of three (or more) digits between the range of allowed values (00-59)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, UntilThreeDigitSecond)
{
  loadVtt( "cue-times/until/second-3-digit.vtt", 1 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 18 );
  assertEquals( getCue( 0 ).endTime(), 2, 46, 0 );
}

/**
 * Format - 'until' numbers of milliseconds digits
 */
/**
 * Test expecting parser to report an error when a 4 component timestamp's 'milliseconds' component
 * consists of fewer than three digits between the range of allowed values (00-59)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, UntilTwoDigitMillisecond)
{
  loadVtt( "cue-times/until/millisecond-2-digit.vtt", 1 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 18 );
  assertEquals( getCue( 0 ).endTime(), 10, 2, 90 );
}

/**
 * Test expecting parser to report no error when a 4 component timestamp's 'milliseconds' component
 * consists of three digits between the range of allowed values (000-999)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, UntilThreeDigitMillisecond)
{
  loadVtt( "cue-times/until/millisecond-3-digit.vtt", 1 );
  assertEquals( getCue( 0 ).endTime(), 0, 0, 0, 222 );
}

/**
 * Test expecting parser to report an error when a 4 component timestamp's 'milliseconds' component
 * consists of more than three digits between the range of allowed values (000-999)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes,UntilFourDigitMillisecond)
{
  loadVtt( "cue-times/until/millisecond-4-digit.vtt", 1 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 18 );
  assertEquals( getCue( 0 ).endTime(), 10, 2, 780 );
}

/**
 * Range checking
 */
/**
 * Test expecting parser to fail when a 4 component timestamp's 'minutes' component
 * consists of a value greater than 59
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, UntilMinuteGreaterThan59)
{
  loadVtt( "cue-times/until/minute-greater-than-59.vtt", 1 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 18 );
  assertEquals( getCue( 0 ).endTime(), 2, 0, 6, 0 );
}

/**
 * Test expecting parser to fail when a 4 component timestamp's 'seconds' component
 * consists of a value greater than 59
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, UntilSecondGreaterThan59)
{
  loadVtt( "cue-times/until/second-greater-than-59.vtt", 1 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 18 );
  assertEquals( getCue( 0 ).endTime(), 11, 4, 0 );
}

/**
 * Test expecting parser to fail when a 4 component timestamp's 'milliseconds' component
 * consists of a value greater than 999
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, UntilMillisecondGreaterThan999)
{
  loadVtt( "cue-times/until/millisecond-greater-than-999.vtt", 1 );
  assertEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 18 );
  assertEquals( getCue( 0 ).endTime(), 0, 1, 0 );
}

/**
 * Bad delimiter
 */
/**
 * Test expecting parser to fail when a 4 component timestamp's 'hour' component
 * is separated from the 'minute' component by a character other than U+003A (COLON)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, UntilBadDelimiterHourMinute)
{
  loadVtt( "cue-times/until/bad-delimiter-hour-minute.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_EXPECTED_TIMESTAMP, 3, 18 );
}

/**
 * Test expecting parser to fail when a 4 component timestamp's 'minute' component
 * is separated from the 'second' component by a character other than U+003A (COLON)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 * representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, UntilBadDelimiterMinuteSecond)
{
  loadVtt( "cue-times/until/bad-delimiter-minute-second.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_EXPECTED_TIMESTAMP, 3, 18 );
}

/**
 * Test expecting parser to fail when a 4 component timestamp's 'second' component
 * is separated from the 'milliseconds' component by a character other than U+002E (FULL STOP)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components,
 * in the given order:
 * 1. Optionally (required if hour is non-zero):
 *    a. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 *       NINE (9), representing the hours as a base ten integer.
 *
 *    b. A U+003A COLON character (:)
 *
 * 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 *    representing the minutes as a base ten integer in the range 0 = minutes = 59.
 *
 * 3. A U+003A COLON character (:)
 *
 * 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    seconds as a base ten integer in the range 0 = seconds = 59.
 *
 * 5. A U+002E FULL STOP character (.).
 *
 * 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 *    thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, UntilBadDelimiterSecondMillisecond)
{
  loadVtt( "cue-times/until/bad-delimiter-second-millisecond.vtt", 0 );
  assertEquals( getError( 0 ), WEBVTT_EXPECTED_TIMESTAMP, 3, 18 );
}

/*
 * This tests the bare minimum required for a valid WebVTT file with
 * one cue and no content.
 * CURRENTY DISABLED: Parser does not recognized
 * a cue with no payload as a cue, is returning 0
 * cues founf.
 * ACCORDING TO WEBVTT SPEC DATE: 2012-12-12
 * http://dev.w3.org/html5/webvtt/#webvtt-cue
 * WHICH STATED:
 * A WebVTT cue consists of the following components, in the given order:
 * Optionally, a WebVTT cue identifier followed by a WebVTT line terminator.
 * WebVTT cue timings.
 * Optionally, one or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION
 * (tab) characters followed by WebVTT cue settings.
 * A WebVTT line terminator.
 * The cue payload: either WebVTT cue text, WebVTT chapter title text, or WebVTT
 * metadata text, but it must not contain the substring "-->" (U+002D HYPHEN-MINUS,
 * U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN).
 *
 * Each payload consists of "zero or more" objects, making
 * them optional.
 */
TEST_F(CueTimes, DISABLED_BareMinimum)
{
  loadVtt("cue-times/bare_minimum.vtt", 1);
  ASSERT_EQ(0, errorCount()) << "This file should contain no errors.";
}

/*
 * This tests the bare minimum required for a valid WebVTT file with
 * one cue and sample content.
 * ACCORDING TO WEBVTT SPEC DATE: 2012-12-12
 * http://dev.w3.org/html5/webvtt/#webvtt-cue
 * WHICH STATED:
 * A WebVTT cue consists of the following components, in the given order:
 * Optionally, a WebVTT cue identifier followed by a WebVTT line terminator.
 * WebVTT cue timings.
 * Optionally, one or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION
 * (tab) characters followed by WebVTT cue settings.
 * A WebVTT line terminator.
 * The cue payload: either WebVTT cue text, WebVTT chapter title text, or WebVTT
 * metadata text, but it must not contain the substring "-->" (U+002D HYPHEN-MINUS,
 * U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN).
 */
TEST_F(CueTimes, BareMinimumWithContent)
{
  loadVtt("cue-times/bare_minimum_content.vtt", 1);
  ASSERT_EQ(0, errorCount()) << "This file should contain no errors.";
}

/*
 * This tests the highest legal values in a timestamp.
 * This does not included hours, as the highest legal value
 * of an hour would be the highest value of an int (system-dependent)
 * CURRENTY DISABLED: Parser does not recognized
 * a cue with no payload as a cue, is returning 0
 * cues founf.
 * ACCORDING TO WEBVTT SPEC DATE: 2012-12-12
 * http://dev.w3.org/html5/webvtt/#webvtt-timestamp
 * WHICH STATED:
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds, and thousandths of a
 * second seconds-frac, consists of the following components, in the given order:
 * Optionally (required if hour is non-zero):
 * Two or more ASCII digits, representing the hours as a base ten integer.
 * A U+003A COLON character (:)
 * Two ASCII digits, representing the minutes as a base ten integer in the range 0 ≤ minutes ≤ 59.
 * A U+003A COLON character (:)
 * Two ASCII digits, representing the seconds as a base ten integer in the range 0 ≤ seconds ≤ 59.
 * A U+002E FULL STOP character (.).
 * Three ASCII digits, representing the thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, DISABLED_HighestValues)
{
  loadVtt("cue-times/highest_values.vtt", 1);
  ASSERT_EQ(0, errorCount()) << "This file should contain no errors.";
}

/*
 * This tests a bunch of space and tab characters in between
 * timestamp tokens
 * CURRENTY DISABLED: Parser does not recognized
 * a cue with no payload as a cue, is returning 0
 * cues founf.
 * ACCORDING TO WEBVTT SPEC DATE: 2012-12-12
 * http://dev.w3.org/html5/webvtt/#webvtt-cue-timings
 * WHICH STATED:
 * The WebVTT cue timings part of a WebVTT cue consists of the following components, in the given order:
 * A WebVTT timestamp representing the start time offset of the cue. The time represented by this WebVTT
 * timestamp must be greater than or equal to the start time offsets of all previous cues in the file.
 * One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.
 * The string "-->" (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN).
 * One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.
 * A WebVTT timestamp representing the end time offset of the cue. The time represented by this WebVTT
 * timestamp must be greater than the start time offset of the cue.
 */
TEST_F(CueTimes, DISABLED_SpaceTabs)
{
  loadVtt("cue-times/space_tabs.vtt", 1);
  ASSERT_EQ(0, errorCount()) << "This file should contain no errors.";
}

/*
 * This tests using tabs instead of sapces
 * in between timesetamp tokens
 * ACCORDING TO WEBVTT SPEC DATE: 2012-12-12
 * http://dev.w3.org/html5/webvtt/#webvtt-cue-timings
 * WHICH STATED:
 * The WebVTT cue timings part of a WebVTT cue consists of the following components, in the given order:
 * A WebVTT timestamp representing the start time offset of the cue. The time represented by this WebVTT
 * timestamp must be greater than or equal to the start time offsets of all previous cues in the file.
 * One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.
 * The string "-->" (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN).
 * One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.
 * A WebVTT timestamp representing the end time offset of the cue. The time represented by this WebVTT
 * timestamp must be greater than the start time offset of the cue.
 */
TEST_F(CueTimes, Tabs)
{
  loadVtt("cue-times/tabs.vtt", 1);
  ASSERT_EQ(0, errorCount()) << "This file should contain no errors.";
}

/*
 * This tests the optional hours token in the timestamp
 * CURRENTY DISABLED: Parser does not recognized
 * a cue with no payload as a cue, is returning 0
 * cues founf.
 * ACCORDING TO WEBVTT SPEC DATE: 2012-12-12
 * http://dev.w3.org/html5/webvtt/#webvtt-timestamp
 * WHICH STATED:
 * A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 * and thousandths of a second seconds-frac, consists of the following components, in the given order:
 * Optionally (required if hour is non-zero):
 * Two or more ASCII digits, representing the hours as a base ten integer.
 * A U+003A COLON character (:)
 *.[...]
 */
TEST_F(CueTimes, Hours)
{
  loadVtt("cue-times/hours.vtt", 1);
  ASSERT_EQ(0, errorCount()) << "This file should contain no errors.";
}

/*
 * This tests multiple cues in a vtt file
 * DISABLED as it is returning an error count greater than
 * 0. Will have to debug when I have some time.
 * ACCORDING TO WEBVTT SPEC DATE: 2012-12-12
 * http://dev.w3.org/html5/webvtt/#webvtt-cue-timings
 * WHICH STATED:
 * The WebVTT cue timings part of a WebVTT cue consists of the following components, in the given order:
 * A WebVTT timestamp representing the start time offset of the cue. The time represented by this WebVTT
 * timestamp must be greater than or equal to the start time offsets of all previous cues in the file.
 * [...]
 */
TEST_F(CueTimes, MultiCues)
{
  loadVtt("cue-times/multicues.vtt", 2);
  ASSERT_EQ(0, errorCount()) << "This file should contain no errors.";
}

/*
 * This tests nested cues.
 * DISABLED as it is returning an error count greater than
 * 0. Will have to debug when I have some time.
 * ACCORDING TO WEBVTT SPEC DATE: 2012-12-12
 * http://dev.w3.org/html5/webvtt/#webvtt-file-using-only-nested-cues
 * WHICH STATED:
 * A WebVTT file whose cues all have an end time offset x greater than or equal to the end time offsets
 * of all the cues whose start time offsets are less than x is said to be a WebVTT file using only nested cues.
 */
TEST_F(CueTimes, NestedCues)
{
  loadVtt("cue-times/nestedcues.vtt", 6);
  ASSERT_EQ(0, errorCount()) << "This file should contain no errors.";
}

/*
 * This tests spaces missing between time stamp tokens
 * Because the parser does not validate, the parser should
 * attempt to parse this. Parse.
 * NO ERROR CODE DEFINED FOR THIS CASE YET
 * THEREFORE, THE LOADVTT STATEMENT DOUBLES
 * AS AN ASSERTION THAT THE VTT FILE IS
 * PARSABLE.
 * DISABLED due to std::bad_alloc being thrown
 * ACCORDING TO WEBVTT SPEC DATE: 2012-12-12
 * http://dev.w3.org/html5/webvtt/#webvtt-cue-timings
 * WHICH STATED:
 * The WebVTT cue timings part of a WebVTT cue consists of the following components, in the given order:
 * A WebVTT timestamp representing the start time offset of the cue. The time represented by this WebVTT
 * timestamp must be greater than or equal to the start time offsets of all previous cues in the file.
 * One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.
 * The string "-->" (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN).
 * One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.
 * A WebVTT timestamp representing the end time offset of the cue. The time represented by this WebVTT
 * timestamp must be greater than the start time offset of the cue.
 *
 */
TEST_F(CueTimes, MissingSpaces)
{
  loadVtt("cue-times/missing_spaces.vtt", 1);
}

/*
 * This tests a missing space between left timestamp and arrow token
 * one cue and no content.
 * Because the parser does not validate, the parser should
 * attempt to parse this. Parse.
 * NO ERROR CODE DEFINED FOR THIS CASE YET
 * THEREFORE, THE LOADVTT STATEMENT DOUBLES
 * AS AN ASSERTION THAT THE VTT FILE IS
 * PARSABLE.
 * ACCORDING TO WEBVTT SPEC DATE: 2012-12-12
 * http://dev.w3.org/html5/webvtt/#webvtt-cue-timings
 * WHICH STATED:
 * The WebVTT cue timings part of a WebVTT cue consists of the following components, in the given order:
 * A WebVTT timestamp representing the start time offset of the cue. The time represented by this WebVTT
 * timestamp must be greater than or equal to the start time offsets of all previous cues in the file.
 * One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.
 * The string "-->" (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN).
 * One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.
 * A WebVTT timestamp representing the end time offset of the cue. The time represented by this WebVTT
 * timestamp must be greater than the start time offset of the cue.
 *
 */
TEST_F(CueTimes, MissingSpaceLeft)
{
  loadVtt("cue-times/missing_space_left.vtt", 1);
}

/*
 * This tests a missing space between right timestamp and arrow token
 * one cue and no content.
 * Because the parser does not validate, the parser should
 * attempt to parse this. Parse.
 * NO ERROR CODE DEFINED FOR THIS CASE YET
 * THEREFORE, THE LOADVTT STATEMENT DOUBLES
 * AS AN ASSERTION THAT THE VTT FILE IS
 * PARSABLE.
 * DISABLED due to std::bad_alloc
 * ACCORDING TO WEBVTT SPEC DATE: 2012-12-12
 * http://dev.w3.org/html5/webvtt/#webvtt-cue-timings
 * WHICH STATED:
 * The WebVTT cue timings part of a WebVTT cue consists of the following components, in the given order:
 * A WebVTT timestamp representing the start time offset of the cue. The time represented by this WebVTT
 * timestamp must be greater than or equal to the start time offsets of all previous cues in the file.
 * One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.
 * The string "-->" (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN).
 * One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.
 * A WebVTT timestamp representing the end time offset of the cue. The time represented by this WebVTT
 * timestamp must be greater than the start time offset of the cue.
 *
 */
TEST_F(CueTimes, MissingSpaceRight)
{
  loadVtt("cue-times/missing_space_right.vtt", 1);
}

/*
 * This tests the effect of non-numeric characters
 * in the timestamp.
 * one cue and no content.
 * Because the parser does not validate, the parser should
 * attempt to parse this. Parse.
 * CURRENTY DISABLED: Parser segmentation faults
 * when trying to parse timestamps and encountering
 * any character it is not expecting.
 * ACCORDING TO WEBVTT SPEC DATE: 2012-12-12
 * http://dev.w3.org/html5/webvtt/#webvtt-cue-timings
 * WHICH STATED:
 * The WebVTT cue timings part of a WebVTT cue consists of the following components, in the given order:
 * A WebVTT timestamp representing the start time offset of the cue. The time represented by this WebVTT
 * timestamp must be greater than or equal to the start time offsets of all previous cues in the file.
 * One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.
 * The string "-->" (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN).
 * One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.
 * A WebVTT timestamp representing the end time offset of the cue. The time represented by this WebVTT
 * timestamp must be greater than the start time offset of the cue.
 *
 */
TEST_F(CueTimes, NoNumsInTimeStamp)
{
  loadVtt("cue-times/nonums_in_timestamp.vtt", 1);
  const Error &err = getError( 0 );
  ASSERT_EQ( WEBVTT_MALFORMED_TIMESTAMP, err.error() );
}

/*
 * This tests demonstrates that a WebVTT file
 * fails validation when the --> token is anything
 * but three characters in a row.
 * Because the parser does not validate, the parser should
 * attempt to parse this. Parse.
 * CURRENTY DISABLED: Parser does not recognized
 * a cue with no payload as a cue, is returning 0
 * cues founf.
 * ACCORDING TO WEBVTT SPEC DATE: 2012-12-12
 * http://dev.w3.org/html5/webvtt/#webvtt-cue-timings
 * WHICH STATED:
 * The WebVTT cue timings part of a WebVTT cue consists of the following components, in the given order:
 * [...]
 * The string "-->" (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN).
 * [...]
 */
TEST_F(CueTimes, ArrowsWrongDirection)
{
  loadVtt("cue-times/arrows_wrong_direction.vtt", 1);
  const Error &err = getError( 0 );
  ASSERT_EQ( WEBVTT_MALFORMED_TIMESTAMP, err.error() );
}

/*
 * This tests demonstrates bad timestamps.
 * Because the parser does not validate, the parser should
 * attempt to parse this. Parse.
 * CURRENTY DISABLED: Parser segmentation faults
 * when trying to parse timestamps and encountering
 * any character it is not expecting.
 * ACCORDING TO WEBVTT SPEC DATE: 2012-12-12
 * http://dev.w3.org/html5/webvtt/#webvtt-cue-timings
 * WHICH STATED:
 * The WebVTT cue timings part of a WebVTT cue consists of the following components, in the given order:
 * A WebVTT timestamp representing the start time offset of the cue. The time represented by this WebVTT
 * timestamp must be greater than or equal to the start time offsets of all previous cues in the file.
 * One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.
 * The string "-->" (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN).
 * One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.
 * A WebVTT timestamp representing the end time offset of the cue. The time represented by this WebVTT
 * timestamp must be greater than the start time offset of the cue.
 *
 */
TEST_F(CueTimes, BadTimeStamps1)
{
  loadVtt("cue-times/bad_timestamps_1.vtt", 1);
  const Error &err = getError( 0 );
  ASSERT_EQ( WEBVTT_MALFORMED_TIMESTAMP, err.error() );
}

/*
 * This tests demonstrates bad timestamps.
 * CURRENTY DISABLED: Parser segmentation faults
 * when trying to parse timestamps and encountering
 * any character it is not expecting.
 * ACCORDING TO WEBVTT SPEC DATE: 2012-12-12
 * http://dev.w3.org/html5/webvtt/#webvtt-cue-timings
 * WHICH STATED:
 * The WebVTT cue timings part of a WebVTT cue consists of the following components, in the given order:
 * A WebVTT timestamp representing the start time offset of the cue. The time represented by this WebVTT
 * timestamp must be greater than or equal to the start time offsets of all previous cues in the file.
 * One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.
 * The string "-->" (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS, U+003E GREATER-THAN SIGN).
 * One or more U+0020 SPACE characters or U+0009 CHARACTER TABULATION (tab) characters.
 * A WebVTT timestamp representing the end time offset of the cue. The time represented by this WebVTT
 * timestamp must be greater than the start time offset of the cue.
 *
 */
TEST_F(CueTimes, BadTimeStamps2)
{
  loadVtt("cue-times/bad_timestamps_2.vtt", 1);
  const Error &err = getError( 0 );
  ASSERT_EQ( WEBVTT_MALFORMED_TIMESTAMP, err.error() );
}

/*
 Test expecting parser to succeed when a 4 component timestamp's 'hours' component
 consists of 2 digits at the high end of the valid range (99)

 e.g 99:00:00.000 --> 99:00:05.000

 From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 and thousandths of a second seconds-frac, consists of the following components,
 in the given order:
 1. Optionally (required if hour is non-zero):
 1. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 NINE (9), representing the hours as a base ten integer.

 2. A U+003A COLON character (:)

 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 representing the minutes as a base ten integer in the range 0 ≤ minutes ≤ 59.

 3. A U+003A COLON character (:)

 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 seconds as a base ten integer in the range 0 ≤ seconds ≤ 59.

 5. A U+002E FULL STOP character (.).

 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, StartTimeStampHours2DigitsHigh)
{
  loadVtt( "cue-times/from/timestamp_hours_2_digits_high_good.vtt", 1 );
  ASSERT_EQ(0, errorCount()) << "This file should contain no errors.";
  ASSERT_EQ(99, getCue(0).startTime().hours());
}

TEST_F(CueTimes, EndTimeStampHours2DigitsHigh)
{
  loadVtt( "cue-times/until/timestamp_hours_2_digits_high_good.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 99, getCue(0).endTime().hours() );
}

/*
 Test expecting parser to succeed when a 4 component timestamp's 'hours' component
 consists of 2 digits at the low end of the valid range (00)

 e.g 00:00:00.000 --> 00:00:05.000

 From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 and thousandths of a second seconds-frac, consists of the following components,
 in the given order:
 1. Optionally (required if hour is non-zero):
 1. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 NINE (9), representing the hours as a base ten integer.

 2. A U+003A COLON character (:)

 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 representing the minutes as a base ten integer in the range 0 ≤ minutes ≤ 59.

 3. A U+003A COLON character (:)

 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 seconds as a base ten integer in the range 0 ≤ seconds ≤ 59.

 5. A U+002E FULL STOP character (.).

 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, StartTimeStampHours2DigitsLow)
{
  loadVtt( "cue-times/from/timestamp_hours_2_digits_low_good.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 00, getCue(0).startTime().hours() );
}

TEST_F(CueTimes, EndTimeStampHours2DigitsLow)
{
  loadVtt( "cue-times/until/timestamp_hours_2_digits_low_good.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 00, getCue(0).endTime().hours() );
}

/*
 Test expecting parser to succeed when a 4 component timestamp's 'hours' component
 consists of 2 digits at the middle of the valid range (54)

 e.g. 54:00:00.000 --> 54:00:05.000

 From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 and thousandths of a second seconds-frac, consists of the following components,
 in the given order:
 1. Optionally (required if hour is non-zero):
 1. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 NINE (9), representing the hours as a base ten integer.

 2. A U+003A COLON character (:)

 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 representing the minutes as a base ten integer in the range 0 ≤ minutes ≤ 59.

 3. A U+003A COLON character (:)

 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 seconds as a base ten integer in the range 0 ≤ seconds ≤ 59.

 5. A U+002E FULL STOP character (.).

 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, StartTimeStampHours2DigitsMiddle)
{
  loadVtt( "cue-times/from/timestamp_hours_2_digits_mid_good.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 54, getCue(0).startTime().hours() );
}

TEST_F(CueTimes, EndTimeStampHours2DigitsMiddle)
{
  loadVtt( "cue-times/until/timestamp_hours_2_digits_mid_good.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 54, getCue(0).endTime().hours() );
}

/*
 Test expecting parser to succeed when a 4 component timestamp's 'hours' component
 consists of more than 2 digits at the high end of the valid range

 e.g 9999:00:00.000 --> 9999:00:05.000

 From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 and thousandths of a second seconds-frac, consists of the following components,
 in the given order:
 1. Optionally (required if hour is non-zero):
 1. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 NINE (9), representing the hours as a base ten integer.

 2. A U+003A COLON character (:)

 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 representing the minutes as a base ten integer in the range 0 ≤ minutes ≤ 59.

 3. A U+003A COLON character (:)

 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 seconds as a base ten integer in the range 0 ≤ seconds ≤ 59.

 5. A U+002E FULL STOP character (.).

 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, StartTimeStampHoursNDigitsHigh)
{
  loadVtt( "cue-times/from/timestamp_hours_n_digits_high_good.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 9999, getCue(0).startTime().hours() );
}

TEST_F(CueTimes, EndTimeStampHoursNDigitsHigh)
{
  loadVtt( "cue-times/until/timestamp_hours_n_digits_high_good.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 9999, getCue(0).endTime().hours() );
}

/*
 Test expecting parser to succeed when a 4 component timestamp's 'hours' component
 consists of more than 2 digits at the low end of the valid range

 e.g. 0000:00:00.000 --> 0000:00:05.000

 From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 and thousandths of a second seconds-frac, consists of the following components,
 in the given order:
 1. Optionally (required if hour is non-zero):
 1. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 NINE (9), representing the hours as a base ten integer.

 2. A U+003A COLON character (:)

 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 representing the minutes as a base ten integer in the range 0 ≤ minutes ≤ 59.

 3. A U+003A COLON character (:)

 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 seconds as a base ten integer in the range 0 ≤ seconds ≤ 59.

 5. A U+002E FULL STOP character (.).

 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, StartTimeStampHoursNDigitsLow)
{
  loadVtt( "cue-times/from/timestamp_hours_n_digits_low_good.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 0000, getCue(0).startTime().hours() );
}

TEST_F(CueTimes, EndTimeStampHoursNDigitsLow)
{
  loadVtt( "cue-times/until/timestamp_hours_n_digits_low_good.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 0000, getCue(0).endTime().hours() );
}

/*
 Test expecting parser to succeed when a 4 component timestamp's 'hours' component
 consists of more than 2 digits at the middle of the valid range

 e.g. 5544:00:00.000 --> 5544:00:05.000

 From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 and thousandths of a second seconds-frac, consists of the following components,
 in the given order:
 1. Optionally (required if hour is non-zero):
 1. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 NINE (9), representing the hours as a base ten integer.

 2. A U+003A COLON character (:)

 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 representing the minutes as a base ten integer in the range 0 ≤ minutes ≤ 59.

 3. A U+003A COLON character (:)

 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 seconds as a base ten integer in the range 0 ≤ seconds ≤ 59.

 5. A U+002E FULL STOP character (.).

 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, StartTimeStampHoursNDigitsMiddle)
{
  loadVtt( "cue-times/from/timestamp_hours_n_digits_mid_good.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 5544, getCue(0).startTime().hours() );
}

TEST_F(CueTimes, EndTimeStampHoursNDigitsMiddle)
{
  loadVtt( "cue-times/until/timestamp_hours_n_digits_mid_good.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 5544, getCue(0).endTime().hours() );
}

/*
 Test expecting parser to succeed when a 4 component timestamp's 'hours' component
 and it's delimiter is omitted.

 e.g. 00:00.000 --> 00:05.000

 From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 and thousandths of a second seconds-frac, consists of the following components,
 in the given order:
 1. Optionally (required if hour is non-zero):
 1. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 NINE (9), representing the hours as a base ten integer.

 2. A U+003A COLON character (:)

 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 representing the minutes as a base ten integer in the range 0 ≤ minutes ≤ 59.

 3. A U+003A COLON character (:)

 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 seconds as a base ten integer in the range 0 ≤ seconds ≤ 59.

 5. A U+002E FULL STOP character (.).

 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 thousandths of a second seconds-frac as a base ten integer.
 */

TEST_F(CueTimes, TimeStampHoursOmitted)
{
  loadVtt( "cue-times/from/timestamp_hours_omitted_good.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

/*
 Test expecting parser to succeed when a 4 component timestamp's 'seconds-frac' component
 is a 3 digit character at the high end of the valid range
 e.g. 00:00:00.999 --> 00:00:01.999

 From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 and thousandths of a second seconds-frac, consists of the following components,
 in the given order:
 1. Optionally (required if hour is non-zero):
 1. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 NINE (9), representing the hours as a base ten integer.

 2. A U+003A COLON character (:)

 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 representing the minutes as a base ten integer in the range 0 ≤ minutes ≤ 59.

 3. A U+003A COLON character (:)

 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 seconds as a base ten integer in the range 0 ≤ seconds ≤ 59.

 5. A U+002E FULL STOP character (.).

 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, StartTimeStampMilliSecondsHigh)
{
  loadVtt( "cue-times/from/timestamp_milliseconds_high_good.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 999, getCue(0).startTime().milliseconds() );
}

TEST_F(CueTimes, EndTimeStampMilliSecondsHigh)
{
  loadVtt( "cue-times/until/timestamp_milliseconds_high_good.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 999, getCue(0).endTime().milliseconds() );
}

/*
 Test expecting parser to succeed when a 4 component timestamp's 'seconds-frac' component
 is a 3 digit character at the low end of the valid range
 e.g. 00:00:00.000 --> 00:00:01.000

 From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 and thousandths of a second seconds-frac, consists of the following components,
 in the given order:
 1. Optionally (required if hour is non-zero):
 1. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 NINE (9), representing the hours as a base ten integer.

 2. A U+003A COLON character (:)

 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 representing the minutes as a base ten integer in the range 0 ≤ minutes ≤ 59.

 3. A U+003A COLON character (:)

 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 seconds as a base ten integer in the range 0 ≤ seconds ≤ 59.

 5. A U+002E FULL STOP character (.).

 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 thousandths of a second seconds-frac as a base ten integer.
 */

TEST_F(CueTimes, StartTimeStampMilliSecondsLow)
{
  loadVtt( "cue-times/from/timestamp_milliseconds_low_good.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 000, getCue(0).startTime().milliseconds() );
}

TEST_F(CueTimes, EndTimeStampMilliSecondsLow)
{
  loadVtt( "cue-times/until/timestamp_milliseconds_low_good.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 000, getCue(0).endTime().milliseconds() );
}

/*
 Test expecting parser to succeed when a 4 component timestamp's 'seconds-frac' component
 is a 3 digit character at the middle of the valid range
 e.g. 00:00:00.555 --> 00:00:01.555

 From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 and thousandths of a second seconds-frac, consists of the following components,
 in the given order:
 1. Optionally (required if hour is non-zero):
 1. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 NINE (9), representing the hours as a base ten integer.

 2. A U+003A COLON character (:)

 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 representing the minutes as a base ten integer in the range 0 ≤ minutes ≤ 59.

 3. A U+003A COLON character (:)

 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 seconds as a base ten integer in the range 0 ≤ seconds ≤ 59.

 5. A U+002E FULL STOP character (.).

 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, StartTimeStampMilliSecondsMiddle)
{
  loadVtt( "cue-times/from/timestamp_milliseconds_mid_good.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 555, getCue(0).startTime().milliseconds() );
}

TEST_F(CueTimes, EndTimeStampMilliSecondsMiddle)
{
  loadVtt( "cue-times/until/timestamp_milliseconds_mid_good.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 555, getCue(0).endTime().milliseconds() );
}

/*
 Test expecting parser to succeed when a 4 component timestamp's 'minutes' component
 is a 2 digit character at the high end of the valid range
 e.g. 00:59:00.000 --> 00:59:00.999

 From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 and thousandths of a second seconds-frac, consists of the following components,
 in the given order:
 1. Optionally (required if hour is non-zero):
 1. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 NINE (9), representing the hours as a base ten integer.

 2. A U+003A COLON character (:)

 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 representing the minutes as a base ten integer in the range 0 ≤ minutes ≤ 59.

 3. A U+003A COLON character (:)

 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 seconds as a base ten integer in the range 0 ≤ seconds ≤ 59.

 5. A U+002E FULL STOP character (.).

 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, StartTimeStampMinutesHigh)
{
  loadVtt( "cue-times/from/timestamp_minutes_high_good.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 59, getCue(0).startTime().minutes() );
}

TEST_F(CueTimes, EndTimeStampMinutesHigh)
{
  loadVtt( "cue-times/until/timestamp_minutes_high_good.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 59, getCue(0).endTime().minutes() );
}

/*
 Test expecting parser to succeed when a 4 component timestamp's 'minutes' component
 is a 2 digit character at the low end of the valid range
 e.g. 00:00:00.000 --> 00:00:00.999

 From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 and thousandths of a second seconds-frac, consists of the following components,
 in the given order:
 1. Optionally (required if hour is non-zero):
 1. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 NINE (9), representing the hours as a base ten integer.

 2. A U+003A COLON character (:)

 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 representing the minutes as a base ten integer in the range 0 ≤ minutes ≤ 59.

 3. A U+003A COLON character (:)

 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 seconds as a base ten integer in the range 0 ≤ seconds ≤ 59.

 5. A U+002E FULL STOP character (.).

 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, StartTimeStampMinutesLow)
{
  loadVtt( "cue-times/from/timestamp_minutes_low_good.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 00, getCue(0).startTime().minutes() );
}

TEST_F(CueTimes, EndTimeStampMinutesLow)
{
  loadVtt( "cue-times/until/timestamp_minutes_low_good.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 00, getCue(0).endTime().minutes() );
}

/*
 Test expecting parser to succeed when a 4 component timestamp's 'minutes' component
 is a 2 digit character at the middle of the valid range
 e.g. 00:30:00.000 --> 00:30:00.999

 From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 and thousandths of a second seconds-frac, consists of the following components,
 in the given order:
 1. Optionally (required if hour is non-zero):
 1. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 NINE (9), representing the hours as a base ten integer.

 2. A U+003A COLON character (:)

 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 representing the minutes as a base ten integer in the range 0 ≤ minutes ≤ 59.

 3. A U+003A COLON character (:)

 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 seconds as a base ten integer in the range 0 ≤ seconds ≤ 59.

 5. A U+002E FULL STOP character (.).

 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 thousandths of a second seconds-frac as a base ten integer.
 */

TEST_F(CueTimes, StartTimeStampMinutesMiddle)
{
  loadVtt( "cue-times/from/timestamp_minutes_mid_good.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 30, getCue(0).startTime().minutes() );
}

TEST_F(CueTimes, EndTimeStampMinutesMiddle)
{
  loadVtt( "cue-times/until/timestamp_minutes_mid_good.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 30, getCue(0).endTime().minutes() );
}

/*
 Test expecting parser to succeed when a 4 component timestamp's 'seconds' component
 is a 2 digit character at the high end of the valid range
 e.g. 00:00:59.000 --> 00:00:59.999

 From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 and thousandths of a second seconds-frac, consists of the following components,
 in the given order:
 1. Optionally (required if hour is non-zero):
 1. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 NINE (9), representing the hours as a base ten integer.

 2. A U+003A COLON character (:)

 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 representing the minutes as a base ten integer in the range 0 ≤ minutes ≤ 59.

 3. A U+003A COLON character (:)

 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 seconds as a base ten integer in the range 0 ≤ seconds ≤ 59.

 5. A U+002E FULL STOP character (.).

 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, StartTimeStampSecondsHigh)
{
  loadVtt( "cue-times/from/timestamp_seconds_high_good.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 59, getCue(0).startTime().seconds() );
}

TEST_F(CueTimes, EndTimeStampSecondsHigh)
{
  loadVtt( "cue-times/until/timestamp_seconds_high_good.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 59, getCue(0).endTime().seconds() );
}

/*
 Test expecting parser to succeed when a 4 component timestamp's 'seconds' component
 is a 2 digit character at the low end of the valid range
 e.g. 00:00:00.000 --> 00:00:00.999

 From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 and thousandths of a second seconds-frac, consists of the following components,
 in the given order:
 1. Optionally (required if hour is non-zero):
 1. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 NINE (9), representing the hours as a base ten integer.

 2. A U+003A COLON character (:)

 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 representing the minutes as a base ten integer in the range 0 ≤ minutes ≤ 59.

 3. A U+003A COLON character (:)

 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 seconds as a base ten integer in the range 0 ≤ seconds ≤ 59.

 5. A U+002E FULL STOP character (.).

 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, StartTimeStampSecondsLow)
{
  loadVtt( "cue-times/from/timestamp_seconds_low_good.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 00, getCue(0).startTime().seconds() );
}

TEST_F(CueTimes, EndTimeStampSecondsLow)
{
  loadVtt( "cue-times/until/timestamp_seconds_low_good.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 00, getCue(0).endTime().seconds() );
}

/*
 Test expecting parser to succeed when a 4 component timestamp's 'seconds' component
 is a 2 digit character at the middle of the valid range
 e.g. 00:00:30.000 --> 00:00:30.999

 From http://dev.w3.org/html5/webvtt/#webvtt-timestamp (10/15/2012):
 A WebVTT timestamp representing hours hours, minutes minutes, seconds seconds,
 and thousandths of a second seconds-frac, consists of the following components,
 in the given order:
 1. Optionally (required if hour is non-zero):
 1. Two or more characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT
 NINE (9), representing the hours as a base ten integer.

 2. A U+003A COLON character (:)

 2. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9),
 representing the minutes as a base ten integer in the range 0 ≤ minutes ≤ 59.

 3. A U+003A COLON character (:)

 4. Two characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 seconds as a base ten integer in the range 0 ≤ seconds ≤ 59.

 5. A U+002E FULL STOP character (.).

 6. Three characters in the range U+0030 DIGIT ZERO (0) to U+0039 DIGIT NINE (9), representing the
 thousandths of a second seconds-frac as a base ten integer.
 */
TEST_F(CueTimes, StartTimeStampSecondsMiddle)
{
  loadVtt( "cue-times/from/timestamp_seconds_mid_good.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 30, getCue(0).startTime().seconds() );
}

TEST_F(CueTimes, EndTimeStampSecondsMiddle)
{
  loadVtt( "cue-times/until/timestamp_seconds_mid_good.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 30, getCue(0).endTime().seconds() );
}
