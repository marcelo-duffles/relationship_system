//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Polit�cnica
// Departamento de Eletr�nica e de Computa��o
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: inviteUser() primary function source file 
// Date: 15/12/2004
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: inviteUser.c,v $
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
#include "help.h"
#include "functions.h"
#include "config.h"
#include "inviteUser.h"
#include "sendmail.h"
 
static const char rcsid [] = "$Id: inviteUser.c,v 1.1 2005/02/16 22:11:21 marceloddm Exp marceloddm $";
  
unsigned inviteUser (userIdType userId, char * name ,char * email )
{
  unsigned retCode;
  char tempFileName[MAX_LENGTH_LONG_FILENAME +1];
  char invitedUserFileName[MAX_LENGTH_LONG_FILENAME +1];
  FILE *writeFile, *readFile; 
  char plainPass[MAX_LENGTH_PLAIN_PASS+1];
  char encryptedPass[ENCRYPTED_PASS_LENGTH+1];
  char emailBody[500 +1];
  userDataType userData;
  
  if (( retCode = checkField ( name , NAME_VALID_CHARACTERS, MIN_LENGTH_NAME, MAX_LENGTH_NAME) ) != OK )
    return ( retCode );
    
  if (( retCode = checkField ( email , EMAIL_VALID_CHARACTERS, MIN_LENGTH_EMAIL, MAX_LENGTH_EMAIL) ) != OK )
    return ( retCode );  
    
  if ((retCode = getDataFromId (userId, &userData)) != OK)
    return (retCode);
    
  sprintf ( tempFileName , "%s" , email  );  
  
  if ((retCode = getLongFilename (DATA_DIR, tempFileName, invitedUserFileName)) != OK)
    return (retCode);
    
  if ((readFile = fopen (invitedUserFileName, "r")) != NULL)
  {
    fclose (readFile);
    return (INVITE_USER__USER_HAS_ALREADY_BEEN_INVITED);
  }
  
  if ((writeFile = fopen (invitedUserFileName, "w")) == NULL)
    return (INVITE_USER__ERROR_OPENING_INVITED_USER_FILE_FOR_WRITING);  
   
  if (( retCode = putString ( writeFile, MIN_LENGTH_NAME, MAX_LENGTH_NAME, name) ) != OK )
  {
    fclose ( writeFile );
    remove (invitedUserFileName);
    return ( retCode );
  }   
  
  if (( retCode = createRandomString ( PLAIN_PASS_VALID_CHARACTERS, NEW_PASSWORD_LENGTH, plainPass) ) != OK )
  {
    fclose ( writeFile );
    remove (invitedUserFileName);
    return ( retCode );
  }
  
  if (( retCode = encodePassword ( plainPass, encryptedPass) ) != OK )
  {
    fclose ( writeFile );
    remove (invitedUserFileName);
    return ( retCode );
  }
  
  if (( retCode = putString ( writeFile, ENCRYPTED_PASS_LENGTH, ENCRYPTED_PASS_LENGTH, encryptedPass) ) != OK )
  {
    fclose ( writeFile );
    remove (invitedUserFileName);
    return ( retCode );
  } 
  
  #ifdef ENGLISH
    snprintf (emailBody, 500, "\n\
      *** This is a system message, you don't need to reply! ***\n\
      \n\
      Dear %s,\n\
      \n\
        %s is inviting you to join our system.\n\
      \n\
        Go to http://www2.del.ufrj.br/~marceloddm/computacao_ii/pf/cgi/showNewUserLoginForm.cgi and answer this invitation.\n\
      \n\
        Your temporary password: %s\n\
      \n\
      \n\
      Our web site: http://www.del.ufrj.br/~marceloddm/computacao_ii/pf", name, userData.name, plainPass);
  #elif PORTUGUESE
    snprintf (emailBody, 500, "\n\
      *** Essa � uma mensagem de sistema, voc� n�o precisa respond�-la! ***\n\
      \n\
      Caro(a) %s,\n\
      \n\
        %s est� te convidando para entrar no nosso sistema.\n\
      \n\
        Visite o endere�o http://www2.del.ufrj.br/~marceloddm/computacao_ii/pf/cgi/showNewUserLoginForm.cgi e responda o convite.\n\
      \n\
        Sua senha provis�ria: %s\n\
      \n\
      \n\
      Nosso web site: http://www.del.ufrj.br/~marceloddm/computacao_ii/pf", name, userData.name, plainPass);  
  #endif
      
  if (sendMail (WEB_SERVER_DOMAIN, SMTP_SERVER_ADDRESS, SMTP_SERVER_PORT, ADMINISTRATOR_EMAIL, email, NULL, NULL, showTextHelpMessage (INVITE_USER__SUBJECT), emailBody, NULL) != OK)
    return (ERROR_SENDING_EMAIL);
    
  return ( OK );  
}

/*$RCSfile: inviteUser.c,v $*/


