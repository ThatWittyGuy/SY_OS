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
    vector<int> a(n * 10);  // Array for storing Gantt chart times

    // Input burst times and arrival times
    for (int i = 0; i < n; i++) {
        cout << "Burst time for process P" << (i + 1) << ": ";
        cin >> bur[i];
        bur1[i] = bur[i];
        cout << "Arrival time for process P" << (i + 1) << ": ";
        cin >> arrival[i];
    }

    cout << "Enter the time slice (in ms): ";
    cin >> t;

    // Calculate the number of time slices needed for each process
    for (int i = 0; i < n; i++) {
        b[i] = (bur[i] + t - 1) / t;  // Ceiling division for time slices
        m += b[i];
    }

    cout << "\nGANTT Chart\n";
    cout << string(m * 8, '-');  // Draw the top line of the Gantt chart
    cout << "\n";

    a[0] = 0;  // Initial time
    while (j < m) {
        x = (x + 1) % n;  // Cycle through processes

        // Wait for a process to arrive
        while (arrival[x] > currentTime) {
            currentTime++;  // Increment time until a process arrives
        }

        // Process execution
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

    cout << "\n" << string(m * 8, '-') << "\n";  // Draw the bottom line of the Gantt chart

    // Print the Gantt chart time stamps
    for (j = 0; j <= m; j++) cout << a[j] << "\t";
    cout << "\n\n";

    // Sorting processes based on their completion times
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i] > p[j]) {
                swap(p[i], p[j]);
                swap(k[i], k[j]);
            }
        }
    }

    // Calculate waiting and turnaround times
    for (int i = 0; i < n; i++) {
        wat[i] = k[i] - arrival[p[i]] - bur1[p[i]];
        tur[i] = k[i] - arrival[p[i]];
    }

    // Calculate total waiting time and turnaround time
    for (int i = 0; i < n; i++) {
        awat += wat[i];
        atur += tur[i];
    }

    awat /= n;
    atur /= n;

    // Output the average times
    cout << "Average waiting time: " << awat << " ms\n";
    cout << "Average turn around time: " <<  atur << " ms\n";

    return 0;
}
