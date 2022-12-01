#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([moba-common], [0.2.0-0000], [pappi-@gmx.de])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_SRCDIR([src])
AC_CONFIG_HEADERS([config.h])
LT_INIT

# Checks for programs.
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([
    arpa/inet.h
    fcntl.h
    netdb.h
    netinet/in.h
    sys/socket.h
    sys/time.h
    sys/timeb.h
    unistd.h
])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([ftime gethostbyname memset mkfifo select socket strerror strtol])

PKG_CHECK_MODULES([GLIB], [glib-2.0 >= 2.24.1])

AX_CXX_COMPILE_STDCXX_17()

AC_CONFIG_FILES([
    Makefile
    src/Makefile
])

AC_OUTPUT
