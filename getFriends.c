//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: getFriends() primary function source file 
// Date: 26/12/2004
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: getFriends.c,v $
 * Revision 1.2  2005/02/16 22:11:21  marceloddm
 * CGI's added
 *
 * Revision 1.1  2004/12/28 00:37:46  marceloddm
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
#include "functions.h"
#include "getFriends.h"
 
static const char rcsid [] = "$Id: getFriends.c,v 1.2 2005/02/16 22:11:21 marceloddm Exp marceloddm $";

unsigned getFriends ( userIdType userId, userDataType ** firstFriend)
{
  unsigned retCode, retCode2;
  char friendsFileName [MAX_LENGTH_LONG_FILENAME +1];
  FILE *rFriendsFile;
  userIdType buffer, bufferTwo;
  userDataType * lastFriend, *cursor, friendData, userData;
  boolean allFound;

  if ((retCode = getDataFromId (userId, &userData)) != OK)
    return (retCode); 
    
  /*PERFORMING NEEDED OPERATIONS IN THE FRIENDS FILE*/ 
  
  if ((retCode = getLongFilename (DATA_DIR, FRIENDS_FILE_NAME , friendsFileName)) != OK)
    return (retCode);

  if ((rFriendsFile = fopen (friendsFileName, "r")) == NULL)
  {
    if (errno != ENOENT)
      return (GET_FRIENDS__ERROR_OPENING_FRIENDS_FILE_FOR_READING);
    return (GET_FRIENDS__FRIENDS_FILE_DOES_NOT_EXIST);
  }

  allFound = false;
  *firstFriend = NULL;
  lastFriend   = NULL;  
  
  for (retCode = 0; ( (retCode != GET_USER_ID__END_OF_FILE) && ( ! allFound ) );)  
  {
    if ((retCode = getUserId ( rFriendsFile, &buffer)) != OK )
    {
      if (retCode != GET_USER_ID__END_OF_FILE)
      {
        fclose (rFriendsFile);
        freeFIFOResources ( firstFriend , &lastFriend );
        return (retCode);
      }
    }
    if ((retCode = getUserId ( rFriendsFile, &bufferTwo)) != OK )
    {
      if (retCode != GET_USER_ID__END_OF_FILE)
      {
        fclose (rFriendsFile);
        freeFIFOResources ( firstFriend , &lastFriend );
        return (retCode);
      }
    }    
    if (retCode != GET_USER_ID__END_OF_FILE) /*SEARCH FOR THE POSITION WHERE THE USER'S FRIENDS ARE*/
    {  
      if ( buffer == userId ) /*FRIEND FOUND, INSERTING INTO FIFO*/ 
      { 
        friendData.userId = bufferTwo;
        if( ( retCode2 = insertFIFO ( firstFriend, &lastFriend, &friendData ) ) != OK )
	{
	  fclose ( rFriendsFile );
	  freeFIFOResources ( firstFriend , &lastFriend );
	  return ( retCode2);
	}
      }
      if ( bufferTwo == userId ) /*FRIEND FOUND, INSERTING INTO FIFO*/ 
      { 
        friendData.userId = buffer;
        if( ( retCode2 = insertFIFO ( firstFriend, &lastFriend, &friendData ) ) != OK )
	{
	  fclose ( rFriendsFile );
	  freeFIFOResources ( firstFriend , &lastFriend );
	  return ( retCode2);
	}
      }
      if ( buffer > userId ) /*ALL FRIENDS HAVE BEEN FOUND*/
        allFound = true;
    }  
  }
  
  fclose (rFriendsFile);
  if (! (* firstFriend) ) /*NO FRIENDS FOUND*/
      return (GET_FRIENDS__NO_FRIENDS_FOUND);
    
       
  /*GETTING USERDATA FROM THE USERS'S FRIENDS*/
  
  cursor = (*firstFriend);
  
  while ( cursor != NULL )
  {
    if ( ( retCode = getDataFromId (cursor->userId, cursor) ) != OK )
    {
      fclose ( rFriendsFile );
      freeFIFOResources ( firstFriend , &lastFriend );
      return ( retCode);
    }  
    
    cursor = cursor->next;
    
  }
  
  return (OK);      
}

/*$RCSfile: getFriends.c,v $*/


