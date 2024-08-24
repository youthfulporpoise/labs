/* 
 * TOM HOARE's quicksort algorithm
 * with Hoare's partition scheme
 */
#include <stdio.h>

int main ();
void quicksort (int*, size_t);
void swap (int*, int*, int*);
void read_array (char*, int*, size_t);
void print_array (char*, int*, size_t);

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

    size_t p = 0, q = 1, r = n - 1;
    while (q <= r) {
        if (a[r] < a[p]) {
            swap(a + p, a + q, a + r);
            p++; q++;
            if (a[r] > a[p]) r--;
        } else r--;
    }

    quicksort(a, p);
    quicksort(a + p + 1, n - p - 1);
}

void swap(int *a, int *b, int *c)
{
    int tmp = *c;
    *c = *b;
    *b = *a;
    *a = tmp;
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
