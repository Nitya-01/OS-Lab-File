#include <iostream>
#include <vector>

using namespace std;

// Function to check if the current state is safe or not
bool isSafe(const vector<vector<int>>& allocation, const vector<vector<int>>& maximum,
            const vector<int>& available) {
    int num_processes = allocation.size();
    int num_resources = available.size();

    // Vector to track if a process has finished
    vector<bool> finished(num_processes, false);

    // Vector to represent the available resources
    vector<int> work = available;

    // Counter for the number of processes finished
    int count = 0;

    // Iterate until all processes are finished or deadlock is detected
    while (count < num_processes) {
        bool found = false;

        // Iterate through each process
        for (int i = 0; i < num_processes; ++i) {
            if (!finished[i]) {
                // Flag to check if the process can execute with current available resources
                bool canExecute = true;

                // Check if the process's maximum needs can be satisfied with available resources
                for (int j = 0; j < num_resources; ++j) {
                    if (maximum[i][j] - allocation[i][j] > work[j]) {
                        // If not, mark the process as unable to execute
                        canExecute = false;
                        break;
                    }
                }

                if (canExecute) {
                    // If the process can execute, mark it as finished
                    found = true;
                    finished[i] = true;
                    ++count;

                    // Update the available resources
                    for (int j = 0; j < num_resources; ++j) {
                        work[j] += allocation[i][j];
                    }
                }
            }
        }

        if (!found) {
            // If no process can execute with current resources, deadlock detected
            return false;
        }
    }

    // No deadlock detected
    return true;
}

int main() {
    int num_processes, num_resources;

    // Input number of processes and resources
    cout << "Enter the number of processes: ";
    cin >> num_processes;
    cout << "Enter the number of resources: ";
    cin >> num_resources;

    // Input allocation matrix
    cout << "Enter the allocation matrix:" << endl;
    vector<vector<int>> allocation(num_processes, vector<int>(num_resources));
    for (int i = 0; i < num_processes; ++i) {
        cout << "Process " << i << ": ";
        for (int j = 0; j < num_resources; ++j) {
            cin >> allocation[i][j];
        }
    }

    // Input maximum matrix
    cout << "Enter the maximum matrix:" << endl;
    vector<vector<int>> maximum(num_processes, vector<int>(num_resources));
    for (int i = 0; i < num_processes; ++i) {
        cout << "Process " << i << ": ";
        for (int j = 0; j < num_resources; ++j) {
            cin >> maximum[i][j];
        }
    }

    // Input available resources
    cout << "Enter the available resources:" << endl;
    vector<int> available(num_resources);
    for (int j = 0; j < num_resources; ++j) {
        cin >> available[j];
    }

    // Check if the current state is safe using Banker's algorithm
    if (isSafe(allocation, maximum, available)) {
        cout << "Safe state. No deadlock possible." << endl;
    } else {
        cout << "Unsafe state. Deadlock possible." << endl;
    }

    return 0;
}
