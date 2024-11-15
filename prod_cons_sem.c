#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5 // Size of the buffer

// Shared buffer
int buffer[N];
int in = 0; // Points to the next available empty slot
int out = 0; // Points to the next available full slot

// Semaphore declarations
sem_t mutex; // Controls access to the buffer (binary semaphore)
sem_t full;  // Number of full slots (counting semaphore)
sem_t empty; // Number of empty slots (counting semaphore)

// Function to simulate producing an item
void produce_item() {
    printf("Producing item\n");
}

// Function to simulate consuming an item
void consume_item() {
    printf("Consuming item\n");
}

// Function to simulate the producer thread
void* producer(void* arg) {
    while (1) {
        produce_item(); // Create an item

        sem_wait(&empty); // Check for an empty slot
        sem_wait(&mutex); // Enter critical section

        // Add item to buffer
        buffer[in] = 1; // Add item to buffer (for simplicity, we just store 1 as an item)
        printf("Produced item at position %d\n", in);
        in = (in + 1) % N; // Circular increment for buffer position

        sem_post(&mutex); // Leave critical section
        sem_post(&full);  // Increment count of full slots

        sleep(1); // Simulate some processing time
    }
    return NULL;
}

// Function to simulate the consumer thread
void* consumer(void* arg) {
    while (1) {
        sem_wait(&full);  // Check for a full slot
        sem_wait(&mutex); // Enter critical section

        // Remove item from buffer
        buffer[out] = 0; // Remove item from buffer (set to 0 for simplicity)
        printf("Consumed item from position %d\n", out);
        out = (out + 1) % N; // Circular increment for buffer position

        sem_post(&mutex); // Leave critical section
        sem_post(&empty);  // Increment count of empty slots

        consume_item(); // Consume the item

        sleep(1); // Simulate some processing time
    }
    return NULL;
}

int main() {
    // Initialize semaphores
    sem_init(&mutex, 0, 1);  // mutex = 1 (binary semaphore)
    sem_init(&full, 0, 0);    // full = 0 (counting semaphore)
    sem_init(&empty, 0, N);   // empty = N (counting semaphore)

    // Create producer and consumer threads
    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for both threads to complete
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}
