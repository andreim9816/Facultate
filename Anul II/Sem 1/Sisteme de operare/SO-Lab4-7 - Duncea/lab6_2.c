#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>

int a[3][3] = {{1,2,3},{3,2,1},{3,3,3}};
int b[3][3] = {{4,7,3},{3,1,1},{3,2,3}};
int c[3][3];

struct date
{
	int dim;
	int linie;
	int coloana;
};

void * calculate(void *v)
{
	struct date *d = v;
	int i, rez = 0;
	//printf("%d %d\n",d->linie,d->coloana);
	for(i=0;i < d->dim ;i++)
	{
		rez += a[d->linie][i] * b[i][d->coloana];
	}
	c[d->linie][d->coloana] = rez;

	free(d);
	//return 
	return NULL;
}


int main(int argc, char* argv[])
{
	
	pthread_t thread_matrix[3][3];
	
	int i,j;
	for(i =0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			struct date *d = malloc(sizeof(struct date));
			d->dim = 3;
			d->linie = i;
			d->coloana = j;
			//Create second thread
			if(pthread_create(thread_matrix[i] + j, NULL, calculate,d))
			{
				perror(NULL);
				return errno;
			}
		}
	}
	
	//Wait for all the threads
	for(i =0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			if(pthread_join(thread_matrix[i][j],NULL))
			{
				perror(NULL);
				return errno;
			}
			printf("%d ",c[i][j]);
		}
		printf("\n");
	}
}
