// FCFS Scheduling
#include <stdio.h>
void printGanttChart(int pid[], int bt[], int n) {
    printf("\n\nGantt Chart:\n");
    printf("|\t");
    
    // IDs
    for (int i = 0; i < n; i++) {
        printf("P%d\t|", pid[i]);
    }
    printf("\n");

    // Time intervals
    int time = 0;
    printf("%d\t", time);
    for (int i = 0; i < n; i++) {
        time += bt[i];
        printf("\t%d\t", time);
    }
    printf("\n");
}

int main()
{
    int pid[15];
    int bt[15];
    int n;
    int i, wt[n];    
    float twt=0.0, tat= 0.0;    
    float att,awt;

    printf("Enter the number of processes: ");
    scanf("%d",&n);
    printf("Enter process id of all the processes: ");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&pid[i]);
    }
    printf("Enter burst time of all the processes: ");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&bt[i]);
    }

    // waiting time of each process
    wt[0]=0;
    for(i=1; i<n; i++)
    {
        wt[i]= bt[i-1]+ wt[i-1];
    }
    printf("Process ID     Burst Time     Waiting Time     TurnAround Time\n");
    for(i=0; i<n; i++)
    {  
        printf("%d\t\t", pid[i]);
        printf("%d\t\t", bt[i]);
        printf("%d\t\t", wt[i]);
        printf("%d\t\t", bt[i]+wt[i]);//turnaround time
        printf("\n");
        twt += wt[i]; //total waiting time
        tat += (wt[i]+bt[i]);//total turnaround time
    }
    awt = twt/n;
    att = tat/n;
    printf("Avg. waiting time= %f\n",awt);
    printf("Avg. turnaround time= %f",att);

    printGanttChart(pid, bt, n);
    return 0;
}