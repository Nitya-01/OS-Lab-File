#include <iostream>
#include <unistd.h>
#include <pthread.h>

using namespace std;

// Function executed by the thread
void *thread_fun(void *arg) {
    cout << "Inside thread function" << endl;
    
    // Print numbers from 0 to 4 with a delay of 1 second
    for(int j = 0; j < 5; j++) {
        cout << j << endl;
        sleep(1);
    }
    
    // Exit the thread
    return NULL;
}

int main() {
    pthread_t thread1; // Declare a pthread variable
    
    // Create a thread
    pthread_create(&thread1, NULL, thread_fun, NULL);
    
    // Wait for the thread to finish (comment out to see the difference)
    pthread_join(thread1, NULL);
    
    cout << "Back to the main process" << endl;
    
    // Print numbers from 15 to 19 with a delay of 1 second
    for(int i = 15; i < 20; i++) {
        cout << i << endl;
        sleep(1);
    }
    
    return 0;
}
