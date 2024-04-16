#include <stdio.h>

int findMax(int arr[], int size) {
	int max = arr[0];

	for (int i = 0; i < size; i++)
	{
		if (max < arr[i])
		{
			max = arr[i];
		}
	}

	return max;
}

int findMin(int arr[], int size) {
	int min = arr[0];

	for (int i = 0; i < size; i++)
	{
		if (min > arr[i])
		{
			min = arr[i];
		}
	}

	return min;
}

int main()
{
	int arr[1000], size;

	printf("Enter the array size:\n");
	scanf_s("%d", &size);

	printf("Enter the array elements:\n");
	for (int i = 0; i < size; i++)
	{
		scanf_s("%d", &arr[i]);
	}

	printf("The smallest element in the array is: %d and the biggest is %d", findMin(arr, size), findMax(arr, size));

	return 0;
}