//#include "voter_info.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>



// seriously need to check all mallocs

// NOT USING TAIL PINTER CAUSE WILL ONLY NAVIGATE FROM THE FRONT 
 struct bucket_node
 {
    struct  voter_info *voter_info; 
    struct bucket_node *next;
 }; 

struct bucket_list
 {
    struct bucket_node *head; 
    int item_number;    ///need to check if using this consistently
    int index_of_association;
    int po; //variable that stores if it is an overflow list or primary list if 1 then primary if 2 then overflow
    struct bucket_list *overflow; 
};

struct hash_table
{
    int i;   // number of buckets for each cell 
    int length; //initial length of the hash_table 
    struct bucket_list **buckets;
    int og_length;
    int split_pointer;
    int round; 
    int numbuckets; //number of buckets at any given time
    int voted;
    int size;
    //struct bucket_list *b= (struct bucket_list*) malloc(sizeof( struct bucket_list));
 
    //value to use for hash function
   // struct hash_item* table ;  malloc( initial_buck * sizeof (struct hash_item));  //the array that we are hashing into with initial number of buckets that we get from the user 
};

int hash_val1( struct hash_table *h , int pin)
{
    int i =  h->round; 
  
    int hashval1=  (pin )  % (int)( pow (2, i) * h->og_length); 
    return hashval1;
}

int hash_val2( struct hash_table *h , int pin)
{
    int i = ( h->round) +1; 
    int hashval1=  (pin )  % (int)(pow(2, i)*h->og_length); 
    int mo= (pow(2, i)*h->og_length); 
    printf("pin is %i \t the mod thing is %i \n", pin, mo);
    return hashval1;
}

void insert_node( struct bucket_list *list, struct voter_info *v)
{
    
    struct bucket_node *newNode = malloc(sizeof(struct bucket_node));
    newNode->voter_info= v;
    newNode->next     = NULL;

    //if head is NULL, it is an empty list
    if(list->head == NULL)
         list->head = newNode;
    //Otherwise, find the last node and add the newNode
    else
    {
        struct bucket_node *lastNode = list->head;
        

        //last node's next address will be NULL.
        while(lastNode->next != NULL)
        {
            lastNode = lastNode->next;
        }

        //add the newNode at the end of the linked list
        lastNode->next = newNode;
      

    }
      list->item_number++;
      printf("node inserted at %i ", list->index_of_association);
      printf("%i lost tyipe  \t %i items in the list \n", list->po, list->item_number);  
}

//used this fpr deleting node : https://eng.libretexts.org/Courses/Delta_College/C_-_Data_Structures/07%3A_Linked_Lists/7.10%3A_Linked_List_Node_Delete
void remove_node(struct bucket_list *list, struct bucket_node *node)
{

   struct bucket_node *nur = list->head;
   struct bucket_node *prev; 
    // If head node itself holds the key to be deleted 
    if (nur != NULL && nur->voter_info->pin == node->voter_info->pin) 
    { 
       
        list->head = list->head->next; // Changed head 
        
        
        list->item_number--; 

         printf("removed\n");
         printf("node removed from po %i \n ", list->po);

        if(list->item_number ==0)
        {
            list=NULL;
        }
            // free old head memory

        free(nur);
        return; 
    } 
    
    // Search for the key to be deleted, keep track of the 
    // previous node as we need to change 'prev->next' 
    while (nur != NULL && nur->voter_info->pin != node->voter_info->pin) 
    { 
        prev = nur; 
        nur = nur->next; 
    }
    
    // If key was not present in linked list 
    if (nur == NULL) 
       return; 
     // Unlink the node from linked list 
     prev->next = nur->next; 

    printf("node removed from po %i \n ", list->po);

    list->item_number--; 
      if(list->item_number ==0)
        {
            list=NULL;
        }


    
}

