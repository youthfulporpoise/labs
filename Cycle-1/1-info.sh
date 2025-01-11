#! /bin/bash

# Print real name and login name.
printf 'Name:         %s (logged in as: %s)\n' "$(id -F)" "$(whoami)"

# Print current shell.
printf 'Shell:        %s\n' "$(echo "$SHELL" | grep -oE '[a-z]*$')"

# Print home directory.
printf 'Home:         %s\n' "$HOME"

# Print operating system type.
printf 'OS type:      %s\n' "$(uname)"

# Print current path.
printf 'Current path: %s\n' "$PWD"

# Print current logins.
echo -e '\nCurrently logged in:'
who

# Print current $PATH setting.
printf '\nPath: %s\n' "$PATH"
