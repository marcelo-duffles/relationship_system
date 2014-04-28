//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: cgiNewUser() primary function source file 
// Date: 14/02/2005
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: cgiNewUser.c,v $
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
#include "addUser.h"


static const char rcsid [] = "$Id: cgiNewUser.c,v 1.1 2005/02/16 22:11:21 marceloddm Exp marceloddm $";


int main (int argc, char **argv)
{
  unsigned errorCode;	
  char temp[10 +1];
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
    
  if ((errorCode = mlCgiGetFormStringNoNewLines ("category", temp, 10)) != ML_CGI_OK)
  {
    mlCgiEndHttpHeader ();
    mlCgiFreeResources ();
    if (errorCode == ML_CGI_FORM_FIELD_NOT_FOUND)
      showHtmlErrorPage (FORM_FIELD_NOT_FOUND);
    if (errorCode == ML_CGI_INVALID_FORM_LENGTH)
      showHtmlErrorPage (INVALID_FORM_FIELD_LENGTH);
    exit (ML_CGI_OK);
  }
  if (!strcmp (temp, "webUser"))
    userData.category = webUser;
  else 
    userData.category = relative;
    
  if (userData.category == webUser)  
  {
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
  }
  else
    userData.userName[0] = EOS;
    
  if (userData.category == webUser)  
  {
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
  }
  else
    userData.plainPass[0] = EOS;
   
  if (userData.category == webUser)  
  { 
    if ((errorCode = encodePassword (userData.plainPass, userData.encryptedPass)) != OK)
    {
      mlCgiEndHttpHeader ();
      mlCgiFreeResources ();
      showHtmlErrorPage (errorCode);
      exit (ML_CGI_OK);
    }
  }
  else
    userData.encryptedPass[0] = EOS;

    
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
  
  if ((errorCode = addUser (&userData)) != OK)
    showHtmlErrorPage (errorCode);
  else
    showHtmlOKPage ();   
    
  remove (userData.email); 
        
  exit (ML_CGI_OK);
}

/*$RCSfile$*/
