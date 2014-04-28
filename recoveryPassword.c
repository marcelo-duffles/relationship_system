//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: recoveryPassword() primary function source file 
// Date: 24/12/2004
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: recoveryPassword.c,v $
 * Revision 1.2  2005/02/16 22:11:21  marceloddm
 * CGI's added
 *
 * Revision 1.1  2004/12/25 17:47:25  marceloddm
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
#include "help.h"
#include "functions.h"
#include "config.h"
#include "recoveryPassword.h"
#include "sendmail.h"

 
static const char rcsid [] = "$Id: recoveryPassword.c,v 1.2 2005/02/16 22:11:21 marceloddm Exp marceloddm $";
  
unsigned recoveryPassword ( userIdType userId )
{
  unsigned retCode, retCode2;
  char passwordFileName[MAX_LENGTH_LONG_FILENAME +1];
  char tempFileName[MAX_LENGTH_LONG_FILENAME +1];
  char newPassword [NEW_PASSWORD_LENGTH + 1];
  char encryptedNewPassword [ENCRYPTED_PASS_LENGTH + 1];
  char emailBody[500 +1];
  FILE *readFile, *writeFile;
  userDataType buffer;
  boolean found;
  
 /*PREPARING TO MAKE CHANGES IN THE PASSWORD FILE*/
   
 if ((retCode = getLongFilename (DATA_DIR, PASSWORD_FILE_NAME, passwordFileName)) != OK)
    return (retCode);
    
  if ((readFile = fopen (passwordFileName, "r")) == NULL)
  {
    if (errno != ENOENT)
      return (RECOVERY_PASSWORD__ERROR_OPENING_PASSWORD_FILE_FOR_READING);
    return (RECOVERY_PASSWORD__PASSWORD_FILE_DOES_NOT_EXIST);
  } 
  
  if ((retCode = getLongFilename (DATA_DIR, PASSWORD_TEMP_FILE_NAME, tempFileName)) != OK)
  {
    fclose (readFile);
    return (retCode);
  }  
    
  if ((writeFile = fopen (tempFileName, "w")) == NULL)
  {
    fclose ( readFile );
    return (RECOVERY_PASSWORD__ERROR_OPENING_PASSWORD_TEMP_FILE_FOR_WRITTING);   
  }
     
  found = false;
  
  for (retCode = 0; retCode != GET_USER_ID__END_OF_FILE;)  
  {
    if ((retCode = getUserData (readFile, PASSWORD_FILE_NAME, &buffer)) != OK) /*READING PASSWORD FILE*/
      if (retCode != GET_USER_ID__END_OF_FILE)
      {
        fclose (readFile);
	fclose (writeFile);
	remove (tempFileName);
        return (retCode);
      }
    if (retCode != GET_USER_ID__END_OF_FILE) 
    {
      if ( buffer.userId != userId ) /*JUST COPYING THE OTHER USERS DATA*/
      {
	if ((retCode2 = putUserData ( writeFile, PASSWORD_TEMP_FILE_NAME, &buffer )) != OK )
        {
	  fclose (readFile);
	  fclose (writeFile);
	  remove (tempFileName);
	  return (retCode2);
        }
      }
      if ( buffer.userId == userId )
      {  
        /*GENERATING NEW PASSWORD*/       
        if ((retCode2 = createRandomString ( RANDOM_STRING_VALID_CHARACTERS, NEW_PASSWORD_LENGTH, newPassword) ) != OK )
        {
	  fclose (readFile);
	  fclose (writeFile);
	  remove (tempFileName);
	  return (retCode2);
	}
	/*ENCRYPTING NEW PASSWORD*/
	if ((retCode2 = encodePassword ( newPassword, encryptedNewPassword) ) != OK )
	{
	  fclose (readFile);
	  fclose (writeFile);
	  remove (tempFileName);
	  return (retCode2);
	}
	
	stringCopy (buffer.encryptedPass, encryptedNewPassword, ENCRYPTED_PASS_LENGTH);
	
	/*UPDATING PASSWORD FILE WITH NEW PASSWORD*/
	if ((retCode2 = putUserData ( writeFile, PASSWORD_TEMP_FILE_NAME, &buffer )) != OK )
        {
	  fclose (readFile);
	  fclose (writeFile);
	  remove (tempFileName);
	  return (retCode2);
        }
	
	found = true;
      }
    }  
  }
  
  fclose ( readFile);
  fclose ( writeFile);
  
  if (! found ) /*NO USER FOUND WITH THE GIVEN USER ID IN THE PASSWORD FILE*/
  {
    remove (tempFileName);
    return ( RECOVERY_PASSWORD__USER_NOT_FOUND );
  }
  
  /*REPLACING FILES */
  
  rename (tempFileName, passwordFileName);
  
  if ((retCode = getDataFromId (userId, &buffer)) != OK)
    return (retCode);
    
  #ifdef ENGLISH
    snprintf (emailBody, 500, "\n\
      *** This is a system message, you don't need to reply! ***\n\
      \n\
      Dear %s,\n\
      \n\
        Your password has been changed to %s.\n\
      \n\
      \n\
      Our web site: http://www.del.ufrj.br/~marceloddm/computacao_ii/pf", buffer.name, newPassword);
  #elif PORTUGUESE
    snprintf (emailBody, 500, "\n\
      *** Essa é uma mensagem de sistema, você não precisa respondê-la! ***\n\
      \n\
      Caro(a) %s,\n\
      \n\
        Sua senha foi alterada para %s.\n\
      \n\
      \n\
      Nosso web site: http://www.del.ufrj.br/~marceloddm/computacao_ii/pf", buffer.name, newPassword);  
  #endif
      
  if (sendMail (WEB_SERVER_DOMAIN, SMTP_SERVER_ADDRESS, SMTP_SERVER_PORT, ADMINISTRATOR_EMAIL, buffer.email, NULL, NULL, showTextHelpMessage (RECOVERY_PASSWORD__SUBJECT), emailBody, NULL) != OK)
    return (ERROR_SENDING_EMAIL);
    
  
  return (OK);      
}

/*$RCSfile: recoveryPassword.c,v $*/


