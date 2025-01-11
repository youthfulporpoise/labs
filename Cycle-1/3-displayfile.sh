#! /bin/bash

# We check whether one and only one filename is supplied to our script.
if [[ "$#" -ne 1 ]]; then
  echo "Usage: $0 <filename>"
  exit 0
fi

# We have check whether the script is executed as an executable or provided as
# an argument to `bash`.
file="$1"

# We check whether the file exists and whether it is a text file.
if ! [[ -f "$file" ]]; then
  echo "$file: does not exist or is not a regular file"
  exit 1
else
  cat "$file"
fi
