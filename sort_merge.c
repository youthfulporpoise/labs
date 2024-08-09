/* 
 *  JOHN VON NEUMANN’S MERGESORT
 *  implemented recursively
 *  with logical splits
 */
#include <stdio.h>

int main ();
void merge_sort (int*, size_t, int*, size_t);
void merge (int*, size_t, int*, size_t);
void print_array (char*, int*, size_t);
void read_array (char*, int*, size_t);

int main()
{
    size_t n;
    printf("Size: "); scanf("%zu", &n);
    int a[n];
    read_array("Array: ", a, n);
    merge_sort(a, n / 2, a + n / 2, n - n / 2);
    print_array("Result: ", a, n);
    return 0;
}

void merge_sort(int* a, size_t n, int* b, size_t m)
{
    if (n > 1) merge_sort(a, n / 2, a + n / 2, n - n / 2);
    if (m > 1) merge_sort(b, m / 2, b + m / 2, m - m / 2);
    merge(a, n, b, m);
}

void merge(int* a, size_t n, int* b, size_t m)
{
    int tmp[n + m];
    size_t k = 0, i = 0, j = 0;
    while (i < n && j < m) {
        if (a[i] <= b[j]) tmp[k++] = a[i++];
        else tmp[k++] = b[j++];
    }
    while (i < n) tmp[k++] = a[i++];
    while (j < m) tmp[k++] = b[j++];
    for (i = 0; i < n + m; ++i) a[i] = tmp[i];
}

void print_array(char* msg, int* a, size_t n)
{
    printf("%s", msg);
    for (size_t i = 0; i < n; ++i) printf("%d ", a[i]);
    puts("");
}

void read_array(char* msg, int* a, size_t n)
{
    printf("%s", msg);
    for (size_t i = 0; i < n; ++i) scanf("%d", a + i);
}
