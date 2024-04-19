// Demonstrates the creation of a child process using the fork() system call in C++ programming.
// The fork() system call creates a new process (child) which is a copy of the calling process (parent).
// Both the parent and child processes continue execution from the point of the fork() call, but they have separate memory spaces.

#include <iostream>
#include <unistd.h> // Required for fork() and getpid()

using namespace std;

int main() {
    pid_t pid; // Variable to store process ID

    // Call fork to create a new process
    pid = fork();

    if (pid < 0) {
        // Fork failed
        cout << "Fork failed!" << endl;
        return 1;
    } else if (pid == 0) {
        // Child process
        cout << "This is the child process." << endl;
        cout << "Child process ID: " << getpid() << endl;
        cout << "My Parent process ID: " << getppid() << endl;
    } else {
        // Parent process
        cout << "This is the parent process." << endl;
        cout << "Parent process ID: " << getpid() << endl;
        cout << "My Child process ID: " << pid << endl;
    }

    return 0;
}
