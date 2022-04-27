#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])

AC_INIT([primtest], [1.0], [romain.villa@ens.uvsq.fr])
AC_MSG_NOTICE([Configuration du programme sur votre système.])

PRIMTEST_HOME="`pwd`"
AC_PREFIX_DEFAULT("`pwd`")

AC_CANONICAL_HOST

AC_CONFIG_SRCDIR([src/utils.h])
AC_CONFIG_HEADERS([src/config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB(gmp, __gmpz_init, ,
  [AC_MSG_ERROR([GNU MP not found, see https://gmplib.org/])])

CFLAGS="-c -Wall -g"
LDFLAGS="-lm -lgmp"
OBJS="main.o utils.o"
AC_SUBST(OBJS)
AC_DEFINE_UNQUOTED(OBJS,      "$OBJS")

# Checks for header files.
AC_CHECK_HEADERS([gmp.h])

# Checks for library functions.
AC_FUNC_MALLOC

AC_CONFIG_FILES([src/Makefile])
AC_OUTPUT

echo "
Configuration:
     compilateur:             ${CC} ${CFLAGS}
     hôte:                    $host
     'linker':                ${LDFLAGS}
     librairies:              ${LIBS}
"