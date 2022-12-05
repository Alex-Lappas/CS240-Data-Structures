/***************************************************************
 *
 * file: pss.h
 *
 * @Author  Nikolaos Vasilikopoulos (nvasilik@csd.uoc.gr)
 * @Version 20-10-2020
 *
 * @e-mail       hy240-list@csd.uoc.gr
 *
 * @brief   Implementation of the "pss.h" header file for the Public Subscribe System,
 * function definitions
 *
 *
 ***************************************************************
 */
#include <stdio.h>
#include <stdlib.h>

#include "pss.h"

/**
 * @brief Optional function to initialize data structures that
 *        need initialization
 *
 * @return 0 on success
 *         1 on failure
 */
int initialize(void){
   int j=0;
	for(j;j<MG;++j){ 
		G[j].gId = j +1;
		G[j].gfirst=NULL;
	}
	return 0;
}
/**
 * @brief Free resources
 *
 * @return 0 on success
 *         1 on failure
 */
int free_all(void){
    return EXIT_SUCCESS;
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
		if (gids_arr[i] > 64 || gids_arr[i]-1<0)
		{
			return 1; /*such teams dont exist. We have only up to 64 groups marked from 1 to 64*/
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

	return 0; /*success*/
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
	struct SubInfo *temp;
	if (size_of_gids_arr <= 1 || size_of_gids_arr > 65)
	{
		return 1; /*ERROR DETECTION TOO FEW OR TOO MANY ARGUMENTS : FAILED*/
	}
	int i = 0;
	for (i; i < size_of_gids_arr - 1; ++i)
	{
		if (gids_arr[i] > 64 || gids_arr[i]-1<0)
		{
			return 1; /*such teams dont exist. We have only up to 64 groups marked from 1 to 64*/
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

	int rep_in_groups = 0;
	for (rep_in_groups; rep_in_groups < MG; ++rep_in_groups)
	{
		temp = S;
		/*printf("sthn omada %d uparxoun: \n", G[rep_in_groups].gId);*/
		while (temp)
		{
			if (L_Lookup((struct Subscription *)G[rep_in_groups].ggsub, temp->sId))
			{
				/*printf("uparcw eimai o %d\n", temp->sId);*/
				temp->sgp[rep_in_groups] = G[rep_in_groups].gfirst;
			}
			temp = temp->snext;
		}
	}

	return 0; /*success*/
}
/**
 * @brief Consume Information for subscriber
 *
 * @param sId Subscriber identifier
 * @return 0 on success
 *          1 on failure
 */
int Consume(int sId){
    return EXIT_SUCCESS;
}
/**
 * @brief Delete subscriber
 *
 * @param sId Subscriber identifier
 * @return 0 on success
 *          1 on failure
 */
int Delete_Subscriber(int sId)
{
	struct SubInfo *temp;
	int exists = 0;
	temp = S;
	while (temp)
	{
		if (temp->sId == sId)
		{ /*if we enter this if statement we know for sure that sub exists somewhere in the groups*/
			exists = 1;
			SL_Delete(&S, sId);
			int reps_to_del=0;
			for(reps_to_del;reps_to_del<MG;++reps_to_del){ 
				if(L_Lookup(G[reps_to_del].ggsub,sId)){
					L_Delete(&G[reps_to_del].ggsub,sId); /*delete subscriber from each group*/
				}else{
					continue; /*if subscriber isnt subbed in said group it is pointless to try and delete it*/
				}
			}
		}
		temp = temp->snext;
	}
	if (exists)
	{
		return 0; /*exists. Event is DONE*/
	}
	else
	{
		return 1; /*doestn exist. event is FAILED*/
	}
}

/**
 * @brief Print Data Structures of the system
 *
 * @return 0 on success
 *          1 on failure
 */
int Print_all(void)
{
	int print_index = 0;
	struct SubInfo *temp = NULL;
	for (print_index; print_index < MG; ++print_index)
	{
		printf("Group with id %d information:\n", G[print_index].gId);
		printf("INFOLIST=<");
		DL_Print(G[print_index].gfirst);
		printf(">\n");
		printf("SUBSCRIPTIONRLIST=<");
		L_Print(G[print_index].ggsub);
		printf(">\n");
	}
	printf("SUBSCRIBERSLIST=<");
	SL_Print(S);
	printf(">\n");
	temp = S;
	while (temp)
	{
		int print_interests = 0;
		printf("Subscriber %d is interested in information with id =<", temp->sId);
		for (print_interests; print_interests < MG; ++print_interests)
		{
			if (temp->sgp[print_interests] != (struct Info *)1 && temp->sgp[print_interests] != NULL)
			{

				printf("%d,", temp->sgp[print_interests]->iId); /*I HAVE TO REMOVE THE LAST , AT SOME POINT. not important tho what can you do*/
			}
		}
		printf(">\n");
		temp = temp->snext;
	}
	return 0; /*always success*/
}