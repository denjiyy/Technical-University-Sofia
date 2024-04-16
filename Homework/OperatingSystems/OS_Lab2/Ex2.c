#include <stdio.h>

void bubble_sort(char arr[][1000], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            int k = 0;
            while (arr[j][k] != '\0' && arr[j + 1][k] != '\0' && arr[j][k] == arr[j + 1][k]) {
                k++;
            }
            if (arr[j][k] > arr[j + 1][k]) {
                char temp[1000];
                for (int m = 0; arr[j][m] != '\0'; m++) {
                    temp[m] = arr[j][m];
                }
                for (int m = 0; arr[j + 1][m] != '\0'; m++) {
                    arr[j][m] = arr[j + 1][m];
                }
                for (int m = 0; temp[m] != '\0'; m++) {
                    arr[j + 1][m] = temp[m];
                }
            }
        }
    }
}

int main() {
    char lines[25][1000];
    int count = 0;

    printf("Enter strings:\n");
    
    while (1) {
        if (count >= 25)
            break;
        if (!fgets(lines[count], sizeof(lines[0]), stdin))
            break;
        if (lines[count][0] == '\n')
            break;
        lines[count][strcspn(lines[count], "\n")] = 0;
        count++;
    }

    bubble_sort(lines, count);

    printf("\nSorted rows:\n");
    for (int i = 0; i < count; i++) {
        printf("%s\n", lines[i]);
    }

    return 0;
}