#! /bin/bash

# This is our iterative Fibonacci function.
function fibonacci {
    n=0
    m=1
    while [[ "$n" -lt "$1" ]]; do
      echo -n "$n "
      tmp="$m"
      m=`expr $n + $m`
      n="$tmp"
    done
    echo
}

# Check for argument count.
if [[ "$#" -ne 1 ]]; then
  echo "Usage: $0 <upper limit>"
  exit 0
fi

fibonacci "$1"
exit 0
