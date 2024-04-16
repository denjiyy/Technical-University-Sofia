#include <stdio.h>

void swap(int *x, int *y) {
	int temp;

	temp = *x;
	*x = *y;
	*y = temp;
}

int main() {
	int a, b;

	printf("Enter number a:\n");
	scanf_s("%d", &a);
	printf("Enter number b:\n");
	scanf_s("%d", &b);

	printf("Before swap number a is: %d, number b is: %d\n", a, b);

	swap(&a, &b);

	printf("After swap number a is: %d, number b is: %d\n", a, b);

	return 0;
}