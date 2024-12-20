#include <stdio.h>
int main()
{
    int i, j, n, a[50], frame[10], no, k, avail, count = 0;
    printf("\nENTER THE NUMBER OF PAGES: ");
    scanf("%d", &n);
    printf("\nENTER THE PAGE NUMBER: ");
    for (i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    printf("\nENTER THE NUMBER OF FRAMES:");
    scanf("%d", &no);
    for (i = 0; i < no; i++)
        frame[i] = -1;
    j = 0;
    printf("Ref String\t Page Frames\n");
    for (i = 1; i <= n; i++)
    {
        printf("%d\t\t", a[i]);
        avail = 0;
        for (k = 0; k < no; k++)
            if (frame[k] == a[i])
                avail = 1;
        if (avail == 0)
        {
            frame[j] = a[i];
            j = (j + 1) % no;
            count++;
            for (k = 0; k < no; k++)
                printf("%d\t", frame[k]);
        }
        printf("\n");
    }
    printf("\nTotal Page Fault: %d", count);
    return 0;
}

// https://meansofmine.blogspot.com/2011/04/c-program-to-implement-fifo-page.html