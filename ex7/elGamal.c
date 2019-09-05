#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
#include <math.h>
#define MOD 100000
unsigned long hcf(unsigned long a,unsigned long b)
{
  unsigned long gcd;
  for(int i=1; i<=a&&i<=b; i++)
  {
    if(a%i==0&&b%i==0)
      gcd = i;
      printf("%d\n", i);
  }
  return gcd;
}

unsigned long fme(unsigned long g,unsigned long x,unsigned long p)
{
  unsigned long y=1;// Initialize result
  g = g%p;// Update g if it is more than or
                 // equal to p
  while(x>0)// If x is odd, multiply g with result
  {
    if(x&1)
      y = (y*g)%p;

       // x must be even now
    x = x/2;
    g = (g*g)%p;
  }
  return y;
}

unsigned long dl(unsigned long y,unsigned long g,unsigned long p)
{
  unsigned long x;
  for(x=1;x<p;x++)
  {
    if(fme(g,x,p)==y)
      return x;
  }
  return 0;
}

unsigned long imp(unsigned long y, unsigned long p)
{

  return fme(y,p-2,p);
}

long long int power (long long int a, long long int b) {
    long long int ans=1ll;
    while(b) {
        if(b&1)ans=(ans*a)%MOD;
        a=(a*a)%MOD;
        b=b/2;
    }
    return ans;
    }

int  main(int argc, char **argv)
{
  srand(time(NULL));
  hcf(1000,200);
  printf("gcd is %lu \n",hcf(1000,200));
  printf("power is %lu \n",fme(3,40000,65537));
  printf("dl is %lu \n",dl(6,2,13));
  printf("imp is %lu \n",imp(5,7));
  unsigned long privatekey = malloc(sizeof(unsigned long));
  unsigned long secretnum = malloc(sizeof(unsigned long));
  unsigned long publickey = malloc(sizeof(unsigned long));
  unsigned long a = malloc(sizeof(unsigned long));
  unsigned long b = malloc(sizeof(unsigned long));
  char *choice = malloc(sizeof(char));
  unsigned long g = 3;
  unsigned long p = 65537;
  printf("cao ni ma bi %lu\n",imp(64675,65537));
  printf("Prime modulus is 65537\n");
  printf("Primitive root wrt 65537 is 3\n");
  printf("Choose: e (encrypt) | d (decrypt) |k (get public key) | x (exit)?");
  scanf("%s",choice);
  while(strcmp(choice,"x")!=0)
  {
    if(strcmp(choice,"k")==0)
    {
      printf("Type private key: ");
      scanf("%lu", &privatekey);
      publickey = fme(g,privatekey,p);
      printf("Public key is: %lu\n",publickey);
    }
    else if(strcmp(choice,"e")==0)
    {
      printf("Type secret number to send: ");
      scanf("%lu", &secretnum);
      printf("Type recipient’s public key: ");
      scanf("%lu", &publickey);
      unsigned long k = 1+rand()%(p-1);
      printf("The encrypted secret is: (%lu, %lu)\n",fme(g,k,p),(secretnum*power(publickey,k))%p);

    }
    else if(strcmp(choice,"d")==0)
    {
      printf("Type in received message in form (a,b):");
      scanf("%lu%lu",&a,&b);
      printf("Type in your private key:");
      scanf("%lu",&privatekey);
      printf("The decrypted secret is: %d\n", b*imp(fme(a,privatekey,65537),65537)%65537);
    }
    printf("Choose: e (encrypt) | d (decrypt) |k (get public key) | x (exit)?");
    scanf("%s",choice);
  }
  return 0;
}
