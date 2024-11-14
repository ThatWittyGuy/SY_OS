#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Process {
    int id, arrivalTime, burstTime, completionTime, turnaroundTime, waitingTime;
};

bool compareArrival(const Process &a, const Process &b) {
    return a.arrivalTime < b.arrivalTime;
}

void displayGanttChart(const vector<Process> &processes) {
    cout << "\nGantt Chart:\n ";
    for (const auto &p : processes) cout << "+-------";
    cout << "+\n|";
    for (const auto &p : processes) cout << " P" << p.id << setw(5) << "|";
    cout << "\n ";
    for (const auto &p : processes) cout << "+-------";
    cout << "+\n0";
    for (const auto &p : processes) cout << setw(8) << p.completionTime;
    cout << "\n";
}

void FCFS() {
    int n;
    cout << "Enter the number of processes for FCFS: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "Enter arrival time and burst time for process P" << processes[i].id << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
    }

    sort(processes.begin(), processes.end(), compareArrival);

    int currentTime = 0;
    float avgWT = 0, avgTAT = 0;
    for (auto &p : processes) {
        currentTime = max(currentTime, p.arrivalTime);
        p.completionTime = currentTime + p.burstTime;
        currentTime = p.completionTime;
        p.turnaroundTime = p.completionTime - p.arrivalTime;
        p.waitingTime = p.turnaroundTime - p.burstTime;
        avgTAT += p.turnaroundTime;
        avgWT += p.waitingTime;
    }

    avgTAT /= n;
    avgWT /= n;

    cout << "\nFCFS Scheduling\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (const auto &p : processes)
        cout << "P" << p.id << "\t" << p.arrivalTime << "\t" << p.burstTime << "\t"
             << p.completionTime << "\t\t" << p.turnaroundTime << "\t\t" << p.waitingTime << "\n";

    cout << "Avg Waiting time: " << avgWT << "\nAvg Turnaround time: " << avgTAT << "\n";
    displayGanttChart(processes);
}

void RoundRobin() {
    int n, t, currentTime = 0, m = 0, x = -1, j = 0, s = 0;
    float awat = 0, atur = 0;
    
    cout << "Enter the number of processes for Round Robin: ";
    cin >> n;

    vector<int> bur(n), bur1(n), arrival(n), b(n), p(n), k(n), wat(n), tur(n), a(n * 10);
    vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        cout << "Burst time for process P" << (i + 1) << ": ";
        cin >> bur[i];
        bur1[i] = bur[i];
        cout << "Arrival time for process P" << (i + 1) << ": ";
        cin >> arrival[i];
        processes[i].id = i + 1;
        processes[i].arrivalTime = arrival[i];
        processes[i].burstTime = bur[i];
    }

    cout << "Enter the time slice (in ms): ";
    cin >> t;

    for (int i = 0; i < n; i++) {
        b[i] = (bur[i] + t - 1) / t;
        m += b[i];
    }

    cout << "\nRound Robin Scheduling\nGANTT Chart\n ";
    for (int i = 0; i < m; i++) cout << "+-------";
    cout << "+\n";

    a[0] = 0;
    while (j < m) {
        x = (x + 1) % n;
        while (arrival[x] > currentTime) currentTime++;

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

    cout << "\n ";
    for (int i = 0; i < m; i++) cout << "+-------";
    cout << "+\n0";
    for (int j = 1; j <= m; j++) cout << setw(7) << a[j];
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
        processes[p[i]].completionTime = k[i];
        processes[p[i]].turnaroundTime = k[i] - processes[p[i]].arrivalTime;
        processes[p[i]].waitingTime = processes[p[i]].turnaroundTime - bur1[p[i]];
        wat[i] = processes[p[i]].waitingTime;
        tur[i] = processes[p[i]].turnaroundTime;
        awat += wat[i];
        atur += tur[i];
    }

    awat /= n;
    atur /= n;

    cout << "\nRound Robin Scheduling\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (const auto &p : processes)
        cout << "P" << p.id << "\t" << p.arrivalTime << "\t" << p.burstTime << "\t"
             << p.completionTime << "\t\t" << p.turnaroundTime << "\t\t" << p.waitingTime << "\n";

    cout << "Avg Waiting time: " << awat << " ms\nAvg Turnaround time: " << atur << " ms\n";
}

int main() {
    FCFS();
    RoundRobin();
    return 0;
}
