AUTOMAKE_OPTIONS = subdir-objects
lib_LTLIBRARIES = \
    libmobacommon.la

libmobacommon_la_SOURCES = \
    helper.cpp \
    ipc.cpp \
    log.cpp \
    signalhandler.cpp \
    version.cpp \
    ini.cpp \
    daemon.cpp

otherincludedir = \
    $(includedir)/moba-common

otherinclude_HEADERS = \
    exception.h \
    helper.h \
    ipc.h \
    log.h \
    ringbuffer.h \
    signalhandler.h \
    version.h \
    ini.h \
    daemon.h

ACLOCAL_AMFLAGS = \
    -I m4

AM_CPPFLAGS = \
    $(GLIB_CFLAGS) \
    -ggdb -g3 -O3 -Wall -Wno-deprecated-declarations

CLEANFILES = \
    *~
