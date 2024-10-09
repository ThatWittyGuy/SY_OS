#include <stdio.h>

#define MAX_PROCESSES 100

void printGanttChart(int processes[], int n, int start_times[], int end_times[]) {
    printf("\nGantt Chart:\n");
    printf("|\t");

    // Print process IDs in the Gantt chart
    for (int i = 0; i < n; i++) {
        printf("P%d\t|", processes[i]);
    }
    printf("\n");

    // Print the time intervals
    for (int i = 0; i <= n; i++) {
        printf("%d\t", end_times[i]);
    }
    printf("\n");
}

int main() {
    int n, i, j;
    int A[MAX_PROCESSES][4]; // [Process ID, Burst Time, Waiting Time, Turnaround Time]
    int arrival_time[MAX_PROCESSES];
    int total_wt = 0, total_tat = 0;
    float avg_wt, avg_tat;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Arrival Time and Burst Time:\n");
    for (i = 0; i < n; i++) {
        printf("P%d Arrival Time: ", i + 1);
        scanf("%d", &arrival_time[i]);
        printf("P%d Burst Time: ", i + 1);
        scanf("%d", &A[i][1]); // Burst Time
        A[i][0] = i + 1; // Process ID
    }

    // Array to keep track of remaining burst times
    int remaining_time[MAX_PROCESSES];
    for (i = 0; i < n; i++) {
        remaining_time[i] = A[i][1];
    }

    int time = 0, completed = 0;
    int start_times[MAX_PROCESSES], end_times[MAX_PROCESSES];

    // Initialize end_times
    end_times[n] = 0;

    // Print table header
    printf("\nProcess\t BT\t AT\t WT\t TAT\n");

    while (completed < n) {
        int smallest = -1;
        int min_burst_time = 9999;

        // Find the process with the smallest burst time that has arrived
        for (i = 0; i < n; i++) {
            if (arrival_time[i] <= time && remaining_time[i] > 0 && remaining_time[i] < min_burst_time) {
                min_burst_time = remaining_time[i];
                smallest = i;
            }
        }

        if (smallest != -1) {
            start_times[completed] = time;
            time += remaining_time[smallest];
            end_times[completed] = time;

            // Calculate waiting and turnaround times
            int wt = start_times[completed] - arrival_time[smallest];
            int tat = end_times[completed] - arrival_time[smallest];
            total_wt += wt;
            total_tat += tat;

            // Print process information
            printf("P%d\t %d\t %d\t %d\t %d\n", A[smallest][0], A[smallest][1], arrival_time[smallest], wt, tat);

            remaining_time[smallest] = 0; // Process completed
            completed++;
        } else {
            time++; // Increment time if no process is available
        }
    }

    avg_wt = (float)total_wt / n;
    avg_tat = (float)total_tat / n;

    printf("\nAverage Waiting Time = %.2f", avg_wt);
    printf("\nAverage Turnaround Time = %.2f", avg_tat);

    // Print the Gantt chart
    printGanttChart(A[0], n, start_times, end_times);

    return 0;
}
