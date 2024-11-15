#include <stdio.h>



struct process
{
    int pid;
    int arrtime;
    int burst;
    int turnaround;
    int wait;
};

void sortprocess(struct Process p[], int n){
    for (int i = 0; i < n-1; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (p[j].arrtime > p[j-1].arrtime)
            {
                /* code */
            }
            
        }
        
        
    }
    
}
