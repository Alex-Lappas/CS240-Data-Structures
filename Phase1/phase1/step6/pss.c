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
	
	if(size_of_gids_arr <= 1){
		return 1 ; /*ERROR DETECTION TOO FEW ARGUMENTS : FAILED*/
	}
	int i = 0;
	struct Info *temp_info;
	struct Info *l;
	for (i; i < size_of_gids_arr - 1; ++i)
	{
		gids_arr[i]=gids_arr[i] - 1; //to adjust the index to actual indexes
		if (G[gids_arr[i]].gfirst == NULL)
		{
			G[gids_arr[i]].gfirst = create_node(iId, iTM); /*if it doesnt have anything inside it, add*/
		}
		else
		{
			DL_Insert(&G[gids_arr[i]].gfirst, create_node(iId, iTM)); /*else append keeping the list sorted*/
		}

		l = DL_LookUp(G[gids_arr[i]].gfirst,iTM,iId);
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
int Delete_Subscriber(int sId){
    return EXIT_SUCCESS;
}
/**
 * @brief Print Data Structures of the system
 *
 * @return 0 on success
 *          1 on failure
 */
int Print_all(void){
    return EXIT_SUCCESS;
}
