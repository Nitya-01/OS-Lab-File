// The Reader-Writer Problem is a classic synchronization problem where multiple readers can read a shared resource simultaneously, but exclusive access is required for writing.
// This implementation uses semaphores to control access to the shared resource, ensuring that readers can access it concurrently while writers have exclusive access.
// Semaphores are used to manage the number of readers accessing the resource and to ensure mutual exclusion for writers.

#include <iostream>
#include <thread>
#include <semaphore.h>

using namespace std;

// Shared variables
int readersCount = 0;
sem_t mutex, rwMutex;

// Reader function
void reader(int id) {
    while (true) {
        // Entry section for reader
        sem_wait(&mutex);
        readersCount++;
        if (readersCount == 1) {
            sem_wait(&rwMutex);
        }
        sem_post(&mutex);

        // Reading section
        cout << "Reader " << id << " is reading" << endl;
        this_thread::sleep_for(chrono::milliseconds(500));

        // Exit section for reader
        sem_wait(&mutex);
        readersCount--;
        if (readersCount == 0) {
            sem_post(&rwMutex);
        }
        sem_post(&mutex);

        // Sleep to simulate idle time
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

// Writer function
void writer(int id) {
    while (true) {
        // Entry section for writer
        sem_wait(&rwMutex);

        // Writing section
        cout << "Writer " << id << " is writing" << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));

        // Exit section for writer
        sem_post(&rwMutex);

        // Sleep to simulate idle time
        this_thread::sleep_for(chrono::milliseconds(2000));
    }
}

int main() {
    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&rwMutex, 0, 1);

    // Create reader threads
    thread readers[3];
    for (int i = 0; i < 3; ++i) {
        readers[i] = thread(reader, i + 1);
    }

    // Create writer threads
    thread writers[2];
    for (int i = 0; i < 2; ++i) {
        writers[i] = thread(writer, i + 1);
    }

    // Join reader threads
    for (int i = 0; i < 3; ++i) {
        readers[i].join();
    }

    // Join writer threads
    for (int i = 0; i < 2; ++i) {
        writers[i].join();
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&rwMutex);

    return 0;
}
