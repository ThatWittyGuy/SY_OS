#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_REQUESTS 100

void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

void calculate_head_movement(int requests[], int n, int start, int total_tracks, int scan_mode) {
    int total_head_movement = 0;
    int sorted_requests[MAX_REQUESTS];
    for (int i = 0; i < n; i++) sorted_requests[i] = requests[i];
    bubble_sort(sorted_requests, n);

    int idx = 0;
    while (idx < n && sorted_requests[idx] < start) idx++;

     printf("SCAN Scheduling: %d", start);

    // Move to the right (or to the end)
    for (int i = idx; i < n; i++) {
        total_head_movement += abs(start - sorted_requests[i]);
        start = sorted_requests[i];
        printf(" -> %d", start);
    }

    // Move to the last track if not already there
    if (start != total_tracks - 1) {
        total_head_movement += abs(start - (total_tracks - 1));
        start = total_tracks - 1;
        printf(" -> %d", start);
    }

    // Move to the left
    for (int i = idx - 1; i >= 0; i--) {
        total_head_movement += abs(start - sorted_requests[i]);
        start = sorted_requests[i];
        printf(" -> %d", start);
    }

    printf("\nTotal Head Movement: %d\n", total_head_movement);
}

void fcfs(int requests[], int n, int start)
{
    int total_head_movement = 0;
    int current = start;
    printf("FCFS Scheduling: %d", current); 

    for (int i = 0; i < n; i++)
    {
        total_head_movement += abs(current - requests[i]);
        current = requests[i];
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
    fcfs(requests, n, start);
    printf("\n");
    calculate_head_movement(requests, n, start, total_tracks, 0);  // SCAN
    return 0;
}
