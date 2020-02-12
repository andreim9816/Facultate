#include<unistd.h>
#include<wait.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<errno.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"decriptare.h"
#include"multiple_use.h"

/* Functions that decrypts the words */

int decrypt_cuv(char**permuted , int dim , char*cuv_encrypted,unsigned int *random, unsigned int SV)
{
   int i;
   *permuted = malloc(sizeof(char) * dim);
   if(!(*permuted))
   {
     perror(NULL);
     return errno;
   }

    /* Using the xor operation, it decrypts each character */
   (*permuted)[0] = SV ^ cuv_encrypted[0] ^ random[0];
   for(i = 1 ; i < dim ; i++)
    (*permuted)[i] = cuv_encrypted[i-1] ^ cuv_encrypted[i] ^ random[i];
  }

int gen_perm_invers(unsigned int **perm_invers , int dim , unsigned int *perm)
{
	/* function that generates an inverse permutation */
  *perm_invers = (unsigned int*)malloc(sizeof(unsigned int) * dim);
  if(!(*perm_invers))
  {
    perror(NULL);
    return errno;
  }

  int i;
  for(i = 0 ; i < dim ; i++)
   (*perm_invers)[perm[i]] = i;
}

int decriptare(char *in, char *out, char *secret)
{
	/*main function that decrypts a word */
  unsigned int SV = 0;
  unsigned int seed = 0;

  /* pointer to the file that contains the secret key */
  FILE *f_secret = fopen(secret, "r");
  if(!f_secret)
  {
    perror(NULL);
    return errno;
  }

  fscanf(f_secret,"%u" , &seed);
  fscanf(f_secret,"%u" , &SV);

  fclose(f_secret);

  // name of the shared memory
  char shm_name2[] = "MemoriePartajata2";

  // shared memory file descriptor
  int shm_fd2 = shm_open(shm_name2, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);

  if(shm_fd2 < 0)
  {
    perror(NULL);
    return errno;
  }

  // pointer to the file that is encrypted
  FILE *fin = fopen(in, "r");
  if(!fin)
  {
    perror(NULL);
    return errno;
  }

  int nr_cuv = 1 , i ,nr = 0;
  char str[100];
  char c, last_c;

  // number of words in the encrypted file
  last_c = fgetc(fin);
  if(last_c != EOF)
    while( (c = fgetc(fin)) != EOF)
    {
      if(c != ' ' && last_c == ' ')
       nr_cuv++;
      last_c = c;
    }
  else nr_cuv = 0;

  fclose(fin);

  fin = fopen(in , "r");
  if(!fin)
  {
    perror(NULL);
    return errno;
  }

   // the size of the total memory ( each word is contained in a page
  int shm_size = getpagesize() * nr_cuv;

   // truncates the memory to its size
  if(ftruncate(shm_fd2, shm_size) == -1)
  {
      perror(NULL);
      shm_unlink(shm_name2);
      return errno;
  }

  // saves in memory the words from the file
  save_shared_memory(fin , shm_fd2 , nr_cuv , shm_name2);
  fclose(fin);

  // pointer to the memory where the words are memorized
  char *shm_ptr2 = mmap(0, shm_size, PROT_READ , MAP_SHARED , shm_fd2 , 0);
  if(shm_ptr2 == MAP_FAILED)
  {
      perror(NULL);
      shm_unlink(shm_name2);
      return errno;
  }

  // pointer to the file that will contain the decrypted file
  FILE *fout = fopen(out, "w+");
  if(!fout)
  {
    perror(NULL);
    return errno;
  }


int status;

 // starts encrypting each word, one word per process
for(i = 1 ; i <= nr_cuv ; i++)
{
  int pid = fork(); // generates a new process

  unsigned int *pseudo_aleator;
  unsigned int *permutare;
  unsigned int *permutare_invers;
  char *cuvant_permutat;
  char *cuvant_encrypt;

  if(pid < 0 )
  {
    perror(NULL);
    return errno;
  }
  else if(pid == 0)
  {
    // if we're in the child process, then we decrypt the word
    char *ptr = (char*)(shm_ptr2 + (i-1) * getpagesize());
    int dim = -1;
    char string[100];

    // loads the word from the shared memory
    while(ptr[0] != '\0')
     {
       string[++dim] = *ptr;
       ptr++;
     }
     string[++dim] = '\0';

    XorShift32(&pseudo_aleator , dim , seed); // generates a sequence of pseudo-random numbers
    Durstenfeld(&permutare , dim , pseudo_aleator); // generates a permutation of the pseudo-random numbers
    gen_perm_invers(&permutare_invers , dim , permutare); //generates the invers permutation
    decrypt_cuv(&cuvant_encrypt , dim , string , pseudo_aleator , SV); // decrypts the current word, based on the permutation
    permut(&cuvant_permutat , cuvant_encrypt , permutare_invers , dim); // permutes the charaters of the word

    int k = 0;

    // prints the decrypted word
    for(k = 0 ; k < dim ; k++)
     {
       fprintf(fout, "%c" , cuvant_permutat[k]);
     }
    fprintf(fout," ");

    // free the memory
    free(pseudo_aleator);
    free(permutare);
    free(permutare_invers);
    free(cuvant_encrypt);
    free(cuvant_permutat);

    return 0;
  }
  else waitpid(pid, &status,0);

}
    fclose(fout);

    // free the shared memory
    munmap(shm_ptr2 ,shm_size);
    shm_unlink(shm_name2);
}

