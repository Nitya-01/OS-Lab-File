// The First Come First Serve (FCFS) scheduling algorithm executes processes in the order they arrive in the ready queue.
// It uses a simple queue data structure to maintain the order of process arrival.
// FCFS is non-preemptive, meaning once a process starts executing, it continues until it finishes or blocks.

#include <iostream>
#include <vector>

using namespace std;

// Structure to represent a process
struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

// Function to implement First Come First Serve algorithm
void FCFS(vector<Process>& processes) {
    int n = processes.size();
    
    int currentTime = 0;
    for (int i = 0; i < n; ++i) {
        // If the current time is less than the arrival time of the process, move the current time forward
        if (currentTime < processes[i].arrival_time) {
            currentTime = processes[i].arrival_time;
        }

        // Update completion time, turnaround time, and waiting time for the process
        processes[i].completion_time = currentTime + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;

        // Update current time
        currentTime = processes[i].completion_time;
    }
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    cout << "Enter arrival time and burst time for each process:" << endl;
    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "Process " << processes[i].id << ":" << endl;
        cout << "Arrival time: ";
        cin >> processes[i].arrival_time;
        cout << "Burst time: ";
        cin >> processes[i].burst_time;
    }

    // Call the function to implement First Come First Serve algorithm
    FCFS(processes);

    // Display the results
    cout << "Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time" << endl;
    for (int i = 0; i < n; ++i) {
        cout << processes[i].id << "\t\t" << processes[i].arrival_time << "\t\t"
             << processes[i].burst_time << "\t\t" << processes[i].completion_time << "\t\t"
             << processes[i].turnaround_time << "\t\t" << processes[i].waiting_time << endl;
    }

    return 0;
}
