#include <stdio.h>
#include <stdbool.h>

#define P 5 // Number of processes
#define R 3 // Number of resources

// Function to find the need of each process
void calculateNeed(int need[P][R], int maxm[P][R], int allot[P][R]) {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = maxm[i][j] - allot[i][j];
        }
    }
}

// Function to check if the request can be granted
bool requestResources(int pid, int request[], int allot[P][R], int maxm[P][R], int avail[], int need[P][R]) {
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
void releaseResources(int pid, int allot[P][R], int avail[], int R) {
    for (int i = 0; i < R; i++) {
        avail[i] += allot[pid][i];
        allot[pid][i] = 0;
    }
}

// Main function to demonstrate resource request algorithm
int main() {
    int maxm[P][R] = { {7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 1, 1}, {0, 0, 2} };
    int allot[P][R] = { {0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2} };
    int avail[R] = {3, 3, 2}; // Available resources

    // Calculate the need matrix
    int need[P][R];
    calculateNeed(need, maxm, allot);

    // Example resource request by process P1
    int pid = 1; // Process ID requesting resources
    int request[] = {1, 0, 2}; // Requesting resources

    if (requestResources(pid, request, allot, maxm, avail, need)) {
        printf("Resource allocation successful.\n");
        
        // Simulate process completion and release resources
        releaseResources(pid, allot, avail, R);
        printf("Resources released after process completion.\n");
    } else {
        printf("Resource allocation failed.\n");
    }

    return 0;
}
