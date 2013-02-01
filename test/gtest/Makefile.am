# Build Google Test from fused source file, see:
# http://code.google.com/p/googletest/wiki/V1_6_AdvancedGuide#Fusing_Google_Test_Source_Files

check_LTLIBRARIES = libgtest.la libgtest_main.la

libgtest_la_SOURCES = gtest/gtest.h gtest-all.cc
libgtest_la_CPPFLAGS = $(GTEST_CPPFLAGS) -I$(top_srcdir)/test/gtest
libgtest_la_LDFLAGS = -L$(top_builddir)/test/gtest
libgtest_la_LIBADD = $(GTEST_LIBS)

libgtest_main_la_SOURCES = gtest/gtest.h gtest_main.cc
libgtest_main_la_CPPFLAGS = $(GTEST_CPPFLAGS) -I$(top_srcdir)/test/gtest
libgtest_main_la_LDFLAGS = -L$(top_builddir)/test/gtest
libgtest_main_la_LIBADD = $(GTEST_LIBS) libgtest.la
