//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: removeParentRelationship() primary function source file 
// Date: 28/12/2004
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: removeParentRelationship.h,v $
 * Revision 1.1  2005/02/16 22:11:21  marceloddm
 * Initial revision
 *
 *
 */


  
#ifndef _REMOVE_RELATIONSHIP_INVITATION_H_
#define _REMOVE_RELATIONSHIP_INVITATION_H_ "@(#)removeParentRelationship.h $Revision: 1.1 $"

#include "types.h"

/*---------------------------------------------------------------------------------------------------------*/
unsigned removeParentRelationship ( userIdType sonOrDaughterId, userIdType fatherOrMotherId);
/* 	
INPUT ARGUMENTS
	- userIdType sonOrDaughterId
	- userIdType fatherOrMotherId
	
DESCRIPTION
	The removeParentRelationship() function does the needed operations remove a parent relationship between the 'sonOrDaughterId' and the 'fatherOrMotherId' .
	
RETURNED VALUES
	The removeParentRelationship() function returns:
	- REMOVE_PARENT_RELATIONSHIP__ERROR_OPENING_PARENTS_FILE_FOR_READING if an error occurs while trying to open the parents file for reading;
	- REMOVE_PARENT_RELATIONSHIP__PARENTS_FILE_DOES_NOT_EXIST if the parents file doesn't exist;
	- REMOVE_PARENT_RELATIONSHIP__ERROR_OPENING_PARENTS_TEMP_FILE_FOR_WRITING if an error occurs while trying to open the parents temporary file for writting;
	- REMOVE_PARENT_RELATIONSHIP__GIVEN_PARENT_RELATIONSHIP_NOT_FOUND if the user with the 'fatherOrMotherId' is not parent of the user with 'sonOrDaughterId';
	- An error code of getDataFromUserId() function if an error occurs while getting data from an userId;
	- An error code of getLongFilename() function if an error occours while getting long filename;
	- An error code of getUserId() function if an error occours while getting an userId from a file;
	- An error code of putUserId() function if an error occours while putting an userId in a file;
	- OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

#endif 

/*$RCSfile: removeParentRelationship.h,v $*/


