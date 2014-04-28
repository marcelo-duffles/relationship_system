//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Polit�cnica
// Departamento de Eletr�nica e de Computa��o
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira
// Description: Help() primary function source file 
// Date: 29/11/2004
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: help.c,v $
 * Revision 1.8  2005/02/16 22:11:21  marceloddm
 * CGI's added
 *
 * Revision 1.7  2004/12/15 01:32:58  marceloddm
 * Constants added: RELATIONSHIP_SYSTEM__OPTION_MUST_COME_FIRST,RELATIONSHIP_SYSTEM__UNKNOWN_OPTION and RELATIONSHIP_SYSTEM__WELCOME_MESSAGE
 *
 * Revision 1.5  2004/12/14 02:51:28  marceloddm
 * Grammar corrections have been made
 *
 * Revision 1.4  2004/12/13 07:53:10  marceloddm
 * Languages settings have been done
 * showTextHelpMessage() and showHtmlHelpMessage() added
 *
 * Revision 1.3  2004/12/11 12:23:43  marceloddm
 * Author changed for 'marceloddm'
 *
 * Revision 1.2  2004/11/30 00:28:30  root
 * I think that this file is now complete
 *
 * Revision 1.1  2004/11/29 20:47:09  root
 * Initial revision
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "help.h"


/*---------------------------------------------------------------------------------------------------------*/
// Global variable which contains the text help messages
char *textHelpMessages[] = 

#ifdef ENGLISH
{
  /*00*/ "\nAdministrator's password: ",
  /*01*/ "\nConfirmation: ",
  /*02*/ "Would you like to install again? (y/n) Answer: ",
  /*03*/ "The system has NOT been installed again.",
  /*04*/ "Installation done successfully.",
  /*05*/ "Atention! Option must come before arguments.",
  /*06*/ "Unknown option!",
  /*07*/ "\n		WELCOME TO RELATIONSHIP SYSTEM!\n\
  Authors: Carlo Fragni and Marcelo Duffles Donato Moreira\n\n\
  Only the administrator can run the program in this interface.",
  /*08*/ "New password: ",
  /*09*/ "Confirmation: ",
  /*10*/ "RELATIONSHIP SYSTEM",
  /*11*/ "Authors: Carlo Fragni and Marcelo Duffles Donato Moreira",
  /*12*/ "Please increase the screen to correctly run in this interface.",
  /*13*/ "MINIMUM SIZE RECOMMENDED: 70 x 32",
  /*14*/ "ESC to exit",
  /*15*/ "ENTER to submit",
  /*16*/ "FORM TO REINSTALL THE SYSTEM",
  /*17*/ "FORM TO ADD USER TO THE SYSTEM",
  /*18*/ "FORM TO EDIT USER DATA",
  /*19*/ "FORM TO REMOVE USER FROM THE SYSTEM",
  /*20*/ "FORM TO INVITE USER",
  /*21*/ "FORM TO INVITE FRIEND",
  /*22*/ "FORM TO GET PENDING FRIENDSHIP INVITATIONS",
  /*23*/ "FORM TO ACCEPT FRIENDSHIP INVITATION",
  /*24*/ "FORM TO REJECT FRIENDSHIP INVITATION",
  /*25*/ "FORM TO EXCLUDE FRIENDSHIP RELATION",
  /*26*/ "FORM TO SEARCH FRIENDS",
  /*27*/ "FORM TO CHANGE CATEGORY",
  /*28*/ "FORM TO ADD PARENT RELATIONSHIP",
  /*29*/ "FORM TO REMOVE PARENT RELATIONSHIP",
  /*30*/ "FORM TO EDIT PARENT RELATIONSHIP",
  /*31*/ "FORM TO SEARCH USERS",
  /*32*/ "FORM TO MOUNT FAMILY TREE",
  /*33*/ "FORM TO RECOVERY PASSWORD",
  /*34*/ "FORM TO CHANGE PASSWORD",
  /*35*/ "FORM TO UPLOAD PHOTO",
  /*36*/ "User ID:",
  /*37*/ "New user's password:", 
  /*38*/ "Username:",
  /*39*/ "Category:",
  /*40*/ "Full Name:",
  /*41*/ "Email:", 
  /*42*/ "Homepage:",
  /*43*/ "Street:",
  /*44*/ "Home Number:",
  /*45*/ "Complement:",
  /*46*/ "District:", 
  /*47*/ "City:", 
  /*48*/ "State:", 
  /*49*/ "Country:",
  /*50*/ "ZIP Code:", 
  /*51*/ "Telephone:", 
  /*52*/ "Cellphone:", 
  /*53*/ "Gender:",
  /*54*/ "Relationship Status:", 
  /*55*/ "Day of born:",
  /*56*/ "Month of born:",
  /*57*/ "Year of born:",
  /*58*/ "Description:",
  /*59*/ "User ID of who is inviting:",
  /*60*/ "User ID of invited user:",
  /*61*/ "User ID of who is accepting invitation:",
  /*62*/ "User ID of who is rejecting invitation:",
  /*63*/ "User ID of who is excluding friendship relation:",
  /*64*/ "New category:",
  /*65*/ "User ID of sun:",
  /*66*/ "User ID of parent:",
  /*67*/ "User ID of new sun:",
  /*68*/ "User ID of new parent:",
  /*69*/ "Keyword:",
  /*70*/ "Lower level:",
  /*71*/ "Upper level:",
  /*72*/ "Filename:",
  /*73*/ "Confirmation",
  /*74*/ "ERROR FOUND IN FORM DATA",
  /*75*/ "Administrator's password:",
  /*76*/ "Press any key to continue...",
  /*77*/ "New web user's password: ",
  /*78*/ "BACKSPACE to clear",
  /*79*/ "PLEASE, INFORM THE USER's ID",
  /*80*/ "PLEASE, INFORM THE NEW DATA",
  /*81*/ "PLEASE, INFORM THE SEARCH KEY",
  /*82*/ "Search key:",
  /*83*/ "LIST OF USERS FOUND",
  /*84*/ "USER ID of who is inviting: ",
  /*85*/ "USER ID of who is been invited: ",
  /*86*/ "USER ID of who is accepting the invitation: ",
  /*87*/ "USER ID of the inviter: ",
  /*88*/ "USER ID of who is rejecting the invitation: ",
  /*89*/ "USER ID of who is excluding the friendship: ",
  /*90*/ "USER ID of the friend who is going to be excluded: ",
  /*91*/ "USER ID of sun(daughter): ",
  /*92*/ "USER ID of new sun(daughter): ",
  /*93*/ "USER ID of parent: ",
  /*94*/ "USER ID of new parent: ",
  /*95*/ "[RELATIONSHIP SYSTEM] Your friendship invitation has been accepted",
  /*96*/ "[RELATIONSHIP SYSTEM] Your friendship invitation has been rejected",
  /*97*/ "[RELATIONSHIP SYSTEM] Your friendship relation has been excluded",
  /*98*/ "[RELATIONSHIP SYSTEM] Your friendship invitation has been sent",
  /*99*/ "[RELATIONSHIP SYSTEM] You have been invited to join our system",
  /*100*/"[RELATIONSHIP SYSTEM] Your password has been changed", 
  /*101*/ "LIST OF FRIENDS FOUND",
}; 