void create_hashtable(int bucketsize , int tablesize, struct hash_table *table )
{
    // struct hash_table *table =  (struct hash_table*)malloc( sizeof (struct hash_table)); do this in the main so that the table is accessibl;e to everything 
    // printf("still trying to go into the creation of the linked list of this bucket");
    printf("%i", bucketsize);
    table->i = bucketsize;
    table->length= tablesize; 
    table->og_length= tablesize;
    table->split_pointer=0;
    table->numbuckets=0;
    table->round=0;
    table->size=0;
    table->voted=0;  
    table->buckets = (struct bucket_list **) malloc( table->length * sizeof(struct bucket_list *));
    int i=0; 
   while (i<table->length)
   {
   // printf("\n%i loll  %i\n", table->buckets[i]->index_of_association, i);
    table->buckets[i]= (struct bucket_list *) malloc(  sizeof(struct bucket_list));
    table->buckets[i]->item_number = 0;
    table->buckets[i]->head=NULL;
    table->buckets[i]->po=1; 
    table->buckets[i]->index_of_association= i;
    table->buckets[i]->overflow=NULL;
    table->numbuckets++;
    //printf("\n%i loll  %i\n", table->buckets[i]->index_of_association, i);
    i=i+1;
   }

    //printf("\n%i loll  %i\n", table->buckets[2]->index_of_association, 3);
   printf( "\n%i",  table->numbuckets);
}


void addBuckket(struct hash_table *table)
{
        int i = table->numbuckets; 
        table->buckets = (struct bucket_list **) realloc(table->buckets, ( i+1) * sizeof(struct bucket_list *)); 
        table->buckets[i]= (struct bucket_list *) malloc(  sizeof(struct bucket_list));
        table->buckets[i]->item_number=0;
        table->buckets[i]->head=NULL;
        table->buckets[i]->po=1; 
        table->buckets[i]->index_of_association=i;
        table->buckets[i]->overflow=NULL;
        table->numbuckets++;
       
        printf("\n\nnumbuckets %i\n", table->numbuckets);
        printf("\n new bucket created at index %i\n", table->buckets[i]->index_of_association  );

}


