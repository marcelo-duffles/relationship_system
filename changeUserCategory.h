//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: changeUserCategory() primary function source file 
// Date: 28/12/2004
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: changeUserCategory.h,v $
 * Revision 1.1  2005/02/16 22:11:21  marceloddm
 * Initial revision
 *
 *
 */
 
#ifndef _CHANGE_USER_CATEGORY_H_
#define _CHANGE_USER_CATEGORY_H_ "@(#)changeUserCategory.h $Revision: 1.1 $"

#include "types.h"

/*---------------------------------------------------------------------------------------------------------*/
unsigned changeUserCategory ( userDataType * userData);
/* 	
INPUT ARGUMENTS
	- userDataType * userData;
	
DESCRIPTION
	The changeUserCategory() function does the needed operations to change a user category. 
	
RETURNED VALUES
	The changeUserCategory() function returns:
	- CHANGE_USER_CATEGORY__ERROR_OPENING_PASSWORD_FILE_FOR_READING if an error occurs while trying to open the users file for reading;
	- CHANGE_USER_CATEGORY__PASSWORD_FILE_DOES_NOT_EXIST if the users file doesn't exist;
	- CHANGE_USER_CATEGORY__ERROR_OPENING_TEMP_FILE_FOR_WRITING if an error occurs while trying to open the password temporary file for writting;
	- An error code of editUserData() function if an error occurs while editing user data;
	- An error code of getLongFilename() function if an error occurs while getting long filename;
	- An error code of getUserData() function if an error occurs while getting user data from a file;
	- An error code of putUserData() function if an error occurs while putting user data in a file;
	- An error code of encodePassword() function if an error occurs while encypting a password;
	- OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

#endif 

/*$RCSfile: changeUserCategory.h,v $*/


