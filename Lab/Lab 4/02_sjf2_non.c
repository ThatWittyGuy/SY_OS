#include <stdio.h>

void printGanttChart(int p[], int n, int bt[]) {
    printf("\n\nGantt Chart:\n");
    printf("|\t");
    // IDs in the Gantt chart
    for (int i = 0; i < n; i++) {
        printf("P%d\t|", p[i]);
    }
    printf("\n");

    // Time intervals
    int time = 0;
    printf("%d\t", time);
    for (int i = 0; i < n; i++) {
        time += bt[i];
        printf("%*d\t", (int)(4 * (i + 1) - 2), time);
    }
    printf("\n");
}

int main() {
    int bt[20], p[20], wt[20], tat[20], i, j, n, total = 0, totalT = 0, pos, temp;
    float avg_wt, avg_tat;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Burst Time:\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &bt[i]);
        p[i] = i + 1; 
    }

    // Sorting of burst times (SJF logic)
    for (i = 0; i < n; i++) {
        pos = i;
        for (j = i + 1; j < n; j++) {
            if (bt[j] < bt[pos])
                pos = j;
        }
        // Swap burst times
        temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;
        // Swap process IDs
        temp = p[i];
        p[i] = p[pos];
        p[pos] = temp;
    }

    wt[0] = 0; 

    // Waiting time of all the processes
    for (i = 1; i < n; i++) {
        wt[i] = 0;
        for (j = 0; j < i; j++)
            wt[i] += bt[j]; 

        total += wt[i]; 
    }
    avg_wt = (float)total / n;
    printf("\nProcess\t Burst Time \tWaiting Time\tTurnaround Time");
    for (i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i]; // Turnaround time
        totalT += tat[i]; // Total turnaround time
        printf("\nP%d\t\t %d\t\t %d\t\t\t%d", p[i], bt[i], wt[i], tat[i]);
    }
    avg_tat = (float)totalT / n;
    printf("\n\nAverage Waiting Time = %f", avg_wt);
    printf("\nAverage Turnaround Time = %f", avg_tat);
    printGanttChart(p, n, bt);
    return 0;
}
