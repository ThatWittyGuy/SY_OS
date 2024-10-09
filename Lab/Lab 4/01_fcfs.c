// Code to FCFS scheduling 
#include <stdio.h>

void printGanttChart(int pid[], int bt[], int n) {
    printf("\nGantt Chart:\n");
    printf("|\t");
    
    // Print process IDs in the Gantt chart
    for (int i = 0; i < n; i++) {
        printf("P%d\t|", pid[i]);
    }
    printf("\n");

    // Print the time intervals
    int time = 0;
    printf("%d\t", time);
    for (int i = 0; i < n; i++) {
        time += bt[i];
        printf("\t%d\t", time);
    }
    printf("\n");
}

int main() {
    int pid[15];
    int bt[15];
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter process id of all the processes: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pid[i]);
    }

    printf("Enter burst time of all the processes: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
    }

    int i, wt[n];
    wt[0] = 0;

    // For calculating waiting time of each process
    for (i = 1; i < n; i++) {
        wt[i] = bt[i - 1] + wt[i - 1];
    }

    printf("Process ID     Burst Time     Waiting Time     TurnAround Time\n");
    float twt = 0.0;
    float tat = 0.0;

    for (i = 0; i < n; i++) {
        printf("%d\t\t", pid[i]);
        printf("%d\t\t", bt[i]);
        printf("%d\t\t", wt[i]);

        // Calculating and printing turnaround time of each process
        printf("%d\t\t", bt[i] + wt[i]);
        printf("\n");

        // For calculating total waiting time
        twt += wt[i];

        // For calculating total turnaround time
        tat += (wt[i] + bt[i]);
    }

    float att, awt;

    // For calculating average waiting time
    awt = twt / n;

    // For calculating average turnaround time
    att = tat / n;

    printf("Avg. waiting time= %f\n", awt);
    printf("Avg. turnaround time= %f\n", att);

    // Print the Gantt chart
    printGanttChart(pid, bt, n);

    return 0;
}
