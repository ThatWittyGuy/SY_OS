#include <stdio.h>

int main() {
    int i, j, n, a[50], frame[10], no, k, count = 0, pos, flag1;
    int time[10]; // Array to track the last used time of pages

    printf("\nENTER THE NUMBER OF PAGES: ");
    scanf("%d", &n);
    
    printf("\nENTER THE PAGE NUMBER: ");
    for (i = 0; i < n; i++) 
        scanf("%d", &a[i]);
    
    printf("\nENTER THE NUMBER OF FRAMES: ");
    scanf("%d", &no);
    
    for (i = 0; i < no; i++)
        frame[i] = -1; // Initialize frames to -1

    // Initialize time array
    for (i = 0; i < no; i++)
        time[i] = 0;

    printf("Ref String\t Page Frames\n");
    
    for (i = 0; i < n; i++) {
        printf("%d\t\t", a[i]);
        flag1 = 0;

        // Check if page is already in the frame
        for (k = 0; k < no; k++) {
            if (frame[k] == a[i]) {
                flag1 = 1; // Page hit
                time[k] = 0; // Reset the time for this page
                break;
            }
        }
        
        // If page not found in frame (page fault)
        if (flag1 == 0) {
            // Check for empty frames
            for (k = 0; k < no; k++) {
                if (frame[k] == -1) {
                    frame[k] = a[i]; // Place page in empty frame
                    time[k] = 0; // Initialize time for the new page
                    flag1 = 1; // Mark that we placed the page
                    break;
                }
            }
            
            // If no empty frame, find the MRU page to replace
            if (flag1 == 0) {
                pos = 0; // Start with the first frame
                for (k = 1; k < no; k++) {
                    if (time[k] < time[pos]) {
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
    printf("\nTotal Hits: %d", n - count); 
    return 0;
}
