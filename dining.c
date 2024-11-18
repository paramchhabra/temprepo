#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 5 // Number of philosophers and forks

pthread_mutex_t chopstick[N]; // Mutex for each chopstick

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

        // Pick up chopsticks
        if (id % 2 == 0) { // Even philosophers pick up left then right
            pthread_mutex_lock(&chopstick[id]);
            pthread_mutex_lock(&chopstick[(id + 1) % N]);
        } else { // Odd philosophers pick up right then left
            pthread_mutex_lock(&chopstick[(id + 1) % N]);
            pthread_mutex_lock(&chopstick[id]);
        }

        eat(id); // Philosopher is eating

        // Put down chopsticks
        pthread_mutex_unlock(&chopstick[id]);
        pthread_mutex_unlock(&chopstick[(id + 1) % N]);
    }

    return NULL;
}

int main() {
    pthread_t philosophers[N];
    int ids[N];

    // Initialize mutexes for chopsticks
    for (int i = 0; i < N; i++) {
        pthread_mutex_init(&chopstick[i], NULL);
    }

    // Create threads for each philosopher
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Wait for all philosopher threads to finish (optional in this infinite loop case)
    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy mutexes
    for (int i = 0; i < N; i++) {
        pthread_mutex_destroy(&chopstick[i]);
    }

    return 0;
}
