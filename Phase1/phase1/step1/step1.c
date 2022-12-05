/*THIS SEGMENT IS USING ID AS KEY EVERYWHERE. IF LATER ON I REALISE THAT I HAVE TO SEARCH OR DELETE BASED ON STM I HAVE TO CHANGE EVERYTHING TO STM BASED.I DID AND NOW I HAVE TO REMEMBER THATIF I WANT TO MAKE MY PROGRAM RUN FASTER LATER ON BASED ON THE LAYOUT OF THE LATER STEPS THAT WILL DETERMINE THE ARGUMENTS OF EACH FUNCTION CODED HERE I CAN USE ONE MORE PARAMETER TO RUN TRHOUGH THE ELEMENTSTHAT HAVE A VALUE LOWER OR HIGHER THAN THE GIVEN ONE CAUSE THE LIST IS ORDERED FROM SMALLEST TIME TAG TO LARGEST
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

struct SubInfo
{
    int sId;
    int stm;
    struct Info *sgp[64];
    struct SubInfo *snext;
};

void SL_Print(struct SubInfo *head)
{
    struct SubInfo *temp = head;

    if (head == NULL)
    {
        printf("%s\n", "This SubInfo list is empty!Why would you want to print anything?");
    }
    while (temp != NULL)
    {
        printf("%s %d %s %d\n", "Id:", temp->sId, "Time stamp:", temp->stm);
        temp = temp->snext;
    }
} /*this function prints sub info*/

void SL_Delete(struct SubInfo **head, int stm)
{
    /*temp is used to freeing the memory*/
    struct SubInfo *temp = *head;

    /* key found on the head node.*/
    /*move to head node to the next and free the head.*/
    if ((*head)->stm == stm)
    {
        temp = *head; /*backup to free the memory*/
        *head = (*head)->snext;
        free(temp);
    }

    else
    {
        struct SubInfo *current = *head;
        while (current->snext != NULL)
        {
            /*if yes  delete the current->next node*/
            if (current->snext->stm == stm)
            {
                temp = current->snext;
                /*node will be deleted from the  list*/
                current->snext = current->snext->snext;
                free(temp);
                /*break to delete first occurance*/
            }
            /*if no move the current node and proceed*/
            else
                current = current->snext;
        }
    }
} /*this function deletes a node in sub info*/

/* int SL_Lookup(struct SubInfo * head, int sId , int stm)
 {
     struct SubInfo *current = head;
     if (current == NULL)
     {
         printf("%s\n", "This SubInfo list is empty!Why would you want to look up anything?");
     }

     while(current->stm < stm){
         current=current->snext; //ordered list : from where on should i start looking for the thing i want. IF THE BASE OF SEARCH IS STM I CAN BINARY SEARC H
     }

     while (current)
     {
         if (current->sId == sId)
         {
             return 1; // found
         }
         current = current->snext;
     }
     return 0; // not found
 };            // this function looks ups the id in  sub info

*/

struct SubInfo *middle(struct SubInfo *start, struct SubInfo *last)
{

    struct SubInfo *min = start;
    struct SubInfo *max = start->snext;

    if (start == NULL)
        return NULL; /*list empty*/

    while (max  != last)
    {
        max  = max ->snext;
        if (max  != last)
        {
            min = min->snext;
            max  = max ->snext;
        }
    }

    return min;
}

struct SubInfo *SL_Lookup(struct SubInfo *head, int stm)
{
    struct SubInfo *start = head;
    struct SubInfo *last = NULL;
    if (head == NULL)
    {
        printf("%s\n", "This  list is empty!Why would you want to look for anything?");
    }

    do
    {
        /*Find middle*/
        struct SubInfo *mid = middle(start, last);

        /*If middle is empty*/
        if (mid == NULL)
            return NULL;

        /*If value is present at middle*/
        if (mid->stm == stm)
            return mid;

        /*If value is more than mid*/
        else if (mid->stm < stm)
            start = mid->snext;

        /*If the value is less than mid.*/
        else
            last = mid;

    } while (last == NULL ||
             last != start);

    /*value not present*/
    return NULL;
} /*this function looks ups the stm in  sub info using binary search*/

void SL_Insert(struct SubInfo **head_ref, struct SubInfo *new_node)
{
    struct SubInfo *current;
    /*Special case for the head end */
    if (*head_ref == NULL || ((*head_ref)->stm >= new_node->stm))
    {
        new_node->snext = *head_ref;
        *head_ref = new_node;
    }
    else
    {
        /*find node to place after the new one */
        current = *head_ref;
        while (current->snext != NULL && current->snext->stm < new_node->stm)
        {
            current = current->snext;
        }
        new_node->snext = current->snext;
        current->snext = new_node;
    }
} /*this function Inserts at list sub info*/

struct SubInfo *SL_newNode(int sId, int stm)
{
    struct SubInfo *new_node = (struct SubInfo *)malloc(sizeof(struct SubInfo));

    new_node->sId = sId;
    new_node->stm = stm;
    new_node->snext = NULL;

    return new_node;
} /*this is a utility function to add nodes to SubInfo list on this example.*/

int main(void)
{
    struct SubInfo *dummy;
    struct SubInfo *head = NULL;
    dummy = SL_newNode(0, 1);

    SL_Insert(&head, dummy);

    dummy = SL_newNode(1, 2);
    SL_Insert(&head, dummy);

    dummy = SL_newNode(2, 3);
    SL_Insert(&head, dummy);

    dummy = SL_newNode(2, 4);
    SL_Insert(&head, dummy);

    dummy = SL_newNode(3, 5);
    SL_Insert(&head, dummy);

    dummy = SL_newNode(4, 6);
    SL_Insert(&head, dummy);

    dummy = SL_newNode(5, 7);
    SL_Insert(&head, dummy);

    dummy = SL_newNode(55, 2);
    SL_Insert(&head, dummy);

    SL_Print(head);

    SL_Delete(&head, 2);

    SL_Print(head);

    /*if (SL_Lookup(head, 2,5))
      {
          printf("HAHAFOUND\n");
      }
      else
          printf("HAHAnotFOUND\n");
*/
    return 0;
}