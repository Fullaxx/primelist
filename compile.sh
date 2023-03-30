#!/bin/bash

set -e

OPT="-O2"
DBG="-ggdb3 -DDEBUG"
CFLAGS="-Wall -ansi"
OPTCFLAGS="${CFLAGS} ${OPT}"
DBGCFLAGS="${CFLAGS} ${DBG}"

rm -f *.exe *.dbg

gcc ${OPTCFLAGS} main.c -lgmp -o primelist.exe
gcc ${DBGCFLAGS} main.c -lgmp -o primelist.dbg

strip *.exe
