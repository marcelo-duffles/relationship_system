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
 * $Log: changeUserCategory.c,v $
 * Revision 1.1  2005/02/16 22:11:21  marceloddm
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
#include "changeUserCategory.h"
 
static const char rcsid [] = "$Id: changeUserCategory.c,v 1.1 2005/02/16 22:11:21 marceloddm Exp marceloddm $";
  
/*FALTA TESTES DA ÁRVORE GENEOLÓGICA*/
/*lembrar de excluir amizades do usuario que estah mudando de webUser para relative*/

unsigned changeUserCategory ( userDataType * userData)
{
  unsigned retCode, retCode2;
  char passwordFileName[MAX_LENGTH_LONG_FILENAME +1];
  char    usersFileName[MAX_LENGTH_LONG_FILENAME +1];
  char     tempFileName[MAX_LENGTH_LONG_FILENAME +1];
  char       inFilename[MAX_LENGTH_LONG_FILENAME +1];
  char      outFilename[MAX_LENGTH_LONG_FILENAME +1];
  char tempInFilename[20 +4 +1];
  char tempOutFilename[20 +5 +1]; 
  FILE *readFile, *writeFile, *inFile, *outFile;
  userDataType buffer;
  boolean found;
  
  if (userData->category == administrator)
    return (CHANGE_USER_CATEGORY__CAN_NOT_CHANGE_ADMINISTRATOR_CATEGORY);
  
  /*CATEGORY CHANGE FROM RELATIVE TO WEB USER*/
  
  if ( userData->category == webUser )
  {
    if (( retCode = encodePassword ( userData->plainPass, userData->encryptedPass) ) != OK )
      return ( retCode );    
    
	if (( retCode = editUserData ( userData )) != OK )
      return ( retCode );
   
       
  if ((retCode = getLongFilename (DATA_DIR, PASSWORD_FILE_NAME, passwordFileName)) != OK)
    return (retCode);
    
  if ((retCode = getLongFilename (DATA_DIR, PASSWORD_TEMP_FILE_NAME, tempFileName)) != OK)
    return (retCode);

  found = false;
  
  readFile = fopen (passwordFileName, "r");
  if (readFile == NULL)
  {
    if (errno != ENOENT)
      return (CHANGE_USER_CATEGORY__ERROR_OPENING_PASSWORD_FILE_FOR_READING);
    return (CHANGE_USER_CATEGORY__PASSWORD_FILE_DOES_NOT_EXIST);
  }

  if ((writeFile = fopen (tempFileName, "w")) == NULL)
  { 
    fclose (readFile);  
    return (CHANGE_USER_CATEGORY__ERROR_OPENING_TEMP_FILE_FOR_WRITING);  
  }   

  for (retCode = 0; retCode != GET_USER_ID__END_OF_FILE;)  
  {
    if ((retCode = getUserData (readFile, PASSWORD_FILE_NAME, &buffer)) != OK )
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
      if (((buffer.userId) > (userData->userId)) && (!found))
      { 
        if ((retCode2 = putUserData (writeFile, PASSWORD_TEMP_FILE_NAME, userData)) != OK )
        {
	  fclose (readFile);
	  fclose (writeFile);
	  remove (tempFileName);
	  return (retCode2);
        }
        found = true;		
      }
      if ((retCode2 = putUserData (writeFile, PASSWORD_TEMP_FILE_NAME, &buffer)) != OK )
        {
	  fclose (readFile);
	  fclose (writeFile);
	  remove (tempFileName);
	  return (retCode2);
        }
    }            
    else
      if (!found)
        if ((retCode2 = putUserData (writeFile, PASSWORD_TEMP_FILE_NAME, userData)) != OK )
        {
	  fclose (readFile);
	  fclose (writeFile);
	  remove (tempFileName);
	  return (retCode2);
        }
  }
  
  fclose (readFile);
  fclose (writeFile);
  rename (tempFileName, passwordFileName);
          
  /*CHANGING CATEGORY IN USERS FILE*/
    
  if ((retCode = getLongFilename (DATA_DIR, USERS_FILE_NAME, usersFileName)) != OK)
    return (retCode);
    
  if ((retCode = getLongFilename (DATA_DIR, USERS_TEMP_FILE_NAME, tempFileName)) != OK)
    return (retCode);


  readFile = fopen (usersFileName, "r");
  if (readFile == NULL)
  {
    if (errno != ENOENT)
      return (CHANGE_USER_CATEGORY__ERROR_OPENING_USERS_FILE_FOR_READING);
    return (CHANGE_USER_CATEGORY__USERS_FILE_DOES_NOT_EXIST);
  }

  if ((writeFile = fopen (tempFileName, "w")) == NULL)
  { 
    fclose (readFile);  
    return (CHANGE_USER_CATEGORY__ERROR_OPENING_TEMP_FILE_FOR_WRITING);  
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
      if ((buffer.userId) == (userData->userId))
	  {
        if ((retCode2 = putUserData (writeFile, USERS_TEMP_FILE_NAME, userData)) != OK )
        {
	  fclose (readFile);
	  fclose (writeFile);
	  remove (tempFileName);
	  return (retCode2);
        }
      }
      else     
        if ((retCode2 = putUserData (writeFile, USERS_TEMP_FILE_NAME, &buffer)) != OK )
        {
	  fclose (readFile);
	  fclose (writeFile);
	  remove (tempFileName);
	  return (retCode2);
        }
    }            
  }
  
  fclose (readFile);
  fclose (writeFile);
  rename (tempFileName, usersFileName);
  
  /*CREATING .in AND .out FILES*/
  
  snprintf (tempInFilename, 20 +3 +1, "%020llu.in", userData->userId); 
  if ((retCode = getLongFilename (DATA_DIR, tempInFilename, inFilename)) != OK)
    return (retCode);
  if ((inFile = fopen (inFilename, "w")) == NULL)
    return (CHANGE_USER_CATEGORY__ERROR_OPENING_IN_FILE_FOR_WRITING);
  fclose (inFile);
  
  snprintf (tempOutFilename, 20 +4 +1, "%020llu.out", userData->userId); 
  if ((retCode = getLongFilename (DATA_DIR, tempOutFilename, outFilename)) != OK)
    return (retCode);
  if ((outFile = fopen (outFilename, "w")) == NULL)
    return (CHANGE_USER_CATEGORY__ERROR_OPENING_OUT_FILE_FOR_WRITING);
  fclose (outFile);
  
  return (OK );  
  }    
      
  /*CATEGORY CHANGE FROM WEB USER TO RELATIVE*/
  
  if ( userData->category == relative )
  {
    userData->userName[0]      = EOS;
    userData->plainPass[0]     = EOS;
    userData->encryptedPass[0] = EOS;
    
    if (( retCode = editUserData ( userData )) != OK )
      return ( retCode );
      
  if ((retCode = getLongFilename (DATA_DIR, PASSWORD_FILE_NAME, passwordFileName)) != OK)
    return (retCode);
    
  if ((retCode = getLongFilename (DATA_DIR, PASSWORD_TEMP_FILE_NAME, tempFileName)) != OK)
    return (retCode);

  readFile = fopen (passwordFileName, "r");
  if (readFile == NULL)
  {
    if (errno != ENOENT)
      return (CHANGE_USER_CATEGORY__ERROR_OPENING_PASSWORD_FILE_FOR_READING);
    return (CHANGE_USER_CATEGORY__PASSWORD_FILE_DOES_NOT_EXIST);
  }

  if ((writeFile = fopen (tempFileName, "w")) == NULL)
  { 
    fclose (readFile);  
    return (CHANGE_USER_CATEGORY__ERROR_OPENING_TEMP_FILE_FOR_WRITING);  
  }   

  for (retCode = 0; retCode != GET_USER_ID__END_OF_FILE;)  
  {
    if ((retCode = getUserData (readFile, PASSWORD_FILE_NAME, &buffer)) != OK )
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
      if ((buffer.userId) != (userData->userId)) 
        if ((retCode2 = putUserData (writeFile, PASSWORD_TEMP_FILE_NAME, &buffer)) != OK )
        {
	  fclose (readFile);
	  fclose (writeFile);
	  remove (tempFileName);
	  return (retCode2);
        }     
    }            
  }
  
  fclose (readFile);
  fclose (writeFile);
  rename (tempFileName, passwordFileName);
            
  /*CHANGING CATEGORY IN USERS FILE*/
    
  if ((retCode = getLongFilename (DATA_DIR, USERS_FILE_NAME, usersFileName)) != OK)
    return (retCode);
    
  if ((retCode = getLongFilename (DATA_DIR, USERS_TEMP_FILE_NAME, tempFileName)) != OK)
    return (retCode);

  readFile = fopen (usersFileName, "r");
  if (readFile == NULL)
  {
    if (errno != ENOENT)
      return (CHANGE_USER_CATEGORY__ERROR_OPENING_USERS_FILE_FOR_READING);
    return (CHANGE_USER_CATEGORY__USERS_FILE_DOES_NOT_EXIST);
  }

  if ((writeFile = fopen (tempFileName, "w")) == NULL)
  { 
    fclose (readFile);  
    return (CHANGE_USER_CATEGORY__ERROR_OPENING_TEMP_FILE_FOR_WRITING);  
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
      if ((buffer.userId) == (userData->userId))
	  {		  
        if ((retCode2 = putUserData (writeFile, USERS_TEMP_FILE_NAME, userData)) != OK )
        {
	  fclose (readFile);
	  fclose (writeFile);
	  remove (tempFileName);
	  return (retCode2);
        }
	  }
      else     
        if ((retCode2 = putUserData (writeFile, USERS_TEMP_FILE_NAME, &buffer)) != OK )
        {
	  fclose (readFile);
	  fclose (writeFile);
	  remove (tempFileName);
	  return (retCode2);
        }
    }            
  }
  
  fclose (readFile);
  fclose (writeFile);
  rename (tempFileName, usersFileName);
  
  /*REMOVING .in AND .out FILES*/
  
  snprintf (tempInFilename, 20 +3 +1, "%020llu.in", userData->userId); 
  if ((retCode = getLongFilename (DATA_DIR, tempInFilename, inFilename)) != OK)
    return (retCode);
  remove (inFilename);
  
  snprintf (tempOutFilename, 20 +4 +1, "%020llu.out", userData->userId); 
  if ((retCode = getLongFilename (DATA_DIR, tempOutFilename, outFilename)) != OK)
    return (retCode);
  remove (outFilename);
  
  return ( OK );      
  }
  
  return ( OK );    
}

/*$RCSfile: changeUserCategory.c,v $*/


