#!/bin/bash

# info: generates compiled program from nasm file
# args:
#	(0): script name
#	(1): source file
#	(2): destiny file

src_file=$1
dst_file=$2

if [ $# -eq 2 ]; then
	nasm -g -o gen.o -f elf32 $src_file
	gcc -m32 -o $dst_file gen.o lib/alfalib.o
	rm -f gen.o
else
	printf 'Bad args: %s SRC DST\n' "$0"
fi
