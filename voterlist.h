#include <stdio.h>
#include <stdlib.h>

#include "voter_info.h"
#ifndef  VOTERLIST_H
#define  VOTERLIST_H

// #include "voter_info.h"


//will be created in main and then passed to linked lists and hash table

struct voter_list_node
{
    struct voter_info *info;  
    struct voter_list_node *next ;
}; 

struct voter_list_list
{
    struct voter_list_node *head;
    struct voter_list_node *current;
}; 

/// check outside that thios person has voted for sure 
void insertv(struct voter_info *inf, struct voter_list_list *a);

void findv( struct voter_info *b, struct voter_list_list *a);

void printlistv(struct voter_list_list *a);

void freev(struct voter_list_list *a);

#endif