#elif PORTUGUESE
{
  /*00*/ "\nSenha do administrador: ",
  /*01*/ "\nConfirma��o: ",
  /*02*/ "Deseja reinstalar o sistema? (s/n) Resposta: ",
  /*03*/ "O sistema N�O foi reinstalado.",
  /*04*/ "Instala��o realizada com sucesso.",
  /*05*/ "Aten��o! A op��o deve vir antes dos argumentos.",
  /*06*/ "Op��o desconhecida!\n",
  /*07*/ "\n	BEM-VINDO AO SISTEMA DE RELACIONAMENTOS!\n\
  Autores: Carlo Fragni e Marcelo Duffles Donato Moreira\n\n\
  Somente o administrador pode rodar o programa nessa interface.", 
  /*08*/ "Nova senha: ",
  /*09*/ "Confirma��o: ",
  /*10*/ "SISTEMA DE RELACIONAMENTOS",
  /*11*/ "Autores: Carlo Fragni e Marcelo Duffles Donato Moreira",
  /*12*/ "Por favor aumente a tela para executar corretamente o modo NCURSES.",
  /*13*/ "TAMANHO MINIMO RECOMENDADO: 70 x 32",
  /*14*/ "ESC para sair",
  /*15*/ "ENTER to enviar",
  /*16*/ "FORMULARIO PARA REINSTALAR O SISTEMA",
  /*17*/ "FORMULARIO PARA ADICIONAR NOVO USU�RIO AO SISTEMA",
  /*18*/ "FORMULARIO PARA EDITAR DADOS DE USU�RIO",
  /*19*/ "FORMULARIO PARA REMOVER USU�RIO DO SISTEMA",
  /*20*/ "FORMULARIO PARA CONVIDAR ALGU�M PARA ENTRAR NO SISTEMA",
  /*21*/ "FORMULARIO PARA CONVIDAR USU�RIO PARA INICIAR AMIZADE",
  /*22*/ "FORMULARIO PARA OBTER CONVITES DE AMIZADE PENDENTES",
  /*23*/ "FORMULARIO PARA ACEITAR CONVITE DE AMIZADE",
  /*24*/ "FORMULARIO PARA REJEITAR CONVITE DE AMIZADE",
  /*25*/ "FORMULARIO PARA EXCLUIR AMIZADE",
  /*26*/ "FORMULARIO PARA BUSCAR AMIGOS",
  /*27*/ "FORMULARIO PARA MUDAR CATEGORIA",
  /*28*/ "FORMULARIO PARA ADICIONAR PAI/M�E",
  /*29*/ "FORMULARIO PARA REMOVER PAI/M�E",
  /*30*/ "FORMULARIO PARA EDIT RELA��O DE PARENTESCO",
  /*31*/ "FORMULARIO PARA BUSCAR USU�RIOS",
  /*32*/ "FORMULARIO PARA MONTAR ARVORE GENEAL�GICA",
  /*33*/ "FORMULARIO PARA RECUPERAR SENHA",
  /*34*/ "FORMULARIO PARA ALTERAR SENHA",
  /*35*/ "FORMULARIO PARA FAZER UPLOAD DE FOTO DO USU�RIO",
  /*36*/ "ID do usu�rio:",
  /*37*/ "Senha do novo usu�rio:", 
  /*38*/ "Username:",
  /*39*/ "Categoria:",
  /*40*/ "Nome Completo:",
  /*41*/ "Email:", 
  /*42*/ "Homepage:",
  /*43*/ "Rua:",
  /*44*/ "N�mero:",
  /*45*/ "Complemento:",
  /*46*/ "Bairro:", 
  /*47*/ "Cidade:", 
  /*48*/ "Estado:", 
  /*49*/ "Pa�s:",
  /*50*/ "CEP:", 
  /*51*/ "Telefone:", 
  /*52*/ "Celular:", 
  /*53*/ "Sexo:",
  /*54*/ "Estado civil:", 
  /*55*/ "Dia de nascimento:",
  /*56*/ "M�s de nascimento:",
  /*57*/ "Ano de nascimento:",
  /*58*/ "Descri��o:",
  /*59*/ "ID do usu�rio que est� efetuando o convite:",
  /*60*/ "ID do convidado:",
  /*61*/ "ID do usu�rio que est� aceitando o convite:",
  /*62*/ "ID do usu�rio que est� rejeitando o convite:",
  /*63*/ "ID do usu�rio que est� excluindo amizade:",
  /*64*/ "Nova categoria:",
  /*65*/ "ID do(a) filho(a):",
  /*66*/ "ID do(a) pai(m�e):",
  /*67*/ "ID do(a) novo(a) filho(a):",
  /*68*/ "ID do(a) novo(a) pai(m�e):",
  /*69*/ "Palavra-chave:",
  /*70*/ "N�vel mais baixo:",
  /*71*/ "N�vel mais alto:",
  /*72*/ "Nome do arquivo:",
  /*73*/ "Confirma��o:",
  /*74*/ "ERRO ENCONTRADO NOS DADOS DO FORMULARIO",
  /*75*/ "Senha do administrador:",
  /*76*/ "Aperte qualquer tecla para continuar...",
  /*77*/ "Senha do novo usu�rio web: ",
  /*78*/ "BACKSPACE para apagar",
  /*79*/ "POR FAVOR, INFORME A ID DO USU�RIO",
  /*80*/ "POR FAVOR, INFORME OS NOVOS DADOS",
  /*81*/ "POR FAVOR, INFORME A PALAVRA-CHAVE",
  /*82*/ "Palavra-chave:",
  /*83*/ "LISTA DE USU�RIOS ENCONTRADOS",
  /*84*/ "ID de quem est� convidando: ",
  /*85*/ "ID de quem est� sendo convidado: ",
  /*86*/ "ID de quem est� aceitando o convite: ",
  /*87*/ "ID de quem efetuou o convite: ",
  /*88*/ "ID de quem est� rejeitando o convite: ",
  /*89*/ "ID de quem est� excluindo a amizade: ",
  /*90*/ "ID do(a) ex-amigo(a): ",
  /*91*/ "ID do(a) filho(a): ",
  /*92*/ "ID do(a) novo(a) filho(a): ",
  /*93*/ "ID do(a) pai(m�e): ",
  /*94*/ "ID do(a) novo(a) pai(m�e): ",
  /*95*/ "[SISTEMA DE RELACIONAMENTOS] Seu convite de amizade foi aceito",
  /*96*/ "[SISTEMA DE RELACIONAMENTOS] Seu convite de amizade foi rejeitado",
  /*97*/ "[SISTEMA DE RELACIONAMENTOS] Sua amizade foi exclu�da",
  /*98*/ "[SISTEMA DE RELACIONAMENTOS] Seu convite de amizade foi enviado",
  /*99*/ "[SISTEMA DE RELACIONAMENTOS] Voc� foi convidado para entrar no nosso sistema",
  /*100*/"[SISTEMA DE RELACIONAMENTOS] Sua senha foi alterada", 
  /*101*/ "LISTA DE AMIGOS ENCONTRADOS",
};
  
