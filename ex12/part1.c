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
        } else {
                List *sourceList = mygraph->table[source].outlist;
                while (sourceList->next != NULL) {
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

int done = 0;
int noNext = 0;

void pending(List *currentQ, int root_node, List *adjacents, int distance[],
                int visited[]) {

        //find the end of queue to append new node
        if (noNext == 0) {
                if (currentQ->next != NULL) {
                        pending(currentQ->next, root_node, adjacents, distance, visited);
                }
                noNext = 1;
        }
        //pending
        if (done == 0) {

                if (adjacents != NULL) {
                        //if the distance of this node is infinity
                        //which means the node is not append on queue
                        if (distance[adjacents->index] == 0 &&
                                visited[adjacents->index] != 1) {
                                if (currentQ->next == NULL) {
                                        currentQ->next = (List *) malloc(sizeof(List));
                                }
                                distance[adjacents->index] = distance[root_node] + 1;
                                currentQ->next->index = adjacents->index;
                        }
                        //if the current distance of this node is greater than
                        //distance from current root node to it + distance between current
                        //root node and start node. (which is not possible in our case)
                        else if (distance[adjacents->index] != 0 &&
                                         distance[adjacents->index] > distance[root_node] + 1) {
                                     distance[adjacents->index] = distance[root_node] + 1;
                        }

                        if (adjacents->next != NULL) {
                                if (currentQ->next == NULL) {
                                        currentQ->next = (List *) malloc(sizeof(List));
                                }
                                pending(currentQ->next, root_node, adjacents->next,
                                                distance, visited);
                        }
                }

                done = 1;
        }
}

/** -------------end of graph functions ---------------**/

/** ------------- Dijkstra ---------------**/
void Dijkstra(Graph graph, int root_node, int visited[], int distance[]) {

        //create a priority queue and set first node on queue the start node
        List *Queue_a = (List *) malloc(sizeof(List));
        Queue_a->index = root_node;

        //get all its adjacent which are nodes
        //with shortest distance to root_node
        List *adjacents = graph.table[root_node].outlist;

        //add root node and
        //node with shortest distance to root_node (its adjacent node)
        //into queue
        pending(Queue_a, root_node, adjacents, distance, visited);
        done = noNext = 0;

        //set distance of root node equals to 0
        distance[root_node] = 0;
    //set it is visited (next best is found)
        visited[root_node] = 1;

        //root node of each adjacent pending
        int centreNode;
        //int count = 0; // for debugging
        while (Queue_a->next != NULL) {
        //printf("%d\n", count); // for debugging

                //mark first node on queue (heap) visited
                visited[Queue_a->index] = 1;
                //remove first node from queue
                Queue_a = Queue_a->next;

                //next node on the queue become root and get all its adjacent node which
                //are node with shortest distance to this node which is the node
                //with shortest distance to previous root node (Dijkstra)
                centreNode = Queue_a->index;
                adjacents = graph.table[centreNode].outlist;

                pending(Queue_a, centreNode, adjacents, distance, visited);
                done = noNext = 0;
              //  count++;
        }

}

/** -------------end of Dijkstra ---------------**/

/** ------------- calculate average ------------**/
double averageDistance(Graph mygraph, int distance[], int visited[]){
        int startNode;
        double sum, average, averageSum;
        double finalAverage;

        for (int i = 1; i < mygraph.MaxSize; i++){
             startNode = i;

             Dijkstra(mygraph, startNode, visited, distance);

             sum = average = 0;
             for(int i = 1; i < mygraph.MaxSize; i++){
                 sum += distance[i];
             }
             average = sum / mygraph.MaxSize;
             printf("the average distances from node %s ", mygraph.table[startNode].name);
             printf("to all other reachable node are: %f\n", average);

             averageSum += average;
             for (int i = 0; i < mygraph.MaxSize; i++) {
                  visited[i] = 0;
                  distance[i] = 0;
             }
    }
        finalAverage = averageSum / mygraph.MaxSize;

    return finalAverage;
}

int main(int argc, char *argv[]) {
        Graph mygraph;

        read_graph(&mygraph, argv[1]);

        int visited[mygraph.MaxSize];
        int distance[mygraph.MaxSize];

        for (int i = 0; i < mygraph.MaxSize; i++) {
                visited[i] = 0;
                distance[i] = 0;
        }

//#define test
#define test
/**-----------  for Test DONT DELETE --------**/
#ifdef test
        int source;
        printf("Which node you want to act as source?\n" );
        scanf("%d", &source);

        Dijkstra(mygraph, source, visited, distance);

        printf("the distances from %s to all other reachable node are:\n",
                        mygraph.table[source].name);
        for (int i = 0; i < mygraph.MaxSize; i++) {
                if (distance[i] != 0) {
                        printf("node: %s distance: %i\n", mygraph.table[i].name, distance[i]);
                }
        }
#endif
/**-----------  for Test DONT DELETE --------**/

#ifdef average
        double finalAverage;
        finalAverage = averageDistance(mygraph, distance, visited);

        printf("average distances from current node to all other nodes");
        printf("is %f", finalAverage);
#endif

        return 0;
}
