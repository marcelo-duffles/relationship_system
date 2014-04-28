//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: Source file of the primary function inviteFriend().
// Date: 15/12/2004
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: inviteFriend.c,v $
 * Revision 1.2  2005/02/16 22:11:21  marceloddm
 * CGI's added
 *
 * Revision 1.1  2004/12/25 17:27:32  marceloddm
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
  
static const char rcsid [] = "$Id: inviteFriend.c,v 1.2 2005/02/16 22:11:21 marceloddm Exp marceloddm $";
  
unsigned inviteFriend ( userIdType invitingFriendId, userIdType invitedFriendId)
{
  unsigned retCode, retCode2;
  char invitedFriendInFileName [MAX_LENGTH_LONG_FILENAME +1];
  char invitedFriendOutFileName [MAX_LENGTH_LONG_FILENAME +1];
  char invitedFriendInFileNameTmp [MAX_LENGTH_LONG_FILENAME +1];
  char invitingFriendOutFileName [MAX_LENGTH_LONG_FILENAME +1];
  char invitingFriendInFileName [MAX_LENGTH_LONG_FILENAME +1];
  char invitingFriendOutFileNameTmp [MAX_LENGTH_LONG_FILENAME +1];
  char friendsFileName [MAX_LENGTH_LONG_FILENAME +1];
  char tempFileName[MAX_LENGTH_LONG_FILENAME +1];
  char emailBody[500 +1];
  FILE *rInvitedInFile, *rInvitedOutFile, *wInvitedInFile, *rInvitingOutFile, *rInvitingInFile, *wInvitingOutFile, *rFriendsFile;
  userIdType buffer, bufferTwo, smallerId, biggerId;
  userDataType invitedFriendData, invitingFriendData;
  boolean found, notFound;
  
  if ( invitingFriendId == invitedFriendId )
    return ( INVITE_FRIEND__CANNOT_INVITE_THE_OWN_USER );

  if ((retCode = getDataFromId (invitingFriendId, &invitingFriendData)) != OK)
    return (retCode);
  if (invitingFriendData.category == relative)
    return (INVITE_FRIEND__RELATIVES_CAN_NOT_INVITE_FRIENDS);
    
  if ((retCode = getDataFromId (invitedFriendId, &invitedFriendData)) != OK)
    return (retCode);
  if (invitedFriendData.category == relative)
    return (INVITE_FRIEND__RELATIVES_CAN_NOT_BE_INVITED);   
    
  /*CHECKING IF THEY ARE ALREADY FRIENDS*/
    
  if ( invitedFriendId > invitingFriendId )
  { 
    smallerId = invitingFriendId;
    biggerId = invitedFriendId;
  }
  else
  {
    smallerId = invitedFriendId;
    biggerId = invitingFriendId;
  }
  
  if ((retCode = getLongFilename (DATA_DIR, FRIENDS_FILE_NAME , friendsFileName)) != OK)
    return (retCode);

  if ((rFriendsFile = fopen (friendsFileName, "r")) == NULL)
  {
    if (errno != ENOENT)
      return (INVITE_FRIEND__ERROR_OPENING_FRIENDS_FILE_FOR_READING);
    return (INVITE_FRIEND__FRIENDS_FILE_DOES_NOT_EXIST);
  }

  notFound = false;
     
  for (retCode = 0; ((retCode != GET_USER_ID__END_OF_FILE) && (!notFound));)  
  {
    if ((retCode = getUserId ( rFriendsFile, &buffer)) != OK )
    {
      if (retCode != GET_USER_ID__END_OF_FILE)
      {
        fclose (rFriendsFile);
        return (retCode);
      }
    }
    if ((retCode = getUserId ( rFriendsFile, &bufferTwo)) != OK )
    {
      if (retCode != GET_USER_ID__END_OF_FILE)
      {
        fclose (rFriendsFile);
        return (retCode);
      }
    }    
    if (retCode != GET_USER_ID__END_OF_FILE) /*SEARCH FOR THE POSITION WHERE THE FRIENDSHIP COULD BE*/
    {  
      if ( buffer > smallerId ) 
        notFound = true;
      
      if ( buffer == smallerId )
	if ( bufferTwo == biggerId ) /*FRIENDSHIP ALREADY EXISTS*/
	{
	  fclose (rFriendsFile);
	  return (INVITE_FRIEND__FRIENDSHIP_ALREADY_EXISTS);
	}
    }            
  }
  
  /*CHECKING IF THERE'S ALREADY AN INVITATION FROM THE INVITED FRIEND TO THE INVITING FRIEND*/
  
  /*CHECKING IN THE INVITED FRIEND OUT FILE*/
  
  sprintf ( tempFileName , "%020llu.out" , invitedFriendId  );
  if ((retCode = getLongFilename (DATA_DIR, tempFileName , invitedFriendOutFileName)) != OK)
    return (retCode);

  if ((rInvitedOutFile = fopen (invitedFriendOutFileName, "r")) == NULL)
  {
    if (errno != ENOENT)
      return (INVITE_FRIEND__ERROR_OPENING_INVITED_FRIEND_OUT_FILE_FOR_READING);
    return (INVITE_FRIEND__INVITED_FRIEND_OUT_FILE_DOES_NOT_EXIST);
  }
     
  for (retCode = 0; retCode != GET_USER_ID__END_OF_FILE;)  
  {
    if ((retCode = getUserId ( rInvitedOutFile, &buffer)) != OK )
    {
      if (retCode != GET_USER_ID__END_OF_FILE)
      {
        fclose (rInvitedOutFile);
        return (retCode);
      }
    }
    if (retCode != GET_USER_ID__END_OF_FILE)    
    {
      if ( buffer == invitingFriendId ) /* INVITATION FOUND */
      {
        fclose ( rInvitedOutFile );
        return ( INVITE_FRIEND__THERE_IS_ALREADY_AN_INVITATION_TO_THE_INVITING_FRIEND_IN_THE_INVITED_FRIEND_OUT_FILE );
      } 
    }
  }     
  
  fclose ( rInvitedOutFile );
  
  /* CHECKING IN THE INVITING FRIEND IN FILE */
  
    sprintf ( tempFileName , "%020llu.in" , invitingFriendId  );
  if ((retCode = getLongFilename (DATA_DIR, tempFileName , invitingFriendInFileName)) != OK)
    return (retCode);

  if ((rInvitingInFile = fopen (invitingFriendInFileName, "r")) == NULL)
  {
    if (errno != ENOENT)
      return (INVITE_FRIEND__ERROR_OPENING_INVITING_FRIEND_IN_FILE_FOR_READING);
    return (INVITE_FRIEND__INVITING_FRIEND_IN_FILE_DOES_NOT_EXIST);
  }
     
  for (retCode = 0; retCode != GET_USER_ID__END_OF_FILE;)  
  {
    if ((retCode = getUserId ( rInvitingInFile, &buffer)) != OK )
    {
      if (retCode != GET_USER_ID__END_OF_FILE)
      {
        fclose (rInvitingInFile);
        return (retCode);
      }
    }

    if (retCode != GET_USER_ID__END_OF_FILE)
    {
      if ( buffer == invitedFriendId ) /* INVITATION FOUND */
      {
        fclose ( rInvitingInFile );
        return ( INVITE_FRIEND__THERE_IS_ALREADY_AN_INVITATION_FROM_THE_INVITED_FRIEND_IN_THE_INVITING_FRIEND_IN_FILE );
      } 
    }
  }     
  
  fclose ( rInvitingInFile );
    
  /*PERFORMING NEEDED OPERATIONS IN THE INVITED FRIEND IN FILE*/
  
  sprintf ( tempFileName , "%020llu.in" , invitedFriendId  );
  if ((retCode = getLongFilename (DATA_DIR, tempFileName , invitedFriendInFileName)) != OK)
    return (retCode);

  if ((rInvitedInFile = fopen (invitedFriendInFileName, "r")) == NULL)
  {
    if (errno != ENOENT)
      return (INVITE_FRIEND__ERROR_OPENING_INVITED_FRIEND_IN_FILE_FOR_READING);
    return (INVITE_FRIEND__INVITED_FRIEND_IN_FILE_DOES_NOT_EXIST);
  }

  sprintf ( tempFileName , "%020llu.in.tmp" , invitedFriendId );
  if ((retCode = getLongFilename (DATA_DIR, tempFileName , invitedFriendInFileNameTmp)) != OK)
    return (retCode);

  if ((wInvitedInFile = fopen (invitedFriendInFileNameTmp , "w")) == NULL)
  {
    fclose ( rInvitedInFile );
    return (INVITE_FRIEND__ERROR_OPENING_INVITED_FRIEND_IN_TEMP_FILE_FOR_WRITTING);
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
      if ( buffer < invitingFriendId)
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
      {
        fclose (rInvitedInFile);
        fclose (wInvitedInFile);
        remove (invitedFriendInFileNameTmp);
	return (INVITE_FRIEND__THERE_IS_ALREADY_AN_INVITATION_IN_THE_INVITED_FRIEND_IN_FILE);       
      } 
      if ( buffer > invitingFriendId )
      {
        if ( ! found )
	{
          if ((retCode2 = putUserId (wInvitedInFile, &invitingFriendId)) != OK )
          {
            fclose (rInvitedInFile);
            fclose (wInvitedInFile);
            remove (invitedFriendInFileNameTmp);
	    return (retCode2);
          }
	  
	  found = true;
	  
	}  
	if ((retCode2 = putUserId (wInvitedInFile, &buffer)) != OK )
        {
          fclose (rInvitedInFile);
          fclose (wInvitedInFile);
          remove (invitedFriendInFileNameTmp);
	  return (retCode2);
        }       
      }  
    }            
  }
    
  if ( !found )  /*IT`S THE LAST ONE*/
    if ((retCode2 = putUserId (wInvitedInFile, &invitingFriendId)) != OK )
    {
      fclose (rInvitedInFile);
      fclose (wInvitedInFile);
      remove (invitedFriendInFileNameTmp);
      return (retCode2);
    }  
    
  fclose (rInvitedInFile);
  fclose (wInvitedInFile);
      
  /*PERFORMING NEEDED OPERATIONS IN THE INVITING FRIEND OUT FILE*/
  
  sprintf ( tempFileName , "%020llu.out" , invitingFriendId  );
  if ((retCode = getLongFilename (DATA_DIR, tempFileName , invitingFriendOutFileName)) != OK)
    return (retCode);

  if ((rInvitingOutFile = fopen (invitingFriendOutFileName, "r")) == NULL)
  {
    if (errno != ENOENT)
      return (INVITE_FRIEND__ERROR_OPENING_INVITING_FRIEND_OUT_FILE_FOR_READING);
    return (INVITE_FRIEND__INVITING_FRIEND_OUT_FILE_DOES_NOT_EXIST);
  }

  sprintf ( tempFileName , "%020llu.out.tmp" , invitingFriendId );
  if ((retCode = getLongFilename (DATA_DIR, tempFileName , invitingFriendOutFileNameTmp)) != OK)
    return (retCode);

  if ((wInvitingOutFile = fopen (invitingFriendOutFileNameTmp , "w")) == NULL)
  {
    fclose ( rInvitingOutFile );
    return (INVITE_FRIEND__ERROR_OPENING_INVITING_FRIEND_OUT_TEMP_FILE_FOR_WRITTING);
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
      if ( buffer < invitedFriendId)
      {
        if ((retCode2 = putUserId (wInvitingOutFile, &buffer)) != OK )
        {
          fclose (rInvitingOutFile);
          fclose (wInvitingOutFile);
          remove (invitingFriendOutFileNameTmp);
	  return (retCode2);
        }     
      }
      if ( buffer == invitedFriendId)
      {
        fclose (rInvitingOutFile);
        fclose (wInvitingOutFile);
        remove (invitingFriendOutFileNameTmp);
	return (INVITE_FRIEND__THERE_IS_ALREADY_AN_INVITATION_IN_THE_INVITING_FRIEND_OUT_FILE);       
      } 
      if ( buffer > invitedFriendId )
      {
        if ( ! found )
	{
          if ((retCode2 = putUserId (wInvitingOutFile, &invitedFriendId)) != OK )
          {
            fclose (rInvitingOutFile);
            fclose (wInvitingOutFile);
            remove (invitingFriendOutFileNameTmp);
	    return (retCode2);
          }
	  
	  found = true;
	  
	}
	if ((retCode2 = putUserId (wInvitingOutFile, &buffer)) != OK )
        {
          fclose (rInvitingOutFile);
          fclose (wInvitingOutFile);
          remove (invitingFriendOutFileNameTmp);
	  return (retCode2);
        }       
      }
    }            
  }
    
  if ( !found )  /*IT`S THE LAST ONE*/
    if ((retCode2 = putUserId (wInvitedInFile, &invitedFriendId)) != OK )
    {
      fclose (rInvitingOutFile);
      fclose (wInvitingOutFile);
      remove (invitingFriendOutFileNameTmp);
      return (retCode2);
    }  
    
  fclose (rInvitingOutFile);
  fclose (wInvitingOutFile);
  
  
    
  /*RENAMEING THE TEMP FILE NAMES TO REPLACE DE OLD ONES*/

  rename (invitingFriendOutFileNameTmp, invitingFriendOutFileName);
  rename (invitedFriendInFileNameTmp, invitedFriendInFileName);  
  
  #ifdef ENGLISH
    snprintf (emailBody, 500, "\n\
      *** This is a system message, you don't need to reply! ***\n\
      \n\
      Dear %s,\n\
      \n\
        Your friendship invitation has been sent to %s.\n\
      \n\
      \n\
      Our web site: http://www.del.ufrj.br/~marceloddm/computacao_ii/pf", invitingFriendData.name, invitedFriendData.name);
  #elif PORTUGUESE
    snprintf (emailBody, 500, "\n\
      *** Essa é uma mensagem de sistema, você não precisa respondê-la! ***\n\
      \n\
      Caro(a) %s,\n\
      \n\
        Seu convite de amizade foi enviado para %s.\n\
      \n\
      \n\
      Nosso web site: http://www.del.ufrj.br/~marceloddm/computacao_ii/pf", invitingFriendData.name, invitedFriendData.name);  
  #endif
      
  if (sendMail (WEB_SERVER_DOMAIN, SMTP_SERVER_ADDRESS, SMTP_SERVER_PORT, ADMINISTRATOR_EMAIL, invitingFriendData.email, NULL, NULL, showTextHelpMessage (INVITE_FRIEND__SUBJECT), emailBody, NULL) != OK)
    return (ERROR_SENDING_EMAIL);

  return (OK);
}


