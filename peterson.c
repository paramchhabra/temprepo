#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

// Shared variables
bool flag[2] = {false, false}; // Flags indicating desire to enter critical section
int turn = 0;                  // Variable to decide whose turn it is

// Critical section simulation
void critical_section(int process_id) {
    printf("Process %d is in the critical section.\n", process_id);
    sleep(1); // Simulate some work in the critical section
    printf("Process %d is leaving the critical section.\n", process_id);
}

// Process 0 function
void* process_0(void* arg) {
    while (1) {
        flag[0] = true;       // Indicate that process 0 wants to enter
        turn = 1;             // Give priority to process 1
        while (flag[1] && turn == 1)
            ;                 // Busy wait until process 1 finishes

        // Enter critical section
        critical_section(0);

        // Exit critical section
        flag[0] = false;
    }
    return NULL;
}

// Process 1 function
void* process_1(void* arg) {
    while (1) {
        flag[1] = true;       // Indicate that process 1 wants to enter
        turn = 0;             // Give priority to process 0
        while (flag[0] && turn == 0)
            ;                 // Busy wait until process 0 finishes

        // Enter critical section
        critical_section(1);

        // Exit critical section
        flag[1] = false;
    }
    return NULL;
}

int main() {
    pthread_t t0, t1;

    // Create threads for process 0 and process 1
    pthread_create(&t0, NULL, process_0, NULL);
    pthread_create(&t1, NULL, process_1, NULL);

    // Wait for threads to finish (optional as this runs indefinitely)
    pthread_join(t0, NULL);
    pthread_join(t1, NULL);

    return 0;
}
