#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 5 // Number of philosophers and forks

// Semaphore (representing forks)
int chopstick[N] = {1, 1, 1, 1, 1}; // Each chopstick is initially available
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex to avoid race conditions when updating chopstick values

// Wait function to acquire a semaphore
void wait(int *sem) {
    while (*sem <= 0); // Busy wait
    (*sem)--;
}

// Signal function to release a semaphore
void signal(int *sem) {
    (*sem)++;
}

// Simulate philosopher thinking
void think(int id) {
    printf("Philosopher %d is thinking.\n", id);
    sleep(1);
}

// Simulate philosopher eating
void eat(int id) {
    printf("Philosopher %d is eating.\n", id);
    sleep(2);
}

// Philosopher function
void* philosopher(void* num) {
    int id = *(int*)num;
    while (1) {
        think(id); // Philosopher is thinking

        // Try to acquire both chopsticks
        pthread_mutex_lock(&mutex); // Lock to avoid race conditions when updating chopsticks
        wait(&chopstick[id]); // Pick up the left chopstick
        wait(&chopstick[(id + 1) % N]); // Pick up the right chopstick
        pthread_mutex_unlock(&mutex);

        eat(id); // Philosopher is eating

        // Release both chopsticks
        pthread_mutex_lock(&mutex);
        signal(&chopstick[id]); // Put down the left chopstick
        signal(&chopstick[(id + 1) % N]); // Put down the right chopstick
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t philosophers[N];
    int ids[N];

    // Create threads for each philosopher
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Wait for all philosopher threads to finish (optional in this infinite loop case)
    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}
