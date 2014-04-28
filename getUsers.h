//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: getUsers() primary function source file 
// Date: 20/12/2004
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: getUsers.h,v $
 * Revision 1.2  2005/02/16 22:11:21  marceloddm
 * CGI's added
 *
 * Revision 1.1  2004/12/20 12:48:10  marceloddm
 * Initial revision
 *
 */

#include "types.h"
 
#ifndef _GET_USERS_H_
#define _GET_USERS_H_ "@(#)getUsers.h $Revision: 1.2 $"
/*---------------------------------------------------------------------------------------------------------*/
unsigned getUsers ( char * searchKey , userDataType ** firstFound );
/* 	
INPUT ARGUMENTS
	- char * searchKey
	
OUTPUT ARGUMENTS
	- userDataType ** firstFound
	
DESCRIPTION
	The getUsers() function search for users which contains the searchKey in their userNames.
	
RETURNED VALUES
	The getUsers() function returns:
	- GET_USERS__INVALID_SEARCH_KEY if the `searchKey` is invalid;
	- GET_USERS__ERROR_OPENING_USERS_FILE_FOR_READING if there's an error while opening the users file;
	- GET_USERS__USERS_FILE_DOES_NOT_EXIST if the users file doesn't exist;
	- GET_USERS__USER_NOT_FOUND if there are no users with userNames containing the searchKey;
	- An error code of getLongFilename() function if an error occours while getting long filename;
	- An error code of getUserData() function if an error occours while getting user data from a file;
	- An error code of insertFIFO() function if an error occurs while inserting in the FIFO;
	- OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

#endif

/*$RCSfile: getUsers.h,v $*/


