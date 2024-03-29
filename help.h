//===========================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira
// Description: help() primary function header file 
// Date: 29/11/2004
//===========================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: help.h,v $
 * Revision 1.8  2005/02/16 22:11:21  marceloddm
 * CGI's added
 *
 * Revision 1.7  2004/12/15 01:32:39  marceloddm
 * Constants added: RELATIONSHIP_SYSTEM__OPTION_MUST_COME_FIRST,RELATIONSHIP_SYSTEM__UNKNOWN_OPTION and RELATIONSHIP_SYSTEM__WELCOME_MESSAGE
 *
 * Revision 1.5  2004/12/14 02:51:39  marceloddm
 * Grammar corrections have been made
 *
 * Revision 1.4  2004/12/13 07:54:59  marceloddm
 *  Languages settings have been done
 * showTextHelpMessage() and showHtmlHelpMessage() added
 *
 * Revision 1.3  2004/12/11 12:37:48  marceloddm
 * Author changed for 'marceloddm'
 *
 * Revision 1.2  2004/11/30 00:29:24  root
 * I think that this file is now complete
 *
 * Revision 1.1  2004/11/29 21:49:02  root
 * Initial revision
 *
 */ 
 

#ifndef _HELP_H_
#define _HELP_H_ "@(#)help.h $Revision: 1.8 $"

