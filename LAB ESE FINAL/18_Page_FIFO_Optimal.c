// FIFO CodePage Replacement in C
#include <stdio.h>
int main()
{
    int i, j, n, a[50], frame[10], no, k, avail, count = 0;
    printf("\n ENTER THE NUMBER OF PAGES:\n");
    scanf("%d", &n);
    printf("\n ENTER THE PAGE NUMBER :\n");
    for (i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    printf("\n ENTER THE NUMBER OF FRAMES :");
    scanf("%d", &no);
    for (i = 0; i < no; i++)
        frame[i] = -1;
    j = 0;
    printf("\tref string\t page frames\n");
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
    printf("Page Fault Is %d", count);
    return 0;
}

// Optimal Code:

#include <stdio.h>

int main() {
    int i, j, n, a[50], frame[10], no, k, count = 0, pos, flag1, flag2;

    printf("\nENTER THE NUMBER OF PAGES: ");
    scanf("%d", &n);
    
    printf("\nENTER THE PAGE NUMBER: ");
    for (i = 0; i < n; i++) 
        scanf("%d", &a[i]);
    
    printf("\nENTER THE NUMBER OF FRAMES: ");
    scanf("%d", &no);
    
    for (i = 0; i < no; i++)
        frame[i] = -1; 

    printf("Ref String\t Page Frames\n");
    
    for (i = 0; i < n; i++) {
        printf("%d\t\t", a[i]);
        flag1 = flag2 = 0;

        for (k = 0; k < no; k++) {
            if (frame[k] == a[i]) {
                flag1 = 1; 
                break;
            }
        }
        
        if (flag1 == 0) {
            for (k = 0; k < no; k++) {
                if (frame[k] == -1) {
                    frame[k] = a[i]; 
                    flag2 = 1; 
                    break;
                }
            }
            
            if (flag2 == 0) {
                pos = -1;
                int farthest = -1;
                for (k = 0; k < no; k++) {
                    int j;
                    for (j = i + 1; j < n; j++) {
                        if (frame[k] == a[j]) {
                            if (j > farthest) {
                                farthest = j; 
                                pos = k; 
                            }
                            break;
                        }
                    }
                    if (j == n) {
                        pos = k; 
                        break;
                    }
                }
                frame[pos] = a[i]; 
            }
            count++; 
            
            for (k = 0; k < no; k++)
                printf("%d\t", frame[k]);
        } else {
            for (k = 0; k < no; k++)
                printf("\t"); 
        }
        
        printf("\n");
    }
    
    printf("\nTotal Page Fault: %d", count);
    return 0;
}
