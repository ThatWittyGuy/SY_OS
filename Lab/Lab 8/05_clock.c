#include <stdio.h>

#define MAX_FRAMES 10

int main() {
    int i, j, n, pages[50], frames[MAX_FRAMES], referenceBit[MAX_FRAMES];
    int numFrames, pageFaults = 0, pointer = 0;

    printf("\nENTER THE NUMBER OF PAGES: ");
    scanf("%d", &n);

    printf("\nENTER THE PAGE NUMBER: ");
    for (i = 0; i < n; i++) 
        scanf("%d", &pages[i]);

    printf("\nENTER THE NUMBER OF FRAMES: ");
    scanf("%d", &numFrames);

    for (i = 0; i < numFrames; i++) {
        frames[i] = -1;  // Initialize frames
        referenceBit[i] = 0;  // Initialize reference bits
    }

    printf("Ref String\t Page Frames\n");

    for (i = 0; i < n; i++) {
        printf("%d\t\t", pages[i]);
        int found = 0;

        // Check if page is already in frames
        for (j = 0; j < numFrames; j++) {
            if (frames[j] == pages[i]) {
                found = 1;  // Page hit
                referenceBit[j] = 1;  // Set reference bit
                break;
            }
        }

        if (!found) {  // Page fault
            while (1) {
                if (referenceBit[pointer] == 0) {
                    // Replace page
                    frames[pointer] = pages[i];
                    referenceBit[pointer] = 0;  // Reset reference bit
                    pointer = (pointer + 1) % numFrames;  // Move pointer
                    pageFaults++;
                    break;
                } else {
                    // Give second chance
                    referenceBit[pointer] = 0;  // Reset reference bit
                    pointer = (pointer + 1) % numFrames;  // Move pointer
                }
            }
        }

        // Print the frames
        for (j = 0; j < numFrames; j++) {
            if (frames[j] != -1) {
                printf("%d\t", frames[j]);
            } else {
                printf("-\t");  // Indicate empty frame
            }
        }
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
    return 0;
}
