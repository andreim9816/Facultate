#include <stdlib.h>
#include <errno.h>
#include <semaphore.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

#define MAX_RESOURCES 10
int available_resources = MAX_RESOURCES;

pthread_mutex_t mtx;

int decrease_count(int count)
{
	int ret =0;
	//lock mutex
	pthread_mutex_lock(&mtx);
	if(available_resources >= count)
	{

		available_resources -=count;
		printf("Got %d resources %d remaining\n",count, available_resources); 
	}
	else
		ret = -1;
	pthread_mutex_unlock(&mtx);

	return ret;
}

int increase_count(int count)
{
	//increment safely
	pthread_mutex_lock(&mtx);
	available_resources +=count;
	printf("Released %d resources %d remaining\n",count, available_resources);
	pthread_mutex_unlock(&mtx);
	return 0;
}


void * sim_work(void *v)
{
	int i;
	//get a number between 1 and 10
	int want = rand() % 9 + 1;
	
	//Sched_yield ?
	while( decrease_count(want) <0);
	
	//Be romanian parlamentar
		//Simulate work
	for(i=0;i<10000;i++)
	{	
		i++;
		i--;
	}
	increase_count(want);
	return NULL;
}

int main()
{
	//initialize rand
	srand(time(0)); 
	
	//Init mutex
	if(pthread_mutex_init(&mtx,NULL))
	{
		perror(NULL);
		return errno;
	}
	
	
	pthread_t threads[10];
	int i;
	for(i = 0;i<10;i++)
	{
		if(pthread_create(threads + i, NULL, sim_work, NULL))
		{
			perror(NULL);
			return errno;
		} 
	}

	for(i = 0;i<10;i++)
	{
		if(pthread_join(threads[i], NULL))
		{
			perror(NULL);
			return errno;
		} 
	}
	
	

	//eliberare resurse
	pthread_mutex_destroy(&mtx);

	return 0;
}




