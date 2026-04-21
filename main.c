#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include "file_analysis.h"
#include "text_processing.h"
#include "utils.h"

void get_directory_name(const char *path, char *dirname)
{
    int len = strlen(path);

    // Remove trailing '/'
    while (len > 0 && path[len - 1] == '/')
        len--;

    int i = len - 1;

    // Find last '/'
    while (i >= 0 && path[i] != '/')
        i--;

    strncpy(dirname, path + i + 1, len - i - 1);
    dirname[len - i - 1] = '\0';
}

void directoryTraversal(const char *path)
{

    DIR *directory;
    struct dirent *entry;
    directory = opendir(path);

    if (directory == NULL)
    {
        perror("opendir");
        return;
    }

    char dirname[1024];
    get_directory_name(path, dirname);

    while ((entry = readdir(directory)) != NULL)
    {
        // skip . and ..
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        char fullPath[1024];
        snprintf(fullPath, sizeof(fullPath), "%s/%s", path, entry->d_name);

        struct stat st;
        if (stat(fullPath, &st) == 0)
        {

            if (S_ISREG(st.st_mode))
            {
                // file

                // already processed files
                int flag = 0;
                FILE *apf1;
                apf1 = fopen("processedfiles.txt", "r+");
                if (apf1 == NULL)
                {
                    perror("processed files");
                    return;
                }

                char line[1024];
                while (fgets(line, sizeof(line), apf1) != NULL)
                {
                    line[strcspn(line, "\n")] = '\0';
                    if (!strcmp(line, fullPath))
                    {
                        flag = 1;
                        break;
                    }
                }
                fclose(apf1);

                if (flag == 1)
                {
                    continue;
                }

                FILE *apf2;
                apf2 = fopen("processedfiles.txt", "a+");
                if (apf2 == NULL)
                {
                    perror("proceesed files");
                    return;
                }
                fprintf(apf2, "%s\n", fullPath);
                fclose(apf2);

                // graph.dot
                FILE *g;
                g = fopen("graph.dot", "a+");
                if (g == NULL)
                {
                    perror("graph.dot");
                    return;
                }

                // add a directed edge here
                //fprintf(g, "\"%s\"->\"%s\" [shape=note, style=filled, fillcolor=lightyellow];\n", dirname, entry->d_name);
                fprintf(g, "\"%s\" [shape=note, style=filled, fillcolor=lightyellow];\n", entry->d_name);
                fprintf(g, "\"%s\"->\"%s\";\n", dirname, entry->d_name);
                fclose(g);

                FILE *file;
                file = fopen(fullPath, "r");
                if (file == NULL)
                {
                    perror("file");
                    return;
                }

                // words.txt
                FILE *w;
                w = fopen("words.txt", "a+");
                if (w == NULL)
                {
                    perror("words.txt");
                    return;
                }

                int nw = count_words(file);
                rewind(file);
                fprintf(w, "%s %d\n", entry->d_name, nw);
                fclose(w);

                // chars.txt
                FILE *c;
                c = fopen("chars.txt", "a+");
                if (c == NULL)
                {
                    perror("chars.txt");
                    return;
                }

                int nc = count_chars(file);
                rewind(file);
                fprintf(c, "%s %d\n", entry->d_name, nc);
                fclose(c);

                // lines.txt
                FILE *l;
                l = fopen("lines.txt", "a+");
                if (l == NULL)
                {
                    perror("lines.txt");
                    return;
                }

                int nl = count_lines(file);
                fprintf(l, "%s %d\n", entry->d_name, nl);
                fclose(l);

                fclose(file);
            }

            if (S_ISDIR(st.st_mode))
            {
                // dir

                // graph.dot
                FILE *g;
                g = fopen("graph.dot", "a+");
                if (g == NULL)
                {
                    perror("graph.dot");
                    return;
                }
                // add a directed edge here
                //fprintf(g, "\"%s\"->\"%s\" [shape=folder, style=filled, fillcolor=lightblue];\n", dirname, entry->d_name);
                fprintf(g, "\"%s\" [shape=folder, style=filled, fillcolor=lightblue];\n", entry->d_name);
                fprintf(g, "\"%s\"->\"%s\";\n", dirname, entry->d_name);
                fclose(g);

                directoryTraversal(fullPath); // recursion
            }
        }
    }
    closedir(directory);
}

