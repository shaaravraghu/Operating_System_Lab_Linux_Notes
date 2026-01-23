#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <climits>

struct Process {
    std::string id;
    int arrival_time;
    int burst_time;
    int remaining_time;
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
        p[i].remaining_time = p[i].burst_time;
    }

    int completed = 0;
    int current_time = 0;
    std::string last_pid = "";
    std::vector<std::pair<std::string, int>> gantt_chart;

    while (completed < n) {
        int idx = -1;
        int min_remaining = INT_MAX;

        // Step 4.1: Find process with minimum remaining time at current_time
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && !p[i].is_completed) {
                if (p[i].remaining_time < min_remaining) {
                    min_remaining = p[i].remaining_time;
                    idx = i;
                }
                // Tie-breaker: earlier arrival time
                if (p[i].remaining_time == min_remaining) {
                    if (p[i].arrival_time < p[idx].arrival_time) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            // Track for Gantt Chart (whenever process changes)
            if (p[idx].id != last_pid) {
                gantt_chart.push_back({p[idx].id, current_time});
                last_pid = p[idx].id;
            }

            // Step 4.3: Execute for 1 time unit
            p[idx].remaining_time--;
            current_time++;

            // Step 4.4: Check if finished
            if (p[idx].remaining_time == 0) {
                p[idx].completion_time = current_time;
                p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
                p[idx].is_completed = true;
                completed++;
                last_pid = ""; // Reset for next selection
            }
        } else {
            // Step 4.2: Idle time
            current_time++;
        }
    }

    // Averages
    double total_wt = 0, total_tat = 0;
    for (const auto &proc : p) {
        total_wt += proc.waiting_time;
        total_tat += proc.turnaround_time;
    }

    // Display Results
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
    for (auto const& [id, time] : gantt_chart) {
        std::cout << "  " << id << "  |";
    }
    std::cout << "\n";
    for (auto const& [id, time] : gantt_chart) {
        std::cout << time << "      ";
    }
    std::cout << current_time << std::endl;

    std::cout << "\nAverage Waiting Time: " << (total_wt / n) << " ms";
    std::cout << "\nAverage Turnaround Time: " << (total_tat / n) << " ms" << std::endl;

    return 0;
}
