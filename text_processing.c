#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "text_processing.h"
#include "utils.h"

int FindWord(FILE *fp, char word[])
{

    int l = 0;
    char line[200];
    int flag = 0;

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        l++;
        char *ptr = strstr(line, word);
        if (ptr != NULL)
        {
            flag = 1;
            // freq of word in particular line
            int freq = 1;
            int length = strlen(word);
            ptr = ptr + length;
            while (strstr(ptr, word) != NULL)
            {
                ptr = ptr + length;
                freq++;
            }
            if (freq > 1)
            {
                printf("Found at Line No : %d and it occured %d times\n", l, freq);
            }
            else
            {
                printf("Found at Line No : %d and it occured %d time\n", l, freq);
            }
        }
    }

    return flag;
}

int countOccurences(FILE *fp, char word[])
{

    char line[200];
    int flag = 0;
    int count = 0;

    while (fgets(line, sizeof(line), fp) != NULL)
    {

        char *ptr = strstr(line, word);
        if (ptr != NULL)
        {
            flag = 1;
            count++;
            // freq of word in particular line
            int freq = 0;
            int length = strlen(word);
            ptr = ptr + length;
            while (strstr(ptr, word) != NULL)
            {
                ptr = ptr + length;
                freq++;
            }
            count += freq;
        }
    }

    return count;
}

void ReplaceWord(FILE *fp, char word1[], char word2[], char filename[])
{
    FILE *temp = safe_open("temp.txt", "w");

    rewind(fp);  // IMPORTANT

    char ch;
    char buffer[100];
    int i = 0;

    while ((ch = fgetc(fp)) != EOF)
    {
        if (isalnum(ch))
        {
            if (i < 99)  // prevent overflow
                buffer[i++] = ch;
        }
        else
        {
            if (i > 0)
            {
                buffer[i] = '\0';

                if (strcmp(buffer, word1) == 0)
                    fprintf(temp, "%s", word2);
                else
                    fprintf(temp, "%s", buffer);

                i = 0;
            }

            fputc(ch, temp);
        }
    }

    //  HANDLE LAST WORD
    if (i > 0)
    {
        buffer[i] = '\0';

        if (strcmp(buffer, word1) == 0)
            fprintf(temp, "%s", word2);
        else
            fprintf(temp, "%s", buffer);
    }

    fclose(temp);

    if (remove(filename) != 0)
        perror("Error deleting original file");

    if (rename("temp.txt", filename) != 0)
        perror("Error renaming temp file");
}

void Deleteword(FILE *fp, char word[], char filename[])
{
    FILE *temp = safe_open("temp.txt", "w");

    rewind(fp);  // ensure reading from start

    char ch;
    char buffer[100];
    int i = 0;

    while ((ch = fgetc(fp)) != EOF)
    {
        if (isalnum(ch))
        {
            if (i < 99)   //prevent overflow
                buffer[i++] = ch;
        }
        else
        {
            if (i > 0)
            {
                buffer[i] = '\0';

                //only write if NOT the word to delete
                if (strcmp(buffer, word) != 0)
                    fprintf(temp, "%s", buffer);

                i = 0;
            }

            fputc(ch, temp); // keep delimiter (space, newline, etc.)
        }
    }

    // handle last word 
    if (i > 0)
    {
        buffer[i] = '\0';

        if (strcmp(buffer, word) != 0)
            fprintf(temp, "%s", buffer);
    }

    fclose(temp);

    if (remove(filename) != 0)
        perror("Error deleting original file");

    if (rename("temp.txt", filename) != 0)
        perror("Error renaming temp file");
}