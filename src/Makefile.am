AUTOMAKE_OPTIONS = subdir-objects
lib_LTLIBRARIES = \
    libmobacommon.la

libmobacommon_la_SOURCES = \
    helper.cpp \
    ipc.cpp \
    log.cpp \
    signalhandler.cpp \
    version.cpp

otherincludedir = \
    $(includedir)/moba-common

otherinclude_HEADERS = \
    exception.h \
    atomic.h \
    helper.h \
    ipc.h \
    log.h \
    ringbuffer.h \
    signalhandler.h \
    version.h

ACLOCAL_AMFLAGS = \
    -I m4

CLEANFILES = \
    *~

AM_CPPFLAGS = \
    -g3 -g -ggdb -O3 -Wall
