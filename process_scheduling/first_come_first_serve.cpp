#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

struct Process {
    std::string id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

// Comparator to sort processes by Arrival Time
bool compareArrival(const Process &a, const Process &b) {
    return a.arrival_time < b.arrival_time;
}

int main() {
    int n;
    std::cout << "Enter the number of processes: ";
    std::cin >> n;

    std::vector<Process> p(n);

    for (int i = 0; i < n; i++) {
        std::cout << "Enter Process ID, Arrival Time, and Burst Time for process " << i + 1 << ": ";
        std::cin >> p[i].id >> p[i].arrival_time >> p[i].burst_time;
    }

    // Step 3: Sort processes by Arrival Time
    std::sort(p.begin(), p.end(), compareArrival);

    // Step 4 & 5: Calculate Completion Time (CT)
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            p[i].completion_time = p[i].arrival_time + p[i].burst_time;
        } else {
            // Check if CPU is idle (CT of previous < AT of current)
            if (p[i-1].completion_time < p[i].arrival_time) {
                p[i].completion_time = p[i].arrival_time + p[i].burst_time;
            } else {
                p[i].completion_time = p[i-1].completion_time + p[i].burst_time;
            }
        }

        // Step 6: Calculate TAT and WT
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
    }

    // Calculate Averages
    double total_wt = 0, total_tat = 0;
    for (const auto &proc : p) {
        total_wt += proc.waiting_time;
        total_tat += proc.turnaround_time;
    }

    // Display Results Table
    std::cout << "\n" << std::left << std::setw(10) << "PID" 
              << std::setw(10) << "AT" << std::setw(10) << "BT" 
              << std::setw(10) << "CT" << std::setw(10) << "TAT" 
              << std::setw(10) << "WT" << std::endl;
    
    for (const auto &proc : p) {
        std::cout << std::left << std::setw(10) << proc.id 
                  << std::setw(10) << proc.arrival_time << std::setw(10) << proc.burst_time 
                  << std::setw(10) << proc.completion_time << std::setw(10) << proc.turnaround_time 
                  << std::setw(10) << proc.waiting_time << std::endl;
    }

    // Display Gantt Chart
    std::cout << "\n--- Gantt Chart ---\n|";
    for (int i = 0; i < n; i++) {
        std::cout << "  " << p[i].id << "  |";
    }
    std::cout << "\n0";
    for (int i = 0; i < n; i++) {
        std::cout << std::setw(7) << p[i].completion_time;
    }

    std::cout << "\n\nAverage Waiting Time: " << total_wt / n << " ms";
    std::cout << "\nAverage Turnaround Time: " << total_tat / n << " ms" << std::endl;

    return 0;
}
