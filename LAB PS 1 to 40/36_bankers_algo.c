#include <stdio.h>

int main() {
    int process, resource, i, j, count1 = 0, canProceed;
    
    printf("Enter number of processes: ");
    scanf("%d", &process);
    printf("Enter number of Resources: ");
    scanf("%d", &resource);

    int avail[resource], max[process][resource], allot[process][resource], need[process][resource], completed[process];

    for (i = 0; i < process; i++) completed[i] = 0;

    printf("Enter available resource instances: ");
    for (i = 0; i < resource; i++) scanf("%d", &avail[i]);

    printf("\nEnter max needs matrix:\n");
    for (i = 0; i < process; i++) {
        printf("For P[%d]: ", i);
        for (j = 0; j < resource; j++) scanf("%d", &max[i][j]);
    }

    printf("\nEnter allocated matrix:\n");
    for (i = 0; i < process; i++) {
        printf("For P[%d]: ", i);
        for (j = 0; j < resource; j++) {
            scanf("%d", &allot[i][j]);
            need[i][j] = max[i][j] - allot[i][j]; 
        }
    }

    printf("\nSafe Sequence is: ");
    while (count1 < process) {
        int count2 = count1;
        for (i = 0; i < process; i++) {
            if (!completed[i]) { 
                canProceed = 1;
                for (j = 0; j < resource; j++) {
                    if (need[i][j] > avail[j]) {
                        canProceed= 0;
                        break;
                    }
                }
                if (canProceed) { 
                    printf("P[%d] ", i);
                    completed[i] = 1; 
                    for (j = 0; j < resource; j++) avail[j] += allot[i][j]; 
                    count1++;
                }
            }
        }
        if (count1 == count2) {
            printf("\nDeadlock Occurred\n");
            return 0;
        }
    }

    printf("\nSystem is in a safe state.\n");
    return 0;
}
