noinst_PROGRAMS = parsevtt
parsevtt_CFLAGS = -DWEBVTT_STATIC=1 -I$(top_builddir)/include -I$(top_srcdir)/include
parsevtt_SOURCES = parsevtt_main.c
parsevtt_LDFLAGS = -static
parsevtt_LDADD = ../libwebvtt/libwebvtt-static.la