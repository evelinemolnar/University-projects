#!/bin/bash
fname=""
while [ ! -f "$fname" ]; do
  read -p "Enter a string: " fname
done
