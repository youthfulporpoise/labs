#include <stdio.h>

/* Read an array size with a prompt which
 * may be empty. */
size_t read_size(char *msg)
{
    size_t x;
    printf("%s", msg);
    scanf("%zu", &x);
    return x;
}


/* Read an array up to n elements. */
void read_array(int *array, size_t n)
{
    printf("Enter %zu elements: ", n);
    for (size_t i = 0; i < n; ++i)
        scanf("%i", &array[i]);
}


/* Print an array up to n elements with a prompt
 * which may be empty. */
void print_array(char *msg, int *array, size_t n)
{
    size_t i = 0;
    printf("%s[%d,", msg, array[i++]);
    for (; i < n - 1; ++i)
        printf(" %d,", array[i]);
    printf(" %d]", array[i]);
    puts("");
}
