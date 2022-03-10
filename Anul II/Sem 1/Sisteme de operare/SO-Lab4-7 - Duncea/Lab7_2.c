#include <stdlib.h>
#include <errno.h>
#include <semaphore.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

int count = 0;
int nr = 0;

pthread_mutex_t mtx;
sem_t semafor;

int init(int N)
{
	count = N -1;
	nr = N;
	//Init semafor
	if(sem_init(&semafor, 0 , 0))
	{
		perror(NULL);
		return errno;
	}

	return 0;
}

int barrier_point()
{
	//increment safely
	pthread_mutex_lock(&mtx);
	

	if(count > 0)
	{
		count--;
		pthread_mutex_unlock(&mtx);
		if(sem_wait(&semafor))
		{
			perror(NULL);
			return errno;
		}
	}
	else
	{	
		pthread_mutex_unlock(&mtx);		
		int i;
		for(i =0;i < nr - 1;i++)
		{
			if(sem_post(&semafor))
			{
				perror(NULL);
				return errno;
			}
		}
	}
	
	return 0;
}


void * thr_work(void *v)
{
	int *tid = (int *) v;
	printf("%d reached the barrier\n", *tid);
	barrier_point();
	printf("%d passed the barrier\n", *tid);

	free(tid);
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

	//Init semafor
	init(10);	

	pthread_t threads[10];
	int i;
	for(i = 0;i<10;i++)
	{
		int * tid = malloc(sizeof(int));
		*tid = i;
		if(pthread_create(threads + i, NULL, thr_work, tid))
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




