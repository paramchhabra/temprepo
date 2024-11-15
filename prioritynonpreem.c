#include <stdio.h>
#include <limits.h>

struct Process {
    int pid;         // Process ID
    int arrival;     // Arrival time
    int burst;       // Burst time
    int priority;    // Priority (lower value means higher priority)
    int completion;  // Completion time
    int turnaround;  // Turnaround time
    int waiting;     // Waiting time
};

// Function to swap two processes
void swap(struct Process *a, struct Process *b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}

// Function to sort processes by arrival time, and by priority if arrival times are the same
void sortByArrivalAndPriority(struct Process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].arrival > proc[j + 1].arrival || 
               (proc[j].arrival == proc[j + 1].arrival && proc[j].priority > proc[j + 1].priority)) {
                swap(&proc[j], &proc[j + 1]);
            }
        }
    }
}

// Function to implement non-preemptive priority scheduling
void priorityScheduling(struct Process proc[], int n) {
    int currentTime = 0, completed = 0, totalTurnaround = 0, totalWaiting = 0;
    int sequence[100]; // Stores the process execution sequence
    int seqIndex = 0;
    int isCompleted[100] = {0}; // Array to mark if a process is completed

    while (completed < n) {
        int highestPriorityIndex = -1;
        int highestPriority = INT_MAX;

        // Find the process with the highest priority (lowest priority value) that has arrived
        for (int i = 0; i < n; i++) {
            if (proc[i].arrival <= currentTime && !isCompleted[i] && proc[i].priority < highestPriority) {
                highestPriority = proc[i].priority;
                highestPriorityIndex = i;
            }
        }

        if (highestPriorityIndex != -1) { // Process found
            int i = highestPriorityIndex;
            currentTime += proc[i].burst;
            proc[i].completion = currentTime;
            proc[i].turnaround = proc[i].completion - proc[i].arrival;
            proc[i].waiting = proc[i].turnaround - proc[i].burst;
            totalTurnaround += proc[i].turnaround;
            totalWaiting += proc[i].waiting;
            sequence[seqIndex++] = proc[i].pid;
            isCompleted[i] = 1;
            completed++;
        } else {
            currentTime++; // No process ready to execute, increment time
        }
    }

    // Display process execution sequence
    printf("\nExecution Sequence: ");
    for (int i = 0; i < seqIndex; i++) {
        printf("P%d ", sequence[i]);
    }

    // Display process details
    printf("\n\nPID\tArrival\tBurst\tPriority\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].arrival, proc[i].burst,
               proc[i].priority, proc[i].completion, proc[i].turnaround, proc[i].waiting);
    }

    // Calculate and display averages
    printf("\nAverage Turnaround Time: %.2f", (float)totalTurnaround / n);
    printf("\nAverage Waiting Time: %.2f\n", (float)totalWaiting / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[100];
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &proc[i].arrival, &proc[i].burst, &proc[i].priority);
    }

    // Sort processes by arrival time and priority
    sortByArrivalAndPriority(proc, n);

    // Perform priority scheduling
    priorityScheduling(proc, n);

    return 0;
}
