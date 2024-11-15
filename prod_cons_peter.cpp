#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>

const int BUFFER_SIZE = 10;
int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

std::atomic<bool> want_to_enter[2];
std::atomic<int> turn;

void producer(int id) {
    for (int j = 0; j < 10; ++j) {
        want_to_enter[id] = true;
        turn = 1 - id;

        while (want_to_enter[1 - id] && turn == 1 - id);

        buffer[in] = j;
        std::cout << "Producer " << id << " produced the item " << j << std::endl;
        in = (in + 1) % BUFFER_SIZE;

        want_to_enter[id] = false;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void consumer(int id) {
    for (int j = 0; j < 10; ++j) {
        want_to_enter[id] = true;
        turn = 1 - id;

        while (want_to_enter[1 - id] && turn == 1 - id);

        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;

        want_to_enter[id] = false;
        std::cout << "Consumer " << id << " consumed: " << item << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}

int main() {
    std::thread p1(producer, 0);
    std::thread p2(consumer, 0);
    std::thread p3(consumer, 1);
    
    p1.join();
    p2.join();
    p3.join();
    
    return 0;
}
