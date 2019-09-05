#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#define __USE_BSD // make prototype for strdup visible
#include <string.h>

typedef struct linkedlist { // linked list of ints (for use in Node)
	int index;
	struct linkedlist *next;
} List;

typedef struct { // a Node of a Graph
	char *name;
	List *outlist; // adjacency list
	int outdegree; // length of outlist
	int indegree;
//double pagerank_score; //not needed for this exercise
} Node;

typedef struct {
	// your code goes here
	int MaxSize;
	Node *table;
} Graph;

/** -------------graph functions ---------------**/

int initialize_graph(Graph *mygraph, int MaxSize) {
	// your code goes here
	mygraph->MaxSize = MaxSize;
	mygraph->table = (Node *) calloc(sizeof(Node), MaxSize);
	for (int i = 0; i < MaxSize; i++) {
		mygraph->table[i].indegree = 0;
		mygraph->table[i].outdegree = 0;
	}

	return 0;
}

int insert_graph_node(Graph *mygraph, int n, char *name) {
	// your code goes here
	mygraph->table[n].name = strdup(name);

	return 0;

}

int insert_graph_link(Graph *mygraph, int source, int target) {
	// your code goes here
	List *targetList = (List*) malloc(sizeof(List));
	targetList->index = target;
	targetList->next = NULL;

	if (mygraph->table[source].outlist == NULL) {
		mygraph->table[source].outlist = targetList;
	}
	else
	{
		List *sourceList = mygraph->table[source].outlist;
		while (sourceList->next != NULL)
		 {
			sourceList = sourceList->next;
		}
		sourceList->next = targetList;
	}//else
	mygraph->table[target].indegree++;
	mygraph->table[source].outdegree++;

	return 0;
}

// use to check result of strdup, malloc etc.
void check(void *memory, char *message) {
	if (memory == NULL) {
		fprintf(stderr, "Can't allocate memory for %s\n", message);
		exit(3);
	}
}
int read_graph(Graph *mygraph, char *filename)
/*
 * Reads in graph from FILE *filename which is of .gx format.
 * Stores it as Graph in *mygraph.
 * Returns an error if file does not start with MAX command,
 * or if any subsequent line is not a NODE or EDGE command.
 * Does not check that node numbers do not exceed the maximum number
 * Defined by the MAX command.
 * 8/2/2010 - JLS
 */
{
	FILE *fp;
	char command[80], name[80];
	int i, s, t;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		fprintf(stderr, "cannot open file %s\n", filename);
		return -1;
	}
	printf("Reading graph from %s\n", filename);
	fscanf(fp, "%s", command);
	if (strcmp(command, "MAX") != 0) {
		fprintf(stderr, "Error in graphics file format\n");
		return -1;
	} else {
		fscanf(fp, "%d", &i);
		initialize_graph(mygraph, i + 1); // +1 so nodes can be numbered 1..MAX
		while (fscanf(fp, "%s", command) != EOF) {
			if (strcmp(command, "NODE") == 0) {
				fscanf(fp, "%d %s", &i, name);
				insert_graph_node(mygraph, i, name);
			} else if (strcmp(command, "EDGE") == 0) {
				fscanf(fp, "%d %d", &s, &t);
				insert_graph_link(mygraph, s, t);
			} else
				return -1;
		}
	}
	return 0;
}
void print_graph(Graph *mygraph)
/*
 * Prints out Graph *mygraph to the stdout in .gx format.
 * 8/2/2010 - JLS
 */
{
	int i;
	List *current;
	printf("MAX %d\n", mygraph->MaxSize);
	for (i = 0; i < mygraph->MaxSize; i++)
		if (mygraph->table[i].name != NULL) {
			printf("NODE %d %s\n", i, mygraph->table[i].name);
			current = mygraph->table[i].outlist;
			while (current != NULL) {
				printf("EDGE %d %d\n", i, current->index);
				current = current->next;
			}
		}
}



/** -------------end of graph functions ---------------**/

/** ------------- InItInList---------------**/
int IsItInList(Graph graph, int current,int target)
{
	while(graph.table[current].outlist!= NULL )
	{
		if(graph.table[current].outlist->index==target)
		{
			printf("fuck");
			return 1;
		}
		graph.table[current].outlist=graph.table[current].outlist->next;
    printf("bb\n");

	}
	return 0;
}

/** ------------- end of Inlist---------------**/

int largestOut(Graph graph,int current,int visited[])
{
	List *adjacents = (List*) malloc(sizeof(List));
  adjacents = graph.table[current].outlist;

	int MAXOUT=adjacents->index;
	//Let maxout be the unvisited node in current.outlist with largest outdegree
	while(adjacents!=NULL && visited[adjacents->next->index]==0)
	{
		printf("fkc1\n" );
		adjacents=adjacents->next;
		if(graph.table[adjacents->index].outdegree>graph.table[MAXOUT].outdegree)
		{
			printf("fkc2\n" );
			MAXOUT=adjacents->index;
		}
		printf("fkc3\n" );
		return MAXOUT;

	}
}


/** ------------- heuristic---------------**/
void Heuristic(Graph graph, int root_node,int target,int visited[]) {

	int path[graph.MaxSize];
	int current=root_node;
	int distance=0;
	List *list;
  //set root_node is visited
	visited[root_node] = 1;


	//while (TARGET not in CURRENT.OUTLIST) and (CURRENT.OUTLIST not empty)
	while(graph.table[current].outlist!=NULL && IsItInList(graph,root_node,target)==0)
	{
		printf("T\n" );
		//CURRENT ← MAXOUT
		path[distance]=current;
		distance++;
    printf("T1\n" );
		current=largestOut(graph,current,visited);
		printf("T2\n" );
    visited[current]=1;

		list=graph.table[current].outlist;
		printf("T3\n" );

	}//while
	path[distance]=current;
	distance++;


	if(IsItInList(graph,root_node,target)==1)
	{
		path[distance]=target;
		printf("The distance between Node:%d and Node:%d is %d \n",path[0],target,distance );
		printf("via  " );
		for(int i=0;i<distance;i++)
		{
			printf("node: %d",path[i]);
		}
	}
	else
		printf("There is no path between those points\n");

}
/** -------------end of heuristic ---------------**/


int main(int argc, char *argv[])
{
	Graph mygraph;

	read_graph(&mygraph, argv[1]);

	int visited[mygraph.MaxSize];
	int distance[mygraph.MaxSize];
	for (int i = 0; i < mygraph.MaxSize; i++)
	{
		visited[i] = 0;
		distance[i] = 0;
	}//for

//which want to executed
#define Test


#ifdef Test
int source;
int target;
printf("Which 2 nodes  you want to act as source and target?\n" );
scanf("%d %d", &source,&target );
Heuristic(mygraph, source, target, visited);
#endif


return 0;
}//main
