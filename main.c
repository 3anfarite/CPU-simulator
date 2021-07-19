#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "functions.h"



int main(int argc, char *argv[]) //argv[0] is the program itself
{                                //argv[1] is the file to input
	AlgorithmToCall whichOne;    //argv[2] is the algorithm
	FILE* fileToRead;
	int numOfProc;


	 if (argc != 3) {
        puts("*****************format: <filename> <algorithm to call>");
        puts("*****************for example : output inputfile.txt sjf");
        puts("*****************RoundRobin         : rr or RR");
        puts("*****************ShortestJobFirst   : sjf or SJF");
        puts("*****************FirstComeFirstServe: fcfs or FCFS");
        return EXIT_FAILURE;
    }


	if (strcmp(argv[2], "sjf") == 0 || strcmp(argv[2], "SJF") == 0)
		whichOne = sjf;
	else if (strcmp(argv[2], "fcfs") == 0 || strcmp(argv[2], "FCFS") == 0)
		whichOne = fcfs;
	else if (strcmp(argv[2], "rr") == 0 || strcmp(argv[2], "RR") == 0)
		whichOne = rr;
	else
	{
		printf("Error! Invalid algorithm call!");
		exit(1);
	}


	fileToRead = fopen(argv[1], "r");
	if (fileToRead == NULL)
	{
		printf("Error! File %s could not be opened!", argv[1]);
		exit(0);
	}


    Process *procArray = CreateProc();

    numOfProc = readFileData(fileToRead, procArray);

	fclose(fileToRead);

	if (whichOne == sjf)
	{
	    sortSJF(procArray, numOfProc);
	}
	if (whichOne == fcfs)
	{
	    sortFCFS(procArray, numOfProc);
	}
	if (whichOne == rr)
	{
	    roundRobin(procArray, numOfProc);
	}

	return 0;
}


