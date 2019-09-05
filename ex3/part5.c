#include <stdio.h>
#include <string.h>

int main()
{
  int count[255] = {0};

   FILE *f = fopen("input.txt", "r");
   int c;
   while((c=fgetc(f))){
     if(c == EOF)
      break;
     count[c]+=1;
   }
   for(int i = 0; i<256; i++)
   {
     if(count[i] >0)
     {
       printf("%d instances of character 0x%x (%c)\n", count[i], i, i);
     }
   }
   return 0;
}
