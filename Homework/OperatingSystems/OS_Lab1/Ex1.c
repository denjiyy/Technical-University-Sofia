#include <stdio.h>

int main() {
	int a, b;
	printf("Enter the first number:\n");
	scanf_s("%d", & a);
	printf("Enter the second number:\n");
	scanf_s("%d", &b);

	printf("Address of the first number a: %p\n", (void*)&a);
	printf("Address of the second number b: %p\n", (void*)&b);

	return 0;
}