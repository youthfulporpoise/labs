#include <stdio.h>

size_t linear_search(int* a, size_t n, int key)
{
    for (size_t i = 0; i < n; ++i) {
        if (key == a[i]) return i;
    } return n;
}

int main()
{
    size_t n;
    printf("Size: "); scanf("%zu", &n);
    int a[n];
    printf("Array: ");
    for (size_t i = 0; i < n; ++i) scanf("%d", a + i);
    int key;
    printf("Key: "); scanf("%d", &key);

    size_t z = linear_search(a, n, key);
    if (z == n) printf("Not found.\n");
    else printf("Found at %zu\n", z);
    
    return 0;
}