void split(struct hash_table *table)
    {
        //adding a bucket at the end 
        addBuckket(table);
        //redistributing from the split pointer bucket using hashval2 
        printf("%i split pointer", table->split_pointer);
        int s= table->split_pointer;
        table->split_pointer++;
        struct bucket_list *rehash = table->buckets[s]; 

        
        while(rehash)
        {
        struct bucket_node *b = rehash->head; // this can be null as well  like maybe nothign was inserted at 0 index

        while (b)   //rehashing primary list 
        {
                struct bucket_node *temp=b->next; 
                 printf("in the overflow or not %i \n", rehash->po);

                 printf("index of association of the list %i\titem number in whatever list %i \n ", rehash->index_of_association, rehash->item_number);
                 if(rehash->item_number==0)
                 {
                    break;
                 }
                 int r =hash_val2(table, b->voter_info->pin);  // need to do this for all entries in the bucket 

                 printf("SECOND  HASH VALUE %i and numbuckets is %i  \n", r, table->numbuckets);

                 if(r == rehash->index_of_association)       //accpint for overflow here 
                {

                   if(rehash->po ==2)
                   {
                     
                     remove_node(rehash, b);  
                     struct bucket_list *a = table->buckets[s]; 
                     // checking where to insert this node cause empty place might have been created in the promary or befor overflow list
                     while(a)
                    {
                        if(a->item_number< table->i)
                        {insert_node(a, b->voter_info);
                        break;}
                        a= a->overflow;
                    }
                }
                b = temp;
                 continue;
                 }

                else{
                    
                 remove_node(rehash, b); 
               
                
           // insert it at r and this should be empty yea stil account for overflow 

                 struct bucket_list * insert_location =  table->buckets[r];

                 printf("\t insert location %i \t and item numbersss %i \n", r , insert_location->item_number);

            
                 if(insert_location->item_number < (table->i)) //checking if need to look at overflow tables whihch should not happen 
                 {            
                     insert_node(insert_location, b->voter_info);         
                 }
                 else
                 {
                      int g=0;
                      while (insert_location->overflow)
                      {    
                           insert_location= insert_location->overflow;

                           if(insert_location->item_number< (table->i) )   //checking if overflow has space for a new node node  and inserting node 
                           {
                            insert_node(insert_location, b->voter_info);   //inserting at the location
                            // remove_node(rehash, b);  // deleting from where it was before 
                            g=1;
                            break;
                           }

                    }

                    printf("%i g \n", g);
                    if(g==0)
                    {
                         // if we are here then that means that we need to insert in an overflow list which first needs to be created 
                         //split again??
                        struct bucket_list *duh = table->buckets[r]->overflow;
                        table->buckets[r]->overflow=(struct bucket_list *) malloc( sizeof(struct bucket_list ));
                        duh=  table->buckets[r]->overflow;
                        duh->item_number=0;
                        table->buckets[r]->overflow->head=NULL;
                        duh->po=2; 
                        duh->index_of_association= r;  
                        insert_node(duh, b->voter_info);
                        // remove_node(rehash, b);
                        split(table);  
                    }
                     }  
                     }


             
             b= temp;
             printf("test\n");
             
        }

            rehash=rehash->overflow;

            printf("issue with rehash  \n");
        }
             //so the entire thing above is for  bucket s not not the overflow list nodes that it might have that need to rehashed as well 
        
        printf("\n done with splitting \n");

           
        if(table->split_pointer== table->length)
            {
                table->round ++; 
                table->length = table->length *2; 
                table->split_pointer =0;
                printf("\n \n hash value increased \n \n");
            }

            printf("item numbers in the previous list %i\n", table->buckets[s]->item_number);

        }

struct bucket_node * lookup(int pin, struct hash_table *table )
{
    int i =0;   
    while(i<table->numbuckets)
    {
        struct bucket_list *list = table->buckets[i];
       // printf("/text print  bucket loop \n");
        while(list)
        {
            struct bucket_node *node = list->head; 
           //  printf("/text print  list loop \n");
             while(node)
             {
           //  printf("/text print node loop \n");
            if(node->voter_info)
            {
                if(node->voter_info->pin == pin)
                {   return node;
                    break;
                }
            node=node->next;
            }  }
            list= list->overflow;
            }
         i++;
          }
return NULL;
}

void inserth(struct voter_info *v , struct hash_table *table )
{   
    int i = hash_val1(table, v->pin); 
    table->size++;

    if(i<table->split_pointer){
        i= hash_val2(table, v->pin);
    }
    //table i is bucket size of the hashtable 

    printf(" %i hash index %i \n", v->pin, i);

    int item = table->buckets[i]->item_number; 
    int total_items_allowed= table->i;
    struct bucket_node *b= (struct bucket_node *)malloc(sizeof(struct bucket_node)); 
    // b->voter_info=v;
    // b->next=NULL;

    printf("%iitem number \t % items allowed  \t index %i \t pin :%i this is before inserting \n", item, total_items_allowed, i, v->pin);
    if(item < total_items_allowed)
    {
        printf("inserted in not overflow %i\n", table->buckets[i]->po);
        insert_node( table->buckets[i], v); 

        printf("inserted in not overflow \n");
    }

     else    {
       
             struct bucket_list *duh = table->buckets[i];
             int flag=0;
            while(duh->overflow)    //inserting to the present overflow list if it is present otherwise adding overflow list 
            {
                duh = duh->overflow; 
                if(duh->item_number <table->i)
                {
                    insert_node(duh, v);
                    flag=1; 
                    break;
                }
                      //we edn with duh being null so duh in itself is the overflow that we need to 
            }

            if(flag==0 )  //this means the node has not been added so the overflow bucket is NULL we create the overflow bucket and then add the node and split
           {
              printf("\nadding an overflow list \n");
              duh=(struct bucket_list *) malloc( sizeof(struct bucket_list ));
          
              duh->item_number=0;
              duh->head=NULL;
              duh->po=2; 
              duh->index_of_association= i;  
              insert_node(duh, v);
              split(table); 
           }
        
            printf("\n done inserting in overflow \n");
    
     }
    printf("done with inserting\n");
    }

