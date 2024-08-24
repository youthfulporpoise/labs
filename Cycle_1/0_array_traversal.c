#include <stdio.h>

int main()
{
	size_t n;
	printf("Array size: ");
	scanf("%zu", &n);

	int a[n];
	printf("Enter %zu elements: ", n);
	for (size_t i = 0; i < n; ++i) scanf("%d", a + i);
	printf("Array: ");
	for (size_t i = 0; i < n; ++i) printf("%d", a[i]);
	puts("");

	return 0;
}
