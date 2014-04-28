//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Polit�cnica
// Departamento de Eletr�nica e de Computa��o
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: showAddUserForm() primary function source file 
// Date: 13/02/2005
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: showAddUserForm.c,v $
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


static const char rcsid [] = "$Id: showAddUserForm.c,v 1.1 2005/02/16 22:11:21 marceloddm Exp marceloddm $";


int main (int argc, char **argv)
{
  unsigned errorCode;	
  char cookieName[COOKIE_NAME_LENGTH +1];
  char cookieValue[COOKIE_VALUE_LENGTH +1];
  char cookieFileName[MAX_LENGTH_LONG_FILENAME +1];

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

  mlCgiEndHttpHeader();
  mlCgiFreeResources ();
  
  #ifdef ENGLISH
    printf ("<HTML>\n");
    printf ("  <HEAD>\n");
    printf ("    <TITLE>Relationship System - Form to add a user to the system </TITLE>\n");
    printf ("  </HEAD>\n");
    printf ("  <BODY BACKGROUND = \"http://www2.del.ufrj.br/~marceloddm/computacao_ii/pf/images/zertxtr.gif\" BGCOLOR = \"#000000\" TEXT = \"#FFFFFF\" LINK = \"#6699CC\" VLINK = \"#669966\" ALINK = \"#999999\">\n");
    printf ("    <DIV ALIGN = \"CENTER\"><STRONG><FONT FACE = \"Courier New\" SIZE = \"5\" COLOR = \"#FFFFFF\">RELATIONSHIP SYSTEM</FONT></STRONG></DIV>\n");
    printf ("    <HR>\n");
    printf ("    <CENTER><STRONG><FONT FACE = \"Courier New\" SIZE = \"4\" COLOR = \"#FFFFFF\">FORM TO ADD A USER TO THE SYSTEM</FONT></STRONG><CENTER>\n");
    printf ("    <HR>\n");
    printf ("    <BR>\n");
    printf ("    <DIV ALIGN = \"CENTER\"><FONT SIZE=\"2\">\n");
    printf ("       <I>Fields with * are obrigatory for all categories.\n");
    printf ("    <BR>\n");
    printf ("          Fields with ** are obrigatory only for WEB USERS.</I>\n");
    printf ("    </DIV>\n");
    printf ("    <BR>\n");
    printf ("    <TABLE BORDER=\"1\" ALIGN = \"center\">\n");
    printf ("    <FORM ACTION=\"http://www2.del.ufrj.br/~marceloddm/computacao_ii/pf/cgi/addUser.cgi\" METHOD=\"post\">\n");
    printf ("                      <INPUT TYPE=\"hidden\"   NAME=\"cookieName\" VALUE=\"%s\">\n", cookieName);
    printf ("       <TR><TD>Username**: </TD>     <TD><INPUT TYPE=\"text\"     NAME=\"username\"   SIZE=\"%i\"  ></TD></TR>\n", MAX_LENGTH_USERNAME);
    printf ("       <TR><TD>Password**: </TD>     <TD><INPUT TYPE=\"password\" NAME=\"password\"   SIZE=\"%i\"  ></TD></TR>\n", MAX_LENGTH_PLAIN_PASS);
    printf ("       <TR><TD>Web user: </TD>     <TD><INPUT TYPE=\"radio\"    NAME=\"category\" VALUE=\"webUser\" CHECKED></TD></TR>\n");
    printf ("       <TR><TD>Relative: </TD>     <TD><INPUT TYPE=\"radio\"    NAME=\"category\" VALUE=\"relative\"></TD></TR>\n"); 
    printf ("       <TR><TD>Full name*: </TD>    <TD><INPUT TYPE=\"text\"     NAME=\"name\"       SIZE=\"40\"  ></TD></TR>\n");  
    printf ("       <TR><TD>Email**: </TD>        <TD><INPUT TYPE=\"text\"     NAME=\"email\"      SIZE=\"40\"  ></TD></TR>\n");
    printf ("       <TR><TD>Homepage: </TD>     <TD><INPUT TYPE=\"text\"     NAME=\"homepage\"   SIZE=\"40\"  ></TD></TR>\n");
    printf ("       <TR><TD>Street: </TD>       <TD><INPUT TYPE=\"text\"     NAME=\"street\"     SIZE=\"40\"  ></TD></TR>\n");  					
    printf ("       <TR><TD>Home number: </TD>  <TD><INPUT TYPE=\"text\"     NAME=\"homeNumber\" SIZE=\"%i\"  ></TD></TR>\n", MAX_LENGTH_HOME_NUMBER);
    printf ("       <TR><TD>Complement: </TD>   <TD><INPUT TYPE=\"text\"     NAME=\"complement\" SIZE=\"40\"  ></TD></TR>\n");   
    printf ("       <TR><TD>District: </TD>     <TD><INPUT TYPE=\"text\"     NAME=\"district\"   SIZE=\"40\"  ></TD></TR>\n"); 
    printf ("       <TR><TD>City: </TD>         <TD><INPUT TYPE=\"text\"     NAME=\"city\"       SIZE=\"40\"  ></TD></TR>\n"); 
    printf ("       <TR><TD>State: </TD>        <TD><INPUT TYPE=\"text\"     NAME=\"state\"      SIZE=\"40\"  ></TD></TR>\n"); 
    printf ("       <TR><TD>Country: </TD>      <TD><INPUT TYPE=\"text\"     NAME=\"country\"    SIZE=\"40\"  ></TD></TR>\n");
    printf ("       <TR><TD>ZIP CODE: </TD>     <TD><INPUT TYPE=\"text\"     NAME=\"zipCode\"    SIZE=\"%i\"  ></TD></TR>\n", MAX_LENGTH_ZIP_CODE);   				
    printf ("       <TR><TD>Telphone: </TD>     <TD><INPUT TYPE=\"text\"     NAME=\"telNumber\"  SIZE=\"%i\"  ></TD></TR>\n", MAX_LENGTH_TEL_NUMBER);
    printf ("       <TR><TD>Cellphone: </TD>    <TD><INPUT TYPE=\"text\"     NAME=\"cellNumber\" SIZE=\"%i\"  ></TD></TR>\n", MAX_LENGTH_CELL_NUMBER);
    printf ("       <TR><TD>Male: </TD>         <TD><INPUT TYPE=\"radio\"    NAME=\"gender\" VALUE=\"male\"  ></TD></TR>\n");
    printf ("       <TR><TD>Female: </TD>       <TD><INPUT TYPE=\"radio\"    NAME=\"gender\" VALUE=\"female\"></TD></TR>\n");
    printf ("       <TR><TD>Single: </TD>       <TD><INPUT TYPE=\"radio\"    NAME=\"relationshipStatus\" VALUE=\"single\"></TD></TR>\n");
    printf ("       <TR><TD>Married: </TD>      <TD><INPUT TYPE=\"radio\"    NAME=\"relationshipStatus\" VALUE=\"married\"></TD></TR>\n");
    printf ("       <TR><TD>Widowed: </TD>      <TD><INPUT TYPE=\"radio\"    NAME=\"relationshipStatus\" VALUE=\"widowed\"></TD></TR>\n");        
    printf ("       <TR><TD>Date of birth*: </TD><TD><INPUT TYPE=\"text\"     NAME=\"birthday\"      SIZE=\"8\"> (DDMMYYYY)</TD></TR>\n"); 
    printf ("       <TR><TD>Description: </TD>  <TD><INPUT TYPE=\"text\"     NAME=\"description\"   SIZE=\"40\"  ></TD></TR>\n");  
    printf ("    </TABLE>\n");  	
    printf ("    <BR><BR>\n");
    printf ("                      <INPUT TYPE=\"submit\"   VALUE=\"Submit\">\n");
    printf ("                      <INPUT TYPE=\"reset\"    VALUE=\"Clear\">\n");
    printf ("    </FORM>\n");
    printf ("    <BR><BR><BR>\n");
    printf ("<P ALIGN=\"left\"><A HREF=\"javascript:window.history.go(-1)\" TARGET=\"_self\">GO BACK</a></p>\n");
    printf ("    <HR>\n");
    printf ("    <DIV ALIGN = \"RIGHT\"><FONT FACE = \"Courier New\" SIZE = \"2\"><U>Authors:</U>\n");
    printf ("    <I> Carlo Fragni and Marcelo Duffles Donato Moreira\n");
    printf ("    <BR>\n");
    printf ("    Last update: 13/02/05</I></FONT>\n");
    printf ("    </DIV></FONT>\n");
    printf ("  <BODY>\n");
    printf ("</HTML>\n");
  #elif PORTUGUESE
    printf ("<HTML>\n");
    printf ("  <HEAD>\n");
    printf ("    <TITLE>Sistema de Relacionamentos - Formul&aacute;rio para adicionar usu&aacute;rio ao sistema</TITLE>\n");
    printf ("  </HEAD>\n");
    printf ("  <BODY BACKGROUND = \"http://www2.del.ufrj.br/~marceloddm/computacao_ii/pf/images/zertxtr.gif\" BGCOLOR = \"#000000\" TEXT = \"#FFFFFF\" LINK = \"#6699CC\" VLINK = \"#669966\" ALINK = \"#999999\">\n");
    printf ("    <DIV ALIGN = \"CENTER\"><STRONG><FONT FACE = \"Courier New\" SIZE = \"5\" COLOR = \"#FFFFFF\">SISTEMA DE RELACIONAMENTOS</FONT></STRONG></DIV>\n");
    printf ("    <HR>\n");
    printf ("    <CENTER><STRONG><FONT FACE = \"Courier New\" SIZE = \"4\" COLOR = \"#FFFFFF\">FORMUL&Aacute;RIO PARA ADICIONAR USU&Aacute;RIO AO SISTEMA</FONT></STRONG><CENTER>\n");
    printf ("    <HR>\n");
    printf ("    <BR>\n");
    printf ("    <DIV ALIGN = \"CENTER\"><FONT SIZE=\"2\">\n");
    printf ("       <I>Campos marcados com * s&atilde;o obrigat&oacute;rios para todas as categorias.\n");
    printf ("    <BR>\n");
    printf ("          Campos marcados com ** s&atilde;o obrigat&oacute;rios somente para usu&aacute;rios web.</I>\n");
    printf ("    </DIV>\n");
    printf ("    <BR>\n");
    printf ("    <TABLE BORDER=\"1\" ALIGN = \"center\">\n");
    printf ("    <FORM ACTION=\"http://www2.del.ufrj.br/~marceloddm/computacao_ii/pf/cgi/addUser.cgi\" METHOD=\"post\">\n");
    printf ("                      <INPUT TYPE=\"hidden\"   NAME=\"cookieName\" VALUE=\"%s\">\n", cookieName);
    printf ("       <TR><TD>Username**: </TD>     <TD><INPUT TYPE=\"text\"     NAME=\"username\"   SIZE=\"%i\"  ></TD></TR>\n", MAX_LENGTH_USERNAME);
    printf ("       <TR><TD>Senha**: </TD>        <TD><INPUT TYPE=\"password\" NAME=\"password\"   SIZE=\"%i\"  ></TD></TR>\n", MAX_LENGTH_PLAIN_PASS);
    printf ("       <TR><TD>Usu�rio web: </TD>  <TD><INPUT TYPE=\"radio\"    NAME=\"category\" VALUE=\"webUser\" CHECKED></TD></TR>\n");
    printf ("       <TR><TD>Parente: </TD>      <TD><INPUT TYPE=\"radio\"    NAME=\"category\" VALUE=\"relative\"></TD></TR>\n"); 
    printf ("       <TR><TD>Nome completo*: </TD><TD><INPUT TYPE=\"text\"     NAME=\"name\"       SIZE=\"40\"  ></TD></TR>\n");  
    printf ("       <TR><TD>Email**: </TD>        <TD><INPUT TYPE=\"text\"     NAME=\"email\"      SIZE=\"40\"  ></TD></TR>\n");
    printf ("       <TR><TD>Homepage: </TD>     <TD><INPUT TYPE=\"text\"     NAME=\"homepage\"   SIZE=\"40\"  ></TD></TR>\n");
    printf ("       <TR><TD>Rua: </TD>          <TD><INPUT TYPE=\"text\"     NAME=\"street\"     SIZE=\"40\"  ></TD></TR>\n");  					
    printf ("       <TR><TD>N�mero: </TD>       <TD><INPUT TYPE=\"text\"     NAME=\"homeNumber\" SIZE=\"%i\"  ></TD></TR>\n", MAX_LENGTH_HOME_NUMBER);
    printf ("       <TR><TD>Complemento: </TD>  <TD><INPUT TYPE=\"text\"     NAME=\"complement\" SIZE=\"40\"></TD></TR>\n");   
    printf ("       <TR><TD>Bairro: </TD>       <TD><INPUT TYPE=\"text\"     NAME=\"district\"   SIZE=\"40\"  ></TD></TR>\n"); 
    printf ("       <TR><TD>Cidade: </TD>       <TD><INPUT TYPE=\"text\"     NAME=\"city\"       SIZE=\"40\"  ></TD></TR>\n"); 
    printf ("       <TR><TD>Estado: </TD>       <TD><INPUT TYPE=\"text\"     NAME=\"state\"      SIZE=\"40\"  ></TD></TR>\n"); 
    printf ("       <TR><TD>Pa�s: </TD>         <TD><INPUT TYPE=\"text\"     NAME=\"country\"    SIZE=\"40\"  ></TD></TR>\n");
    printf ("       <TR><TD>CEP: </TD>          <TD><INPUT TYPE=\"text\"     NAME=\"zipCode\"    SIZE=\"%i\"  ></TD></TR>\n", MAX_LENGTH_ZIP_CODE);   				
    printf ("       <TR><TD>Telefone: </TD>     <TD><INPUT TYPE=\"text\"     NAME=\"telNumber\"  SIZE=\"%i\"  ></TD></TR>\n", MAX_LENGTH_TEL_NUMBER);
    printf ("       <TR><TD>Celular: </TD>      <TD><INPUT TYPE=\"text\"     NAME=\"cellNumber\" SIZE=\"%i\"  ></TD></TR>\n", MAX_LENGTH_CELL_NUMBER);
    printf ("       <TR><TD>Masculino: </TD>    <TD><INPUT TYPE=\"radio\"    NAME=\"gender\" VALUE=\"male\"  ></TD></TR>\n");
    printf ("       <TR><TD>Feminino: </TD>     <TD><INPUT TYPE=\"radio\"    NAME=\"gender\" VALUE=\"female\"></TD></TR>\n");
    printf ("       <TR><TD>Solteiro(a): </TD>  <TD><INPUT TYPE=\"radio\"    NAME=\"relationshipStatus\" VALUE=\"single\"></TD></TR>\n");
    printf ("       <TR><TD>Casado(a): </TD>    <TD><INPUT TYPE=\"radio\"    NAME=\"relationshipStatus\" VALUE=\"married\"></TD></TR>\n");
    printf ("       <TR><TD>Viuvo(a): </TD>     <TD><INPUT TYPE=\"radio\"    NAME=\"relationshipStatus\" VALUE=\"widowed\"></TD></TR>\n");        
    printf ("       <TR><TD>Data de nascimento*: </TD><TD><INPUT TYPE=\"text\"     NAME=\"birthday\"      SIZE=\"8\"> (DDMMAAAA)</TD></TR>\n"); 
    printf ("       <TR><TD>Descri��o: </TD>    <TD><INPUT TYPE=\"text\"     NAME=\"description\"   SIZE=\"40\"  ></TD></TR>\n");  
    printf ("    </TABLE>\n");  	
    printf ("    <BR><BR>\n");
    printf ("                      <INPUT TYPE=\"submit\"   VALUE=\"Submeter\">\n");
    printf ("                      <INPUT TYPE=\"reset\"    VALUE=\"Apagar\">\n");
    printf ("    </FORM>\n");
    printf ("    <BR><BR><BR>\n");
    printf ("<P ALIGN=\"left\"><A HREF=\"javascript:window.history.go(-1)\" TARGET=\"_self\">VOLTAR</a></p>\n");
    printf ("    <HR>\n");
    printf ("    <DIV ALIGN = \"RIGHT\"><FONT FACE = \"Courier New\" SIZE = \"2\"><U>Autores:</U>\n");
    printf ("    <I> Carlo Fragni e Marcelo Duffles Donato Moreira\n");
    printf ("    <BR>\n");
    printf ("    &Uacute;ltima Atualiza&ccedil;&atilde;o: 13/02/05</I></FONT>\n");
    printf ("    </DIV></FONT>\n");
    printf ("  <BODY>\n");
    printf ("</HTML>\n");
  #endif

  exit (ML_CGI_OK);
}

/*$RCS$*/
