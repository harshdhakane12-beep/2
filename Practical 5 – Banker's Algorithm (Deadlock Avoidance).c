
#include <stdio.h>
#include <stdbool.h>

int main()
{
    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], need[n][m];
    int avail[m], work[m];
    int finish[n], safe[n];

    printf("Enter Allocation Matrix:\n");

    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Max Matrix:\n");

    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources:\n");

    for(int j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    printf("\nNeed Matrix:\n");

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
            printf("%d ", need[i][j]);

        printf("\n");
    }

    for(int i = 0; i < n; i++)
        finish[i] = 0;

    for(int j = 0; j < m; j++)
        work[j] = avail[j];

    int count = 0;

    while(count < n)
    {
        int found = 0;

        for(int i = 0; i < n; i++)
        {
            if(finish[i] == 0)
            {
                int flag = 1;

                for(int j = 0; j < m; j++)
                {
                    if(need[i][j] > work[j])
                    {
                        flag = 0;
                        break;
                    }
                }

                if(flag == 1)
                {
                    for(int j = 0; j < m; j++)
                        work[j] += alloc[i][j];

                    safe[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0)
        {
            printf("\nSystem is in UNSAFE state\n");
            return 0;
        }
    }

    printf("\nSystem is in SAFE state\n");
    printf("Safe Sequence: ");

    for(int i = 0; i < n; i++)
        printf("P%d ", safe[i]);

    printf("\n");

    return 0;
}
