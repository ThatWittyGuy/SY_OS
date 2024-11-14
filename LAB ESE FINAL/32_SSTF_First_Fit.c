#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_REQUESTS 100

void sstf(int requests[], int n, int start)
{
    bool visited[MAX_REQUESTS] = {false};
    int total_head_movement = 0, current = start;
    printf("SSTF Scheduling: %d", current); // Start position

    for (int i = 0; i < n; i++)
    {
        int min_distance = 1000, min_index = -1;
        for (int j = 0; j < n; j++)
        {
            if (!visited[j])
            {
                int distance = abs(current - requests[j]);
                if (distance < min_distance)
                {
                    min_distance = distance;
                    min_index = j;
                }
            }
        }
        visited[min_index] = true;
        total_head_movement += min_distance;
        current = requests[min_index];
        printf(" -> %d", current);
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
    sstf(requests, n, start);

    return 0;
}

// First Fit in C

#include <stdio.h>

int main() {
    static int block_arr[10], file_arr[10];
    int fragments[10], blocks[10], files[10];
    int m, n, number_of_blocks, number_of_files, temp;

    printf("\nEnter the Total Number of Blocks:\t");
    scanf("%d", &number_of_blocks);
    printf("Enter the Total Number of Files:\t");
    scanf("%d", &number_of_files);

    printf("\nEnter the Size of the Blocks:\n");
    for (m = 0; m < number_of_blocks; m++) {
        printf("Block No.[%d]:\t", m + 1);
        scanf("%d", &blocks[m]);
        block_arr[m] = 0; 
    }

    printf("\nEnter the Size of the Files:\n");
    for (m = 0; m < number_of_files; m++) {
        printf("File No.[%d]:\t", m + 1);
        scanf("%d", &files[m]);
        file_arr[m] = -1; 
    }

    for (m = 0; m < number_of_files; m++) {
        temp = -1; 
        for (n = 0; n < number_of_blocks; n++) {
            if (block_arr[n] != 1) { 
                temp = blocks[n] - files[m]; 
                if (temp >= 0) { 
                    file_arr[m] = n; 
                    fragments[m] = temp; 
                    block_arr[n] = 1; 
                    break;
                }
            }
        }
        if (file_arr[m] == -1) {
            fragments[m] = -1; // No allocation possible, set fragment to -1
        }
    }

    printf("\nFile Number\tBlock Number\tFile Size\tBlock Size\tFragment");
    for (m = 0; m < number_of_files; m++) {
        printf("\n%d\t\t", m + 1); 
        
        if (file_arr[m] != -1) { 
            printf("%d\t\t%d\t\t%d\t\t%d", 
                   file_arr[m] + 1, 
                   files[m], 
                   blocks[file_arr[m]], 
                   fragments[m]);
        } else {
            printf("-\t\t%d\t\t-\t\t-", files[m]); // Indicate not allocated
        }
    }
    
    printf("\n");
    return 0;
}

