//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: cgiGetFriends() primary function source file 
// Date: 14/02/2005
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: cgiGetFriends.c,v $
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
#include "getFriends.h"


static const char rcsid [] = "$Id: cgiGetFriends.c,v 1.1 2005/02/16 22:11:21 marceloddm Exp marceloddm $";


int main (int argc, char **argv)
{
  unsigned errorCode;	
  char cookieName[COOKIE_NAME_LENGTH +1];
  char cookieValue[COOKIE_VALUE_LENGTH +1];
  char cookieFileName[MAX_LENGTH_LONG_FILENAME +1];
  char temp[20 +1];
  userIdType callerOfProgramId, givenId;
  userDataType buffer;
  userDataType *first, *last;

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
    showHtmlErrorPage (ONLY_THE_ADMINISTRATOR_CAN_GET_FRIENDS_OF_OTHERS_USERS);
    exit (ML_CGI_OK);
  }
  
  mlCgiEndHttpHeader();
  mlCgiFreeResources ();
  
  if ((errorCode = getFriends (givenId, &first)) != OK)
    showHtmlErrorPage (errorCode);
  else
  {
    #ifdef ENGLISH
      printf ("<HTML>\n");
      printf ("  <HEAD>\n");
      printf ("    <TITLE>Relationship System - List of friends</TITLE>\n");
      printf ("  </HEAD>\n");
      printf ("  <BODY BACKGROUND = \"http://www2.del.ufrj.br/~marceloddm/computacao_ii/pf/images/zertxtr.gif\" BGCOLOR = \"#000000\" TEXT = \"#FFFFFF\" LINK = \"#6699CC\" VLINK = \"#669966\" ALINK = \"#999999\">\n");
      printf ("    <DIV ALIGN = \"CENTER\"><STRONG><FONT FACE = \"Courier New\" SIZE = \"5\" COLOR = \"#FFFFFF\">RELATIONSHIP SYSTEM</FONT></STRONG></DIV>\n");
      printf ("    <HR>\n");
      printf ("    <CENTER><STRONG><FONT FACE = \"Courier New\" SIZE = \"4\" COLOR = \"#FFFFFF\">LIST OF FRIENDS</FONT></STRONG><CENTER>\n");
      printf ("    <HR>\n");
      printf ("    <BR><BR>\n");
      printf ("    <TABLE BORDER=\"1\" ALIGN = \"center\">\n");
      
      while (retrieveFIFO ( &first, &last, &buffer ) == OK) 
        printf ("       <TR><TD>User: %s</TD> <TD> <---> </TD> <TD>ID: %llu</TD></TR>\n", buffer.name, buffer.userId);
      freeFIFOResources (&first, &last);

      printf ("    </TABLE>\n");  	
      printf ("    <BR><BR><BR>\n");
      printf ("<P ALIGN=\"left\"><A HREF=\"javascript:window.history.go(-1)\" TARGET=\"_self\">GO BACK</a></p>\n");
      printf ("    <HR>\n");
      printf ("    <DIV ALIGN = \"RIGHT\"><FONT FACE = \"Courier New\" SIZE = \"2\"><U>Authors:</U>\n");
      printf ("    <I> Carlo Fragni and Marcelo Duffles Donato Moreira\n");
      printf ("    <BR>\n");
      printf ("    Last update: 14/02/05</I></FONT>\n");
      printf ("    </DIV></FONT>\n");
      printf ("  <BODY>\n");
      printf ("</HTML>\n");
    #elif PORTUGUESE
      printf ("<HTML>\n");
      printf ("  <HEAD>\n");
      printf ("    <TITLE>Sistema de Relacionamentos - Lista de amigos</TITLE>\n");
      printf ("  </HEAD>\n");
      printf ("  <BODY BACKGROUND = \"http://www2.del.ufrj.br/~marceloddm/computacao_ii/pf/images/zertxtr.gif\" BGCOLOR = \"#000000\" TEXT = \"#FFFFFF\" LINK = \"#6699CC\" VLINK = \"#669966\" ALINK = \"#999999\">\n");
      printf ("    <DIV ALIGN = \"CENTER\"><STRONG><FONT FACE = \"Courier New\" SIZE = \"5\" COLOR = \"#FFFFFF\">SISTEMA DE RELACIONAMENTOS</FONT></STRONG></DIV>\n");
      printf ("    <HR>\n");
      printf ("    <CENTER><STRONG><FONT FACE = \"Courier New\" SIZE = \"4\" COLOR = \"#FFFFFF\">LISTA DE AMIGOS</FONT></STRONG><CENTER>\n");
      printf ("    <HR>\n");
      printf ("    <BR><BR>\n");
      printf ("    <TABLE BORDER=\"1\" ALIGN = \"center\">\n");

      while (retrieveFIFO ( &first, &last, &buffer ) == OK) 
        printf ("       <TR><TD>Usuário: %s</TD> <TD> <---> </TD> <TD>ID: %llu</TD></TR>\n", buffer.name, buffer.userId);
      freeFIFOResources (&first, &last);

      printf ("    </TABLE>\n");  	
      printf ("    <BR><BR><BR>\n");
      printf ("<P ALIGN=\"left\"><A HREF=\"javascript:window.history.go(-1)\" TARGET=\"_self\">VOLTAR</a></p>\n");
      printf ("    <HR>\n");
      printf ("    <DIV ALIGN = \"RIGHT\"><FONT FACE = \"Courier New\" SIZE = \"2\"><U>Autores:</U>\n");
      printf ("    <I> Carlo Fragni e Marcelo Duffles Donato Moreira\n");
      printf ("    <BR>\n");
      printf ("    &Uacute;ltima Atualiza&ccedil;&atilde;o: 14/02/05</I></FONT>\n");
      printf ("    </DIV></FONT>\n");
      printf ("  <BODY>\n");
      printf ("</HTML>\n");
    #endif
  }  
        
  exit (ML_CGI_OK);
}

/*$RCSfile$*/
