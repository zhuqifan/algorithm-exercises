#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
FILE *fp;

typedef struct book
{
  double rating;
  double price;
  double relevance;
  int ID;
} B;
typedef int(*FUNC_PTR)(const void *,const void *);
B *list;

int read_file(char *infile, int N)
{
  int c;
  if((fp=fopen(infile, "rb")))
    {
      fscanf(fp, "%*s\t%*s\t%*s\t%*s\n");
      c=0;
      while((!feof(fp))&&(c<N))
	{
	  fscanf(fp, "%lf\t%lf\t%lf\t%d\n", &list[c].rating,  &list[c].price, &list[c].relevance, &list[c].ID);
	  c++;
	}
      fclose(fp);
    }
      else
    {
      fprintf(stderr,"%s did not open. Exiting.\n",infile);
      exit(-1);
    }
  return(c);
}

int comp_on_rating(const void *a, const void *b)
{
  if ((*(B *)a).rating < (*(B *)b).rating)
  {
     return -1;
  }
    else
  {
    if ((*(B *)a).rating > (*(B *)b).rating)
    {
      return 1;
    }
      else
    {
      return 0;
    }
  }
}

int comp_on_relev(const void *a, const void *b)
{

  if ((*(B *)a).relevance < (*(B *)b).relevance)
  {
     return -1;
  }
     else
  {
     if ((*(B *)a).relevance > (*(B *)b).relevance)
     {
       return 1;
     }
       else
     {
       return 0;
     }
  }
}

int comp_on_price(const void *a, const void *b)
{

  if ((*(B *)a).price < (*(B *)b).price)
  {
     return 1;
  }
     else
  {
     if ((*(B *)a).price > (*(B *)b).price)
     {
       return -1;
     }
       else
     {
       return 0;
     }
  }
}

void mergesort(B *list, int l, int m, int r,FUNC_PTR compareBy)
{
    int i;
    int k;
    int j;
    int x = m - l + 1;
    int y =  r - m;

    /* create temp arrays */
    B *listL;
    B *listR;
    listL = (B *)malloc(x*sizeof(B));
    listR = (B *)malloc(y*sizeof(B));
    /* Copy data to temp arrays listL[] and listR[] */
    for (i = 0; i < x; i++)
        listL[i] = list[l + i];
    for (j = 0; j < y; j++)
        listR[j] = list[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < x && j < y)
    {
        if (compareBy(&listL[i], &listR[j]) <= 0)
        {
            list[k] = listL[i];
            i++;
        }
        else
        {
            list[k] = listR[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of listL[], if there
       are any */
    while (i < x)
    {
        list[k] = listL[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of listR[], if there
       are any */
    while (j < y)
    {
        list[k] = listR[j];
        j++;
        k++;
    }
}
//http://www.geeksforgeeks.org/merge-sort/
void mySort(B *list, int l, int r, FUNC_PTR compareBy)
{
  if (l < r)
  {
      // Same as (l+r)/2, but avoids overflow for
      // large l and h
      int m = l+(r-l)/2;

      // Sort first and second halves
      mySort(list, l, m,compareBy);
      mySort(list, m+1, r,compareBy);

      mergesort(list, l, m, r,compareBy);
  }
}
void user_interface(int N)
{

  // For Part 1 this function calls the sort function to sort on Price only
  // For Part 2 this function
  FUNC_PTR compareBy;
  char *ifsort = malloc(sizeof(char));
  char *c1 = malloc(sizeof(char));
  char *c2 = malloc(sizeof(char));
  char *c3 = malloc(sizeof(char));
  // (1) asks the user if they would like to sort their search results
  printf("Would you like to sort the search results? y/n\n");
  scanf("%s",ifsort);
  if (strcmp(ifsort,"n") != 0)
  {
    printf("What is the most important key,rating/price/relevance?\n");
    scanf("%s",c1);
    printf("What is the most important key,rating/price/relevance/none?\n");
    scanf("%s",c2);
    printf("What is the most important key,rating/price/relevance/none?\n");
    scanf("%s",c3);
  }
  // (2) asks for the most important field (or key), the next most etc
  // (3) calls your sort function
  if (strcmp(c3,"rating") == 0){
    compareBy = &comp_on_rating;
    mySort(list,0,N-1,compareBy);
  }
  else if (strcmp(c3,"price") == 0){
    compareBy = &comp_on_rating;
    mySort(list,0,N-1,compareBy);
  }
  else if (strcmp(c3,"relevance") == 0){
    compareBy = &comp_on_rating;
    mySort(list,0,N-1,compareBy);
  }
  if (strcmp(c2,"rating") == 0){
    compareBy = &comp_on_rating;
    mySort(list,0,N-1,compareBy);
  }
  else if (strcmp(c2,"price") == 0){
    compareBy = &comp_on_rating;
    mySort(list,0,N-1,compareBy);
  }
  else if (strcmp(c2,"relevance") == 0){
    compareBy = &comp_on_rating;
    mySort(list,0,N-1,compareBy);
  }
  if (strcmp(c1,"rating") == 0){
    compareBy = &comp_on_rating;
    mySort(list,0,N-1,compareBy);
  }
  else if (strcmp(c1,"price") == 0){
    compareBy = &comp_on_rating;
    mySort(list,0,N-1,compareBy);
  }
  else if (strcmp(c1,"relevance") == 0){
    compareBy = &comp_on_rating;
    mySort(list,0,N-1,compareBy);
  }

}


void print_results(int N)
{
    int i;
    if((fp=fopen("top20.txt","w")))
    {
      for(i=N-1;i>=N-20;i--)
      {
	  printf("%g    %g    %g    %d\n", list[i].rating, list[i].price, list[i].relevance, list[i].ID);
	  fprintf(fp, "%g    %g    %g    %d\n", list[i].rating, list[i].price, list[i].relevance, list[i].ID);

      }
      fclose(fp);
    }
      else
    {
      fprintf(stderr,"Trouble opening output file top20.txt\n");
      exit(-1);
    }

}


int main(int argc, char *argv[])
{
  int N;

  if(argc!=3)
    {
      fprintf(stderr, "./exec <input_size> <filename>\n");
      exit(-1);
    }

  N=atoi(argv[1]);

  list = (B *)malloc(N*sizeof(B));

  N=read_file(argv[2], N);

  user_interface(N);

  print_results(N);

  return(0);
}
