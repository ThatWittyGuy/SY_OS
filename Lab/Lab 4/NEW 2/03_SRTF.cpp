#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
};

void printGanttChart(const vector<pair<int, int>> &ganttChart) {
    cout << "\nGantt Chart:\n";

    for (const auto &entry : ganttChart) {
        cout << "| " << setw(8) << "P" << entry.first;
    }
    cout << "|"; 

    cout << "\n";

    cout << setw(1) << "0"; 

    for (size_t i = 0; i < ganttChart.size(); i++) {
        cout << setw(8) << ganttChart[i].second; 
    }
    cout << endl; 
}


void printProcessTable(const vector<Process> &processes, double avgWT, double avgTAT) {
   cout<<"\nProcess Table:\n";
   cout<<setw(5)<< "ID"
       <<setw(15)<< "Arrival Time"
       <<setw(15)<< "Burst Time"
       <<setw(20)<< "Completion Time"
       <<setw(15)<< "Waiting Time"
       <<setw(20)<< "Turnaround Time"
       <<" \n";

   for (const auto &p : processes){
       cout<<setw(5)<<p.id 
           <<setw(15)<<p.arrivalTime 
           <<setw(15)<<p.burstTime 
           <<setw(20)<<p.completionTime 
           <<" "<<setw(15)<<p.waitingTime 
           <<" "<<setw(20)<<p.turnaroundTime 
           <<" \n";
   }

   cout<<"\nAverage Waiting Time: "<<avgWT 
       <<" \nAverage Turnaround Time: "<<avgTAT 
       <<" \n";
}

void srtf(vector<Process> &processes){
   int n=processes.size();
   vector<pair<int,int>> ganttChart;  // Store pairs of (process ID, end time)
   
   int completed=0,current_time=0,totalWT=0,totalTAT=0;

   while(completed<n){
       int idx=-1,min_time=numeric_limits<int>::max();

       for(int i=0;i<n;i++){
           if(processes[i].arrivalTime<=current_time && 
              processes[i].remainingTime>0 && 
              processes[i].remainingTime<min_time){
               min_time=processes[i].remainingTime;  
               idx=i;  
           }
       }

       if(idx!=-1){
           if(ganttChart.empty() || ganttChart.back().first!=processes[idx].id){
               ganttChart.push_back({processes[idx].id,current_time});  // Add new process and current time.
           }
           processes[idx].remainingTime--;
           current_time++;
           if(processes[idx].remainingTime==0){
               processes[idx].completionTime=current_time;  
               processes[idx].turnaroundTime=processes[idx].completionTime-processes[idx].arrivalTime;  
               processes[idx].waitingTime=processes[idx].turnaroundTime-processes[idx].burstTime;  
               totalWT+=processes[idx].waitingTime;  
               totalTAT+=processes[idx].turnaroundTime;  
               completed++;

               ganttChart.back().second=current_time;  // Update last added process's end time.
           }
       } else{
           current_time++;  // Idle time.
       }
   }

   double avgWT=totalWT/n;  
   double avgTAT=totalTAT/n;

   printGanttChart(ganttChart);
   printProcessTable(processes,avgWT,avgTAT);
}

int main(){
   int n;

   cout<<"Enter the number of processes: ";  
   cin>>n;

   vector<Process> processes(n);  

   for(int i=0;i<n;++i){
       processes[i].id=i+1;  
       cout<<"Enter arrival time and burst time for process P"<<i+1<<": ";  
       cin>>processes[i].arrivalTime>>processes[i].burstTime;  
       processes[i].remainingTime=processes[i].burstTime;  
   }

   srtf(processes);  

return 0;}
