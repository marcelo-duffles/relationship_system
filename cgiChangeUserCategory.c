//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: cgiChangeUserCategory() primary function source file 
// Date: 14/02/2005
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: cgiChangeUserCategory.c,v $
 * Revision 1.1  2005/02/16 22:11:21  marceloddm
 * Initial revision
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include "mlcgi.h"
#include "const.h"
#include "types.h"
#include "error.h"
#include "config.h"
#include "functions.h"
#include "changeUserCategory.h"


static const char rcsid [] = "$Id: cgiChangeUserCategory.c,v 1.1 2005/02/16 22:11:21 marceloddm Exp marceloddm $";


int main (int argc, char **argv)
{
  unsigned errorCode;	
  char cookieName[COOKIE_NAME_LENGTH +1];
  char cookieValue[COOKIE_VALUE_LENGTH +1];
  char cookieFileName[MAX_LENGTH_LONG_FILENAME +1];
  char temp[20 +1];
  userIdType callerOfProgramId, givenId;
  userDataType userData;

  if ((errorCode = mlCgiInitialize ()) != ML_CGI_OK)
  {
    if (errorCode == ML_CGI_FATAL_ERROR)
      showHtmlErrorPage (FATAL_ERROR);
    if (errorCode == ML_CGI_MEMORY_ALLOCATION_ERROR)
      showHtmlErrorPage (MEMORY_ALLOCATION_ERROR);
    if (errorCode == ML_CGI_INVALID_CONTENT_LENGTH)
      showHtmlErrorPage (INVALID_CONTENT_LENGTH);
    if (errorCode == ML_CGI_IO_ERROR)
      showHtmlErrorPage (CGI_IO_ERROR);
    if (errorCode == ML_CGI_INVALID_CONTENT_TYPE)
      showHtmlErrorPage (INVALID_CONTENT_TYPE);
    if (errorCode == ML_CGI_INVALID_REQUEST_METHOD)
      showHtmlErrorPage (INVALID_REQUEST_METHOD);
    exit (ML_CGI_OK);
  }

  if (!isCgi)
  {
    printf ("%s\n", showTextErrorMessage (IS_NOT_CGI));
    exit (ML_CGI_OK);
  }
	  
  mlCgiBeginHttpHeader ("text/html");
    
  if ((errorCode = mlCgiGetFormStringNoNewLines ("cookieName", cookieName, COOKIE_NAME_LENGTH)) != ML_CGI_OK)
  {
    mlCgiEndHttpHeader ();
    mlCgiFreeResources ();
    if (errorCode == ML_CGI_FORM_FIELD_NOT_FOUND)
      showHtmlErrorPage (FORM_FIELD_NOT_FOUND);
    if (errorCode == ML_CGI_INVALID_FORM_LENGTH)
      showHtmlErrorPage (INVALID_FORM_FIELD_LENGTH);
    exit (ML_CGI_OK);
  }

  if ((errorCode = mlCgiGetSpecificCookie (cookieName, COOKIE_NAME_LENGTH, cookieValue, COOKIE_VALUE_LENGTH)) != ML_CGI_OK)
  {
    mlCgiEndHttpHeader();
    mlCgiFreeResources ();
    if (errorCode == ML_CGI_INVALID_COOKIE_NAME)     
      showHtmlErrorPage (INVALID_COOKIE_NAME);
    if (errorCode == ML_CGI_INVALID_COOKIE_VALUE)
      showHtmlErrorPage (INVALID_COOKIE_VALUE);
    if (errorCode == ML_CGI_COOKIE_NOT_FOUND)
      showHtmlErrorPage (COOKIE_NOT_FOUND);
    exit (ML_CGI_OK); 
  }
  
  if ((errorCode = validateCookie (cookieName, cookieValue, mlCgiEnvironmentVariablesValues[ML_CGI_REMOTE_ADDRESS])) != OK)
  {
    if (errorCode != VALIDATE_COOKIE__COOKIE_FILE_DOES_NOT_EXIST)
    {
      if ((errorCode = getCookieValue (cookieName, cookieValue)) != OK)
      {
        mlCgiEndHttpHeader ();
        mlCgiFreeResources ();
        showHtmlErrorPage (errorCode);
        exit (ML_CGI_OK);
      }
      if ((errorCode = mlCgiSetCookie (cookieName, cookieValue, 0, NULL, NULL, NULL)) != ML_CGI_OK)
      {
        mlCgiEndHttpHeader();
        mlCgiFreeResources ();
        if (errorCode == ML_CGI_INVALID_COOKIE_NAME)     
          showHtmlErrorPage (INVALID_COOKIE_NAME);
        if (errorCode == ML_CGI_INVALID_COOKIE_VALUE)
          showHtmlErrorPage (INVALID_COOKIE_VALUE);
        if (errorCode == ML_CGI_INVALID_COOKIE_EXPIRATION)
          showHtmlErrorPage (INVALID_COOKIE_EXPIRATION);
        exit (ML_CGI_OK); 
      }
      if ((errorCode = getLongFilename (COOKIES_DIR, cookieName, cookieFileName)) != OK)
      {
        mlCgiEndHttpHeader();
        mlCgiFreeResources ();
        showHtmlErrorPage (errorCode);
        exit (ML_CGI_OK); 
      }
      remove (cookieFileName); 
    }
    mlCgiEndHttpHeader();
    mlCgiFreeResources ();
    showHtmlErrorPage (errorCode);
    exit (ML_CGI_OK); 
  }
  
  if ((errorCode = mlCgiGetFormStringNoNewLines ("userId", temp, 20)) != ML_CGI_OK)
  {
    mlCgiEndHttpHeader ();
    mlCgiFreeResources ();
    if (errorCode == ML_CGI_FORM_FIELD_NOT_FOUND)
      showHtmlErrorPage (FORM_USER_ID_NOT_FOUND);
    if (errorCode == ML_CGI_INVALID_FORM_LENGTH)
      showHtmlErrorPage (INVALID_FORM_USER_ID_LENGTH);
    exit (ML_CGI_OK);
  }
  givenId           = strtoul (temp, NULL, 10);
  callerOfProgramId = strtoul (cookieName, NULL, 10); 
  
  if ((callerOfProgramId != 0) && (givenId != callerOfProgramId))
  {
    mlCgiEndHttpHeader ();
    mlCgiFreeResources ();
    showHtmlErrorPage (ONLY_THE_ADMINISTRATOR_CAN_CHANGE_CATEGORY_OF_OTHERS_USERS);
    exit (ML_CGI_OK);
  }
  
  if ((errorCode = getDataFromId (givenId, &userData)) != OK)
  {
    mlCgiEndHttpHeader();
    mlCgiFreeResources ();
    showHtmlErrorPage (errorCode);
    exit (ML_CGI_OK);
  }
  
  if (userData.category == webUser)
    userData.category = relative;
  else
  {
    userData.category = webUser;
    if ((errorCode = mlCgiGetFormStringNoNewLines ("username", userData.userName, MAX_LENGTH_USERNAME)) != ML_CGI_OK)
    {
      mlCgiEndHttpHeader ();
      mlCgiFreeResources ();
      if (errorCode == ML_CGI_FORM_FIELD_NOT_FOUND)
        showHtmlErrorPage (FORM_USERNAME_NOT_FOUND);
      if (errorCode == ML_CGI_INVALID_FORM_LENGTH)
        showHtmlErrorPage (INVALID_FORM_USERNAME_LENGTH);
      exit (ML_CGI_OK);
    }
    if ((errorCode = mlCgiGetFormStringNoNewLines ("password", userData.plainPass, MAX_LENGTH_PLAIN_PASS)) != ML_CGI_OK)
    {
      mlCgiEndHttpHeader ();
      mlCgiFreeResources ();
      if (errorCode == ML_CGI_FORM_FIELD_NOT_FOUND)
        showHtmlErrorPage (FORM_PLAIN_PASS_NOT_FOUND);
      if (errorCode == ML_CGI_INVALID_FORM_LENGTH)
        showHtmlErrorPage (INVALID_FORM_PLAIN_PASS_LENGTH);
      exit (ML_CGI_OK);
    }
    if ((errorCode = mlCgiGetFormStringNoNewLines ("email", userData.email, MAX_LENGTH_EMAIL)) != ML_CGI_OK)
    {
      mlCgiEndHttpHeader ();
      mlCgiFreeResources ();
      if (errorCode == ML_CGI_FORM_FIELD_NOT_FOUND)
        showHtmlErrorPage (FORM_EMAIL_NOT_FOUND);
      if (errorCode == ML_CGI_INVALID_FORM_LENGTH)
        showHtmlErrorPage (INVALID_FORM_EMAIL_LENGTH);
      exit (ML_CGI_OK);
    }
  }
  
  mlCgiEndHttpHeader();
  mlCgiFreeResources ();
  
  if ((errorCode = changeUserCategory (&userData)) != OK)
    showHtmlErrorPage (errorCode);
  else
    showHtmlOKPage ();    
        
  exit (ML_CGI_OK);
}

/*$RCSfile$*/