int check_if_exists(int pin , struct hash_table *table)
{
    struct bucket_node *node = lookup(pin, table);
    if(node ==NULL)
    return 0; 
    return 1;
}

void printcontent(struct hash_table *table)
{
    int i =0; 
    int count =0;
    while(i<table->numbuckets)
    {
        struct bucket_list *list = table->buckets[i];
       // printf("/text print  bucket loop \n");
        while(list)
        {
            struct bucket_node *node = list->head; 
           //  printf("/text print  list loop \n");
            while(node)
             {
           //  printf("/text print node loop \n");
            if(node->voter_info)
            {
            printf("\nfirst name : %s\n ", node->voter_info->firstname);
            printf("last name : %s\n ", node->voter_info->lastname);
            printf("zip :%i \n", node->voter_info->zip);
            printf("pin %i \n ", node->voter_info->pin);
            count++;
            }
            node=node->next;
            }  
            list= list->overflow;
            }
         i++;
          }
          printf("total things printed : %i", count);
}

void register_vote ( struct zip_list *z, struct hash_table *table, int pin )
{
    struct bucket_node *node= lookup(pin, table); 
    if(node)
    {
        if(node->voter_info)
        {
            if(node->voter_info->vote==0){
            node->voter_info->vote =1; 
            printf("the voter has been registered \n");
            insert_already_existing(z, node->voter_info);
            table->voted++;
            }
            else
           {
             printf("the voter has already been been registered \n");
           }
        }
    }
    else{
        printf("voter not in the database \n");
    }
}

void percentage (struct hash_table *table)

{
    float x= ((float)table->voted/(float)table->size)*100; 
    //  printf("tptal number of people who voted: %i ", table->voted );
    // printf("tptal number of people : %i ", table->size );
    printf("Percentage of people who voted: %f percent \n", x);
}

void display_bucket_node_info (struct bucket_node *node)
{

    if(node)
    {printf("\nfirst name : %s\n ", node->voter_info->firstname);
    printf("last name : %s\n ", node->voter_info->lastname);
    printf("zip :%i \n", node->voter_info->zip);
    printf("pin %i \n ", node->voter_info->pin);
    }
    else 
    printf("please enter correct pin\n");
}

void bulk_vote(char *file , struct zip_list *a, struct hash_table *table)
{
      FILE* fp = fopen(file, "r");

      
    if (!fp)
        printf("Can't open file\n");

    else{

        char *line;
        while (fgets(line, 100, fp) != NULL) {

            register_vote( a, table, atoi(line));
    }}
}

void freelist (struct bucket_list *a )
{
    struct bucket_node *Node;
    while( a->head!= NULL)
     {
        Node = a->head; 
        a->head= a->head->next; 
        free(Node);
     }
}

void freeh(struct hash_table *table)
{
    int i =0;
    while(i<table->numbuckets)
    {   
        struct bucket_list *list = table->buckets[i];
       // printf("/text print  bucket loop \n");
        while(list)
        {
            struct bucket_list *temp;
            struct bucket_node *node; 
           //printf("/text print  list loop \n");
            while(list->head)
            {

                node= list->head; 
           //  printf("/text print node loop \n");
            if(node->voter_info)
            {
                free(node->voter_info);
            }
            list->head=list->head->next;
            
            free( node);
            }  
            temp =list;
            list= list->overflow;
            free(temp);
            }
         i++;
          }
         // printf("total things printed : %i", count);

}