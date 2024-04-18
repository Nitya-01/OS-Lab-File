// The Shortest Remaining Time First (SRTF) scheduling algorithm is a preemptive version of SJF.
// It continuously checks for the shortest remaining time among the ready processes and switches execution 
// to the one with the shortest remaining time if a new process arrives with a shorter burst time.

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Structure to represent a process
struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time; // Remaining time needed to complete the process
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

// Comparison function for sorting processes based on arrival time
bool compareArrivalTime(const Process& p1, const Process& p2) {
    return p1.arrival_time < p2.arrival_time;
}

// Comparison function for sorting processes based on remaining time
bool compareRemainingTime(const Process& p1, const Process& p2) {
    return p1.remaining_time < p2.remaining_time;
}

// Function to implement Shortest Remaining Time First algorithm
void SRTF(vector<Process>& processes) {
    int n = processes.size();
    // Sort processes based on arrival time
    sort(processes.begin(), processes.end(), compareArrivalTime);

    int currentTime = 0;
    int completedProcesses = 0;
    vector<bool> completed(n, false);

    // Process until all processes are completed
    while (completedProcesses < n) {
        int minRemainingTime = INT_MAX;
        int shortestIndex = -1;

        // Find the process with the shortest remaining time
        for (int i = 0; i < n; ++i) {
            if (!completed[i] && processes[i].arrival_time <= currentTime && processes[i].remaining_time < minRemainingTime) {
                minRemainingTime = processes[i].remaining_time;
                shortestIndex = i;
            }
        }

        // If no process is found at the current time, move to the next time unit
        if (shortestIndex == -1) {
            currentTime++;
            continue;
        }

        // Decrement the remaining time for the selected process
        processes[shortestIndex].remaining_time--;

        // If the process is completed, update its completion time and other metrics
        if (processes[shortestIndex].remaining_time == 0) {
            completedProcesses++;
            completed[shortestIndex] = true;
            processes[shortestIndex].completion_time = currentTime + 1;
            processes[shortestIndex].turnaround_time = processes[shortestIndex].completion_time - processes[shortestIndex].arrival_time;
            processes[shortestIndex].waiting_time = processes[shortestIndex].turnaround_time - processes[shortestIndex].burst_time;
        }

        currentTime++;
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
        processes[i].remaining_time = processes[i].burst_time;
    }

    // Call the function to implement Shortest Remaining Time First algorithm
    SRTF(processes);

    // Display the results
    cout << "Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time" << endl;
    for (int i = 0; i < n; ++i) {
        cout << processes[i].id << "\t\t" << processes[i].arrival_time << "\t\t"
             << processes[i].burst_time << "\t\t" << processes[i].completion_time << "\t\t"
             << processes[i].turnaround_time << "\t\t" << processes[i].waiting_time << endl;
    }

    return 0;
}
