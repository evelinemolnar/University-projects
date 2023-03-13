#!/bin/bash
if [ $# -lt 1 ]; then
    echo "Insufficient arguments"
    exit 1
fi
if [ ! -d "$1" ]; then
    echo "Parameter is not a folder"
    exit 1
fi
total=0
for f in $(ls "$1" | grep -E "\.c$"); do
  if test -f "$1/$f"; then
    nr_lines=$(grep -E -c -v "^[ \t]*$" "$1/$f")
    echo "$f: $nr_lines"
    total=$((total+nr_lines))
  fi
done
echo "Total lines: $total"
