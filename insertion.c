#include <stdio.h>
#include <stdbool.h>
#include "common.h"

int main() {
    size_t n = read_size("Number of elements: ");
    int array[n + 1];
    read_array(array, n);

    int x;
    size_t index;
    while (true) { /* Check for a valid insertion index. */
        printf("Insertion (element) (index): ");
        scanf("%d %zu", &x, &index);
        if (0 < index && index <= n) break;
        else {
            puts("\n(!) The index is invalid; try again.");
            continue;
        }
    }
    
    size_t i;
    for (i = n; i > index; --i)
        array[i] = array[i - 1];
    array[i] = x;

    print_array("\nResult: ", array, n + 1);
    return 0;
}
