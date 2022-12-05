/***************************************************************
 *
 * file: main.c
 *
 * @Author  Nikolaos Vasilikopoulos (nvasilik@csd.uoc.gr)
 * @Version 25-10-2022
 *
 * @e-mail       hy240-list@csd.uoc.gr
 *
 * @brief   Main function for the needs of CS-240 project 2022.Prof. Panagiota Fatourou.
 * @see     Compile with command: gcc -ansi main.c pss.c -o run
 ***************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include "pss.h"

#define BUFFER_SIZE 1024 /* Maximum length of a line in input file */

/* Uncomment the following line to enable debugging prints
 * or comment to disable it */
#define DEBUG
#ifdef DEBUG
#define DPRINT(...) fprintf(stderr, __VA_ARGS__);
#else /* DEBUG */
#define DPRINT(...)
#endif /* DEBUG */

struct Group groups[MG];
struct Group *G = groups;
struct SubInfo *S;

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

struct Info *DL_LookUp(struct Info *head, int itm, int iId)
{
	struct Info *current = head;

	if (head == NULL)
	{
		printf("%s\n", "This  list is empty!Why would you want to print anything?");
	}
	while (current)
	{
		if (current->itm == itm && current->iId == iId)
		{
			return current; /*found */
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
		printf("%s", "This Info list is empty!Why would you want to print anything?");
	}
	while (temp)
	{
		if (temp->inext == NULL)
		{
			printf("%d", temp->iId); /*TO REMOVE FINAL , IF THERE IS NO ELEMENT LEFT TO PRINT*/
		}
		else
		{
			printf("%d,", temp->iId);
		}
		temp = temp->inext;
	}
}

struct Info *create_node(int iId, int itm)
{
	int i = 0;
	struct Info *new_node = (struct Info *)malloc(sizeof(struct Info));
	new_node->itm = itm;
	new_node->iId = iId;
	new_node->iprev = new_node->inext = NULL;

	for (i; i < MG; ++i)
	{
		new_node->igp[i] = 0; /*initialize igp = 0 This is an important change*/
	}

