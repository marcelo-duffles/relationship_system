//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: inviteUser() primary function source file 
// Date: 30/12/2004
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: inviteUser.h,v $
 * Revision 1.1  2005/02/16 22:11:21  marceloddm
 * Initial revision
 *
 *
 */


 
#ifndef _INVITE_USER_H_
#define _INVITE_USER_H_ "@(#)inviteUser.h $Revision: 1.1 $"

#include "types.h"

/*---------------------------------------------------------------------------------------------------------*/
unsigned inviteUser (userIdType userId, char *name ,char *email);
/* 	
INPUT ARGUMENTS
	- userIdType userId
	- char * name
	- char * email
	
DESCRIPTION
	The inviteUser() function does the needed operations to invite an user to join the system.
	
RETURNED VALUES
	The inviteUser() function returns:
	- INVITE_USER__ERROR_OPENING_INVITED_USER_FILE_FOR_WRITING if an error occurs while trying to open the invited user file for writting; 
	- An error code of getLongFilename() function if an error occurs while getting long filename;
	- An error code of putString() function if an error occurs while putting a string in a file;
	- An error code of checkField() function if an error occurs while checking a field;
	- An error code of createRandomString() function if an error occurs while generating a random password;
	- An error code of encodePassword() function if an error occurs while encoding the temporary password;
	- OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

#endif 

/*$RCSfile: inviteUser.h,v $*/

