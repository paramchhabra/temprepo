#include <stdio.h>
#include <limits.h>

struct Process {
    int pid;          // Process ID
    int arrival;      // Arrival time of the process
    int burst;        // Total burst time of the process
    int priority;     // Priority value (lower value means higher priority)
    int remaining;    // Remaining burst time of the process
    int completion;   // Completion time of the process
    int turnaround;   // Turnaround time of the process
    int waiting;      // Waiting time of the process
};

// Function to implement preemptive priority scheduling
void preemptivePriorityScheduling(struct Process proc[], int n) {
    int currentTime = 0, completed = 0;
    int totalTurnaround = 0, totalWaiting = 0;
    int sequence[100]; // Stores the process execution sequence
    int seqIndex = 0;

    while (completed < n) {
        int highestPriorityIndex = -1;
        int highestPriority = INT_MAX;

        // Find the process with the highest priority (lowest priority value) that has arrived and has remaining time
        for (int i = 0; i < n; i++) {
            if (proc[i].arrival <= currentTime && proc[i].remaining > 0 && proc[i].priority < highestPriority) {
                highestPriority = proc[i].priority;
                highestPriorityIndex = i;
            }
        }

        if (highestPriorityIndex != -1) { // Process found
            int i = highestPriorityIndex;
            proc[i].remaining--; // Execute for one time unit
            sequence[seqIndex++] = proc[i].pid;

            if (proc[i].remaining == 0) { // Process completes
                proc[i].completion = currentTime + 1;
                proc[i].turnaround = proc[i].completion - proc[i].arrival;
                proc[i].waiting = proc[i].turnaround - proc[i].burst;
                totalTurnaround += proc[i].turnaround;
                totalWaiting += proc[i].waiting;
                completed++;
            }

            currentTime++; // Increment current time after execution
        } else {
            currentTime++; // No process is ready, increment time
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
        proc[i].remaining = proc[i].burst; // Initialize remaining burst time
    }

    // Perform preemptive priority scheduling
    preemptivePriorityScheduling(proc, n);

    return 0;
}
