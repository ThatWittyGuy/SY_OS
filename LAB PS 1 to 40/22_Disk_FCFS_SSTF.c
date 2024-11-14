#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_REQUESTS 100

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

void sstf(int requests[], int n, int start)
{
    bool visited[MAX_REQUESTS] = {false};
    int total_head_movement = 0, current = start;
    printf("SSTF Scheduling: %d", current); 

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
    fcfs(requests, n, start);
    printf("\n");
    sstf(requests, n, start);
    printf("\n");
    return 0;
}
