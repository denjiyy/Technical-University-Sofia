#include <stdio.h>

int countWords(FILE *fileName) {
    int words = 0;
    _Bool isWord = 0;
    int c;

    while ((c = fgetc(fileName)) != EOF)
    {
        if (c == ' ' || c == '\t' || c == '\n')
        {
            isWord = 0;
        }
        else if (!isWord) {
            isWord = 1;
            words++;
        }
    }

    return words;
}

int main() {
    char fileName[20];

    printf("Enter the file name: ");
    fgets(fileName, sizeof(fileName), stdin);

    if (fileName[strlen(fileName) - 1] == '\n')
        fileName[strlen(fileName) - 1] = '\0';

    FILE* fptr = fopen(fileName, "r");

    if (fptr == NULL) {
        printf("Failed to open file.\n");
        return 1;
    }

    int words = countWords(fptr);

    printf("Number of words in the file: %d\n", words);

    fclose(fptr);
    return 0;
}