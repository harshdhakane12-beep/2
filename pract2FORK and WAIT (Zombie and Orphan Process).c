
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX 100

void bubble_sort(int a[], int n)
{
    int i, j, temp;

    for(i = 0; i < n-1; i++)
        for(j = 0; j < n-i-1; j++)
            if(a[j] > a[j+1])
            {
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
}

void selection_sort(int a[], int n)
{
    int i, j, min, temp;

    for(i = 0; i < n-1; i++)
    {
        min = i;

        for(j = i+1; j < n; j++)
            if(a[j] < a[min])
                min = j;

        temp = a[i];
        a[i] = a[min];
        a[min] = temp;
    }
}

void display(int a[], int n)
{
    for(int i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");
}

int main()
{
    int a[MAX], p[MAX], c[MAX];
    int n, choice;

    printf("Enter number of integers: ");
    scanf("%d", &n);

    if(n <= 0 || n > MAX)
        return 1;

    printf("Enter integers:\n");

    for(int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
        p[i] = a[i];
        c[i] = a[i];
    }

    printf("\n1. Normal Execution");
    printf("\n2. Zombie State");
    printf("\n3. Orphan State");
    printf("\nEnter choice: ");
    scanf("%d", &choice);

    pid_t pid = fork();

    if(pid < 0)
    {
        printf("Fork Failed");
        return 1;
    }

    if(pid == 0)
    {
        printf("\nChild Process Started\n");
        printf("Child PID: %d\n", getpid());

        if(choice == 3)
        {
            sleep(5);
            printf("New Parent PID: %d\n", getppid());
        }

        selection_sort(c, n);

        printf("Child Sorted Array: ");
        display(c, n);

        exit(0);
    }
    else
    {
        printf("\nParent Process Started\n");

        bubble_sort(p, n);

        printf("Parent Sorted Array: ");
        display(p, n);

        if(choice == 1)
        {
            wait(NULL);
            printf("Child Process Completed\n");
        }
        else if(choice == 2)
        {
            printf("Parent sleeping without wait\n");
            sleep(10);
            wait(NULL);
            printf("Zombie Process Reaped\n");
        }
        else if(choice == 3)
        {
            printf("Parent exiting\n");
            exit(0);
        }
        else
        {
            wait(NULL);
            printf("Invalid Choice\n");
        }
    }

    return 0;
}
