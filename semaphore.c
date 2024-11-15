#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h> // For sleep function

// Semaphore structure
typedef struct {
    int sem;
} Semaphore;

// Function to initialize the semaphore
void initSemaphore(Semaphore* sem, int value) {
    sem->sem = value;
}

// Wait function (decrement semaphore)
void wait(Semaphore* sem) {
    while (sem->sem <= 0) { // Busy wait if semaphore is not available
        // Do nothing, just wait for the semaphore to become 1
    }
    sem->sem = sem->sem - 1; // Acquire the semaphore (decrement)
}

// Signal function (increment semaphore)
void signal(Semaphore* sem) {
    sem->sem = sem->sem + 1; // Release the semaphore (increment)
}

// Critical section
void critical_section(pthread_t thread_id) {
    printf("Thread %lu entering critical section...\n", thread_id);
    sleep(1); // Simulate some work with a small delay (1 second)
    printf("Thread %lu exiting critical section...\n", thread_id);
}

// Process function for each thread
void* process(void* arg) {
    Semaphore* sem = (Semaphore*) arg;
    pthread_t thread_id = pthread_self(); // Get current thread's ID
    
    wait(sem); // Acquire the semaphore (lock)
    critical_section(thread_id); // Enter the critical section
    signal(sem); // Release the semaphore (unlock)
    
    return NULL;
}

int main() {
    Semaphore sem;
    initSemaphore(&sem, 1); // Initialize semaphore to 1 (binary semaphore)

    pthread_t t1, t2;

    // Create two threads, t1 and t2
    pthread_create(&t1, NULL, process, (void*)&sem);
    pthread_create(&t2, NULL, process, (void*)&sem);

    // Wait for both threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
