#!/bin/bash

# Luke Jiang
# CSE 374 HW 2 Problem 3
# April 10 2018

if [ $# -lt 2 ]; then
  echo "Error: less than two arguments" >&2
  exit 1
fi

if [ -e "$1" ]
then
  echo "Error: first file exists" >&2
  exit 1
else
  errorMsg="$1"
  shift
  cat $@ 2> "$errorMsg"
  exit 0
fi
