#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

const int BUFFER_SIZE = 10;
int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

std::mutex mtx;
std::condition_variable cv;
int count = 0;

void producer(int id) {
    for (int j = 0; j < 10; ++j) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return count < BUFFER_SIZE; });

        buffer[in] = j;
        std::cout << "Producer " << id << " produced the item " << j << std::endl;
        in = (in + 1) % BUFFER_SIZE;
        ++count;

        cv.notify_all();
    }
}

void consumer(int id) {
    for (int j = 0; j < 10; ++j) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return count > 0; });

        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        --count;

        std::cout << "Consumer " << id << " consumed: " << item << std::endl;

        cv.notify_all();
    }
}

int main() {
    std::thread p1(producer, 0);
    std::thread c1(consumer, 0);
    std::thread c2(consumer, 1);
    
    p1.join();
    c1.join();
    c2.join();
    
    return 0;
}
