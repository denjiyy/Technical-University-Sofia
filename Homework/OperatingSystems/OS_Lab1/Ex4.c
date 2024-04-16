#include <stdio.h>

int main() {
    int arr[1000], size;

    printf("Enter the size of the array:\n");
    scanf_s("%d", &size);

    printf("Enter the elements of the array:\n");
    for (int i = 0; i < size; i++)
    {
        scanf_s("%d", arr + i);
    }

    int* ptr = arr;

    printf("The array elements are:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", *(ptr + i));
    }
    printf("\n");

    return 0;
}