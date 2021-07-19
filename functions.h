#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structures.h"

Process* CreateProc();


int readFileData(FILE* fileToRead, Process* procArray);


void swapProc(Process* proc1, Process* proc2);

void sortSJF(Process *procArray, int numOfProc);
void sortFCFS(Process *procArray, int numOfProc);
void roundRobin(Process *procArray, int numOfProc);




