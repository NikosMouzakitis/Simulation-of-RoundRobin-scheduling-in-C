#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//	Simulating 4 processes,in a CPU scheduler.
//	Estimating average time per process,total time
//	and time of swapping processes into CPU.

//	author:Mouzakitis Nikolaos,Crete 2017.

struct process
{
	double time_req;
	int id;
};

void round_robin_sjf(struct process *p,int len,double *quantum,double *swap_time)
{
	int i,j,swap_proc_cnt = 0,cflag = 0,check = 0;	//cflag on 1 will indicate that all processes completed.
	double temp,time = 0.0;
	double *pt = (double *) malloc(len*sizeof(double));	//by checking this array we will schedule.
	double *remain = (double *) malloc(len*sizeof(double));
	int *completed = (int *) malloc(len*sizeof(int));
	
	printf("\n\n");	
	printf("Simulating Round Robin Algorithm (implemented with initialized SJF scheduling)- [ %d processes].\n",len);
	printf("run__\n");

	for(i = 0; i <len; i++)
		*(completed + i) = 0;	//setting all elements of array to 0.(no process is complete at first place)
	
	for(i = 0; i < len ; i++)
		*(pt + i) = (p+i)->time_req;

	for(i = 0; i < len-1; i++)
		for(j = i+1; j < len; j++)
			if( *(pt+i) > *(pt + j) )
			{
				temp = *(pt + i);
				*(pt + i) = *(pt + j);	//sorting out times to implement SJF.
				*(pt + j ) = temp;			
			}
	
	for(i = 0; i < len; i++)
		*(remain + i) = *(pt+i);	//copying sorted times to remaining time's array for each process.

	printf("Processes/Execution_time_required.\n");

	for(i = 0; i <len; i++)
		printf("%d	%f\n",i,*(remain+i));
	printf("Quantum_exec:%f\nSwap_time:%lf\n",*quantum,*swap_time);
	
	while(!cflag)
	{		
		for(i = 0; i < len; i++)
			if(*(remain + i) > 0.0)
			{
				if(*(remain + i) > *quantum)
				{
					*(remain + i ) -= *quantum;
					time += *quantum;
					time += *swap_time;
					swap_proc_cnt++;
				}
				else
				{
					time += *(remain+i) ;
					time += *swap_time;
					swap_proc_cnt++;
					*(remain+i) = 0.0;
				}
			}

	/*	Checking every loop for termination	*/
				
		for(i = 0; i < len; i++)
			if(*(remain + i ) <= 0.0)
				*(completed + i ) = 1;

		for(i = 0,check = 0; i <len; i++)
			check += *(completed + i);	// (if all processes complete adding up len * 1 will give us len)

		if(check == len)
			cflag = 1;	//all processes completed.		
	}	

	printf("Total time: %f\t Total swaps in CPU: %d\n",time,swap_proc_cnt);
	printf("average time per process: %f\n",time/len);
}

int main(int argc,char *argv[])
{
	double quantum   = 0.0005;	
	double swap_time = 0.00005;	
	struct process pin[4],*p;
		
	p = pin;

	pin[0].id = 1;
	pin[1].id = 2;
	pin[2].id = 3;
	pin[3].id = 4;

	pin[0].time_req = 1.4;
	pin[1].time_req = 0.5;
	pin[2].time_req = 1;
	pin[3].time_req = 0.7;

	round_robin_sjf(p,4,&quantum,&swap_time);

	return 0;
}