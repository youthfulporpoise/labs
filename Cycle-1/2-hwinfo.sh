#! /bin/bash

# Check which operating system is run.
# Currently supported platforms:
#   • Linux
#   • macOS
OS="$(uname -s)"

case $OS in
  Darwin|Linux)
    ;;
  *)
    echo "not supported: $OS"
    exit 1
    ;;
esac

echo
# Print OS version, release number, and kernel version.
case $OS in
  Darwin)
    system_profiler SPSoftwareDataType
    echo "Release number: $(uname -r)"
    ;;
  Linux)
    echo "OS: $(uname -n) ($(uname -s))"
    echo "Release number: $(uname -r)"
    echo "Kernel version $(uname -v)"
    ;;
esac

echo
# Print all available shells.
SHELLS="$(cat /etc/shells | egrep '^[^#\n]')"
echo 'Available shells:'
for shell in $SHELLS; do
  echo -e "    • $shell"
done

echo
# Print CPU and memory information.
case $OS in
  Darwin)
    system_profiler SPHardwareDataType
    ;;
  Linux)
    lscpu
    echo
    lsmem
    ;;
esac

echo
# Print hard disk and filesystem information.
case $OS in
  Darwin)
    diskutil list
    ;;
  Linux)
    lsblk
    echo
    df -hPT
    ;;
esac
