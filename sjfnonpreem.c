#include <stdio.h>

struct Process {
    int pid;         // Process ID
    int arrival;     // Arrival time
    int burst;       // Burst time
    int completion;  // Completion time
    int turnaround;  // Turnaround time
    int waiting;     // Waiting time
    int isCompleted; // Flag to check if process is completed
};

// Function to sort processes by arrival time, and by burst time if arrival times are the same
void sortProcesses(struct Process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].arrival > proc[j].arrival || 
               (proc[i].arrival == proc[j].arrival && proc[i].burst > proc[j].burst)) {
                // Swap processes
                struct Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

// Non-preemptive SJF Scheduling function
void nonPreemptiveSJF(struct Process proc[], int n) {
    int currentTime = 0, completed = 0;
    float totalTurnaround = 0, totalWaiting = 0;

    while (completed < n) {
        int shortest = -1;
        int minBurst = 1e9; // A large number to find the minimum burst time

        // Find the shortest job among the available processes
        for (int i = 0; i < n; i++) {
            if (proc[i].arrival <= currentTime && !proc[i].isCompleted) {
                if (proc[i].burst < minBurst) {
                    minBurst = proc[i].burst;
                    shortest = i;
                }
            }
        }

        if (shortest == -1) {
            currentTime++; // If no process has arrived, increment time
        } else {
            // Process the shortest job
            proc[shortest].completion = currentTime + proc[shortest].burst;
            proc[shortest].turnaround = proc[shortest].completion - proc[shortest].arrival;
            proc[shortest].waiting = proc[shortest].turnaround - proc[shortest].burst;
            proc[shortest].isCompleted = 1;
            completed++;

            // Update totals
            totalTurnaround += proc[shortest].turnaround;
            totalWaiting += proc[shortest].waiting;
            
            // Update current time
            currentTime = proc[shortest].completion;
        }
    }

    // Calculate and display average times
    printf("\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].arrival, proc[i].burst,
               proc[i].completion, proc[i].turnaround, proc[i].waiting);
    }
    printf("\nAverage Turnaround Time: %.2f", totalTurnaround / n);
    printf("\nAverage Waiting Time: %.2f\n", totalWaiting / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[20];
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", proc[i].pid);
        scanf("%d %d", &proc[i].arrival, &proc[i].burst);
        proc[i].isCompleted = 0; // Initialize as not completed
    }

    // Sort processes by arrival time and burst time
    sortProcesses(proc, n);

    // Perform Non-Preemptive SJF scheduling
    nonPreemptiveSJF(proc, n);

    return 0;
}
