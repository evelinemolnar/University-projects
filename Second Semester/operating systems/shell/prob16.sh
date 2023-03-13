#!/bin/bash
dir=${1:-"."}
if [ -d "$dir" ]; then
    for f in $(find "$dir" -type f); do
	ls -l 	chmod 222 ???

