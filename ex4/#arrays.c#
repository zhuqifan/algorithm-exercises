#include <stdio.h>
#include <stdlib.h>

/* these arrays are just used to give the parameters to 'insert',
   to create the 'people' array
*/
struct Person{
  char* name;
  int age;
};


#define HOW_MANY 7
char *names[HOW_MANY]= {"Simon", "Suzie", "Alfred", "Chip", "John", "Tim",
		      "Harriet"};
int ages[HOW_MANY]= {22, 24, 106, 6, 18, 32, 24};

/* declare your struct for a person here */

static void insert(struct Person *people[], char *name, int age,int *nextinsert)
{
//  static int nextfreeplace = 0;
  people[*nextinsert] = malloc(sizeof(struct Person));
  people[*nextinsert]->name = name;
  people[*nextinsert]->age = age;
  // people[nextfreeplace].name = name;
  // people[nextfreeplace].age = age;
//  nextfreeplace++;
  /* put name and age into the next free place in the array parameter here */
  /* modify nextfreeplace here */
  (*nextinsert)++;
}

int main(int argc, char **argv)
{
  /* declare the people array here */
  int *nextinsert = 0;
  struct Person *people[7];
  for (int a = 0; a < 7; a++)
  {
    insert(people, names[a], ages[a], &nextinsert);
  }
  for (int a = 0; a < 7; a++)
  {
    printf("%s is %d years old\n",people[a]->name,people[a]->age);
  }
  for (int a = 0; a < 7; a++)
  {
    free(people[a]);
  }
  /* print the people array here*/

  return 0;
}
