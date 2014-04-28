//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: changePassword() primary function source file 
// Date: 24/12/2004
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: changePassword.h,v $
 * Revision 1.1  2005/02/16 22:11:21  marceloddm
 * Initial revision
 *
 *
 */

 
#ifndef _CHANGE_PASSWORD_H_
#define _CHANGE_PASSWORD_H_ "@(#)changePassword.h $Revision: 1.1 $"

#include "types.h"

/*---------------------------------------------------------------------------------------------------------*/
unsigned changePassword ( userIdType userId, char * newPass );
/* 	
INPUT ARGUMENTS
	- userIdType userId
	- char * newPass
	
DESCRIPTION
	The changePassword() function replaces the user`s old password with the new one given.
	
RETURNED VALUES
	The changePassword() function returns:
	- CHANGE_PASSWORD__ERROR_OPENING_PASSWORD_FILE_FOR_READING if there's an error while opening the password file;
	- CHANGE_PASSWORD__PASSWORD_FILE_DOES_NOT_EXIST if the password file doesn't exist;
	- CHANGE_PASSWORD__ERROR_OPENING_PASSWORD_TEMP_FILE_FOR_WRITTING if an error occours while opening a temporary file;
	- CHANGE_PASSWORD__USER_NOT_FOUND if no user with the given id is found in the password file;
	- An error code of getLongFilename() function if an error occours while getting long filename;
	- An error code of putUserData() function if an error occours while putting user data in a file;
	- An error code of getUserData() function if an error occours while getting user data from a file;
	- An error code of checkField() fuction if there's an error in the given newPass.
	- OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

#endif

// $RCSfile: changePassword.h,v $


