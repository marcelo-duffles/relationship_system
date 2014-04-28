//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: acceptFriendshipInvitation() primary function source file 
// Date: 22/12/2004
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: acceptFriendshipInvitation.h,v $
 * Revision 1.2  2005/02/16 22:11:21  marceloddm
 * CGI's added
 *
 * Revision 1.1  2004/12/20 20:01:24  marceloddm
 * Initial revision
 *
 */


 
#ifndef _ACCEPT_FRIENDSHIP_INVITATION_H_
#define _ACCEPT_FRIENDSHIP_INVITATION_H_ "@(#)acceptFriendshipInvitation.h $Revision: 1.2 $"

#include "types.h"

/*---------------------------------------------------------------------------------------------------------*/
unsigned acceptFriendshipInvitation ( userIdType invitedFriend, userIdType invitingFriend);
/* 	
INPUT ARGUMENTS
	- userIdType invitedFriend
	- userIdType invitingFriend
	
DESCRIPTION
	The acceptFriendshipInvitation() function does the needed operations to establish a friendship relationship between the 'invitingFriend' and the 'invitedFriend' .
	
NOTE
	If the inviting user and the invited user where already friends, their ids are removed from the .in and .out files, their friendship continues in the friends files and the ACCEPT_FRIENDSHIP_INVITATION__FRIENDSHIP_ALREADY_EXISTS error code is returned.
	
RETURNED VALUES
	The acceptFriendshipInvitation() function returns:
	- ACCEPT_FRIENDSHIP_INVITATION__ERROR_OPENING_INVITED_FRIEND_IN_FILE_FOR_READING if an error occurs while trying to open the invited friend`s in file for reading;
	- ACCEPT_FRIENDSHIP_INVITATION__INVITED_FRIEND_IN_FILE_DOES_NOT_EXIST if the invited friend`s in file doesn't exist;
	- ACCEPT_FRIENDSHIP_INVITATION__ERROR_OPENING_INVITED_FRIEND_IN_TEMP_FILE_FOR_WRITTING if an error occurs while trying to open the invited friend`s in temporary file for writting;
	- ACCEPT_FRIENDSHIP_INVITATION__INVITED_FRIEND_IN_FILE_DOES_NOT_HAVE_INVITATION_FROM_GIVEN_INVITING_FRIEND if there was no invitation from the given inviting friend userId in the invited friend`s in file;
	- ACCEPT_FRIENDSHIP_INVITATION__ERROR_OPENING_INVITING_FRIEND_OUT_FILE_FOR_READING if an error occurs while trying to open the inviting friend`s out file for reading;
	- ACCEPT_FRIENDSHIP_INVITATION__INVITING_FRIEND_OUT_FILE_DOES_NOT_EXIST if the inviting friend`s out file doesn't exist;
	- ACCEPT_FRIENDSHIP_INVITATION__ERROR_OPENING_INVITING_FRIEND_OUT_TEMP_FILE_FOR_WRITTING if an error occurs while trying to open the inviting friend`s out temporary file for writting;
	- ACCEPT_FRIENDSHIP_INVITATION__INVITING_FRIEND_OUT_FILE_DOES_NOT_HAVE_INVITATION_TO_GIVEN_INVITED_FRIEND if there was no invitation to the given invited friend userId in the inviting friend`s out file;
	- ACCEPT_FRIENDSHIP_INVITATION__ERROR_OPENING_FRIENDS_FILE_FOR_READING if an error occurs while trying to open the friends file for reading;
	- ACCEPT_FRIENDSHIP_INVITATION__FRIENDS_FILE_DOES_NOT_EXIST if the friends file doesn't exist;
	- ACCEPT_FRIENDSHIP_INVITATION__ERROR_OPENING_FRIENDS_TEMP_FILE_FOR_WRITING if an error occurs while trying to open the friends temporary file for writting;
	- ACCEPT_FRIENDSHIP_INVITATION__FRIENDSHIP_ALREADY_EXISTS if the inviting user and the invited user where already friends;
	- An error code of getLongFilename() function if an error occours while getting long filename;
	- An error code of getUserId() function if an error occours while getting an userId from a file;
	- An error code of putUserId() function if an error occours while putting an userId in a file;
	- OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

#endif 

/*$RCSfile: acceptFriendshipInvitation.h,v $*/


