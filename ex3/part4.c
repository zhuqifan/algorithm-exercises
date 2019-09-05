#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float c2f(float c)
{
 float f = 9*c/5 +32;
 return f;
}


float f2c(float f)
{
  float c = (f-32)*5/9;
  return c;
}


int main(int argc, char *argv[])
{
  float f1;
  float c1;
  if(argc<3)
   printf("3 arguments needed");
  else{
    if (strcmp(argv[1],"-c"))
    {
      sscanf(argv[2], "%f", &f1);
      if(f2c(f1) < -273.15)
       printf("the value is too small");
      else
       printf("%fC = %fF", f2c(f1), f1);
    }
    if(strcmp(argv[1],"-f"))
    {
      sscanf(argv[2], "%f", &c1);
      if(c1 < -273.15)
        printf("the value is too small");
      else
        printf("%fC = %fF", c1, c2f(c1));
    }
  }
  printf("\n");
  return 0;
}
