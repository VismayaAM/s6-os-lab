#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

struct Process{
	int pid;
	int arrT;
	int burstT;
	int turnT;
	int waitT;
	int compT;
	int remain;
};

int main(){
	struct Process processes[20];
	int p;
	int count=0;
	int time=0;
	int smallest=0;
	float wait_time;
	float turnaround_time;
	int totTime=0;
	printf("Enter the number of processes: ");
    scanf("%d", &p);
	printf("Enter arrival time and Burst Time:\n");
    for(int i=0;i<p;i++){
		printf("%d: ",i+1);
		scanf("%d%d",&processes[i].arrT,&processes[i].burstT);
		processes[i].remain=processes[i].burstT;
		totTime+=processes[i].burstT;
		if(processes[i].arrT<=processes[smallest].arrT){
			smallest=i;
			time=processes[smallest].arrT;
		}
		processes[i].pid=i+1;

    }
    int flag=0;
    processes[19].remain=1000;
    

	for(time=time;count!=p;time++){
		
		smallest=19;
		for(int i=0;i<p;i++){

			if(processes[i].arrT<=time && processes[i].remain<processes[smallest].remain && processes[i].remain>0){
				smallest=i;
				printf("%d%d\n",smallest,processes[smallest].remain);
			}
		}
		
		if(processes[smallest].remain>0){
			processes[smallest].remain-=1;
			if(processes[smallest].remain==0){
				flag=1;
			}
		}
		
		if(processes[smallest].remain==0 && flag==1){
			count++;
			processes[smallest].compT=time+1;
    		processes[smallest].turnT=processes[smallest].compT-processes[smallest].arrT;
    		processes[smallest].waitT=processes[smallest].turnT-processes[smallest].burstT;
    		wait_time += processes[smallest].waitT;
            turnaround_time += processes[smallest].turnT;
    		flag=0;
		}
		

	}
    
    printf("Si No:\tArrival Time\tBurst Time\tWaiting time\tTurnAround Time\n");
  
    for(int i=0;i<p;i++){
        				printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",processes[i].pid,processes[i].arrT,processes[i].burstT,processes[i].waitT,processes[i].turnT);
    }
      printf("\n\nAverage Waiting Time:\t%f\n", wait_time/(float)p);
    printf("Average Turnaround Time:\t%f\n", turnaround_time/(float)p);
    
    return 0;
 }
