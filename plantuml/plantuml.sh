#! /bin/zsh

if [[ "$#" -ne 1 ]]; then
    printf "Usage: $0 <file name>.uml\n"
    exit 0
fi

filename="$(echo $1 | awk '{ split($0, a, "."); print a[1]; }')"

java -jar plantuml-mit-1.2024.7.jar -tsvg "$filename.uml"
if [[ "$?" -ne 0 ]]; then
    printf "error: diagram compilation did not exit successfully\n"
    exit "$?"
fi

svg2pdf "$filename.svg" "$filename.pdf"
if [[ "$?" -ne 0 ]]; then
    printf "error: svg to pdf conversion did not execute successfully\n"
    exit "$?"
fi

rm $filename.svg
printf "Output: %s\n" "$filename.pdf"

exit 0
