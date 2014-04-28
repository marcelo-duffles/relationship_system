//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: addUser() primary function source file 
// Date: 21/12/2004
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: addUser.c,v $
 * Revision 1.2  2005/02/16 22:11:21  marceloddm
 * CGI's added
 *
 * Revision 1.1  2004/12/21 23:06:02  marceloddm
 * Initial revision
 *
 */

 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>
#include <errno.h>
#include "const.h"
#include "types.h"
#include "error.h"
#include "functions.h"
#include "addUser.h"
#include "config.h"


unsigned addUser (userDataType *newData)
{
  unsigned errorCode;
  char passwordFileName[MAX_LENGTH_LONG_FILENAME +1];
  char usersFileName[MAX_LENGTH_LONG_FILENAME +1];
  char tempFileName[MAX_LENGTH_LONG_FILENAME +1];
  char inFilename[MAX_LENGTH_LONG_FILENAME +1];
  char outFilename[MAX_LENGTH_LONG_FILENAME +1];
  char tempInFilename[20 +4 +1];
  char tempOutFilename[20 +5 +1]; 
  userDataType buffer;
  userIdType id;
  FILE *usersFile, *passwordFile, *tempFile, *inFile, *outFile;
  boolean found;

  
  if ((errorCode = checkUserData (newData)) != OK)
    return (errorCode);

  if ((errorCode = getLongFilename (DATA_DIR, USERS_FILE_NAME, usersFileName)) != OK)
    return (errorCode);
    
  if ((usersFile = fopen (usersFileName, "r")) == NULL)
  {
    if (errno != ENOENT)
      return (ADD_USER__ERROR_OPENING_USERS_FILE_FOR_READING);
    return (ADD_USER__USERS_FILE_DOES_NOT_EXIST);
  }  
    
  for (errorCode = 0, id = 0, found = false; errorCode != GET_USER_ID__END_OF_FILE; id++)  
  {
    if ((errorCode = getUserData (usersFile, USERS_FILE_NAME, &buffer)) != OK)
      if (errorCode != GET_USER_ID__END_OF_FILE)
      {
        fclose (usersFile);
        return (errorCode);
      }
    if (errorCode != GET_USER_ID__END_OF_FILE) 
    {
      if (id < buffer.userId)
      {
        newData->userId = id;
	found = true;
      }
      if (!(strcmp (buffer.name, newData->name)) && !strcmp (buffer.birthday, newData->birthday))
      {
	fclose (usersFile);
	return (ADD_USER__USER_ALREADY_EXIST);
      }
    }
  }
  fclose (usersFile);
  if (!found)
    newData->userId = id -1;     
      
  if (newData->category == webUser)
  {  
    if ((errorCode = getLongFilename (DATA_DIR, PASSWORD_FILE_NAME, passwordFileName)) != OK)
      return (errorCode);
    
    if ((passwordFile = fopen (passwordFileName, "r")) == NULL)
    {
      if (errno != ENOENT)
        return (ADD_USER__ERROR_OPENING_PASSWORD_FILE_FOR_READING);
      return (ADD_USER__PASSWORD_FILE_DOES_NOT_EXIST);
    }  
    
    for (errorCode = 0; errorCode != GET_USER_ID__END_OF_FILE;)  
    {
      if ((errorCode = getUserData (passwordFile, PASSWORD_FILE_NAME, &buffer)) != OK)
        if (errorCode != GET_USER_ID__END_OF_FILE)
        {
          fclose (passwordFile);
          return (errorCode);
        }
      if (errorCode != GET_USER_ID__END_OF_FILE) 
        if (!strcmp (buffer.userName, newData->userName))
        {
	  fclose (passwordFile);
	  return (ADD_USER__USERNAME_ALREADY_EXIST);
        }
    }
    fclose (passwordFile);
  }
        
  if ((errorCode = getLongFilename (DATA_DIR, USERS_TEMP_FILE_NAME, tempFileName)) != OK)
    return (errorCode);
    
  if ((tempFile = fopen (tempFileName, "w")) == NULL)
    return (ADD_USER__ERROR_OPENING_USERS_TEMP_FILE_FOR_WRITING);
    
  if ((usersFile = fopen (usersFileName, "r")) == NULL)
    return (ADD_USER__ERROR_OPENING_USERS_FILE_FOR_READING);

  for (errorCode = 0, found = false; errorCode != GET_USER_ID__END_OF_FILE;)  
  {
    if ((errorCode = getUserData (usersFile, USERS_FILE_NAME, &buffer)) != OK )
    {
      if (errorCode != GET_USER_ID__END_OF_FILE)
      {
        fclose (usersFile);
        fclose (tempFile);
        remove (tempFileName);
        return (errorCode);
      }
    }
    if (errorCode != GET_USER_ID__END_OF_FILE)
    {  
      if (newData->userId < buffer.userId) 
      {
        if (putUserData (tempFile, USERS_TEMP_FILE_NAME, newData) != OK )
        {
	  fclose (usersFile);
	  fclose (tempFile);
	  remove (tempFileName);
	  return (ADD_USER__ERROR_WRITING_IN_USERS_TEMP_FILE);
        }     
	found = true;
      }
      if (putUserData (tempFile, USERS_TEMP_FILE_NAME, &buffer) != OK )
      {
	 fclose (usersFile);
	 fclose (tempFile);
         remove (tempFileName);
	 return (ADD_USER__ERROR_WRITING_IN_USERS_TEMP_FILE);
      }
    }            
  }
  if (!found)
    if (putUserData (tempFile, USERS_TEMP_FILE_NAME, newData) != OK )
    {
      fclose (usersFile);
      fclose (tempFile);
      remove (tempFileName);
      return (ADD_USER__ERROR_WRITING_IN_USERS_TEMP_FILE);
    }  
  fclose (usersFile);
  fclose (tempFile);
  rename (tempFileName, usersFileName);
  
  if (newData->category == webUser)
  {
    if ((errorCode = getLongFilename (DATA_DIR, PASSWORD_TEMP_FILE_NAME, tempFileName)) != OK)
      return (errorCode);
    
    if ((tempFile = fopen (tempFileName, "w")) == NULL)
      return (ADD_USER__ERROR_OPENING_PASSWORD_TEMP_FILE_FOR_WRITING);
    
    if ((passwordFile = fopen (passwordFileName, "r")) == NULL)
        return (ADD_USER__ERROR_OPENING_PASSWORD_FILE_FOR_READING);
    

    for (errorCode = 0, found = false; errorCode != GET_USER_ID__END_OF_FILE;)  
    {
      if ((errorCode = getUserData (passwordFile, PASSWORD_FILE_NAME, &buffer)) != OK )
      {
        if (errorCode != GET_USER_ID__END_OF_FILE)
        {
          fclose (passwordFile);
          fclose (tempFile);
          remove (tempFileName);
          return (errorCode);
        }
      }
      if (errorCode != GET_USER_ID__END_OF_FILE)
      {  
        if (newData->userId < buffer.userId) 
        {
          if (putUserData (tempFile, PASSWORD_TEMP_FILE_NAME, newData) != OK )
          {
	    fclose (passwordFile);
	    fclose (tempFile);
            remove (tempFileName);
	    return (ADD_USER__ERROR_WRITING_IN_PASSWORD_TEMP_FILE);
          }     
	  found = true;
        }
        if (putUserData (tempFile, PASSWORD_TEMP_FILE_NAME, &buffer) != OK )
        {
  	   fclose (passwordFile);
	   fclose (tempFile);
	   remove (tempFileName);
	   return (ADD_USER__ERROR_WRITING_IN_PASSWORD_TEMP_FILE);
        }
      }            
    }
    if (!found)
      if (putUserData (tempFile, PASSWORD_TEMP_FILE_NAME, newData) != OK )
      {
        fclose (passwordFile);
        fclose (tempFile);
        remove (tempFileName);
        return (ADD_USER__ERROR_WRITING_IN_PASSWORD_TEMP_FILE);
      } 
    fclose (passwordFile);
    fclose (tempFile);
    rename (tempFileName, passwordFileName);
  }
  
  if (newData->category == webUser)
  {
    snprintf (tempInFilename, 20 +3 +1, "%020llu.in", newData->userId); 
    if ((errorCode = getLongFilename (DATA_DIR, tempInFilename, inFilename)) != OK)
      return (errorCode);
    if ((inFile = fopen (inFilename, "w")) == NULL)
      return (ADD_USER__ERROR_OPENING_IN_FILE_FOR_WRITING);
    fclose (inFile);
  
    snprintf (tempOutFilename, 20 +4 +1, "%020llu.out", newData->userId); 
    if ((errorCode = getLongFilename (DATA_DIR, tempOutFilename, outFilename)) != OK)
      return (errorCode);
    if ((outFile = fopen (outFilename, "w")) == NULL)
      return (ADD_USER__ERROR_OPENING_OUT_FILE_FOR_WRITING);
   fclose (outFile);
  }
   
  return (OK);      
}
  

/*$RCSfile: addUser.c,v $*/
