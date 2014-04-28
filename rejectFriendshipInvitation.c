//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: rejectFriendshipInvitation() primary function source file. 
// Date: 22/12/2004
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: rejectFriendshipInvitation.c,v $
 * Revision 1.2  2005/02/16 22:11:21  marceloddm
 * CGI's added
 *
 * Revision 1.1  2004/12/25 17:28:55  marceloddm
 * Initial revision
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
#include "help.h"
#include "functions.h"
#include "sendmail.h"
 
static const char rcsid [] = "$Id: rejectFriendshipInvitation.c,v 1.2 2005/02/16 22:11:21 marceloddm Exp marceloddm $";
  
unsigned rejectFriendshipInvitation ( userIdType invitedFriendId, userIdType invitingFriendId)
{
  unsigned retCode, retCode2;
  char invitedFriendInFileName [MAX_LENGTH_LONG_FILENAME +1];
  char invitedFriendInFileNameTmp [MAX_LENGTH_LONG_FILENAME +1];
  char invitingFriendOutFileName [MAX_LENGTH_LONG_FILENAME +1];
  char invitingFriendOutFileNameTmp [MAX_LENGTH_LONG_FILENAME +1];
  char tempFileName[MAX_LENGTH_LONG_FILENAME +1];
  char emailBody[500 +1];
  FILE *rInvitedInFile, *wInvitedInFile, *rInvitingOutFile, *wInvitingOutFile;
  userIdType buffer;
  userDataType invitedFriendData, invitingFriendData;
  boolean found;
  
  if ((retCode = getDataFromId (invitedFriendId, &invitedFriendData)) != OK)
    return (retCode);
  if ((retCode = getDataFromId (invitingFriendId, &invitingFriendData)) != OK)
    return (retCode);
  
  /*PERFORMING NEEDED OPERATIONS IN THE INVITED FRIEND IN FILE*/
  
  sprintf ( tempFileName , "%020llu.in" , invitedFriendId  );
  if ((retCode = getLongFilename (DATA_DIR, tempFileName , invitedFriendInFileName)) != OK)
    return (retCode);

  if ((rInvitedInFile = fopen (invitedFriendInFileName, "r")) == NULL)
  {
    if (errno != ENOENT)
      return (REJECT_FRIENDSHIP_INVITATION__ERROR_OPENING_INVITED_FRIEND_IN_FILE_FOR_READING);
    return (REJECT_FRIENDSHIP_INVITATION__INVITED_FRIEND_IN_FILE_DOES_NOT_EXIST);
  }

  sprintf ( tempFileName , "%020llu.in.tmp" , invitedFriendId );
  if ((retCode = getLongFilename (DATA_DIR, tempFileName , invitedFriendInFileNameTmp)) != OK)
    return (retCode);

  if ((wInvitedInFile = fopen (invitedFriendInFileNameTmp , "w")) == NULL)
  {
    fclose ( rInvitedInFile );
    return (REJECT_FRIENDSHIP_INVITATION__ERROR_OPENING_INVITED_FRIEND_IN_TEMP_FILE_FOR_WRITTING);
  }
  
  found = false;
  
  for (retCode = 0; retCode != GET_USER_ID__END_OF_FILE;)  
  {
    if ((retCode = getUserId ( rInvitedInFile, &buffer)) != OK )
    {
      if (retCode != GET_USER_ID__END_OF_FILE)
      {
        fclose (rInvitedInFile);
        fclose (wInvitedInFile);
        remove (invitedFriendInFileNameTmp);
        return (retCode);
      }
    }
        
    if (retCode != GET_USER_ID__END_OF_FILE)
    {
      if ( buffer != invitingFriendId)
      {
        if ((retCode2 = putUserId (wInvitedInFile, &buffer)) != OK )
        {
          fclose (rInvitedInFile);
          fclose (wInvitedInFile);
          remove (invitedFriendInFileNameTmp);
	  return (retCode2);
        }     
      }
      if ( buffer == invitingFriendId)
        found = true; 
    }            
  }
    
  fclose (rInvitedInFile);
  fclose (wInvitedInFile);
   
  if (! found )
  {
    remove (invitedFriendInFileNameTmp);
    return (REJECT_FRIENDSHIP_INVITATION__INVITED_FRIEND_IN_FILE_DOES_NOT_HAVE_INVITATION_FROM_GIVEN_INVITING_FRIEND);   
  }  
  
  /*PERFORMING NEEDED OPERATIONS IN THE INVITING FRIEND OUT FILE*/
  
  sprintf ( tempFileName , "%020llu.out" , invitingFriendId  );
  if ((retCode = getLongFilename (DATA_DIR, tempFileName , invitingFriendOutFileName)) != OK)
    return (retCode);

  if ((rInvitingOutFile = fopen (invitingFriendOutFileName, "r")) == NULL)
  {
    if (errno != ENOENT)
      return (REJECT_FRIENDSHIP_INVITATION__ERROR_OPENING_INVITING_FRIEND_OUT_FILE_FOR_READING);
    return (REJECT_FRIENDSHIP_INVITATION__INVITING_FRIEND_OUT_FILE_DOES_NOT_EXIST);
  }

  sprintf ( tempFileName , "%020llu.out.tmp" , invitingFriendId );
  if ((retCode = getLongFilename (DATA_DIR, tempFileName , invitingFriendOutFileNameTmp)) != OK)
    return (retCode);

  if ((wInvitingOutFile = fopen (invitingFriendOutFileNameTmp , "w")) == NULL)
  {
    fclose ( rInvitingOutFile );
    return (REJECT_FRIENDSHIP_INVITATION__ERROR_OPENING_INVITING_FRIEND_OUT_TEMP_FILE_FOR_WRITTING);
  }
  
  found = false;
      
  for (retCode = 0; retCode != GET_USER_ID__END_OF_FILE;)  
  {
    if ((retCode = getUserId ( rInvitingOutFile, &buffer)) != OK )
    {
      if (retCode != GET_USER_ID__END_OF_FILE)
      {
        fclose (rInvitingOutFile);
        fclose (wInvitingOutFile);
        remove (invitingFriendOutFileNameTmp);
        return (retCode);
      }
    }
    if (retCode != GET_USER_ID__END_OF_FILE)
    {  
      if ( buffer != invitedFriendId)
      {
        if ((retCode2 = putUserId (wInvitingOutFile, &buffer)) != OK )
        {
          fclose (rInvitedInFile);
          fclose (wInvitedInFile);
          remove (invitingFriendOutFileNameTmp);
	  return (retCode2);
        }     
      }
      if ( buffer == invitedFriendId)
        found = true; 
    }            
  }
  
  fclose (rInvitingOutFile);
  fclose (wInvitingOutFile);
   
  if (! found )
  {
    remove (invitingFriendOutFileNameTmp);
    return (REJECT_FRIENDSHIP_INVITATION__INVITING_FRIEND_OUT_FILE_DOES_NOT_HAVE_INVITATION_TO_GIVEN_INVITED_FRIEND);   
  }  
    
  /*RENAMEING THE TEMP FILE NAMES TO REPLACE DE OLD ONES*/
  rename (invitingFriendOutFileNameTmp, invitingFriendOutFileName);
  rename (invitedFriendInFileNameTmp, invitedFriendInFileName);  
  
  #ifdef ENGLISH
    snprintf (emailBody, 500, "\n\
      *** This is a system message, you don't need to reply! ***\n\
      \n\
      Dear %s,\n\
      \n\
        Your friendship invitation has been rejected by %s.\n\
      \n\
      \n\
      Our web site: http://www.del.ufrj.br/~marceloddm/computacao_ii/pf", invitingFriendData.name, invitedFriendData.name);
  #elif PORTUGUESE
    snprintf (emailBody, 500, "\n\
      *** Essa é uma mensagem de sistema, você não precisa respondê-la! ***\n\
      \n\
      Caro(a) %s,\n\
      \n\
        Seu convite de amizade foi rejeitado por %s.\n\
      \n\
      \n\
      Nosso web site: http://www.del.ufrj.br/~marceloddm/computacao_ii/pf", invitingFriendData.name, invitedFriendData.name);  
  #endif
      
  if (sendMail (WEB_SERVER_DOMAIN, SMTP_SERVER_ADDRESS, SMTP_SERVER_PORT, ADMINISTRATOR_EMAIL, invitingFriendData.email, NULL, NULL, showTextHelpMessage (REJECT_FRIENDSHIP_INVITATION__SUBJECT), emailBody, NULL) != OK)
    return (ERROR_SENDING_EMAIL);
    
  
  return (OK);      
}

/*$RCSfile: rejectFriendshipInvitation.c,v $*/

