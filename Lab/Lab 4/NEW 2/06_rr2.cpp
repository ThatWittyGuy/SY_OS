#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

int main() {
    int i, x = -1, m = 0, n, t, s = 0;
    vector<int> bur(10), bur1(10), p(10), k(10), arrival(10);
    vector<int> wat(10), tur(10);
    vector<int> a(50);
    int temp;
    float awat, atur;
    int ttur = 0, twat = 0, j = 0;
    
    cout << "Enter no. of processes : ";
    cin >> n;

    for (i = 0; i < n; i++) {
        cout << "Burst time for process P" << (i + 1) << " : ";
        cin >> bur[i];
        bur1[i] = bur[i];
        cout << "Arrival time for process P" << (i + 1) << " : ";
        cin >> arrival[i]; // Input for arrival time
    }

    cout << "Enter the time slice (in ms) : ";
    cin >> t;

    vector<int> b(n);
    for (i = 0; i < n; i++) {
        b[i] = bur[i] / t;
        if ((bur[i] % t) != 0)
            b[i] += 1;
        m += b[i];
    }

    cout << "\nGANTT Chart\n";
    for (i = 0; i < m; i++)
        cout << "--------";
    cout << "\n";

    a[0] = 0;
    vector<bool> done(n, false); // Track if a process is done
    int currentTime = 0;

    while (j < m) {
        x = (x + 1) % n; // Cycle through processes

        // Check if the process can run (it must be ready)
        while (arrival[x] > currentTime) {
            currentTime++; // Increment time until a process arrives
        }

        if (bur[x] > 0) { // Process can run
            if (bur[x] >= t) {
                bur[x] -= t;
                a[j + 1] = currentTime + t;
                currentTime += t;
            } else {
                currentTime += bur[x];
                a[j + 1] = currentTime;
                bur[x] = 0;
            }

            if (bur[x] == 0) {
                p[s] = x;
                k[s] = a[j + 1];
                s++;
            }
            j++;
            cout << "  P" << (x + 1) << "  |";
        }
    }

    cout << "\n";
    for (i = 0; i < m; i++)
        cout << "--------";
    cout << "\n";

    for (j = 0; j <= m; j++)
        cout << a[j] << "\t";

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (p[i] > p[j]) {
                swap(p[i], p[j]);
                swap(k[i], k[j]);
            }
        }
    }

    for (i = 0; i < n; i++) {
        wat[i] = k[i] - arrival[p[i]] - bur1[p[i]];
        tur[i] = k[i] - arrival[p[i]];
    }

    for (i = 0; i < n; i++) {
        ttur += tur[i];
        twat += wat[i];
    }

    awat = static_cast<float>(twat) / n;
    atur = static_cast<float>(ttur) / n;

    cout << "\n\nAverage waiting time     : " << fixed << setprecision(2) << awat << " ms";
    cout << "\nAverage turn around time : " << fixed << setprecision(2) << atur << " ms\n";

    return 0;
}
