#include "graph.h"
/* Good luck */

// double *queue  = malloc(2000 * sizeof(double));

void searchBFS(Graph *mygraph, int start){
  int maximum = mygraph->MaxSize;
  int queue[maximum];
  for (int i = 0; i < maximum; i++)
    queue[i] = -1;
  //
  // printf("waefwae %d",queue[1000]);

  queue[0] = start;
  int front = 0, rear = 1;

  while(queue[front] != -1){
    List *current;
    mygraph->table[queue[front]].visited++;
    current = mygraph->table[queue[front]].outlist;
    front++;

    while (current!=NULL) {
      if(mygraph->table[current->index].visited == 0){
        queue[rear] = current->index;
        mygraph->table[queue[rear]].visited++;
        rear++;
      }
      current = current->next;
    }
  }
  printf("All the nodes visited: ");
  for (int i = 0; i < maximum; i++){
    if(mygraph->table[i].visited != 0)
      printf ("NODE %s ", mygraph->table[i].name);
  }
  printf ("\n");
}

void searchDFS(Graph *mygraph, int start){
  int maximum = mygraph->MaxSize;

  int queue[maximum];
  for (int i = 0; i < maximum; i++)
    queue[i] = -1;

    //printf("waefwae %d",queue[1]);
  queue[1] = start;
  int top = 1;
  while(queue[top] != -1){
    List *current;
    mygraph->table[queue[top]].visited++;
    current = mygraph->table[queue[top]].outlist;
    top--;

    while (current!=NULL) {
      if(mygraph->table[current->index].visited == 0){
        top++;
        queue[top] = current->index;
        mygraph->table[queue[top]].visited++;
      }
      current = current->next;
    }
  }
  printf("All the nodes visited: ");
  for (int i = 0; i < maximum; i++){
    if(mygraph->table[i].visited != 0)
      printf ("NODE %s ", mygraph->table[i].name);
  }
  printf ("\n");
}
