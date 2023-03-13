#!/bin/bash/

if [ $# -lt 1] ; then
	echo "no arg given"
	exit 1
fi
echo -n "">file.txt
while [ $# -gt 0];do
	if file $1 | grep -E -q "C source";then
		grep -E "^#include" "$1"|awk '{print $2}' | sed 's/[<>]//g'>>file.txt
	fi
	shift 1
done
