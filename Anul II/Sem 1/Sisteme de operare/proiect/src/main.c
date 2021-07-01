#include"criptare.h"
#include"decriptare.h"
#include"multiple_use.h"
#include<string.h>

/* main function, that encrypts / decrypts a file, depending on the parameters given in the terminal */

int main(int argc, char**argv)
{
  if(argc < 5)
  {
    printf("Need more arguments!\n");
    return 0;
  }

  if(strcmp("encrypt" , argv[1]) == 0)
   criptare(argv[2], argv[3], argv[4]);

  else if(strcmp("decrypt" , argv[1]) == 0)
   decriptare(argv[2], argv[3], argv[4]);

  else
  {
    printf("First paramter must be either << encrypt >> or << decrypt >> \n");
    return 0;
  }

return 0;
}
