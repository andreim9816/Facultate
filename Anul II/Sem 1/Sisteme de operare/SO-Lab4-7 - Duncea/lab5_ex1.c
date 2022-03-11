#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define CHILD_MEM_SIZE PAGE_SIZE


void Child(int shm_fd,int offset,int nr)
{
	//Map memory
	int * shm_ptr = mmap(0, getpagesize(), PROT_WRITE, MAP_SHARED, shm_fd, getpagesize() * offset);

	//Write first number
	*shm_ptr = nr;
	shm_ptr++;

	//Run collatz	
	while(nr!= 1)
	{
		*shm_ptr = nr;
		shm_ptr++;

		if(nr% 2==0)
			nr = nr/2;
		else
			nr = 3*nr+1;
	}
	//Done collatz
	*shm_ptr = 1;
	shm_ptr++;

	//Write end 
	*shm_ptr = 0;
	shm_ptr++;
	
	//Unmap memory
	munmap( shm_ptr , getpagesize());

	//dONE CHILD
	printf("Done Parent: %d, Me %d \n",getppid(), getpid());
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


	//Get memory
	char   shm_name [ ]   =  "collatz_shm";
	int   shm_fd;
	size_t shm_size = getpagesize() * (argc -1);

	//Deschidere
	shm_fd  =  shm_open ( shm_name ,  O_CREAT|O_RDWR,   S_IRUSR|S_IWUSR ) ;
	if   ( shm_fd<0 )
	{	
		perror (NULL );
		return  errno;
	}
	//Dimensionare
	if(ftruncate(shm_fd, shm_size) == -1)
	{
		perror(NULL);
		shm_unlink(shm_name);
		return errno;
	}
	//Mapare
	void * shm_ptr = mmap(0,shm_size,PROT_READ, MAP_SHARED,shm_fd,0);
	if(shm_ptr == MAP_FAILED)
	{
		perror(NULL);
		shm_unlink(shm_name);
		return errno;
	}
	for(int i =0;i<argc-1;i++)
	{
		int pid;
		pid = fork();

		if(pid ==0)
		{
			//Child
			Child(shm_fd,i,atoi(argv[i+1]));
			return 0;
		}
	}
	
	
	//Parent

	for(int i=0;i<argc-1;i++)
	{
		wait(NULL);	
	}

	for(int i=0;i<argc -1;i++)
	{
		int *child_shm_ptr = (int *) (shm_ptr +getpagesize()*i);
		printf("%d: ",*(child_shm_ptr++));
		
		while (*child_shm_ptr != 0)
			printf("%d ",*(child_shm_ptr++));
		printf(".\n");
	}

	//unlink and unmap memory
	munmap(shm_ptr,shm_size);
	shm_unlink(shm_name);

	return 0;
}