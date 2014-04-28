//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: login() primary function source file 
// Date: 16/12/2004
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: login.c,v $
 * Revision 1.7  2005/02/16 22:11:21  marceloddm
 * CGI's added
 *
 * Revision 1.6  2004/12/21 20:26:02  marceloddm
 * Some corrections have been done
 *
 * Revision 1.5  2004/12/20 23:52:42  marceloddm
 * This function is almost finish
 * Next step: make the autenticateUser() function
 *
 * Revision 1.4  2004/12/20 12:50:03  marceloddm
 * Implementation of showHtmlErrorPage() function has been done
 *
 * Revision 1.3  2004/12/17 01:29:05  marceloddm
 * We must make the showHtmlErrorPage() to complete this function
 *
 * Revision 1.2  2004/12/17 00:26:07  marceloddm
 * Next step: include the new constants and make login.h
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mlcgi.h"
#include "const.h"
#include "types.h"
#include "error.h"
#include "config.h"
#include "functions.h"


static const char rcsid [] = "$Id: login.c,v 1.7 2005/02/16 22:11:21 marceloddm Exp marceloddm $";


int main (int argc, char **argv)
{
  unsigned errorCode;	
  char username [MAX_LENGTH_USERNAME + 1];
  char plainPass [MAX_LENGTH_PLAIN_PASS + 1];
  char cookieName[COOKIE_NAME_LENGTH +1];
  char cookieValue[COOKIE_VALUE_LENGTH +1];
  char cookieFileName[MAX_LENGTH_LONG_FILENAME +1];
  time_t cookieExpiration;

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
    
  if ((errorCode = mlCgiGetFormStringNoNewLines ("username", username, MAX_LENGTH_USERNAME)) != ML_CGI_OK)
  {
    mlCgiEndHttpHeader ();
    mlCgiFreeResources ();
    if (errorCode == ML_CGI_FORM_FIELD_NOT_FOUND)
      showHtmlErrorPage (FORM_USERNAME_NOT_FOUND);
    if (errorCode == ML_CGI_INVALID_FORM_LENGTH)
      showHtmlErrorPage (INVALID_FORM_USERNAME_LENGTH);
    exit (ML_CGI_OK);
  }

  if ((errorCode = mlCgiGetFormStringNoNewLines ("password", plainPass, MAX_LENGTH_PLAIN_PASS)) != ML_CGI_OK)
  {
    mlCgiEndHttpHeader ();
    mlCgiFreeResources ();
    if (errorCode == ML_CGI_FORM_FIELD_NOT_FOUND)
        showHtmlErrorPage (FORM_PLAIN_PASS_NOT_FOUND);
    if (errorCode == ML_CGI_INVALID_FORM_LENGTH)
        showHtmlErrorPage (INVALID_FORM_PLAIN_PASS_LENGTH);
    exit (ML_CGI_OK);
  }

  if ((errorCode = autenticateUser (username, plainPass)) != OK)
  {
    mlCgiEndHttpHeader ();
    mlCgiFreeResources ();
    showHtmlErrorPage (errorCode);
    exit (ML_CGI_OK);
  }

  if ((errorCode = verifyIfCookieFileExist (username, cookieName)) != OK)
    if (errorCode != VERIFY_IF_COOKIE_FILE_EXIST__COOKIE_FILE_DOES_NOT_EXIST)
	{
      mlCgiEndHttpHeader ();
      mlCgiFreeResources ();
      showHtmlErrorPage (errorCode);
      exit (ML_CGI_OK);
	}
  
  if (errorCode != VERIFY_IF_COOKIE_FILE_EXIST__COOKIE_FILE_DOES_NOT_EXIST)
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
  
  if ((errorCode = createRandomString (COOKIE_VALUE_VALID_CHARACTERS, COOKIE_VALUE_LENGTH, cookieValue)) != OK)
  {
    mlCgiEndHttpHeader();
    mlCgiFreeResources ();
    showHtmlErrorPage (errorCode);
    exit (ML_CGI_OK); 
  }
  
  cookieExpiration = COOKIE_EXPIRATION + time (NULL);   
  if ((errorCode = createNewCookieFile (cookieName, cookieValue, cookieExpiration, mlCgiEnvironmentVariablesValues[ML_CGI_REMOTE_ADDRESS])) != OK)
  {
    mlCgiEndHttpHeader();
    mlCgiFreeResources ();
    showHtmlErrorPage (errorCode);
    exit (ML_CGI_OK); 
  }
  
  if ((errorCode = mlCgiSetCookie (cookieName, cookieValue, COOKIE_EXPIRATION, NULL, NULL, NULL)) != ML_CGI_OK)
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
  mlCgiEndHttpHeader();
  mlCgiFreeResources ();
  
  showHtmlInitialPage (cookieName);

  exit (ML_CGI_OK);
}

/*$RCSfile: login.c,v $*/
