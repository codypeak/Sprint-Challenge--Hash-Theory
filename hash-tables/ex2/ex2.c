#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "ex2.h"

//output char** array of strings with entire route
//hash each ticket so source is key and destination value
//ith location can be found with i-1
char **reconstruct_trip(Ticket **tickets, int length)
{
  HashTable *ht = create_hash_table(16);
  char **route = malloc(length * sizeof(char *));

  //populate hash table with tickets
  for (int i = 0; i < length; i++)
  {
    //set keys and values
    char *source = tickets[i]->source;
    char *destination = tickets[i]->destination;
    //add pairs to table
    hash_table_insert(ht, source, destination);
  }

  //find key of departure origen
  char *start = "NONE";
  //declare destination
  char *current_destination;

  //loop through tickets starting with none appending each destination
  for (int i = 0; i < length; i++)
  {
    {
      //find start
      if (i == 0) 
      {
        current_destination = hash_table_retrieve(ht, start);
      }
      else
      //else find destination
      {
        current_destination = hash_table_retrieve(ht, current_destination);
      }
      //assign the current city to its place in array
      route[i] = current_destination;
    }
  }

  return route;
}

void print_route(char **route, int length)
{
  for (int i = 0; i < length; i++) {
    printf("%s\n", route[i]);
  }
}



#ifndef TESTING
int main(void)
{
  // Short test
  Ticket **tickets = malloc(3 * sizeof(Ticket *));

  Ticket *ticket_1 = malloc(sizeof(Ticket));
  ticket_1->source = "NONE";
  ticket_1->destination = "PDX";
  tickets[0] = ticket_1;

  Ticket *ticket_2 = malloc(sizeof(Ticket));
  ticket_2->source = "PDX";
  ticket_2->destination = "DCA";
  tickets[1] = ticket_2;

  Ticket *ticket_3 = malloc(sizeof(Ticket));
  ticket_3->source = "DCA";
  ticket_3->destination = "NONE";
  tickets[2] = ticket_3;

  print_route(reconstruct_trip(tickets, 3), 3); // PDX, DCA, NONE

  return 0;
}
#endif
