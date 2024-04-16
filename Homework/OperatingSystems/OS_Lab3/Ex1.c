#include <stdio.h>

int factorialRecursive(int x) {
	if (x <= 0)
	{
		return 1;
	}

	return x * factorialRecursive(x - 1);
}

int main() {
	int x;

	printf("Enter a number:\n");

	scanf_s("%d", &x);
	
	printf("The factorial of the number %d is %d", x, factorialRecursive(x));

	return 0;
}