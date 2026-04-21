#include<stdio.h>

#define MAX_WORDS 1000
#define MAX_LEN 50

typedef struct {
    char word[MAX_LEN];
    int count;
}WordFreq;

int count_lines(FILE *fp);
int count_words(FILE *fp);
int count_chars(FILE *fp);
void topNWords(FILE *fp, int N);