#endif
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
// Global variable which contains the html help messages
char *htmlHelpMessages[] = 

#ifdef ENGLISH
{
  /*00*/ "\nAdministrator's password: ",
  /*01*/ "\nConfirmation: ", 
  /*02*/ "Would you like to install again? (y/n) Answer: ",
  /*03*/ "The system has NOT been installed again.",
  /*04*/ "Installation done successfully.",
  /*05*/ "Atention! Option must come before arguments.",
  /*06*/ "Unknown option!\n",
  /*07*/ "\n		WELCOME TO RELATIONSHIP SYSTEM!\n\
  Authors: Carlo Fragni and Marcelo Duffles Donato Moreira\n\
  Only the administrator can run the program in this interface.",
  /*08*/ "New password: ",
  /*09*/ "Confirmation: ",
  /*10*/ "RELATIONSHIP SYSTEM",
  /*11*/ "Authors: Carlo Fragni and Marcelo Duffles Donato Moreira",
  /*12*/ "Please increase the screen to correctly run in this interface.",
  /*13*/ "MINIMUM SIZE RECOMMENDED: 70 x 32",
  /*14*/ "ESC to exit",
  /*15*/ "ENTER to submit",
  /*16*/ "FORM TO REINSTALL THE SYSTEM",
  /*17*/ "FORM TO ADD USER TO THE SYSTEM",
  /*18*/ "FORM TO EDIT USER DATA",
  /*19*/ "FORM TO REMOVE USER FROM THE SYSTEM",
  /*20*/ "FORM TO INVITE USER",
  /*21*/ "FORM TO INVITE FRIEND",
  /*22*/ "FORM TO GET PENDING FRIENDSHIP INVITATIONS",
  /*23*/ "FORM TO ACCEPT FRIENDSHIP INVITATION",
  /*24*/ "FORM TO REJECT FRIENDSHIP INVITATION",
  /*25*/ "FORM TO EXCLUDE FRIENDSHIP RELATION",
  /*26*/ "FORM TO SEARCH FRIENDS",
  /*27*/ "FORM TO CHANGE CATEGORY",
  /*28*/ "FORM TO ADD PARENT RELATIONSHIP",
  /*29*/ "FORM TO REMOVE PARENT RELATIONSHIP",
  /*30*/ "FORM TO EDIT PARENT RELATIONSHIP",
  /*31*/ "FORM TO SEARCH USERS",
  /*32*/ "FORM TO MOUNT FAMILY TREE",
  /*33*/ "FORM TO RECOVERY PASSWORD",
  /*34*/ "FORM TO CHANGE PASSWORD",
  /*35*/ "FORM TO UPLOAD PHOTO",
  /*36*/ "User ID:",
  /*37*/ "New user's password:", 
  /*38*/ "Username:",
  /*39*/ "Category:",
  /*40*/ "Full Name:",
  /*41*/ "Email:", 
  /*42*/ "Homepage:",
  /*43*/ "Street:",
  /*44*/ "Home Number:",
  /*45*/ "Complement:",
  /*46*/ "District:", 
  /*47*/ "City:", 
  /*48*/ "State:", 
  /*49*/ "Country:",
  /*50*/ "ZIP Code:", 
  /*51*/ "Telephone:", 
  /*52*/ "Cellphone:", 
  /*53*/ "Gender:",
  /*54*/ "Relationship Status:", 
  /*55*/ "Day of born:",
  /*56*/ "Month of born:",
  /*57*/ "Year of born:",
  /*58*/ "Description:",
  /*59*/ "User ID of who is inviting:",
  /*60*/ "User ID of invited user:",
  /*61*/ "User ID of who is accepting invitation:",
  /*62*/ "User ID of who is rejecting invitation:",
  /*63*/ "User ID of who is excluding friendship relation:",
  /*64*/ "New category:",
  /*65*/ "User ID of sun:",
  /*66*/ "User ID of parent:",
  /*67*/ "User ID of new sun:",
  /*68*/ "User ID of new parent:",
  /*69*/ "Keyword:",
  /*70*/ "Lower level:",
  /*71*/ "Upper level:",
  /*72*/ "Filename:",
  /*73*/ "Confirmation:",
  /*74*/ "ERROR FOUND IN FORM DATA",
  /*75*/ "Administrator password:",
  /*76*/ "Press any key to continue...",
  /*77*/ "New web user's password: ",
  /*78*/ "BACKSPACE to clear",
  /*79*/ "PLEASE, INFORM THE USER's ID",
  /*80*/ "PLEASE, INFORM THE NEW DATA",
  /*81*/ "PLEASE, INFORM THE SEARCH KEY",
  /*82*/ "Search key:",
  /*83*/ "LIST OF USERS FOUND",
  /*84*/ "USER ID of who is inviting: ",
  /*85*/ "USER ID of who is been invited: ",
  /*86*/ "USER ID of who is accepting the invitation: ",
  /*87*/ "USER ID of the inviter: ",
  /*88*/ "USER ID of who is rejecting the invitation: ",
  /*89*/ "USER ID of who is excluding the friendship: ",
  /*90*/ "USER ID of the friend who is going to be excluded: ",
  /*91*/ "USER ID of sun(daughter): ",
  /*92*/ "USER ID of new sun(daughter): ",
  /*93*/ "USER ID of parent: ",
  /*94*/ "USER ID of new parent: ",
  /*95*/ "[RELATIONSHIP SYSTEM] Your friendship invitation has been accepted",
  /*96*/ "[RELATIONSHIP SYSTEM] Your friendship invitation has been rejected",
  /*97*/ "[RELATIONSHIP SYSTEM] Your friendship relation has been excluded",
  /*98*/ "[RELATIONSHIP SYSTEM] Your friendship invitation has been sent",
  /*99*/ "[RELATIONSHIP SYSTEM] You have been invited to join our system",
  /*100*/"[RELATIONSHIP SYSTEM] Your password has been changed", 
  /*101*/ "LIST OF FRIENDS FOUND",
}; 

