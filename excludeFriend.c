//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: excludeFriend() primary function source file 
// Date: 25/12/2004
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: excludeFriend.c,v $
 * Revision 1.2  2005/02/16 22:11:21  marceloddm
 * CGI's added
 *
 * Revision 1.1  2004/12/25 17:01:13  marceloddm
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
#include "excludeFriend.h"
#include "sendmail.h"
 
static const char rcsid [] = "$Id: excludeFriend.c,v 1.2 2005/02/16 22:11:21 marceloddm Exp marceloddm $";

unsigned excludeFriend ( userIdType noMoreFriendId, userIdType excludedFriendId)
{
  unsigned retCode, retCode2;
  char friendsFileName [MAX_LENGTH_LONG_FILENAME +1];
  char friendsFileNameTmp [MAX_LENGTH_LONG_FILENAME +1];
  char emailBody[500 +1];
  FILE *rFriendsFile, *wFriendsFile;
  userIdType buffer, bufferTwo, smallerId, biggerId;
  userDataType noMoreFriendData, excludedFriendData;
  boolean found;
  
  if ((retCode = getDataFromId (noMoreFriendId, &noMoreFriendData)) != OK)
    return (retCode);
  if ((retCode = getDataFromId (excludedFriendId, &excludedFriendData)) != OK)
    return (retCode);  
    
  if ( noMoreFriendId > excludedFriendId )
  { 
    smallerId = excludedFriendId;
    biggerId = noMoreFriendId;
  }
  else
  {
    smallerId = noMoreFriendId;
    biggerId = excludedFriendId;
  }
  
  /*PERFORMING NEEDED OPERATIONS IN THE FRIENDS FILE*/ 
  
  if ((retCode = getLongFilename (DATA_DIR, FRIENDS_FILE_NAME , friendsFileName)) != OK)
    return (retCode);

  if ((rFriendsFile = fopen (friendsFileName, "r")) == NULL)
  {
    if (errno != ENOENT)
      return (EXCLUDE_FRIEND__ERROR_OPENING_FRIENDS_FILE_FOR_READING);
    return (EXCLUDE_FRIEND__FRIENDS_FILE_DOES_NOT_EXIST);
  }

  if ((retCode = getLongFilename (DATA_DIR, FRIENDS_TEMP_FILE_NAME , friendsFileNameTmp)) != OK)
    return (retCode);

  if ((wFriendsFile = fopen (friendsFileNameTmp , "w")) == NULL)
  {
    fclose ( rFriendsFile );
    return (EXCLUDE_FRIEND__ERROR_OPENING_FRIENDS_TEMP_FILE_FOR_WRITING);
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
    if (retCode != GET_USER_ID__END_OF_FILE) /*SEARCH FOR THE POSITION WHERE THE FRIENDSHIP IS GOING TO BE EXCLUDED*/
    {  
      if ( buffer != smallerId ) /*JUST COPYING THE OTHER FRIENDSHIPS*/  
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
      if ( buffer == smallerId )
      {
        if ( bufferTwo == biggerId ) /*IT`S BEFORE THE POSITION WHERE THE FRIENDSHIP IS GOING TO BE EXCLUDED*/
	  found = true;
        if ( bufferTwo != biggerId ) /*JUST COPYING THE OTHER FRIENDSHIPS*/
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
  }
  
  if (! found ) /*FRIENDSHIP BETWEEN THE GIVEN USERS NOT FOUND*/
    {
      fclose (rFriendsFile);
      fclose (wFriendsFile);
      remove (friendsFileNameTmp);
      return (EXCLUDE_FRIEND__THE_TWO_GIVEN_USERS_WERE_NOT_FRIENDS);
    }
    
    
  /*RENAMEING THE TEMP FILE NAMES TO REPLACE DE OLD ONES*/
  fclose (rFriendsFile);
  fclose (wFriendsFile);
  
  rename (friendsFileNameTmp, friendsFileName);
  
  #ifdef ENGLISH
    snprintf (emailBody, 500, "\n\
      *** This is a system message, you don't need to reply! ***\n\
      \n\
      Dear %s,\n\
      \n\
        Your friendship relation has been excluded by %s.\n\
      \n\
      \n\
      Our web site: http://www.del.ufrj.br/~marceloddm/computacao_ii/pf", excludedFriendData.name, noMoreFriendData.name);
  #elif PORTUGUESE
    snprintf (emailBody, 500, "\n\
      *** Essa é uma mensagem de sistema, você não precisa respondê-la! ***\n\
      \n\
      Caro(a) %s,\n\
      \n\
        Sua amizade foi excluída por %s.\n\
      \n\
      \n\
      Nosso web site: http://www.del.ufrj.br/~marceloddm/computacao_ii/pf", excludedFriendData.name, noMoreFriendData.name);  
  #endif
      
  if (sendMail (WEB_SERVER_DOMAIN, SMTP_SERVER_ADDRESS, SMTP_SERVER_PORT, ADMINISTRATOR_EMAIL, excludedFriendData.email, NULL, NULL, showTextHelpMessage (EXCLUDE_FRIEND__SUBJECT), emailBody, NULL) != OK)
    return (ERROR_SENDING_EMAIL);
   
  
  return (OK);      
}

/*$RCSfile: excludeFriend.c,v $*/


