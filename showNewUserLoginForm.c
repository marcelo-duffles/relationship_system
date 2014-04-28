//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: showNewUserLoginForm() primary function source file 
// Date: 14/02/2005
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: showNewUserLoginForm.c,v $
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


static const char rcsid [] = "$Id: showNewUserLoginForm.c,v 1.1 2005/02/16 22:11:21 marceloddm Exp marceloddm $";


int main (int argc, char **argv)
{
  unsigned errorCode;	

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
  mlCgiEndHttpHeader();
  mlCgiFreeResources ();
  
  #ifdef ENGLISH
    printf ("<HTML>\n");
    printf ("  <HEAD>\n");
    printf ("    <TITLE>Relationship System - Form to new user login</TITLE>\n");
    printf ("  </HEAD>\n");
    printf ("  <BODY BACKGROUND = \"http://www2.del.ufrj.br/~marceloddm/computacao_ii/pf/images/zertxtr.gif\" BGCOLOR = \"#000000\" TEXT = \"#FFFFFF\" LINK = \"#6699CC\" VLINK = \"#669966\" ALINK = \"#999999\">\n");
    printf ("    <DIV ALIGN = \"CENTER\"><STRONG><FONT FACE = \"Courier New\" SIZE = \"5\" COLOR = \"#FFFFFF\">RELATIONSHIP SYSTEM</FONT></STRONG></DIV>\n");
    printf ("    <HR>\n");
    printf ("    <CENTER><STRONG><FONT FACE = \"Courier New\" SIZE = \"4\" COLOR = \"#FFFFFF\">FORM TO NEW USER LOGIN</FONT></STRONG><CENTER>\n");
    printf ("    <HR>\n");
    printf ("    <BR><BR>\n");
    printf ("    <TABLE BORDER=\"1\" ALIGN = \"center\">\n");
    printf ("    <FORM ACTION=\"http://www2.del.ufrj.br/~marceloddm/computacao_ii/pf/cgi/showNewUserForm.cgi\" METHOD=\"post\">\n");
    printf ("       <TR><TD>Email: </TD>        <TD><INPUT TYPE=\"text\"     NAME=\"email\"      SIZE=\"40\"  ></TD></TR>\n");
    printf ("       <TR><TD>Password: </TD>     <TD><INPUT TYPE=\"password\"     NAME=\"password\"   SIZE=\"40\"  ></TD></TR>\n");
    printf ("       <TR><TD>Accept the invitation: </TD><TD><INPUT TYPE=\"radio\" NAME=\"option\" VALUE=\"accept\" checked</TD></TR>\n");
    printf ("       <TR><TD>Reject the invitation: </TD><TD><INPUT TYPE=\"radio\" NAME=\"option\" VALUE=\"reject\" </TD></TR>\n");
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
    printf ("    Last update: 17/02/05</I></FONT>\n");
    printf ("    </DIV></FONT>\n");
    printf ("  <BODY>\n");
    printf ("</HTML>\n");
  #elif PORTUGUESE
    printf ("<HTML>\n");
    printf ("  <HEAD>\n");
    printf ("    <TITLE>Sistema de Relacionamentos - Formul&aacute;rio para login de novo usu&aacute;rio</TITLE>\n");
    printf ("  </HEAD>\n");
    printf ("  <BODY BACKGROUND = \"http://www2.del.ufrj.br/~marceloddm/computacao_ii/pf/images/zertxtr.gif\" BGCOLOR = \"#000000\" TEXT = \"#FFFFFF\" LINK = \"#6699CC\" VLINK = \"#669966\" ALINK = \"#999999\">\n");
    printf ("    <DIV ALIGN = \"CENTER\"><STRONG><FONT FACE = \"Courier New\" SIZE = \"5\" COLOR = \"#FFFFFF\">SISTEMA DE RELACIONAMENTOS</FONT></STRONG></DIV>\n");
    printf ("    <HR>\n");
    printf ("    <CENTER><STRONG><FONT FACE = \"Courier New\" SIZE = \"4\" COLOR = \"#FFFFFF\">FORMUL&Aacute;RIO PARA LOGIN DE NOVO USU&Aacute;RIO</FONT></STRONG><CENTER>\n");
    printf ("    <HR>\n");
    printf ("    <BR><BR>\n");
    printf ("    <TABLE BORDER=\"1\" ALIGN = \"center\">\n");
    printf ("    <FORM ACTION=\"http://www2.del.ufrj.br/~marceloddm/computacao_ii/pf/cgi/showNewUserForm.cgi\" METHOD=\"post\">\n");
    printf ("       <TR><TD>Email: </TD>      <TD><INPUT TYPE=\"text\"     NAME=\"email\"     SIZE=\"40\"  ></TD></TR>\n"); 
    printf ("       <TR><TD>Senha: </TD>      <TD><INPUT TYPE=\"password\"     NAME=\"password\"   SIZE=\"40\"  ></TD></TR>\n");
    printf ("       <TR><TD>Aceitar o convite: </TD><TD><INPUT TYPE=\"radio\" NAME=\"option\" VALUE=\"accept\" checked</TD></TR>\n");
    printf ("       <TR><TD>Rejeitar o convite: </TD><TD><INPUT TYPE=\"radio\" NAME=\"option\" VALUE=\"reject\" </TD></TR>\n");
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
    printf ("    &Uacute;ltima Atualiza&ccedil;&atilde;o: 17/02/05</I></FONT>\n");
    printf ("    </DIV></FONT>\n");
    printf ("  <BODY>\n");
    printf ("</HTML>\n");
  #endif

  exit (ML_CGI_OK);
}

/*$RCSfile$*/