int main(int a, char *b[])
{
    if (a != 2)
    {
        printf("error:invalid arguments\n");
        return 1;
    }

    char input[256];
    strcpy(input, b[1]);

    FILE *fi;
    fi = fopen(input, "r");
    if (fi == NULL)
    {
        perror("input.txt");
        return 1;
    }

    char dirpath[1024];
    fscanf(fi, "%s", dirpath);

    char line[100];
    while (fgets(line, sizeof(line), fi))
    {
        int j=0;
        while(line[j]=='\n'){
            line[j]=' ';
            j++;
        }
        
        printf("%s\n",line);
        char op[10];
        sscanf(line, "%s", op);
        toLowerCase(op);

        char word[100];
        char filename[1024]; // filepath

        if (strcmp(op, "search") == 0)
        {
            // line: search {word} in {filename}
            sscanf(line, "%s %s %*s %s", op, word, filename);

            printf("%s\n", filename);
            printf("\n");
            FILE *f;
            f = fopen(filename, "r");
            if (f == NULL)
            {
                perror("file");
                printf("%s %s in %s command failed\n", op, word, filename);
                continue;
            }

            int flag = FindWord(f, word);
            if (flag == 0)
            {
                printf("word:%s is not there in %s\n", word, filename);
            }

            fclose(f);

            printf("\n");
            printf("_______________________________________________\n");
            printf("\n");
        }

        if (strcmp(op, "count") == 0)
        {
            // line: count {word} in {filename}
            sscanf(line, "%s %s %*s %s", op, word, filename);
            printf("%s\n", filename);
            FILE *f;
            f = fopen(filename, "r");
            if (f == NULL)
            {
                perror("file");
                printf("%s %s in %s command failed\n", op, word, filename);
                continue;
            }

            int count = countOccurences(f, word);

            if (count == 1)
            {
                printf("%s appeared once in %s\n", word, filename);
            }

            else if (count == 0)
            {
                printf("%s is not there in %s\n", word, filename);
            }

            else
            {
                printf("%s occured %d times in %s", word, count, filename);
            }

            fclose(f);

            printf("\n");
            printf("_______________________________________________\n");
            printf("\n");
        }

        if (strcmp(op, "replace") == 0)
        {
            // line: replace {word} with {newword} in {filename}

            char newword[100];

            sscanf(line, "%s %s %*s %s %*s %s", op, word, newword, filename);

            FILE *f;
            f = fopen(filename, "r");
            if (f == NULL)
            {
                perror("file");
                printf("%s %s with %s in %s command failed\n", op, word, newword, filename);
                continue;
            }
            int count = countOccurences(f, word);
            if (count == 0)
            {
                printf("There is no %s in %s\n", word, filename);
            }
            if (count > 0)
            {
                ReplaceWord(f, word, newword, filename);
                printf("%s %s with %s in %s command sucessfully executed\n",op,word,newword,filename);
            }

            printf("\n");
            printf("_______________________________________________\n");
            printf("\n");
            fclose(f);
        }

        if (strcmp(op, "delete") == 0)
        {
            // line: delete {word} in {filename}
            sscanf(line, "%s %s %*s %s", op, word, filename);

            FILE *f;
            f = fopen(filename, "r");
            if (f == NULL)
            {
                perror("file");
                printf("%s %s in %s command failed\n", op, word, filename);
                continue;
            }
            int count = countOccurences(f, word);
            if (count == 0)
            {
                printf("There is no %s in %s\n", word, filename);
            }
            if (count > 0)
            {
                Deleteword(f, word, filename);
                printf("%s %s in %scommand sucessfully executed\n",op,word,filename);
            }

            printf("_______________________________________________\n");
            printf("\n");
            fclose(f);
        }

        if (strcmp(op, "deletefile") == 0)
        {
            // line: deletefile {filename}
            // sscanf(line, "%s %s", op, filename);
            printf("%s\n",line);
            if (sscanf(line, "%s %s", op, filename) != 2)
            {
                printf("Invalid command format. Usage: deletefile <filename>\n");
                continue;
            }
            //remove newline if present
            filename[strcspn(filename, "\n")] = '\0';

            if (remove(filename) == 0)
            {
                printf("File '%s' deleted successfully.\n", filename);
            }
            else
            {
                perror("Error deleting file"); 
                printf("File '%s' does not exist or permission denied etc\n", filename);
            }

            printf("_______________________________________________\n");
            printf("\n");
        }

        if (strcmp(op, "append") == 0)
        {
            // line: append {word} to {filename}
            sscanf(line, "%s %s %*s %s", op, word, filename);

            FILE *f;
            f = fopen(filename, "r");
            if (f == NULL)
            {
                perror("file");
                printf("%sing %s to %s failed.\n", op, word, filename);
                continue;
            }

            fprintf(f, "%s ", word);
            fclose(f);
            printf("Word '%s' appended sucessfully to file %s\n", word, filename);
            printf("_______________________________________________\n");
            printf("\n");
        }

        if (strcmp(op, "rename") == 0)
        {
            // line: rename {filename} to {newname}
            char newname[50];
            sscanf(line, "%s %s %*s %s", op, filename, newname);
            if (rename(filename, newname) == 0)
            {
                printf("File renamed from '%s' to '%s'\n", filename, newname);
            }
            else
            {
                if (errno == ENOENT)
                {
                    printf("Error: Source file '%s' does not exist.\n", filename);
                }
                else if (errno == EACCES)
                {
                    printf("Error: Permission denied.\n");
                }
                else if (errno == EEXIST)
                {
                    printf("Error: Destination file '%s' already exists.\n", newname);
                }
                else
                {
                    perror("Error renaming file");
                }
            }
            printf("_______________________________________________\n");
            printf("\n");
        }

        if (strcmp(op, "top") == 0)
        {
            // line: top {num} {filename}
            int num;
            sscanf(line, "%s %d %s", op, &num, filename);

            FILE *f;
            f = fopen(filename, "r");
            if (f == NULL)
            {
                perror("file");
                continue;
            }

            topNWords(f, num);
            fclose(f);
            printf("_______________________________________________\n");
            printf("\n");
        }
    }

    fclose(fi);

    FILE *g;
    g = fopen("graph.dot", "a+");
    if (g == NULL)
    {
        perror("graph.dot");
        return 1;
    }

    fprintf(g, "digraph G {\n");
    fprintf(g,"node [style=filled]\n");
    fclose(g);

    directoryTraversal(dirpath);

    FILE *g1;
    g1 = fopen("graph.dot", "a");
    if (g1 == NULL)
    {
        perror("graph.dot");
        return 1;
    }

    fprintf(g1, "}\n");
    fclose(g1);

    // graph.png
    system("dot -Tpng graph.dot -o graph.png");

    // bargraphs
    system("gnuplot plot_lines.gp");
    system("gnuplot plot_words.gp");
    system("gnuplot plot_chars.gp");
}