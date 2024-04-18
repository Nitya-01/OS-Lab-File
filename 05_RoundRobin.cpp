#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Structure to represent a process
struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time; // Time remaining for the process to complete
    int completion_time; // Time when the process completes execution
    int turnaround_time; // Time taken from arrival to completion
    int waiting_time; // Time spent waiting in the ready queue
};

// Function to implement Round Robin algorithm
void RoundRobin(vector<Process>& processes, int quantum) {
    int n = processes.size();
    queue<Process> ready_queue;
    int currentTime = 0;

    // Push processes into the ready queue in the order of their arrival
    for (int i = 0; i < n; ++i) {
        ready_queue.push(processes[i]);
    }

    // Process until the ready queue is empty
    while (!ready_queue.empty()) {
        Process current_process = ready_queue.front();
        ready_queue.pop();

        // If the process arrives after the current time, wait until it arrives
        if (currentTime < current_process.arrival_time) {
            currentTime = current_process.arrival_time;
        }

        // Execute the process for the time quantum or until it completes
        int execution_time = min(quantum, current_process.remaining_time);
        current_process.remaining_time -= execution_time;
        currentTime += execution_time;

        // If the process is not completed, push it back into the ready queue
        if (current_process.remaining_time > 0) {
            ready_queue.push(current_process);
        } else {
            // If the process is completed, calculate completion time, turnaround time, and waiting time
            current_process.completion_time = currentTime;
            current_process.turnaround_time = current_process.completion_time - current_process.arrival_time;
            current_process.waiting_time = current_process.turnaround_time - current_process.burst_time;
        }
    }
}

int main() {
    int n, quantum;
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
        processes[i].remaining_time = processes[i].burst_time;
    }

    cout << "Enter time quantum: ";
    cin >> quantum;

    // Call the function to implement Round Robin algorithm
    RoundRobin(processes, quantum);

    // Display the results
    cout << "Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time" << endl;
    for (int i = 0; i < n; ++i) {
        cout << processes[i].id << "\t\t" << processes[i].arrival_time << "\t\t"
             << processes[i].burst_time << "\t\t" << processes[i].completion_time << "\t\t"
             << processes[i].turnaround_time << "\t\t" << processes[i].waiting_time << endl;
    }

    return 0;
}
