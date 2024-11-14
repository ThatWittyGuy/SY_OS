// Priority Non in CPP

#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>

using namespace std;

struct Process {
    int id, arrivalTime, burstTime, priority, completionTime, waitingTime, turnaroundTime;
};

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

    printGanttChart(ganttChart);

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

// SJF in CPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <climits>

using namespace std;

struct Process {
    int id, arrivalTime, burstTime, completionTime, turnaroundTime, waitingTime;
    bool isCompleted = false;
};

bool compareArrival(const Process &a, const Process &b) {
    return a.arrivalTime < b.arrivalTime;
}

void displayGanttChart(const vector<Process> &ganttChart) {
    cout << "\nGantt Chart:\n ";
    for (const auto &p : ganttChart) cout << "+-------";
    cout << "+\n|";
    for (const auto &p : ganttChart) cout << " P" << p.id << setw(5) << "|";
    cout << "\n ";
    for (const auto &p : ganttChart) cout << "+-------";
    cout << "+\n0";
    for (const auto &p : ganttChart) cout << setw(8) << p.completionTime;
    cout << "\n";
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "Enter arrival time and burst time for process P" << processes[i].id << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
    }

    sort(processes.begin(), processes.end(), compareArrival);

    int currentTime = 0, completed = 0;
    double totalWT = 0, totalTAT = 0;
    vector<Process> ganttChart;

    while (completed < n) {
        int idx = -1, minBurstTime = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (!processes[i].isCompleted && processes[i].arrivalTime <= currentTime) {
                if (processes[i].burstTime < minBurstTime || 
                    (processes[i].burstTime == minBurstTime && processes[i].arrivalTime < processes[idx].arrivalTime)) {
                    minBurstTime = processes[i].burstTime;
                    idx = i;
                }
            }
        }

        if (idx == -1) ++currentTime;
        else {
            auto &p = processes[idx];
            p.completionTime = currentTime + p.burstTime;
            p.turnaroundTime = p.completionTime - p.arrivalTime;
            p.waitingTime = p.turnaroundTime - p.burstTime;

            totalWT += p.waitingTime;
            totalTAT += p.turnaroundTime;
            p.isCompleted = true;
            currentTime = p.completionTime;
            ganttChart.push_back(p);
            ++completed;
        }
    }

    cout << "\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (const auto &p : processes) {
        cout << "P" << p.id << "\t" << p.arrivalTime << "\t" << p.burstTime << "\t"
             << p.completionTime << "\t\t" << p.turnaroundTime << "\t\t" << p.waitingTime << "\n";
    }

    displayGanttChart(ganttChart);
    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << totalWT / n << endl;
    cout << "Average Turnaround Time: " << totalTAT / n << endl;

    return 0;
}
