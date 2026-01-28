#include <iostream>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <vector>
using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

// Structure to store execution details
struct ExecutionStep {
    int processId;
    int startTime;
    int endTime;
    int remainingTime;
};

// Function to compare processes by arrival time
bool compareArrival(Process a, Process b) {
    if (a.arrivalTime == b.arrivalTime)
        return a.id < b.id;
    return a.arrivalTime < b.arrivalTime;
}

void roundRobinScheduling(Process processes[], int n, int timeQuantum, vector<ExecutionStep>& executionLog) {
    // Sort processes by arrival time
    sort(processes, processes + n, compareArrival);
    
    queue<int> readyQueue;
    int currentTime = 0;
    int completed = 0;
    bool* inQueue = new bool[n];
    
    // Initialize inQueue array
    for (int i = 0; i < n; i++) {
        inQueue[i] = false;
    }
    
    cout << "\n========================================\n";
    cout << "        EXECUTION VISUALIZATION         \n";
    cout << "========================================\n\n";
    
    // Add processes that arrive at time 0
    for (int i = 0; i < n; i++) {
        if (processes[i].arrivalTime == 0) {
            readyQueue.push(i);
            inQueue[i] = true;
            cout << "Time " << currentTime << ": P" << processes[i].id << " added to ready queue\n";
        }
    }
    
    // Main scheduling loop
    while (completed < n) {
        // If ready queue is empty, advance time
        if (readyQueue.empty()) {
            cout << "\nTime " << currentTime << ": CPU is IDLE (no process ready)\n";
            
            // Find next process to arrive
            int nextArrival = -1;
            for (int i = 0; i < n; i++) {
                if (processes[i].remainingTime > 0) {
                    if (nextArrival == -1 || processes[i].arrivalTime < processes[nextArrival].arrivalTime) {
                        nextArrival = i;
                    }
                }
            }
            
            if (nextArrival != -1) {
                currentTime = processes[nextArrival].arrivalTime;
                readyQueue.push(nextArrival);
                inQueue[nextArrival] = true;
                cout << "Time " << currentTime << ": P" << processes[nextArrival].id << " arrives and added to ready queue\n";
            }
            continue;
        }
        
        // Display ready queue status
        cout << "\n--- Ready Queue: [";
        queue<int> tempQueue = readyQueue;
        while (!tempQueue.empty()) {
            cout << "P" << processes[tempQueue.front()].id;
            tempQueue.pop();
            if (!tempQueue.empty()) cout << ", ";
        }
        cout << "] ---\n";
        
        // Get process from front of queue
        int currentProcess = readyQueue.front();
        readyQueue.pop();
        inQueue[currentProcess] = false;
        
        int startTime = currentTime;
        int executionTime = 0;
        
        // Execute process
        if (processes[currentProcess].remainingTime > timeQuantum) {
            // Execute for time quantum
            executionTime = timeQuantum;
            currentTime += timeQuantum;
            processes[currentProcess].remainingTime -= timeQuantum;
            
            cout << "\nTime " << startTime << " - " << currentTime << ": P" << processes[currentProcess].id 
                 << " is RUNNING (executed " << executionTime << " units)\n";
            cout << "               Remaining time: " << processes[currentProcess].remainingTime << " units\n";
        } else {
            // Execute for remaining time
            executionTime = processes[currentProcess].remainingTime;
            currentTime += processes[currentProcess].remainingTime;
            processes[currentProcess].remainingTime = 0;
            processes[currentProcess].completionTime = currentTime;
            completed++;
            
            cout << "\nTime " << startTime << " - " << currentTime << ": P" << processes[currentProcess].id 
                 << " is RUNNING (executed " << executionTime << " units)\n";
            cout << "               Process COMPLETED!\n";
        }
        
        // Store execution step
        ExecutionStep step;
        step.processId = processes[currentProcess].id;
        step.startTime = startTime;
        step.endTime = currentTime;
        step.remainingTime = processes[currentProcess].remainingTime;
        executionLog.push_back(step);
        
        // Add newly arrived processes to ready queue
        bool newArrivals = false;
        for (int i = 0; i < n; i++) {
            if (!inQueue[i] && 
                processes[i].arrivalTime <= currentTime && 
                processes[i].remainingTime > 0 &&
                i != currentProcess) {
                readyQueue.push(i);
                inQueue[i] = true;
                if (!newArrivals) {
                    cout << "\n  New arrivals: ";
                    newArrivals = true;
                }
                cout << "P" << processes[i].id << " ";
            }
        }
        if (newArrivals) cout << "added to ready queue\n";
        
        // Add current process back to queue if not finished
        if (processes[currentProcess].remainingTime > 0) {
            readyQueue.push(currentProcess);
            inQueue[currentProcess] = true;
            cout << "  P" << processes[currentProcess].id << " moved to end of ready queue\n";
        }
    }
    
    cout << "\n========================================\n";
    cout << "     ALL PROCESSES COMPLETED!           \n";
    cout << "========================================\n";
    
    delete[] inQueue;
}

