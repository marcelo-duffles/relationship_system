//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: getFriendshipInvitation() primary function source file 
// Date: 26/12/2004
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: getFriendshipInvitation.h,v $
 * Revision 1.1  2005/02/16 22:11:21  marceloddm
 * Initial revision
 *
 *
 */


 
#ifndef _GET_FRIENDSHIP_INVITATION_H_
#define _GET_FRIENDSHIP_INVITATION_H_ "@(#)getFriendshipInvitation.h $Revision: 1.1 $"


#include "types.h"

/*---------------------------------------------------------------------------------------------------------*/
unsigned getFriendshipInvitation ( userIdType userId, userDataType ** firstInvitation);
/* 	
INPUT ARGUMENTS
	- userIdType userId
	- userDataType ** firstInvitation
	
DESCRIPTION
	The getFriendshipinvitation() function searches for the given user invitations and builds a FIFO with his invitations using the 'firstInvitation' pointer.
	
RETURNED VALUES
	The getFriendshipInvitation() function returns:
	- GET_FRIENDSHIP_INVITATION__ERROR_OPENING_USER_IN_FILE_FOR_READING if an error occurs while trying to open the user in file for reading;
	- GET_FRIENDSHIP_INVITATION__USER_IN_FILE_DOES_NOT_EXIST if the user in file doesn't exist;
	- GET_FRIENDSHIP_INVITATION__NO_INVITATIONS_FOUND if the given user does not have invitations;
	- An error code of insertFIFO() function if an error occurs while inserting a friend into the FIFO;
	- An error code of getLongFilename() function if an error occours while getting long filename;
	- An error code of getUserId() function if an error occours while getting an userId from a file;
	- OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

#endif 

/*$RCSfile: getFriendshipInvitation.h,v $*/


