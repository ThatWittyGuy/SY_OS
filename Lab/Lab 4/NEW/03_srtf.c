#include <stdio.h>

#define MAX_PROCESSES 20

void printGanttChart(int p[], int n, int completion_time[]) {
    printf("\nGantt Chart:\n");
    printf("|\t");

    // Print process IDs in the Gantt chart
    for (int i = 0; i < n; i++) {
        printf("P%d\t|", p[i]);
    }
    printf("\n");

    // Print the time intervals
    for (int i = 0; i <= n; i++) {
        printf("%d\t", completion_time[i]);
    }
    printf("\n");
}

int main() {
    int bt[MAX_PROCESSES], p[MAX_PROCESSES], rt[MAX_PROCESSES], wt[MAX_PROCESSES], tat[MAX_PROCESSES], arrival_time[MAX_PROCESSES];
    int i, n, total = 0, totalT = 0, complete = 0, time = 0, min_index;
    float avg_wt, avg_tat;

    printf("Enter number of processes (max %d): ", MAX_PROCESSES);
    scanf("%d", &n);

    if (n > MAX_PROCESSES) {
        printf("Number of processes exceeds the maximum allowed.\n");
        return 1;
    }

    printf("\nEnter Arrival Time and Burst Time:\n");
    for (i = 0; i < n; i++) {
        printf("P%d Arrival Time: ", i + 1);
        scanf("%d", &arrival_time[i]);
        printf("P%d Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
        p[i] = i + 1; // Store process IDs
        rt[i] = bt[i]; // Remaining time initialized to burst time
    }

    printf("\nProcess\t Burst Time\t Arrival Time\t Waiting Time\t Turnaround Time\n");

    int completion_time[2 * MAX_PROCESSES]; // Adjusted size
    int index = 0;

    while (complete < n) {
        // Find the process with the minimum remaining time
        min_index = -1;
        int min_remaining_time = 999; // A large number

        for (i = 0; i < n; i++) {
            if (arrival_time[i] <= time && rt[i] > 0 && rt[i] < min_remaining_time) {
                min_remaining_time = rt[i];
                min_index = i;
            }
        }

        if (min_index != -1) {
            if (rt[min_index] == bt[min_index]) {
                completion_time[index++] = time; // Start time
            }

            rt[min_index]--;
            time++;

            if (rt[min_index] == 0) {
                completion_time[index++] = time; // End time
                complete++;
                tat[min_index] = time - arrival_time[min_index]; // Turnaround time
                wt[min_index] = tat[min_index] - bt[min_index]; // Waiting time
                total += wt[min_index];
                totalT += tat[min_index];

                printf("P%d\t\t %d\t\t %d\t\t %d\t\t\t%d\n", p[min_index], bt[min_index], arrival_time[min_index], wt[min_index], tat[min_index]);
            }
        } else {
            time++;
        }
    }

    // Average waiting time and turnaround time
    avg_wt = (float)total / n;
    avg_tat = (float)totalT / n;

    printf("\nAverage Waiting Time = %.2f", avg_wt);
    printf("\nAverage Turnaround Time = %.2f", avg_tat);

    // Print the Gantt chart
    printGanttChart(p, n, completion_time);

    return 0;
}
