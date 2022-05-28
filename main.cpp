#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <climits>
#include <limits>
using namespace std;

struct Process
{
  int Pid;
  int arrivalTime;
  int burstTime;
  int completionTime;
  int waitTime;
  int TaT;
  int responseTime;
  int startTime;
  int remainingTime;
  int priority;
}procArr[100];

class priorityProcess{
    public:
        int arrivalTime;
        int burstTime;
        int priority;
        int remainingTime;
        int responseTime;
        int completionTime;
        int waitingTime;
        int turnAroundTime;
        int startTime;
        void initialize(){
            remainingTime = burstTime;
        }
};


bool processComplete[100]={false}, firstProcess=true;
int currentTime = 0;
int completed = 0;

int previous = 0;


int maxCompleteTime;
int minArrivalTime;
int numProcesses;

double TaTTotal = 0;
double waitTimeTotal = 0;
double responseTimeTotal = 0;
int i;



bool getArrivalT(struct Process proc1,struct Process proc2)
{
    int a = proc1.arrivalTime;
    int b = proc2.arrivalTime;
   return a < b;


}

bool getPID(struct Process pid1,struct Process pid2)
{
   int a = pid1.Pid;
   int b = pid2.Pid;
   return a < b;
}

void fcfsFit() {
    cout << "\n==========================This is the FCFS ==========================" << endl;

        sort(procArr,procArr + numProcesses, getArrivalT);


        for(i = 1; i <= numProcesses; i++)
        {
            procArr[i].startTime = (i==0) ? procArr[i].arrivalTime : max(procArr[i].arrivalTime, procArr[i-1].completionTime);
            procArr[i].completionTime =  procArr[i].startTime + procArr[i].burstTime;
            procArr[i].TaT = procArr[i].completionTime-procArr[i].arrivalTime;
            procArr[i].waitTime = procArr[i].TaT-procArr[i].burstTime;
            procArr[i].responseTime=procArr[i].waitTime;

          TaTTotal += procArr[i].TaT;
          waitTimeTotal += procArr[i].waitTime;
          responseTimeTotal += procArr[i].responseTime;

        }

        sort(procArr,procArr + numProcesses, getPID);


    cout<<"\nProcess \t StartTime \t ExecutionTime \t CompletionTime \t TurnAroundTime \t WaitTime \t ResponseTime \t ArrivalTime\n";
    for(i = 1; i <= numProcesses; i++)
//     cout << i << setw (19) << procArr[i].arrivalTime << setw (14)<< procArr[i].burstTime << setw (17) << procArr[i].completionTime << setw (16) <<procArr[i].TaT <<setw (18)<< procArr[i].waitTime << setw (15) << procArr[i].responseTime << endl;
        cout << i << setw (20) << procArr[i].startTime << setw (20)<< procArr[i].burstTime << setw (20) << procArr[i].completionTime << setw (20) <<procArr[i].TaT <<setw (20)<< procArr[i].waitTime << setw (20) << procArr[i].responseTime << setw (20) << procArr[i].arrivalTime <<  endl;





        cout<<"\nAverage Turn Around time: "<< TaTTotal/numProcesses;
        cout<<"\nAverage Waiting Time: "<<waitTimeTotal/numProcesses;
        cout<<"\nAverage Response Time: "<<responseTimeTotal/numProcesses;

    cout << "\nOrder of execution: ";
       for ( i = 1 ; i <= numProcesses; i++)
       {
           cout << "P" << procArr[i].Pid <<" -> ";
       }
    cout << "\n========================================================================" << endl;
}


