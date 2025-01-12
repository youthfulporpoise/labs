#! /bin/bash

# A recursive function to list files.
function list {
  echo "$3$2"
  if [[ -d "$1/$2" ]]; then
    for p in `ls -1 "$1/$2"`; do
      list "$1/$2" "$p" "$3: "
    done
  fi
}

if [[ "$#" -lt 1 ]]; then
  echo "Usage: $0 <path> <path> ..."
  exit 0
fi

for p in "$@"; do
  list "." "$p" ""
done
