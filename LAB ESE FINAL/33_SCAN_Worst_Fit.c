#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_REQUESTS 100

void bubble_sort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

void print_moves(int start, int requests[], int n, bool visited[], int *total_head_movement)
{
    int current = start;
    printf("%d", current); // Start position

    for (int i = 0; i < n; i++)
    {
        if (visited[i])
            continue; // Skip if already visited
        *total_head_movement += abs(current - requests[i]);
        current = requests[i];
        printf(" -> %d", current);
    }
}

void scan(int requests[], int n, int start, int total_tracks)
{
    int total_head_movement = 0;
    int sorted_requests[MAX_REQUESTS];
    for (int i = 0; i < n; i++)
        sorted_requests[i] = requests[i];
    bubble_sort(sorted_requests, n);

    printf("SCAN Scheduling: %d", start); // Start position
    int idx = 0;
    while (idx < n && sorted_requests[idx] < start)
        idx++;

    for (int i = idx; i < n; i++)
    {
        total_head_movement += abs(start - sorted_requests[i]);
        start = sorted_requests[i];
        printf(" -> %d", start);
    }

    if (start != total_tracks - 1)
    {
        total_head_movement += abs(start - (total_tracks - 1));
        start = total_tracks - 1;
        printf(" -> %d", start);
    }

    for (int i = idx - 1; i >= 0; i--)
    {
        total_head_movement += abs(start - sorted_requests[i]);
        start = sorted_requests[i];
        printf(" -> %d", start);
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
    scan(requests, n, start, total_tracks);
    printf("\n");
    cscan(requests, n, start, total_tracks);

    return 0;
}

// WORST FIT in C

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
        int worst_fit_index = -1; // To track the index of the worst fit block
        int max_fragment = -1; 

        for (n = 0; n < number_of_blocks; n++) {
            if (block_arr[n] != 1) { 
                int temp_fragment = blocks[n] - Process[m]; 
                if (temp_fragment >= 0 && temp_fragment > max_fragment) { 
                    worst_fit_index = n; 
                    max_fragment = temp_fragment; 
                }
            }
        }

        if (worst_fit_index != -1) {
            file_arr[m] = worst_fit_index; 
            fragments[m] = max_fragment; 
            block_arr[worst_fit_index] = 1; 
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
