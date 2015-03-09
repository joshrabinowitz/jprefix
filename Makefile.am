# see http://inti.sourceforge.net/tutorial/libinti/autotoolsproject.html
# and https://www.gnu.org/software/automake/manual/html_node/Use-TAP-with-the-Automake-test-harness.html#Use-TAP-with-the-Automake-test-harness
bin_PROGRAMS = jprefix

# see https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html for explanations of warnings
AM_CPPFLAGS = -Wall -Wextra

jprefix_SOURCES =  jprefix.cc jprefix.h  jpdateutils.cc jpdateutils.h

# this makes a test target for 'make check' (!)
TESTS = test-jprefix.pl
