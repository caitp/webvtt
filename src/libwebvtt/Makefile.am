lib_LTLIBRARIES = libwebvtt.la
noinst_LTLIBRARIES = libwebvtt-static.la

#Mangled config file
BUILT_SOURCES = $(top_builddir)/include/webvtt/webvtt-config.h

$(top_builddir)/include/webvtt/webvtt-config.h: $(top_builddir)/config.h
	@cat $< | sed "s/#define \([[:alpha:]_]\{1,\}\)/#define WEBVTT_\1/" > $@

WEBVTT_SOURCES = alloc.c cue.c cuetext.c error.c lexer.c parser.c string.c \
		 cue_internal.h cuetext_internal.h \
		 parser_internal.h string_internal.h \
		 $(top_builddir)/include/webvtt/webvtt-config.h
WEBVTT_CFLAGS = -I$(top_builddir)/include -I$(top_srcdir)/include

libwebvtt_la_LDFLAGS = -no-undefined -shared
libwebvtt_la_CPPFLAGS = -DWEBVTT_BUILD_LIBRARY=1 $(WEBVTT_CFLAGS)
libwebvtt_la_SOURCES = $(WEBVTT_SOURCES)

libwebvtt_static_la_LDFLAGS = -no-undefined -static
libwebvtt_static_la_CPPFLAGS = -DWEBVTT_STATIC=1 $(WEBVTT_CFLAGS)
libwebvtt_static_la_SOURCES = $(WEBVTT_SOURCES)
