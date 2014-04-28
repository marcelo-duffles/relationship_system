//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: addParentRelationship() primary function source file 
// Date: 28/12/2004
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: addParentRelationship.h,v $
 * Revision 1.1  2005/02/16 22:11:21  marceloddm
 * Initial revision
 *
 *
 */
 
#ifndef _ADD_RELATIONSHIP_INVITATION_H_
#define _ADD_RELATIONSHIP_INVITATION_H_ "@(#)addParentRelationship.h $Revision: 1.1 $"

#include "types.h"

/*---------------------------------------------------------------------------------------------------------*/
unsigned addParentRelationship ( userIdType sonOrDaughterId, userIdType fatherOrMotherId);
/* 	
INPUT ARGUMENTS
	- userIdType sonOrDaughterId
	- userIdType fatherOrMotherId
	
DESCRIPTION
	The addParentRelationship() function does the needed operations to establish a parent relationship between the 'sonOrDaughterId' and the 'fatherOrMotherId' .
	
RETURNED VALUES
	The addParentRelationship() function returns:
	- ADD_PARENT_RELATIONSHIP__GIVEN_PARENT_HAS_NO_GENDER_ANSWERED if there's no gender answered by the user with the fatherOrMotherId;
	- ADD_PARENT_RELATIONSHIP__ERROR_OPENING_PARENTS_FILE_FOR_READING if an error occurs while trying to open the parents file for reading;
	- ADD_PARENT_RELATIONSHIP__PARENTS_FILE_DOES_NOT_EXIST if the parents file doesn't exist;
	- ADD_PARENT_RELATIONSHIP__ERROR_OPENING_PARENTS_TEMP_FILE_FOR_WRITING if an error occurs while trying to open the parents temporary file for writting;
	- ADD_PARENT_RELATIONSHIP__USER_ALREADY_HAS_A_FATHER if the given user already has a father;
	- ADD_PARENT_RELATIONSHIP__USER_ALREADY_HAS_A_MOTHER if the given user already has a mother;
	- ADD_PARENT_RELATIONSHIP__GIVEN_PERSON_IS_ALREADY_PARENT_OF_THE_GIVEN_USER if the user with the 'fatherOrMotherId' is already a parent of the user with 'sonOrDaughterId';
	- An error code of getDataFromUserId() function if an error occurs while getting data from an userId;
	- An error code of getLongFilename() function if an error occours while getting long filename;
	- An error code of getUserId() function if an error occours while getting an userId from a file;
	- An error code of putUserId() function if an error occours while putting an userId in a file;
	- OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

#endif 

/*$RCSfile: addParentRelationship.h,v $*/


