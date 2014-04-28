/*
 * Universidade do Brasil
 * Escola Politecnica
 * Departamento de Eletronica e Computacao
 * Computacao II
 * Prof. Marcelo Luiz Drumond Lanza
 *
 * File:                sendmail.h
 * Author:              Marcelo Luiz Drumond Lanza
 * Description:         
 * 
 * $Date: 2005/02/16 22:11:21 $
 * $Log: sendmail.h,v $
 * Revision 1.1  2005/02/16 22:11:21  marceloddm
 * Initial revision
 *
 *
 */

#ifndef __SENDMAIL__
#define __SENDMAIL__ "@(#)sendmail.h $Revision: 1.1 $"

#ifndef OK
#define OK					0
#endif
#define INVALID_SMTP_SERVER_ADDRESS		1
#define INVALID_FROM				2
#define INVALID_TO				3
#define INVALID_BODY				4
#define SOCKET_ERROR				5
#define CONNECT_ERROR				6
#define RECV_ERROR				7
#define SMTP_SERVER_ERROR			8
#define INVALID_CHARACTER			9
#define INVALID_CLIENT_DOMAIN			10


unsigned sendMail (char *, char *, unsigned, char *, char *, char *, char *, char *, char *, char *); 

#endif
