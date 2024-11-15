#include <stdio.h>
#include <limits.h> // For INT_MAX

struct Process {
    int pid;            // Process ID
    int arrival;        // Arrival Time
    int burst;          // Burst Time
    int remaining;      // Remaining Time
    int completion;     // Completion Time
    int turnaround;     // Turnaround Time
    int waiting;        // Waiting Time
};

// Function to find the index of the process with the shortest remaining time
int findShortestJob(struct Process proc[], int n, int currentTime) {
    int minTime = INT_MAX;
    int shortest = -1;

    for (int i = 0; i < n; i++) {
        if (proc[i].arrival <= currentTime && proc[i].remaining > 0 && proc[i].remaining < minTime) {
            minTime = proc[i].remaining;
            shortest = i;
        }
    }
    return shortest;
}

// Preemptive Shortest Job First (SJF) scheduling
void preemptiveSJF(struct Process proc[], int n) {
    int currentTime = 0, completed = 0;
    float totalTurnaround = 0, totalWaiting = 0;

    // Loop until all processes are completed
    while (completed < n) {
        int idx = findShortestJob(proc, n, currentTime);

        if (idx == -1) {
            currentTime++; // No process ready, increment time
        } else {
            proc[idx].remaining--;
            currentTime++;

            // If process is completed
            if (proc[idx].remaining == 0) {
                proc[idx].completion = currentTime;
                proc[idx].turnaround = proc[idx].completion - proc[idx].arrival;
                proc[idx].waiting = proc[idx].turnaround - proc[idx].burst;

                totalTurnaround += proc[idx].turnaround;
                totalWaiting += proc[idx].waiting;
                completed++;
            }
        }
    }

    // Display process details
    printf("\nPID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].arrival, proc[i].burst, proc[i].completion, proc[i].turnaround, proc[i].waiting);
    }

    // Display average times
    printf("\nAverage Turnaround Time: %.2f\n", totalTurnaround / n);
    printf("Average Waiting Time: %.2f\n", totalWaiting / n);
}

int main() {
    int n;
    struct Process proc[100];

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input arrival and burst times for each process
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter arrival time for process %d: ", proc[i].pid);
        scanf("%d", &proc[i].arrival);
        printf("Enter burst time for process %d: ", proc[i].pid);
        scanf("%d", &proc[i].burst);
        proc[i].remaining = proc[i].burst; // Initialize remaining time
    }

    // Execute preemptive SJF scheduling
    preemptiveSJF(proc, n);

    return 0;
}
