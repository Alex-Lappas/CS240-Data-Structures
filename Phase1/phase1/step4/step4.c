#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

struct Subscription {
    int sId;
    struct Subscription *snext;
};

struct Subscription *newNode(int data)
{
    struct Subscription *new_node = (struct Subscription *)malloc(sizeof(struct Subscription));
    new_node->sId = data;
    new_node->snext = NULL;

    return new_node;
} /* Function to create new node*/

void L_Insert(struct Subscription **head_ref, struct Subscription *new_node)
{
    new_node->snext = (*head_ref);
    (*head_ref) = new_node;
} /*Function to insert (at the head of) the list*/

void L_Print(struct Subscription *head)
{
    struct Subscription *temp = head;

    if (head == NULL)
    {
        printf("%s\n", "This  list is empty!Why would you want to print anything?");
    }
    while (temp != NULL)
    {
        printf(" %d\n", temp->sId);
        temp = temp->snext;
    }
} /*function to print linked list*/

void L_Delete(struct Subscription **head, int data)
{
    /* temp is used to freeing the memory*/
    struct Subscription *temp = *head;

    /*key found on the head node.*/
    /*move to head node to the next and free the head.*/
    if ((*head)->sId == data)
    {
        temp = *head; /* backup to free the memory*/
        *head = (*head)->snext;
        free(temp);
    }
    else
    {
        struct Subscription *current = *head;
        while (current->snext != NULL)
        {
            /*if yes, we need to delete the current->next node*/
            if (current->snext->sId == data)
            {
                temp = current->snext;
                /*node will be disconnected from the linked list.*/
                current->snext = current->snext->snext;
                free(temp);
                break;
            }
            /*Otherwise, move the current node and proceed*/
            else
                current = current->snext;
        }
    }
} /*this function deletes a node with specific data*/

int L_Lookup(struct Subscription *head, int data)
{
    struct Subscription *current = head;

    if (head == NULL)
    {
        printf("%s\n", "This  list is empty!Why would you want to print anything?");
    }
    while (current)
    {
        if (current->sId == data)
        {
            return 1; /*found */
        }
        current = current->snext;
    }
    return 0; /*not found*/
}

int main(void)
{
    struct Subscription *dummy;
    struct Subscription *head = NULL;
    dummy = newNode(1);
    L_Insert(&head, dummy);
    dummy = newNode(2);
    L_Insert(&head, dummy);
    dummy = newNode(3);
    L_Insert(&head, dummy);
    dummy = newNode(4);
    L_Insert(&head, dummy);
    dummy = newNode(6);
    L_Insert(&head, dummy);
    dummy = newNode(89);
    L_Insert(&head, dummy);

    L_Print(head);

    L_Delete(&head, 4);
    L_Print(head);

    printf("%d", L_Lookup(head, 4));
    printf("%d", L_Lookup(head, 1));
    return 0;
}