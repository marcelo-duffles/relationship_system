//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: install() primary function source file 
// Date: 11/12/2004
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: install.c,v $
 * Revision 1.7  2005/02/16 22:11:21  marceloddm
 * CGI's added
 *
 * Revision 1.6  2004/12/20 12:49:02  marceloddm
 * Some corrections have been done: fclose() has been added in some parts of the code
 *
 * Revision 1.5  2004/12/16 00:17:17  marceloddm
 * The checkUserData() returned to the code
 *
 * Revision 1.4  2004/12/15 01:33:26  marceloddm
 * The function does not check fields any more
 *
 * Revision 1.3  2004/12/14 02:47:18  marceloddm
 * This function is now complete.
 * It's time to test it.
 *
 * Revision 1.2  2004/12/13 15:59:57  marceloddm
 * Updated with putUserData() function
 *
 * Revision 1.1  2004/12/13 07:56:07  marceloddm
 * Initial revision
 *
 */


#include <stdio.h>
#include <sys/errno.h>
#include <errno.h>
#include "functions.h"
#include "types.h"
#include "error.h"
#include "const.h"
#include "config.h"


unsigned install (userDataType *userData)
{
  unsigned errorCode;
  FILE *passwordFile, *usersFile, *friendsFile, *parentsFile, *inFile, *outFile;
  char passwordFilename[MAX_LENGTH_LONG_FILENAME +1];
  char usersFilename[MAX_LENGTH_LONG_FILENAME +1];
  char friendsFilename[MAX_LENGTH_LONG_FILENAME +1];
  char parentsFilename[MAX_LENGTH_LONG_FILENAME +1];
  char inFilename[MAX_LENGTH_LONG_FILENAME +1];
  char outFilename[MAX_LENGTH_LONG_FILENAME +1];
  char tempInFilename[20 +4 +1];
  char tempOutFilename[20 +5 +1]; 
  
  if (userData == NULL)
    return (INSTALL__INVALID_USER_DATA);
    
  if ((errorCode = checkUserData (userData)) != OK)
    return (errorCode);
    
/*---------------------------------------------------------------------------------------------------------*/

  if ((errorCode = getLongFilename (DATA_DIR, PASSWORD_FILE_NAME, passwordFilename)) != OK)
    return (errorCode);
   
  if ((passwordFile = fopen (passwordFilename, "r")) != NULL)
  {
    fclose (passwordFile);
    return (INSTALL__SYSTEM_ALREADY_INSTALLED);
  }
    
  if (errno != ENOENT)
    return (INSTALL__ERROR_READING_PASSWORD_FILE);
    
  if ((passwordFile = fopen (passwordFilename, "w")) == NULL)
    return (INSTALL__ERROR_OPENING_PASSWORD_FILE_FOR_WRITING);
    
  if ((errorCode = putUserData (passwordFile, PASSWORD_FILE_NAME, userData)) != OK)
  {
    fclose (passwordFile);  
    return (errorCode);
  }
    
  fclose (passwordFile);  
  
/*---------------------------------------------------------------------------------------------------------*/
  
  if ((errorCode = getLongFilename (DATA_DIR, USERS_FILE_NAME, usersFilename)) != OK)
    return (errorCode);
  
  if ((usersFile = fopen (usersFilename, "r")) != NULL)
  {
    fclose (usersFile);
    return (INSTALL__SYSTEM_ALREADY_INSTALLED);
  }
  
  if (errno != ENOENT)
    return (INSTALL__ERROR_READING_USERS_FILE);
    
  if ((usersFile = fopen (usersFilename, "w")) == NULL)
    return (INSTALL__ERROR_OPENING_USERS_FILE_FOR_WRITING); 
    
  if ((errorCode = putUserData (usersFile, USERS_FILE_NAME, userData)) != OK)
  {
    fclose (usersFile);
    return (errorCode);
  }
      
  fclose (usersFile);
  
/*---------------------------------------------------------------------------------------------------------*/ 
    
  if ((errorCode = getLongFilename (DATA_DIR, PARENTS_FILE_NAME, parentsFilename)) != OK)
    return (errorCode);
  
  if ((parentsFile = fopen (parentsFilename, "r")) != NULL)
  {
    fclose (parentsFile);
    return (INSTALL__SYSTEM_ALREADY_INSTALLED);
  }
  
  if (errno != ENOENT)
    return (INSTALL__ERROR_READING_PARENTS_FILE);
    
  if ((parentsFile = fopen (parentsFilename, "w")) == NULL)
    return (INSTALL__ERROR_OPENING_PARENTS_FILE_FOR_WRITING); 
    
  fclose (parentsFile);
  
/*---------------------------------------------------------------------------------------------------------*/ 
  if ((errorCode = getLongFilename (DATA_DIR, FRIENDS_FILE_NAME, friendsFilename)) != OK)
    return (errorCode);
  
  if ((friendsFile = fopen (friendsFilename, "r")) != NULL)
  {
    fclose (friendsFile);
    return (INSTALL__SYSTEM_ALREADY_INSTALLED);
  }
  
  if (errno != ENOENT)
    return (INSTALL__ERROR_READING_FRIENDS_FILE);
    
  if ((friendsFile = fopen (friendsFilename, "w")) == NULL)
    return (INSTALL__ERROR_OPENING_FRIENDS_FILE_FOR_WRITING); 
   
  fclose (friendsFile);
  
/*---------------------------------------------------------------------------------------------------------*/  
  snprintf (tempInFilename, 20 +3 +1, "%020llu.in", userData->userId); 
  if ((errorCode = getLongFilename (DATA_DIR, tempInFilename, inFilename)) != OK)
    return (errorCode);
  if ((inFile = fopen (inFilename, "w")) == NULL)
    return (INSTALL__ERROR_OPENING_IN_FILE_FOR_WRITING);
  fclose (inFile);
  
  snprintf (tempOutFilename, 20 +4 +1, "%020llu.out", userData->userId); 
  if ((errorCode = getLongFilename (DATA_DIR, tempOutFilename, outFilename)) != OK)
    return (errorCode);
  if ((outFile = fopen (outFilename, "w")) == NULL)
    return (INSTALL__ERROR_OPENING_OUT_FILE_FOR_WRITING);
  fclose (outFile);
  
/*---------------------------------------------------------------------------------------------------------*/  
  
  return (OK);
}
