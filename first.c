#include <stdio.h>

struct Process {
    int pid;            // Process ID
    int arrival;        // Arrival Time
    int burst;          // Burst Time
    int completion;     // Completion Time
    int turnaround;     // Turnaround Time
    int waiting;        // Waiting Time
};

// Function to sort processes by arrival time
void sortByArrival(struct Process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].arrival > proc[j].arrival) {
                // Swap processes
                struct Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

// FCFS scheduling function
void firstComeFirstServe(struct Process proc[], int n) {
    int currentTime = 0;
    float totalTurnaround = 0, totalWaiting = 0;

    // Process scheduling
    for (int i = 0; i < n; i++) {
        if (currentTime < proc[i].arrival) {
            currentTime = proc[i].arrival;
        }
        
        proc[i].completion = currentTime + proc[i].burst;
        proc[i].turnaround = proc[i].completion - proc[i].arrival;
        proc[i].waiting = proc[i].turnaround - proc[i].burst;

        totalTurnaround += proc[i].turnaround;
        totalWaiting += proc[i].waiting;

        currentTime = proc[i].completion;
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
    }

    // Sort processes by arrival time and run FCFS scheduling
    sortByArrival(proc, n);
    firstComeFirstServe(proc, n);

    return 0;
}
