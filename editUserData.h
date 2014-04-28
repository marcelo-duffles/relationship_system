//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: editUserData() primary function source file 
// Date: 15/12/2004
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: editUserData.h,v $
 * Revision 1.4  2005/02/16 22:11:21  marceloddm
 * CGI's added
 *
 * Revision 1.3  2004/12/20 12:37:53  marceloddm
 * comments have been added
 *
 * Revision 1.2  2004/12/17 12:09:48  marceloddm
 * Coments regarding to the return codes and a function description added.
 *
 * Revision 1.1  2004/12/16 00:12:42  marceloddm
 * Initial revision
 *
 */

 
#ifndef _EDIT_USER_DATA_H_
#define _EDIT_USER_DATA_H_ "@(#)editUserData.h $Revision: 1.4 $"

#include "types.h"

/*---------------------------------------------------------------------------------------------------------*/
unsigned editUserData ( userDataType * newData );
/* 	
INPUT ARGUMENTS
	- userDataType *newData
	
DESCRIPTION
	The editUserData() function edits the users file of the system, replacing the requested user data with the new one given if there are no problems.
	
RETURNED VALUES
	The editUserData() function returns:
	- EDIT_USER_DATA__ERROR_OPENING_USERS_FILE_FOR_READING if there's an error while opening the users file;
	- EDIT_USER_DATA__USERS_FILE_DOES_NOT_EXIST if the users file doesn't exist;
	- EDIT_USER_DATA__ERROR_OPENING_TEMP_FILE_FOR_WRITING if an error occours while opening a temporary file;
	- EDIT_USER_DATA__NAME_AND_BIRTHDAY_ALREADY_EXIST if newData contains the exact name and birthday from another user;
	- EDIT_USER_DATA__ERROR_WRITING_IN_TEMP_FILE if an error occurs while writing in the temporary file;
	- EDIT_USER_DATA__USER_NOT_FOUND if there's no user with the ID from newData;
	- An error code of getLongFilename() function if an error occours while getting long filename;
	- An error code of putUserData() function if an error occours while putting user data in a file;
	- An error code of getUserData() function if an error occours while getting user data from a file;
	- An error code of checkUserData() function if there are invalid fields in the newData;
	- OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

#endif /*_EDIT_USER_DATA_*/

/*$RCSfile: editUserData.h,v $*/


