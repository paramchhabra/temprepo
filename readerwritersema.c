#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Semaphores and shared variables
sem_t mutex;    // Protects read_count
sem_t wrt;      // Controls access to the shared resource
int read_count = 0; // Number of readers currently accessing the resource

// Shared resource (for demonstration)
int shared_data = 0;

// Function for readers
void* reader(void* arg) {
    int id = *(int*)arg;

    while (1) {
        // Enter critical section to update read_count
        sem_wait(&mutex);
        read_count++;
        if (read_count == 1) {
            // First reader locks writers
            sem_wait(&wrt);
        }
        sem_post(&mutex);

        // Read data (simulated)
        printf("Reader %d: Read shared data = %d\n", id, shared_data);
        sleep(1); // Simulate reading time

        // Exit critical section
        sem_wait(&mutex);
        read_count--;
        if (read_count == 0) {
            // Last reader unlocks writers
            sem_post(&wrt);
        }
        sem_post(&mutex);

        sleep(1); // Simulate time before the next read
    }

    return NULL;
}

// Function for writers
void* writer(void* arg) {
    int id = *(int*)arg;

    while (1) {
        // Enter critical section to write
        sem_wait(&wrt);

        // Write data (simulated)
        shared_data++;
        printf("Writer %d: Wrote shared data = %d\n", id, shared_data);
        sleep(1); // Simulate writing time

        // Exit critical section
        sem_post(&wrt);

        sleep(2); // Simulate time before the next write
    }

    return NULL;
}

int main() {
    int num_readers = 3; // Number of readers
    int num_writers = 2; // Number of writers

    pthread_t readers[num_readers], writers[num_writers];
    int reader_ids[num_readers], writer_ids[num_writers];

    // Initialize semaphores
    sem_init(&mutex, 0, 1); // Binary semaphore
    sem_init(&wrt, 0, 1);   // Binary semaphore

    // Create reader threads
    for (int i = 0; i < num_readers; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < num_writers; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Wait for all threads to finish (in this case, the program runs indefinitely)
    for (int i = 0; i < num_readers; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < num_writers; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
