#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

struct Info
{
    int iId;
    int itm;
    int igp[64];
    struct Info *iprev;
    struct Info *inext;
};

struct Info *create_node(int iId, int itm)
{
    struct Info *new_node = (struct Info *)malloc(sizeof(struct Info));
    new_node->itm = itm;
    new_node->iId = iId;
    new_node->iprev = new_node->inext = NULL;
    return new_node;
}

void DL_Insert(struct Info **head_ref, struct Info *newNode)
{
    struct Info *current;

    /*base case list is empty*/
    if (*head_ref == NULL)
    {
        *head_ref = newNode;
    }

    /*new node data smaller than head. new node = head*/
    else if ((*head_ref)->itm >= newNode->itm)
    {
        newNode->inext = *head_ref;
        newNode->inext->iprev = newNode;
        *head_ref = newNode;
    }

    else
    {
        /*search for node to place after the new node*/
        current = *head_ref;
        while (current->inext != NULL && current->inext->itm < newNode->itm)
        {
            current = current->inext;
        }

        newNode->inext = current->inext;

        /*if it is not the last node*/
        if (current->inext != NULL)
        {
            newNode->inext->iprev = newNode;
        }

        current->inext = newNode;
        newNode->iprev = current;
    }
}

void DL_Delete(struct Info **head, int itm)
{
    struct Info *temp = *head;
    /*base case*/
    if (*head == NULL)
        printf("%s\n", "This Info list is empty!Why would you want to delete anything?");

    /* if node to be deleted is head node*/
    if (((*head)->itm == itm))
    {
        temp = *head; /*backup to free the memory*/
        *head = (*head)->inext;
        free(temp);
    }
    else
    {
        struct Info *current = *head;
        while (current->inext != NULL)
        {
            if (current->inext->itm == itm)
            {
                temp = current->inext;
                current->inext = current->inext->inext;
                current->inext->inext->iprev = current;
                free(temp);
                /*break to delete first occurance*/
            }
            else
                current = current->inext;
        }
    }
}

int DL_LookUp(struct Info *head, int itm) {
     struct Info *current = head;

    if (head == NULL)
    {
        printf("%s\n", "This  list is empty!Why would you want to print anything?");
    }
    while (current)
    {
        if (current->itm == itm)
        {
            return 1; /*found */
        }
        current = current->inext;
    }
    return 0; /*not found*/
}

void DL_Print(struct Info *head)
{

    struct Info *temp = head;
    if (head == NULL)
    {
        printf("%s\n", "This Info list is empty!Why would you want to print anything?");
    }
    while (temp)
    {
        printf("%s %d %s %d\n", "Id:", temp->iId, "Time stamp:", temp->itm);
        temp = temp->inext;
    }
}

int main(void)
{
    struct Info *dummy;
    struct Info *head = NULL;

    dummy = create_node(0, 1);

    DL_Insert(&head, dummy);

    dummy = create_node(1, 2);
    DL_Insert(&head, dummy);

    dummy = create_node(5, 3);
    DL_Insert(&head, dummy);

    dummy = create_node(7, 4);
    DL_Insert(&head, dummy);

    dummy = create_node(3, 5);
    DL_Insert(&head, dummy);

    dummy = create_node(4, 6);
    DL_Insert(&head, dummy);

    dummy = create_node(5, 7);
    DL_Insert(&head, dummy);

    dummy = create_node(55, 3);
    DL_Insert(&head, dummy);

    DL_Delete(&head, 2);

    

    DL_Print(head);
    printf("%d\n", DL_LookUp(head,7));
    return 0;
}