          #include<stdio.h>
          #include<stdlib.h>
          #include<string.h>
          /* these arrays are just used to give the parameters to 'insert',
             to create the 'people' array
          */
          struct Person{
            char* name;
            int age;
            struct Person *next;
          };
          struct Person *headptr = NULL;

          typedef int(*func)(int,int);


          #define HOW_MANY 7
          char *names[HOW_MANY]= {"Simon", "Suzie", "Alfred", "Chip", "John", "Tim",
          		      "Harriet"};
          int ages[HOW_MANY]= {22, 24, 106, 6, 18, 32, 24};

          /* declare your struct for a person here */

          // static struct Person* insert(struct Person *people, char *name, int age)
          // {
          //    struct Person *ptr = (struct Person*)malloc(sizeof(struct Person));
          //    if(ptr == NULL) abort();
          //
          //    ptr->name = name;
          //    ptr->age = age;
          //    ptr -> next = headptr;
          //    headptr = ptr;
          //    return ptr;
          //   /* put name and age into the next free place in the array parameter here */
          //   /* modify nextfreeplace here */
          // }

          static struct Person* insert_start(struct Person *people, char *name, int age)
          {
             struct Person *ptr = (struct Person*)malloc(sizeof(struct Person));
             if(ptr == NULL) abort();

             ptr->name = name;
             ptr->age = age;
             ptr -> next = people;
             people = ptr;
             return people;
            /* put name and age into the next free place in the array parameter here */
            /* modify nextfreeplace here */
          }
          static struct Person* insert_end(struct Person *people, char *name, int age)
          {
            struct Person *ptr = (struct Person*)malloc(sizeof(struct Person));
            ptr->name = name;
            ptr->age = age;
             if(people == NULL)
             {
              // struct Person *ptr = (struct Person*)malloc(sizeof(struct Person));
               ptr->next = NULL;
               people = ptr;
               return people;
             }
             else
             {
               struct Person *temp = people;
               while (temp->next != NULL)
               {
                  temp = temp->next;
               }
               temp->next = ptr;
               return people;
             }
          }

          int compare_people_by_name(struct Person *people1, struct Person *people2)
          {
            return(strcmp(people1->name, people2->name));
          }
          int compare_people_by_age(struct Person *people1, struct Person *people2)
          {
            return(people1->age - people2->age);
          }




          static struct Person* insert_sorted(struct Person *people,struct Person **ptr2ptr, char *name, int age, func funct)
          {
            struct Person *ptr = (struct Person*)malloc(sizeof(struct Person));
            ptr->name = name;
            ptr->age = age;
            ptr2ptr= &people;
            while((*ptr2ptr != NULL)&&(funct((*ptr2ptr), ptr)<0))
            {
              ptr2ptr = &(*ptr2ptr)->next;
            }
            ptr->next = (*ptr2ptr);
            (*ptr2ptr) = ptr;
            return people;


          }



          int main(int argc, char **argv)
          {

            struct Person *people = NULL;
            struct Person **ptr2ptr = NULL;
            func funct = &compare_people_by_age;
            /* declare the people array here */

            for (int a = 0; a < 7; a++)
            {
              people = insert_sorted(people, ptr2ptr, names[a], ages[a], funct);
            }

            struct Person *ptr = people;
            while(ptr != NULL)
            {
              printf("%s is %d years old\n",ptr->name,ptr->age);
              ptr = ptr->next;
            }
            /* print the people array here*/

            return 0;
          }
