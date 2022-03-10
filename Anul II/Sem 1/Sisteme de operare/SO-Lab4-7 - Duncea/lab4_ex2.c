#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

void collatz(int nr)
{
	if(nr == 1)
	{
		printf("1.\n");
		return;
	}
	if(nr<1)
	{
		printf("Gresit");
		return;
	}
	printf("%d ",nr);
	if(nr% 2==0)
	{
		
		collatz(nr/2);
	}
	else
	{
		collatz(3*nr+1);
	}
}

int main(int argc, char * argv[])
{
	//Check arguments
	if(argc != 2)
	{
		printf("Wrong argument count");
		return 0;
	}

	int pid;
	pid = fork();

	if(pid ==0)
	{
		//Child
		collatz(atoi(argv[1]));
		return 0;
	}
	
	//Parent
	printf("My PID %d, Child PID %d\n",getpid(),pid);
	
	wait(NULL);
	printf("Child %d finished\n",pid);
	return 0;
}
