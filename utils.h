#include<stdio.h>

#define MAX_LEN 50
#define MAX_WORDS 1000

typedef struct {
    char word[MAX_LEN];
    int count;
}WordFreq;

FILE* safe_open(const char *filename, const char *mode);
void toLowerCase(char *str);
void cleanWord(char* word);
int findWord(WordFreq arr[], int size, char *word);
int cmp(const void *a, const void *b);