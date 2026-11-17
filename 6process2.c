
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

#define SIZE 1024

void analyze(char text[], int *chars,
             int *words, int *lines)
{
    int i, in_word = 0;

    *chars = 0;
    *words = 0;
    *lines = 1;

    for(i = 0; text[i] != '\0'; i++)
    {
        (*chars)++;

        if(isspace((unsigned char)text[i]))
            in_word = 0;
        else if(!in_word)
        {
            (*words)++;
            in_word = 1;
        }
    }
}

int main()
{
    int fd;
    char input[SIZE], buffer[SIZE];

    printf("--- Process 2 Started ---\n");

    while(1)
    {
        fd = open("fifo1", O_RDONLY);

        int n = read(fd, input, SIZE-1);
        close(fd);

        if(n <= 0)
            continue;

        input[n] = '\0';

        if(strcmp(input, "exit") == 0)
            break;

        int chars, words, lines;

        analyze(input, &chars, &words, &lines);

        FILE *fp = fopen("report.txt", "w");

        fprintf(fp, "Original Text: %s\n", input);
        fprintf(fp, "Total Characters: %d\n", chars);
        fprintf(fp, "Total Words: %d\n", words);
        fprintf(fp, "Total Lines: %d\n", lines);

        fclose(fp);

        fp = fopen("report.txt", "r");

        fd = open("fifo2", O_WRONLY);

        while(fgets(buffer, SIZE, fp) != NULL)
            write(fd, buffer, strlen(buffer));

        fclose(fp);
        close(fd);
    }

    printf("Process 2 Terminating\n");

    return 0;
}
