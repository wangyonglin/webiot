#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(wangyonglin,1.0,admin@wangyonglin.com)
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/application/application.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
LD_LIBRARY_PATH
LT_INIT
# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h fcntl.h float.h limits.h netdb.h netinet/in.h stddef.h stdint.h stdlib.h string.h sys/ioctl.h sys/socket.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT64_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_FORK
AC_FUNC_MALLOC
AC_FUNC_STRNLEN
AC_FUNC_STRTOD
AC_CHECK_FUNCS([bzero dup2 floor gettimeofday memset pow socket strchr strerror strspn strstr strtol])
AC_CONFIG_FILES([Makefile
                src/application/Makefile
                src/wangyonglin/Makefile
                src/mosquitto/Makefile
                src/https/Makefile])
AC_OUTPUT
