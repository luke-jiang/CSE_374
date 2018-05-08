#!/bin/bash

# Luke Jiang
# CSE 374 HW 3 Problem 3
# April 14 2018

i=0
for url in $(cat "$2"); do
  i=$((i+1))
  echo "Performing byte-size measurement on $url..."
  pageSize=$(./perform-measurement.sh "$url")
  if [ "$pageSize" != 0 ]
  then
    echo "...successful"
    echo "$i $url $pageSize" >> "$1"
  else
    echo "...failure"
  fi
done

exit 0