#elif PORTUGUESE
{
  /*00*/ "\nSenha do administrador: ",
  /*01*/ "\nConfirma&ccedil;&atilde;o: ",
  /*02*/ "Deseja reinstalar o sistema? (y/n) Resposta: ",
  /*03*/ "O sistema N&Atilde;O foi reinstalado.\n",
  /*04*/ "Instala&ccedil;&atilde;o realizada com sucesso."
  /*05*/ "Aten&ccedil;&atilde;o! A op&ccedil;&atilde;o deve vir antes dos argumentos.",
  /*06*/ "Op&ccedil;&atilde;o desconhecida!",
  /*07*/ "\n	BEM-VINDO AO SISTEMA DE RELACIONAMENTOS!\n\
  Autores: Carlo Fragni e Marcelo Duffles Donato Moreira\n\n\
  Somente o administrador pode rodar o programa nessa interface.", 
  /*08*/ "Nova senha: ",
  /*09*/ "Confirma&ccedil;&atilde;o: ",
  /*10*/ "SISTEMA DE RELACIONAMENTOS",
  /*11*/ "Autores: Carlo Fragni e Marcelo Duffles Donato Moreira",
  /*12*/ "Por favor aumente a tela para executar corretamente o modo NCURSES.",
  /*13*/ "TAMANHO MINIMO RECOMENDADO: 70 x 32",
  /*14*/ "ESC para sair",
  /*15*/ "ENTER to enviar",
  /*16*/ "FORMULARIO PARA REINSTALAR O SISTEMA",
  /*17*/ "FORMULARIO PARA ADICIONAR NOVO USU�RIO AO SISTEMA",
  /*18*/ "FORMULARIO PARA EDITAR DADOS DE USU�RIO",
  /*19*/ "FORMULARIO PARA REMOVER USU�RIO DO SISTEMA",
  /*20*/ "FORMULARIO PARA CONVIDAR ALGU�M PARA ENTRAR NO SISTEMA",
  /*21*/ "FORMULARIO PARA CONVIDAR USU�RIO PARA INICIAR AMIZADE",
  /*22*/ "FORMULARIO PARA OBTER CONVITES DE AMIZADE PENDENTES",
  /*23*/ "FORMULARIO PARA ACEITAR CONVITE DE AMIZADE",
  /*24*/ "FORMULARIO PARA REJEITAR CONVITE DE AMIZADE",
  /*25*/ "FORMULARIO PARA EXCLUIR AMIZADE",
  /*26*/ "FORMULARIO PARA BUSCAR AMIGOS",
  /*27*/ "FORMULARIO PARA MUDAR CATEGORIA",
  /*28*/ "FORMULARIO PARA ADICIONAR PAI/M�E",
  /*29*/ "FORMULARIO PARA REMOVER PAI/M�E",
  /*30*/ "FORMULARIO PARA EDIT RELA&Ccedil;�O DE PARENTESCO",
  /*31*/ "FORMULARIO PARA BUSCAR USU�RIOS",
  /*32*/ "FORMULARIO PARA MONTAR ARVORE GENEAL�GICA",
  /*33*/ "FORMULARIO PARA RECUPERAR SENHA",
  /*34*/ "FORMULARIO PARA ALTERAR SENHA",
  /*35*/ "FORMULARIO PARA FAZER UPLOAD DE FOTO DO USU�RIO",
  /*36*/ "ID do usu&aacute;rio:",
  /*37*/ "Senha do novo usu&aacute;rio:", 
  /*38*/ "Username:",
  /*39*/ "Categoria:",
  /*40*/ "Nome Completo:",
  /*41*/ "Email:", 
  /*42*/ "Homepage:",
  /*43*/ "Rua:",
  /*44*/ "N&uacute;mero:",
  /*45*/ "Complemento:",
  /*46*/ "Bairro:", 
  /*47*/ "Cidade:", 
  /*48*/ "Estado:", 
  /*49*/ "Pa&iacute;s:",
  /*50*/ "CEP:", 
  /*51*/ "Telefone:", 
  /*52*/ "Celular:", 
  /*53*/ "Sexo:",
  /*54*/ "Estado civil:", 
  /*55*/ "Dia de nascimento:",
  /*56*/ "M&ecirc;s de nascimento:",
  /*57*/ "Ano de nascimento:",
  /*58*/ "Descri&ccedil;&atilde;o:",
  /*59*/ "ID do usu&aacute;rio que est&aacute; efetuando o convite:",
  /*60*/ "ID do convidado:",
  /*61*/ "ID do usu&aacute;rio que est&aacute; aceitando o convite:",
  /*62*/ "ID do usu&aacute;rio que est&aacute; rejeitando o convite:",
  /*63*/ "ID do usu&aacute;rio que est&aacute; excluindo amizade:",
  /*64*/ "Nova categoria:",
  /*65*/ "ID do(a) filho(a):",
  /*66*/ "ID do(a) pai(m&atilde;e):",
  /*67*/ "ID do(a) novo(a) filho(a):",
  /*68*/ "ID do(a) novo(a) pai(m&atilde;e):",
  /*69*/ "Palavra-chave:",
  /*70*/ "N&iacute;vel mais baixo:",
  /*71*/ "N&iacute;vel mais alto:",
  /*72*/ "Nome do arquivo:",
  /*73*/ "Confirma&ccedil;&atilde;o:",
  /*74*/ "ERRO ENCONTRADO NOS DADOS DO FORMULARIO",
  /*75*/ "Senha do administrador:",
  /*76*/ "Aperte qualquer tecla para continuar...",
  /*77*/ "Senha do novo usu&aacute;rio web: ",
  /*78*/ "BACKSPACE para apagar",
  /*79*/ "POR FAVOR, INFORME A ID DO USU&Aacute;RIO",
  /*80*/ "POR FAVOR, INFORME OS NOVOS DADOS",
  /*81*/ "POR FAVOR, INFORME A PALAVRA-CHAVE",
  /*82*/ "Palavra-chave:",
  /*83*/ "LISTA DE USU&Aacute;RIOS ENCONTRADOS",
  /*84*/ "ID de quem est&aacute; convidando: ",
  /*85*/ "ID de quem est&acute; sendo convidado: ",
  /*86*/ "ID de quem est&aacute; aceitando o convite: ",
  /*87*/ "ID de quem efetuou o convite: ",
  /*88*/ "ID de quem est&aacute; rejeitando o convite: ",
  /*89*/ "ID de quem est&aacute; excluindo a amizade: ",
  /*90*/ "ID do(a) ex-amigo(a): ",
  /*91*/ "ID do(a) filho(a): ",
  /*92*/ "ID do(a) novo(a) filho(a): ",
  /*93*/ "ID do(a) pai(m&atilde;e): ",
  /*94*/ "ID do(a) novo(a) pai(m&atilde;e): ",
  /*95*/ "[SISTEMA DE RELACIONAMENTOS] Seu convite de amizade foi aceito",
  /*96*/ "[SISTEMA DE RELACIONAMENTOS] Seu convite de amizade foi rejeitado",
  /*97*/ "[SISTEMA DE RELACIONAMENTOS] Sua amizade foi exclu&iacute;da",
  /*98*/ "[SISTEMA DE RELACIONAMENTOS] Seu convite de amizade foi enviado",
  /*99*/ "[SISTEMA DE RELACIONAMENTOS] Voc&ecirc; foi convidado para entrar no nosso sistema",
  /*100*/"[SISTEMA DE RELACIONAMENTOS] Sua senha foi alterada", 
  /*101*/ "LISTA DE AMIGOS ENCONTRADOS",
};
  
