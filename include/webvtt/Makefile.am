#Install locations
webvttincludedir = $(includedir)/webvtt

#Mangled config file
BUILT_SOURCES = $(builddir)/webvtt-config.h
CLEANFILES = $(builddir)/webvtt-config.h

$(builddir)/webvtt-config.h: $(top_builddir)/config.h Makefile
	@cat $< | sed "s/#define \([[:alpha:]_]\{1,\}\)/#define WEBVTT_\1/" > $@

#C API headers
webvttinclude_HEADERS = \
  $(builddir)/webvtt-config.h \
  webvtt-config-win32.h \
  cue.h \
  error.h \
  parser.h \
  string.h \
  util.h
