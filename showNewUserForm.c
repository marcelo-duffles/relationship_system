//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Polit�cnica
// Departamento de Eletr�nica e de Computa��o
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: cgiNewUserLogin() primary function source file 
// Date: 14/02/2005
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: showNewUserForm.c,v $
 * Revision 1.1  2005/02/16 22:11:21  marceloddm
 * Initial revision
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/errno.h>
#include "mlcgi.h"
#include "const.h"
#include "types.h"
#include "error.h"
#include "config.h"
#include "functions.h"


static const char rcsid [] = "$Id: showNewUserForm.c,v 1.1 2005/02/16 22:11:21 marceloddm Exp marceloddm $";


int main (int argc, char **argv)
{
  unsigned errorCode;	
  char email[MAX_LENGTH_EMAIL +1];
  char password[MAX_LENGTH_PLAIN_PASS +1];
  char option[10 +1];
  char name[MAX_LENGTH_NAME +1];
  char filename[MAX_LENGTH_LONG_FILENAME +1];
  char encryptedPass[ENCRYPTED_PASS_LENGTH +1];
  FILE *tempFile;

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

  if ((errorCode = mlCgiGetFormStringNoNewLines ("email", email, MAX_LENGTH_EMAIL)) != ML_CGI_OK)
  {
    mlCgiEndHttpHeader ();
    mlCgiFreeResources ();
    if (errorCode == ML_CGI_FORM_FIELD_NOT_FOUND)
      showHtmlErrorPage (FORM_FIELD_NOT_FOUND);
    if (errorCode == ML_CGI_INVALID_FORM_LENGTH)
      showHtmlErrorPage (INVALID_FORM_FIELD_LENGTH);
    exit (ML_CGI_OK);
  }

  if ((errorCode = mlCgiGetFormStringNoNewLines ("password", password, MAX_LENGTH_PLAIN_PASS)) != ML_CGI_OK)
  {
    mlCgiEndHttpHeader ();
    mlCgiFreeResources ();
    if (errorCode == ML_CGI_FORM_FIELD_NOT_FOUND)
      showHtmlErrorPage (FORM_PLAIN_PASS_NOT_FOUND);
    if (errorCode == ML_CGI_INVALID_FORM_LENGTH)
      showHtmlErrorPage (INVALID_FORM_PLAIN_PASS_LENGTH);
    exit (ML_CGI_OK);
  }
  
  if ((errorCode = mlCgiGetFormStringNoNewLines ("option", option, 10)) != ML_CGI_OK)
  {
    mlCgiEndHttpHeader ();
    mlCgiFreeResources ();
    if (errorCode == ML_CGI_FORM_FIELD_NOT_FOUND)
      showHtmlErrorPage (FORM_FIELD_NOT_FOUND);
    if (errorCode == ML_CGI_INVALID_FORM_LENGTH)
      showHtmlErrorPage (INVALID_FORM_FIELD_LENGTH);
    exit (ML_CGI_OK);
  }

  mlCgiEndHttpHeader();
  mlCgiFreeResources ();
  
  if (!strcmp (option, "reject"))
  {
    remove (email);
    showHtmlErrorPage (USER_HAS_REJECTED_THE_INVITATION);
    exit (ML_CGI_OK);
  }
  
  if ((errorCode = getLongFilename (DATA_DIR, email, filename)) != OK)
  {
    showHtmlErrorPage (errorCode);
    exit (ML_CGI_OK);
  }
    
  if ((tempFile = fopen (filename, "r")) == NULL)
  {
    if (errno != ENOENT)
    {
      showHtmlErrorPage (ERROR_OPENING_TEMPORARY_FILE_FOR_READING);
      exit (ML_CGI_OK);
    }
    showHtmlErrorPage (TEMPORARY_FILE_DOES_NOT_EXIST);
    exit (ML_CGI_OK);
  } 
  
  if ((errorCode = getString (tempFile, MIN_LENGTH_NAME, MAX_LENGTH_NAME, name)) != OK)
  {
    fclose (tempFile);
    showHtmlErrorPage (errorCode);
    exit (ML_CGI_OK);
  }
  if ((errorCode = getString (tempFile, ENCRYPTED_PASS_LENGTH, ENCRYPTED_PASS_LENGTH, encryptedPass)) != OK)
  {
    fclose (tempFile);
    showHtmlErrorPage (errorCode);
    exit (ML_CGI_OK);
  }
  fclose (tempFile);
  
  if ((errorCode = checkPassword (encryptedPass, password)) != OK)
  {
    showHtmlErrorPage (errorCode);
    exit (ML_CGI_OK);
  }
  remove (filename);
  
  #ifdef ENGLISH
    printf ("<HTML>\n");
    printf ("  <HEAD>\n");
    printf ("    <TITLE>Relationship System - Form to add a new user to the system </TITLE>\n");
    printf ("  </HEAD>\n");
    printf ("  <BODY BACKGROUND = \"http://www2.del.ufrj.br/~marceloddm/computacao_ii/pf/images/zertxtr.gif\" BGCOLOR = \"#000000\" TEXT = \"#FFFFFF\" LINK = \"#6699CC\" VLINK = \"#669966\" ALINK = \"#999999\">\n");
    printf ("    <DIV ALIGN = \"CENTER\"><STRONG><FONT FACE = \"Courier New\" SIZE = \"5\" COLOR = \"#FFFFFF\">RELATIONSHIP SYSTEM</FONT></STRONG></DIV>\n");
    printf ("    <HR>\n");
    printf ("    <CENTER><STRONG><FONT FACE = \"Courier New\" SIZE = \"4\" COLOR = \"#FFFFFF\">FORM TO ADD A NEW USER TO THE SYSTEM</FONT></STRONG><CENTER>\n");
    printf ("    <HR>\n");
    printf ("    <BR><BR>\n");
    printf ("    <TABLE BORDER=\"1\" ALIGN = \"center\">\n");
    printf ("    <FORM ACTION=\"http://www2.del.ufrj.br/~marceloddm/computacao_ii/pf/cgi/newUser.cgi\" METHOD=\"post\">\n");
    printf ("       <TR><TD>Username: </TD>     <TD><INPUT TYPE=\"text\"     NAME=\"username\"   SIZE=\"%i\"  ></TD></TR>\n", MAX_LENGTH_USERNAME);
    printf ("       <TR><TD>Password: </TD>     <TD><INPUT TYPE=\"password\" NAME=\"password\"   SIZE=\"%i\" VALUE=\"%s\" ></TD></TR>\n", MAX_LENGTH_PLAIN_PASS, password);
    printf ("       <TR><TD>Web user: </TD>     <TD><INPUT TYPE=\"radio\"    NAME=\"category\" VALUE=\"webUser\" CHECKED></TD></TR>\n");
    printf ("       <TR><TD>Relative: </TD>     <TD><INPUT TYPE=\"radio\"    NAME=\"category\" VALUE=\"relative\"></TD></TR>\n"); 
    printf ("       <TR><TD>Full name: </TD>    <TD><INPUT TYPE=\"text\"     NAME=\"name\"       SIZE=\"40\" VALUE=\"%s\"></TD></TR>\n", name);  
    printf ("       <TR><TD>Email: </TD>        <TD><INPUT TYPE=\"text\"     NAME=\"email\"      SIZE=\"40\" VALUE=\"%s\"></TD></TR>\n", email);
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
    printf ("       <TR><TD>Date of birth: </TD><TD><INPUT TYPE=\"text\"     NAME=\"birthday\"      SIZE=\"8\"> (DDMMYYYY)</TD></TR>\n"); 
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
    printf ("    <TITLE>Sistema de Relacionamentos - Formul&aacute;rio para adicionar novo usu&aacute;rio ao sistema</TITLE>\n");
    printf ("  </HEAD>\n");
    printf ("  <BODY BACKGROUND = \"http://www2.del.ufrj.br/~marceloddm/computacao_ii/pf/images/zertxtr.gif\" BGCOLOR = \"#000000\" TEXT = \"#FFFFFF\" LINK = \"#6699CC\" VLINK = \"#669966\" ALINK = \"#999999\">\n");
    printf ("    <DIV ALIGN = \"CENTER\"><STRONG><FONT FACE = \"Courier New\" SIZE = \"5\" COLOR = \"#FFFFFF\">SISTEMA DE RELACIONAMENTOS</FONT></STRONG></DIV>\n");
    printf ("    <HR>\n");
    printf ("    <CENTER><STRONG><FONT FACE = \"Courier New\" SIZE = \"4\" COLOR = \"#FFFFFF\">FORMUL&Aacute;RIO PARA ADICIONAR NOVO USU&Aacute;RIO AO SISTEMA</FONT></STRONG><CENTER>\n");
    printf ("    <HR>\n");
    printf ("    <BR><BR>\n");
    printf ("    <TABLE BORDER=\"1\" ALIGN = \"center\">\n");
    printf ("    <FORM ACTION=\"http://www2.del.ufrj.br/~marceloddm/computacao_ii/pf/cgi/newUser.cgi\" METHOD=\"post\">\n");
    printf ("       <TR><TD>Username: </TD>     <TD><INPUT TYPE=\"text\"     NAME=\"username\"   SIZE=\"%i\"  ></TD></TR>\n", MAX_LENGTH_USERNAME);
    printf ("       <TR><TD>Senha: </TD>        <TD><INPUT TYPE=\"password\" NAME=\"password\"   SIZE=\"%i\" VALUE=\"%s\"></TD></TR>\n", MAX_LENGTH_PLAIN_PASS, password);
    printf ("       <TR><TD>Usu�rio web: </TD>  <TD><INPUT TYPE=\"radio\"    NAME=\"category\" VALUE=\"webUser\" CHECKED></TD></TR>\n");
    printf ("       <TR><TD>Parente: </TD>      <TD><INPUT TYPE=\"radio\"    NAME=\"category\" VALUE=\"relative\"></TD></TR>\n"); 
    printf ("       <TR><TD>Nome completo: </TD><TD><INPUT TYPE=\"text\"     NAME=\"name\"       SIZE=\"40\" VALUE=\"%s\"></TD></TR>\n", name);  
    printf ("       <TR><TD>Email: </TD>        <TD><INPUT TYPE=\"text\"     NAME=\"email\"      SIZE=\"40\" VALUE=\"%s\"></TD></TR>\n", email);
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
    printf ("       <TR><TD>Data de nascimento: </TD><TD><INPUT TYPE=\"text\"     NAME=\"birthday\"      SIZE=\"8\"> (DDMMYYYY)</TD></TR>\n"); 
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

/*$RCSfile$*/
