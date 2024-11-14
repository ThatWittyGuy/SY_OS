#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 9999

struct proc {
    int no, at, bt, rt, ct, wt, tat, pri, temp;
};

struct proc read(int i) {
    struct proc p;
    printf("\nProcess No: %d\n", i);
    p.no = i;
    printf("Enter Arrival Time: ");
    scanf("%d", &p.at);
    printf("Enter Burst Time: ");
    scanf("%d", &p.bt);
    p.rt = p.bt;
    printf("Enter Priority: ");
    scanf("%d", &p.pri);
    p.temp = p.pri;
    return p;
}

// Function to print the Gantt chart in the desired format
void printGanttChart(struct proc p[], int n) {
    printf("\nGantt Chart:\n");
    // Print top border
    for (int i = 0; i < n; ++i) {
        printf("+-------");
    }
    printf("+\n|");

    // Print process IDs in the Gantt chart
    for (int i = 0; i < n; ++i) {
        printf(" P%d     |", p[i].no);
    }
    printf("\n ");

    // Print the separator line
    for (int i = 0; i < n; ++i) {
        printf("+-------");
    }
    printf("+\n0");

    // Print the times in the Gantt chart
    int currentTime = 0;
    for (int i = 0; i < n; ++i) {
        currentTime += p[i].bt;
        printf("%8d", currentTime);
    }
    printf("\n");
}

int main() {
    int i, n, c, remaining, min_val, min_index;
    struct proc p[10], temp;
    float avgtat = 0, avgwt = 0;

    printf("<--Smallest Priority First Scheduling Algorithm (Preemptive)-->\n");
    printf("Enter Number of Processes: ");
    scanf("%d", &n);

    // Read processes
    for (i = 0; i < n; i++) {
        p[i] = read(i + 1);
    }

    remaining = n;

    // Sort by Arrival Time
    for (i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // First process selection
    min_val = p[0].temp;
    min_index = 0;

    // Select the first process to execute
    for (int j = 0; j < n && p[j].at <= p[0].at; j++) {
        if (p[j].temp < min_val) {
            min_val = p[j].temp;
            min_index = j;
        }
    }

    i = min_index;
    c = p[i].ct = p[i].at + 1;
    p[i].rt--;

    // List of processes for Gantt chart
    struct proc ganttChart[n];
    int ganttCount = 0;

    // Start preemptive execution of processes
    ganttChart[ganttCount++] = p[i];  // Store the first process in the Gantt chart

    while (remaining > 0) {
        min_val = p[0].temp;
        min_index = 0;

        for (int j = 0; j < n && p[j].at <= c; j++) {
            if (p[j].temp < min_val) {
                min_val = p[j].temp;
                min_index = j;
            }
        }

        i = min_index;
        p[i].ct = c = c + 1;
        p[i].rt--;

        // Add the process to the Gantt chart
        ganttChart[ganttCount++] = p[i];

        if (p[i].rt == 0) {
            p[i].temp = MAX;
            remaining--;
        }
    }

    // Print the Gantt chart
    printGanttChart(ganttChart, ganttCount);

    printf("\nProcessNo\tAT\tBT\tPri\tCT\tTAT\tWT\n");
    // Calculate TAT and WT
    for (i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        avgtat += p[i].tat;
        p[i].wt = p[i].tat - p[i].bt;
        avgwt += p[i].wt;

        printf("P%d\t\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].no, p[i].at, p[i].bt, p[i].pri, p[i].ct, p[i].tat, p[i].wt);
    }

    avgtat /= n;
    avgwt /= n;

    printf("\nAverage TurnAroundTime = %f\nAverage WaitingTime = %f\n", avgtat, avgwt);
    return 0;
}
