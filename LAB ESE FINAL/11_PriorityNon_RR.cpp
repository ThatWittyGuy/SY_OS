// Priority Non in CPP

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

// Round Robin in CPP

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    int n, t, m = 0, currentTime = 0, x = -1, j = 0, s = 0;
    float awat = 0, atur = 0;
    
    cout << "Enter no. of processes: ";
    cin >> n;

    vector<int> bur(n), bur1(n), arrival(n), b(n), p(n), k(n), wat(n), tur(n);
    vector<int> a(n * 10);  

    for (int i = 0; i < n; i++) {
        cout << "Burst time for process P" << (i + 1) << ": ";
        cin >> bur[i];
        bur1[i] = bur[i];
        cout << "Arrival time for process P" << (i + 1) << ": ";
        cin >> arrival[i];
    }

    cout << "Enter the time slice (in ms): ";
    cin >> t;

    for (int i = 0; i < n; i++) {
        b[i] = (bur[i] + t - 1) / t;  
        m += b[i];
    }

    cout << "\nGANTT Chart\n";
    cout << string(m * 8, '-');  
    cout << "\n";

    a[0] = 0;  
    while (j < m) {
        x = (x + 1) % n;  

        while (arrival[x] > currentTime) {
            currentTime++;  
        }

        if (bur[x] > 0) {
            int sliceTime = min(bur[x], t);
            bur[x] -= sliceTime;
            a[j + 1] = currentTime + sliceTime;
            currentTime += sliceTime;

            if (bur[x] == 0) {
                p[s] = x;
                k[s] = a[j + 1];
                s++;
            }

            cout << "  P" << (x + 1) << "  |";
            j++;
        }
    }

    cout << "\n" << string(m * 8, '-') << "\n";  

    for (j = 0; j <= m; j++) cout << a[j] << "\t";
    cout << "\n\n";

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i] > p[j]) {
                swap(p[i], p[j]);
                swap(k[i], k[j]);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        wat[i] = k[i] - arrival[p[i]] - bur1[p[i]];
        tur[i] = k[i] - arrival[p[i]];
    }

    for (int i = 0; i < n; i++) {
        awat += wat[i];
        atur += tur[i];
    }

    awat /= n;
    atur /= n;

    cout << "Average waiting time: " << awat << " ms\n";
    cout << "Average turn around time: " <<  atur << " ms\n";

    return 0;
}
