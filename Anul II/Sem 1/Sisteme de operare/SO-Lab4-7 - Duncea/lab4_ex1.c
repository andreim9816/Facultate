#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	int pid;
	pid = fork();
	if(pid ==0)
	{
		char * argv[] = {"ls",NULL};
		execve("/bin/ls",argv,NULL);
		return 1;
	}
	
	//Parent
	printf("My PID %d, Child PID %d\n",getpid(),pid);
	
	wait(NULL);
	printf("Child %d finished\n",pid);
	return 0;
}
