#! /bin/bash

# First, check whether we have two arguments (two numbers) and only two.
# To do that, we have to know whether the script was an argument to `bash` or
# not.
if [[ "$#" -ne 2 ]]; then
  echo "Usage: $0 <number> <number>"
  exit 0
else
  n="$1"
  m="$2"
fi

# Now we do arithmetic.
echo "Sum: $(expr $n + $m)"
echo "Difference: $(expr $n - $m)"
echo "Product: $(expr $n \* $m)"
echo "Quotient: $(expr $n / $m)"

exit 0
