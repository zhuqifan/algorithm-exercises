//from http://www.cs.manchester.ac.uk/ugt/COMP26120/lab/ex9hints.html
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>


struct node
{
  char* objectname; // a string declaration to hold an object-name (which may be NULL)
  char* question; // a string declaration to hold a question (which may be NULL)
  struct node *yes_ptr; // only NULL for objects
  struct node *no_ptr; // only NULL for objects
};

void nodePrint(struct node *ptr)
{
  if(ptr->objectname != NULL)
    printf("Object: %s\n",ptr->objectname);
  else
    printf("Object: [NOTHING]\n");
  if(ptr->question!=NULL)
    printf("Question: %s\n",ptr->question);
  else
    printf("Question: [NOTHING]\n");
  if(ptr->yes_ptr != NULL)
    printf("Yes %s\n%s\n",ptr->yes_ptr->objectname,ptr->yes_ptr->question);
  if(ptr->no_ptr != NULL)
    printf("No %s\n%s\n",ptr->no_ptr->objectname,ptr->no_ptr->question);
}
char* filename = "tree.txt";
void treePrint(struct node *ptr,FILE *f)
{
  if (ptr == NULL){}
  else
  {
    //if (ptr is a question)
    if(ptr->question != NULL)
    {
      //print "question:" and the question
      //printf("Question: %s\n",ptr->question);
      fprintf(f,"Question: %s\n",ptr->question);
      //now print the yes and no subtrees:
      treePrint(ptr->yes_ptr,f);
      treePrint(ptr->no_ptr,f);
    }
      else
    { // ptr is an object
      //print "object:" and the object-name
      //printf("Object: %s\n",ptr->objectname);
      fprintf(f,"Object: %s\n",ptr->objectname);
    }
  }
}
// char *fgets(char *str, int size, FILE *f);
// struct node *treeRead()
// {
//   sscanf(char *str, format, vars...);
//   if (nothing there) // i.e. no input
//     return NULL;
//   else
//   {
//     ptr = malloc (size of a struct node)
//     if (the line started with "question:")
//     {
//       fill ptr with the question from the input line
//       //now read the yes and no subtrees:
//       ptr->yes_ptr = treeRead()
//       ptr->no_ptr= treeRead()
//     }
//       else
//     { // the line started with "object:"
//       fill ptr with the object-name from the input line
//       ptr->yes_ptr= ptr->no_ptr= NULL
//     }
//   }
// }

//initialise the tree // first version: just one object, a pangolin



int main(int argc, char **argv)
{
  struct node *root = malloc(sizeof(struct node));
  root->yes_ptr = malloc(sizeof(struct node));
  root->no_ptr = malloc(sizeof(struct node));
  root->no_ptr->yes_ptr = malloc(sizeof(struct node));
  root->no_ptr->no_ptr = malloc(sizeof(struct node));
  root->no_ptr->yes_ptr->yes_ptr = malloc(sizeof(struct node));
  root->no_ptr->yes_ptr->no_ptr = malloc(sizeof(struct node));

  root->question = "Does it have a tail?";
  root->yes_ptr->objectname="pangolin";
  root->no_ptr->question = "is it flat?";
  root->no_ptr->yes_ptr->question = "can u dip it in your tea?";
  root->no_ptr->no_ptr->objectname = "pete";
  root->no_ptr->yes_ptr->yes_ptr->objectname = "biscuit";
  root->no_ptr->yes_ptr->no_ptr->objectname = "pizza";
  //nodePrint(root);
  // first version: play just one round
  //current node = root of tree
  struct node *current = root;
  struct node *head = current;
  char* answer = malloc(sizeof(char));
  char* object = malloc(sizeof(char));
  char* question = malloc(sizeof(char));
  //while (not finished)
  //while(current->yes_ptr!=NULL||current->no_ptr!=NULL)
  while(current!=NULL)
  {
    //if (current node is a leaf)
    if(current->objectname!=NULL)
    { // object node
      //make the guess
      printf("%s?\n",current->objectname);
      //if (user says guess is correct)
      scanf("%s",answer);
      if(strcmp(answer,"y")==0)
      {
        printf("ez, i win\n");
        return 0;
      }
      if(strcmp(answer,"n")==0)
      {
        //say user has won
        printf("you win\n");
        //ask for new object-name and question
        printf("what were you thinking of?\n");
        scanf("%s",object);
        printf("Please give me a question about a %s, so I can tell the difference between a %s and %s\n",object,object,current->objectname);
        scanf("%s",question);
        current->question = question;
        current->yes_ptr = malloc(sizeof(struct node));
        current->no_ptr = malloc(sizeof(struct node));
        current->yes_ptr->objectname = object;
        current->no_ptr->objectname = current->objectname;
        current->objectname = NULL;
        //insert the new object-name and question into the tree
        printf("thanks!\n");
        // nodePrint(current);
        printf("Would you like to play again?\n");
        scanf("%s",answer);
        if(strcmp(answer,"y")==0)
        {
          printf("ok\n");
          current = head;
        }
        if(strcmp(answer,"n")==0)
        {
            FILE *f = fopen(filename, "w");
           treePrint(head,f);
          fclose(f);
          return 0;
        }
      }
      //finished
    }
    else
    {
      // question node
      //ask the question
      printf("%s\n",current->question);
      // printf("---------------\n");
      // nodePrint(current);
      // printf("---------------\n");
      scanf("%s",answer);
      //set current node according to Yes/No response
      if(strcmp(answer,"y")==0)
        current = current->yes_ptr;
      if(strcmp(answer,"n")==0)
        current = current->no_ptr;
    }
  }

  return 0;
}
