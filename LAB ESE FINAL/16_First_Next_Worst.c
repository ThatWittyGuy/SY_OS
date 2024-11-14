// First Fit in C

#include <stdio.h>

int main() {
    static int block_arr[10], file_arr[10];
    int fragments[10], blocks[10], files[10];
    int m, n, number_of_blocks, number_of_files, temp;

    printf("\nEnter the Total Number of Blocks:\t");
    scanf("%d", &number_of_blocks);
    printf("Enter the Total Number of Files:\t");
    scanf("%d", &number_of_files);

    printf("\nEnter the Size of the Blocks:\n");
    for (m = 0; m < number_of_blocks; m++) {
        printf("Block No.[%d]:\t", m + 1);
        scanf("%d", &blocks[m]);
        block_arr[m] = 0; 
    }

    printf("\nEnter the Size of the Files:\n");
    for (m = 0; m < number_of_files; m++) {
        printf("File No.[%d]:\t", m + 1);
        scanf("%d", &files[m]);
        file_arr[m] = -1; 
    }

    for (m = 0; m < number_of_files; m++) {
        temp = -1; 
        for (n = 0; n < number_of_blocks; n++) {
            if (block_arr[n] != 1) { 
                temp = blocks[n] - files[m]; 
                if (temp >= 0) { 
                    file_arr[m] = n; 
                    fragments[m] = temp; 
                    block_arr[n] = 1; 
                    break;
                }
            }
        }
        if (file_arr[m] == -1) {
            fragments[m] = -1; // No allocation possible, set fragment to -1
        }
    }

    printf("\nFile Number\tBlock Number\tFile Size\tBlock Size\tFragment");
    for (m = 0; m < number_of_files; m++) {
        printf("\n%d\t\t", m + 1); 
        
        if (file_arr[m] != -1) { 
            printf("%d\t\t%d\t\t%d\t\t%d", 
                   file_arr[m] + 1, 
                   files[m], 
                   blocks[file_arr[m]], 
                   fragments[m]);
        } else {
            printf("-\t\t%d\t\t-\t\t-", files[m]); // Indicate not allocated
        }
    }
    
    printf("\n");
    return 0;
}

// Next Fit in C

#include <stdio.h>

int main() {
    static int block_arr[10], file_arr[10];
    int fragments[10], blocks[10], Process[10];
    int m, n, number_of_blocks, number_of_process, last_allocated = 0;

    printf("\nEnter the Total Number of Blocks:\t");
    scanf("%d", &number_of_blocks);
    printf("Enter the Total Number of Process:\t");
    scanf("%d", &number_of_process);

    printf("\nEnter the Size of the Blocks:\n");
    for (m = 0; m < number_of_blocks; m++) {
        printf("Block No.[%d]:\t", m + 1);
        scanf("%d", &blocks[m]);
        block_arr[m] = 0; 
    }

    printf("\nEnter the Size of the Process:\n");
    for (m = 0; m < number_of_process; m++) {
        printf("File No.[%d]:\t", m + 1);
        scanf("%d", &Process[m]);
        file_arr[m] = -1; 
    }

    for (m = 0; m < number_of_process; m++) {
        int allocated = 0; // Flag to check if file is allocated
        for (n = last_allocated; n < number_of_blocks; n++) {
            if (block_arr[n] != 1) { 
                int temp = blocks[n] - Process[m]; 
                if (temp >= 0) { 
                    file_arr[m] = n; 
                    fragments[m] = temp; 
                    block_arr[n] = 1; 
                    last_allocated = n; // Update last allocated position
                    allocated = 1; // Mark as allocated
                    break;
                }
            }
        }

        // If not allocated in the first pass, check from the beginning
        if (!allocated) {
            for (n = 0; n < last_allocated; n++) {
                if (block_arr[n] != 1) { 
                    int temp = blocks[n] - Process[m]; 
                    if (temp >= 0) { 
                        file_arr[m] = n; 
                        fragments[m] = temp; 
                        block_arr[n] = 1; 
                        last_allocated = n; // Update last allocated position
                        allocated = 1; // Mark as allocated
                        break;
                    }
                }
            }
        }

        if (file_arr[m] == -1) {
            fragments[m] = -1; // No allocation possible, set fragment to -1
        }
    }

    printf("\nFile Number\tBlock Number\tFile Size\tBlock Size\tFragment");
    for (m = 0; m < number_of_process; m++) {
        printf("\n%d\t\t", m + 1); 
        
        if (file_arr[m] != -1) { 
            printf("%d\t\t%d\t\t%d\t\t%d", 
                   file_arr[m] + 1, 
                   Process[m], 
                   blocks[file_arr[m]], 
                   fragments[m]);
        } else {
            printf("-\t\t%d\t\t-\t\t-", Process[m]); // Indicate not allocated
        }
    }
    
    printf("\n");
    return 0;
}

// Worst Fit in C

#include <stdio.h>

int main() {
    static int block_arr[10], file_arr[10];
    int fragments[10], blocks[10], Process[10];
    int m, n, number_of_blocks, number_of_process;

    printf("\nEnter the Total Number of Blocks:\t");
    scanf("%d", &number_of_blocks);
    printf("Enter the Total Number of Processes:\t");
    scanf("%d", &number_of_process);

    printf("\nEnter the Size of the Blocks:\n");
    for (m = 0; m < number_of_blocks; m++) {
        printf("Block No.[%d]:\t", m + 1);
        scanf("%d", &blocks[m]);
        block_arr[m] = 0; 
    }

    printf("\nEnter the Size of the Processes:\n");
    for (m = 0; m < number_of_process; m++) {
        printf("Process No.[%d]:\t", m + 1);
        scanf("%d", &Process[m]);
        file_arr[m] = -1; 
    }

    for (m = 0; m < number_of_process; m++) {
        int worst_fit_index = -1; // To track the index of the worst fit block
        int max_fragment = -1; 

        for (n = 0; n < number_of_blocks; n++) {
            if (block_arr[n] != 1) { 
                int temp_fragment = blocks[n] - Process[m]; 
                if (temp_fragment >= 0 && temp_fragment > max_fragment) { 
                    worst_fit_index = n; 
                    max_fragment = temp_fragment; 
                }
            }
        }

        if (worst_fit_index != -1) {
            file_arr[m] = worst_fit_index; 
            fragments[m] = max_fragment; 
            block_arr[worst_fit_index] = 1; 
        } else {
            fragments[m] = -1; // No allocation possible, set fragment to -1
        }
    }

    printf("\nProcess Number\tBlock Number\tProcess Size\tBlock Size\tFragment");
    for (m = 0; m < number_of_process; m++) {
        printf("\n%d\t\t", m + 1); 
        
        if (file_arr[m] != -1) { 
            printf("%d\t\t%d\t\t%d\t\t%d", 
                   file_arr[m] + 1, 
                   Process[m], 
                   blocks[file_arr[m]], 
                   fragments[m]);
        } else {
            printf("-\t\t%d\t\t-\t\t-", Process[m]); // Indicate not allocated
        }
    }
    
    printf("\n");
    return 0;
}
