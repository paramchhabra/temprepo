#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>

std::mutex mtx;
std::condition_variable cv;
int readCount = 0;
bool writing = false;

void reader(int id) {
    for (int i = 0; i < 5; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !writing; });  // Wait while writing is in progress
        readCount++;
        lock.unlock();

        std::cout << "Reader " << id << " is reading." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        lock.lock();
        readCount--;
        if (readCount == 0) {
            cv.notify_all();  // Notify writers if no more readers
        }
        lock.unlock();
    }
}

void writer(int id) {
    for (int i = 0; i < 5; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(150));

        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return readCount == 0 && !writing; });  // Wait until no readers and no writing
        writing = true;

        std::cout << "Writer " << id << " is writing." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));

        writing = false;
        cv.notify_all();  // Notify readers and other writers
    }
}

int main() {
    std::vector<std::thread> readers;
    std::vector<std::thread> writers;

    for (int i = 0; i < 3; ++i) {
        readers.emplace_back(reader, i);
        writers.emplace_back(writer, i);
    }

    for (auto& r : readers) r.join();
    for (auto& w : writers) w.join();

    return 0;
}
