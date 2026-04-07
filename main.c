#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "file_analysis.h"
#include "file_traversal.h"
#include "utils.h"

int main(int a,char*b[]){
    if(a!=2){
        printf("error:invalid arguments\n");
        return 1;
    }

    char input[256];
    strcpy(input,b[1]);

    FILE* f;
    f = safe_open(input,"r");

    char dirpath[50];
    fscanf(f,"%s",dirpath);

    char line[100];
    while(fgets(line,sizeof(line),f)){

        char op[10];
        sscanf(line,"%s",op);
        toLowercase(op);

        char word[100];
        char filename[100];//filepath

        if(strcmp(op,"search")==0){
            //line: search {word} in {filename}
            sscanf(line,"%s",word);
            sscanf(line,"%s",filename);
            //filename = "IN"
            //we need to scan again
            sscanf(line,"%s",filename);

            FILE* f;
            f=safe_open(filename,"r");

            int flag = FindWord(f,word);
            if(flag == 0){
                printf("This word:%s is not there in %s\n",word,filename);
            }
            printf("\n");
           printf("_______________________________________________\n");
           printf("\n");
        }

        if(strcmp(op,"count")==0){
            //line: count {word} in {filename}
            sscanf(line,"%s",word);
            sscanf(line,"%s",filename);
            sscanf(line,"%s",filename);

            FILE* f;
            f=safe_open(filename,"r");

            int count = countOccurences(f,word);

            if(count == 1){
                printf("%s appeared once in %s\n",word,filename);
            }

            else if(count == 0){
                printf("%s is not there in %s\n",word,filename);
            }

            else{
                printf("%s occured %d times in %s",word,count,filename);
            }

            printf("\n");
            printf("_______________________________________________\n");
            printf("\n");
        }

        if(strcmp(op,"replace")==0){
            //line: replace {word} with {newword} in {filename} 
            sscanf(line,"%s",word);
            char newword[100];
            sscanf(line,"%s",newword);
            sscanf(line,"%s",newword);
            sscanf(line,"%s",filename);
            sscanf(line,"%s",filename);

            FILE* f;
            f = safe_open(filename,"r");

            ReplaceWord(f,word,newword);
        }
    }

}