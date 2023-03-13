#!/bin/bash
if [ -z "$1" ]; then
    echo "No parameters given"
    exit 1
fi
while [ ! $# -eq 0 ]; do
	arg=$1
	if file $arg | grep -E -q ".c"; then
		grep -E "^#include" "$1"|awk '{print $2}' | sed 's/[<>]//g'
	fi
	shift 1
done
