#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
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

// Function to print Gantt Chart
void printGanttChart(const vector<Process> &ganttChart) {
    cout << "\nGantt Chart:\n";

    // Print process representation
    for (const auto &process : ganttChart) {
        cout << "| " << setw(8) << "P" << process.id;
    }
    cout << "|"; // Close Gantt chart line

    // New line for time markers
    cout << "\n";

    // Print starting time
    cout << setw(1) << "0"; 

    // Print completion times
    int currentTime = 0;
    for (const auto &process : ganttChart) {
        currentTime += process.burstTime;
        cout << setw(8) << currentTime; // Print end time of each process
    }
    cout << endl; // New line after printing all times
}

// Priority Non-Preemptive Scheduling Function
void priorityNonPreemptive(vector<Process> &processes) {
    int n = processes.size();
    vector<int> isCompleted(n, 0);
    vector<Process> ganttChart; // To store the order of execution
    double totalWT = 0, totalTAT = 0;
    int currentTime = 0, completed = 0;

    while (completed < n) {
        int idx = -1;
        int lowestPriority = numeric_limits<int>::max(); // Initialize to max value

        // Find the lowest priority process that has arrived
        for (int i = 0; i < n; ++i) {
            if (processes[i].arrivalTime <= currentTime && !isCompleted[i]) {
                if (processes[i].priority < lowestPriority) { // Change the comparison here
                    lowestPriority = processes[i].priority;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            ganttChart.push_back(processes[idx]); // Add to Gantt chart
            currentTime += processes[idx].burstTime;
            processes[idx].completionTime = currentTime;
            processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
            processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
            totalWT += processes[idx].waitingTime;
            totalTAT += processes[idx].turnaroundTime;
            isCompleted[idx] = 1;
            completed++;
        } else {
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
    }

    priorityNonPreemptive(processes);

    return 0;
}
