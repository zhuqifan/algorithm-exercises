#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
  if(argc <= 0)
   printf("you have to put some words in command line");
  else
   {
     int length;
     for(int i = 1; i < argc; i++)
     {
       if(length< strlen(argv[i]))
        length = strlen(argv[i]);
     }
     for(int j = 1; j< argc; j++)
     {
       if(length == strlen(argv[j]))
        printf("longest parameter is '%s\n'", argv[j]);
     }
   }
   return 0;
}
