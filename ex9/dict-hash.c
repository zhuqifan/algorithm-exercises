#include <stdlib.h>
#include <ctype.h>
#define __USE_BSD
#include <string.h>

#include "speller.h"
#include "dict.h"

typedef struct
{ // hash-table entry
  Key_Type element; // only data is the key itself
  enum {empty, in_use, deleted} state;
} cell;

typedef unsigned int Table_size; // type for size-of or index-into hash table

struct table
{
  cell *cells; Table_size table_size; // cell cells [table_size];
  Table_size entries; // number of cells in_use
  int collision, duplicate, collisionInsert, items, exceeds;
  // add anything else that you need
};

Table initialize_table (Table_size size)
{
  struct table *tableCell = malloc(sizeof(struct table));
  tableCell -> table_size = size;
  tableCell -> entries = 0;
  tableCell -> collision = 0;
  tableCell -> duplicate = 0;
  tableCell -> items = 0;
  tableCell -> collisionInsert = 0;
  tableCell -> exceeds = 0;
  tableCell -> cells = malloc(sizeof(cell)*size);
  return tableCell;
}

int compute_hash(Key_Type key, Table table)
{
  int hash = 0;
  int len = strlen(key);
  for (int i = 0; i < len; i++)
  {
    hash = (hash + key[i]) * 31;
  }
  hash = abs(hash) % (table -> table_size);
  return hash;
}

cell insertHash(Key_Type key)
{
  cell newEntry;
  newEntry.element = strdup(key);
  newEntry.state = in_use;
  return newEntry;
}

Table insert (Key_Type key, Table table)
{
  table -> items += 1;
  if((table -> entries) < (table -> table_size))
  {
    int hash = compute_hash(key, table);
    if(table -> cells[hash].state == in_use)
    {
      if(strcmp(table -> cells[hash].element, key) == 0)
        table -> duplicate += 1;
      else
      {
        table -> collision += 1;
        int size = table -> table_size;
        Boolean quit = FALSE;
        int originalHash = hash;
        hash++;
        while(quit == FALSE && hash != originalHash)
        {
          if(hash == (size -1))
            hash = 0;
          if(table -> cells[hash].state == empty)
          {
            table -> cells[hash] = insertHash(key);
            table -> entries += 1;
            table -> collisionInsert += 1;
            quit = TRUE;
          }
          hash += 1;
        }
        if (quit == FALSE)
          table -> exceeds += 1;
      }
    }
    else
    {
      table -> cells[hash] = insertHash(key);
      table -> entries += 1;
    }
    return table;
  }
  else
  {
    printf("Hash table is full, no more elements can be inserted\n");
    table -> exceeds += 1;
    return table;
  }
}

Boolean find (Key_Type key, Table table)
{
  int hash = compute_hash(key, table);
  if(table -> cells[hash].state == in_use)
    return TRUE;
  else
  {
    int size = table -> table_size;
    int originalHash = hash;
    while(hash != originalHash)
    {
      if(hash == (size -1))
        hash = 0;
      if(table -> cells[hash].element == key)
        return TRUE;
      else if(table -> cells[hash].state == empty)
        return FALSE;
      hash += 1;
    }
  }
}

void print_table(Table table)
{
  int size = table -> table_size;
  for (int i = 0; i<size; i++)
  {
    if(table -> cells[i].state != empty)
      printf("%s\n", table -> cells[i].element);
  }
}

void print_stats (Table table)
{
  printf("Number of Items in dictionary file: %d\n", table -> items);
  printf("Number of duplicate: %d\n", table -> duplicate);
  printf("Number of collision: %d\n", table -> collision);
  printf("Number of entries: %d\n", table -> entries);
  printf("Of which are Collision Inserts: %d\n", table -> collisionInsert);
  printf("Number of items unable to insert due to a full table: %d\n",
          table -> exceeds);
}
