AUTOMAKE_OPTIONS = subdir-objects
lib_LTLIBRARIES = \
    libMoBaCommon.la

libMoBaCommon_la_SOURCES = \
    helper.cpp \
    ipc.cpp \
    jsondecoder.cpp \
    jsonstreamreadersocket.cpp \
    log.cpp \
    signalhandler.cpp \
    version.cpp

otherincludedir = \
    $(includedir)/moba

otherinclude_HEADERS = \
    exception.h \
    atomic.h \
    helper.h \
    ipc.h \
    jsonabstractitem.h \
    jsondecoder.h \
    jsonstreamreader.h \
    jsonstreamreadersocket.h \
    log.h \
    ringbuffer.h \
    signalhandler.h \
    version.h

ACLOCAL_AMFLAGS = \
    -I m4

CLEANFILES = \
    *~

