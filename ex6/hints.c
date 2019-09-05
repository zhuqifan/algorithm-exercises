//from http://www.cs.manchester.ac.uk/ugt/COMP26120/lab/ex9hints.html

struct node
{
  String // a string declaration to hold an object-name (which may be NULL)
  String // a string declaration to hold a question (which may be NULL)
  struct node *yes_ptr; // only NULL for objects
  struct node *no_ptr; // only NULL for objects
}

void treePrint(struct node *ptr)
{
  if (ptr == NULL)
  {
    do nothing
  }
  else
  {
    if (ptr is a question)
    {
      print "question:" and the question
      //now print the yes and no subtrees:
      treePrint(ptr->yes_ptr);
      treePrint(ptr->no_ptr);
    }
      else
    { // ptr is an object
      print "object:" and the object-name
    }
  }
}

struct node *treeRead()
{
  read the next line of input
  if (nothing there) // i.e. no input
    return NULL;
  else
  {
    ptr = malloc (size of a struct node)
    if (the line started with "question:")
    {
      fill ptr with the question from the input line
      //now read the yes and no subtrees:
      ptr->yes_ptr = treeRead()
      ptr->no_ptr= treeRead()
    }
      else
    { // the line started with "object:"
      fill ptr with the object-name from the input line
      ptr->yes_ptr= ptr->no_ptr= NULL
    }
  }
}

initialise the tree // first version: just one object, a pangolin

// first version: play just one round
current node = root of tree
while (not finished)
{
  if (current node is a leaf)
  { // object node
    make the guess
    if (user says guess is correct)
    {
      say computer has won
    }
      else
    {
      say user has won
      ask for new object-name and question
      insert the new object-name and question into the tree
    }
    finished
  }
    else
  {
    // question node
    ask the question
    set current node according to Yes/No response
  }
}
