//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: mountFamilyTree() primary function source file 
// Date: 21/02/2004
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date$
 * $Log$
 *
 */


 
#ifndef _MOUNT_FAMILY_TREE_H_
#define _MOUNT_FAMILY_TREE_H_ "@(#)mountFamilyTree.h $Revision$"

#include "types.h"

/*---------------------------------------------------------------------------------------------------------*/
unsigned mountFamilyTree (userIdType userId, unsigned bottom, unsigned top, familyTreeType **user);
/* 	
INPUT ARGUMENTS
	- userIdType userId
	- unsigned bottom
	- unsigned top
	
OUTPUT ARGUMENTS
	- familyTreeType **user
	
DESCRIPTION
	The mountFamilyTree() function returns tha family tree of the 'user' whose ID is 'userId'.
	
RETURNED VALUES
	The mountFamilyTree() function returns:
	- MOUNT_FAMILY_TREE__NO_USER_FAMILY, if no user family has been given;
	- An error code of getUserFamily() function if an error occurs while getting an user family;
	- OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

#endif 

/*$RCSfile$*/


