#include<stdio.h>
#include"file_analysis.h"

int count_lines(FILE *fp){
    int l=0;
    char line[200];
    while(fgets(line,sizeof(line),fp)!=NULL){
        l++;
    }
    return l;
}

int count_words(FILE *fp){
    int w=0;
    char word[100];
    while(fscanf(fp,"%s",word)==1){
        w++;
    }
    return w;
}

int count_chars(FILE* fp){
    int c=0;
    char line[200];
    while(fgets(line,sizeof(line),fp)!=NULL){
        int i=0;
        while(line[i]!='\n'){
            if(line[i]==' '||line[i]=='\t'){
                i++;
            }
            else{
                c++;
                i++;
            }
        }
    }
    return c;
}