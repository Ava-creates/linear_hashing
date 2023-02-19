
#include <stdio.h>
#include <stdlib.h>
#include "voter_info.h"
#include "voterlist.h"
#ifndef  ZIPLIST_H
#define  ZIPLIST_H

struct zip_node
{
    int zip; 
    struct voter_list_list *vote_list; 
    struct zip_node *next ;
    int members;
}; 

struct zip_list
{
    struct zip_node *head;
    struct zip_node *current;
    int total;
}; 

void insert_new_zip(int zip, struct zip_list *a, struct voter_info *v);

void insert_already_existing(struct zip_list *a, struct voter_info *v);

void find(int zip, struct zip_list *a);

void printlist(struct zip_list *a); 

int total_people_voted(struct zip_list *a);

void total_voted_in_zip(int zip, struct zip_list *a); 

// used this for sorting  : https://www.geeksforgeeks.org/merge-sort-for-linked-list/
struct zip_node* SortedMerge(struct zip_node* a, struct zip_node* b);

void FrontBackSplit(struct zip_node *z , struct zip_node ** frontRef, struct zip_node** backRef);

void sort(struct zip_list *z, struct zip_node *node);
 

void printsorted(struct zip_list *a);

void freez(struct zip_list *a);

#endif