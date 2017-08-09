AUTOMAKE_OPTIONS = subdir-objects
lib_LTLIBRARIES = \
    libMoBaCommon.la

libMoBaCommon_la_SOURCES = \
    helper.cpp \
    ipc.cpp \
    jsondecoder.cpp \
    jsonmsgdecoder.cpp \
    jsonmsgencoder.cpp \
    jsonstreamreadersocket.cpp \
    log.cpp \
    message.cpp \
    msgendpoint.cpp \
    msgenvhandler.cpp \
    msglayoutshandler.cpp \
    msgsystemhandler.cpp \
    msgtimerhandler.cpp \
    signalhandler.cpp \
    stopwatch.cpp \
    version.cpp

otherincludedir = \
    $(includedir)/moba

otherinclude_HEADERS = \
    atomic.h \
    helper.h \
    ipc.h \
    jsonabstractitem.h \
    jsondecoder.h \
    jsonmsgdecoder.h \
    jsonmsgencoder.h \
    jsonstreamreader.h \
    jsonstreamreadersocket.h \
    log.h \
    message.h \
    msgclienthandler.h \
    msgendpoint.h \
    msgenvhandler.h \
    msglayouthandler.h \
    msglayoutshandler.h \
    msgserverhandler.h \
    msgsystemhandler.h \
    msgtimerhandler.h \
    ringbuffer.h \
    signalhandler.h \
    stopwatch.h \
    version.h

ACLOCAL_AMFLAGS = \
    -I m4

CLEANFILES = \
    *~

