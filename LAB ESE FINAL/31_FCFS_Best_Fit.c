
// FCFS 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_REQUESTS 100

void fcfs(int requests[], int n, int start)
{
    int total_head_movement = 0;
    int current = start;
    printf("FCFS Scheduling: %d", current); // Start position

    for (int i = 0; i < n; i++)
    {
        total_head_movement += abs(current - requests[i]);
        current = requests[i];
        printf(" -> %d", current); // Append move
    }

    printf("\nTotal Head Movement: %d\n", total_head_movement);
}

int main()
{
    int requests[MAX_REQUESTS], n, start, total_tracks;

    printf("Enter the number of requests: ");
    scanf("%d", &n);
    printf("Enter the requests: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &requests[i]);
    printf("Enter the starting position of the head: ");
    scanf("%d", &start);
    printf("Enter the total number of tracks: ");
    scanf("%d", &total_tracks);

    printf("\n");
    fcfs(requests, n, start);

    return 0;
}

// Best Fit in C

#include <stdio.h>

int main() {
    static int block_arr[10], file_arr[10];
    int fragments[10], blocks[10], Process[10];
    int m, n, number_of_blocks, number_of_process;

    printf("\nEnter the Total Number of Blocks:\t");
    scanf("%d", &number_of_blocks);
    printf("Enter the Total Number of Processes:\t");
    scanf("%d", &number_of_process);

    printf("\nEnter the Size of the Blocks:\n");
    for (m = 0; m < number_of_blocks; m++) {
        printf("Block No.[%d]:\t", m + 1);
        scanf("%d", &blocks[m]);
        block_arr[m] = 0; 
    }

    printf("\nEnter the Size of the Processes:\n");
    for (m = 0; m < number_of_process; m++) {
        printf("Process No.[%d]:\t", m + 1);
        scanf("%d", &Process[m]);
        file_arr[m] = -1; 
    }

    for (m = 0; m < number_of_process; m++) {
        int best_fit_index = -1; 
        int min_fragment = 9999; 

        for (n = 0; n < number_of_blocks; n++) {
            if (block_arr[n] != 1) { // Check if block is free
                int temp_fragment = blocks[n] - Process[m]; 
                if (temp_fragment >= 0 && temp_fragment < min_fragment) { 
                    best_fit_index = n; 
                    min_fragment = temp_fragment; 
                }
            }
        }

        if (best_fit_index != -1) {
            file_arr[m] = best_fit_index; 
            fragments[m] = min_fragment; 
            block_arr[best_fit_index] = 1; 
        } else {
            fragments[m] = -1; // No allocation possible, set fragment to -1
        }
    }

    printf("\nProcess Number\tBlock Number\tProcess Size\tBlock Size\tFragment");
    for (m = 0; m < number_of_process; m++) {
        printf("\n%d\t\t", m + 1); 
        
        if (file_arr[m] != -1) { 
            printf("%d\t\t%d\t\t%d\t\t%d", 
                   file_arr[m] + 1, 
                   Process[m], 
                   blocks[file_arr[m]], 
                   fragments[m]);
        } else {
            printf("-\t\t%d\t\t-\t\t-", Process[m]); // Indicate not allocated
        }
    }
    
    printf("\n");
    return 0;
}