//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: editParentRelationship() primary function source file 
// Date: 29/12/2004
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: editParentRelationship.h,v $
 * Revision 1.1  2005/02/16 22:11:21  marceloddm
 * Initial revision
 *
 *
 */


 
#ifndef _EDIT_PARENT_RELATIONSHIP_H_
#define _EDIT_PARENT_RELATIONSHIP_H_ "@(#)editParentRelationship.h $Revision: 1.1 $"

#include "types.h"

/*---------------------------------------------------------------------------------------------------------*/
unsigned editParentRelationship ( userIdType sonOrDaughterId, userIdType fatherOrMotherId, userIdType newSonOrDaughterId, userIdType newFatherOrMotherId);
/* 	
INPUT ARGUMENTS
	- userIdType sonOrDaughterId
	- userIdType fatherOrMotherId
	- userIdType newSonOrDaughterId
	- userIdType newFatherOrMotherId
	
DESCRIPTION
	The editParentRelationship() function does the needed operations to establish a parent relationship between the 'newSonOrDaughterId' and the 'newFatherOrMotherId' and to cancel the parent relationship between the 'sonOrDaughterId' and the 'fatherOrMotherId.
	
RETURNED VALUES
	The addParentRelationship() function returns:
	- EDIT_PARENT_RELATIONSHIP__GIVEN_PARENT_HAS_NO_GENDER_ANSWERED if there's no gender answered by the user with the fatherOrMotherId;
	- EDIT_PARENT_RELATIONSHIP__NO_CHANGES_IN_RELATIONSHIP_REQUIRED if the given pairs of ids are equal;
	- EDIT_PARENT_RELATIONSHIP_OLD_PARENT_AND_NEW_PARENT_HAVE_OTHER_SEX if the son/daughter id is the same and the gender of the given new parent is different than the former one;
	- EDIT_PARENT_RELATIONSHIP__ERROR_OPENING_PARENTS_FILE_FOR_READING if an error occurs while trying to open the parents file for reading;
	- EDIT_PARENT_RELATIONSHIP__PARENTS_FILE_DOES_NOT_EXIST if the parents file doesn't exist;
	- EDIT_PARENT_RELATIONSHIP__ERROR_OPENING_PARENTS_TEMP_FILE_FOR_WRITING if an error occurs while trying to open the parents temporary file for writting;
	- EDIT_PARENT_RELATIONSHIP__GIVEN_OLD_RELATIONSHIP_NOT_FOUND if the given pair of ids to be replaced by the new one was not found;
	- An error code of getDataFromUserId() function if an error occurs while getting data from an userId;
	- An error code of getLongFilename() function if an error occours while getting long filename;
	- An error code of getUserId() function if an error occours while getting an userId from a file;
	- An error code of putUserId() function if an error occours while putting an userId in a file;
	- OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

#endif 

/*$RCSfile: editParentRelationship.h,v $*/


