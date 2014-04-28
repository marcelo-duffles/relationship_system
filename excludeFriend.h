//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: excludeFriend() primary function source file. 
// Date: 25/12/2004
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: excludeFriend.h,v $
 * Revision 1.2  2005/02/16 22:11:21  marceloddm
 * CGI's added
 *
 * Revision 1.1  2004/12/25 17:01:41  marceloddm
 * Initial revision
 *
 */

 
#ifndef _EXCLUDE_FRIEND_H_
#define _EXCLUDE_FRIEND_H_ "@(#)excludeFriend.h$Revision: 1.2 $"


#include "types.h"

/*---------------------------------------------------------------------------------------------------------*/
unsigned excludeFriend ( userIdType excludedFriend, userIdType excludingFriend);
/* 	
INPUT ARGUMENTS
	- userIdType excludedFriend
	- userIdType excludingFriend
	
DESCRIPTION
	The excludeFriend() function does the needed operations to exclude a friendship relationship between the 'excludingFriend' and the 'excludedFriend' .
	
RETURNED VALUES
	The excludeFriend() function returns:
	- EXCLUDE_FRIEND__ERROR_OPENING_FRIENDS_FILE_FOR_READING if an error occurs while trying to open the friends file for reading;
	- EXCLUDE_FRIEND__FRIENDS_FILE_DOES_NOT_EXIST if the friends file doesn't exist;
	- EXCLUDE_FRIEND__ERROR_OPENING_FRIENDS_TEMP_FILE_FOR_WRITING if an error occurs while trying to open the friends temporary file for writting;
	- EXCLUDE_FRIEND__THE_TWO_GIVEN_USERS_WERE_NOT_FRIENDS if the inviting user and the invited user were not friends;
	- An error code of getLongFilename() function if an error occours while getting long filename;
	- An error code of getUserId() function if an error occours while getting an userId from a file;
	- An error code of putUserId() function if an error occours while putting an userId in a file;
	- OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

#endif 

/*$RCSfile: excludeFriend.h,v $*/


