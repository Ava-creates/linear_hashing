#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "voter_info.h"
#include "voterlist.h"
#include "ziplist.h"
#include "hash.h"


void  parse (char* line , struct voter_info *person) {
   
    sscanf(line, "%d,%[^,],%[^,],%d", &person->pin, person->firstname, person->lastname, &person->zip);
    
}


int main(int argc, char *argv[])
{
    char *file; 
    int keys_in_bucket =20; 
    if(argc>1)
    {
        int i = 0; 
        for (i=1 ; i<argc ; i++)
        {
            if(strcmp(argv[i], "-f")==0)
            {
                if(i%2 ==1 )
                {
                    file = argv[i+1]; 
                }
                else
                {
                    printf("woops \n");
                }
            }

           if(strcmp(argv[i], "-b")==0)
            {
                if(i%2 ==1 )
                {
                    keys_in_bucket = atoi(argv[i+1]); 
                    printf("keys allowed in buckets %i \n", keys_in_bucket);
                   
                }
                else
                {
                    printf("woops \t index is %i \n", i);
                }
                   

            }
        }
    }

    struct voter_list_list *b= (struct voter_list_list*) malloc(sizeof(struct voter_list_list));
    struct zip_list *a= (struct zip_list*) malloc(sizeof(struct zip_list));

    struct hash_table *table =(struct hash_table*) malloc(sizeof(struct hash_table));

    FILE* fp = fopen("./voters500.csv", "r");
    create_hashtable(keys_in_bucket, 2, table); 

    if (!fp)
        printf("Can't open file\n");

    else{
         char line[1000];
        while (fgets(line, 1000, fp) != NULL) {
        struct voter_info *person = (struct voter_info*) malloc(sizeof(struct voter_info));
        // Parse the record from the line of text
        parse(line, person);
        // insert_already_existing(a, person); 
        inserth(person, table);
    }          
    }
    
   // printcontent(table);
    printf("\ndata has been loaded \n");


    while(1)
    {

    printf("\nplease enter commands you want to execute \n\n");

    char buf[100];
    fgets(buf, 100, stdin);

    char *pch;
      
    if(buf[0]=='l')
    {
       pch = strtok (buf," ");
       pch = strtok (NULL, " ");
       int pin = atoi(pch);
       struct bucket_node *node =  lookup(pin, table);
       display_bucket_node_info(node);
    }

    else if(buf[0]=='b')
    {
       pch = strtok (buf," ");
       char ar[3]; 
       strncpy(ar, pch , 3);
       ar[2]='\0';
       pch = strtok (NULL, " ");   //filename 
       bulk_vote(pch, a, table);
       
    }

    else if(buf[0]=='r')
     {
       pch = strtok (buf," ");
       pch = strtok (NULL, " ");
       int pin = atoi(pch);
       register_vote(a, table, pin);
    }


    else if(buf[0]=='v')
     {
       int num = total_people_voted(a);
       printf("Total number of people who have voted so far: %i \n", num);
    }

    else if(buf[0]=='p')
    {
        char ar[5]; 
        strncpy(ar, buf , 5);
        ar[4]='\0';
       if(strcmp(ar, "perc")==0)
       {
        percentage(table); 
       }
       else
       {
        printf("wrong command entered \n");
       }
    }

    else if(buf[0]=='z')
    {
        pch = strtok (buf," ");
     
       pch = strtok (NULL, " ");
      
       int zip = atoi(pch);

       total_voted_in_zip(zip, a);
    }
    
    else if(buf[0]=='e')
    {
         char ar[5]; 
        strncpy(ar, buf , 5);
        ar[4]='\0';

        if(strcmp(ar, "exit")==0)
        {
         //   freeh(table);

         // aa need to figure this out 
         
            freez(a);
            break; 
        }
    }

     else if(buf[0]=='o')
    {     
        sort(a, a->head);
        printsorted(a);
    }


     else if(buf[0]=='i')
     {
       struct voter_info *person = (struct voter_info*) malloc(sizeof(struct voter_info));
       pch = strtok (buf," ");
       pch = strtok (NULL, " ");
       int pin = atoi(pch);
       pch = strtok (NULL, " ");
        strcpy(person->firstname, pch);
       pch = strtok (NULL, " ");
       strcpy(person->lastname, pch); 
       pch = strtok (NULL, " ");
       int zip = atoi(pch);

       int check = check_if_exists( pin, table); 

        person->pin = pin ;
        person->vote =0; 
        person->zip= zip;    
        if(check==0)
        {
            inserth(person, table);
        }
        else{
            printf("data about the pin already int he system \n");
        }
    }


    else{
        printf(" invalid command \n");
     
    }

    }
     printf("keys allowed in buckets %i \n", keys_in_bucket);

     printf("%s\n", argv[2]);

     printf("%i\n", atoi(argv[2]));

    return 0;
}


