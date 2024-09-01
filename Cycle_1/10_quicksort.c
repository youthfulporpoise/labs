/* 
 * TOM HOARE's quicksort algorithm
 * with Hoare's partition scheme
 */
#include <stdio.h>
#include <stdbool.h>

int main ();
void quicksort (int*, size_t);
void read_array (char*, int*, size_t);
void print_array (char*, int*, size_t);

int __tmp__;
#define SWAP(a, b) { __tmp__ = (a);  (a) = (b); (b) = __tmp__; }

int main()
{
    size_t n;
    printf("Size: "); scanf("%zu", &n);
    int a[n];
    read_array("Array: ", a, n);
    quicksort(a, n);
    print_array("Result: ", a, n);

    return 0;
}

void quicksort(int *a, size_t n)
{
    if (n <= 1) return;

    int pivot = a[n / 2];
    size_t q = 0, r = n - 1;
    while (q <= r) {
        while (a[q] < pivot) q++;
        while (a[r] > pivot) r--;
        if (q >= r) break;
        else {
            SWAP(a[q], a[r]);
            q++; r--;
        }
    }

    quicksort(a, q);
    quicksort(a + q, n - q);
}

void read_array(char* msg, int* a, size_t n)
{
    printf("%s", msg);
    for (size_t i = 0; i < n; ++i) scanf("%d", a + i);
}

void print_array(char* msg, int* a, size_t n)
{
    printf("%s", msg);
    for (size_t i = 0; i < n; ++i) printf("%d ", a[i]);
    puts("");
}
