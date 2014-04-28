//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: getFriendshipInvitation() primary function source file 
// Date: 30/12/2004
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: getFriendshipInvitation.c,v $
 * Revision 1.1  2005/02/16 22:11:21  marceloddm
 * Initial revision
 *
 *
 */

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/errno.h>
#include "const.h"
#include "types.h"
#include "config.h"
#include "error.h"
#include "functions.h"
#include "getFriendshipInvitation.h"
 
static const char rcsid [] = "$Id: getFriendshipInvitation.c,v 1.1 2005/02/16 22:11:21 marceloddm Exp marceloddm $";

unsigned getFriendshipInvitation ( userIdType userId, userDataType ** firstInvitation)
{
  unsigned retCode, retCode2;
  char userInFileName [MAX_LENGTH_LONG_FILENAME +1];
  char tempFileName [MAX_LENGTH_LONG_FILENAME +1];
  FILE *rUserInFile;
  userIdType buffer;
  userDataType * lastInvitation, invitationData, userData;
  
  
  if ((retCode = getDataFromId (userId, &userData)) != OK)
    return (retCode);
  if (userData.category == relative)
    return (GET_FRIENDSHIP_INVITATION__RELATIVES_HAVE_NOT_INVITATIONS);
  
  /*PERFORMING NEEDED OPERATIONS IN THE USER IN FILE*/ 
  
  sprintf ( tempFileName , "%020llu.in" , userId  );
  
  if ((retCode = getLongFilename (DATA_DIR, tempFileName , userInFileName)) != OK)
    return (retCode);

  if ((rUserInFile = fopen (userInFileName, "r")) == NULL)
  {
    if (errno != ENOENT)
      return (GET_FRIENDSHIP_INVITATION__ERROR_OPENING_USER_IN_FILE_FOR_READING);
    return (GET_FRIENDSHIP_INVITATION__USER_IN_FILE_DOES_NOT_EXIST);
  }

  *firstInvitation = NULL;
  lastInvitation   = NULL; 
   
  for (retCode = 0; retCode != GET_USER_ID__END_OF_FILE;)  
  {
    if ((retCode = getUserId ( rUserInFile, &buffer)) != OK )
    {
      if (retCode != GET_USER_ID__END_OF_FILE)
      {
        fclose (rUserInFile);
        freeFIFOResources ( firstInvitation , &lastInvitation );
        return (retCode);
      }
    }
    
    if (retCode != GET_USER_ID__END_OF_FILE) /*INSERTING INVITATION INTO FIFO*/ 
    {  
      invitationData.userId = buffer;
      if ((retCode2 = getDataFromId (invitationData.userId, &invitationData)) != OK)
        return (retCode2);
      if( ( retCode2 = insertFIFO ( firstInvitation, &lastInvitation, &invitationData ) ) != OK )
      {
	fclose ( rUserInFile );
	freeFIFOResources ( firstInvitation , &lastInvitation );
	return ( retCode2);
      }
    }
  }
  
  if (! (* firstInvitation) ) /*NO INVITATIONS FOUND*/
    {
      fclose (rUserInFile);
      return (GET_FRIENDSHIP_INVITATION__NO_INVITATIONS_FOUND);
    }
        
  fclose (rUserInFile);
    
  return (OK);      
}

/*$RCSfile: getFriendshipInvitation.c,v $*/


