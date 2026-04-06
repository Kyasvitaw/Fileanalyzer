#include<stdio.h>
#include"utils.h"

FILE* safe_open(const char *filename, const char *mode) {
    FILE *fp = fopen(filename, mode);
    if (!fp) {
        printf("Error opening file: %s\n", filename);
    }
    return fp;
}