#include <iostream>
#include <thread>
#include <semaphore.h>
#include <vector>
#include <chrono>

sem_t writeSemaphore;
sem_t readerSemaphore;
int readCount = 0;

void reader(int id) {
    for (int i = 0; i < 5; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        sem_wait(&readerSemaphore);
        readCount++;
        if (readCount == 1) {
            sem_wait(&writeSemaphore);
        }
        sem_post(&readerSemaphore);

        std::cout << "Reader " << id << " is reading." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        sem_wait(&readerSemaphore);
        readCount--;
        if (readCount == 0) {
            sem_post(&writeSemaphore);
        }
        sem_post(&readerSemaphore);
    }
}

void writer(int id) {
    for (int i = 0; i < 5; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(150));

        sem_wait(&writeSemaphore);
        std::cout << "Writer " << id << " is writing." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        sem_post(&writeSemaphore);
    }
}

int main() {
    sem_init(&writeSemaphore, 0, 1);
    sem_init(&readerSemaphore, 0, 1);

    std::vector<std::thread> readers;
    std::vector<std::thread> writers;

    for (int i = 0; i < 3; ++i) {
        readers.emplace_back(reader, i);
        writers.emplace_back(writer, i);
    }

    for (auto& r : readers) r.join();
    for (auto& w : writers) w.join();

    sem_destroy(&writeSemaphore);
    sem_destroy(&readerSemaphore);

    return 0;
}
