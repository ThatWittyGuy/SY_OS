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

void cscan(int requests[], int n, int start, int total_tracks)
{
    int total_head_movement = 0;
    int sorted_requests[MAX_REQUESTS];
    for (int i = 0; i < n; i++)
        sorted_requests[i] = requests[i];
    bubble_sort(sorted_requests, n);

    printf("C-SCAN Scheduling: %d", start); // Start position
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
        start = 0;
        total_head_movement += (total_tracks - 1);
        printf(" -> %d", start);
    }

    for (int i = 0; i < idx; i++)
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
    sstf(requests, n, start);
    printf("\n");
    cscan(requests, n, start, total_tracks);

    return 0;
}