void shortestJobNext(){
    cout << "\n==========================This is the Shortest Job Next ==========================" << endl;

        while(completed != numProcesses)
        {
            int minIndex = -1;
            int minimum = INT_MAX;
            for(int i = 1; i <= numProcesses; i++) {
                if(procArr[i].arrivalTime <= currentTime && processComplete[i] == false) {
                    if(procArr[i].burstTime < minimum) {
                        minimum = procArr[i].burstTime;
                        minIndex = i;
                    }
                    if(procArr[i].burstTime== minimum) {
                        if(procArr[i].arrivalTime < procArr[minIndex].arrivalTime) {
                            minimum= procArr[i].burstTime;
                            minIndex = i;
                        }
                    }
                }
            }

            if(minIndex == -1)
            {
                currentTime++;
            }
            else
            {
                procArr[minIndex].startTime = currentTime;
                procArr[minIndex].completionTime = procArr[minIndex].startTime + procArr[minIndex].burstTime;
                procArr[minIndex].TaT = procArr[minIndex].completionTime - procArr[minIndex].arrivalTime;
                procArr[minIndex].waitTime = procArr[minIndex].TaT - procArr[minIndex].burstTime;
                procArr[minIndex].responseTime = procArr[minIndex].waitTime;
                procArr[minIndex].responseTime = procArr[minIndex].startTime - procArr[minIndex].arrivalTime;

            TaTTotal +=procArr[minIndex].TaT;
            waitTimeTotal += procArr[minIndex].waitTime;
            responseTimeTotal += procArr[minIndex].responseTime;


            completed++;
            processComplete[minIndex]=true;
            currentTime = procArr[minIndex].completionTime;
            previous= currentTime;
            firstProcess = false;
            }
        }

        maxCompleteTime = INT_MIN;
        minArrivalTime= INT_MAX;
        for(i = 1; i <= numProcesses;i++)
        {
            maxCompleteTime = max(maxCompleteTime,procArr[i].completionTime);
            minArrivalTime = min(minArrivalTime,procArr[i].arrivalTime);
        }



    cout<<"\nProcess \t StartTime \t ExecutionTime \t CompletionTime \t TurnAroundTime \t WaitTime \t ResponseTime \t ArrivalTime\n";
    for(i = 1; i <= numProcesses; i++)
//     cout << i << setw (19) << procArr[i].arrivalTime << setw (14)<< procArr[i].burstTime << setw (17) << procArr[i].completionTime << setw (16) <<procArr[i].TaT <<setw (18)<< procArr[i].waitTime << setw (15) << procArr[i].responseTime << endl;
        cout << i << setw (20) << procArr[i].startTime << setw (20)<< procArr[i].burstTime << setw (20) << procArr[i].completionTime << setw (20) <<procArr[i].TaT <<setw (20)<< procArr[i].waitTime << setw (20) << procArr[i].responseTime << setw (20) << procArr[i].arrivalTime <<  endl;



    cout<<"\nAverage TaT: "<< (float)TaTTotal/numProcesses;
    cout<<"\nAverage Waiting Time: "<<(float)waitTimeTotal/numProcesses;
    cout<<"\nAverage Response Time: "<<(float)responseTimeTotal/numProcesses;


    cout << "\nOrder of execution: ";
       for ( i = 1 ; i <= numProcesses; i++)
       {
           cout << "P" << procArr[i].burstTime <<" -> ";
           
       }
    
    cout << "\n========================================================================" << endl;
   }


    void Priority(){
        cout << "\n==========================This is the Priority ==========================" << endl;
        
        cout << "\nInput the number of processes:" << endl;
        cin >> numProcesses;

        priorityProcess processes[numProcesses];

        cout << "\nInput the size of each process for Arrival Time" << endl;
        for(i = 1; i <= numProcesses; i++){

            cout<<"\nProcess for Arrival Time " << i << ": ";
            cin >> processes[i].arrivalTime;
           processes[i].arrivalTime = i;
            processes[i].initialize();
        }
        cout << "\nInput the size of each process for Priority" << endl;
        for(i = 1; i <= numProcesses; i++){

            cout<<"\nProcess for Priority " << i << ": ";
            cin >> processes[i].priority;
            processes[i].initialize();
        }
        
        cout << "\nInput the size of each process for Execution Time" << endl;
        for(i = 1; i <= numProcesses; i++){

            cout<<"\nProcess for Execution Time " << i << ": ";
            cin >> processes[i].burstTime;
            processes[i].initialize();
        }

           for( i = 1; i <= numProcesses;i++){
               for(int j = i; j <= numProcesses;j++){
                   if(processes[j].arrivalTime < processes[i].arrivalTime){
                       priorityProcess temp = processes[j];
                       processes[j] = processes[i];
                       processes[i] = temp;
                   }
               }
           }


        int currentTime = 0;

        while(true){

            int HighestPriority = -1;
            int currentPriority = numeric_limits<int>::max();

            bool isCompleted = true;

            for( i = 1;i <= numProcesses;i++){
                if(processes[i].remainingTime > 0){
                    isCompleted = false;
                    if(processes[i].arrivalTime <= currentTime){
                        if(processes[i].priority < currentPriority){
                            currentPriority = processes[i].priority;
                            HighestPriority = i;
                        }
                    }
                    
                }
            }

            if(isCompleted){
                break;
            }

            if(processes[HighestPriority].remainingTime == processes[HighestPriority].burstTime){
                processes[HighestPriority].responseTime = currentTime;
            }

            processes[HighestPriority].remainingTime--;
            currentTime++;

            if(processes[HighestPriority].remainingTime == 0){
                processes[HighestPriority].completionTime = currentTime;
                processes[currentPriority].startTime = currentTime;

            }
        }

        int TaTtotal = 0;
        int ResponseTimeTotal = 0;
        int CompletionTimeTotal = 0;
        int WaitingTimeTotal = 0;
       
       
        cout<<"\nProcess \t startTime \t ExecutionTime \t CompletionTime \t TurnAroundTime \t WaitTime \t ResponseTime  \t ArrivalTime\n";
        for( i = 1; i <= numProcesses; i++){
            cout << i << setw (20) << processes[i].startTime << setw (20)<< processes[i].burstTime << setw (20) << processes[i].completionTime << setw (20);
            processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;
                processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;
            cout<<processes[i].turnAroundTime <<setw (20)<< processes[i].waitingTime << setw (20) << processes[i].responseTime << setw (20) << processes[i].arrivalTime << endl;


            TaTtotal += processes[i].turnAroundTime;
            ResponseTimeTotal += processes[i].responseTime;
            CompletionTimeTotal += processes[i].completionTime;
            WaitingTimeTotal += processes[i].waitingTime;
            
        }
        cout << "\nAverage TaT for " << (numProcesses) << " Processes: " << (float) TaTtotal/numProcesses;
        cout << "\nAverage ResponseTime for " << (numProcesses) << " Processes: " << (float) ResponseTimeTotal/numProcesses;
        cout << "\nAverage CompletionTime for " << (numProcesses) << " Processes: " << (float) CompletionTimeTotal/numProcesses;
        cout << "\nAverage WaitingTime for " << (numProcesses) << " Processes: " << (float) WaitingTimeTotal/numProcesses;
       
        cout << "\nOrder of execution: ";
           for ( i = 1 ; i <= numProcesses; i++)
           {
               cout << "P" << processes[i].priority << " -> ";
           }
        cout << "\n========================================================================" << endl;
       }




