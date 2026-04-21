#ifndef UTILS_H
#define UTILS_H

#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include"file_analysis.h"

#define MAX_LEN 50
#define MAX_WORDS 1000

FILE* safe_open(const char *filename, const char *mode);
void toLowerCase(char *str);
void cleanWord(char* word);
int findWord(WordFreq arr[], int size, char *word);
int cmp(const void *a, const void *b);

#endif