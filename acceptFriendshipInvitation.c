//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: Source file of the primary function acceptFriendshipInvitation().
// Date: 15/12/2004
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: acceptFriendshipInvitation.c,v $
 * Revision 1.2  2005/02/16 22:11:21  marceloddm
 * CGI's added
 *
 * Revision 1.1  2004/12/20 20:01:06  marceloddm
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
  
static const char rcsid [] = "$Id: acceptFriendshipInvitation.c,v 1.2 2005/02/16 22:11:21 marceloddm Exp marceloddm $";
  
unsigned acceptFriendshipInvitation ( userIdType invitedFriendId, userIdType invitingFriendId)
{
  unsigned retCode, retCode2;
  char invitedFriendInFileName [MAX_LENGTH_LONG_FILENAME +1];
  char invitedFriendInFileNameTmp [MAX_LENGTH_LONG_FILENAME +1];
  char invitingFriendOutFileName [MAX_LENGTH_LONG_FILENAME +1];
  char invitingFriendOutFileNameTmp [MAX_LENGTH_LONG_FILENAME +1];
  char friendsFileName [MAX_LENGTH_LONG_FILENAME +1];
  char friendsFileNameTmp [MAX_LENGTH_LONG_FILENAME +1];
  char tempFileName[MAX_LENGTH_LONG_FILENAME +1];
  char emailBody[500 +1];
  FILE *rInvitedInFile, *wInvitedInFile, *rInvitingOutFile, *wInvitingOutFile, *rFriendsFile, *wFriendsFile;
  userIdType buffer, bufferTwo, smallerId, biggerId;
  userDataType invitingFriendData, invitedFriendData;
  boolean found;
  
  if ((retCode = getDataFromId (invitingFriendId, &invitingFriendData)) != OK)
    return (retCode);
  if ((retCode = getDataFromId (invitedFriendId, &invitedFriendData)) != OK)
    return (retCode);

        
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
  
  /*PERFORMING NEEDED OPERATIONS IN THE INVITED FRIEND IN FILE*/
  
  sprintf ( tempFileName , "%020llu.in" , invitedFriendId  );
  if ((retCode = getLongFilename (DATA_DIR, tempFileName , invitedFriendInFileName)) != OK)
    return (retCode);

  if ((rInvitedInFile = fopen (invitedFriendInFileName, "r")) == NULL)
  {
    if (errno != ENOENT)
      return (ACCEPT_FRIENDSHIP_INVITATION__ERROR_OPENING_INVITED_FRIEND_IN_FILE_FOR_READING);
    return (ACCEPT_FRIENDSHIP_INVITATION__INVITED_FRIEND_IN_FILE_DOES_NOT_EXIST);
  }

  sprintf ( tempFileName , "%020llu.in.tmp" , invitedFriendId );
  if ((retCode = getLongFilename (DATA_DIR, tempFileName , invitedFriendInFileNameTmp)) != OK)
    return (retCode);

  if ((wInvitedInFile = fopen (invitedFriendInFileNameTmp , "w")) == NULL)
  {
    fclose ( rInvitedInFile );
    return (ACCEPT_FRIENDSHIP_INVITATION__ERROR_OPENING_INVITED_FRIEND_IN_TEMP_FILE_FOR_WRITTING);
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
    return (ACCEPT_FRIENDSHIP_INVITATION__INVITED_FRIEND_IN_FILE_DOES_NOT_HAVE_INVITATION_FROM_GIVEN_INVITING_FRIEND);   
  }  
  
  /*PERFORMING NEEDED OPERATIONS IN THE INVITING FRIEND OUT FILE*/
  
  sprintf ( tempFileName , "%020llu.out" , invitingFriendId  );
  if ((retCode = getLongFilename (DATA_DIR, tempFileName , invitingFriendOutFileName)) != OK)
    return (retCode);

  if ((rInvitingOutFile = fopen (invitingFriendOutFileName, "r")) == NULL)
  {
    if (errno != ENOENT)
      return (ACCEPT_FRIENDSHIP_INVITATION__ERROR_OPENING_INVITING_FRIEND_OUT_FILE_FOR_READING);
    return (ACCEPT_FRIENDSHIP_INVITATION__INVITING_FRIEND_OUT_FILE_DOES_NOT_EXIST);
  }

  sprintf ( tempFileName , "%020llu.out.tmp" , invitingFriendId );
  if ((retCode = getLongFilename (DATA_DIR, tempFileName , invitingFriendOutFileNameTmp)) != OK)
    return (retCode);

  if ((wInvitingOutFile = fopen (invitingFriendOutFileNameTmp , "w")) == NULL)
  {
    fclose ( rInvitingOutFile );
    return (ACCEPT_FRIENDSHIP_INVITATION__ERROR_OPENING_INVITING_FRIEND_OUT_TEMP_FILE_FOR_WRITTING);
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
    return (ACCEPT_FRIENDSHIP_INVITATION__INVITING_FRIEND_OUT_FILE_DOES_NOT_HAVE_INVITATION_TO_GIVEN_INVITED_FRIEND);   
  }
  
  /*PERFORMING NEEDED OPERATIONS IN THE FRIENDS FILE*/ 
  
  if ((retCode = getLongFilename (DATA_DIR, FRIENDS_FILE_NAME , friendsFileName)) != OK)
    return (retCode);

  if ((rFriendsFile = fopen (friendsFileName, "r")) == NULL)
  {
    if (errno != ENOENT)
      return (ACCEPT_FRIENDSHIP_INVITATION__ERROR_OPENING_FRIENDS_FILE_FOR_READING);
    return (ACCEPT_FRIENDSHIP_INVITATION__FRIENDS_FILE_DOES_NOT_EXIST);
  }

  if ((retCode = getLongFilename (DATA_DIR, FRIENDS_TEMP_FILE_NAME , friendsFileNameTmp)) != OK)
    return (retCode);

  if ((wFriendsFile = fopen (friendsFileNameTmp , "w")) == NULL)
  {
    fclose ( rFriendsFile );
    return (ACCEPT_FRIENDSHIP_INVITATION__ERROR_OPENING_FRIENDS_TEMP_FILE_FOR_WRITING);
  }
  
  found = false;
     
  for (retCode = 0; retCode != GET_USER_ID__END_OF_FILE;)  
  {
    if ((retCode = getUserId ( rFriendsFile, &buffer)) != OK )
    {
      if (retCode != GET_USER_ID__END_OF_FILE)
      {
        fclose (rFriendsFile);
        fclose (wFriendsFile);
        remove (friendsFileNameTmp);
        return (retCode);
      }
    }
    if ((retCode = getUserId ( rFriendsFile, &bufferTwo)) != OK )
    {
      if (retCode != GET_USER_ID__END_OF_FILE)
      {
        fclose (rFriendsFile);
        fclose (wFriendsFile);
        remove (friendsFileNameTmp);
        return (retCode);
      }
    }    
    if (retCode != GET_USER_ID__END_OF_FILE) /*SEARCH FOR THE POSITION WHERE THE FRIENDSHIP IS GOING TO BE INCLUDED*/
    {  
      if ( buffer > smallerId ) /*IT`S IN THE POSITION WHERE THE FRIENDSHIP SHOULD BE INCLUDED*/
      {
        if ( !found )
	{
          if ((retCode2 = putUserId (wFriendsFile, &smallerId)) != OK )
          {
            fclose (rFriendsFile);
            fclose (wFriendsFile);
            remove (friendsFileNameTmp);
	    return (retCode2);
          }
	  if ((retCode2 = putUserId (wFriendsFile, &biggerId)) != OK )
          {
            fclose (rFriendsFile);
            fclose (wFriendsFile);
            remove (friendsFileNameTmp);
	    return (retCode2);
          }
	  
	  found = true;
	  
	}
        if ((retCode2 = putUserId (wFriendsFile, &buffer)) != OK )
        {
          fclose (rFriendsFile);
          fclose (wFriendsFile);
          remove (friendsFileNameTmp);
	  return (retCode2);
        }     
        if ((retCode2 = putUserId (wFriendsFile, &bufferTwo)) != OK )
        {
          fclose (rFriendsFile);
          fclose (wFriendsFile);
          remove (friendsFileNameTmp);
	  return (retCode2);
        }
      }
      if ( buffer == smallerId )
      {
        if ( bufferTwo < biggerId ) /*IT`S BEFORE THE POSITION WHERE THE FRIENDSHIP IS GOING TO BE INCLUDED*/
	{
	  if ((retCode2 = putUserId (wFriendsFile, &buffer)) != OK )
          {
            fclose (rFriendsFile);
            fclose (wFriendsFile);
            remove (friendsFileNameTmp);
	    return (retCode2);
          }     
          if ((retCode2 = putUserId (wFriendsFile, &bufferTwo)) != OK )
          {
            fclose (rFriendsFile);
            fclose (wFriendsFile);
            remove (friendsFileNameTmp);
	    return (retCode2);
          } 
	}
	if ( bufferTwo == biggerId ) /*FRIENDSHIP ALREADY EXISTS*/
	{
	  fclose (wFriendsFile);
	  fclose (rFriendsFile);
	  rename (invitingFriendOutFileNameTmp, invitingFriendOutFileName);
	  rename (invitedFriendInFileNameTmp, invitedFriendInFileName);
	  return (ACCEPT_FRIENDSHIP_INVITATION__FRIENDSHIP_ALREADY_EXISTS);
	}
	if ( bufferTwo > biggerId ) /*IT`S IN THE POSITION WHERE THE FRIENDSHIP SHOULD BE INCLUDED*/
	{
	  if ( !found )
	  {
	    if ((retCode2 = putUserId (wFriendsFile, &smallerId)) != OK )
            {
              fclose (rFriendsFile);
              fclose (wFriendsFile);
              remove (friendsFileNameTmp);
	      return (retCode2);
            }
	    if ((retCode2 = putUserId (wFriendsFile, &biggerId)) != OK )
            {
              fclose (rFriendsFile);
              fclose (wFriendsFile);
              remove (friendsFileNameTmp);
	      return (retCode2);
            }
	    
	    found = true;
	    
	  }
          if ((retCode2 = putUserId (wFriendsFile, &buffer)) != OK )
          {
            fclose (rFriendsFile);
            fclose (wFriendsFile);
            remove (friendsFileNameTmp);
	    return (retCode2);
          }     
          if ((retCode2 = putUserId (wFriendsFile, &bufferTwo)) != OK )
          {
            fclose (rFriendsFile);
            fclose (wFriendsFile);
            remove (friendsFileNameTmp);
	    return (retCode2);
          }
	}
      }
      if ( buffer < smallerId ) /*IT`S BEFORE THE POSITION WHERE THE FRIENDSHIP IS GOING TO BE INCLUDED*/
      {
        if ((retCode2 = putUserId (wFriendsFile, &buffer)) != OK )
        {
          fclose (rFriendsFile);
          fclose (wFriendsFile);
          remove (friendsFileNameTmp);
	  return (retCode2);
        }     
        if ((retCode2 = putUserId (wFriendsFile, &bufferTwo)) != OK )
        {
          fclose (rFriendsFile);
          fclose (wFriendsFile);
          remove (friendsFileNameTmp);
	  return (retCode2);
        }
      }
    }            
  }
  
  if (! found ) /*IT`S THE LAST FRIENDSHIP OF THE FILE*/
  {
    if ((retCode2 = putUserId (wFriendsFile, &smallerId)) != OK )
    {
      fclose (rFriendsFile);
      fclose (wFriendsFile);
      remove (friendsFileNameTmp);
      return (retCode2);
    }
    if ((retCode2 = putUserId (wFriendsFile, &biggerId)) != OK )
    {
      fclose (rFriendsFile);
      fclose (wFriendsFile);
      remove (friendsFileNameTmp);
      return (retCode2);
    }
  }  
    
  /*RENAMEING THE TEMP FILE NAMES TO REPLACE DE OLD ONES*/
  fclose (rFriendsFile);
  fclose (wFriendsFile);
  rename (invitingFriendOutFileNameTmp, invitingFriendOutFileName);
  rename (invitedFriendInFileNameTmp, invitedFriendInFileName);
  rename (friendsFileNameTmp, friendsFileName);
  
  
  #ifdef ENGLISH
    snprintf (emailBody, 500, "\n\
      *** This is a system message, you don't need to reply! ***\n\
      \n\
      Dear %s,\n\
      \n\
        Your friendship invitation has been accepted by %s.\n\
      \n\
      \n\
      Our web site: http://www.del.ufrj.br/~marceloddm/computacao_ii/pf", invitingFriendData.name, invitedFriendData.name);
  #elif PORTUGUESE
    snprintf (emailBody, 500, "\n\
      *** Essa é uma mensagem de sistema, você não precisa respondê-la! ***\n\
      \n\
      Caro(a) %s,\n\
      \n\
        Seu convite de amizade foi aceito por %s.\n\
      \n\
      \n\
      Nosso web site: http://www.del.ufrj.br/~marceloddm/computacao_ii/pf", invitingFriendData.name, invitedFriendData.name);  
  #endif
      
  if (sendMail (WEB_SERVER_DOMAIN, SMTP_SERVER_ADDRESS, SMTP_SERVER_PORT, ADMINISTRATOR_EMAIL, invitingFriendData.email, NULL, NULL, showTextHelpMessage (ACCEPT_FRIENDSHIP_INVITATION__SUBJECT), emailBody, NULL) != OK)
    return (ERROR_SENDING_EMAIL);

  return (OK);      
}

/*$RCSfile: acceptFriendshipInvitation.c,v $*/


