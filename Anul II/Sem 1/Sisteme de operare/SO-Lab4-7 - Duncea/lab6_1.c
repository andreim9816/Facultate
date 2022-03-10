#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>

void * second(void *v)
{
	char * text = v;
	printf("%s\n",text);
	int n = strlen(text);
	char * result = malloc(n + 1);
	int i,j=n-1;
	for(i=0;i < n;i++)
	{
		result[i] = text[j--];
	}
	result[n] = 0;
	
	//return 
	return result;
}


int main(int argc, char* argv[])
{
	//Verify arguments
	if(argc!=2)
	{
		printf("Wrong argument count!");
		return 0;
	}
	
	pthread_t thread_two;

	//Create second thread
	if(pthread_create(&thread_two,NULL,second,argv[1]))
	{
		perror(NULL);
		return errno;
	}
	void * result;
	//Wait for second thread to finish
	if(pthread_join(thread_two,&result))
	{
		perror(NULL);
		return errno;
	}

	printf("%s\n",(char*)result);
	free(result);
}
