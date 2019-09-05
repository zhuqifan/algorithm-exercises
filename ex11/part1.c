#include "graph.h"


int maxout = 0;
int maxin = 0;
int minin = 10000;

char *p1;
char *p2;
char *p3;

void extrem(Graph *mygraph)
{
  int i;
  for (i=0; i<mygraph->MaxSize; i++)
  {
    if (mygraph->table[i].name!=NULL)
    {
      //printf ("NODE %d %s\n", i, mygraph->table[i].name);
      if(maxout<mygraph->table[i].outdegree)
      {
        maxout= mygraph->table[i].outdegree;
        p1 = mygraph->table[i].name;
      }
      if(maxin<mygraph->table[i].indegree)
      {
        maxin = mygraph->table[i].indegree;
        p2 = mygraph->table[i].name;
      }
      if(minin>mygraph->table[i].indegree && mygraph->table[i].indegree!=0)
      {
        minin = mygraph->table[i].indegree;
        p3 = mygraph->table[i].name;
      }
    }
  }
  printf ("largest out-degree : %d, name: %s\n", maxout,p1);
  printf ("largest in-degree : %d, name: %s\n", maxin,p2 );
  printf ("smallest (non-zero) in-degree : %d, name: %s\n", minin,p3);
}
int main(int argc,char *argv[])
{
  Graph mygraph;

  read_graph(&mygraph,argv[1]);
  print_graph (&mygraph);
  /* you take it from here */
//  print_graph (&mygraph);

  extrem(&mygraph);


  return(0);
}
