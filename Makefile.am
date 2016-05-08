# see http://inti.sourceforge.net/tutorial/libinti/autotoolsproject.html
# and https://www.gnu.org/software/automake/manual/html_node/Use-TAP-with-the-Automake-test-harness.html#Use-TAP-with-the-Automake-test-harness
bin_PROGRAMS = jprefix

# see https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html for explanations of warnings
AM_CPPFLAGS = -Wall -Wextra
AUTOMAKE_OPTIONS = subdir-objects

jprefix_SOURCES =  src/jprefix.cc src/jprefix.h  src/jpdateutils.cc src/jpdateutils.h  \
				   src/jpopts.cc src/jpopts.h  src/jposutils.h src/jposutils.cc src/jpstrutils.cc src/jpstrutils.h

TESTS = test/test-jprefix.pl

