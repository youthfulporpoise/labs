#include <stdio.h>
#include "common.h"

int main ();
size_t search (int, int*, size_t);

int main()
{
    size_t n = read_size("Number of elements: ");
    int array[n];
    read_array(array, n);
    
    unsigned choice;
    printf("\nDelete by:\n"
           "\t(1) value\n"
           "\t(2) index\n"
           "Choice: ");
    scanf("%u", &choice);

    switch (choice) {
        case (1):
            int value;
            printf("\nValue to delete: ");
            scanf("%d", &value);
            size_t index = search(value, array, n);

            if (index < n) {
                for (size_t i = index; i < n - 1; ++i)
                    array[i] = array[i + 1];
            } else {
                printf("%d: value does not exist\n", value);
                return 1;
            } break;

        case (2):
            size_t index;
            printf("\nIndex: ");
            scanf("%zu", &index);

            if (0 < index && index < n) {
                for (size_t i = index; i < n - 1; ++i)
                    array[i] = array[i + 1];
            } else {
                printf("%zu: index does not exist\n", index);
                return 1;
            } break;
    }

    n--;
    print_array("Result: ", array, n);
    return 0;
}

/* Perform linear search of a value in
 * an n-element array. */
size_t search(int value, int *array, size_t n)
{
    size_t i;
    for (i = 0; i < n; ++i)
        if (array[i] == value) return i;
    return i;
}
