#!/bin/bash

# Luke Jiang
# CSE 374 HW 3 Problem 1
# April 14 2018

if [ $# == 0 ]; then
  echo "Error: no arguments passed, need one argumnent"
  exit 1
fi

count=0
tempfile=$(mktemp)
wget --timeout=30  --tries=3 -O "$tempfile" "$1" > /dev/null 2>&1
count=$(wc -c < "$tempfile")

echo "$count"
rm "$tempfile"
exit 0
