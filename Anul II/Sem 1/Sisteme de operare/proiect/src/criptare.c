#include<unistd.h>
#include<wait.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<errno.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"criptare.h"
#include"multiple_use.h"

/* Functions that encrypt the words */

int encrypt_cuv(char**encrypted , int dim , char*cuv_permuted,unsigned int *random, unsigned int SV)
{
  int i;
  *encrypted = malloc(sizeof(char) * dim);

  if(!(*encrypted))
  {
    perror(NULL);
    return errno;
  }

  /* Using the xor operation, it encrypts each character */
  (*encrypted)[0] = SV ^ cuv_permuted[0] ^ random[0];
  for(i = 1 ; i < dim ; i++)
   (*encrypted)[i] = (*encrypted)[i-1] ^ cuv_permuted[i] ^ random[i];
 }

  /* Main function that encrypts the words from a file */
int criptare(char *in, char *out, char *secret)
{
  unsigned int SV = 0; // strating value
  unsigned int seed = 0; // seed

  // pointer to the secret key file
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
  char shm_name1[] = "MemoriePartajata1";

  // shared memory file descriptor
  int shm_fd1 = shm_open(shm_name1, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);

  // pointer to the file that has to be encrypted
  FILE *fin = fopen(in, "r");
  if(!fin)
  {
    perror(NULL);
    return errno;
  }

  // pointer to the file that contains the new generated encrypted words
  FILE *fout = fopen(out , "w");
  if(!fout)
  {
   perror(NULL);
   return errno;
  }

  if(shm_fd1 < 0)
  {
    perror(NULL);
    return errno;
  }

    int nr_cuv = 1 , i ,nr = 0;
    char str[100];
    char c, last_c;

    // number of words in the file
    last_c = fgetc(fin);
    if(last_c != EOF)
      while( (c = fgetc(fin)) != EOF)
      {
        if(c == ' ' && last_c != ' ')
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
    int shm_size = (nr_cuv) * getpagesize();

    // truncates the memory to its size
    if(ftruncate(shm_fd1, shm_size) == -1)
    {
        perror(NULL);
        shm_unlink(shm_name1);
        return errno;
    }

    // saves in memory the words from the file
    save_shared_memory(fin , shm_fd1 , nr_cuv , shm_name1);
    fclose(fin);

    // pointer to the memory where the words are memorized
    char *shm_ptr2 = mmap(0, shm_size, PROT_READ , MAP_SHARED , shm_fd1 , 0);
    if(shm_ptr2 == MAP_FAILED)
    {
        perror(NULL);
        shm_unlink(shm_name1);
        return errno;
    }

    int status;

    // starts encrypting each word, one word per process
    for(i = 1 ; i <= nr_cuv ; i++)
    {
      int pid = fork(); // generates a new process

      unsigned int *pseudo_aleator;
      unsigned int *permutare;
      char *cuvant_permutat;
      char *cuvant_encrypt;
      char *cuv;

      if(pid < 0 )
      {
        perror(NULL);
        return errno;
      }
      else if(pid == 0)
      {
        // if we're in the child process, then we encrypt the word
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
        permut(&cuvant_permutat , string , permutare , dim); //permute the numbers
        encrypt_cuv(&cuvant_encrypt , dim , cuvant_permutat , pseudo_aleator , SV); // encrypts the current word, based on the permutation
        fprintf(fout , "%s " , cuvant_encrypt); // prints the encrypted word

        // free the memory
        free(pseudo_aleator);
        free(permutare);
        free(cuvant_permutat);
        free(cuvant_encrypt);
        return 0;
      }
     else waitpid(pid , &status , 0);
    }

  fclose(fout);

  // free the shared memory
  munmap(shm_ptr2 ,shm_size);
  shm_unlink(shm_name1);
}
