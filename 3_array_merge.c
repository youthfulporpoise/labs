#include <stdio.h>

int main()
{
	size_t n;
	printf("First array size: ");
	scanf("%zu", &n);
	int a1[n];
	printf("Enter %zu elements: ", n);
	for (size_t i = 0; i < n; ++i) scanf("%d", a1 + i);

	size_t m;
	printf("Second array size: ");
	scanf ("%zu", &m);
	int a2[m];
	printf("Enter %zu elements: ", m);
	for (size_t i = 0; i < m; ++i) scanf("%d", a2 + i);

	int a0[n + m];
	for (size_t i = 0; i < n; ++i) a0[i] = a1[i];
	for (size_t i = 0; i < m; ++i) a0[n + i] = a2[i];

	printf("Result: ");
	for (size_t i = 0; i < n + m; ++i) printf("%d ", a0[i]);
	puts("");
	return 0;
}
