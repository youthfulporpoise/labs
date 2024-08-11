#include <stdio.h>

int main ();
size_t binsrch (int*, size_t, int);
void read_array (char*, int*, size_t);
void print_array (char*, int*, size_t);


int main()
{
    size_t n;
    printf("Size: "); scanf("%zu", &n);

    int a[n];
    read_array("Array: ", a, n);

    int key;
    printf("Key: "); scanf("%d", &key);

    size_t z = binsrch(a, n, key);
    if (z >= n) printf("%d does not exist.\n", key);
    else printf("%d found at index %zu.\n", key, z);

    return 0;
}

size_t binsrch(int* a, size_t n, int key)
{
    if (n == 0) return 0;

    size_t m = (n - 1) / 2;
    if (a[m] > key) { 
        size_t z = binsrch(a, m, key);
        if (z > m) return n;
        else return (z);
    } else if (a[m] < key)  {
        size_t z = binsrch(a + m + 1, n - m, key);
        if (z > m) return n;
        else return (m + z + 1);
    } else return m;
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