#define GET_ADMINISTRATOR_PASSWORD__PROMPT_OF_PASSWORD				0
#define GET_ADMINISTRATOR_PASSWORD__PROMPT_OF_CONFIRMATION			1
#define QUESTION_OF_REINSTALL							2
#define RELATIONSHIP_SYSTEM__CONFIRMATION_OF_DO_NOT_REINSTALL			3
#define INSTALLATION_DONE_SUCCESSFULLY 			 			4
#define RELATIONSHIP_SYSTEM__OPTION_MUST_COME_FIRST				5
#define RELATIONSHIP_SYSTEM__UNKNOWN_OPTION					6
#define RELATIONSHIP_SYSTEM__WELCOME_MESSAGE					7
#define RELATIONSHIP_SYSTEM__PROMPT_OF_PASSWORD					8
#define RELATIONSHIP_SYSTEM__PROMPT_OF_CONFIRMATION				9	
#define NCURSES__TITLE								10
#define NCURSES__AUTHORS							11
#define NCURSES__INCREASE_SCREEN						12
#define NCURSES__MIN_SIZE_RECOMMENDED						13
#define NCURSES__ESC_TO_EXIT							14
#define NCURSES__ENTER_TO_SUBMIT						15
#define REINSTALL_FORM_DESCRIPTION						16
#define ADD_USER_FORM_DESCRIPTION						17
#define EDIT_USER_DATA_FORM_DESCRIPTION						18
#define REMOVE_USER_FORM_DESCRIPTION						19
#define INVITE_USER_FORM_DESCRIPTION						20
#define INVITE_FRIEND_FORM_DESCRIPTION						21
#define FRIENDSHIP_FORM_DESCRIPTION						22
#define ACCEPT_FORM_DESCRIPTION							23
#define REJECT_FORM_DESCRIPTION							24
#define EXCLUDE_FORM_DESCRIPTION						25
#define GET_FRIENDS_FORM_DESCRIPTION						26
#define CHANGE_CATEGORY_FORM_DESCRIPTION					27
#define ADD_PARENT_RELATIONSHIP_FORM_DESCRIPTION				28
#define REMOVE_PARENT_RELATIONSHIP_FORM_DESCRIPTION				29
#define EDIT_PARENT_RELATIONSHIP_FORM_DESCRIPTION				30
#define GET_USERS_FORM_DESCRIPTION						31
#define MOUNT_FORM_DESCRIPTION							32
#define RECOVERY_PASSWORD_FORM_DESCRIPTION					33
#define CHANGE_PASSWORD_FORM_DESCRIPTION					34
#define UPLOAD_FORM_DESCRIPTION							35
#define USER_ID_FIELD_DESCRIPTION						36
#define NEW_USER_PASSWORD_FIELD_DESCRIPTION					37
#define USERNAME_FIELD_DESCRIPTION						38
#define CATEGORY_FIELD_DESCRIPTION						39
#define NAME_FIELD_DESCRIPTION							40
#define EMAIL_FIELD_DESCRIPTION							41
#define HOMEPAGE_FIELD_DESCRIPTION						42
#define STREET_FIELD_DESCRIPTION						43
#define HOME_NUMBER_FIELD_DESCRIPTION						44
#define COMPLEMENT_FIELD_DESCRIPTION						45
#define DISTRICT_FIELD_DESCRIPTION						46
#define CITY_FIELD_DESCRIPTION							47
#define STATE_FIELD_DESCRIPTION							48
#define COUNTRY_FIELD_DESCRIPTION						49
#define ZIP_CODE_FIELD_DESCRIPTION						50
#define TEL_NUMBER_FIELD_DESCRIPTION						51
#define CELL_NUMBER_FIELD_DESCRIPTION						52
#define GENDER_FIELD_DESCRIPTION						53
#define RELATIONSHIP_STATUS_FIELD_DESCRIPTION					54
#define DAY_OF_BORN_FIELD_DESCRIPTION						55
#define MONTH_OF_BORN_FIELD_DESCRIPTION						56
#define YEAR_OF_BORN_FIELD_DESCRIPTION						57
#define DESCRIPTION_FIELD_DESCRIPTION						58
#define USER_ID_OF_WHO_IS_INVITING_FIELD_DESCRIPTION				59
#define USER_ID_OF_INVITED_USER_FIELD_DESCRIPTION				60
#define USER_ID_OF_WHO_IS_ACCEPTING_INVITATION_FIELD_DESCRIPTION		61
#define USER_ID_OF_WHO_IS_REJECTING_INVITATION_FIELD_DESCRIPTION		62
#define USER_ID_OF_WHO_IS_EXCLUDING_FRIENDSHIP_RELATION_FIELD_DESCRIPTION	63
#define NEW_CATEGORY_FIELD_DESCRIPTION						64
#define USER_ID_OF_SUN_FIELD_DESCRIPTION					65
#define USER_ID_OF_PARENT_FIELD_DESCRITION					66
#define USER_ID_OF_NEW_SUN_FIELD_DESCRIPTION					67
#define USER_ID_OF_NEW_PARENT_FIELD_DESCRITION					68
#define KEYWORD_FIELD_DESCRITION						69
#define LOWER_LEVEL_FIELD_DESCRIPTION						70
#define UPPER_LEVEL_FIELD_DESCRIPTION						71
#define FILENAME_FIELD_DESCRIPTION						72
#define CONFIRMATION_FIELD_DESCRIPTION						73
#define NCURSES__ERROR_IN_FORM_DATA						74
#define ADMINISTRATOR_PASS_FIELD_DESCRIPTION					75
#define NCURSES__PRESS_ANY_KEY_TO_CONTINUE					76
#define REQUIRE_NEW_WEB_USER_PASSWORD						77
#define NCURSES__BACKSPACE_TO_CLEAR						78
#define NCURSES__INFORM_USER_ID							79
#define NCURSES__INFORM_NEW_DATA						80
#define NCURSES__INFORM_SEARCH_KEY						81
#define SEARCH_KEY_FIELD_DESCRIPTION						82
#define LIST_OF_USERS_FOUND							83	
#define INVITING_USER_ID_FIELD_DESCRIPTION					84
#define INVITED_USER_ID_FIELD_DESCRIPTION					85
#define ACCEPTING_USER_ID_FIELD_DESCRIPTION					86
#define INVITER_USER_ID_FIELD_DESCRIPTION					87
#define REJECTING_USER_ID_FIELD_DESCRIPTION					88
#define EXCLUDING_USER_ID_FIELD_DESCRIPTION					89
#define EXCLUDED_USER_ID_FIELD_DESCRIPTION					90
#define SUN_USER_ID_FIELD_DESCRIPTION						91
#define NEW_SUN_USER_ID_FIELD_DESCRIPTION					92
#define PARENT_USER_ID_FIELD_DESCRIPTION					93
#define NEW_PARENT_USER_ID_FIELD_DESCRIPTION					94
#define ACCEPT_FRIENDSHIP_INVITATION__SUBJECT					95
#define REJECT_FRIENDSHIP_INVITATION__SUBJECT					96
#define EXCLUDE_FRIEND__SUBJECT							97
#define INVITE_FRIEND__SUBJECT							98
#define INVITE_USER__SUBJECT							99
#define RECOVERY_PASSWORD__SUBJECT						100
#define LIST_OF_FRIENDS_FOUND							101	




/*---------------------------------------------------------------------------------------------------------*/
char *showTextHelpMessage (unsigned helpCode);
/* 	
INPUT ARGUMENTS
	- unsigned helpCode 
 
DESCRIPTION
	The showTextHelpMessage() function reads the helpCode input argument and returns the corresponding text help message.
	
RETURNED VALUES
	The showTextHelpMessage() function returns a text help message string. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
char *showHtmlHelpMessage (unsigned helpCode);
/* 	
INPUT ARGUMENTS
	- unsigned helpCode 
 
DESCRIPTION
	The showHtmlHelpMessage() function reads the helpCode input argument and returns the corresponding html help message.
	
RETURNED VALUES
	The showTextHelpMessage() function returns a html help message string. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
void help (void);
/* 	
DESCRIPTION
	The help() function shows a help message.   
*/
/*---------------------------------------------------------------------------------------------------------*/

#endif

// $RCSfile: help.h,v $
