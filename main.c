#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "file_analysis.h"
#include "file_traversal.h"
#include "utils.h"


void process_line(char*line){
    char* token=strtok(line," ");
    char directory[256];
    strcpy(directory,token);
    token=strtok(NULL," ");
    if(token==NULL){
        
    }
    if(strcmp(token,"replace")==0){


    }
    if(strcmp(token,"count1")==0){


    }
    if(strcmp(token,"count2")==0){


    }
}

int main(int a,char*b[]){
    if(a!=2){
        printf("error:invalid arguments\n");
        return 1;
    }
    char input[256];
    strcpy(input,b[1]);
    FILE* f;
    f=fopen(input,"r");
    if(f==NULL){
        printf("file does not exist\n");
        return 1;
    }
    char line[300];
    while(fgets(line,sizeof(line),f)!=NULL){

    }

}