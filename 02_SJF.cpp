#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

bool compareArrivalTime(const Process& p1, const Process& p2) {
    return p1.arrival_time < p2.arrival_time;
}

bool compareBurstTime(const Process& p1, const Process& p2) {
    return p1.burst_time < p2.burst_time;
}

void SJF(vector<Process>& processes) {
    int n = processes.size();
    sort(processes.begin(), processes.end(), compareArrivalTime);

    int currentTime = 0;
    for (int i = 0; i < n; ++i) {
        if (currentTime < processes[i].arrival_time) {
            currentTime = processes[i].arrival_time;
        }

        processes[i].completion_time = currentTime + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;

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

    SJF(processes);

    cout << "Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time" << endl;
    for (int i = 0; i < n; ++i) {
        cout << processes[i].id << "\t\t" << processes[i].arrival_time << "\t\t"
             << processes[i].burst_time << "\t\t" << processes[i].completion_time << "\t\t"
             << processes[i].turnaround_time << "\t\t" << processes[i].waiting_time << endl;
    }

    return 0;
}
