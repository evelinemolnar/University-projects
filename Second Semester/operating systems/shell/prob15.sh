#!/bin/bash
if [ -z "$1" ]; then
    echo "No parameters given"
    exit 1
fi
if [ ! -d "$1" ]; then
    echo "Parameter is not a folder"
    exit 1
fi
for f in $(ls "$1" | grep -E "\.c$"); do
  if test -f "$1/$f"; then
     rm "$1/$f"
  fi
done
for f in $(ls "$1" | grep -E "\.txt$"); do
   echo "$f" 
done| sort -n
