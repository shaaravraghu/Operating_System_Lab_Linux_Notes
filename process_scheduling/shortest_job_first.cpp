#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <climits>

struct Process {
    std::string id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    bool is_completed = false;
};

int main() {
    int n;
    std::cout << "Enter the number of processes: ";
    std::cin >> n;

    std::vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        std::cout << "Enter Process ID, Arrival Time, and Burst Time for process " << i + 1 << ": ";
        std::cin >> p[i].id >> p[i].arrival_time >> p[i].burst_time;
    }

    int completed = 0;
    int current_time = 0;
    std::vector<Process*> gantt_order;

    while (completed < n) {
        int idx = -1;
        int min_burst = INT_MAX;

        // Step 4.1: Find process with min Burst Time among arrived & uncompleted processes
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && !p[i].is_completed) {
                if (p[i].burst_time < min_burst) {
                    min_burst = p[i].burst_time;
                    idx = i;
                }
                // If burst times are equal, tie-break with Arrival Time
                else if (p[i].burst_time == min_burst) {
                    if (p[i].arrival_time < p[idx].arrival_time) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            // Step 4.3: Execute process
            current_time += p[idx].burst_time;
            p[idx].completion_time = current_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            p[idx].is_completed = true;
            completed++;
            gantt_order.push_back(&p[idx]);
        } else {
            // Step 4.2: Idle time if no process has arrived yet
            current_time++;
        }
    }

    // Calculations for Averages
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
    for (auto proc : gantt_order) {
        std::cout << "  " << proc->id << "  |";
    }
    std::cout << "\n0";
    for (auto proc : gantt_order) {
        std::cout << std::setw(7) << proc->completion_time;
    }

    std::cout << "\n\nAverage Waiting Time: " << (total_wt / n) << " ms";
    std::cout << "\nAverage Turnaround Time: " << (total_tat / n) << " ms" << std::endl;

    return 0;
}
