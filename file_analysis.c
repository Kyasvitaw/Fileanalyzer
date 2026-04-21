#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "file_analysis.h"
#include "utils.h"

int count_lines(FILE *fp)
{
    int l = 0;
    char line[200];
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        l++;
    }
    return l;
}

int count_words(FILE *fp)
{
    int w = 0;
    char word[100];
    while (fscanf(fp, "%s", word) == 1)
    {
        w++;
    }
    return w;
}

int count_chars(FILE *fp)
{
    int c = 0;
    char line[200];
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        int i = 0;
        while (line[i] != '\n')
        {
            if (line[i] == ' ' || line[i] == '\t')
            {
                i++;
            }
            else
            {
                c++;
                i++;
            }
        }
    }
    return c;
}

void topNWords(FILE *fp, int N)
{
    WordFreq arr[MAX_WORDS];
    int size = 0;

    char word[MAX_LEN];

    while (fscanf(fp, "%s", word) == 1)
    {

        cleanWord(word);
        toLowerStr(word);

        if (strlen(word) == 0)
            continue;

        int idx = findWord(arr, size, word);

        if (idx == -1)
        {
            strcpy(arr[size].word, word);
            arr[size].count = 1;
            size++;
        }
        else
        {
            arr[idx].count++;
        }
    }

    // sort by frequency
    qsort(arr, size, sizeof(WordFreq), cmp);

    printf("\nTop %d words:\n", N);
    for (int i = 0; i < N && i < size; i++)
    {
        printf("%d. %s -> %d\n", i + 1, arr[i].word, arr[i].count);
    }
}