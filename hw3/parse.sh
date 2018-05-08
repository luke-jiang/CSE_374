#!/bin/bash

# Luke Jiang
# CSE 374 HW 3 Problem 2
# April 14 2018

if [ $# -lt 2 ]; then
  echo "Error: less than two arguments"
  exit 1
elif [ ! -e "$1" ]; then
  echo "Error: input html file does not exist"
  exit 1
fi

grep 'http://' "$2" | sed 's/.*\(http:\/\/\([A-Za-z0-9]\|\.\|\/\|-\|%\)\+\).*/\1/g' | sed -e '1,5d; 7d; 9d' | sed -e "101,111d" > "$1"

exit 0
