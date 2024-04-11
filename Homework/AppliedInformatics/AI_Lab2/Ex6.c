#include <stdio.h>
int main(void)
{
	int number1;
	float number2;
	double number3;
	char letter1;
	printf("Enter int number1: ");
	scanf_s("%i", &number1);
	printf("Enter float number2: ");
	scanf_s("%f", &number2);
	printf("Enter double number3: ");
	scanf_s("%le", &number3);
	printf("Enter char letter1: ");
	scanf_s(" %c", &letter1, 1);
	printf("\n\n");
	printf("Results:\n");
	printf("number1: %i\n", number1);
	printf("number2: %f\n", number2);
	printf("number3: %le\n", number3);
	printf("letter1: %c\n", letter1);
	return 0;
}