#endif
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
char *showTextHelpMessage (unsigned helpCode)
{
  return (textHelpMessages[helpCode]);
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
char *showHtmlHelpMessage (unsigned helpCode)
{
  return (htmlHelpMessages[helpCode]);
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
void help (void)
{
  #ifdef ENGLISH
  printf ("Usage: ./relationshipSystem [OPTION] [ARGUMENTS]\n\n");
  printf ("List of options:\n\n");
  printf ("\
  [-n | --ncurses]\n\
        Run the program with NCURSES's interface.\n\n\
\
  [-h | --help]\n\
  	Show a complete help message with all options of command line with their respective arguments.\n\n\
\
  [-t | --install] <Username> <Full Name> <Email> <Homepage> <Street> <Home Number> <Complement>\n\
  		   <District> <City> <State> <Country> <Zip Code> <Telephone> <Cellular> <Gender>\n\
		   <Relationship Status> <Day of Born> <Month of Born> <Year of Born> <Description>\n\
	Install the system, including administrator's data.\n\
	All arguments must be filled, even if with a zero-size string \"\".\n\n\
\
  [-a | --add] <Username> <Category> <Full Name> <Email> <Homepage> <Street> <Home Number> <Complement>\n\
  	       <District> <City> <State> <Country> <Zip Code> <Telephone> <Cellular> <Gender>\n\
	       <Relationship Status> <Day of Born> <Month of Born> <Year of Born> <Description>\n\
	Add a new user to the system.\n\
	All arguments must be filled, even if with a zero-size string \"\".\n\n\
\
  [-e | --edit] <User ID> <Full Name> <Email> <Homepage> <Street> <Home Number> <Complement>\n\
	        <District> <City> <State> <Country> <Zip Code> <Telephone> <Cellular> <Gender>\n\
	        <Relationship Status> <Day of Born> <Month of Born> <Year of Born> <Description>\n\
	Edit user data.");
	
printf ("\
	All arguments must be filled, even if with a zero-size string \"\".\n\n");
	
printf ("  [-r | --remove] <User ID>\n\
	Remove a user from the system.\n\n");

printf ("  [-i | --invite] <User ID of who is inviting> <Full Name> <Email>\n\
	Invite someone to enter in the system.\n\n");

printf ("  [-I | --Invite] <User ID of who is inviting> <Friend`s User ID>\n\
  	Invite a user to enter in a friendship group.\n\n");

printf ("  [-F | --Friendship] <User ID>\n\
  	Get pending invitations of a user.\n\n");

printf ("  [-P | --Accept] <User ID of who is accepting the invite> <Friend`s User ID>\n\
  	Accept friendship invitation.\n\n");

printf ("  [-J | --Reject> <User ID of who is rejecting the invite> <Friend`s User ID>\n\
  	Reject friendship invitation.\n\n");

printf("  [-X | --Exclude] <User ID of who is excluding the friendship relation> <Friend`s User ID>\n\
  	Exclude friendship relation.\n\n");

printf ("  [-G | --Get] <User ID>\n\
  	Get friends of a user.\n\n");

printf ("  [-c | --change] <User ID>\n\
  	Change user category.\n\n");

printf ("  [-A | --Add] <Son`s User ID> <Parents`s User ID>\n\
  	Add parent relationship.\n\n");

printf ("  [-R | --Remove] <Son`s User ID> <Parent`s User ID>\n\
  	Remove parent relationship.\n\n");

printf ("  [-E | --Edit] <Son`s User ID> <Parent`s User ID> <New Son`s User ID> <New Parent`s User ID>\n\
  	Edit parent relationship.\n\n");

printf("  [-g | --get] <Key word>\n\
  	Search users.\n\n");

printf ("  [-m | --mount] <User ID> <Lower Level> <Upper level>\n\
  	Mount family tree.\n\n");

printf ("  [-p | --password] <User ID>\n\
  	Recovery password.\n\n");

printf ("  [-C | --Change] <User ID>\n\
  	Change password.\n\n");

printf ("  [-u | --upload] <User ID> <Filename>\n\
  	Upload user's picture.\n\n");
	
#elif PORTUGUESE
  printf ("Uso: ./relationshipSystem [OP��O] [ARGUMENTOS]\n\n");
  printf ("Lista de op��es:\n\n");
  printf ("\
  [-n | --ncurses]\n\
        Roda o programa com a interface gr�fica NCURSES.\n\n\
\
  [-h | --help]\n\
  	Exibe uma mensagem de ajuda completa, com todas as op��es de linha de comando com seus respectivos argumentos.\n\n\
\
  [-t | --install] <Username> <Nome Completo> <Email> <Homepage> <Logradouro> <N�mero> <Complemento>\n\
  		   <Bairro> <Cidade> <Estado> <Pa�s> <CEP> <Telefone> <Celular> <Sexo> <Estado Civil>\n\
		   <Dia de Nascimento> <M�s de Nascimento> <Ano de Nascimento> <Descri��o>\n\
	Instala o sistema, incluindo os dados do administrador.\n\
	Todos os argumentos s�o obrigat�rios, ainda que preenchidos com uma string de tamanho nulo \"\".\n\n\
\
  [-a | --add] <Username> <Categoria> <Nome Completo> <Email> <Homepage> <Logradouro> <N�mero>\n\
  	       <Complemento> <Bairro> <Cidade> <Estado> <Pa�s> <CEP> <Telefone> <Celular> <Sexo>\n\
	       <Estado Civil> <Dia de Nascimento> <M�s de Nascimento> <Ano de Nascimento> <Descri��o>\n\
	Adiciona um novo usu�rio ao sistema.\n\
	Todos os argumentos s�o obrigat�rios, ainda que preenchidos com uma string de tamanho nulo \"\".\n\n\
\
  [-e | --edit] <ID do Usu�rio> <Nome Completo> <Email> <Homepage> <Logradouro> <N�mero> <Complemento>\n\
  		<Bairro> <Cidade> <Estado> <Pa�s> <CEP> <Telefone> <Celular> <Sexo> <Estado Civil>\n\
		<Dia de Nascimento> <M�s de Nascimento> <Ano de Nascimento> <Descri��o>\n\
	Edita dados do usu�rio.");
	
printf ("\
	Todos os argumentos s�o obrigat�rios, ainda que preenchidos com uma string de tamanho nulo \"\".\n\n");
	
printf ("  [-r | --remove] <ID de Usu�rio>\n\
	Remove um usu�rio do sistema.\n\n");

printf ("  [-i | --invite] <ID do usu�rio que est� efetuando o convite> <Nome Completo> <Email>\n\
	Convida algu�m para entrar no sistema.\n\n");

printf ("  [-I | --Invite] <ID do usu�rio que est� efetuando o convite> <ID do usu�rio que vai receber o convite>\n\
  	Convida algu�m para iniciar uma rela��o de amizade.\n\n");

printf ("  [-F | --Friendship] <ID do usu�rio>\n\
  	Obt�m os convites pendentes de um usu�rio.\n\n");

printf ("  [-P | --Accept] <ID do usu�rio que est� aceitando o convite> <ID do usu�rio que efetuou o convite>\n\
  	Aceita convite de amizade.\n\n");

printf ("  [-J | --Reject> <ID do usu�rio que est� rejeitando o convite> <ID do usu�rio que efetuou o convite>\n\
  	Rejeita convite de amizade.\n\n");

printf("  [-X | --Exclude] <ID do usu�rio que est� excluindo amizade> <ID do ex-amigo>\n\
  	Exclui amizade.\n\n");

printf ("  [-G | --Get] <ID do usu�rio>\n\
  	Obt�m amigos de um usu�rio.\n\n");

printf ("  [-c | --change] <ID do usu�rio>\n\
  	Troca a categoria do usu�rio.\n\n");

printf ("  [-A | --Add] <ID do(a) filho(a)> <ID do(a) pai/m�e>\n\
  	Adiciona rela��o de parentesco.\n\n");

printf ("  [-R | --Remove] <ID do(a) filho(a)> <ID do(a) pai/m�e>\n\
  	Remove rela��o de parentesco.\n\n");

printf ("  [-E | --Edit] <ID do(a) filho(a)> <ID do(a) pai/m�e> <ID do(a) novo(a) filho(a)> <ID do(a) novo(a) pai/m�e>\n\
  	Edita rela��o de parentesco.\n\n");

printf("  [-g | --get] <Palavra-chave>\n\
  	Procura usu�rios.\n\n");

printf ("  [-m | --mount] <ID do usu�rio> <N�vel mais baixo> <N�vel mais alto>\n\
  	Monta �rvore geneal�gica.\n\n");

printf ("  [-p | --password] <ID do usu�rio>\n\
  	Recupera senha.\n\n");

printf ("  [-C | --Change] <ID do Usu�rio>\n\
  	Troca senha.\n\n");

printf ("  [-u | --upload] <ID do usu�rio> <Nome do Arquivo>\n\
  	Faz upload de foto do usu�rio.\n\n");
	
#endif
}
/*---------------------------------------------------------------------------------------------------------*/
