/* Define to 1 if your system has a GNU libc compatible `malloc' function, and
   to 0 otherwise. */
#define WEBVTT_HAVE_MALLOC 1

/* Define to 1 if you have the <memory.h> header file. */
#define WEBVTT_HAVE_MEMORY_H 1

#if (defined(_MSC_VER) && _MSC_VER >= 1600) || (__STDC_VERSION__ >= 199901L)
/* C99 Headers */
/* Define to 1 if you have the <stdint.h> header file. */
#define WEBVTT_HAVE_STDINT_H 1

#endif

/* Define to 1 if you have the <stdlib.h> header file. */
#define WEBVTT_HAVE_STDLIB_H 1

/* Define if strerror() is available */
#define WEBVTT_HAVE_STRERROR 1

/* Define to 1 if you have the <string.h> header file. */
#define WEBVTT_HAVE_STRING_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define WEBVTT_HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define WEBVTT_HAVE_SYS_TYPES_H 1

#ifndef _MSC_VER
/* MSVC does not provide unistd.h */
/* Define to 1 if you have the <unistd.h> header file. */
#define WEBVTT_HAVE_UNISTD_H 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define WEBVTT_HAVE_INTTYPES_H 1
#endif

/* Name of package */
#define WEBVTT_PACKAGE "webvtt"

/* Define to the address where bug reports for this package should be sent. */
#define WEBVTT_PACKAGE_BUGREPORT ""

/* Define to the full name of this package. */
#define WEBVTT_PACKAGE_NAME "webvtt"

/* Define to the full name and version of this package. */
#define WEBVTT_PACKAGE_STRING "webvtt 0.0.2"

/* Define to the one symbol short name of this package. */
#define WEBVTT_PACKAGE_TARNAME "webvtt"

/* Define to the home page for this package. */
#define WEBVTT_PACKAGE_URL ""

/* Define to the version of this package. */
#define WEBVTT_PACKAGE_VERSION "0.0.2"

/* Define to 1 if you have the ANSI C header files. */
#define WEBVTT_STDC_HEADERS 1

/* Version number of package */
#define WEBVTT_VERSION "0.0.2"

/* Define to rpl_malloc if the replacement function should be used. */
/* #undef malloc */
