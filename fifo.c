#include <stdio.h>

void fifoPageReplacement(int pages[], int n, int capacity) {
    int memory[capacity];      // Array to represent memory slots
    int front = 0, rear = 0;   // Pointers for FIFO queue simulation
    int count = 0;             // Number of pages in memory
    int pageFaults = 0;        // Counter for page faults

    // Initialize memory slots to -1 (indicating empty)
    for (int i = 0; i < capacity; i++) {
        memory[i] = -1;
    }

    printf("\nPage Reference\tMemory State\n");
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in memory
        for (int j = 0; j < count; j++) {
            if (memory[j] == page) {
                found = 1;
                break;
            }
        }

        if (!found) { // Page fault occurs
            pageFaults++;

            if (count < capacity) {
                // Add the page to memory (no replacement needed yet)
                memory[rear] = page;
                rear = (rear + 1) % capacity;
                count++;
            } else {
                // Replace the oldest page (FIFO)
                memory[rear] = page;
                rear = (rear + 1) % capacity;
                front = (front + 1) % capacity;
            }
        }

        // Print the current memory state
        printf("%d\t\t", page);
        for (int j = 0; j < count; j++) {
            printf("%d ", memory[j]);
        }
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
}

// Driver code
int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;

    printf("FIFO Page Replacement Algorithm\n");
    fifoPageReplacement(pages, n, capacity);

    return 0;
}
