#! /bin/bash

# Check argument count correctness.
if [[ "$#" -ne 1 ]]; then
  echo "Usage: $0 <directory>"
  exit 0
fi

# Check the argument is a valid directory.
if ! [[ -d "$1" ]]; then
  echo "$1: not a directory"
  exit 1
fi

# Compress.
zip -Z deflate -r "$1.zip" "$1"
echo "[ok] archived: $1 -> $1.zip"
exit 0
