//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: recoveryPassword() primary function source file 
// Date: 24/12/2004
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2004/12/25 17:47:44 $
 * $Log: recoveryPassword.h,v $
 * Revision 1.1  2004/12/25 17:47:44  marceloddm
 * Initial revision
 *
 */

 
#ifndef _RECOVERY_PASSWORD_H_
#define _RECOVERY_PASSWORD_H_ "@(#)recoveryPassword.h $Revision: 1.1 $"

#include "types.h"

/*---------------------------------------------------------------------------------------------------------*/
unsigned recoveryPassword ( userIdType userId );
/* 	
INPUT ARGUMENTS
		- userIdType userId
	
DESCRIPTION
	The recoveryPassword() function replaces the user`s old password with a new 8-characters randomic password and sends an e-mail to the user informing what`s his new password.
	
RETURNED VALUES
	The recoveryPassword() function returns:
	- RECOVERY_PASSWORD__ERROR_OPENING_PASSWORD_FILE_FOR_READING if there's an error while opening the password file;
	- RECOVERY_PASSWORD__PASSWORD_FILE_DOES_NOT_EXIST if the password file doesn't exist;
	- RECOVERY_PASSWORD__ERROR_OPENING_PASSWORD_TEMP_FILE_FOR_WRITTING if an error occours while opening a temporary file;
	- RECOVERY_PASSWORD__USER_NOT_FOUND if no user with the given id is found in the password file;
	- An error code of getLongFilename() function if an error occours while getting long filename;
	- An error code of putUserData() function if an error occours while putting user data in a file;
	- An error code of getUserData() function if an error occours while getting user data from a file;
	- OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

#endif

// $RCSfile: recoveryPassword.h,v $


