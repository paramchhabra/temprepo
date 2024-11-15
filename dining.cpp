#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

using namespace std;

const int N = 5; // Number of philosophers (and forks)
mutex chopstick[N]; // One mutex for each chopstick

void think(int philosopherId) {
    cout << "Philosopher " << philosopherId << " is thinking." << endl;
    this_thread::sleep_for(chrono::milliseconds(1000)); // Simulate thinking time
}

void eat(int philosopherId) {
    cout << "Philosopher " << philosopherId << " is eating." << endl;
    this_thread::sleep_for(chrono::milliseconds(1000)); // Simulate eating time
}

void philosopher(int id, int iterations) {
    for (int i = 0; i < iterations; ++i) {
        think(id); // Philosopher is thinking

        // Pick up the left chopstick (mutex)
        chopstick[id].lock();
        cout << "Philosopher " << id << " picked up left chopstick." << endl;

        // Pick up the right chopstick (mutex)
        chopstick[(id + 1) % N].lock();
        cout << "Philosopher " << id << " picked up right chopstick." << endl;

        eat(id); // Philosopher is eating

        // Put down the left chopstick
        chopstick[id].unlock();
        cout << "Philosopher " << id << " put down left chopstick." << endl;

        // Put down the right chopstick
        chopstick[(id + 1) % N].unlock();
        cout << "Philosopher " << id << " put down right chopstick." << endl;
    }
}

int main() {
    int iterations = 3; // Number of thinking/eating cycles per philosopher
    vector<thread> philosophers;

    // Create philosopher threads
    for (int i = 0; i < N; ++i) {
        philosophers.push_back(thread(philosopher, i, iterations));
    }

    // Join philosopher threads
    for (int i = 0; i < N; ++i) {
        philosophers[i].join();
    }

    return 0;
}
