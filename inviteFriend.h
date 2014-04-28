//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: inviteFriend() primary function source file 
// Date: 23/12/2004
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: inviteFriend.h,v $
 * Revision 1.2  2005/02/16 22:11:21  marceloddm
 * CGI's added
 *
 * Revision 1.1  2004/12/25 17:27:50  marceloddm
 * Initial revision
 *
 */

 
#ifndef _INVITE_FRIEND_H_
#define _INVITE_FRIEND_H_ "@(#)inviteFriend.h $Revision: 1.2 $"

#include "types.h"

/*---------------------------------------------------------------------------------------------------------*/
unsigned inviteFriend ( userIdType invitingFriend, userIdType invitedFriend);
/* 	
INPUT ARGUMENTS
	- userIdType invitingFriend
	- userIdType invitedFriend
	
DESCRIPTION
	The inviteFriend() function does the needed operations to invite the 'invited friend' to become friend of the 'invitingFriend' .
	
NOTE
	If the inviting user and the invited user where already friends the function returns the INVITE_FRIEND__FRIENDSHIP_ALREADY_EXISTS error code .
	
RETURNED VALUES
	The inviteFriend() function returns:
	- INVITE_FRIEND__CANNOT_INVITE_THE_OWN_USER if the given invitingFriend is the same than the invitedFriend.
	- INVITE_FRIEND__ERROR_OPENING_INVITED_FRIEND_OUT_FILE_FOR_READING if an error occurs while trying to open the invited friend`s out file for reading; 
	- INVITE_FRIEND__INVITED_FRIEND_OUT_FILE_DOES_NOT_EXIST if the invited friend's out file doesn't exist;
	- INVITE_FRIEND__THERE_IS_ALREADY_AN_INVITATION_TO_THE_INVITING_FRIEND_IN_THE_INVITED_FRIEND_OUT_FILE if there's already an invitation to the inviting friend in the invited friend out file;
	- INVITE_FRIEND__ERROR_OPENING_INVITING_FRIEND_IN_FILE_FOR_READING if an error occurs while trying to open the inviting friend`s in file for reading; 
	- INVITE_FRIEND__INVITING_FRIEND_IN_FILE_DOES_NOT_EXIST if the inviting friend's in file doesn't exist;
	- INVITE_FRIEND__THERE_IS_ALREADY_AN_INVITATION_FROM_THE_INVITED_FRIEND_IN_THE_INVITING_FRIEND_IN_FILE if there's already an invitation from the invited friend in the inviting friend in file.
	- INVITE_FRIEND__ERROR_OPENING_INVITED_FRIEND_IN_FILE_FOR_READING if an error occurs while trying to open the invited friend`s in file for reading;
	- INVITE_FRIEND__INVITED_FRIEND_IN_FILE_DOES_NOT_EXIST if the invited friend`s in file doesn't exist;
	- INVITE_FRIEND__ERROR_OPENING_INVITED_FRIEND_IN_TEMP_FILE_FOR_WRITTING if an error occurs while trying to open the invited friend`s in temporary file for writting;
	- INVITE_FRIEND__THERE_IS_ALREADY_AN_INVITATION_IN_THE_INVITED_FRIEND_IN_FILE if there`s already an invitation from the given inviting friend userId in the invited friend`s in file;
	- INVITE_FRIEND__ERROR_OPENING_INVITING_FRIEND_OUT_FILE_FOR_READING if an error occurs while trying to open the inviting friend`s out file for reading;
	- INVITE_FRIEND__INVITING_FRIEND_OUT_FILE_DOES_NOT_EXIST if the inviting friend`s out file doesn't exist;
	- INVITE_FRIEND__ERROR_OPENING_INVITING_FRIEND_OUT_TEMP_FILE_FOR_WRITTING if an error occurs while trying to open the inviting friend`s out temporary file for writting;
	- INVITE_FRIEND__THERE_IS_ALREADY_AN_INVITATION_IN_THE_INVITING_FRIEND_OUT_FILE if there`s already an invitation to the given invited friend userId in the inviting friend`s out file;
	- INVITE_FRIEND__ERROR_OPENING_FRIENDS_FILE_FOR_READING if an error occurs while trying to open the friends file for reading;
	- INVITE_FRIEND__FRIENDS_FILE_DOES_NOT_EXIST if the friends file doesn't exist;
	- INVITE_FRIEND__FRIENDSHIP_ALREADY_EXISTS if the inviting user and the invited user were already friends;
	- An error code of getLongFilename() function if an error occours while getting long filename;
	- An error code of getUserId() function if an error occours while getting an userId from a file;
	- An error code of putUserId() function if an error occours while putting an userId in a file;
	- OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

#endif 

/*$RCSfile: inviteFriend.h,v $*/

