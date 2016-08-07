#!/bin/bash
libtoolize --force
aclocal
autoheader
automake --force-missing --add-missing
autoconf
./configure
#make -i
#make -i
#make -i check
#make -i check
#make -i check
