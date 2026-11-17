
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

#define SIZE 1024

int main()
{
    int pipe1[2], pipe2[2];
    pid_t pid;

    pipe(pipe1);
    pipe(pipe2);

    pid = fork();

    if(pid < 0)
    {
        printf("Fork Failed");
        return 1;
    }

    if(pid > 0)
    {
        close(pipe1[0]);
        close(pipe2[1]);

        char filepath[SIZE];
        char buffer[SIZE];
        int n;

        printf("Enter file pathname: ");
        fgets(filepath, SIZE, stdin);

        filepath[strcspn(filepath, "\n")] = '\0';

        write(pipe1[1], filepath, strlen(filepath)+1);
        close(pipe1[1]);

        printf("\nFile Content:\n");

        while((n = read(pipe2[0], buffer, SIZE-1)) > 0)
        {
            buffer[n] = '\0';
            printf("%s", buffer);
        }

        close(pipe2[0]);
        wait(NULL);
    }
    else
    {
        close(pipe1[1]);
        close(pipe2[0]);

        char filepath[SIZE];
        char buffer[SIZE];

        int n = read(pipe1[0], filepath, SIZE-1);
        close(pipe1[0]);

        if(n > 0)
        {
            filepath[n] = '\0';

            int fd = open(filepath, O_RDONLY);

            if(fd < 0)
            {
                char *msg = "File cannot be opened";
                write(pipe2[1], msg, strlen(msg));
            }
            else
            {
                while((n = read(fd, buffer, SIZE)) > 0)
                    write(pipe2[1], buffer, n);

                close(fd);
            }
        }

        close(pipe2[1]);
        exit(0);
    }

    return 0;
}
