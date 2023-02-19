#include <stdio.h>
#include <stdlib.h>

#include "voter_info.h"
#include "voterlist.h"


/// check outside that thios person has voted for sure 
void insertv(struct voter_info *inf, struct voter_list_list *a) {
   //create a link
   struct voter_list_node *link = (struct voter_list_node*) malloc(sizeof(struct voter_list_node));
	link->info = inf;
  

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

void findv( struct voter_info *b, struct voter_list_list *a)
{
    struct voter_list_node *Node = a->head;

    int flag =0;
    while (Node!=NULL)
    {
        if(Node->info == b)
        {
            flag=1; 
            break;
        }

        Node=Node->next; 
    }

    printf("%i", flag);

}


void printlistv(struct voter_list_list *a){
     struct voter_list_node *Node= a->head;
     int j=0;
     while( Node!= NULL)
     {
        j++; 
     //   printf("%s\n", Node->info->firstname );

        printf("%i\n",Node->info->pin );
        printf("first name :%s\n", Node->info->firstname);
        
        Node=Node->next; 

     }
    
}

void freev(struct voter_list_list *a)
{
    struct voter_list_node *Node;
    while( a->head!= NULL)
     {
        Node = a->head; 
      
        a->head= a->head->next; 
        free(Node);
     }
}