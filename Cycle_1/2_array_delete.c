#include <stdio.h>

int main ();
size_t search (int, int*, size_t);

int main()
{
	size_t n;
	printf("Array size: ");
	scanf("%zu", &n);

	int array[n];
	printf("Enter %zu elements: ", n);
	for (size_t i = 0; i < n; ++i)
		scanf("%d", array + i);

	unsigned choice;
	printf("Delete by (1) value or (2) index: ");
	scanf("%u", &choice);

	size_t index;
	switch (choice) {
		case (1):
			int value;
			printf("Enter value: ");
			scanf("%d", &value);
			index = search(value, array, n);
			if (index < n) break;
			else {
				puts("value: invalid");
				return 1;
			}
		case (2):
			printf("Enter index: ");
			scanf("%zu", &index);
			if (index < n) break;
			else {
				puts("index: invalid");
				return 1;
			}
		default:
			puts("choice: invalid");
			return 1;
	}
	for (size_t i = index; i < n; ++i)
		array[i] = array[i + 1];
	n--;
	printf("Result: ");
	for (size_t i = 0; i < n; ++i)
		printf("%d ", array[i]);
	puts("");
	return 0;
}

size_t search(int value, int *array, size_t n)
{
	size_t i;
	for (i = 0; i < n; ++i)
		if (array[i] == value) return i;
	return n;
}
