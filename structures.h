

typedef struct Process
{
    char name[100];
	int arrivalTime;
	int burstTime;
}Process;


typedef enum
{
    sjf,
    fcfs,
    rr,
}AlgorithmToCall;

