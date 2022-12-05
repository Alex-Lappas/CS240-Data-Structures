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
		groups[j].gId = j;
	}
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
	int i = 0;

	for (i; i < size_of_gids_arr - 1; ++i)
	{
		if (groups[gids_arr[i]].gfirst == NULL)
		{
			groups[gids_arr[i]].gfirst = create_node(iId, iTM);
		}
		else
		{
			DL_Insert(&groups[gids_arr[i]].gfirst, create_node(iId, iTM));
		}
		/* DL_Print(groups[gids_arr[i]].gfirst); this should print out the first node X times where X is the number of groups intereted in the information*/
	}

	/*To gradually check progress of adding to list uncomment the following*/
	/*DL_Print(groups[2].gfirst);
	printf("spacerrrrrrrrrrrrrrrrrrrrrrrrrrrr1\n");
	DL_Print(groups[3].gfirst);
	printf("spacerrrrrrrrrrrrrrrrrrrrrrrrrrrr2\n");
	DL_Print(groups[4].gfirst);
	printf("spacerrrrrrrrrrrrrrrrrrrrrrrrrrrr3\n");
	DL_Print(groups[5].gfirst);
	printf("spacerrrrrrrrrrrrrrrrrrrrrrrrrrrr4\n");
	DL_Print(groups[6].gfirst);*/

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
int Subscriber_Registration(int sTM,int sId,int* gids_arr,int size_of_gids_arr){
    return EXIT_SUCCESS;
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
