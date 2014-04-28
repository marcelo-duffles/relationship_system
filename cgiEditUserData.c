//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: cgiEditUserData() primary function source file 
// Date: 13/02/2005
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: cgiEditUserData.c,v $
 * Revision 1.1  2005/02/16 22:11:21  marceloddm
 * Initial revision
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mlcgi.h"
#include "const.h"
#include "types.h"
#include "error.h"
#include "config.h"
#include "functions.h"
#include "editUserData.h"


static const char rcsid [] = "$Id: cgiEditUserData.c,v 1.1 2005/02/16 22:11:21 marceloddm Exp marceloddm $";


int main (int argc, char **argv)
{
  unsigned errorCode;	
  char cookieName[COOKIE_NAME_LENGTH +1];
  char cookieValue[COOKIE_VALUE_LENGTH +1];
  char cookieFileName[MAX_LENGTH_LONG_FILENAME +1];
  char temp[10 +1];
  char givenId[20 +1];
  userDataType userData;
  userIdType callerOfProgramId;

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
  
  if ((errorCode = mlCgiGetFormStringNoNewLines ("userId", givenId, 20)) != ML_CGI_OK)
  {
    mlCgiEndHttpHeader ();
    mlCgiFreeResources ();
    if (errorCode == ML_CGI_FORM_FIELD_NOT_FOUND)
      showHtmlErrorPage (FORM_USER_ID_NOT_FOUND);
    if (errorCode == ML_CGI_INVALID_FORM_LENGTH)
      showHtmlErrorPage (INVALID_FORM_USER_ID_LENGTH);
    exit (ML_CGI_OK);
  }
  userData.userId   = strtoul (givenId   , NULL, 10);
  callerOfProgramId = strtoul (cookieName, NULL, 10); 
  
  if ((callerOfProgramId != 0) && (userData.userId != callerOfProgramId))
  {
    mlCgiEndHttpHeader ();
    mlCgiFreeResources ();
    showHtmlErrorPage (ONLY_THE_ADMINISTRATOR_CAN_EDIT_DATA_OF_OTHERS_USERS);
    exit (ML_CGI_OK);
  }
  
  if ((errorCode = getDataFromId (userData.userId, &userData)) != OK)
  {
    mlCgiEndHttpHeader ();
    mlCgiFreeResources ();
    showHtmlErrorPage (errorCode);
    exit (ML_CGI_OK);
  }
    
  if ((errorCode = mlCgiGetFormStringNoNewLines ("name", userData.name, MAX_LENGTH_NAME)) != ML_CGI_OK)
  {
    mlCgiEndHttpHeader ();
    mlCgiFreeResources ();
    if (errorCode == ML_CGI_FORM_FIELD_NOT_FOUND)
      showHtmlErrorPage (FORM_NAME_NOT_FOUND);
    if (errorCode == ML_CGI_INVALID_FORM_LENGTH)
      showHtmlErrorPage (INVALID_FORM_NAME_LENGTH);
    exit (ML_CGI_OK);
  }
  
  if (userData.category == webUser)  
  {
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
  else
  {
    errorCode = mlCgiGetFormStringNoNewLines ("email", userData.email, MAX_LENGTH_EMAIL);
    if (errorCode == ML_CGI_FORM_FIELD_NOT_FOUND)
      userData.email[0] = EOS;
    if (errorCode != ML_CGI_OK)
    {
      mlCgiEndHttpHeader ();
      mlCgiFreeResources ();
      if (errorCode == ML_CGI_INVALID_FORM_LENGTH)
       showHtmlErrorPage (INVALID_FORM_EMAIL_LENGTH);
      exit (ML_CGI_OK);
    }
  }
    

  errorCode = mlCgiGetFormStringNoNewLines ("homepage", userData.homepage, MAX_LENGTH_HOMEPAGE);
  if (errorCode == ML_CGI_FORM_FIELD_NOT_FOUND)
    userData.homepage[0] = EOS;
  if (errorCode != ML_CGI_OK)
  {
    mlCgiEndHttpHeader ();
    mlCgiFreeResources ();
    if (errorCode == ML_CGI_INVALID_FORM_LENGTH)
      showHtmlErrorPage (INVALID_FORM_HOMEPAGE_LENGTH);
    exit (ML_CGI_OK);
  }
  
  errorCode = mlCgiGetFormStringNoNewLines ("street", userData.address.street, MAX_LENGTH_STREET);
  if (errorCode == ML_CGI_FORM_FIELD_NOT_FOUND)
    userData.address.street[0] = EOS;
  if (errorCode != ML_CGI_OK)
  {
    mlCgiEndHttpHeader ();
    mlCgiFreeResources ();
    if (errorCode == ML_CGI_INVALID_FORM_LENGTH)
      showHtmlErrorPage (INVALID_FORM_STREET_LENGTH);
    exit (ML_CGI_OK);
  }
  
  errorCode = mlCgiGetFormStringNoNewLines ("homeNumber", userData.address.homeNumber, MAX_LENGTH_HOME_NUMBER);
  if (errorCode == ML_CGI_FORM_FIELD_NOT_FOUND)
    userData.address.homeNumber[0] = EOS;
  if (errorCode != ML_CGI_OK)
  {
    mlCgiEndHttpHeader ();
    mlCgiFreeResources ();
    if (errorCode == ML_CGI_INVALID_FORM_LENGTH)
      showHtmlErrorPage (INVALID_FORM_HOME_NUMBER_LENGTH);
    exit (ML_CGI_OK);
  }
  
  errorCode = mlCgiGetFormStringNoNewLines ("complement", userData.address.complement, MAX_LENGTH_COMPLEMENT);
  if (errorCode == ML_CGI_FORM_FIELD_NOT_FOUND)
    userData.address.complement[0] = EOS;
  if (errorCode != ML_CGI_OK)
  {
    mlCgiEndHttpHeader ();
    mlCgiFreeResources ();
    if (errorCode == ML_CGI_INVALID_FORM_LENGTH)
      showHtmlErrorPage (INVALID_FORM_COMPLEMENT_LENGTH);
    exit (ML_CGI_OK);
  }
  
  errorCode = mlCgiGetFormStringNoNewLines ("district", userData.address.district, MAX_LENGTH_DISTRICT);
  if (errorCode == ML_CGI_FORM_FIELD_NOT_FOUND)
    userData.address.district[0] = EOS;
  if (errorCode != ML_CGI_OK)
  {
    mlCgiEndHttpHeader ();
    mlCgiFreeResources ();
    if (errorCode == ML_CGI_INVALID_FORM_LENGTH)
      showHtmlErrorPage (INVALID_FORM_DISTRICT_LENGTH);
    exit (ML_CGI_OK);
  }
  
  errorCode = mlCgiGetFormStringNoNewLines ("city", userData.address.city, MAX_LENGTH_CITY);
  if (errorCode == ML_CGI_FORM_FIELD_NOT_FOUND)
    userData.address.city[0] = EOS;
  if (errorCode != ML_CGI_OK)
  {
    mlCgiEndHttpHeader ();
    mlCgiFreeResources ();
    if (errorCode == ML_CGI_INVALID_FORM_LENGTH)
      showHtmlErrorPage (INVALID_FORM_CITY_LENGTH);
    exit (ML_CGI_OK);
  }
  
  errorCode = mlCgiGetFormStringNoNewLines ("state", userData.address.state, MAX_LENGTH_STATE);
  if (errorCode == ML_CGI_FORM_FIELD_NOT_FOUND)
    userData.address.homeNumber[0] = EOS;
  if (errorCode != ML_CGI_OK)
  {
    mlCgiEndHttpHeader ();
    mlCgiFreeResources ();
    if (errorCode == ML_CGI_INVALID_FORM_LENGTH)
      showHtmlErrorPage (INVALID_FORM_STATE_LENGTH);
    exit (ML_CGI_OK);
  }
  
  errorCode = mlCgiGetFormStringNoNewLines ("country", userData.address.country, MAX_LENGTH_COUNTRY);
  if (errorCode == ML_CGI_FORM_FIELD_NOT_FOUND)
    userData.address.country[0] = EOS;
  if (errorCode != ML_CGI_OK)
  {
    mlCgiEndHttpHeader ();
    mlCgiFreeResources ();
    if (errorCode == ML_CGI_INVALID_FORM_LENGTH)
      showHtmlErrorPage (INVALID_FORM_COUNTRY_LENGTH);
    exit (ML_CGI_OK);
  }
  
  errorCode = mlCgiGetFormStringNoNewLines ("zipCode", userData.address.zipCode, MAX_LENGTH_ZIP_CODE);
  if (errorCode == ML_CGI_FORM_FIELD_NOT_FOUND)
    userData.address.zipCode[0] = EOS;
  if (errorCode != ML_CGI_OK)
  {
    mlCgiEndHttpHeader ();
    mlCgiFreeResources ();
    if (errorCode == ML_CGI_INVALID_FORM_LENGTH)
      showHtmlErrorPage (INVALID_FORM_ZIP_CODE_LENGTH);
    exit (ML_CGI_OK);
  }
  
  errorCode = mlCgiGetFormStringNoNewLines ("telNumber", userData.telNumber, MAX_LENGTH_TEL_NUMBER);
  if (errorCode == ML_CGI_FORM_FIELD_NOT_FOUND)
    userData.telNumber[0] = EOS;
  if (errorCode != ML_CGI_OK)
  {
    mlCgiEndHttpHeader ();
    mlCgiFreeResources ();
    if (errorCode == ML_CGI_INVALID_FORM_LENGTH)
      showHtmlErrorPage (INVALID_FORM_TEL_NUMBER_LENGTH);
    exit (ML_CGI_OK);
  }
  
  errorCode = mlCgiGetFormStringNoNewLines ("cellNumber", userData.cellNumber, MAX_LENGTH_CELL_NUMBER);
  if (errorCode == ML_CGI_FORM_FIELD_NOT_FOUND)
    userData.cellNumber[0] = EOS;
  if (errorCode != ML_CGI_OK)
  {
    mlCgiEndHttpHeader ();
    mlCgiFreeResources ();
    if (errorCode == ML_CGI_INVALID_FORM_LENGTH)
      showHtmlErrorPage (INVALID_FORM_CELL_NUMBER_LENGTH);
    exit (ML_CGI_OK);
  }
  
  errorCode = mlCgiGetFormStringNoNewLines ("gender", temp, 10);
  if (errorCode == ML_CGI_FORM_FIELD_NOT_FOUND)
    userData.gender = notAnswered;
  if (errorCode != ML_CGI_OK)
  {
    mlCgiEndHttpHeader ();
    mlCgiFreeResources ();
    if (errorCode == ML_CGI_INVALID_FORM_LENGTH)
      showHtmlErrorPage (INVALID_FORM_GENDER_LENGTH);
    exit (ML_CGI_OK);
  }
  if (!strcmp (temp, "male"))
    userData.gender = male;
  else if
    (!strcmp (temp, "female"))
      userData.gender = female;
  else
    userData.gender = notAnswered;

  errorCode = mlCgiGetFormStringNoNewLines ("relationshipStatus", temp, 10);
  if (errorCode == ML_CGI_FORM_FIELD_NOT_FOUND)
    userData.relationshipStatus = notGiven;
  if (errorCode != ML_CGI_OK)
  {
    mlCgiEndHttpHeader ();
    mlCgiFreeResources ();
    if (errorCode == ML_CGI_INVALID_FORM_LENGTH)
      showHtmlErrorPage (INVALID_FORM_RELATIONSHIP_STATUS_LENGTH);
    exit (ML_CGI_OK);
  }
  if (!strcmp (temp, "single"))
    userData.relationshipStatus = single;
  else if
    (!strcmp (temp, "married"))
      userData.relationshipStatus = married;
  else if
    (!strcmp (temp, "widowed"))
      userData.relationshipStatus = widowed;
  else
    userData.relationshipStatus = notGiven;

  if ((errorCode = mlCgiGetFormStringNoNewLines ("birthday", userData.birthday, MAX_LENGTH_BIRTHDAY)) != ML_CGI_OK)
  {
    mlCgiEndHttpHeader ();
    mlCgiFreeResources ();
    if (errorCode == ML_CGI_FORM_FIELD_NOT_FOUND)
      showHtmlErrorPage (FORM_BIRTHDAY_NOT_FOUND);
    if (errorCode == ML_CGI_INVALID_FORM_LENGTH)
      showHtmlErrorPage (INVALID_FORM_BIRTHDAY_LENGTH);
    exit (ML_CGI_OK);
  }
  
  errorCode = mlCgiGetFormStringNoNewLines ("description", userData.description, MAX_LENGTH_DESCRIPTION);
  if (errorCode == ML_CGI_FORM_FIELD_NOT_FOUND)
    userData.description[0] = EOS;
  if (errorCode != ML_CGI_OK)
  {
    mlCgiEndHttpHeader ();
    mlCgiFreeResources ();
    if (errorCode == ML_CGI_INVALID_FORM_LENGTH)
      showHtmlErrorPage (INVALID_FORM_DESCRIPTION_LENGTH);
    exit (ML_CGI_OK);
  }
  
  mlCgiEndHttpHeader();
  mlCgiFreeResources ();

  if (userData.category == relative)
  {
    userData.userName[0] = EOS;
	userData.plainPass[0] = EOS;
	userData.encryptedPass[0] = EOS;
  }
  else
  {
    strcpy (userData.plainPass, "noPass");
	if ((errorCode = encodePassword (userData.plainPass, userData.encryptedPass)) != OK)
	{
      showHtmlErrorPage (errorCode);
	  exit (ML_CGI_OK);
	}
  }		  
  
  if ((errorCode = editUserData (&userData)) != OK)
    showHtmlErrorPage (errorCode);
  else
    showHtmlOKPage ();    
        
  exit (ML_CGI_OK);
}

/*$RCSfile$*/
