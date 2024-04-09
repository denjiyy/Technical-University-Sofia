#include <stdio.h>

int function(int a, int b, int c) {
	return (a + b) * c;
}

int main(void) {
	int a, b, c;
	printf("Enter a: ");
	scanf_s("%d", &a);
	printf("Enter b: ");
	scanf_s("%d", &b);
	printf("Enter c: ");
	scanf_s("%d", &c);

	printf("%d = (%d + %d) * %d", function(a, b, c), a, b, c);
	return 0;
}