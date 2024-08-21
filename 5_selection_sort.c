#include <stdio.h>

int main ();
void ssort (int*, size_t);
void swap (int*, int*);
void read_array (char*, int*, size_t);
void print_array (char*, int*, size_t);

int main()
{
    size_t n;
    printf("Size: "); scanf("%zu", &n);
    int a[n];
    read_array("Array: ", a, n);
    ssort(a, n);
    print_array("Result: ", a, n);

}

void ssort(int* a, size_t n)
{
    size_t min;
    for (size_t i = 0; i < n - 1; ++i) {
        min = i;
        for (size_t j = i + 1; j < n; ++j)
            if (a[j] < a[min]) min = j;
        swap(a + i, a + min);
    }
}

void swap(int* a, int* b)
{
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
