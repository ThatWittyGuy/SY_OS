#include <stdio.h>

// Function to swap two variables
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to print the Gantt chart
void printGanttChart(int index[], int n, int b[]) {
    printf("\nGantt Chart:\n");
    printf("|\t");

    // Print process IDs in the Gantt chart
    for (int i = 0; i < n; i++) {
        printf("P%d\t|", index[i]);
    }
    printf("\n");

    // Print the time intervals
    int t = 0;
    for (int i = 0; i < n; i++) {
        t += b[i];
        printf("%d\t", t);
    }
    printf("\n");
}

int main() {
    int n;

    printf("Enter Number of Processes: ");
    scanf("%d", &n);

    // Arrays for burst time, priority, and process IDs
    int b[n], p[n], index[n];

    // Input burst time and priority for each process
    for (int i = 0; i < n; i++) {
        printf("Enter Burst Time and Priority Value for Process %d: ", i + 1);
        scanf("%d %d", &b[i], &p[i]);
        index[i] = i + 1; // Store process IDs
    }

    // Sort processes based on priority (higher priority first)
    for (int i = 0; i < n; i++) {
        int a = p[i], m = i;

        // Finding the highest priority element and placing it at its desired position
        for (int j = i; j < n; j++) {
            if (p[j] < a) {
                a = p[j];
                m = j;
            }
        }

        // Swapping processes
        swap(&p[i], &p[m]);
        swap(&b[i], &b[m]);
        swap(&index[i], &index[m]);
    }

    // T stores the starting time of the process
    int t = 0;

    // Printing scheduled process execution order
    printf("\nOrder of Process Execution:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d is executed from %d to %d\n", index[i], t, t + b[i]);
        t += b[i];
    }

    // Printing process details
    printf("\nProcess Id\tBurst Time\tWait Time\tTurnaround Time\n");
    int wait_time = 0;
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\n", index[i], b[i], wait_time, wait_time + b[i]);
        wait_time += b[i];
    }

    // Print the Gantt chart
    printGanttChart(index, n, b);

    return 0;
}
