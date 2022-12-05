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
#include <assert.h>
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
		if (temp->snext == NULL)
		{
			printf("%d", temp->sId);
		}
		else
		{
			printf("%d,", temp->sId);
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
		if (temp->snext == NULL)
		{
			printf("%d", temp->sId); /*TO REMOVE FINAL , IF THERE IS NO ELEMENT LEFT TO PRINT*/
		}
		else
		{
			printf("%d,", temp->sId);
		}
		temp = temp->snext;
	}
} /*this function prints sub info*/

void DL_Print_consume(struct Info *head)
{
	struct Info *temp;
	temp = head;
	while (temp != NULL)
	{
		if (temp->inext == NULL)
		{
			printf("(%d:%d)\n", temp->iId, temp->itm); /*TO REMOVE FINAL -> IF THERE IS NO ELEMENT LEFT TO PRINT AND ADD THE NEW LINE*/
		}
		else
		{
			printf("(%d:%d)->", temp->iId, temp->itm);
		}
		temp = temp->inext;
	}
}

void SL_Delete(struct SubInfo **head, int sId)
{
	/*temp is used to freeing the memory*/
	struct SubInfo *temp = *head;

	/* key found on the head node.*/
	/*move to head node to the next and free the head.*/
	if ((*head)->sId == sId)
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
			if (current->snext->sId == sId)
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

int SL_Lookup(struct SubInfo *head, int sId)
{
	struct SubInfo *current = head;

	while (current)
	{
		if (current->sId == sId)
		{
			return 1; /*found*/
		}
		current = current->snext;
	}
	return 0; /*not found*/
}

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
	int i = 0;
	struct SubInfo *new_node = (struct SubInfo *)malloc(sizeof(struct SubInfo));

	new_node->sId = sId;
	new_node->stm = stm;
	new_node->snext = NULL;

	for (i; i < MG; ++i)
	{
		new_node->sgp[i] = (struct Info *)1; /*THIS CREATES THE DEFAULT LAYOUT OF THE sgp pointer table*/
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
				for (print_after_insert; print_after_insert < num_of_gids - 1; ++print_after_insert)
				{
					printf("GROUPID = <%d>,INFOLIST=", G[gids_arr[print_after_insert]].gId);
					printf("<");
					DL_Print(G[gids_arr[print_after_insert]].gfirst);
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
				for (print_after_subscribe; print_after_subscribe < num_of_gids - 1; ++print_after_subscribe)
				{
					printf("GROUPID = <%d>,SUBLIST=", G[print_after_subscribe].gId);
					printf("<");
					L_Print(G[gids_arr[print_after_subscribe]].ggsub);
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

		/* Consume
		 * C <sId> */
		case 'C':
		{
			int sId;
			sscanf(buff, "%c %d", &event, &sId);
			if (Consume(sId) == 0)
			{
				DPRINT("%c <%d> DONE\n", event, sId);
				struct SubInfo *temp;
				temp = S;
				while (temp)
				{
					int print_after_consume = 0;
					if (temp->sId == sId)
					{
						for (print_after_consume; print_after_consume < MG; ++print_after_consume)
						{
							if (temp->sgp[print_after_consume] != (struct Info *)1)
							{
								printf("GROUPID=<%d>,", G[print_after_consume].gId);
								printf("INFOLIST=<");
								DL_Print(G[print_after_consume].gfirst);
								printf(">,");
								printf("NEWGP=<%d>", temp->sgp[print_after_consume]->iId);
							}
						}
					}
					temp = temp->snext;
				}
			}
			else
			{
				fprintf(stderr, "%c %d failed\n", event, sId);
			}
			break;
		}

		/* Delete_Subscriber
		 * D <sId>: */
		case 'D':
		{
			int sId;
			sscanf(buff, "%c %d", &event, &sId);
			if (Delete_Subscriber(sId) == 0)
			{
				DPRINT("%c <%d> DONE\n", event, sId);
				int print_after_delete = 0;
				printf("SUBSCRIBERLIST=<");
				SL_Print(S);
				printf(">\n");
				for (print_after_delete; print_after_delete < MG; ++print_after_delete)
				{
					printf("GROUPID=<%d>,", G[print_after_delete].gId);
					printf("SUBLIST=<");
					L_Print(G[print_after_delete].ggsub);
					printf(">\n");
				}
			}
			else
			{
				fprintf(stderr, "%c %d failed\n", event, sId);
			}
			break;
		}

		/* Print
		 * P */
		case 'P':
		{
			if (Print_all() == 0)
			{
				DPRINT("%c DONE\n", buff[0]);
				struct SubInfo *temp = NULL;
				int print_after_print = 0;
				int valid_teams = 0;
				int numSubs = 0;
				int run = 0;
				for (print_after_print; print_after_print < MG; ++print_after_print)
				{
					printf("GROUPID= <%d>,", G[print_after_print].gId);
					printf("INFOLIST=<");
					DL_Print(G[print_after_print].gfirst);
					printf(">,");
					printf("SUBLIST=<");
					L_Print(G[print_after_print].ggsub);
					printf(">\n");
				}
				printf("SUBSCRIBERLIST=<");
				SL_Print(S);
				printf(">\n");
				temp = S;
				while (temp)
				{
					int print_interests = 0;
					printf("SUBSCRIBERID=<%d>,GROUPLIST=<", temp->sId);
					for (print_interests; print_interests < MG; ++print_interests)
					{
						if (temp->sgp[print_interests] != (struct Info *)1)
						{

							printf("%d,", print_interests + 1); /*I HAVE TO REMOVE THE LAST , AT SOME POINT. not important tho what can you do*/
						}
					}
					printf(">\n");
					temp = temp->snext;
					numSubs++;
				}
				for (run; run < MG; ++run)
				{
					if (G[run].gfirst != NULL)
					{
						valid_teams++; /*i suppose valid groups are the groups that have information attached to them*/
					}
				}
				printf("NO_GROUPS=<%d>,NO_SUBSCRIBERS=<%d>", valid_teams, numSubs);
			}
			else
			{
				fprintf(stderr, "%c failed\n", buff[0]);
			}

			break;
		}
		}
	}

	/*free_all();*/
	return EXIT_SUCCESS;
}