AUTOMAKE_OPTIONS = subdir-objects
lib_LTLIBRARIES = \
    libmobacommon.la

libmobacommon_la_SOURCES = \
    helper.cpp \
    ipc.cpp \
    signalhandler.cpp \
    version.cpp \
    ini.cpp \
    daemon.cpp

otherincludedir = \
    $(includedir)/moba-common

otherinclude_HEADERS = \
    daemon.h \
    drivingdirection.h \
    enumswitchstand.h \
    exception.h \
    helper.h \
    ini.h \
    ipc.h \
    ringbuffer.h \
    signalhandler.h \
    version.h

ACLOCAL_AMFLAGS = \
    -I m4

libmobacommon_la_LIBADD = \
    $(GLIB_LIBS)

AM_CPPFLAGS = \
    $(GLIB_CFLAGS) \
    -ggdb -g3 -O3 -Wall -Wno-deprecated-declarations

CLEANFILES = \
    *~
