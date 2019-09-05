#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define __USE_BSD
#include <string.h>
#include "speller.h"
#include "dict.h"

typedef struct node * tree_ptr;
struct node {
  Key_Type element; // only data is the key itself
  tree_ptr left, right;
  // add anything else that you need
};

struct table {
  tree_ptr head; // points to the head of the tree
  tree_ptr current;
  // add anything else that you need
};

Table initialize_table(/*ignore parameter*/) {
Table pointtable = malloc(sizeof(struct table));
pointtable-> head=NULL;
pointtable-> current=NULL;
return pointtable;
}

void insert_again(Key_Type key,tree_ptr node){
    Key_Type currentKey = node-> element;
    if(strcmp(key,currentKey)< 0)
    {
        if (node-> left == NULL)
        {
            tree_ptr newPtr = (tree_ptr)malloc(sizeof(struct node));
            newPtr-> element = strdup(key);
            newPtr-> left = NULL;
            newPtr-> right = NULL;
            node-> left = newPtr;
        }
        else
          insert_again(key,node-> left);
    }
    else if(strcmp(key,currentKey) > 0)
    {

        if (node-> right == NULL)
        {
            tree_ptr newPtr = (tree_ptr)malloc(sizeof(struct node));
            newPtr-> element = strdup(key);
            newPtr-> left = NULL;
            newPtr-> right = NULL;
            node-> right = newPtr;
        }
        else {
            insert_again(key, node-> right);
        }
    }
}

Table inserttree(Key_Type key, Table table) {
    if (table-> head == NULL)
    {
        tree_ptr newPtr = (tree_ptr)malloc(sizeof(struct node));
        newPtr-> element = strdup(key);
        newPtr-> left = NULL;
        newPtr-> right = NULL;
        table-> head = newPtr;
    }
    else
    {
         insert_again(key,table-> head);
    }
    return table;
}

//avl tree
tree_ptr turnRight(tree_ptr y)
{
    tree_ptr x = y->left;
    tree_ptr T2 = x->right;

    x->right = y;
    y->left = T2;

    return x;
}

tree_ptr turnLeft(tree_ptr x)
{
    tree_ptr y = x->right;
    tree_ptr T2 = y->left;

    y->left = x;
    x->right = T2;

    return y;
}

int getBalance(tree_ptr N)
{
    if (N == NULL)
        return 0;
    int difference= maxheight(N->left) - maxheight(N->right);
    return difference;
}

tree_ptr insertavl(Key_Type key,tree_ptr currentNode,tree_ptr *head)
{
    insertavl(key,currentNode,head);
    currentNode=*head;

    int balance=getBalance(currentNode);

    if (balance > 1 && strcmp(key,currentNode->left->element)<0)
        return turnRight(currentNode);
    if (balance < -1 && strcmp(key,currentNode->right->element)>0)
        return turnLeft(currentNode);
    if (balance > 1 && strcmp(key,currentNode->left->element)>0)
    {
        currentNode->left =  turnLeft(currentNode->left);
        return turnRight(currentNode);
    }
    if (balance < -1 && strcmp(key,currentNode->right->element)<0)
    {
        currentNode->right = turnRight(currentNode->right);
        return turnLeft(currentNode);
    }
    return currentNode;
}

Table insert(Key_Type key, Table table) {
    switch(mode)
    {
      case 1:inserttree(key,table);
      break;
      case 2:table->head=insertavl(key,table->current,&table->head);
      break;
    }
    table->current=table->head;
    return table;
}

Boolean find(Key_Type key, Table table) {
    tree_ptr newPtr = table->head;
    while (newPtr != NULL)
    {
      int keyCompare = strcmp( key, newPtr->element );
      if (keyCompare == 0)
          return TRUE;

      if (keyCompare < 0)
          newPtr = newPtr->left;
      else
          newPtr = newPtr->right;
   }
   return FALSE;
}

void printTable(tree_ptr node)
{
    if (node-> left != NULL)
    printTable(node-> left);
      printf("%s\n",node-> element);
    if (node-> right != NULL)
    printTable(node-> right);
}

void print_table(Table dictable) {
  printTable(dictable-> head);
}

int maxheight(tree_ptr node)
{
   int right_height,left_height;
   if(node==NULL)
       return 0;
   left_height=maxheight(node->left);
   right_height=maxheight(node->right);

   if(left_height>right_height)
      return left_height+1;
   else
      return right_height+1;
}
void print_stats (Table dictable) {
  printf("max height of dictable = %d\n", maxheight(dictable->head));
}
