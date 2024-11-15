#include <iostream>
#include <thread>              // For std::thread
#include <mutex>               // For std::mutex and std::unique_lock
#include <condition_variable>  // For std::condition_variable
#include <chrono>              // For std::chrono::seconds
#include <queue>
#include <mutex>               // For std::mutex and std::unique_lock

const int MAX_BUFFER_SIZE = 5;

std::queue<int> buffer;
std::mutex mtx;
std::condition_variable cv_empty, cv_full;

int empty_slots = MAX_BUFFER_SIZE;
int full_slots = 0;

void producer(int id, int itemsToProduce) {
    for (int i = 0; i < itemsToProduce; ++i) {
        std::unique_lock<std::mutex> lock(mtx);

        cv_empty.wait(lock, [] { return empty_slots > 0; });

        buffer.push(i);
        std::cout << "Producer " << id << " produced item " << i << "\n";
        --empty_slots;
        ++full_slots;

        cv_full.notify_one();

        lock.unlock();

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void consumer(int id, int itemsToConsume) {
    for (int i = 0; i < itemsToConsume; ++i) {
        std::unique_lock<std::mutex> lock(mtx);

        cv_full.wait(lock, [] { return full_slots > 0; });

        int item = buffer.front();
        buffer.pop();
        std::cout << "Consumer " << id << " consumed item " << item << "\n";
        --full_slots;
        ++empty_slots;

        cv_empty.notify_one();

        lock.unlock();

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    int items = 10;

    std::thread prod1(producer, 1, items);
    std::thread cons1(consumer, 1, items);

    prod1.join();
    cons1.join();

    return 0;
}