void userInput(){

    cout << "\nInput the number of processes:" << endl;
    cin >> numProcesses;

    cout << fixed << setprecision(2);

    cout << "\nInput the size of each process for Arrival Time" << endl;
    for(i = 1; i <= numProcesses; i++){

        cout<<"\nProcess for Arrival Time " << i << ": ";
        cin >> procArr[i].arrivalTime;
        procArr[i].Pid=i;
    }
    cout << "\nInput the size of each process for Execution Time" << endl;
    for(i = 1; i <= numProcesses; i++){

        cout<<"\nProcess for Execution Time " << i << ": ";
        cin >> procArr[i].burstTime;
    }


    }

int main() {

    int action;

        do {
            cout << "\nMemory Management:" << endl;
            cout << "1 - First Come Fist Server(FCFS)" << endl;
            cout << "2 - Shortest Job Next" << endl;
            cout << "3 - Priority" << endl;
            cout << "4 - Exit Memory Management Program " << endl;


            cout << "What would you like to do ? Enter a number: ";
            cin >> action;


            switch (action) {

            case 1:
                    userInput();
                fcfsFit();
                break;


            case 2:
                    userInput();
                    shortestJobNext();
                break;

                case 3:
                        Priority();
                    break;

                case 4:
                    cout << "\nExited Memory Management Program Successfully!" << endl;
                    break;



            }
        } while (action != 4);

    return 0;
}

