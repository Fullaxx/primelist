#!/bin/bash

set -e

OPT="-O2"
DBG="-ggdb3 -DDEBUG"
CFLAGS="-Wall"
CFLAGS+=" -std=c99"
OPTCFLAGS="${CFLAGS} ${OPT}"
DBGCFLAGS="${CFLAGS} ${DBG}"

rm -f *.exe *.dbg

gcc ${OPTCFLAGS} simple.c -lgmp -o simple.exe
gcc ${DBGCFLAGS} simple.c -lgmp -o simple.dbg

gcc ${OPTCFLAGS} threaded.c -lgmp -o threaded.exe
gcc ${DBGCFLAGS} threaded.c -lgmp -o threaded.dbg

strip *.exe
