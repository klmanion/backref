## configure.ac

AC_PREREQ([2.69])
AC_INIT([backref], [0.1.1], [klmanion@gmail.com])

AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([-Wall -Werror foreign])

AC_PROG_CC
AC_LANG_C

AC_FUNC_MALLOC

AC_ARG_ENABLE([debug],
			  AS_HELP_STRING([--enable-debug], [Enable debug mode]),
			  [AC_DEFINE([DEBUG], [], [desc])])

AC_CONFIG_FILES([
 Makefile
 src/Makefile
 share/man/man1/Makefile
])

AC_OUTPUT

