#!/bin/bash

if [$# -lt 1]; then 
	echo "no args"
	exit 1
fi
if [ -d $1]; then
	
	init_cap = $(du -b $1 | awk 'END{print $1}')

	while true; do
		cap=$(du -b $1 | awk 'END{print $1}')
		sleep 3
		if [! $init_cap -eq $cap];then
			echo "S-a produs o modificare"
			init_cap=$cap
		fi
	done
fi

