#include <stdio.h>

// Function to find the least recently used page
int findLRU(int time[], int n) {
    int minimum = time[0], pos = 0;
    for (int i = 1; i < n; i++) {
        if (time[i] < minimum) {
            minimum = time[i];
            pos = i;
        }
    }
    return pos;
}

// Function to implement LRU page replacement
void lruPageReplacement(int pages[], int n, int capacity) {
    int frames[capacity];  // Array to store pages in memory
    int time[capacity];    // Array to track usage time of pages
    int pageFaults = 0;    // Counter for page faults
    int counter = 0;       // Counter to simulate time (for LRU tracking)
    int found, pos;

    // Initialize frames to -1 (indicating empty)
    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;
    }

    printf("\nPage Reference\tMemory State\n");
    for (int i = 0; i < n; i++) {
        found = 0;

        // Check if the page is already in memory
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                time[j] = counter++;  // Update the time for this page
                break;
            }
        }

        if (!found) { // Page fault occurs
            if (i < capacity) {
                // Place page in an empty frame
                frames[i] = pages[i];
                time[i] = counter++;
            } else {
                // Replace least recently used page
                pos = findLRU(time, capacity);
                frames[pos] = pages[i];
                time[pos] = counter++;
            }
            pageFaults++;
        }

        // Print the current memory state
        printf("%d\t\t", pages[i]);
        for (int j = 0; j < capacity; j++) {
            if (frames[j] != -1) {
                printf("%d ", frames[j]);
            } else {
                printf("- ");
            }
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

    printf("LRU Page Replacement Algorithm\n");
    lruPageReplacement(pages, n, capacity);

    return 0;
}
