# see http://inti.sourceforge.net/tutorial/libinti/autotoolsproject.html
# and http://linux.blogs.com.np/2008/04/18/using-automake-and-autoconf-with-c/comment-page-1/

AC_INIT(src/jprefix.cc)


PACKAGE=jprefix
VERSION=0.1.0

AM_INIT_AUTOMAKE($PACKAGE, $VERSION)

JPREFIX_REQUIRED_VERSION=1.0.7
#PKG_CHECK_MODULES(INTI, inti-1.0 >= $INTI_REQUIRED_VERSION)
#AC_SUBST(INTI_CFLAGS)
#AC_SUBST(INTI_LIBS)

AC_PROG_CC
AC_PROG_CXX

AC_PROG_INSTALL

AC_OUTPUT(Makefile src/Makefile)
