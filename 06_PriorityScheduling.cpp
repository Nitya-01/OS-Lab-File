// The Priority Scheduling algorithm assigns a priority to each process, and the process with the highest priority is selected for execution.
// It uses a priority queue or sorting mechanism to prioritize processes based on their priorities.
// Priority can be defined based on various factors such as process importance, deadline, or other criteria.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent a process
struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

// Comparison function for sorting processes based on arrival time
bool sortByArrivalTime(const Process& p1, const Process& p2) {
    return p1.arrival_time < p2.arrival_time;
}

// Function to implement Priority Scheduling algorithm
void PriorityScheduling(vector<Process>& processes) {
    int num_processes = processes.size();
    sort(processes.begin(), processes.end(), sortByArrivalTime);

    int current_time = 0;
    vector<bool> is_completed(num_processes, false);

    // Process each job in the order of their arrival
    while (true) {
        int highest_priority = -1;
        int highest_priority_index = -1;

        // Find the process with the highest priority that has arrived and not completed
        for (int i = 0; i < num_processes; ++i) {
            if (!is_completed[i] && processes[i].arrival_time <= current_time) {
                if (highest_priority == -1 || processes[i].priority < highest_priority) {
                    highest_priority = processes[i].priority;
                    highest_priority_index = i;
                }
            }
        }

        // If no process is found, break the loop
        if (highest_priority_index == -1) {
            break;
        }

        // Execute the process
        Process& current_process = processes[highest_priority_index];
        current_process.completion_time = current_time + current_process.burst_time;
        current_process.turnaround_time = current_process.completion_time - current_process.arrival_time;
        current_process.waiting_time = current_process.turnaround_time - current_process.burst_time;

        // Update current time and mark the process as completed
        current_time = current_process.completion_time;
        is_completed[highest_priority_index] = true;
    }
}

int main() {
    int num_processes;
    cout << "Enter the number of processes: ";
    cin >> num_processes;

    // Input arrival time, burst time, and priority for each process
    vector<Process> processes(num_processes);
    cout << "Enter arrival time, burst time, and priority for each process:" << endl;
    for (int i = 0; i < num_processes; ++i) {
        processes[i].id = i + 1;
        cout << "Process " << processes[i].id << ":" << endl;
        cout << "Arrival time: ";
        cin >> processes[i].arrival_time;
        cout << "Burst time: ";
        cin >> processes[i].burst_time;
        cout << "Priority: ";
        cin >> processes[i].priority;
    }

    // Call the function to implement Priority Scheduling algorithm
    PriorityScheduling(processes);

    // Display the results
    cout << "Process\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time" << endl;
    for (int i = 0; i < num_processes; ++i) {
        cout << processes[i].id << "\t\t" << processes[i].arrival_time << "\t\t"
             << processes[i].burst_time << "\t\t" << processes[i].priority << "\t\t"
             << processes[i].completion_time << "\t\t" << processes[i].turnaround_time << "\t\t" << processes[i].waiting_time << endl;
    }

    return 0;
}
