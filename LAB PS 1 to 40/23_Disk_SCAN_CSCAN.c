#include <stdio.h>
#include <stdlib.h>

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

    printf("%s Scheduling: %d", (scan_mode == 0 ? "SCAN" : "C-SCAN"), start);

    // Move to the right (or to the end in C-SCAN)
    for (int i = idx; i < n; i++) {
        total_head_movement += abs(start - sorted_requests[i]);
        start = sorted_requests[i];
        printf(" -> %d", start);
    }

    if (scan_mode == 0 && start != total_tracks - 1) {
        // SCAN: move to the last track and reverse direction
        total_head_movement += abs(start - (total_tracks - 1));
        start = total_tracks - 1;
        printf(" -> %d", start);
    } else if (scan_mode == 1 && start != total_tracks - 1) {
        // C-SCAN: jump to the first track after reaching the last track
        total_head_movement += abs(start - (total_tracks - 1));
        start = 0;
        total_head_movement += (total_tracks - 1);
        printf(" -> %d", start);
    }

    // Move to the left (or to the beginning in C-SCAN)
    for (int i = (scan_mode == 0 ? idx - 1 : 0); (scan_mode == 0 ? i >= 0 : i < idx); (scan_mode == 0 ? i-- : i++)) {
        total_head_movement += abs(start - sorted_requests[i]);
        start = sorted_requests[i];
        printf(" -> %d", start);
    }

    printf("\nTotal Head Movement: %d\n", total_head_movement);
}

int main() {
    int requests[MAX_REQUESTS], n, start, total_tracks;

    printf("Enter the number of requests: ");
    scanf("%d", &n);
    printf("Enter the requests: ");
    for (int i = 0; i < n; i++) scanf("%d", &requests[i]);
    printf("Enter the starting position of the head: ");
    scanf("%d", &start);
    printf("Enter the total number of tracks: ");
    scanf("%d", &total_tracks);

    printf("\n");
    calculate_head_movement(requests, n, start, total_tracks, 0);  // SCAN
    printf("\n");
    calculate_head_movement(requests, n, start, total_tracks, 1);  // C-SCAN

    return 0;
}
