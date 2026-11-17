
#include <stdio.h>
#include <stdlib.h>

void SSTF(int req[], int n, int head)
{
    int visited[100] = {0};
    int total = 0, diff, min, pos;

    printf("\nSSTF Order: %d", head);

    for(int i = 0; i < n; i++)
    {
        min = 999999;
        pos = -1;

        for(int j = 0; j < n; j++)
        {
            if(!visited[j])
            {
                diff = abs(head - req[j]);

                if(diff < min)
                {
                    min = diff;
                    pos = j;
                }
            }
        }

        visited[pos] = 1;
        total += abs(head - req[pos]);
        head = req[pos];

        printf(" -> %d", head);
    }

    printf("\nTotal Head Movement (SSTF) = %d\n", total);
}

void SCAN(int req[], int n, int head, int size)
{
    int a[100], total = 0, temp;

    for(int i = 0; i < n; i++)
        a[i] = req[i];

    a[n] = head;
    n++;

    for(int i = 0; i < n-1; i++)
    {
        for(int j = 0; j < n-i-1; j++)
        {
            if(a[j] > a[j+1])
            {
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }

    int index = 0;

    while(a[index] != head)
        index++;

    printf("\nSCAN Order: %d", head);

    for(int i = index+1; i < n; i++)
    {
        total += abs(head - a[i]);
        head = a[i];

        printf(" -> %d", head);
    }

    if(head != size-1)
    {
        total += abs(head - (size-1));
        head = size-1;

        printf(" -> %d", head);
    }

    for(int i = index-1; i >= 0; i--)
    {
        total += abs(head - a[i]);
        head = a[i];

        printf(" -> %d", head);
    }

    printf("\nTotal Head Movement (SCAN) = %d\n", total);
}

void CLOOK(int req[], int n, int head)
{
    int a[100], total = 0, temp;
    int index = 0;

    for(int i = 0; i < n; i++)
        a[i] = req[i];

    for(int i = 0; i < n-1; i++)
    {
        for(int j = 0; j < n-i-1; j++)
        {
            if(a[j] > a[j+1])
            {
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }

    while(index < n && a[index] < head)
        index++;

    printf("\nC-LOOK Order: %d", head);

    for(int i = index; i < n; i++)
    {
        total += abs(head - a[i]);
        head = a[i];

        printf(" -> %d", head);
    }

    if(index > 0)
    {
        total += abs(head - a[0]);
        head = a[0];

        printf(" -> %d", head);

        for(int i = 1; i < index; i++)
        {
            total += abs(head - a[i]);
            head = a[i];

            printf(" -> %d", head);
        }
    }

    printf("\nTotal Head Movement (C-LOOK) = %d\n", total);
}

int main()
{
    int req[100], n, head, size;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    if(n < 1 || n > 99)
        return 1;

    printf("Enter request queue: ");

    for(int i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter total cylinders: ");
    scanf("%d", &size);

    if(size < 1 || head < 0 || head >= size)
        return 1;

    for(int i = 0; i < n; i++)
    {
        if(req[i] < 0 || req[i] >= size)
            return 1;
    }

    SSTF(req, n, head);
    SCAN(req, n, head, size);
    CLOOK(req, n, head);

    return 0;
}
