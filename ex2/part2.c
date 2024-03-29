#include <stdio.h>  // FILE stderr fopen fclose fprintf printf fgets
#include <stdlib.h> // exit malloc free atoi abs
#include <ctype.h>

int main(int argc, char *argv[])
{
 //char *filename = argv[1];
  int numberOfLower = 0;
  int numberOfUpper = 0;
  int numberOfChar = 0;
  char *inputfile[20];
  char *outputfile[20];
  printf("please enter inputfile and outputfile\n");
  scanf("%s %s",&inputfile,&outputfile);

  // A stream for getting data from the user.
  FILE *stream= fopen(inputfile, "r");
  FILE *f = fopen(outputfile, "w");
  if(f == NULL)
  {
    printf("Error opening file!\n");
    exit(1);
  }

  if (!stream)
  {
    fprintf(stderr, "can't open %s for reading\n", inputfile);
    exit(-1);
  }
  int buffer_size = 200;
  char data[200];

  while(fgets(data, buffer_size, stream))//salariesScanner.hasNextLine())
  {
    int index = 0;
    char currentChar;
    while((currentChar = data[index])!= '\0')
    {
       if(isupper(currentChar))
       {
         numberOfUpper++;
         putchar(tolower(currentChar));
         fprintf(f, "%c", tolower(currentChar));
       }
       else if(islower(currentChar))
       {
         numberOfLower++;
         putchar(toupper(currentChar));
         fprintf(f, "%c", toupper(currentChar));
       }
      else
       {
         putchar(currentChar);
         fprintf(f, "%c", currentChar);
      }
      index++;
      numberOfChar++;
    }
  }
  printf("Read %d characters in total, %d converted to upper-case, %d to lower-ase",numberOfChar ,numberOfUpper, numberOfLower);
  fprintf(f, "Read %d characters in total, %d converted to upper-case, %d to lower-ase",numberOfChar ,numberOfUpper, numberOfLower);
  fclose(f);
  fclose(stream);
  return(0);
}
