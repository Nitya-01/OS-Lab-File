#include <iostream>
#include <unistd.h> // Required for fork() and getpid()

using namespace std;

int main() {
    pid_t pid; // Variable to store process ID

    // Call fork to create a new process
    pid = fork();

    if (pid < 0) {
        // Fork failed
        cerr << "Fork failed!" << endl;
        return 1;
    } else if (pid == 0) {
        // Child process
        cout << "This is the child process." << endl;
        cout << "Child process ID: " << getpid() << endl;
    } else {
        // Parent process
        cout << "This is the parent process." << endl;
        cout << "Parent process ID: " << getpid() << endl;
        cout << "Child process ID: " << pid << endl;
    }

    return 0;
}
