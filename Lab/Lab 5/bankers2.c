// Resource Request Algorithm

#include <stdio.h>
#include <stdbool.h>

#define MAX_P 10 // Maximum number of processes
#define MAX_R 10 // Maximum number of resources

// Function to find the need of each process
void calculateNeed(int need[MAX_P][MAX_R], int maxm[MAX_P][MAX_R], int allot[MAX_P][MAX_R], int P, int R) {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = maxm[i][j] - allot[i][j];
        }
    }
}

// Function to check if the request can be granted
bool requestResources(int pid, int request[], int allot[MAX_P][MAX_R], int maxm[MAX_P][MAX_R], int avail[], int need[MAX_P][MAX_R], int P, int R) {
    // Check if request is less than need
    for (int i = 0; i < R; i++) {
        if (request[i] > need[pid][i]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return false;
        }
    }

    // Check if request is less than available
    for (int i = 0; i < R; i++) {
        if (request[i] > avail[i]) {
            printf("Resources are not available.\n");
            return false;
        }
    }

    // Pretend to allocate requested resources
    for (int i = 0; i < R; i++) {
        avail[i] -= request[i];
        allot[pid][i] += request[i];
        need[pid][i] -= request[i];
    }

    return true;
}

// Function to release resources after process completion
void releaseResources(int pid, int allot[MAX_P][MAX_R], int avail[], int R) {
    for (int i = 0; i < R; i++) {
        avail[i] += allot[pid][i];
        allot[pid][i] = 0;
    }
}

// Main function to demonstrate resource request algorithm
int main() {
    int P, R;

    // Input number of processes and resources
    printf("Enter the number of processes: ");
    scanf("%d", &P);
    
    printf("Enter the number of resources: ");
    scanf("%d", &R);

    // Declare matrices and arrays
    int maxm[MAX_P][MAX_R], allot[MAX_P][MAX_R], avail[MAX_R], need[MAX_P][MAX_R];

    // Input maximum resource claims for each process
    printf("Enter the maximum resource claims matrix:\n");
    for (int i = 0; i < P; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < R; j++) {
            scanf("%d", &maxm[i][j]);
        }
    }

    // Input currently allocated resources for each process
    printf("Enter the currently allocated resources matrix:\n");
    for (int i = 0; i < P; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < R; j++) {
            scanf("%d", &allot[i][j]);
        }
    }

    // Input available resources
    printf("Enter the available resources vector:\n");
    for (int j = 0; j < R; j++) {
        scanf("%d", &avail[j]);
    }

    // Calculate the need matrix
    calculateNeed(need, maxm, allot, P, R);

    // Example resource request by a user-defined process
    int pid;
    printf("Enter the process ID requesting resources (0 to %d): ", P - 1);
    scanf("%d", &pid);

    int request[MAX_R];
    printf("Enter the resource request vector for Process %d:\n", pid);
    for (int j = 0; j < R; j++) {
        scanf("%d", &request[j]);
    }

    if (requestResources(pid, request, allot, maxm, avail, need, P, R)) {
        printf("Resource allocation successful.\n");

        // Simulate process completion and release resources
        releaseResources(pid, allot, avail, R);
        printf("Resources released after process completion.\n");
        
        // Print updated available resources
        printf("Updated available resources:\n");
        for (int j = 0; j < R; j++) {
            printf("%d ", avail[j]);
        }
        printf("\n");
        
        // Print updated allocation matrix
        printf("Updated allocation matrix:\n");
        for (int i = 0; i < P; i++) {
            printf("Process %d: ", i);
            for (int j = 0; j < R; j++) {
                printf("%d ", allot[i][j]);
            }
            printf("\n");
        }
        
        // Print updated need matrix
        printf("Updated need matrix:\n");
        for (int i = 0; i < P; i++) {
            printf("Process %d: ", i);
            for (int j = 0; j < R; j++) {
                printf("%d ", need[i][j]);
            }
            printf("\n");
        }
        
    } else {
        printf("Resource allocation failed.\n");
    }

    return 0;
}
