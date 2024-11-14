// Priority Preemptive in CPP

#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <climits>

using namespace std;

struct Process {
    int id, arrivalTime, burstTime, remainingTime, priority, completionTime, waitingTime, turnaroundTime;
};

void printProcessTable(const vector<Process>& processes, double avgWT, double avgTAT) {
    cout << "\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (const auto& p : processes) {
        cout << "P" << p.id << "\t" << p.arrivalTime << "\t" << p.burstTime << "\t"
             << p.completionTime << "\t\t" << p.turnaroundTime << "\t\t" << p.waitingTime << "\n";
    }
    cout << "The average Waiting time : " << avgWT << "\n";
    cout << "The average Turnaround time : " << avgTAT << "\n";
}

void printGanttChart(const vector<pair<int, int>>& ganttChart) {
    cout << "\nGantt Chart:\n";
    int time = 0;
    
for (size_t i = 0; i < ganttChart.size(); ++i) {
    time += ganttChart[i].second;
    if (i == ganttChart.size() - 1 || ganttChart[i].first != ganttChart[i + 1].first) {
        cout << "| " << setw(4)
             << (ganttChart[i].first == -1 ? "Idle" : "P" + to_string(ganttChart[i].first)) << " ";
    }
}

    cout << " |" << endl;
    
    time = 0;
    for (size_t i = 0; i < ganttChart.size(); ++i) {
        if (i == 0) {
            cout << 0; 
        }
        time += ganttChart[i].second;
        if (i == ganttChart.size() - 1 || ganttChart[i].first != ganttChart[i + 1].first) {
            cout << setw(ganttChart[i].second * 6 + 1) << time;
        }
    }
    cout << endl;
}


void priorityPreemptive(vector<Process>& processes) {
    int n = processes.size();
    vector<int> isCompleted(n, 0);
    vector<pair<int, int>> ganttChart;
    double totalWT = 0, totalTAT = 0;
    int currentTime = 0, completed = 0;

    while (completed < n) {
        int idx = -1, lowestPriority = numeric_limits<int>::max();
        for (int i = 0; i < n; ++i) {
            if (processes[i].arrivalTime <= currentTime && !isCompleted[i] && processes[i].priority < lowestPriority) {
                lowestPriority = processes[i].priority;
                idx = i;
            }
        }
        if (idx != -1) {
            processes[idx].remainingTime--;
            ganttChart.push_back({processes[idx].id, 1});
            currentTime++;
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
            ganttChart.push_back({-1, 1});
            currentTime++;
        }
    }

    double avgWT = totalWT / n, avgTAT = totalTAT / n;
    printGanttChart(ganttChart);
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

// Priority Non Preemptive in CPP

#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>

using namespace std;

struct Process {
    int id, arrivalTime, burstTime, priority, completionTime, waitingTime, turnaroundTime;
};

// Function to print Gantt Chart
void printGanttChart(const vector<Process>& ganttChart) {
    cout << "\nGantt Chart:\n";
    for (size_t i = 0; i < ganttChart.size(); ++i)
        cout << "+-------";
    cout << "+\n|";
    for (const auto& p : ganttChart)
        cout << " P" << p.id << setw(5) << "|";
    cout << "\n ";
    for (size_t i = 0; i < ganttChart.size(); ++i)
        cout << "+-------";
    cout << "+\n0";

    int currentTime = 0;
    for (const auto& p : ganttChart) {
        currentTime += p.burstTime;
        cout << setw(8) << currentTime;
    }
    cout << "\n";
}

void priorityNonPreemptive(vector<Process>& p) {
    int n = p.size(), completed = 0, currentTime = 0;
    vector<int> isCompleted(n, 0);
    vector<Process> ganttChart;
    double totalWT = 0, totalTAT = 0;

    while (completed < n) {
        int idx = -1;
        int lowestPriority = numeric_limits<int>::max();

        for (int i = 0; i < n; ++i) {
            if (p[i].arrivalTime <= currentTime && !isCompleted[i] && p[i].priority < lowestPriority) {
                lowestPriority = p[i].priority;
                idx = i;
            }
        }

        if (idx != -1) {
            ganttChart.push_back(p[idx]);
            currentTime += p[idx].burstTime;
            p[idx].completionTime = currentTime;
            p[idx].turnaroundTime = p[idx].completionTime - p[idx].arrivalTime;
            p[idx].waitingTime = p[idx].turnaroundTime - p[idx].burstTime;
            totalWT += p[idx].waitingTime;
            totalTAT += p[idx].turnaroundTime;
            isCompleted[idx] = 1;
            completed++;
        } else {
            currentTime++;
        }
    }

    // Print Gantt chart
    printGanttChart(ganttChart);

    // Simplified process table
    cout << "\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (const auto& p : p) {
        cout << "P" << p.id << "\t" << p.arrivalTime << "\t" << p.burstTime << "\t"
             << p.completionTime << "\t\t" << p.turnaroundTime << "\t\t" << p.waitingTime << "\n";
    }

    cout << "The average Waiting time : " << totalWT / n << "\n";
    cout << "The average Turnaround time : " << totalTAT / n << "\n";
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> p(n);
    for (int i = 0; i < n; ++i) {
        p[i].id = i + 1;
        cout << "Enter arrival time, burst time, and priority for process P" << i + 1 << ": ";
        cin >> p[i].arrivalTime >> p[i].burstTime >> p[i].priority;
    }

    priorityNonPreemptive(p);
    return 0;
}
