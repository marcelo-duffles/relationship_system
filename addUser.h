//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: addUser() primary function source file 
// Date: 21/12/2004
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: addUser.h,v $
 * Revision 1.2  2005/02/16 22:11:21  marceloddm
 * CGI's added
 *
 * Revision 1.1  2004/12/21 23:06:32  marceloddm
 * Initial revision
 *
 */

 
#ifndef _ADD_USER_H_
#define _ADD_USER_H_ "@(#)addUser.h$Revision: 1.2 $"

#include "types.h"

/*---------------------------------------------------------------------------------------------------------*/
unsigned addUser (userDataType *newData);
/* 	
INPUT ARGUMENTS
	- userDataType *newData
	
DESCRIPTION
	The addUser() function adds a new user to the system if there isn't already a user with new user's name and birthday.
	
RETURNED VALUES
	The addUser() function returns:
	- ADD_USER__ERROR_OPENING_USERS_FILE_FOR_READING if there's an error while opening the users file;
	- ADD_USER__ERROR_OPENING_PASSWORD_FILE_FOR_READING if there's an error while opening the password file;
	- ADD_USER__USERS_FILE_DOES_NOT_EXIST if the users file doesn't exist;
	- ADD_USER__PASSWORD_FILE_DOES_NOT_EXIST if the password file doesn't exist;
	- ADD_USER__ERROR_OPENING_USERS_TEMP_FILE_FOR_WRITING if an error occurs while opening the users temporary file;
	- ADD_USER__ERROR_OPENING_PASSWORD_TEMP_FILE_FOR_WRITING if an error occurs while opening the password temporary file;
	- ADD_USER__USER_ALREADY_EXIST if newData contains the exact name and birthday from another user;
	- ADD_USER__ERROR_WRITING_IN_USERS_TEMP_FILE if an error occurs while writing in the users temporary file;
	- ADD_USER__ERROR_WRITING_IN_PASSWORD_TEMP_FILE if an error occurs while writing in the password temporary file;
	- An error code of getLongFilename() function if an error occurs while getting long filename;
	- An error code of putUserData() function if an error occurs while putting user data in a file;
	- An error code of getUserData() function if an error occurs while getting user data from a file;
	- An error code of checkUserData() function if there are invalid fields in the newData;
	- OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

#endif 

/*$RCSfile: addUser.h,v $*/


