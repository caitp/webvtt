lib_LTLIBRARIES = libwebvttxx.la
noinst_LTLIBRARIES = libwebvttxx-static.la

#Mangled config file
BUILT_SOURCES = $(top_builddir)/include/webvtt/webvtt-config.h

$(top_builddir)/include/webvtt/webvtt-config.h: $(top_builddir)/config.h
	@cat $< | sed "s/#define \([[:alpha:]_]\{1,\}\)/#define WEBVTT_\1/" > $@

WEBVTTXX_SOURCES = abstract_parser.cpp file_parser.cpp node.cpp nodefactory.cpp $(top_builddir)/include/webvtt/webvtt-config.h
WEBVTTXX_CFLAGS = -I$(top_builddir)/include -I$(top_srcdir)/include

libwebvttxx_la_LDFLAGS = -no-undefined -shared
libwebvttxx_la_CPPFLAGS = -DWEBVTTXX_BUILD_LIBRARY=1 $(WEBVTTXX_CFLAGS)
libwebvttxx_la_CXXFLAGS = $(libwebvttxx_la_CPPFLAGS)
libwebvttxx_la_SOURCES = $(WEBVTTXX_SOURCES)
libwebvttxx_la_LIBADD = ../libwebvtt/libwebvtt.la

libwebvttxx_static_la_LDFLAGS = -no-undefined -static
libwebvttxx_static_la_CPPFLAGS = -DWEBVTT_STATIC=1 -DWEBVTTXX_STATIC=1 $(WEBVTTXX_CFLAGS)
libwebvttxx_static_la_CXXFLAGS = $(libwebvttxx_static_la_CPPFLAGS)
libwebvttxx_static_la_SOURCES = $(WEBVTTXX_SOURCES)
libwebvttxx_static_la_LIBADD = $(top_builddir)/src/libwebvtt/libwebvtt-static.la
