#include <stdio.h>

int countDigits(int n) {
    if (n < 10) {
        return 1;
    }

    return 1 + countDigits(n / 10);
}

int main() {
    int num;
    printf("Enter a whole positive number:\n");
    scanf_s("%d", &num);
    if (num <= 0) {
        printf("Enter a positive number!\n");
        return 1;
    }
    int digits = countDigits(num);
    printf("The count of digits in the number is: %d\n", digits);
    return 0;
}