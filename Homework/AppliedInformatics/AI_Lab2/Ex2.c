#include <stdio.h>

int main(void) {
	float x, polynomial;
	x = 2.55;
	polynomial = 3 * x * 3 - 5 * x * 2 + 6;
	printf("The result is: %f.\n", polynomial);
	return 0;
}