void calculateTimes(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        // Turnaround Time = Completion Time - Arrival Time
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        
        // Waiting Time = Turnaround Time - Burst Time
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
    }
}

void displayGanttChart(vector<ExecutionStep>& executionLog) {
    cout << "\n========================================\n";
    cout << "           GANTT CHART                  \n";
    cout << "========================================\n\n";
    
    // Display process boxes
    cout << "|";
    for (const auto& step : executionLog) {
        cout << " P" << step.processId << " |";
    }
    cout << "\n";
    
    // Display timeline
    cout << executionLog[0].startTime;
    for (const auto& step : executionLog) {
        int width = 4;
        for (int i = 0; i < width; i++) cout << " ";
        cout << step.endTime;
    }
    cout << "\n";
}

void displayResults(Process processes[], int n) {
    cout << "\n========================================\n";
    cout << "          SCHEDULING RESULTS           \n";
    cout << "========================================\n\n";
    
    cout << left << setw(10) << "Process" 
         << setw(12) << "Arrival" 
         << setw(12) << "Burst" 
         << setw(14) << "Completion"
         << setw(12) << "Waiting" 
         << setw(14) << "Turnaround" << endl;
    cout << "------------------------------------------------------------------------\n";
    
    double totalWaitingTime = 0;
    double totalTurnaroundTime = 0;
    
    for (int i = 0; i < n; i++) {
        cout << left << setw(10) << ("P" + to_string(processes[i].id))
             << setw(12) << processes[i].arrivalTime
             << setw(12) << processes[i].burstTime
             << setw(14) << processes[i].completionTime
             << setw(12) << processes[i].waitingTime
             << setw(14) << processes[i].turnaroundTime << endl;
        
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }
    
    cout << "------------------------------------------------------------------------\n";
    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << totalWaitingTime / n << endl;
    cout << "Average Turnaround Time: " << totalTurnaroundTime / n << endl;
    cout << "\n========================================\n";
}

int main() {
    int n, timeQuantum;
    vector<ExecutionStep> executionLog;
    
    cout << "========================================\n";
    cout << "   ROUND ROBIN CPU SCHEDULING ALGORITHM\n";
    cout << "========================================\n\n";
    
    cout << "Enter the number of processes: ";
    cin >> n;
    
    Process* processes = new Process[n];
    
    cout << "\nEnter details for each process:\n";
    cout << "--------------------------------\n";
    
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "\nProcess P" << (i + 1) << ":\n";
        cout << "  Arrival Time: ";
        cin >> processes[i].arrivalTime;
        cout << "  Burst Time: ";
        cin >> processes[i].burstTime;
        
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].completionTime = 0;
        processes[i].turnaroundTime = 0;
        processes[i].waitingTime = 0;
    }
    
    cout << "\nEnter Time Quantum: ";
    cin >> timeQuantum;
    
    // Perform Round Robin Scheduling with visualization
    roundRobinScheduling(processes, n, timeQuantum, executionLog);
    
    // Display Gantt Chart
    displayGanttChart(executionLog);
    
    // Calculate waiting and turnaround times
    calculateTimes(processes, n);
    
    // Display results
    displayResults(processes, n);
    
    delete[] processes;
    
    return 0;
}
