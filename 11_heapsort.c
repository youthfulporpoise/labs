#include <stdio.h>

int main ();
void heapsort (int*, size_t);
void sift (int*, size_t);
void rectify_heap (int*, size_t, size_t);
void swap (int*, int*);
void read_array (char*, int*, size_t);
void print_array (char*, int*, size_t);


int main()
{
    size_t n;
    printf("Size: "); scanf("%zu", &n);
    int a[n];
    read_array("Array: ", a, n);
    heapsort(a, n);
    print_array("Result: ", a, n);

    return 0;
}

void heapsort(int *a, size_t n)
{
    /* Build the max heap. */
    size_t p = 0; 
    while (p < n) sift(a, p++);
    p--;
    /* Swap and rectify. */
    while (p > 0) {
        swap(a, a + p);
        p--;
        rectify_heap(a, 0, p);
    }
}

void sift(int *a, size_t i)
{  /* Sift the largest to the top. */
    if (i < 1) return;
    if (a[i] > a[i / 2]) {
        swap(a + i, a + i / 2);
        sift(a, i / 2);
    } else return;
}

void rectify_heap(int *a, size_t i, size_t t)
{   /* Rectify a violated heap structure. */
    size_t lc = 2 * i,
           rc = 2 * i + 1,
           max = i;
    if (lc <= t && a[lc] > a[max]) max = lc;
    if (rc <= t && a[rc] > a[max]) max = rc;
    if (max == i) return;
    else {
        swap(a + i, a + max);
        rectify_heap(a, max, t);
    }
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
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
