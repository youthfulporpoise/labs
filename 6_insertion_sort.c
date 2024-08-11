#include <stdio.h>

int main ();
void inssort (int*, size_t);
void shift_insert (int*, size_t);
void read_array (char*, int*, size_t);
void print_array (char*, int*, size_t);

int main()
{
    size_t n;
    printf("Size: "); scanf("%zu", &n);
    int a[n];
    read_array("Array: ", a, n);
    inssort(a, n);
    print_array("Result: ", a, n);
}

void inssort(int* a, size_t n)
{
    for (size_t i = 1; i < n; ++i) {
        for (size_t j = 0; j < i; ++j) {
            if (a[i] < a[j]) {
                shift_insert(a + j, i - j + 1);
                break;
            }
        }
    }
}

void shift_insert(int* a, size_t n)
{
    int v = a[n - 1];
    for (size_t i = n - 1; i > 0; --i)
        a[i] = a[i - 1];
    a[0] = v;
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
