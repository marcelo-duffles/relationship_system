//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: editUserData() primary function source file 
// Date: 15/12/2004
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: editUserData.c,v $
 * Revision 1.5  2005/02/16 22:11:21  marceloddm
 * CGI's added
 *
 * Revision 1.4  2004/12/20 12:37:13  marceloddm
 * Problem not yet solved
 *
 * Revision 1.3  2004/12/18 02:00:13  marceloddm
 * There is a problem in this function
 *
 * Revision 1.2  2004/12/17 12:09:03  marceloddm
 * The editUserData() function is now complete!
 *
 * Revision 1.1  2004/12/16 00:09:12  marceloddm
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
#include "error.h"
#include "functions.h"
#include "editUserData.h"
#include "config.h"
 
static const char rcsid [] = "$Id: editUserData.c,v 1.5 2005/02/16 22:11:21 marceloddm Exp marceloddm $";
  
unsigned editUserData (userDataType *newData)
{
  unsigned retCode;
  char usersFileName[MAX_LENGTH_LONG_FILENAME +1];
  char tempFileName[MAX_LENGTH_LONG_FILENAME +1];
  FILE *readFile, *writeFile;
  userDataType buffer;
  boolean found;
  
  
  if ((retCode = checkUserData (newData)) != OK)
    return (retCode);

  if ((retCode = getLongFilename (DATA_DIR, USERS_FILE_NAME, usersFileName)) != OK)
    return (retCode);
    
  if ((retCode = getLongFilename (DATA_DIR, USERS_TEMP_FILE_NAME, tempFileName)) != OK)
    return (retCode);

  found = false;

  readFile = fopen (usersFileName, "r");
  if (readFile == NULL)
  {
    if (errno != ENOENT)
      return (EDIT_USER_DATA__ERROR_OPENING_USERS_FILE_FOR_READING);
    return (EDIT_USER_DATA__USERS_FILE_DOES_NOT_EXIST);
  }

  if ((writeFile = fopen (tempFileName, "w")) == NULL)
  { 
    fclose (readFile);  
    return (EDIT_USER_DATA__ERROR_OPENING_TEMP_FILE_FOR_WRITING);  
  }   

  for (retCode = 0; retCode != GET_USER_ID__END_OF_FILE;)  
  {
    if ((retCode = getUserData (readFile, USERS_FILE_NAME, &buffer)) != OK )
    {
      if (retCode != GET_USER_ID__END_OF_FILE)
      {
        fclose (readFile);
        fclose (writeFile);
        remove (tempFileName);
        return (retCode);
      }
    }
    if (retCode != GET_USER_ID__END_OF_FILE)
    {  
      if ((buffer.userId) != (newData->userId))
      {
        if (!strcmp (buffer.name, newData->name))
          if (!(strcmp (buffer.birthday, newData->birthday)))
          {
	    fclose (readFile);
	    fclose (writeFile);
	    remove (tempFileName);
	    return (EDIT_USER_DATA__NAME_AND_BIRTHDAY_ALREADY_EXIST);
	  }
        if (putUserData (writeFile, USERS_TEMP_FILE_NAME, &buffer) != OK )
        {
	  fclose (readFile);
	  fclose (writeFile);
	  remove (tempFileName);
	  return (EDIT_USER_DATA__ERROR_WRITING_IN_TEMP_FILE);
        }     
      }
      if ((buffer.userId) == (newData->userId))
      {
        if (putUserData (writeFile, USERS_TEMP_FILE_NAME, newData) != OK )
        {
	   fclose (readFile);
	   fclose (writeFile);
	   remove (tempFileName);
	   return (EDIT_USER_DATA__ERROR_WRITING_IN_TEMP_FILE);
        }
        found = true; 
      }
    }            
  }

  fclose (readFile);
  fclose (writeFile);
  
  if (!found)
  {
    remove (tempFileName);
    return (EDIT_USER_DATA__USER_NOT_FOUND);   
  }

  rename (tempFileName, usersFileName);

  return (OK);      
}

/*$RCSfile: editUserData.c,v $*/


