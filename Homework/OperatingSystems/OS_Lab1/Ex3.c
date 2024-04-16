#include <stdio.h>

int findMaxElement(int arr[], int size) {
	int max = arr[0];

	for (int i = 0; i < size; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}

	return max;
}

void printArray(int arr[], int size) {
	for (int i = 0; i < size; i++)
	{
		printf("%d ", arr[i]);
	}
}

int main() {
	int arr[1000], size;

	printf("Enter the size of the array:\n");

	scanf_s("%d", &size);

	printf("Enter the elements of the array:\n");

	for (int i = 0; i < size; i++)
	{
		scanf_s("%d", &arr[i]);
	}

	printf("The array is:\n");

	printArray(arr, size);

	printf("\n");

	int maxElement = findMaxElement(arr, size);

	printf("The max element in the array is: %d, its address is: %d", maxElement, (void*)&maxElement);

	return 0;
}