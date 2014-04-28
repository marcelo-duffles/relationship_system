//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: getFriends() primary function source file 
// Date: 26/12/2004
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2004/12/28 00:38:14 $
 * $Log: getFriends.h,v $
 * Revision 1.1  2004/12/28 00:38:14  marceloddm
 * Initial revision
 *
 */

 
#ifndef _GET_FRIENDS_H_
#define _GET_FRIENDS_H_ "@(#)getFriends.h $Revision: 1.1 $"


#include "types.h"

/*---------------------------------------------------------------------------------------------------------*/
unsigned getFriends ( userIdType userId, userDataType ** firstFriend);
/* 	
INPUT ARGUMENTS
	- userIdType userId
	- userIdType firstFriend
	
DESCRIPTION
	The getFriends() function searches for the given user friends and builds a FIFO with his friends data using the 'firstFriend' pointer.
	
RETURNED VALUES
	The getFriends() function returns:
	- GET_FRIENDS__ERROR_OPENING_FRIENDS_FILE_FOR_READING if an error occurs while trying to open the friends file for reading;
	- GET_FRIENDS__FRIENDS_FILE_DOES_NOT_EXIST if the friends file doesn't exist;
	- GET_FRIENDS__NO_FRIENDS_FOUND if the given user does not have friends;
	- An error code of getDataFromId() function if an error occurs while getting data from an id;
	- An error code of insertFIFO() function if an error occurs while inserting a friend into the FIFO;
	- An error code of getLongFilename() function if an error occours while getting long filename;
	- An error code of getUserId() function if an error occours while getting an userId from a file;
	- OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

#endif 

/*$RCSfile: getFriends.h,v $*/


