#include <stdio.h>
#include "common.h"

int main()
{
    size_t n = read_size("Number of elements: ");
    int array[n];
    read_array(array, n);
    print_array("Array: ", array, n);

    return 0;
}
