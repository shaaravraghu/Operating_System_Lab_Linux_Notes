#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

struct Process {
    string pid;
    int arrival;
    int burst;
    int remaining;
    int completion = 0;
    int turnaround = 0;
    int waiting = 0;
    int lastQueueEnter = 0;
    int currentQueue = 1;
};

int main() {

    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    cout << "Enter Process ID, Arrival Time, Burst Time:\n";

    for(int i = 0; i < n; i++) {
        cin >> processes[i].pid 
            >> processes[i].arrival 
            >> processes[i].burst;

        processes[i].remaining = processes[i].burst;
    }

    // Sort by arrival time
    sort(processes.begin(), processes.end(),
        [](Process a, Process b){
            return a.arrival < b.arrival;
        });

    queue<int> Q1, Q2, Q3;
    vector<bool> added(n, false);

    int time = 0;
    int completed = 0;

    cout << "\n========= GANTT CHART =========\n\n";

    while(completed < n) {

        // Add arriving processes to Q1
        for(int i = 0; i < n; i++) {
            if(processes[i].arrival <= time &&
               processes[i].remaining > 0 &&
               !added[i]) {

                Q1.push(i);
                processes[i].currentQueue = 1;
                processes[i].lastQueueEnter = time;
                added[i] = true;
            }
        }

        // Aging mechanism
        for(int i = 0; i < n; i++) {
            if(processes[i].remaining > 0) {

                if(processes[i].currentQueue == 2 &&
                   time - processes[i].lastQueueEnter > 20) {

                    Q1.push(i);
                    processes[i].currentQueue = 1;
                    processes[i].lastQueueEnter = time;
                }

                else if(processes[i].currentQueue == 3 &&
                        time - processes[i].lastQueueEnter > 20) {

                    Q2.push(i);
                    processes[i].currentQueue = 2;
                    processes[i].lastQueueEnter = time;
                }
            }
        }

        int idx = -1;
        int quantum = 0;
        int executingQueue = 0;

        if(!Q1.empty()) {
            idx = Q1.front(); Q1.pop();
            quantum = 4;
            executingQueue = 1;
        }
        else if(!Q2.empty()) {
            idx = Q2.front(); Q2.pop();
            quantum = 8;
            executingQueue = 2;
        }
        else if(!Q3.empty()) {
            idx = Q3.front(); Q3.pop();
            quantum = processes[idx].remaining; // FCFS
            executingQueue = 3;
        }

        if(idx == -1) {
            time++;
            continue;
        }

        int startTime = time;
        int execTime = min(quantum, processes[idx].remaining);

        processes[idx].remaining -= execTime;
        time += execTime;

        int endTime = time;

        // Print execution block with timestamps
        cout << startTime << " - "
             << endTime << " : "
             << processes[idx].pid
             << " (Q" << executingQueue << ")\n";

        if(processes[idx].remaining == 0) {
            processes[idx].completion = time;
            completed++;
        }
        else {
            if(executingQueue == 1) {
                Q2.push(idx);
                processes[idx].currentQueue = 2;
            }
            else if(executingQueue == 2) {
                Q3.push(idx);
                processes[idx].currentQueue = 3;
            }
            else {
                Q3.push(idx);
            }

            processes[idx].lastQueueEnter = time;
        }
    }

    double totalWT = 0, totalTAT = 0;

    cout << "\n========= PROCESS TABLE =========\n\n";
    cout << "PID\tAT\tBT\tCT\tTAT\tWT\n";

    for(int i = 0; i < n; i++) {

        processes[i].turnaround =
            processes[i].completion - processes[i].arrival;

        processes[i].waiting =
            processes[i].turnaround - processes[i].burst;

        totalWT += processes[i].waiting;
        totalTAT += processes[i].turnaround;

        cout << processes[i].pid << "\t"
             << processes[i].arrival << "\t"
             << processes[i].burst << "\t"
             << processes[i].completion << "\t"
             << processes[i].turnaround << "\t"
             << processes[i].waiting << "\n";
    }

    cout << "\nAverage Waiting Time: "
         << totalWT / n << endl;

    cout << "Average Turnaround Time: "
         << totalTAT / n << endl;

    return 0;
}
