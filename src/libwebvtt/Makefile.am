# Copyright (c) 2013 Mozilla Foundation and Contributors
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#
#  - Redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer.
#  - Redistributions in binary form must reproduce the above copyright
# notice, this list of conditions and the following disclaimer in the
# documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
lib_LTLIBRARIES = libwebvtt.la
noinst_LTLIBRARIES = libwebvtt-static.la

WEBVTT_SOURCES = alloc.c cue.c cuetext.c error.c lexer.c \
		 node.c parser.c string.c node_list.c \
		 cue_internal.h cuetext_internal.h node_internal.h \
		 parser_internal.h string_internal.h
WEBVTT_CFLAGS = -I$(top_builddir)/include -I$(top_srcdir)/include

libwebvtt_la_LDFLAGS = -no-undefined -shared
libwebvtt_la_CPPFLAGS = -DWEBVTT_BUILD_LIBRARY=1 $(WEBVTT_CFLAGS)
libwebvtt_la_SOURCES = $(WEBVTT_SOURCES)

libwebvtt_static_la_LDFLAGS = -no-undefined -static
libwebvtt_static_la_CPPFLAGS = -DWEBVTT_STATIC=1 $(WEBVTT_CFLAGS)
libwebvtt_static_la_SOURCES = $(WEBVTT_SOURCES)
