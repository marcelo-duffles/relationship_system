//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: ncursesMenu() primary function source file 
// Date: 24/12/2004
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: ncursesMenu.h,v $
 * Revision 1.2  2005/02/16 22:11:21  marceloddm
 * CGI's added
 *
 * Revision 1.1  2004/12/24 03:41:46  marceloddm
 * Initial revision
 *
 * Revision 1.1  2004/12/24 03:27:41  marceloddm
 * Initial revision
 *
 */


 
#ifndef _NCURSES_MENU_H_
#define _NCURSES_MENU_H_ "@(#)ncursesMenu.h$Revision: 1.2 $"


/*---------------------------------------------------------------------------------------------------------*/
unsigned ncursesMenu (void);
/* 	
DESCRIPTION
	The ncursesMenu() function shows a NCURSES graphic interface and treats correctly the option selected by the user.
	
RETURNED VALUES
	The ncursesMenu() function returns:
	- NCURSES__ERROR_INITIALIZING_NCURSES if an error occours while initializing the NCURSES mode;
	- NCURSES__ERROR_DISABLING_LINE_BUFFERING if an error occours while disabling line buffering and erase/kill character processing;
	- NCURSES__ERROR_DISABLING_ECHO if an error occours while disabling ECHO;
	- NCURSES__ERROR_ENABLING_KEYPAD if an error occours while enabling KEYPAD;
	- NCURSES__MEMORY_ALLOCATION_ERROR if an error occours while allocating memory;
	- NCURSES__ERROR_CREATING_NEW_MENU_ITEM if an error occours while creating a new menu item;
	- NCURSES__ERROR_CREATING_NEW_MENU if an error occours while creating a new menu;
	- NCURSES__ERROR_POSTING_MENU if an error occours while posting menu;
	- NCURSES__ERROR_UNPOSTING_MENU if an error occours while unposting menu;
	- NCURSES__ERROR_REFRESHING_TERMINAL if an error occours while refreshing the terminal;
	- NCURSES__ERROR_IN_MENU_DRIVER_FUNCTION if an error occours while calling the menu_driver() function;
	- NCURSES_ERROR_FREEING_MEMORY_ALLOCATED_TO_MENU_ITEMS if an error occours while freeing memory allocated to menu items;
	- NCURSES_ERROR_FREEING_MEMORY_ALLOCATED_TO_MENU if an error occours while freeing memory allocated to menu;
	- NCURSES__ERROR_FINALIZING_NCURSES if an error occours while finalizing the NCURSES mode;
	- OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

#endif 



/*$RCSfile: ncursesMenu.h,v $*/

