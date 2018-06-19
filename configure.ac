## configure.ac

AC_PREREQ([2.69])
AC_INIT([backref], [1.1.0], [klmanion@gmail.com])

AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([-Wall -Werror foreign])

AC_LANG_C
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_CC_C99
AC_PROG_INSTALL
AC_C_CONST
AC_C_INLINE
AC_HEADER_STDC
PKG_PROG_PKG_CONFIG

AC_FUNC_MALLOC

AM_CONDITIONAL([IS_GCC], [test x"$GCC" = x"yes"])

AC_ARG_ENABLE([debug],
	AC_HELP_STRING([--enable-debug], [enable debug macros and assertions]),
	[enable_debug="$enableval"],
	[enable_debug="no"])
AM_CONDITIONAL([IS_DEBUG], [test x"$enable_debug" = x"yes"])

AC_CONFIG_FILES([
 Makefile
 src/Makefile
 share/man/man1/Makefile
])

AC_SUBST([AM_CFLAGS])
AC_SUBST([AM_CPPFLAGS])

AC_OUTPUT

