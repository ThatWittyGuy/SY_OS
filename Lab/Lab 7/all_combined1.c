#include <stdio.h>

void allocate_memory(int blocks[], int block_arr[], int files[], int file_arr[], int fragments[], int number_of_blocks, int number_of_files, int choice) {
    int m, n, temp, best_fit_index, worst_fit_index;
    int min_fragment, max_fragment, last_allocated = 0;

    for (m = 0; m < number_of_files; m++) {
        file_arr[m] = -1; // Initialize file allocation status
        fragments[m] = -1; // Initialize fragment as -1 (unallocated)
    }

    for (m = 0; m < number_of_files; m++) {
        switch (choice) {
            case 1: // First Fit
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
                break;

            case 2: // Next Fit
                for (n = last_allocated; n < number_of_blocks; n++) {
                    if (block_arr[n] != 1) {
                        temp = blocks[n] - files[m];
                        if (temp >= 0) {
                            file_arr[m] = n;
                            fragments[m] = temp;
                            block_arr[n] = 1;
                            last_allocated = n;
                            break;
                        }
                    }
                }
                if (file_arr[m] == -1) {
                    for (n = 0; n < last_allocated; n++) {
                        if (block_arr[n] != 1) {
                            temp = blocks[n] - files[m];
                            if (temp >= 0) {
                                file_arr[m] = n;
                                fragments[m] = temp;
                                block_arr[n] = 1;
                                last_allocated = n;
                                break;
                            }
                        }
                    }
                }
                break;

            case 3: // Worst Fit
                worst_fit_index = -1;
                max_fragment = -1;
                for (n = 0; n < number_of_blocks; n++) {
                    if (block_arr[n] != 1) {
                        temp = blocks[n] - files[m];
                        if (temp >= 0 && temp > max_fragment) {
                            worst_fit_index = n;
                            max_fragment = temp;
                        }
                    }
                }
                if (worst_fit_index != -1) {
                    file_arr[m] = worst_fit_index;
                    fragments[m] = max_fragment;
                    block_arr[worst_fit_index] = 1;
                }
                break;

            case 4: // Best Fit
                best_fit_index = -1;
                min_fragment = 9999;
                for (n = 0; n < number_of_blocks; n++) {
                    if (block_arr[n] != 1) {
                        temp = blocks[n] - files[m];
                        if (temp >= 0 && temp < min_fragment) {
                            best_fit_index = n;
                            min_fragment = temp;
                        }
                    }
                }
                if (best_fit_index != -1) {
                    file_arr[m] = best_fit_index;
                    fragments[m] = min_fragment;
                    block_arr[best_fit_index] = 1;
                }
                break;
        }
    }
}

int main() {
    int blocks[10], block_arr[10], files[10], file_arr[10], fragments[10];
    int number_of_blocks, number_of_files, choice;

    printf("Enter the Total Number of Blocks: ");
    scanf("%d", &number_of_blocks);
    printf("Enter the Total Number of Files: ");
    scanf("%d", &number_of_files);

    printf("Enter the Size of the Blocks:\n");
    for (int m = 0; m < number_of_blocks; m++) {
        printf("Block No.[%d]: ", m + 1);
        scanf("%d", &blocks[m]);
        block_arr[m] = 0; // Initially, all blocks are unallocated
    }

    printf("Enter the Size of the Files:\n");
    for (int m = 0; m < number_of_files; m++) {
        printf("File No.[%d]: ", m + 1);
        scanf("%d", &files[m]);
    }

    printf("Choose Memory Allocation Strategy:\n");
    printf("1. First Fit\n");
    printf("2. Next Fit\n");
    printf("3. Worst Fit\n");
    printf("4. Best Fit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    allocate_memory(blocks, block_arr, files, file_arr, fragments, number_of_blocks, number_of_files, choice);

    printf("\nFile Number\tBlock Number\tFile Size\tBlock Size\tFragment\n");
    for (int m = 0; m < number_of_files; m++) {
        printf("%d\t\t", m + 1);
        if (file_arr[m] != -1) {
            printf("%d\t\t%d\t\t%d\t\t%d\n", file_arr[m] + 1, files[m], blocks[file_arr[m]], fragments[m]);
        } else {
            printf("-\t\t%d\t\t-\t\t-\n", files[m]); // Indicate not allocated
        }
    }

    return 0;
}
