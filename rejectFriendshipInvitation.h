//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: rejectFriendshipInvitation() primary function source file 
// Date: 22/12/2004
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2004/12/25 17:29:27 $
 * $Log: rejectFriendshipInvitation.h,v $
 * Revision 1.1  2004/12/25 17:29:27  marceloddm
 * Initial revision
 *
 */


 
#ifndef _REJECT_FRIENDSHIP_INVITATION_H_
#define _REJECT_FRIENDSHIP_INVITATION_H_ "@(#)rejectFriendshipInvitation.h $Revision: 1.1 $"

#include "types.h"

/*---------------------------------------------------------------------------------------------------------*/
unsigned rejectFriendshipInvitation ( userIdType invitedFriend, userIdType invitingFriend);
/* 	
INPUT ARGUMENTS
	- userIdType invitedFriend
	- userIdType invitingFriend
	
DESCRIPTION
	The rejectFriendshipInvitation() function does the needed operations to reject a friendship invitation between the 'invitingFriend' and the 'invitedFriend' .
	
RETURNED VALUES
	The acceptFriendshipInvitation() function returns:
	- REJECT_FRIENDSHIP_INVITATION__ERROR_OPENING_INVITED_FRIEND_IN_FILE_FOR_READING if an error occurs while trying to open the invited friend`s in file for reading;
	- REJECT_FRIENDSHIP_INVITATION__INVITED_FRIEND_IN_FILE_DOES_NOT_EXIST if the invited friend`s in file doesn't exist;
	- REJECT_FRIENDSHIP_INVITATION__ERROR_OPENING_INVITED_FRIEND_IN_TEMP_FILE_FOR_WRITTING if an error occurs while trying to open the invited friend`s in temporary file for writting;
	- REJECT_FRIENDSHIP_INVITATION__INVITED_FRIEND_IN_FILE_DOES_NOT_HAVE_INVITATION_FROM_GIVEN_INVITING_FRIEND if there was no invitation from the given inviting friend userId in the invited friend`s in file;
	- REJECT_FRIENDSHIP_INVITATION__ERROR_OPENING_INVITING_FRIEND_OUT_FILE_FOR_READING if an error occurs while trying to open the inviting friend`s out file for reading;
	- REJECT_FRIENDSHIP_INVITATION__INVITING_FRIEND_OUT_FILE_DOES_NOT_EXIST if the inviting friend`s out file doesn't exist;
	- REJECT_FRIENDSHIP_INVITATION__ERROR_OPENING_INVITING_FRIEND_OUT_TEMP_FILE_FOR_WRITTING if an error occurs while trying to open the inviting friend`s out temporary file for writting;
	- REJECT_FRIENDSHIP_INVITATION__INVITING_FRIEND_OUT_FILE_DOES_NOT_HAVE_INVITATION_TO_GIVEN_INVITED_FRIEND if there was no invitation to the given invited friend userId in the inviting friend`s out file;
	- An error code of getLongFilename() function if an error occours while getting long filename;
	- An error code of getUserId() function if an error occours while getting an userId from a file;
	- An error code of putUserId() function if an error occours while putting an userId in a file;
	- OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

#endif /*_REJECT_FRIENDSHIP_INVITATION_*/

/*$RCSfile: rejectFriendshipInvitation.h,v $*/


