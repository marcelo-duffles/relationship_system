//===========================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira
// Description: install() primary function header file 
// Date: 11/12/2004
//===========================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2004/12/15 01:34:01 $
 * $Log: install.h,v $
 * Revision 1.4  2004/12/15 01:34:01  marceloddm
 * The function does not check fields any more
 *
 * Revision 1.3  2004/12/14 02:48:03  marceloddm
 * I think that this file is now complete.
 *
 * Revision 1.2  2004/12/13 07:58:40  marceloddm
 * Not already done
 *
 * Revision 1.1  2004/12/13 07:57:03  marceloddm
 * Initial revision
 *
 */ 
 

#ifndef _INSTALL_H_
#define _INSTALL_H_ "@(#)install.h $Revision: 1.4 $"


/*---------------------------------------------------------------------------------------------------------*/
unsigned install (userDataType *userData);
/* 	
INPUT ARGUMENTS
	- userDataType *userData
	
DESCRIPTION
	The install() function creates the system files: password, users, friends and parents. These two last files are created in blank. The two first files are created with the administrator's data.
	
RETURNED VALUES
	The install() function returns:
	- INSTALL__INVALID_USER_DATA if the 'userData' is invalid;
	- INSTALL__SYSTEM_ALREADY_INSTALLED if the system is already installed;
	- INSTALL__ERROR_READING_PASSWORD_FILE if an error occours while reading password file;
	- INSTALL__ERROR_OPENING_PASSWORD_FILE_FOR_WRITING if an error occours while opening password file for writing;
	- INSTALL__ERROR_READING_USERS_FILE if an error occours while reading users file;
	- INSTALL__ERROR_OPENING_USERS_FILE_FOR_WRITING if an error occours while opening users file for writing;
	- INSTALL__ERROR_READING_PARENTS_FILE if an error occours while reading parents file;
	- INSTALL__ERROR_OPENING_PARENTS_FILE_FOR_WRITING if an error occours while opening parents file for writing;
	- INSTALL__ERROR_READING_FRIENDS_FILE if an error occours while reading friends file;
	- INSTALL__ERROR_OPENING_FRIENDS_FILE_FOR_WRITING if an error occours while opening friends file for writing;
	- An error code of getLongFilename() function if an error occours while getting long filename;
	- An error code of putUserData() function if an error occours while putting user data in an file;
	- OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

#endif

// $RCSfile: install.h,v $
