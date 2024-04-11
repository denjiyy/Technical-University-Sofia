#include <stdio.h>

int main(void) {
	float c, f;
	printf("Enter temperature in Fahrenheit: ");
	scanf_s("%f", &f);
	c = (f - 32.0) / 1.8;
	printf("The temperature in Celsius is: %f.\n", c);
	return 0;
}