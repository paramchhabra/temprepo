#include <stdio.h>

void implementBestFit(int blockSize[], int blocks, int processSize[], int processes) {
    // This will store the block id of the allocated block to a process
    int allocation[processes];
    int occupied[blocks];

    // Initially assigning -1 to all allocation indexes
    // means nothing is allocated currently
    for (int i = 0; i < processes; i++) {
        allocation[i] = -1;
    }

    for (int i = 0; i < blocks; i++) {
        occupied[i] = 0;
    }

    // Pick each process and find suitable blocks
    // according to its size and assign to it
    for (int i = 0; i < processes; i++) {
        int indexPlaced = -1;
        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i] && !occupied[j]) {
                // Place it at the first block fit to accommodate process
                if (indexPlaced == -1)
                    indexPlaced = j;

                // If any future block is smaller than the current block where
                // process is placed, change the block and thus indexPlaced
                // This reduces wastage, achieving best fit
                else if (blockSize[j] < blockSize[indexPlaced])
                    indexPlaced = j;
            }
        }

        // If we were successfully able to find a block for the process
        if (indexPlaced != -1) {
            // Allocate this block to the process
            allocation[i] = indexPlaced;

            // Mark the block as occupied
            occupied[indexPlaced] = 1;
        }
    }

    // Print the allocation results
    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < processes; i++) {
        printf("%d \t\t\t %d \t\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

// Driver code
int main() {
    int blockSize[] = {100, 50, 30, 120, 35};
    int processSize[] = {40, 10, 30, 60};
    int blocks = sizeof(blockSize) / sizeof(blockSize[0]);
    int processes = sizeof(processSize) / sizeof(processSize[0]);

    implementBestFit(blockSize, blocks, processSize, processes);
    return 0;
}
