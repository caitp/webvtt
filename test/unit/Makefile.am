# Unit tests to be run.
AM_CPPFLAGS = \
  -DWEBVTT_STATIC=1 \
  -I$(top_builddir)/include \
  -I$(top_srcdir)/include \
  -I$(top_srcdir)/src/libwebvtt \
  -I$(top_srcdir)/test/gtest \
  -I$(top_srcdir)/src \
  $(GTEST_CPPFLAGS)

AM_CXXFLAGS = $(AM_CPPFLAGS) $(CXXFLAGS)
AM_LDFLAGS = -static -lm

# Add subdirectories containing test files here:
EXTRA_DIST = \
  cue-ids \
  cue-settings \
  cue-times \
  filestructure \
  payload \
  regressions

LIBS = \
  $(top_builddir)/src/libwebvtt/libwebvtt-static.la \
  $(top_builddir)/src/libwebvttxx/libwebvttxx-static.la \
  $(top_builddir)/test/gtest/libgtest_main.la \
  $(top_builddir)/test/gtest/libgtest.la \
  $(GTEST_LIBS)

LDADD = $(LIBS)

INTERNAL_TESTS = \
  lexer_unittest \
  readcuetext_unittest \
  string_unittest \
  datastatetokenizer_unittest \
  escapestatetokenizer_unittest \
  tagstatetokenizer_unittest \
  starttagstatetokenizer_unittest \
  annotationstatetokenizer_unittest \
  endtagstatetokenizer_unittest \
  timestamptokenizer_unittest \
  tagclasstokenizer_unittest \
  stringlist_unittest \
	setcuesettings_unittest

FILESTRUCTURE_TESTS = \
  filestructure_unittest

CUESETTINGS_TESTS = \
  csgeneric_unittest \
  csline_unittest \
  cssize_unittest \
  csposition_unittest \
  csvertical_unittest \
  csalign_unittest

CUETIMES_TESTS = \
  cuetimes_unittest \
  ctgenstructure_unittest

CUEIDS_TESTS = \
  ciarrow_unittest \
  cigeneral_unittest \
  cilanguage_unittest \
  cilineendings_unittest

PAYLOAD_TESTS = \
  plboldtag_unittest \
  plclasstag_unittest \
  plescapecharacter_unittest \
  plformat_unittest \
  plitalictag_unittest \
  pltagformat_unittest \
  pltimestamp_unittest \
  plunderlinetag_unittest \
  plvoicetag_unittest \
  plrubytag_unittest \
  pllangtag_unittest

# Test set representing reproduction of reported library bugs.
# Do not check in code that changes one of these from a passing
# to a failing state.
#
# These are not unit tests, and do not necessarily represent small
# units of code.
REGRESSION_TESTS = regression_tests

UNIT_TESTS = \
  $(INTERNAL_TESTS) \
  $(FILESTRUCTURE_TESTS) \
  $(CUESETTINGS_TESTS) \
  $(CUETIMES_TESTS) \
  $(CUEIDS_TESTS) \
  $(PAYLOAD_TESTS)

# On TravisCI, we run valgrind for unit tests with --exit-exitcode=1,
# which means otherwise passing tests fail when valgrind fails leak-check.
# Tests added to KNOWN_VALGRIND_TEST_FAILURES will not cause the test run
# to fail. You can run tests with valgrind like so:
#
#   ./configure --enable-valgrind-testing
#   make && make check
KNOWN_VALGRIND_TEST_FAILURES =
if VALGRIND_TESTING
KNOWN_VALGRIND_TEST_FAILURES +=
endif

# Tests we expect to fail (i.e., known-fails)
XFAIL_TESTS = $(KNOWN_VALGRIND_TEST_FAILURES)

# TODO: OS X needs to filer gtest valgrind warnings:
# valgrind ... <unittest> 2>&1 | sed -e "/warning: addVar:/d"
TESTS = $(UNIT_TESTS) $(REGRESSION_TESTS)
TESTS_ENVIRONMENT = TEST_FILE_DIR=$(srcdir) \
                    $(VALGRIND_ENVIRONMENT)

noinst_PROGRAMS = $(UNIT_TESTS) $(REGRESSION_TESTS)

# gtest fragments
EXTRA_DIST += cue_testfixture \
              payload_testfixture \
              cuetexttokenizer_fixture \
              test_parser \
              regression_testfixture

# Utility unit tests
lexer_unittest_SOURCES = lexer_unittest.cpp
readcuetext_unittest_SOURCES = readcuetext_unittest.cpp
string_unittest_SOURCES = string_unittest.cpp
datastatetokenizer_unittest_SOURCES = datastatetokenizer_unittest.cpp
escapestatetokenizer_unittest_SOURCES = escapestatetokenizer_unittest.cpp
tagstatetokenizer_unittest_SOURCES = tagstatetokenizer_unittest.cpp
starttagstatetokenizer_unittest_SOURCES = starttagstatetokenizer_unittest.cpp
annotationstatetokenizer_unittest_SOURCES = annotationstatetokenizer_unittest.cpp
endtagstatetokenizer_unittest_SOURCES = endtagstatetokenizer_unittest.cpp
timestamptokenizer_unittest_SOURCES = timestamptokenizer_unittest.cpp
tagclasstokenizer_unittest_SOURCES = tagclasstokenizer_unittest.cpp
stringlist_unittest_SOURCES = stringlist_unittest.cpp
setcuesettings_unittest_SOURCES = setcuesettings_unittest.cpp

filestructure_unittest_SOURCES = filestructure_unittest.cpp
# Cue Settings tests
csgeneric_unittest_SOURCES = csgeneric_unittest.cpp
csline_unittest_SOURCES = csline_unittest.cpp
cssize_unittest_SOURCES = cssize_unittest.cpp
csposition_unittest_SOURCES = csposition_unittest.cpp
csvertical_unittest_SOURCES = csvertical_unittest.cpp
csalign_unittest_SOURCES = csalign_unittest.cpp

# Cue Times tests
cuetimes_unittest_SOURCES = cuetimes_unittest.cpp
ctgenstructure_unittest_SOURCES = ctgenstructure_unittest.cpp

# Cue Ids Tests
ciarrow_unittest_SOURCES = ciarrow_unittest.cpp
cigeneral_unittest_SOURCES = cigeneral_unittest.cpp
cilanguage_unittest_SOURCES = cilanguage_unittest.cpp
cilineendings_unittest_SOURCES = cilineendings_unittest.cpp

# Payload Tests
plboldtag_unittest_SOURCES = plboldtag_unittest.cpp
plclasstag_unittest_SOURCES = plclasstag_unittest.cpp
plescapecharacter_unittest_SOURCES = plescapecharacter_unittest.cpp
plformat_unittest_SOURCES  = plformat_unittest.cpp
plitalictag_unittest_SOURCES = plitalictag_unittest.cpp
pltagformat_unittest_SOURCES = pltagformat_unittest.cpp
pltimestamp_unittest_SOURCES = pltimestamp_unittest.cpp
plunderlinetag_unittest_SOURCES = plunderlinetag_unittest.cpp
plvoicetag_unittest_SOURCES = plvoicetag_unittest.cpp
plrubytag_unittest_SOURCES = plrubytag_unittest.cpp
pllangtag_unittest_SOURCES = pllangtag_unittest.cpp

# Regression Tests
regression_tests_SOURCES = regression_tests.cpp
