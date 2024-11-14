#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

struct Process {
    int id, arrivalTime, burstTime, remainingTime, completionTime, waitingTime, turnaroundTime;
};

void printGanttChart(const vector<pair<int, int>>& ganttChart) {
    cout << "\nGantt Chart:\n";
    for (const auto& entry : ganttChart) cout << "+-------";
    cout << "+\n|";
    for (const auto& entry : ganttChart) cout << " P" << entry.first << setw(5) << "|";
    cout << "\n ";
    for (const auto& entry : ganttChart) cout << "+-------";
    cout << "+\n0";
    for (const auto& entry : ganttChart) cout << setw(8) << entry.second;
    cout << "\n";
}

void srtf(vector<Process>& processes) {
    int n = processes.size(), completed = 0, current_time = 0, totalWT = 0, totalTAT = 0;
    vector<pair<int, int>> ganttChart;

    while (completed < n) {
        int idx = -1, min_time = numeric_limits<int>::max();
        for (int i = 0; i < n; ++i) {
            if (processes[i].arrivalTime <= current_time && processes[i].remainingTime > 0 && processes[i].remainingTime < min_time) {
                min_time = processes[i].remainingTime;
                idx = i;
            }
        }

        if (idx != -1) {
            if (ganttChart.empty() || ganttChart.back().first != processes[idx].id) {
                ganttChart.push_back({processes[idx].id, current_time});
            }
            processes[idx].remainingTime--;
            current_time++;
            if (processes[idx].remainingTime == 0) {
                processes[idx].completionTime = current_time;
                processes[idx].turnaroundTime = current_time - processes[idx].arrivalTime;
                processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
                totalWT += processes[idx].waitingTime;
                totalTAT += processes[idx].turnaroundTime;
                completed++;
                ganttChart.back().second = current_time;
            }
        } else {
            current_time++;
        }
    }

    // Print Gantt chart
    printGanttChart(ganttChart);

    // Calculate averages
    double avgWT = totalWT / (double)n, avgTAT = totalTAT / (double)n;

    // Print process table in main
    cout << "\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (const auto& p : processes) {
        cout << "P" << p.id << "\t" << p.arrivalTime << "\t" << p.burstTime << "\t"
             << p.completionTime << "\t\t" << p.turnaroundTime << "\t\t" << p.waitingTime << "\n";
    }
    cout << "The average Waiting time : " << avgWT << "\n";
    cout << "The average Turnaround time : " << avgTAT << "\n";
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    vector<Process> processes(n);
    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "Enter arrival time and burst time for process P" << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
    }
    srtf(processes);
    return 0;
}
