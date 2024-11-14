// LRU Code 
#include <stdio.h>
int main() {
    int i, j, n, a[50], frame[10], no, k, count = 0, pos, flag1;
    int time[10]; 

    printf("\nENTER THE NUMBER OF PAGES: ");
    scanf("%d", &n);
    
    printf("\nENTER THE PAGE NUMBER: ");
    for (i = 0; i < n; i++) 
        scanf("%d", &a[i]);
    printf("\nENTER THE NUMBER OF FRAMES: ");
    scanf("%d", &no);
    for (i = 0; i < no; i++)
        frame[i] = -1; 

    for (i = 0; i < no; i++)
        time[i] = 0;

    printf("Ref String\t Page Frames\n");
    
    for (i = 0; i < n; i++) {
        printf("%d\t\t", a[i]);
        flag1 = 0;

        for (k = 0; k < no; k++) {
            if (frame[k] == a[i]) {
                flag1 = 1; 
                time[k] = 0; 
                break;
            }
        }
        
        if (flag1 == 0) {
            for (k = 0; k < no; k++) {
                if (frame[k] == -1) {
                    frame[k] = a[i]; 
                    time[k] = 0; 
                    flag1 = 1; 
                    break;
                }
            }
            if (flag1 == 0) {
                pos = 0; 
                for (k = 1; k < no; k++) {
                    if (time[k] > time[pos]) {
                        pos = k; 
                    }
                }
                frame[pos] = a[i]; 
                time[pos] = 0; 
            }
            count++; 
            for (k = 0; k < no; k++)
                printf("%d\t", frame[k]);
        } else {
            for (k = 0; k < no; k++)
                printf("\t"); 
        }

        for (k = 0; k < no; k++) {
            if (frame[k] != -1) {
                time[k]++; 
            }
        }
        printf("\n");
    }
    printf("\nTotal Page Fault: %d", count);
    return 0;
}


// Optimal Code

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
