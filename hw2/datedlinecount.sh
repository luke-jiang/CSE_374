#!/bin/bash

# Luke Jiang
# CSE 374 HW 2 Problem 4
# April 10 2018

# Error handling for not enough argument
if [ $# -lt 2 ]; then
  echo "Error: less than two arguments"
  exit 1
fi

# Append date and line counts of each file to the first argument
log="$1"
shift
date >> "$log"
wc -l $@ >> "$log"

# Output a total line for single file case
if [ $# -eq 1 ]; then
  count=$(wc -l $@)
  arr=($count)
  total=${arr[0]}
  echo $total" total" >> "$log"
fi

# Remove extra space before each line of output
sed 's/^[ \t]*//' -i "$log"
exit 0
