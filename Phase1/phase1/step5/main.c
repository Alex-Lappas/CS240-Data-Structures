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

struct Info * DL_LookUp(struct Info *head, int itm , int iId )
{
	struct Info *current = head;

	if (head == NULL)
	{
		printf("%s\n", "This  list is empty!Why would you want to print anything?");
	}
	while (current)
	{
		if (current->itm == itm && current->iId==iId)
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
	while (temp){if(temp->inext==NULL){
		printf("%d", temp->iId); /*TO REMOVE FINAL , IF THERE IS NO ELEMENT LEFT TO PRINT*/
	}
	else{
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

struct Group groups[MG];

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
		groups[j].gId = j + 1;
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
	
	if(size_of_gids_arr <= 1){
		return 1 ; /*ERROR DETECTION TOO FEW ARGUMENTS : FAILED*/
	}
	int i = 0;
	struct Info *temp_info;
	struct Info *l;
	for (i; i < size_of_gids_arr - 1; ++i)
	{
		gids_arr[i]=gids_arr[i] - 1; //to adjust the index to actual indexes
		if (groups[gids_arr[i]].gfirst == NULL)
		{
			groups[gids_arr[i]].gfirst = create_node(iId, iTM); /*if it doesnt have anything inside it, add*/
		}
		else
		{
			DL_Insert(&groups[gids_arr[i]].gfirst, create_node(iId, iTM)); /*else append keeping the list sorted*/
		}

		l = DL_LookUp(groups[gids_arr[i]].gfirst,iTM,iId);
		int j = 0;
		for (j; j < size_of_gids_arr - 1; ++j)
		{
			//printf("%d\n", gids_arr[j]);
			if (l->igp[gids_arr[j]] == 0)
			{
				l->igp[gids_arr[j]] = 1; /*establish igp table*/
			}
			else
				l->igp[gids_arr[j]] = 0;
		}

		temp_info = groups[gids_arr[i]].gfirst;
		while (temp_info)
		{
			if (temp_info->inext == NULL)
			{
				groups[gids_arr[i]].glast = temp_info; /*establish glast pointer*/
			}
			temp_info = temp_info->inext;
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
				for(print_after_insert; print_after_insert<MG;++print_after_insert){ 
					printf("GROUPID = <%d>,INFOLIST=", groups[print_after_insert].gId);
					printf("<");
					DL_Print(groups[print_after_insert].gfirst);
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
			// break;
		}
		}

		/*return (EXIT_SUCCESS); COMMENT OR UNCOMMENT THIS TO READ SINGLE LINES OF INPUT*/
	}
	/*DL_Print(groups[0].gfirst);
	printf("spacerrrrrrrrrrrrrrrrrrrrrrrrrrrr1\n");
	DL_Print(groups[2].gfirst);
	printf("spacerrrrrrrrrrrrrrrrrrrrrrrrrrrr1\n");
	DL_Print(groups[3].gfirst);
	printf("spacerrrrrrrrrrrrrrrrrrrrrrrrrrrr2\n");
	DL_Print(groups[4].gfirst);
	printf("spacerrrrrrrrrrrrrrrrrrrrrrrrrrrr3\n");
	DL_Print(groups[5].gfirst);
	printf("spacerrrrrrrrrrrrrrrrrrrrrrrrrrrr4\n");
	DL_Print(groups[6].gfirst);
	printf("spacerrrrrrrrrrrrrrrrrrrrrrrrrrrr4\n");

	printf("%d\n", groups[2].glast->iId);
	printf("%d\n", groups[6].glast->iId);

	printf("Information with id %d is found in these groups: ", groups[3].gfirst->inext->iId);
	for(rep; rep<MG;++rep){
		printf("%d/", groups[3].gfirst->inext->igp[rep]);
	}*/
}