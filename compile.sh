#!/bin/bash

set -e

OPT="-O2"
DBG="-ggdb3 -DDEBUG"
CFLAGS="-Wall"
CFLAGS+=" -std=c99"
OPTCFLAGS="${CFLAGS} ${OPT}"
DBGCFLAGS="${CFLAGS} ${DBG}"

rm -f *.exe *.dbg

gcc ${OPTCFLAGS} simple_list.c -lgmp -o simple_list.exe
gcc ${DBGCFLAGS} simple_list.c -lgmp -o simple_list.dbg

gcc ${OPTCFLAGS} threaded_list.c -lgmp -o threaded_list.exe
gcc ${DBGCFLAGS} threaded_list.c -lgmp -o threaded_list.dbg

strip *.exe
