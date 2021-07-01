#include<unistd.h>
#include<wait.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<errno.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void XorShift32(unsigned int **v, unsigned int dim, unsigned int seed)
{
    /* function that generates an array of pseudo-random numbers, based on the seed value */
    int i;

    *v = (unsigned int *)malloc( sizeof(unsigned int)* dim);
    if(!(*v))
    {
        perror("Eroare la alocarea de memorie pentru vectorul de numere aleatoare ");
        return;
    }

    (*v)[0] = seed;

    for(i = 1 ; i < dim ; i++)
    {
        unsigned int r;
        r = (*v)[i-1];
        r = r ^ r <<13;
        r = r ^ r >>17;
        r = r ^ r <<5;
       (*v)[i] = r;
    }
}

void Durstenfeld(unsigned int **perm, int dim, unsigned int *v)
{
    int i;
    /* function that generates a random permutation */
    *perm=(unsigned int*)malloc(sizeof(unsigned int) * dim);
    if(!(*perm))
    {
        perror("Eroare la alocarea de memorie a vectorului");
        return;
    }

    for(i = dim - 1 ; i >= 0 ; i--)
        (*perm)[i] = i;

    for(i = dim - 1 ; i >= 1 ; i--)
    {
        unsigned int r = v[dim - i] % (i + 1); // generates a random number
        unsigned int aux = (*perm)[r];
        (*perm)[r] = (*perm)[i];
        (*perm)[i] = aux;
    }
}

int permut(char **encrypt, char *cuv, unsigned int *permutare , unsigned int dim)
{
	/* function that permutes the characters of a word */
    int i;
    *encrypt = malloc(sizeof(char) * dim);

    if(!(*encrypt))
    {
        perror(NULL);
        return 0;
    }

    for(i = 0 ; i < dim ; i++)
     (*encrypt)[permutare[i]] = cuv[i];
}

int save_shared_memory(FILE *f , int shm_fd , int nr_cuv , char*shm_name)
{
/* function that loads into a shared memory the content of a file */
  int i;
  for(i = 1 ; i <= nr_cuv ; i++)
  {
    char *shm_ptr = mmap(0, getpagesize(), PROT_WRITE , MAP_SHARED , shm_fd , (i-1) * getpagesize());

    if(shm_ptr == MAP_FAILED)
    {
      printf("EROARE");
      perror(NULL);
      shm_unlink(shm_name);
      return errno;
    }

    // loads into memory each word
    char string[100];
    int index;
    fscanf(f , "%s" , string);
    for(index = 0 ; index < strlen(string); index++)
    {
      shm_ptr[0] = string[index];
      shm_ptr++;
    }
    *shm_ptr = '\0';
   }
}

