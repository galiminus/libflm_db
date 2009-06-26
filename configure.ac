#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.26)
AC_INIT(libflm_db, 0.4, victor@phorque.net)
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CC
AM_PROG_AS
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB
AC_PROG_LIBTOOL

AM_PROG_CC_C_O

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([	arpa/inet.h		\
			fcntl.h			\
			limits.h		\
			netdb.h			\
			netinet/in.h		\
			stddef.h		\
			stdlib.h		\
			string.h		\
			strings.h		\
			sys/file.h		\
			sys/param.h		\
			sys/socket.h		\
			sys/time.h		\
			syslog.h		\
			unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_MODE_T
AC_TYPE_OFF_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_FORK
AC_FUNC_LSTAT_FOLLOWS_SLASHED_SYMLINK
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_TYPE_SIGNAL
AC_CHECK_FUNCS([alarm getcwd gethostbyname gettimeofday inet_ntoa memmove memset select socket strcasecmp strchr strdup strerror strncasecmp strrchr strstr])

AC_CONFIG_FILES([Makefile
                 src/Makefile
		 src/pgsql/Makefile])

AC_OUTPUT
