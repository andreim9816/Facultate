#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

void collatz(int nr)
{
	if(nr == 1)
	{
		printf("1.\n\n");
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
	if(argc < 2)
	{
		printf("Wrong argument count");
		return 0;
	}

	printf("Starting parent: %d\n",getpid());

	for(int i =0;i<argc-1;i++)
	{
		int pid;
		pid = fork();

		if(pid ==0)
		{
			//Child
			printf("%s: ",argv[i+1]);
			collatz(atoi(argv[i+1]));
			return 0;
		}
	}
	
	
	//Parent

	for(int i=0;i<argc-1;i++)
	{
		printf("Child %d finished\n", wait(NULL));
	}

	return 0;
}