	return new_node;
}

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
		printf("%s", "This  list is empty!Why would you want to print anything?");
	}
	while (temp != NULL)
	{
		if(temp->snext==NULL){ 
			printf(" %d", temp->sId);
		}else{
		printf(" %d,", temp->sId);
		}
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
		/*printf("%s\n", "---");*/
		return 0;
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

struct Subscription *newNode(int data)
{
	struct Subscription *new_node = (struct Subscription *)malloc(sizeof(struct Subscription));
	new_node->sId = data;
	new_node->snext = NULL;

	return new_node;
} /* Function to create new node*/

void SL_Print(struct SubInfo *head)
{
	struct SubInfo *temp = head;

	if (head == NULL)
	{
		printf("%s", "This SubInfo list is empty!Why would you want to print anything?");
	}
	while (temp != NULL)
	{
		if(temp->snext==NULL){
			printf("%d", temp->sId);  /*TO REMOVE FINAL , IF THERE IS NO ELEMENT LEFT TO PRINT*/
		}else{
				printf("%d,", temp->sId);							
		}
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
 };            // this function looks ups the id in  sub info AND IS A BACKUP IN CASE I NEED IT

*/

struct SubInfo *middle(struct SubInfo *start, struct SubInfo *last)
{

	struct SubInfo *min = start;
	struct SubInfo *max = start->snext;

	if (start == NULL)
		return NULL; /*list empty*/

	while (max != last)
	{
		max = max->snext;
		if (max != last)
		{
			min = min->snext;
			max = max->snext;
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
	int i=0;
	struct SubInfo *new_node = (struct SubInfo *)malloc(sizeof(struct SubInfo));

	new_node->sId = sId;
	new_node->stm = stm;
	new_node->snext = NULL;

	for(i;i<MG;++i){ 
		new_node->sgp[i] = (struct Info*)1; /*THIS CREATES THE DEFAULT LAYOUT OF THE sgp pointer table*/
	}

	return new_node;
} /*this is a utility function to add nodes to SubInfo list on this example.*/

/**
 * @brief Parsing event arguments from buffer
 *
 * @param buff String of current line in the test file
 * @param int_arr_size Pointer to integer that represents the number of arguments in the test after the Event char
 *
 * @return 0 on success
 *         1 on failure
 */
static int *event_args(char *buff, unsigned int *int_arr_size)
{
	int *int_arr;
	char event = '\0';
	int value;
	char *p = buff + 1;
	unsigned int len = 0;
	unsigned int count_args = 1;
	unsigned int i = 0;
	sscanf(buff, "%c", &event);
	while (sscanf(p, "%d%n", &value, &len) == 1 && value != -1)
	{
		count_args++;
		p += len;
	}
	p = buff + 1;
	(*int_arr_size) = count_args;
	int_arr = malloc(count_args * sizeof(int));
	while (sscanf(p, "%d%n", &value, &len) == 1)
	{
		int_arr[i++] = value;
		p += len;
		if (value == -1)
		{
			break;
		}
	}

	return int_arr;
}

/**
 * @brief Optional function to initialize data structures that
 *        need initialization
 *
 * @return 0 on success
 *         1 on failure
 */
int initialize(void)
{
	int j = 0;
	for (j; j < MG; ++j)
	{
		G[j].gId = j + 1;
		G[j].gfirst=NULL;
	}
}

/**
 * @brief Insert info
 *
 * @param iTM Timestamp of arrival
 * @param iId Identifier of information
 * @param gids_arr Pointer to array containing the gids of the Event.
 * @param size_of_gids_arr Size of gids_arr including -1
 * @return 0 on success
 *          1 on failure
 */
int Insert_Info(int iTM, int iId, int *gids_arr, int size_of_gids_arr)
{

	if (size_of_gids_arr <= 1 || size_of_gids_arr > 65)
	{
		return 1; /*ERROR DETECTION TOO FEW OR TOO MANY ARGUMENTS : FAILED*/
	}
	int i = 0;
	struct Info *temp_info;
	struct Info *l;
	for (i; i < size_of_gids_arr - 1; ++i)
	{
		if (gids_arr[i] > 64)
		{
			return 1; /*such teams dont exist. We have only up to 64 groups*/
		}
		gids_arr[i] = gids_arr[i] - 1; /*to adjust the index to actual indexes*/ 
		if (G[gids_arr[i]].gfirst == NULL)
		{
			G[gids_arr[i]].gfirst = create_node(iId, iTM); /*if it doesnt have anything inside it, add*/
		}
		else
		{
			DL_Insert(&G[gids_arr[i]].gfirst, create_node(iId, iTM)); /*else append keeping the list sorted*/
		}

		l = DL_LookUp(G[gids_arr[i]].gfirst, iTM, iId);
		int j = 0;
		for (j; j < size_of_gids_arr - 1; ++j)
		{
			if (l->igp[gids_arr[j]] == 0)
			{
				l->igp[gids_arr[j]] = 1; /*establish igp table*/
			}
			else
				l->igp[gids_arr[j]] = 0;
		}

		temp_info = G[gids_arr[i]].gfirst;
		while (temp_info)
		{
			if (temp_info->inext == NULL)
			{
				G[gids_arr[i]].glast = temp_info; /*establish glast pointer*/
			}
			temp_info = temp_info->inext;
		}
	}

	return 0; /*success in general*/
}

/**
 * @brief Subsriber Registration
 *
 * @param sTM Timestamp of arrival
 * @param sId Identifier of subscriber
 * @param gids_arr Pointer to array containing the gids of the Event.
 * @param size_of_gids_arr Size of gids_arr including -1
 * @return 0 on success
 *          1 on failure
 */
int Subscriber_Registration(int sTM, int sId, int *gids_arr, int size_of_gids_arr)
{
	struct SubInfo * temp; 
	if (size_of_gids_arr <= 1 || size_of_gids_arr > 65)
	{
		return 1; /*ERROR DETECTION TOO FEW OR TOO MANY ARGUMENTS : FAILED*/
	}
	int i = 0;
	for (i; i < size_of_gids_arr - 1; ++i)
	{
		if (gids_arr[i] > 64)
		{
			return 1; /*such teams dont exist. We have only up to 64 groups*/
		}
		gids_arr[i] = gids_arr[i] - 1; /*to adjust the index to actual indexes*/ 
		if (G[gids_arr[i]].ggsub == NULL)
		{
			G[gids_arr[i]].ggsub = newNode(sId); /*if it doesnt have anything inside it, add*/
		}
		else /*HERE WE INITIALIZE GGSUB WITH A SINGLY LINKED LIST OF ALL THE IDS OF THE SUBSCRIBERS SUBRSCRIBED TO SAID  INFO*/
		{
			L_Insert(&G[gids_arr[i]].ggsub, newNode(sId)); /*else append.The appending happens at the head so first value to be appended = last node */
		}
	}
	if (S == NULL)
	{
		S = SL_newNode(sId, sTM);
	}
	else
	{
		SL_Insert(&S, SL_newNode(sId, sTM));
	}

int rep_in_groups= 0;
for(rep_in_groups; rep_in_groups<MG;++rep_in_groups){
	temp= S;
	/*printf("sthn omada %d uparxoun: \n", G[rep_in_groups].gId);*/
	while(temp){ 
		if(L_Lookup((struct Subscription *)G[rep_in_groups].ggsub,temp->sId)){ 
				/*printf("uparcw eimai o %d\n", temp->sId);*/
				temp->sgp[rep_in_groups]=G[rep_in_groups].gfirst;
			}
		temp= temp->snext;
	}
}
	
	return 0; /*success*/
}

/**
 * @brief The main function
 *
 * @param argc Number of arguments
 * @param argv Argument vector
 *
 * @return 0 on success
 *         1 on failure
 */
int main(int argc, char **argv)
{
	int rep = 0; /*dummy variable for for loops*/
	FILE *fin = NULL;
	char buff[BUFFER_SIZE], event = '\0';

	initialize(); /*gives each group an id */

	/* Check command buff arguments */
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
		return EXIT_FAILURE;
	}

	/* Open input file */
	if ((fin = fopen(argv[1], "r")) == NULL)
	{
		fprintf(stderr, "\n Could not open file: %s\n", argv[1]);
		perror("Opening test file\n");
		return EXIT_FAILURE;
	}

	/* Read input file buff-by-buff and handle the events */
	while (fgets(buff, BUFFER_SIZE, fin))
	{
		DPRINT("\n>>> Event: %s\n", buff);
		switch (buff[0])
		{

		/* Comment */
		case '#':
			break;

		/* Insert_Info
		 * I <itm> <iId> <gId1> <gId2> ... <gIdk> -1 */
		case 'I':
		{
			int itm;
			int iId;
			unsigned int num_of_gids;
			int *event_args_arr;
			int *gids_arr;
			event_args_arr = event_args(buff, &num_of_gids);
			itm = event_args_arr[0];
			iId = event_args_arr[1];
			gids_arr = event_args_arr + 2;
			num_of_gids -= 2;
			if (Insert_Info(itm, iId, gids_arr, num_of_gids) == 0)
			{
				DPRINT("%c <%d> <%d> DONE\n", buff[0], itm, iId);
				int print_after_insert = 0;
				for (print_after_insert; print_after_insert < MG; ++print_after_insert)
				{
					printf("GROUPID = <%d>,INFOLIST=", G[print_after_insert].gId);
					printf("<");
					DL_Print(G[print_after_insert].gfirst);
					printf(">");
					printf("\n");
				}
			}
			else
			{
				fprintf(stderr, "%s failed\n", buff);
			}
			num_of_gids = 0;
			free(event_args_arr);
			break;
		}

		/* Subscriber_Registration
		 * S <sΤΜ> <sId> <gId1> <gId2> ... <gIdm> -1  */
		case 'S':
		{
			int sTM, sId;
			unsigned int num_of_gids;
			int *event_args_arr;
			int *gids_arr;
			event_args_arr = event_args(buff, &num_of_gids);
			sTM = event_args_arr[0];
			sId = event_args_arr[1];
			gids_arr = event_args_arr + 2;
			num_of_gids -= 2;
			if (Subscriber_Registration(sTM, sId, gids_arr, num_of_gids) == 0)
			{
				DPRINT("%c <%d> <%d> DONE\n", buff[0], sTM, sId);
				printf("SUBSCRIBERLIST=<");
				SL_Print(S);
				printf(">\n");
				int print_after_subscribe = 0;
				for(print_after_subscribe;print_after_subscribe<MG;++print_after_subscribe){
					printf("GROUPID = <%d>,SUBLIST=", G[print_after_subscribe].gId);
					printf("<");
					L_Print(G[print_after_subscribe].ggsub);
					printf(">");
					printf("\n");
				}
			}
			else
			{
				fprintf(stderr, "%s failed\n", buff);
			}
			num_of_gids = 0;
			free(event_args_arr);
			break;
		}
		}
	}
}