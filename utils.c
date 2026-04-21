#include <stdio.h>
#include "utils.h"
#define MAX_LEN 50

FILE *safe_open(const char *filename, const char *mode)
{
    FILE *fp = fopen(filename, mode);
    if (!fp)
    {
        printf("Error opening file: %s\n", filename);
    }
    return fp;
}

void toLowerCase(char *str)
{
    for (int i = 0; str[i]; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            str[i] = str[i] + 32;
        }
    }
}

void cleanWord(char *word)
{
    int i, j = 0;
    char temp[MAX_LEN];

    for (i = 0; word[i]; i++)
    {
        if (isalnum(word[i]))
        {
            temp[j++] = word[i];
        }
    }
    temp[j] = '\0';
    strcpy(word, temp);
}

int findWord(WordFreq arr[], int size, char *word)
{
    for (int i = 0; i < size; i++)
    {
        if (strcmp(arr[i].word, word) == 0)
            return i;
    }
    return -1;
}

int cmp(const void *a, const void *b)
{
    WordFreq *w1 = (WordFreq *)a;
    WordFreq *w2 = (WordFreq *)b;
    return w2->count - w1->count;
}