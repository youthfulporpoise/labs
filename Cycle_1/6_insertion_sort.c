#include <stdio.h>

int main ();
void insertion_sort (int*, size_t);
void shift_insert (int*, size_t);
void read_array (char*, int*, size_t);
void print_array (char*, int*, size_t);

int main()
{
    size_t n;
    printf("Size: "); scanf("%zu", &n);
    int a[n];
    read_array("Array: ", a, n);
    insertion_sort(a, n);
    print_array("Result: ", a, n);
}

void insertion_sort(int* a, size_t n)
{
    for (size_t i = 1; i < n; ++i) {
        size_t j = i;
        char x = a[i];
        while (j > 0 && x < a[j - 1]) {
            a[j] = a[j - 1];
            --j;
        } a[j] = x;
    }
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
