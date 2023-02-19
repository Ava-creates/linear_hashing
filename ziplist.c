
#include <stdio.h>
#include <stdlib.h>
#include "voter_info.h"
#include "voterlist.h"
#include "ziplist.h"

void insert_new_zip(int zip, struct zip_list *a, struct voter_info *v) {
   //create a link

   struct zip_node *link = (struct zip_node*) malloc(sizeof(struct zip_node));
    link->zip=zip; 
	link->vote_list = (struct voter_list_list*) malloc(sizeof(struct voter_list_list)); 
    link->members=0;
    insertv(v, link->vote_list);
    link->members++;
    if(a->head==NULL)
    {
        a->head= link;
        a->current= link;
        a->current->next=NULL;
    }

    else{
        a->current->next= link;
        link->next=NULL;
        a->current= a->current->next;
    }

}

void insert_already_existing(struct zip_list *a, struct voter_info *v)
{ 
    struct zip_node *Node = a->head;
    int flag =0;
    while (Node!=NULL)
    {
        if(Node->zip == v->zip)
        {
            insertv(v, Node->vote_list); 
            Node->members++;
            flag=1; 
            break;
        }

        Node=Node->next; 
    }
   printf("here \n");
    if(flag==0)
    {
        insert_new_zip(v->zip, a, v);
    }

}
void find(int zip, struct zip_list *a)
{
    struct zip_node *Node = a->head;
    int flag =0;
    while (Node!=NULL)
    {
        if(Node->zip == zip)
        {
            flag=1; 

            break;
        }

        Node=Node->next; 
    }

    printf("%i", flag);

}


void printlist(struct zip_list *a){
     struct zip_node *Node= a->head;
     while( Node!= NULL)
     {
        printlistv(Node->vote_list);
        Node=Node->next; 
     }
    
}

int total_people_voted(struct zip_list *a)
{
    if(a->head==NULL)
    {
        return 0;
    }
    struct zip_node *Node= a->head;
    a->total=0;
    while(Node)
    {
        a->total+=Node->members;
        Node=Node->next;
    }

    return a->total;
}

void total_voted_in_zip(int zip, struct zip_list *a)
{

    struct zip_node *Node = a->head;
    int flag =0;
    int votes=0;
    while (Node!=NULL)
    {
        if(Node->zip == zip)
        {
            flag=1; 
            votes = Node->members;
            printf("people who voted in this area : %i\n", votes);
            printlistv(Node->vote_list);
            break;
        }

        Node=Node->next; 
    }

    if(flag==0)
    {
        printf("\n zip not in the file yet so no one voted \n");
    }

}

// used this for sorting  : https://www.geeksforgeeks.org/merge-sort-for-linked-list/

struct zip_node* SortedMerge(struct zip_node* a, struct zip_node* b)
{
    struct zip_node* result = NULL;
 
    /* Base cases */
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);
 
    /* Pick either a or b, and recur */
    if (a->members >= b->members) {
        result = a;
        result->next = SortedMerge(a->next, b);
    }
    else {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return (result);
}

void FrontBackSplit(struct zip_node *z , struct zip_node ** frontRef, struct zip_node** backRef)
{
    struct zip_node *source = z;
    struct zip_node* fast;
    struct zip_node* slow;
    slow = source;
    fast = source->next;
 
    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
 
    /* 'slow' is before the midpoint in the list, so split it in two
    at that point. */
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}

void sort(struct zip_list *z, struct zip_node *node)
{
    struct zip_node *head = node;
    struct zip_node * a;
    struct zip_node * b;
 
    /* Base case -- length 0 or 1 */
    if ((head == NULL) || (head->next == NULL)) {
        return;
    }
 
    /* Split head into 'a' and 'b' sublists */
    FrontBackSplit(head, &a, &b);
 
    /* Recursively sort the sublists */
    sort(z,a);
    sort(z, b);
 
    /* answer = merge the two sorted lists together */
    z->head = SortedMerge(a, b);

}
 

void printsorted(struct zip_list *a)
{
    if(a->total==0)
    {
        printf("the list is empty \n");
    }
   struct zip_node *Node= a->head;
     while( Node!= NULL)
     {
       printf("total number of members: %i \t zip: %i,,,,", Node->members, Node->zip) ;
       Node= Node->next;
     }
}


void freez(struct zip_list *a)
{
    struct zip_node *Node;
    while( a->head!= NULL)
     {
        freev(a->head->vote_list);
        Node = a->head;
        a->head= a->head->next; 
        free(Node);
     }
}
