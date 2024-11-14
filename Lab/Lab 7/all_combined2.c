#include <stdio.h>

int block_arr[10];  // Declare block_arr globally so it can be accessed in both main and allocate_memory

void allocate_memory(int number_of_blocks, int number_of_files, int blocks[], int files[], char* strategy) {
    static int file_arr[10], fragments[10];
    int m, n, index, temp, best_fit, worst_fit, min_fragment, max_fragment;

    // Initialize the allocation status for each file to -1 (not allocated)
    for (m = 0; m < number_of_files; m++) {
        file_arr[m] = -1;
    }

    // Process each file
    for (m = 0; m < number_of_files; m++) {
        if (strategy == "First Fit") {
            // First Fit Algorithm
            temp = -1;
            for (n = 0; n < number_of_blocks; n++) {
                if (block_arr[n] != 1) { // Block is free
                    temp = blocks[n] - files[m];
                    if (temp >= 0) { // Fit found
                        file_arr[m] = n;
                        fragments[m] = temp; // Calculate the fragment
                        block_arr[n] = 1; // Mark block as allocated
                        break;
                    }
                }
            }
            if (file_arr[m] == -1) {
                fragments[m] = -1; // No allocation possible, set fragment to -1
            }
        } 
        else if (strategy == "Next Fit") {
            // Next Fit Algorithm (Allocate from the last used block onward)
            static int last_allocated = 0; // Keep track of the last allocated block
            int allocated = 0;
            for (n = last_allocated; n < number_of_blocks; n++) {
                if (block_arr[n] != 1 && blocks[n] >= files[m]) {
                    file_arr[m] = n;
                    fragments[m] = blocks[n] - files[m];
                    block_arr[n] = 1;
                    last_allocated = n; // Update the last allocated block
                    allocated = 1;
                    break;
                }
            }
            if (!allocated) {
                for (n = 0; n < last_allocated; n++) {
                    if (block_arr[n] != 1 && blocks[n] >= files[m]) {
                        file_arr[m] = n;
                        fragments[m] = blocks[n] - files[m];
                        block_arr[n] = 1;
                        break;
                    }
                }
            }
            if (file_arr[m] == -1) {
                fragments[m] = -1;
            }
        } 
        else if (strategy == "Worst Fit") {
            // Worst Fit Algorithm
            max_fragment = -1;
            for (n = 0; n < number_of_blocks; n++) {
                if (block_arr[n] != 1 && blocks[n] >= files[m]) {
                    int temp_fragment = blocks[n] - files[m];
                    if (temp_fragment > max_fragment) {
                        index = n;
                        max_fragment = temp_fragment;
                    }
                }
            }
            if (max_fragment != -1) {
                file_arr[m] = index;
                fragments[m] = max_fragment; // Calculate the fragment
                block_arr[index] = 1; // Mark block as allocated
            } else {
                fragments[m] = -1; // No allocation possible
            }
        }
        else if (strategy == "Best Fit") {
            // Best Fit Algorithm
            min_fragment = 9999;
            for (n = 0; n < number_of_blocks; n++) {
                if (block_arr[n] != 1 && blocks[n] >= files[m]) {
                    int temp_fragment = blocks[n] - files[m];
                    if (temp_fragment < min_fragment) {
                        index = n;
                        min_fragment = temp_fragment;
                    }
                }
            }
            if (min_fragment != 9999) {
                file_arr[m] = index;
                fragments[m] = min_fragment; // Calculate the fragment
                block_arr[index] = 1; // Mark block as allocated
            } else {
                fragments[m] = -1; // No allocation possible
            }
        }
    }

    // Output results
    printf("\n%s Allocation:\n", strategy);
    printf("File Number\tBlock Number\tFile Size\tBlock Size\tFragment\n");
    for (m = 0; m < number_of_files; m++) {
        printf("%d\t\t", m + 1);
        if (file_arr[m] != -1) {
            printf("%d\t\t%d\t\t%d\t\t%d\n", file_arr[m] + 1, files[m], blocks[file_arr[m]], fragments[m]);
        } else {
            printf("-\t\t%d\t\t-\t\t-\n", files[m]);
        }
    }
    printf("\n");
}

int main() {
    int number_of_blocks, number_of_files;
    int blocks[10], files[10];

    // User Input for number of blocks and files
    printf("\nEnter the Total Number of Blocks:\t");
    scanf("%d", &number_of_blocks);
    printf("Enter the Total Number of Files:\t");
    scanf("%d", &number_of_files);

    // Input block sizes
    printf("\nEnter the Size of the Blocks:\n");
    for (int m = 0; m < number_of_blocks; m++) {
        printf("Block No.[%d]:\t", m + 1);
        scanf("%d", &blocks[m]);
    }

    // Input file sizes
    printf("\nEnter the Size of the Files:\n");
    for (int m = 0; m < number_of_files; m++) {
        printf("File No.[%d]:\t", m + 1);
        scanf("%d", &files[m]);
    }

    // Reset block allocation status for each algorithm
    for (int i = 0; i < number_of_blocks; i++) {
        block_arr[i] = 0; // Reset block status to unallocated
    }

    // First Fit Allocation
    allocate_memory(number_of_blocks, number_of_files, blocks, files, "First Fit");

    // Reset block allocation status for Next Fit
    for (int i = 0; i < number_of_blocks; i++) {
        block_arr[i] = 0; // Reset block status to unallocated
    }
    // Next Fit Allocation
    allocate_memory(number_of_blocks, number_of_files, blocks, files, "Next Fit");

    // Reset block allocation status for Worst Fit
    for (int i = 0; i < number_of_blocks; i++) {
        block_arr[i] = 0; // Reset block status to unallocated
    }
    // Worst Fit Allocation
    allocate_memory(number_of_blocks, number_of_files, blocks, files, "Worst Fit");

    // Reset block allocation status for Best Fit
    for (int i = 0; i < number_of_blocks; i++) {
        block_arr[i] = 0; // Reset block status to unallocated
    }
    // Best Fit Allocation
    allocate_memory(number_of_blocks, number_of_files, blocks, files, "Best Fit");

    return 0;
}
