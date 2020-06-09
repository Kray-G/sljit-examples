#!/bin/bash

function mkudis86() {
	cd ../udis86
	pwd
	if [ ! -f configure ]; then
		sh ./autogen.sh
	fi
	./configure
	make
	cd ../examples
	cp -f ../udis86/libudis86/.libs/libudis86.so.0.0.0 ./
	ln -s libudis86.so.0.0.0 libudis86.so
	ln -s libudis86.so.0.0.0 libudis86.so.0
}

function error() {
	echo Usage: ./build.sh [source file]
	exit 1
}

if [ "$1" == "" ]; then error; fi
if [ ! -f libudis86.so ]; then mkudis86; fi
if [ ! -f libudis86.so ]; then error; fi

OUT=`basename $1 .c`
gcc -o $OUT.exe -I ../sljit -DSLJIT_CONFIG_AUTO=1 $1 ../sljit/sljitLir.c -Wl,-rpath,'$ORIGIN' -L. -ludis86

exit 0

