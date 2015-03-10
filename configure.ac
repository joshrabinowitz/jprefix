# see http://inti.sourceforge.net/tutorial/libinti/autotoolsproject.html
# and http://linux.blogs.com.np/2008/04/18/using-automake-and-autoconf-with-c/comment-page-1/
# and http://www.bioinf.uni-freiburg.de/~mmann/HowTo/automake.html

# set variables
PACKAGE=jprefix

# initial info about project
AC_INIT([jprefix],[0.66],[joshr])
#AC_CONFIG_SRCDIR([src/jprefix.cc],[src/jprefix.h])

# check for C++ preprocessor and compiler
AC_PROG_CXX
AC_PROG_CXXCPP

#  'foreign' below means "software does not conform to the typical gnu standards, 
#                         and thus omitting README (and NEWS AUTHORS and ChangeLog) 
#                         is not an error"
AM_INIT_AUTOMAKE([foreign])

# use the C++ compiler for following checks
AC_LANG([C++])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([getopt.h])
AC_CHECK_HEADERS([stdio.h])
AC_CHECK_HEADERS([stdlin.h])
AC_CHECK_HEADERS([time.h])
AC_CHECK_HEADERS([sys/time.h])
AC_CHECK_HEADERS([fstream])
AC_CHECK_HEADERS([iostream])
AC_CHECK_HEADERS([iomanip])
AC_CHECK_HEADERS([sstream])
AC_CHECK_HEADERS([string])
AC_CHECK_HEADERS([vector])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# distribute additional compiler and linker flags among Makefiles
# --> set and change these variables instead of CXXFLAGS or LDFLAGS (for user only)
AC_SUBST([AM_CXXFLAGS])
AC_SUBST([AM_LDFLAGS])

# finally this generates the Makefiles etc. for the build
AC_OUTPUT(Makefile src/Makefile)

