#include <stdio.h>

int main()
{
	size_t n;
	printf("Array size: ");
	scanf("%zu", &n);

	int array[n + 1];
	printf("Enter %zu elements: ", n);
	for (size_t i = 0; i < n; ++i)
		scanf("%d", array + i);

	size_t m, i;
	int x;
	printf("Insert (element) (index): ");
	scanf("%d %zu", &x, &m);

	/* Insertion procedure */
	for (i = n; i > m; --i)
		array[i] = array[i - 1];
	array[i] = x;

	printf("Result: ");
	for (i = 0; i <= n; ++i)
		printf("%d ", array[i]);
	puts("");
	return 0;
}
