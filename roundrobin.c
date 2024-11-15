#include <stdio.h>

struct Process {
    int pid;         // Process ID
    int arrival;     // Arrival time
    int burst;       // Burst time
    int remaining;   // Remaining burst time
    int completion;  // Completion time
    int turnaround;  // Turnaround time
    int waiting;     // Waiting time
};

// Helper function to swap two processes
void swap(struct Process *a, struct Process *b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}

// Function to sort processes by arrival time
void sortByArrival(struct Process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].arrival > proc[j + 1].arrival) {
                swap(&proc[j], &proc[j + 1]);
            }
        }
    }
}

// Round Robin scheduling function
void roundRobin(struct Process proc[], int n, int quantum) {
    int currentTime = 0, completed = 0, seqIndex = 0;
    int totalTurnaround = 0, totalWaiting = 0;
    int sequence[100]; // Stores the process execution sequence

    // Initialize remaining burst time for each process
    for (int i = 0; i < n; i++) {
        proc[i].remaining = proc[i].burst;
    }

    while (completed < n) {
        int found = 0; // Flag to check if any process is executed in this cycle
        for (int i = 0; i < n; i++) {
            if (proc[i].arrival <= currentTime && proc[i].remaining > 0) { // Process is eligible
                sequence[seqIndex++] = proc[i].pid; // Add to execution sequence
                if (proc[i].remaining <= quantum) {
                    currentTime += proc[i].remaining;
                    proc[i].completion = currentTime;
                    proc[i].remaining = 0;
                    proc[i].turnaround = proc[i].completion - proc[i].arrival;
                    proc[i].waiting = proc[i].turnaround - proc[i].burst;
                    totalTurnaround += proc[i].turnaround;
                    totalWaiting += proc[i].waiting;
                    completed++;
                } else {
                    currentTime += quantum;
                    proc[i].remaining -= quantum;
                }
                found = 1;
            }
        }
        if (!found) currentTime++; // No process executed, increment time
    }

    // Display process execution sequence
    printf("\nExecution Sequence: ");
    for (int i = 0; i < seqIndex; i++) {
        printf("P%d ", sequence[i]);
    }

    // Display process details
    printf("\n\nPID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].arrival, proc[i].burst,
               proc[i].completion, proc[i].turnaround, proc[i].waiting);
    }

    // Calculate and display averages
    printf("\nAverage Turnaround Time: %.2f", (float)totalTurnaround / n);
    printf("\nAverage Waiting Time: %.2f\n", (float)totalWaiting / n);
}

int main() {
    int n, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[100];
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &proc[i].arrival, &proc[i].burst);
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    // Sort processes by arrival time
    sortByArrival(proc, n);

    // Perform Round Robin scheduling
    roundRobin(proc, n, quantum);

    return 0;
}
