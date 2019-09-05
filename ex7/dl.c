#include<stdio.h>
#include<stdlib.h>
unsigned long dl(unsigned long y,unsigned long g,unsigned long p)
{
  unsigned long x = 0;
  unsigned long result = 1;
  while(result!=y)
  {
    result = result*g%p;
    x++;
  }
  return x;
}


int  main(int argc, char **argv)
{
  printf("dl is %lu \n",dl(6,2,13));
  printf("dl is %lu \n",dl(64675,3,65537));
}
