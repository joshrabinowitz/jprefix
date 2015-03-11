#!/bin/bash

# .cleanup.sh.swp  .gitignore  Makefile.am  aclocal.m4     cleanup.sh*  configure*    src/
# .git/        LICENSE     README.md    autom4te.cache/  config.log   configure.ac

# COPYING@        aclocal.m4      configure.ac
#INSTALL@        autogen.sh*     depcomp@
#LICENSE         cleanup.sh*     install-sh@
#Makefile.am     compile@        missing@
#README.md       config.status*      src/

rm -f aclocal.m4 configure config.log config.status
rm -rf autom4te.cache src/.deps
rm -f depcomp install-sh compile missing
rm -f Makefile Makefile.in  src/Makefile src/Makefile.in
rm -f src/*.o src/.dirstamp
rm -f test/test-jprefix.pl.*  test-suite.log  test-driver


