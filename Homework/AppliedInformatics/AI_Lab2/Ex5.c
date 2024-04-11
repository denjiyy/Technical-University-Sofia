#include <stdio.h>

int main(void) {
	int a = 100;
	float b = 331.79;
	double c = 8.44e+11;
	char d = 'A';
	bool e = false;

	printf("a = %i\n", a);
	printf("b = %f\n", b);
	printf("c = %e\n", c);
	printf("c = %g\n", c);
	printf("d = %c\n", d);
	printf("e = %i\n", e);

	return 0;
}