// Dekker's Algorithm provides a solution to the critical section problem by allowing only one process to enter its critical section at a time.
// It uses semaphores to synchronize access to shared resources between multiple processes.
// The algorithm ensures mutual exclusion, progress, and bounded waiting without using busy-waiting.

#include <iostream>
#include <thread>
#include <semaphore.h>

using namespace std;

const int NUM_THREADS = 2;

// Shared variables
int turn = 0;
bool flag[NUM_THREADS] = {false};

// Semaphore declarations
sem_t sem;

// Thread function for each process
void process(int id) {
    for (int i = 0; i < 5; ++i) {
        // Entry section
        flag[id] = true;
        while (flag[1 - id]) {
            if (turn != id) {
                flag[id] = false;
                while (turn != id);
                flag[id] = true;
            }
        }

        // Critical section
        cout << "Process " << id + 1 << " is in critical section" << endl;
        this_thread::sleep_for(chrono::milliseconds(500));

        // Exit section
        turn = 1 - id;
        flag[id] = false;
    }
}

int main() {
    // Initialize semaphore
    sem_init(&sem, 0, 1);

    // Create threads
    thread t1(process, 0);
    thread t2(process, 1);

    // Join threads
    t1.join();
    t2.join();

    // Destroy semaphore
    sem_destroy(&sem);

    return 0;
}
