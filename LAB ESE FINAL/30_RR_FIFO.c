#include <iostream>
#include <vector>
#include <iomanip>

using namespace std; // CPP

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


// FIFO Page replacement in C

#include <stdio.h>
int main()
{
    int i, j, n, a[50], frame[10], no, k, avail, count = 0;
    printf("\n ENTER THE NUMBER OF PAGES:\n");
    scanf("%d", &n);
    printf("\n ENTER THE PAGE NUMBER :\n");
    for (i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    printf("\n ENTER THE NUMBER OF FRAMES :");
    scanf("%d", &no);
    for (i = 0; i < no; i++)
        frame[i] = -1;
    j = 0;
    printf("\tref string\t page frames\n");
    for (i = 1; i <= n; i++)
    {
        printf("%d\t\t", a[i]);
        avail = 0;
        for (k = 0; k < no; k++)
            if (frame[k] == a[i])
                avail = 1;
        if (avail == 0)
        {
            frame[j] = a[i];
            j = (j + 1) % no;
            count++;
            for (k = 0; k < no; k++)
                printf("%d\t", frame[k]);
        }
        printf("\n");
    }
    printf("Page Fault Is %d", count);
    return 0;
}
