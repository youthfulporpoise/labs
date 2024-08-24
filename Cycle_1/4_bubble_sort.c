/*
 * BUBBLE SORT
 * A program to sort an array of integers using
 * the bubble sort alogrithm.
 */

#include <stdio.h>
#include <stdbool.h>

void bubble_sort (int*, size_t);
void swap (int*, int*);

int main() {
    size_t n;
    printf("Array length: ");
    scanf("%zu", &n);

    int array[n];
    printf("Enter %zu elements: ", n);
    for (size_t i = 0; i < n; i++)
        scanf("%d", array + i);

    bubble_sort(array, n);
    printf("\nResult: ");
    for (size_t i = 0; i < n; ++i) printf("%d ", array[i]);
    puts("");

    return 0;
}

void bubble_sort(int* array, size_t n) {
    size_t i, j;
    bool was_swapped;
    for (i = 0; i < n; ++i) {
        was_swapped = false;
        for (j = 0; j < n - i - 1; ++j) {
            if (array[j] > array[j + 1]) {
                swap(array + j, array + j + 1);
                was_swapped = true;
            }
        } 
        if (was_swapped) continue;
        else break;
    }
}

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
