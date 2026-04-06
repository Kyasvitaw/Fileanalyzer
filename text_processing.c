#include<stdio.h>
#include<string.h>
#include"text_processing.h"
#include"utils.h"

void FindWord(FILE* fp, char word[]){
    
    int l=0;
    char line[200];
    int flag = 0;
    
    while(fgets(line,sizeof(line),fp)!=NULL){
        l++;
        char* ptr=strstr(line, word);
        if(ptr!=NULL){
            flag=1;
            //freq of word in particular line
            int freq=1;
            int length=strlen(word);
            ptr=ptr+length;
            while(!strstr(ptr,word)){
                ptr=ptr+length;
                freq++;
            }
            if(freq>1){
                printf("Found at Line No : %d and it occured %d times\n",l,freq);
            }
            else{
               printf("Found at Line No : %d and it occured %d time\n",l,freq); 
            }
        }
    }

    if(flag==0){
        printf("Not found\n");
    }
}

int countOccurnces(FILE* fp,char word[]){
    
    char line[200];
    int flag = 0;
    int count=0;
    
    while(fgets(line,sizeof(line),fp)!=NULL){
        
        char* ptr=strstr(line, word);
        if(ptr!=NULL){
            flag=1;
            count++;
            //freq of word in particular line
            int freq=1;
            int length=strlen(word);
            ptr=ptr+length;
            while(!strstr(ptr,word)){
                ptr=ptr+length;
                freq++;
            }
            count+=freq;
        }
    }

    return count;
}

void ReplaceWord(FILE* fp, char word1[], char word2[],char filename[]){
    
    FILE* nf;
    nf = safe_open("temp.txt","w+");

    char word[50];
    while(fscanf(fp,"%s",word)==1){
        if(strcmp(word, word1)==0){
            fprintf(nf,"%s ",word2);
        }
        else{
            fprintf(nf,"%s ",word);
        }
    }

    fclose(nf);

    remove(filename);
    rename("temp.txt",filename);
}