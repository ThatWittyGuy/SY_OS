#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std; // C++

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
    cout << "+\n";
    cout << "0";
    for (const auto &p : processes) cout << setw(8) << p.completionTime;
    cout << "\n";
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    float avgWT = 0, avgTAT = 0;

    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "Enter arrival time and burst time for process P" << processes[i].id << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
    }

    sort(processes.begin(), processes.end(), compareArrival);

    int currentTime = 0;
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

    cout << "\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (const auto &p : processes) {
        cout << "P" << p.id << "\t" << p.arrivalTime << "\t" << p.burstTime << "\t"
             << p.completionTime << "\t\t" << p.turnaroundTime << "\t\t" << p.waitingTime << "\n";
    }

    cout << "The average Waiting time : " << avgWT << "\n";
    cout << "The average Turnaround time : " << avgTAT << "\n";

    displayGanttChart(processes);

    return 0;
}


// Optimal Code Page Replacement in C

#include <stdio.h>

int main() {
    int i, j, n, a[50], frame[10], no, k, count = 0, pos, flag1, flag2;

    printf("\nENTER THE NUMBER OF PAGES: ");
    scanf("%d", &n);
    
    printf("\nENTER THE PAGE NUMBER: ");
    for (i = 0; i < n; i++) 
        scanf("%d", &a[i]);
    
    printf("\nENTER THE NUMBER OF FRAMES: ");
    scanf("%d", &no);
    
    for (i = 0; i < no; i++)
        frame[i] = -1; 

    printf("Ref String\t Page Frames\n");
    
    for (i = 0; i < n; i++) {
        printf("%d\t\t", a[i]);
        flag1 = flag2 = 0;

        for (k = 0; k < no; k++) {
            if (frame[k] == a[i]) {
                flag1 = 1; 
                break;
            }
        }
        
        if (flag1 == 0) {
            for (k = 0; k < no; k++) {
                if (frame[k] == -1) {
                    frame[k] = a[i]; 
                    flag2 = 1; 
                    break;
                }
            }
            
            if (flag2 == 0) {
                pos = -1;
                int farthest = -1;
                for (k = 0; k < no; k++) {
                    int j;
                    for (j = i + 1; j < n; j++) {
                        if (frame[k] == a[j]) {
                            if (j > farthest) {
                                farthest = j; 
                                pos = k; 
                            }
                            break;
                        }
                    }
                    if (j == n) {
                        pos = k; 
                        break;
                    }
                }
                frame[pos] = a[i]; 
            }
            count++; 
            
            for (k = 0; k < no; k++)
                printf("%d\t", frame[k]);
        } else {
            for (k = 0; k < no; k++)
                printf("\t"); 
        }
        
        printf("\n");
    }
    
    printf("\nTotal Page Fault: %d", count);
    return 0;
}
