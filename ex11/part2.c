#include "graph.h"
#define DFS
#undef BFS

int main(int argc,char *argv[])
{
  Graph mygraph;
  read_graph(&mygraph,argv[1]);
  /* you take it from here */



  //print_graph(&mygraph);

  int position;
  printf("the start point is : \n");
  scanf("%d",&position);

  #ifdef DFS
  searchDFS(&mygraph,position);
  #endif

  #ifdef BFS
  searchBFS(&mygraph,position);
  #endif

  return(0);
}
