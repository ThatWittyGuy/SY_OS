#include <stdio.h>

int block_arr[10];

void reset_blocks(int number_of_blocks) {
    for (int i = 0; i < number_of_blocks; i++) {
        block_arr[i] = 0;
    }
}

void allocate_memory(int number_of_blocks, int number_of_files, int blocks[], int files[], const char* strategy) {
    int file_arr[10], fragments[10];
    int m, n, index, best_fit, worst_fit, min_fragment, max_fragment;

    for (m = 0; m < number_of_files; m++) {
        file_arr[m] = -1;
    }

    for (m = 0; m < number_of_files; m++) {
        if (strategy == "First Fit") {
            for (n = 0; n < number_of_blocks; n++) {
                if (!block_arr[n] && blocks[n] >= files[m]) {
                    file_arr[m] = n;
                    fragments[m] = blocks[n] - files[m];
                    block_arr[n] = 1;
                    break;
                }
            }
            if (file_arr[m] == -1) fragments[m] = -1;
        }
        else if (strategy == "Next Fit") {
            static int last_allocated = 0;
            int allocated = 0;
            for (n = last_allocated; n < number_of_blocks; n++) {
                if (!block_arr[n] && blocks[n] >= files[m]) {
                    file_arr[m] = n;
                    fragments[m] = blocks[n] - files[m];
                    block_arr[n] = 1;
                    last_allocated = n;
                    allocated = 1;
                    break;
                }
            }
            if (!allocated) {
                for (n = 0; n < last_allocated; n++) {
                    if (!block_arr[n] && blocks[n] >= files[m]) {
                        file_arr[m] = n;
                        fragments[m] = blocks[n] - files[m];
                        block_arr[n] = 1;
                        break;
                    }
                }
            }
            if (file_arr[m] == -1) fragments[m] = -1;
        }
        else if (strategy == "Worst Fit") {
            max_fragment = -1;
            for (n = 0; n < number_of_blocks; n++) {
                if (!block_arr[n] && blocks[n] >= files[m]) {
                    int temp_fragment = blocks[n] - files[m];
                    if (temp_fragment > max_fragment) {
                        index = n;
                        max_fragment = temp_fragment;
                    }
                }
            }
            if (max_fragment != -1) {
                file_arr[m] = index;
                fragments[m] = max_fragment;
                block_arr[index] = 1;
            } else {
                fragments[m] = -1;
            }
        }
    }

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

    printf("\nEnter the Total Number of Blocks:\t");
    scanf("%d", &number_of_blocks);
    printf("Enter the Total Number of Files:\t");
    scanf("%d", &number_of_files);

    printf("\nEnter the Size of the Blocks:\n");
    for (int m = 0; m < number_of_blocks; m++) {
        printf("Block No.[%d]:\t", m + 1);
        scanf("%d", &blocks[m]);
    }

    printf("\nEnter the Size of the Files:\n");
    for (int m = 0; m < number_of_files; m++) {
        printf("File No.[%d]:\t", m + 1);
        scanf("%d", &files[m]);
    }

    reset_blocks(number_of_blocks);
    allocate_memory(number_of_blocks, number_of_files, blocks, files, "First Fit");

    reset_blocks(number_of_blocks);
    allocate_memory(number_of_blocks, number_of_files, blocks, files, "Next Fit");

    reset_blocks(number_of_blocks);
    allocate_memory(number_of_blocks, number_of_files, blocks, files, "Worst Fit");

    return 0;
}
