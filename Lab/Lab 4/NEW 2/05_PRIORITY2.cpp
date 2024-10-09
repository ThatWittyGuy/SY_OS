#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <limits>
using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int priority;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
};

// Function to print the process table and calculate average times
void printProcessTable(const vector<Process> &processes, double avgWT, double avgTAT) {
    cout << "\nProcess Table:\n";
    cout << setw(5) << "ID" 
         << setw(15) << "Arrival Time" 
         << setw(15) << "Burst Time"
         << setw(10) << "Priority" 
         << setw(20) << "Completion Time"
         << setw(15) << "Waiting Time" 
         << setw(20) << "Turnaround Time" 
         << endl;

    for (const auto &p : processes) {
        cout << setw(5) << p.id 
             << setw(15) << p.arrivalTime 
             << setw(15) << p.burstTime
             << setw(10) << p.priority 
             << setw(20) << p.completionTime
             << setw(15) << p.waitingTime 
             << setw(20) << p.turnaroundTime 
             << endl;
    }

    cout << "\nAverage Waiting Time: " << avgWT << endl;
    cout << "Average Turnaround Time: " << avgTAT << endl;
}

// Function to print the Gantt chart
void printGanttChart(const vector<pair<int, int>> &ganttChart) {
    cout << "\nGantt Chart:\n";
    
    // Print process IDs with grouping
    for (size_t i = 0; i < ganttChart.size(); ++i) {
        if (i == 0 || ganttChart[i].first != ganttChart[i - 1].first) {
            // Print the previous entry's duration if it's not the first entry
            if (i > 0 && ganttChart[i - 1].first != -1) {
                cout << "| ";
                cout << std::setw(ganttChart[i - 1].second * 4 + 1) // Adjust width based on duration
                     << "P" << ganttChart[i - 1].first; // Print process ID
                cout << " ";
            } else if (i > 0 && ganttChart[i - 1].first == -1) {
                cout << "| ";
                cout << std::setw(ganttChart[i - 1].second * 4 + 1)
                     << "Idle"; // Print idle time
                cout << " ";
            }
        }
        
        // Handle last entry separately
        if (i == ganttChart.size() - 1) {
            if (ganttChart[i].first != -1)
                cout << "| " 
                     << std::setw(ganttChart[i].second * 4 + 1)
                     << "P" << ganttChart[i].first; // Print last process ID
            else
                cout << "| "
                     << std::setw(ganttChart[i].second * 4 + 1)
                     << "Idle"; // Print last idle time
        }
    }
    
    cout << "|" << endl;

    cout << "0  " ;
    // Print time line, only at end of blocks
    int time = 0;
    for (size_t i = 0; i < ganttChart.size(); ++i) {
        time += ganttChart[i].second; // Increment time by burst time

        // Only print the time at the end of each block
        if (i == 0 || ganttChart[i].first != ganttChart[i - 1].first || i == ganttChart.size() - 1) {
            cout << time; // Print end time for processes or idle periods
            cout << "   | "; // Separator for each time unit
        }
    }

    cout << endl;
}

// Priority Preemptive Scheduling Function
void priorityPreemptive(vector<Process> &processes) {
    int n = processes.size();
    vector<int> isCompleted(n, 0);
    vector<pair<int, int>> ganttChart; // To store (process ID, burst time)
    double totalWT = 0, totalTAT = 0;
    int currentTime = 0, completed = 0;

    while (completed < n) {
        int idx = -1;
        int lowestPriority = numeric_limits<int>::max(); // Initialize to max value

        // Find the process with the lowest priority that has arrived and is not completed
        for (int i = 0; i < n; ++i) {
            if (processes[i].arrivalTime <= currentTime && !isCompleted[i]) {
                if (processes[i].priority < lowestPriority) { // Change the comparison here
                    lowestPriority = processes[i].priority;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            // Execute the process for 1 time unit
            processes[idx].remainingTime--;
            ganttChart.push_back({processes[idx].id, 1}); // Record this process for Gantt chart
            currentTime++;

            // If the process is completed
            if (processes[idx].remainingTime == 0) {
                processes[idx].completionTime = currentTime;
                processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
                processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
                totalWT += processes[idx].waitingTime;
                totalTAT += processes[idx].turnaroundTime;
                isCompleted[idx] = 1;
                completed++;
            }
        } else {
            // If no process is ready, increment time
            ganttChart.push_back({-1, 1}); // Indicate idle time
            currentTime++;
        }
    }

    double avgWT = totalWT / n;
    double avgTAT = totalTAT / n;

    // Print Gantt chart
    printGanttChart(ganttChart);
    
    // Print process table
    printProcessTable(processes, avgWT, avgTAT);
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "Enter arrival time, burst time, and priority for process P" << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime >> processes[i].priority;
        processes[i].remainingTime = processes[i].burstTime;
    }

    priorityPreemptive(processes);

    return 0;
}
