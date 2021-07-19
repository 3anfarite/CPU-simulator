#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "functions.h"



//Creates a process item dynamically , checks if the creation was successfull and returns the address of the item
Process* CreateProc()
{
    Process* proc;
    proc = (Process*)malloc(sizeof(Process));
    if (proc == NULL)
	{
		printf("Error! Malloc failed at procedure creation!");
		exit(5);
	}
	return proc;
}


//So this method read data from the file (using sscanf) and store them in procArray (an array of processes)
int readFileData(FILE* fileToRead, Process* procArray)
{
    char line[100];
    int i=0;
    int numOfProcs;

    while (fgets(line, sizeof line, fileToRead)) //store the whole line in line[100]
        {
            if(line[0] == '#' || line[0] == '\n')   //check if the line is empty of it's a comment(comments like in python)
            {
                i = i;
            }
           else
            {
                sscanf(line, "%s %d %d" ,
                        procArray[i].name,
                        &procArray[i].arrivalTime ,
                        &procArray[i].burstTime);
                i++;
            }
        }
        numOfProcs = i;
        for(int j = 0 ; j<numOfProcs;j++){          //display processes red from the input file
            printf("\nProcess name : %s ", procArray[j].name);
            printf("\nProcess arrival : %d ",procArray[j].arrivalTime);
            printf("\nProcess burst : %d ", procArray[j].burstTime);
            printf("\n*************************************");
        }
    return numOfProcs;
}
//swapping processes for sorting
void swapProc(Process* proc1, Process* proc2){

    Process temp = *proc1;

    //proc1->name = proc2->name;
    proc1->arrivalTime = proc2->arrivalTime;
    proc1->burstTime = proc2->burstTime;


    //proc2->name = temp.name;
    proc2->arrivalTime = temp.arrivalTime;
    proc2->burstTime = temp.burstTime;

    //swapping strings
    strcpy(temp.name,proc1->name);
    strcpy(proc1->name,proc2->name);
    strcpy(proc2->name,temp.name);

}

void sortSJF(Process *procArray, int numOfProc){   // bubble sort
    int i,j,k=1,time=0,min,sum=0,ta=0;
    int wt[numOfProc],tat[numOfProc];
    for(i = 0; i < numOfProc-1; i++){         /* sorting processes according to arrivals */
        for(j = 0; j<numOfProc-i-1 ; j++){
            if(procArray[j].arrivalTime> procArray[j+1].arrivalTime){
                swapProc(&procArray[j], &procArray[j+1]);
            }
        }
    }
    for(j=0;j<numOfProc;j++){
        time=time+procArray[j].burstTime;
        min=procArray[k].burstTime;     //k=1 first loop
        for(i=k;i<numOfProc;i++)
        {
            if (time >= procArray[i].arrivalTime && procArray[i].burstTime<min)
            {
                swapProc(&procArray[k], &procArray[i]);
            }
        }
        k++;
    }
    wt[0]=0;
    for(i=1;i<numOfProc;i++)
    {
        sum=sum+procArray[i-1].burstTime;
        wt[i]=sum-procArray[i].arrivalTime;
    }
    for(i=0;i<numOfProc;i++)
    {
        ta = ta + procArray[i].burstTime;
        tat[i]= ta - procArray[i].arrivalTime;
    }
    printf("\n\n");
    printf("*******************SHORTEST JOB FIRST SCHEDULING********************\n");
    printf("Name\tArrivalTime\tBurstTime\tTurnAroundTime\tWaitTime\n");
    printf("***************************************\n");
    for(i=0;i<numOfProc;i++)
    {
            printf("%s\t%d\t\t%d\t\t%d\t\t%d\n",procArray[i].name,procArray[i].arrivalTime,
                                            procArray[i].burstTime,tat[i],wt[i]);
    }
    printf("***************************************\n");
//

}


void sortFCFS(Process *procArray, int numOfProc){
    int i;
    int wt[numOfProc],tat[numOfProc];
    for(i = 0; i < numOfProc-1; i++){         /* sorting processes according to arrivals */
        for(int j = 0; j<numOfProc-i-1 ; j++){
            if(procArray[j].arrivalTime> procArray[j+1].arrivalTime){
                swapProc(&procArray[j], &procArray[j+1]);
            }
        }
    }
    wt[0]=0;
    for(i=1;i<numOfProc;i++)
    {
        wt[i]=0;
        for(int j=0;j<i;j++)
            wt[i]+=procArray[j].burstTime;
    }
    for(i=0;i<numOfProc;i++)
    {
        tat[i]=procArray[i].burstTime+wt[i];
    }

    printf("\n\n");
    printf("*******************FIRST COME FIRST SERVE SCHEDULING********************\n");
    printf("Name\tArrivalTime\tBurstTime\tTurnAroundTime\tWaitTime\n");
    printf("***************************************\n");
    for(i=0;i<numOfProc;i++)
    {
            printf("%s\t%d\t\t%d\t\t%d\t\t%d\n",procArray[i].name,procArray[i].arrivalTime,
                                            procArray[i].burstTime,tat[i],wt[i]);
    }
    printf("***************************************\n");
//
}


void roundRobin(Process *procArray,int numOfProc){
    int i = 0, time = 0, done = 0, quantum;
    int dummyBurst[numOfProc],
        tat[numOfProc],
        wt[numOfProc];//tat : turnAroundTime;
    int x;                                                  //wt  : waitTime
    x = numOfProc;
    printf("\nEnter Time Quantum: ");
    scanf("%d", &quantum);

    for(i = 0; i < numOfProc-1; i++){         /* sorting processes according to arrivals */
        for(int j = 0; j<numOfProc-i-1 ; j++){
            if(procArray[j].arrivalTime> procArray[j+1].arrivalTime){
                swapProc(&procArray[j],&procArray[j+1]);
            }
        }
    }
    // storing all bursts in another variable
    for(i = 0; i<numOfProc; i++){dummyBurst[i] = procArray[i].burstTime;}

    printf("\n Gantt Chart\n");
    for (time=0,i=0;x!=0;){ //no need to increment in a for loop ( form (;;))
        if(dummyBurst[i] <= quantum && dummyBurst[i]>0){
            time = time + dummyBurst[i];
            printf(" -> [%s] <- %d", procArray[i].name, time );
            dummyBurst[i] = 0;
            done = 1;
        }
        else if (dummyBurst[i] > 0){
            dummyBurst[i] = dummyBurst[i] - quantum ;
            time = time + quantum;
            printf(" -> [%s] <- %d",procArray[i].name, time);
        }
        if(dummyBurst[i] == 0 && done == 1){
            x--; //x now id the number of remaining processes
            tat[i] = time - procArray[i].arrivalTime;
            wt[i] = time - procArray[i].arrivalTime - procArray[i].burstTime;
            done = 0;
        }
        if(i == numOfProc - 1)
            i=0;
        else if(procArray[i+1].arrivalTime <= time)
            i++;
        else
            i=0;
    }
       printf("\n\n");
    printf("*******************ROUNDROBIN SCHEDULING********************\n");
       printf("Name\tArrivalTime\tBurstTime\tTurnAroundTime\tWaitTime\n");
       printf("***************************************\n");
       for(i=0;i<numOfProc;i++)
       {
              printf("%s\t%d\t%d\t%d\t%d\n",procArray[i].name,procArray[i].arrivalTime,
                                            procArray[i].burstTime,tat[i],wt[i]);
       }
       printf("***************************************\n");
}












