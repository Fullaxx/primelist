#!/bin/bash

set -e

OPT="-O2"
DBG="-ggdb3 -DDEBUG"
CFLAGS="-Wall -ansi"
OPTCFLAGS="${CFLAGS} ${OPT}"
DBGCFLAGS="${CFLAGS} ${DBG}"

rm -f *.exe *.dbg

gcc ${OPTCFLAGS} simple.c -lgmp -o simple.exe
gcc ${DBGCFLAGS} simple.c -lgmp -o simple.dbg

strip *.exe
