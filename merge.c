#include <stdio.h>
#include "common.h"

int main()
{
    size_t n = read_size("First array size: ");
    int a0[n];
    read_array(a0, n);
    size_t m = read_size("Second array size: ");
    int a1[m];
    read_array(a1, m);

    int a[n + m];
    size_t i, j;
    for (i = 0; i < n; ++i) a[i] = a0[i];
    for (j = 0; j < m; ++j) a[j + i] = a1[j];
    print_array("Result: ", a, n + m);

    return 0;
}
