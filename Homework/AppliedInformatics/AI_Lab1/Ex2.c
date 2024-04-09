#include <stdio.h>

int main(void) {
	int a, b;
	printf("Enter the first number:\n");
	scanf_s("%d", &a);
	printf("Enter the second number:\n");
	scanf_s("%d", &b);

	printf("The subtraction of %d and %d is %d", a, b, subtraction(a, b));
	return 0;
}

int subtraction(int a, int b) {
	return a - b;
}