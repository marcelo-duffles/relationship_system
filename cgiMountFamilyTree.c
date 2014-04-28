//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: cgiMountFamilyTree() primary function source file 
// Date: 21/02/2005
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date$
 * $Log$
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
#include "mountFamilyTree.h"


static const char rcsid [] = "$Id$";


int main (int argc, char **argv)
{
  unsigned errorCode;	
  char cookieName[COOKIE_NAME_LENGTH +1];
  char cookieValue[COOKIE_VALUE_LENGTH +1];
  char cookieFileName[MAX_LENGTH_LONG_FILENAME +1];
  char temp[20 +1];
  unsigned bottom, top;
  userIdType callerOfProgramId, givenId;
  userDataType buffer;
  familyTreeType family, *user, *cursor, *currentSon, *currentBrother;

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
  givenId           = strtoul (temp,       NULL, 10);
  callerOfProgramId = strtoul (cookieName, NULL, 10); 
  
  if ((callerOfProgramId != 0) && (givenId != callerOfProgramId))
  {
    mlCgiEndHttpHeader ();
    mlCgiFreeResources ();
    showHtmlErrorPage (YOU_CAN_ONLY_MOUNT_YOUR_OWN_FAMILY);
    exit (ML_CGI_OK);
  }
  
  if ((errorCode = mlCgiGetFormStringNoNewLines ("bottom", temp, 20)) != ML_CGI_OK)
  {
    mlCgiEndHttpHeader ();
    mlCgiFreeResources ();
    if (errorCode == ML_CGI_FORM_FIELD_NOT_FOUND)
      showHtmlErrorPage (FORM_FIELD_NOT_FOUND);
    if (errorCode == ML_CGI_INVALID_FORM_LENGTH)
      showHtmlErrorPage (INVALID_FORM_FIELD_LENGTH);
    exit (ML_CGI_OK);
  }
  bottom = strtoul (temp, NULL, 10);
  
  if ((errorCode = mlCgiGetFormStringNoNewLines ("top", temp, 20)) != ML_CGI_OK)
  {
    mlCgiEndHttpHeader ();
    mlCgiFreeResources ();
    if (errorCode == ML_CGI_FORM_FIELD_NOT_FOUND)
      showHtmlErrorPage (FORM_FIELD_NOT_FOUND);
    if (errorCode == ML_CGI_INVALID_FORM_LENGTH)
      showHtmlErrorPage (INVALID_FORM_FIELD_LENGTH);
    exit (ML_CGI_OK);
  }
  top = strtoul (temp, NULL, 10);
  
  mlCgiEndHttpHeader();
  mlCgiFreeResources ();
  
  user = &family;
  if ((errorCode = mountFamilyTree (0 /*givenId*/,1 /* bottom*/,1 /*top*/, &user)) != OK)
    showHtmlErrorPage (errorCode);
  else
  {
    #ifdef ENGLISH
      printf ("<HTML>\n");
      printf ("  <HEAD>\n");
      printf ("    <TITLE>Relationship System - Family tree</TITLE>\n");
      printf ("  </HEAD>\n");
      printf ("  <BODY BACKGROUND = \"http://www2.del.ufrj.br/~marceloddm/computacao_ii/pf/images/zertxtr.gif\" BGCOLOR = \"#000000\" TEXT = \"#FFFFFF\" LINK = \"#6699CC\" VLINK = \"#669966\" ALINK = \"#999999\">\n");
      printf ("    <DIV ALIGN = \"CENTER\"><STRONG><FONT FACE = \"Courier New\" SIZE = \"5\" COLOR = \"#FFFFFF\">RELATIONSHIP SYSTEM</FONT></STRONG></DIV>\n");
      printf ("    <HR>\n");
      printf ("    <CENTER><STRONG><FONT FACE = \"Courier New\" SIZE = \"4\" COLOR = \"#FFFFFF\">FAMILY TREE</FONT></STRONG><CENTER>\n");
      printf ("    <HR>\n");
      printf ("    <BR><BR>\n");
      
      while ((cursor = retrieveFamily (&user)) != NULL)
      {
        printf ("    <TABLE BORDER=\"1\" ALIGN = \"center\">\n");
        getDataFromId (cursor->userId, &buffer);
        printf ("       <TR><TD>User: %s</TD> <TD> <---> </TD> <TD>ID: %llu</TD></TR>\n", buffer.name, buffer.userId);
	  
	if (cursor->parent != NULL)
	{
	  getDataFromId ((cursor->parent)->userId, &buffer);
          printf ("       <TR><TD>Parent1: %s</TD> <TD> <---> </TD> <TD>ID: %llu</TD></TR>\n", buffer.name, buffer.userId);
	    
	  if ((cursor->parent)->spouse != NULL)
	  {
	    getDataFromId (((cursor->parent)->spouse)->userId, &buffer);
            printf ("       <TR><TD>Parent2: %s</TD> <TD> <---> </TD> <TD>ID: %llu</TD></TR>\n", buffer.name, buffer.userId);
	  }
	}
	    
	if (cursor->spouse != NULL)
	{
	  getDataFromId ((cursor->spouse)->userId, &buffer);
          printf ("       <TR><TD>Spouse: %s</TD> <TD> <---> </TD> <TD>ID: %llu</TD></TR>\n", buffer.name, buffer.userId);
	}

        for (currentBrother = cursor->brother; currentBrother != NULL; currentBrother = currentBrother->brother)
	{
	  getDataFromId (currentBrother->userId, &buffer);
          printf ("       <TR><TD>Next brother/sister: %s</TD> <TD> <---> </TD> <TD>ID: %llu</TD></TR>\n", buffer.name, buffer.userId);
	}
	  
        for (currentSon = cursor->son; currentSon != NULL; currentSon = currentSon->brother)
	{
	  getDataFromId (currentSon->userId, &buffer);
          printf ("       <TR><TD>Son/daughter: %s</TD> <TD> <---> </TD> <TD>ID: %llu</TD></TR>\n", buffer.name, buffer.userId);
	}
        printf ("    </TABLE>\n");  	  
	printf ( "   <BR>\n");
      }  

      printf ("    <BR><BR><BR>\n");
      printf ("<P ALIGN=\"left\"><A HREF=\"javascript:window.history.go(-1)\" TARGET=\"_self\">GO BACK</a></p>\n");
      printf ("    <HR>\n");
      printf ("    <DIV ALIGN = \"RIGHT\"><FONT FACE = \"Courier New\" SIZE = \"2\"><U>Authors:</U>\n");
      printf ("    <I> Carlo Fragni and Marcelo Duffles Donato Moreira\n");
      printf ("    <BR>\n");
      printf ("    Last update: 21/02/05</I></FONT>\n");
      printf ("    </DIV></FONT>\n");
      printf ("  <BODY>\n");
      printf ("</HTML>\n");
    #elif PORTUGUESE
      printf ("<HTML>\n");
      printf ("  <HEAD>\n");
      printf ("    <TITLE>Sistema de Relacionamentos - &Aacute;rvore geneal&oacute;gica</TITLE>\n");
      printf ("  </HEAD>\n");
      printf ("  <BODY BACKGROUND = \"http://www2.del.ufrj.br/~marceloddm/computacao_ii/pf/images/zertxtr.gif\" BGCOLOR = \"#000000\" TEXT = \"#FFFFFF\" LINK = \"#6699CC\" VLINK = \"#669966\" ALINK = \"#999999\">\n");
      printf ("    <DIV ALIGN = \"CENTER\"><STRONG><FONT FACE = \"Courier New\" SIZE = \"5\" COLOR = \"#FFFFFF\">SISTEMA DE RELACIONAMENTOS</FONT></STRONG></DIV>\n");
      printf ("    <HR>\n");
      printf ("    <CENTER><STRONG><FONT FACE = \"Courier New\" SIZE = \"4\" COLOR = \"#FFFFFF\">&Aacute;RVORE GENEAL&Oacute;GICA</FONT></STRONG><CENTER>\n");
      printf ("    <HR>\n");
      printf ("    <BR><BR>\n");

	  exit (0);
	  
      while ((cursor = retrieveFamily (&user)) != NULL)
      {
        printf ("    <TABLE BORDER=\"1\" ALIGN = \"center\">\n");
        getDataFromId (cursor->userId, &buffer);
        printf ("       <TR><TD>User: %s</TD> <TD> <---> </TD> <TD>ID: %llu</TD></TR>\n", buffer.name, buffer.userId);
	  
	if (cursor->parent != NULL)
	{
	  getDataFromId ((cursor->parent)->userId, &buffer);
          printf ("       <TR><TD>Parent1: %s</TD> <TD> <---> </TD> <TD>ID: %llu</TD></TR>\n", buffer.name, buffer.userId);
	    
	  if ((cursor->parent)->spouse != NULL)
	  {
	    getDataFromId (((cursor->parent)->spouse)->userId, &buffer);
            printf ("       <TR><TD>Parent2: %s</TD> <TD> <---> </TD> <TD>ID: %llu</TD></TR>\n", buffer.name, buffer.userId);
	  }
	}
	    
	if (cursor->spouse != NULL)
	{
	  getDataFromId ((cursor->spouse)->userId, &buffer);
          printf ("       <TR><TD>Spouse: %s</TD> <TD> <---> </TD> <TD>ID: %llu</TD></TR>\n", buffer.name, buffer.userId);
	}

        for (currentBrother = cursor->brother; currentBrother != NULL; currentBrother = currentBrother->brother)
	{
	  getDataFromId (currentBrother->userId, &buffer);
          printf ("       <TR><TD>Next brother/sister: %s</TD> <TD> <---> </TD> <TD>ID: %llu</TD></TR>\n", buffer.name, buffer.userId);
	}
	  
        for (currentSon = cursor->son; currentSon != NULL; currentSon = currentSon->brother)
	{
	  getDataFromId (currentSon->userId, &buffer);
          printf ("       <TR><TD>Son/daughter: %s</TD> <TD> <---> </TD> <TD>ID: %llu</TD></TR>\n", buffer.name, buffer.userId);
	}
        printf ("    </TABLE>\n");  	  
	printf ( "   <BR>\n");
      }  

      printf ("    <BR><BR><BR>\n");
      printf ("<P ALIGN=\"left\"><A HREF=\"javascript:window.history.go(-1)\" TARGET=\"_self\">VOLTAR</a></p>\n");
      printf ("    <HR>\n");
      printf ("    <DIV ALIGN = \"RIGHT\"><FONT FACE = \"Courier New\" SIZE = \"2\"><U>Autores:</U>\n");
      printf ("    <I> Carlo Fragni e Marcelo Duffles Donato Moreira\n");
      printf ("    <BR>\n");
      printf ("    &Uacute;ltima Atualiza&ccedil;&atilde;o: 21/02/05</I></FONT>\n");
      printf ("    </DIV></FONT>\n");
      printf ("  <BODY>\n");
      printf ("</HTML>\n");
    #endif
  }  
        
  exit (ML_CGI_OK);
}

/*$RCSfile$*/
