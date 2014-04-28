//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Polit�cnica
// Departamento de Eletr�nica e de Computa��o
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: ncursesMenu() primary function source file 
// Date: 22/12/2004
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: ncursesMenu.c,v $
 * Revision 1.2  2005/02/16 22:11:21  marceloddm
 * CGI's added
 *
 * Revision 1.1  2004/12/24 03:41:08  marceloddm
 * Initial revision
 *
 * Revision 1.1  2004/12/24 03:23:56  marceloddm
 * Initial revision
 *
 */


static const char rcsid [] = "$Id: ncursesMenu.c,v 1.2 2005/02/16 22:11:21 marceloddm Exp marceloddm $";

#include <stdlib.h>
#include <curses.h>
#include <menu.h>
#include <form.h>
#include <string.h>
#include "const.h"
#include "error.h"
#include "help.h"
#include "functions.h"
#include "install.h"
#include "addUser.h"
#include "editUserData.h"
#include "changeUserCategory.h"
#include "inviteUser.h"
#include "getUsers.h"
#include "getFriends.h"
#include "removeUser.h"
#include "inviteFriend.h"
#include "getFriendshipInvitation.h"
#include "acceptFriendshipInvitation.h"
#include "rejectFriendshipInvitation.h"
#include "excludeFriend.h"
#include "changePassword.h"
#include "recoveryPassword.h"
#include "addParentRelationship.h"
#include "removeParentRelationship.h"
#include "editParentRelationship.h"


unsigned ncursesMenu (void)
{
  unsigned index, selection, errorCode, count;	
  char temp[20+1];  
  char idField1[20+1];  
  char idField2[20+1];
  char idField3[20+1];  
  char idField4[20+1];    
  char newPass[MAX_LENGTH_PLAIN_PASS +1];
  boolean idIsValid, searchKeyIsValid;
  ITEM **menuItems;
  MENU *menu;
  FIELD **formFields, **tempFormFields;
  FORM *form, *tempForm;
  WINDOW *menuWindow, *menuSubWindow;
  int option;
  userDataType *first, *last;
  userDataType userData, buffer;
  char *menuOptions[] =
  {
    "reinstall",
    "add",
    "edit",
    "remove",
    "invite",
    "Invite",
    "Friendship",
    "Accept",
    "Reject",
    "Exclude",
    "Get",
    "change",
    "Add",
    "Remove",
    "Edit",
    "get",
    "mount",
    "password",
    "Change",
    "upload",
    "Exit"
  };
    
  #ifdef ENGLISH
    char *menuDescriptions[] =
    {
      "Reinstall the system",
      "Add a new user to the system",
      "Edit user data",
      "Remove a user from the system",
      "Invite someone to enter in the system",
      "Invite a user to the enter in a friendship group",
      "Get pending invitations of a user",
      "Accept friendship invitation",
      "Reject friendship invitation",
      "Exclude friendship relation",
      "Get friends of a user",
      "Change user category",
      "Add parent relationship",
      "Remove parent relationship",
      "Edit parent relationship",
      "Search users",
      "Mount family tree",
      "Recovery password",
      "Change password",
      "Upload user's picture",
      "Exit from the system" 
    };
  #elif PORTUGUESE
    char *menuDescriptions[] =
    {
      "Reinstala o sistema",
      "Adiciona um novo usuario ao sistema",
      "Edita os dados de um usuario",
      "Remove um usuario do sistema",
      "Convida alguem para entrar no sistema",
      "Convida alguem para iniciar uma relacao de amizade",
      "Obtem convites pendentes de um usuario",
      "Aceita convite de amizade",
      "Rejeita convite de amizade",
      "Exclui amizade",
      "Obtem amigos de um usuario",
      "Troca categoria de usuario",
      "Adiciona relacao de parentesco",
      "Remove relacao de parentesco",
      "Edita relacao de parentesco",
      "Procura usuarios",
      "Monta arvore genealogica",
      "Recupera senha",
      "Troca senha",
      "Faz upload de foto do usuario",
      "Sai do sistema" 
    };
  #endif

    
  if ((stdscr = initscr ()) == NULL)
    return (NCURSES__ERROR_INITIALIZING_NCURSES);
  if (cbreak () != OK)
  {
    endwin ();
    return (NCURSES__ERROR_DISABLING_LINE_BUFFERING);
  }
  if (noecho () != OK)
  {
    endwin ();
    return (NCURSES__ERROR_DISABLING_ECHO);
  } 
  if (keypad (stdscr, TRUE) != OK)
  {
    endwin ();
    return (NCURSES__ERROR_ENABLING_KEYPAD);
  }
  if ((has_colors ()) || can_change_color ())
  {
    start_color ();
    init_pair (1, COLOR_BLUE, COLOR_BLACK);
    init_pair (2, COLOR_CYAN, COLOR_BLACK);
    init_pair (3, COLOR_WHITE, COLOR_BLACK);
    init_pair (4, COLOR_YELLOW, COLOR_BLACK);
    attrset (COLOR_PAIR(2));
  }
  
  if ((LINES < MIN_NB_LINES) || (COLS < MIN_NB_COLS))
  {
    mvprintw (5, 1, "%s", showTextHelpMessage (NCURSES__INCREASE_SCREEN));
    mvprintw (7, 1, "%s", showTextHelpMessage (NCURSES__MIN_SIZE_RECOMMENDED));
    mvprintw (LINES -10, FIELD_START_X +2, "%s", showTextHelpMessage (NCURSES__PRESS_ANY_KEY_TO_CONTINUE));
    getch ();
    refresh ();
    endwin ();
  }
  
  if ((LINES < MIN_NB_LINES) || (COLS < MIN_NB_COLS))
  {
    endwin ();
    return (NCURSES__ERROR_SIZE_SMALLER_THAN_RECOMMENDED);
  }

  for (selection = option = NCURSES__REINSTALL_OPTION; selection != NCURSES__EXIT_OPTION; )
  {
    menuItems = (ITEM **) calloc (NCURSES__NB_MENU_OPTIONS +1, sizeof (ITEM *));
    if (menuItems == NULL)
    {
      endwin ();
      return (NCURSES__MEMORY_ALLOCATION_ERROR);
    }
    for (index = 0; index < NCURSES__NB_MENU_OPTIONS; index++)
    {
      menuItems[index] = new_item (menuOptions[index], menuDescriptions[index]);
      if (menuItems[index] == NULL)
      {
	free (menuItems);
	endwin ();
        return (NCURSES__ERROR_CREATING_NEW_MENU_ITEM);
      }
    }
    menuItems[index] = NULL;
    if ((menu = new_menu (menuItems)) == NULL)
    {
      freeMenuItemsResources (menuItems);
      endwin ();
      return (NCURSES__ERROR_CREATING_NEW_MENU);
    }

    clear ();
    wattron (stdscr, COLOR_PAIR(2));
    mvprintw (1, (COLS - strlen (showTextHelpMessage (NCURSES__TITLE)))/2, "%s", showTextHelpMessage (NCURSES__TITLE));
    mvprintw (2, (COLS - strlen (showTextHelpMessage (NCURSES__AUTHORS)))/2, "%s", showTextHelpMessage (NCURSES__AUTHORS));
    wattroff (stdscr, COLOR_PAIR(2));
	
    if ((menuWindow = newwin (NB_MENU_LINES, NB_MENU_COLS, (LINES - NB_MENU_LINES)/2 , (COLS - NB_MENU_COLS)/2)) == NULL)
    {
      freeMenuResources (menu, menuItems);	  
      endwin ();
      return (NCURSES__ERROR_CREATING_MENU_WINDOW);
    }
    if (keypad (menuWindow, TRUE) != OK)
    {
      freeMenuResources (menu, menuItems);
      endwin ();
      return (NCURSES__ERROR_ENABLING_KEYPAD);
    }
    if (set_menu_win (menu, menuWindow) != OK)
    {
      freeMenuResources (menu, menuItems);
      endwin ();
      return (NCURSES__ERROR_SETTING_MENU_WINDOW);
    }
    if ((menuSubWindow = derwin (menuWindow, NB_MENU_LINES -4, NB_MENU_COLS -2, 3, 1)) == NULL)
    {
      freeMenuResources (menu, menuItems);
      endwin ();
      return (NCURSES__ERROR_CREATING_MENU_SUB_WINDOW);
    }
    if (set_menu_sub (menu, menuSubWindow) != OK)
    {
      freeMenuResources (menu, menuItems);
      endwin ();
      return (NCURSES__ERROR_SETTING_MENU_SUB_WINDOW);
    }
    set_menu_mark (menu, " --> ");
    wattrset (menuSubWindow, COLOR_PAIR(2));
    wattrset (menuWindow, COLOR_PAIR(1));
    if (box (menuWindow, 0, 0) != OK)
    {
      freeMenuResources (menu, menuItems);
      endwin ();
      return (NCURSES__ERROR_CREATING_MENU_BORDER);
    }
    printInMiddle (menuWindow, 1, 0, NB_MENU_COLS, "MENU", COLOR_PAIR(2));
    mvwaddch (menuWindow, 2, 0, ACS_LTEE);
    mvwhline (menuWindow, 2, 1, ACS_HLINE, NB_MENU_COLS -2);
    mvwaddch (menuWindow, 2, NB_MENU_COLS -1, ACS_RTEE);
    mvprintw (LINES -2, 0, "%s", showTextHelpMessage (NCURSES__ESC_TO_EXIT));

    if (set_menu_format (menu, NCURSES__NB_MENU_OPTIONS, 1) != OK)
    {
      freeMenuResources (menu, menuItems);
      endwin ();
      return (NCURSES__ERROR_SETTING_MENU_FORMAT);
    }
    if (post_menu (menu) != OK)
    {
      freeMenuResources (menu, menuItems);
      endwin ();
      return (NCURSES__ERROR_POSTING_MENU);
    }
    if (refresh () != OK)
    {
      unpost_menu (menu);
      freeMenuResources (menu, menuItems);
      endwin ();
      return (NCURSES__ERROR_REFRESHING_TERMINAL);
    }
    if (wrefresh (menuWindow) != OK)
    {
      unpost_menu (menu);
      freeMenuResources (menu, menuItems);
      endwin ();
      return (NCURSES__ERROR_REFRESHING_MENU_WINDOW);
    }

    for (selection = NCURSES__REINSTALL_OPTION; ((option = wgetch (menuWindow)) != ENTER) && (option != ESCAPE); )
    {
      switch (option)
      {
        case (KEY_DOWN):
	  if (selection != NCURSES__EXIT_OPTION)
	  {
	    if (menu_driver (menu, REQ_DOWN_ITEM) != OK)
            {
	      unpost_menu (menu);
              freeMenuResources (menu, menuItems);
	      endwin ();
	      return (NCURSES__ERROR_IN_MENU_DRIVER_FUNCTION);
	    }
	    selection++;
	  }
        break;

        case (KEY_UP):
	  if (selection != NCURSES__REINSTALL_OPTION)
	  {
            if (menu_driver (menu, REQ_UP_ITEM) != OK)
            {
              unpost_menu (menu);
              freeMenuResources (menu, menuItems);
	      endwin ();
	      return (NCURSES__ERROR_IN_MENU_DRIVER_FUNCTION);
	    }
	    selection--;
	  }
        break;
      }
      if (wrefresh (menuWindow) != OK)
      {
        unpost_menu (menu);
        freeMenuResources (menu, menuItems);
	endwin ();
        return (NCURSES__ERROR_REFRESHING_MENU_WINDOW);
      }
    }  
    
    if (unpost_menu (menu) != OK)
    {
      endwin ();
      return (NCURSES__ERROR_UNPOSTING_MENU);
    }
    if ((errorCode = freeMenuResources (menu, menuItems)) != OK)
    {
      endwin ();
      return (errorCode);
    }

    clear ();
    if (refresh () != OK)
    {
      endwin ();
      return (NCURSES__ERROR_REFRESHING_TERMINAL);
    }

    if (option == ESCAPE) 
      selection = NCURSES__EXIT_OPTION;	    
      
    switch (selection)
    {
      case (NCURSES__REINSTALL_OPTION):
        if ((formFields = createFormFields ('t')) == NULL)
	{
	  endwin ();
          return (NCURSES__ERROR_CREATING_FORM_FIELDS);
        }

	if ((form = new_form (formFields)) == NULL)
	{
	  freeFormFieldsResources (formFields);
	  endwin ();
	  return (NCURSES__ERROR_CREATING_FORM);
	}

	if (post_form (form) != OK)
	{
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_POSTING_FORM);
	}
	
	if (refresh () != OK)
	{
	  unpost_form (form);
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	}
	set_current_field (form, formFields[0]);
	showDescriptionsOfFields ('t');;
        wattron (stdscr, COLOR_PAIR(4));
	mvprintw (LINES -4, 2, "%s", showTextHelpMessage (NCURSES__BACKSPACE_TO_CLEAR));
	mvprintw (LINES -3, 2, "%s", showTextHelpMessage (NCURSES__ENTER_TO_SUBMIT));
        mvprintw (LINES -2, 2, "%s", showTextHelpMessage (NCURSES__ESC_TO_EXIT));
        wattroff (stdscr, COLOR_PAIR(4));
	move (FIELD_START_Y, FIELD_START_X);
	if ((errorCode = setInitialValuesOfFields (form, &userData,'t')) != OK)
        {
	  unpost_form (form);
	  freeFormResources (form, formFields);
	  endwin ();
	  return (errorCode);
	}

	if (refresh () != OK)
	{
	  unpost_form (form);
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	}

	while ((option = getch ()) != ENTER)
	  switch (option)
	  {
	    case (ESCAPE):
              unpost_form (form);
              freeFormResources (form, formFields);
	      endwin ();
	      return (OK);
	    break;
	    case (KEY_DOWN):
              if (form_driver (form, REQ_NEXT_FIELD) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
              if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_UP):
              if (form_driver (form, REQ_PREV_FIELD) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
              if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_LEFT):
              if (form_driver (form, REQ_PREV_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_RIGHT):
              if (form_driver (form, REQ_NEXT_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (BACKSPACE):
              if (form_driver (form, REQ_DEL_PREV) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (DEL):
              if (form_driver (form, REQ_DEL_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    default:
              if (form_driver (form, option) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
	  }
        if (form_driver (form, REQ_NEXT_FIELD) == E_SYSTEM_ERROR)
        {
          unpost_form (form);
          freeFormResources (form, formFields);
	  endwin ();
          return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
        }
        if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
        {
          unpost_form (form);
          freeFormResources (form, formFields);
	  endwin ();
          return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
        }
	
        if ((errorCode = repairFormData (&userData, formFields, 't')) != OK)
	{
	  if ((errorCode == REPAIR_FORM_DATA__NO_USER_DATA) || (errorCode == REPAIR_FORM_DATA__NO_FORM_FIELDS) || (errorCode == REPAIR_FORM_DATA__UNKNOWN_OPTION))
	  {
	    unpost_form (form);
	    freeFormResources (form, formFields);
	    endwin ();
	    return (errorCode);
	  }
	  else
	    mvprintw (LINES -6, FIELD_START_X, "%s", showTextErrorMessage (errorCode));
	}
	else
	  if ((errorCode = checkUserData (&userData)) != OK)
            mvprintw (LINES -6, FIELD_START_X, "%s", showTextErrorMessage (errorCode));
          else
	  {
	    if ((errorCode = backupSystemFiles ()) != OK)
	    {
	      endwin ();
	      return (errorCode);
	    }
	    if ((errorCode = install (&userData)) != OK)
	      mvprintw (LINES -6, FIELD_START_X, "%s", showTextHelpMessage (errorCode));
	    else
	      mvprintw (LINES -6, FIELD_START_X, "%s", showTextHelpMessage (INSTALLATION_DONE_SUCCESSFULLY));
          }
       
	mvprintw (LINES -4, FIELD_START_X, "%s", showTextHelpMessage (NCURSES__PRESS_ANY_KEY_TO_CONTINUE));
	getch ();
	if (refresh () != OK)
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	  
	if (unpost_form (form) != OK)
	{
	  endwin ();
          return (NCURSES__ERROR_UNPOSTING_FORM);
	}
        if ((errorCode = freeFormResources (form, formFields)) != OK)
	{
	  endwin ();
          return (errorCode);
	}
      break;
    
      case (NCURSES__ADD_USER_OPTION):
        if ((formFields = createFormFields ('a')) == NULL)
	{
	  endwin ();
          return (NCURSES__ERROR_CREATING_FORM_FIELDS);
        }

	if ((form = new_form (formFields)) == NULL)
	{
	  freeFormFieldsResources (formFields);
	  endwin ();
	  return (NCURSES__ERROR_CREATING_FORM);
	}

	if (post_form (form) != OK)
	{
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_POSTING_FORM);
	}
	
	if (refresh () != OK)
	{
	  unpost_form (form);
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	}
	set_current_field (form, formFields[0]);
	showDescriptionsOfFields ('a');;
        wattron (stdscr, COLOR_PAIR(4));
	mvprintw (LINES -4, 2, "%s", showTextHelpMessage (NCURSES__BACKSPACE_TO_CLEAR));
	mvprintw (LINES -3, 2, "%s", showTextHelpMessage (NCURSES__ENTER_TO_SUBMIT));
        mvprintw (LINES -2, 2, "%s", showTextHelpMessage (NCURSES__ESC_TO_EXIT));
        wattroff (stdscr, COLOR_PAIR(4));
	move (FIELD_START_Y, FIELD_START_X);

	if (refresh () != OK)
	{
	  unpost_form (form);
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	}

	while ((option = getch ()) != ENTER)
	  switch (option)
	  {
	    case (ESCAPE):
              unpost_form (form);
              freeFormResources (form, formFields);
	      endwin ();
	      return (OK);
	    break;
	    case (KEY_DOWN):
              if (form_driver (form, REQ_NEXT_FIELD) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
              if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_UP):
              if (form_driver (form, REQ_PREV_FIELD) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
              if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_LEFT):
              if (form_driver (form, REQ_PREV_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_RIGHT):
              if (form_driver (form, REQ_NEXT_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (BACKSPACE):
              if (form_driver (form, REQ_DEL_PREV) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (DEL):
              if (form_driver (form, REQ_DEL_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    default:
              if (form_driver (form, option) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
	  }
        if (form_driver (form, REQ_NEXT_FIELD) == E_SYSTEM_ERROR)
        {
          unpost_form (form);
          freeFormResources (form, formFields);
	  endwin ();
          return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
        }
        if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
        {
          unpost_form (form);
          freeFormResources (form, formFields);
	  endwin ();
          return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
        }
	
        if ((errorCode = repairFormData (&userData, formFields, 'a')) != OK)
	{
	  if ((errorCode == REPAIR_FORM_DATA__NO_USER_DATA) || (errorCode == REPAIR_FORM_DATA__NO_FORM_FIELDS) || (errorCode == REPAIR_FORM_DATA__UNKNOWN_OPTION))
	  {
	    unpost_form (form);
	    freeFormResources (form, formFields);
	    endwin ();
	    return (errorCode);
	  }
	  else
	    mvprintw (LINES -6, FIELD_START_X, "%s", showTextErrorMessage (errorCode));
	}
	else
	  if ((errorCode = checkUserData (&userData)) != OK)
            mvprintw (LINES -6, FIELD_START_X, "%s", showTextErrorMessage (errorCode));
          else
	  {
	    errorCode = addUser (&userData);
	    mvprintw (LINES -6, FIELD_START_X, "%s", showTextErrorMessage (errorCode));
          }
       
	mvprintw (LINES -4, FIELD_START_X, "%s", showTextHelpMessage (NCURSES__PRESS_ANY_KEY_TO_CONTINUE));
	getch ();
	if (refresh () != OK)
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	  
	if (unpost_form (form) != OK)
	{
	  endwin ();
          return (NCURSES__ERROR_UNPOSTING_FORM);
	}
        if ((errorCode = freeFormResources (form, formFields)) != OK)
	{
	  endwin ();
          return (errorCode);
	}
      break;

      case (NCURSES__EDIT_OPTION):
        formFields = (FIELD **) calloc (1 +1, sizeof (FIELD *));
        if ((formFields[0] = new_field (FIELD_HEIGHT, 20, FIELD_START_Y +6, FIELD_START_X, 0, 0)) == NULL)
        {
          free (formFields);
          return (NCURSES__ERROR_CREATING_FORM_FIELDS);
        }
	formFields[1] = NULL;
        set_field_back (formFields[0], A_UNDERLINE);
        set_field_fore (formFields[0], COLOR_PAIR(3));
        set_field_pad  (formFields[0], '_');
        field_opts_off (formFields[0], O_AUTOSKIP);
	if ((form = new_form (formFields)) == NULL)
	{
	  freeFormFieldsResources (formFields);
	  endwin ();
	  return (NCURSES__ERROR_CREATING_FORM);
	}      
	if (post_form (form) != OK)
	{
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_POSTING_FORM);
	}	
	if (refresh () != OK)
	{
	  unpost_form (form);
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	}
	set_current_field (form, formFields[0]);
        printInMiddle (stdscr, 5, 0, COLS, showTextHelpMessage (NCURSES__INFORM_USER_ID), COLOR_PAIR(4));
        wattron (stdscr, COLOR_PAIR(2));
        mvprintw (FIELD_START_Y +6, 15, "%s", showTextHelpMessage (USER_ID_FIELD_DESCRIPTION));	
        wattroff (stdscr, COLOR_PAIR(2));
        wattron (stdscr, COLOR_PAIR(4));	
	mvprintw (LINES -6, 4, "%s", showTextHelpMessage (NCURSES__BACKSPACE_TO_CLEAR));
	mvprintw (LINES -5, 4, "%s", showTextHelpMessage (NCURSES__ENTER_TO_SUBMIT));
        mvprintw (LINES -4, 4, "%s", showTextHelpMessage (NCURSES__ESC_TO_EXIT));
        wattroff (stdscr, COLOR_PAIR(4));
	move (FIELD_START_Y +6, FIELD_START_X);	
	if (refresh () != OK)
	{
	  unpost_form (form);
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	}	
	while ((option = getch ()) != ENTER)
	  switch (option)
	  {
	    case (ESCAPE):
              unpost_form (form);
              freeFormResources (form, formFields);
	      endwin ();
	      return (OK);
	    break;
	    case (KEY_LEFT):
              if (form_driver (form, REQ_PREV_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_RIGHT):
              if (form_driver (form, REQ_NEXT_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (BACKSPACE):
              if (form_driver (form, REQ_DEL_PREV) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (DEL):
              if (form_driver (form, REQ_DEL_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    default:
              if (form_driver (form, option) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
	  }
        if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
        {
          unpost_form (form);
          freeFormResources (form, formFields);
	  endwin ();
          return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
        }	
	stringCopy (temp, repairString (field_buffer (formFields[0], 0)), 20);
	if ((errorCode = checkField (temp, "0123456789", 1, 20)) != OK)
	{
	  idIsValid = false;
	  mvprintw (LINES -12, FIELD_START_X+2, "%s", showTextErrorMessage (errorCode));
	}
	else
	{
	  idIsValid = true;
	  mvprintw (LINES -12, FIELD_START_X+2, "%s", showTextErrorMessage (OK));
	}
        mvprintw (LINES -10, FIELD_START_X+2, "%s", showTextHelpMessage (NCURSES__PRESS_ANY_KEY_TO_CONTINUE));
	getch ();
	if (refresh () != OK)
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	if (unpost_form (form) != OK)
	{
	  endwin ();
          return (NCURSES__ERROR_UNPOSTING_FORM);
	}
        if ((errorCode = freeFormResources (form, formFields)) != OK)
	{
	  endwin ();
          return (errorCode);
	}	
	

	if (idIsValid)
	{  
	  userData.userId = strtoul (temp, NULL, 10);	
	  clear ();
	  if (refresh () != OK)
	    return (NCURSES__ERROR_REFRESHING_TERMINAL);
          if ((formFields = createFormFields ('e')) == NULL)
	  {
	    endwin ();
            return (NCURSES__ERROR_CREATING_FORM_FIELDS);
          }

	  if ((form = new_form (formFields)) == NULL)
	  {
	    freeFormFieldsResources (formFields);
	    endwin ();
	    return (NCURSES__ERROR_CREATING_FORM);
	  }

	  if (post_form (form) != OK)
	  {
	    freeFormResources (form, formFields);
	    endwin ();
	    return (NCURSES__ERROR_POSTING_FORM);
	  }
	
	  if (refresh () != OK)
	  {
	    unpost_form (form);
	    freeFormResources (form, formFields);
	    endwin ();
	    return (NCURSES__ERROR_REFRESHING_TERMINAL);
	  }
	  set_current_field (form, formFields[0]);
	  showDescriptionsOfFields ('e');;
          wattron (stdscr, COLOR_PAIR(4));
	  mvprintw (LINES -4, 2, "%s", showTextHelpMessage (NCURSES__BACKSPACE_TO_CLEAR));
	  mvprintw (LINES -3, 2, "%s", showTextHelpMessage (NCURSES__ENTER_TO_SUBMIT));
          mvprintw (LINES -2, 2, "%s", showTextHelpMessage (NCURSES__ESC_TO_EXIT));
          wattroff (stdscr, COLOR_PAIR(4));
	  move (FIELD_START_Y, FIELD_START_X);
	  if ((errorCode = setInitialValuesOfFields (form, &userData,'e')) != OK)
          {
	    unpost_form (form);
	    freeFormResources (form, formFields);
	    endwin ();
	    return (errorCode);
	  }

	  if (refresh () != OK)
          {
	    unpost_form (form);
	    freeFormResources (form, formFields);
	    endwin ();
	    return (NCURSES__ERROR_REFRESHING_TERMINAL);
	  }

	  while ((option = getch ()) != ENTER)
	    switch (option)
	    {
	      case (ESCAPE):
                unpost_form (form);
                freeFormResources (form, formFields);
	        endwin ();
	        return (OK);
	      break;
	      case (KEY_DOWN):
                if (form_driver (form, REQ_NEXT_FIELD) == E_SYSTEM_ERROR)
                {
                  unpost_form (form);
                  freeFormResources (form, formFields);
	   	  endwin ();
	          return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	        }
                if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
                {
                  unpost_form (form);
                  freeFormResources (form, formFields);
		  endwin ();
	          return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	        }
              break;
	      case (KEY_UP):
                if (form_driver (form, REQ_PREV_FIELD) == E_SYSTEM_ERROR)
                {
                  unpost_form (form);
                  freeFormResources (form, formFields);
		  endwin ();
	          return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	        }
                if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
                {
                  unpost_form (form);
                  freeFormResources (form, formFields);
		  endwin ();
	          return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	        }
              break;
	      case (KEY_LEFT):
                if (form_driver (form, REQ_PREV_CHAR) == E_SYSTEM_ERROR)
                {
                  unpost_form (form);
                  freeFormResources (form, formFields);
	   	  endwin ();
	          return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	        }
              break;
	      case (KEY_RIGHT):
                if (form_driver (form, REQ_NEXT_CHAR) == E_SYSTEM_ERROR)
                {
                  unpost_form (form);
                  freeFormResources (form, formFields);
		  endwin ();
	          return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	        }
              break;
	      case (BACKSPACE):
                if (form_driver (form, REQ_DEL_PREV) == E_SYSTEM_ERROR)
                {
                  unpost_form (form);
                  freeFormResources (form, formFields);
		  endwin ();
	          return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	        }
              break;
	      case (DEL):
                if (form_driver (form, REQ_DEL_CHAR) == E_SYSTEM_ERROR)
                {
                  unpost_form (form);
                  freeFormResources (form, formFields);
		  endwin ();
	          return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	        }
              break;
	      default:
                if (form_driver (form, option) == E_SYSTEM_ERROR)
                {
                  unpost_form (form);
                  freeFormResources (form, formFields);
		  endwin ();
	          return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	        }
	    }
          if (form_driver (form, REQ_NEXT_FIELD) == E_SYSTEM_ERROR)
          {
            unpost_form (form);
            freeFormResources (form, formFields);
	    endwin ();
            return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
          }
          if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
          {
            unpost_form (form);
            freeFormResources (form, formFields);
	    endwin ();
            return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
          }
	  
	  if ((errorCode = getDataFromId (userData.userId, &userData)) != OK)
	  {
	    unpost_form (form);
	    freeFormResources (form, formFields);
	    endwin ();
	    return (errorCode);
	  }
	  if (userData.category == relative)
	  {
	    userData.plainPass[0]     = EOS;
	    userData.encryptedPass[0] = EOS;
	    userData.userName[0]      = EOS;
	  }
	  else
	  {
	    strcpy (userData.plainPass, "noPass");
	    if ((errorCode = encodePassword (userData.plainPass, userData.encryptedPass)) != OK)
	    {
	      unpost_form (form);
	      freeFormResources (form, formFields);
	      endwin ();
	      return (errorCode);
	    }  
	  }
	    
          if ((errorCode = repairFormData (&userData, formFields, 'e')) != OK)
	  {
	    if ((errorCode == REPAIR_FORM_DATA__NO_USER_DATA) || (errorCode == REPAIR_FORM_DATA__NO_FORM_FIELDS) || (errorCode == REPAIR_FORM_DATA__UNKNOWN_OPTION))
	    {
	      unpost_form (form);
	      freeFormResources (form, formFields);
	      endwin ();
	      return (errorCode);
	    }
	    else
	      mvprintw (LINES -6, FIELD_START_X, "%s", showTextErrorMessage (errorCode));
	  }
	  else
	    if ((errorCode = checkUserData (&userData)) != OK)
                mvprintw (LINES -6, FIELD_START_X, "%s", showTextErrorMessage (errorCode));
            else
	    {
	      errorCode = editUserData (&userData);
	      mvprintw (LINES -6, FIELD_START_X, "%s", showTextErrorMessage (errorCode));
            }
       
	  mvprintw (LINES -4, FIELD_START_X, "%s", showTextHelpMessage (NCURSES__PRESS_ANY_KEY_TO_CONTINUE));
	  getch ();
  	  if (refresh () != OK)
	    return (NCURSES__ERROR_REFRESHING_TERMINAL);
	  
	  if (unpost_form (form) != OK)
	  {
	    endwin ();
            return (NCURSES__ERROR_UNPOSTING_FORM);
	  }
          if ((errorCode = freeFormResources (form, formFields)) != OK)
 	  {
	    endwin ();
            return (errorCode);
	  }
	}
        break;

      case (NCURSES__REMOVE_OPTION):
        formFields = (FIELD **) calloc (1 +1, sizeof (FIELD *));
        if ((formFields[0] = new_field (FIELD_HEIGHT, 20, FIELD_START_Y +6, FIELD_START_X, 0, 0)) == NULL)
        {
          free (formFields);
          return (NCURSES__ERROR_CREATING_FORM_FIELDS);
        }
	formFields[1] = NULL;
        set_field_back (formFields[0], A_UNDERLINE);
        set_field_fore (formFields[0], COLOR_PAIR(3));
        set_field_pad  (formFields[0], '_');
        field_opts_off (formFields[0], O_AUTOSKIP);
	if ((form = new_form (formFields)) == NULL)
	{
	  freeFormFieldsResources (formFields);
	  endwin ();
	  return (NCURSES__ERROR_CREATING_FORM);
	}      
	if (post_form (form) != OK)
	{
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_POSTING_FORM);
	}	
	if (refresh () != OK)
	{
	  unpost_form (form);
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	}
	set_current_field (form, formFields[0]);
        printInMiddle (stdscr, 5, 0, COLS, showTextHelpMessage (NCURSES__INFORM_USER_ID), COLOR_PAIR(4));
        wattron (stdscr, COLOR_PAIR(2));
        mvprintw (FIELD_START_Y +6, 15, "%s", showTextHelpMessage (USER_ID_FIELD_DESCRIPTION));	
        wattroff (stdscr, COLOR_PAIR(2));
        wattron (stdscr, COLOR_PAIR(4));	
	mvprintw (LINES -6, 4, "%s", showTextHelpMessage (NCURSES__BACKSPACE_TO_CLEAR));
	mvprintw (LINES -5, 4, "%s", showTextHelpMessage (NCURSES__ENTER_TO_SUBMIT));
        mvprintw (LINES -4, 4, "%s", showTextHelpMessage (NCURSES__ESC_TO_EXIT));
        wattroff (stdscr, COLOR_PAIR(4));
	move (FIELD_START_Y +6, FIELD_START_X);	
	if (refresh () != OK)
	{
	  unpost_form (form);
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	}	
	while ((option = getch ()) != ENTER)
	  switch (option)
	  {
	    case (ESCAPE):
              unpost_form (form);
              freeFormResources (form, formFields);
	      endwin ();
	      return (OK);
	    break;
	    case (KEY_LEFT):
              if (form_driver (form, REQ_PREV_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_RIGHT):
              if (form_driver (form, REQ_NEXT_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (BACKSPACE):
              if (form_driver (form, REQ_DEL_PREV) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (DEL):
              if (form_driver (form, REQ_DEL_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    default:
              if (form_driver (form, option) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
	  }
        if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
        {
          unpost_form (form);
          freeFormResources (form, formFields);
	  endwin ();
          return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
        }	
	stringCopy (temp, repairString (field_buffer (formFields[0], 0)), 20);
	if ((errorCode = checkField (temp, "0123456789", 1, 20)) != OK)
	  mvprintw (LINES -12, FIELD_START_X+2, "%s", showTextErrorMessage (errorCode));
	else
	{  
	  errorCode = removeUser (strtoul (temp, NULL, 10));
	  mvprintw (LINES -12, FIELD_START_X+2, "%s", showTextErrorMessage (errorCode));
	}
	  
        mvprintw (LINES -10, FIELD_START_X+2, "%s", showTextHelpMessage (NCURSES__PRESS_ANY_KEY_TO_CONTINUE));
	getch ();
	if (refresh () != OK)
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	if (unpost_form (form) != OK)
	{
	  endwin ();
          return (NCURSES__ERROR_UNPOSTING_FORM);
	}
        if ((errorCode = freeFormResources (form, formFields)) != OK)
	{
	  endwin ();
          return (errorCode);
	}
      break;

      case (NCURSES__INVITE_USER_OPTION):
        if ((formFields = createFormFields ('i')) == NULL)
	{
	  endwin ();
          return (NCURSES__ERROR_CREATING_FORM_FIELDS);
        }

	if ((form = new_form (formFields)) == NULL)
	{
	  freeFormFieldsResources (formFields);
	  endwin ();
	  return (NCURSES__ERROR_CREATING_FORM);
	}

	if (post_form (form) != OK)
	{
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_POSTING_FORM);
	}
	
	if (refresh () != OK)
	{
	  unpost_form (form);
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	}
	set_current_field (form, formFields[0]);
	showDescriptionsOfFields ('i');;
        wattron (stdscr, COLOR_PAIR(4));
	mvprintw (LINES -4, 2, "%s", showTextHelpMessage (NCURSES__BACKSPACE_TO_CLEAR));
	mvprintw (LINES -3, 2, "%s", showTextHelpMessage (NCURSES__ENTER_TO_SUBMIT));
        mvprintw (LINES -2, 2, "%s", showTextHelpMessage (NCURSES__ESC_TO_EXIT));
        wattroff (stdscr, COLOR_PAIR(4));
 	move (FIELD_START_Y +3, FIELD_START_X +7);

	if (refresh () != OK)
	{
	  unpost_form (form);
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	}

	while ((option = getch ()) != ENTER)
	  switch (option)
	  {
	    case (ESCAPE):
              unpost_form (form);
              freeFormResources (form, formFields);
	      endwin ();
	      return (OK);
	    break;
	    case (KEY_DOWN):
              if (form_driver (form, REQ_NEXT_FIELD) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
              if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_UP):
              if (form_driver (form, REQ_PREV_FIELD) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
              if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_LEFT):
              if (form_driver (form, REQ_PREV_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_RIGHT):
              if (form_driver (form, REQ_NEXT_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (BACKSPACE):
              if (form_driver (form, REQ_DEL_PREV) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (DEL):
              if (form_driver (form, REQ_DEL_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    default:
              if (form_driver (form, option) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
	  }
        if (form_driver (form, REQ_NEXT_FIELD) == E_SYSTEM_ERROR)
        {
          unpost_form (form);
          freeFormResources (form, formFields);
	  endwin ();
          return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
        }
        if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
        {
          unpost_form (form);
          freeFormResources (form, formFields);
	  endwin ();
          return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
        }
	
        if ((errorCode = repairFormData (&userData, formFields, 'i')) != OK)
	{
	  if ((errorCode == REPAIR_FORM_DATA__NO_USER_DATA) || (errorCode == REPAIR_FORM_DATA__NO_FORM_FIELDS) || (errorCode == REPAIR_FORM_DATA__UNKNOWN_OPTION))
	  {
	    unpost_form (form);
	    freeFormResources (form, formFields);
	    endwin ();
	    return (errorCode);
	  }
	  else
	    mvprintw (LINES -6, FIELD_START_X, "%s", showTextErrorMessage (errorCode));
	}
	else
	{
          if ((errorCode = checkField (userData.name, NAME_VALID_CHARACTERS, MIN_LENGTH_NAME,
                               MAX_LENGTH_NAME)) != OK)
            switch (errorCode)
            {
              case (CHECK_FIELD__FIELD_HAS_NOT_VALID_CHARACTERS):
                mvprintw (LINES -6, FIELD_START_X, "%s", showTextErrorMessage (CHECK_USER_DATA__NAME_HAS_NOT_VALID_CHARACTERS));
              break;
              case (CHECK_FIELD__BIG_FIELD):
                mvprintw (LINES -6, FIELD_START_X, "%s", showTextErrorMessage (CHECK_USER_DATA__BIG_NAME));
              break;
              case (CHECK_FIELD__SMALL_FIELD):
                mvprintw (LINES -6, FIELD_START_X, "%s", showTextErrorMessage (CHECK_USER_DATA__SMALL_NAME));
              break;
              default:
                mvprintw (LINES -6, FIELD_START_X, "%s", showTextErrorMessage (errorCode));
            } 
	  else if ((errorCode = checkField (userData.email, EMAIL_VALID_CHARACTERS, MIN_LENGTH_EMAIL,
         			 MAX_LENGTH_EMAIL)) != OK)
            switch (errorCode)
            {
              case (CHECK_FIELD__FIELD_HAS_NOT_VALID_CHARACTERS):
                mvprintw (LINES -6, FIELD_START_X, "%s", showTextErrorMessage (CHECK_USER_DATA__EMAIL_HAS_NOT_VALID_CHARACTERS));printf ("email: %s", userData.email);
              break;
              case (CHECK_FIELD__BIG_FIELD):
                mvprintw (LINES -6, FIELD_START_X, "%s", showTextErrorMessage (CHECK_USER_DATA__BIG_EMAIL));
              break;
              case (CHECK_FIELD__SMALL_FIELD):
                mvprintw (LINES -6, FIELD_START_X, "%s", showTextErrorMessage (CHECK_USER_DATA__SMALL_EMAIL));
              break;
              default:
                mvprintw (LINES -6, FIELD_START_X, "%s", showTextErrorMessage (errorCode));
            }
          else
	  {
	    errorCode = inviteUser (userData.userId, userData.name, userData.email);
	    mvprintw (LINES -6, FIELD_START_X, "%s", showTextErrorMessage (errorCode));
          }
        }
	mvprintw (LINES -4, FIELD_START_X, "%s", showTextHelpMessage (NCURSES__PRESS_ANY_KEY_TO_CONTINUE));
	getch ();
	if (refresh () != OK)
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	  
	if (unpost_form (form) != OK)
	{
	  endwin ();
          return (NCURSES__ERROR_UNPOSTING_FORM);
	}
        if ((errorCode = freeFormResources (form, formFields)) != OK)
	{
	    endwin ();
            return (errorCode);
	}
      break;

      case (NCURSES__INVITE_FRIEND_OPTION):
 	if ((formFields = createFormFields ('I')) == NULL)
	{
	  endwin ();
          return (NCURSES__ERROR_CREATING_FORM_FIELDS);
        }

	if ((form = new_form (formFields)) == NULL)
	{
	  freeFormFieldsResources (formFields);
	  endwin ();
	  return (NCURSES__ERROR_CREATING_FORM);
	}

	if (post_form (form) != OK)
	{
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_POSTING_FORM);
	}
	
	if (refresh () != OK)
	{
	  unpost_form (form);
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	}
	set_current_field (form, formFields[0]);
	showDescriptionsOfFields ('I');;
        wattron (stdscr, COLOR_PAIR(4));
	mvprintw (LINES -4, 2, "%s", showTextHelpMessage (NCURSES__BACKSPACE_TO_CLEAR));
	mvprintw (LINES -3, 2, "%s", showTextHelpMessage (NCURSES__ENTER_TO_SUBMIT));
        mvprintw (LINES -2, 2, "%s", showTextHelpMessage (NCURSES__ESC_TO_EXIT));
        wattroff (stdscr, COLOR_PAIR(4));
 	move (FIELD_START_Y +7, FIELD_START_X +20);

	if (refresh () != OK)
	{
	  unpost_form (form);
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	}

	while ((option = getch ()) != ENTER)
	  switch (option)
	  {
	    case (ESCAPE):
              unpost_form (form);
              freeFormResources (form, formFields);
	      endwin ();
	      return (OK);
	    break;
	    case (KEY_DOWN):
              if (form_driver (form, REQ_NEXT_FIELD) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
              if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_UP):
              if (form_driver (form, REQ_PREV_FIELD) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
              if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_LEFT):
              if (form_driver (form, REQ_PREV_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_RIGHT):
              if (form_driver (form, REQ_NEXT_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (BACKSPACE):
              if (form_driver (form, REQ_DEL_PREV) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (DEL):
              if (form_driver (form, REQ_DEL_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    default:
              if (form_driver (form, option) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
	  }
        if (form_driver (form, REQ_NEXT_FIELD) == E_SYSTEM_ERROR)
        {
          unpost_form (form);
          freeFormResources (form, formFields);
	  endwin ();
          return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
        }
        if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
        {
          unpost_form (form);
          freeFormResources (form, formFields);
	  endwin ();
          return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
        }
	stringCopy (idField1, repairString (field_buffer (formFields[0], 0)), 20);
	stringCopy (idField2, repairString (field_buffer (formFields[1], 0)), 20);
	if ((errorCode = checkField (idField1, "0123456789", 1, 20)) != OK)
	  mvprintw (LINES -12, FIELD_START_X+2, "%s", showTextErrorMessage (errorCode));
	else if
	  ((errorCode = checkField (idField2, "0123456789", 1, 20)) != OK)
	    mvprintw (LINES -12, FIELD_START_X+2, "%s", showTextErrorMessage (errorCode));
	else
	{
	  errorCode = inviteFriend (strtoul (idField1, NULL, 10), strtoul (idField2, NULL, 10));
	  mvprintw (LINES -12, FIELD_START_X+2, "%s", showTextErrorMessage (errorCode));
	}
      
	mvprintw (LINES -10, FIELD_START_X +2, "%s", showTextHelpMessage (NCURSES__PRESS_ANY_KEY_TO_CONTINUE));
	getch ();
	if (refresh () != OK)
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	  
	if (unpost_form (form) != OK)
	{
	  endwin ();
          return (NCURSES__ERROR_UNPOSTING_FORM);
	}
        if ((errorCode = freeFormResources (form, formFields)) != OK)
	{
	    endwin ();
            return (errorCode);
	}
      break;

      case (NCURSES__FRIENDSHIP_OPTION):
        formFields = (FIELD **) calloc (1 +1, sizeof (FIELD *));
        if ((formFields[0] = new_field (FIELD_HEIGHT, 20, FIELD_START_Y +6, FIELD_START_X, 0, 0)) == NULL)
        {
          free (formFields);
          return (NCURSES__ERROR_CREATING_FORM_FIELDS);
        }
	formFields[1] = NULL;
        set_field_back (formFields[0], A_UNDERLINE);
        set_field_fore (formFields[0], COLOR_PAIR(3));
        set_field_pad  (formFields[0], '_');
        field_opts_off (formFields[0], O_AUTOSKIP);
	if ((form = new_form (formFields)) == NULL)
	{
	  freeFormFieldsResources (formFields);
	  endwin ();
	  return (NCURSES__ERROR_CREATING_FORM);
	}      
	if (post_form (form) != OK)
	{
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_POSTING_FORM);
	}	
	if (refresh () != OK)
	{
	  unpost_form (form);
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	}
	set_current_field (form, formFields[0]);
        printInMiddle (stdscr, 5, 0, COLS, showTextHelpMessage (NCURSES__INFORM_USER_ID), COLOR_PAIR(4));
        wattron (stdscr, COLOR_PAIR(2));
        mvprintw (FIELD_START_Y +6, 15, "%s", showTextHelpMessage (USER_ID_FIELD_DESCRIPTION));	
        wattroff (stdscr, COLOR_PAIR(2));
        wattron (stdscr, COLOR_PAIR(4));	
	mvprintw (LINES -6, 4, "%s", showTextHelpMessage (NCURSES__BACKSPACE_TO_CLEAR));
	mvprintw (LINES -5, 4, "%s", showTextHelpMessage (NCURSES__ENTER_TO_SUBMIT));
        mvprintw (LINES -4, 4, "%s", showTextHelpMessage (NCURSES__ESC_TO_EXIT));
        wattroff (stdscr, COLOR_PAIR(4));
	move (FIELD_START_Y +6, FIELD_START_X);	
	if (refresh () != OK)
	{
	  unpost_form (form);
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	}	
	while ((option = getch ()) != ENTER)
	  switch (option)
	  {
	    case (ESCAPE):
              unpost_form (form);
              freeFormResources (form, formFields);
	      endwin ();
	      return (OK);
	    break;
	    case (KEY_LEFT):
              if (form_driver (form, REQ_PREV_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_RIGHT):
              if (form_driver (form, REQ_NEXT_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (BACKSPACE):
              if (form_driver (form, REQ_DEL_PREV) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (DEL):
              if (form_driver (form, REQ_DEL_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    default:
              if (form_driver (form, option) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
	  }
        if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
        {
          unpost_form (form);
          freeFormResources (form, formFields);
	  endwin ();
          return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
        }	
	stringCopy (temp, repairString (field_buffer (formFields[0], 0)), 20);
	if ((errorCode = checkField (temp, "0123456789", 1, 20)) != OK)
	  mvprintw (LINES -12, FIELD_START_X+2, "%s", showTextErrorMessage (errorCode));
	else
	{  
	  if ((errorCode = getFriendshipInvitation (strtoul (temp, NULL, 10), &first)) != OK)
	    mvprintw (LINES -12, FIELD_START_X+2, "%s", showTextErrorMessage (errorCode));
	  else
	  {
	    clear ();
	    if (refresh () != OK)
	      return (NCURSES__ERROR_REFRESHING_TERMINAL);
	    printInMiddle (stdscr, 3, 0, COLS, showTextHelpMessage (LIST_OF_USERS_FOUND), COLOR_PAIR(4));
            wattron (stdscr, COLOR_PAIR(4));
	    mvprintw (LINES -4, 2, "%s", showTextHelpMessage (NCURSES__BACKSPACE_TO_CLEAR));
	    mvprintw (LINES -3, 2, "%s", showTextHelpMessage (NCURSES__ENTER_TO_SUBMIT));
            mvprintw (LINES -2, 2, "%s", showTextHelpMessage (NCURSES__ESC_TO_EXIT));
            wattroff (stdscr, COLOR_PAIR(4));
            wattron (stdscr, COLOR_PAIR(2));	  
            for (count = 0; (errorCode = retrieveFIFO (&first, &last, &buffer)) == OK; count++)
            {
              #ifdef ENGLISH 
                mvprintw (FIELD_START_Y +4 + count, FIELD_START_X -6, "User: %s  -->  Id: %llu", buffer.name , buffer.userId );
	      #elif PORTUGUESE
                mvprintw (FIELD_START_Y +4 + count, FIELD_START_X -6, "Usu�rio: %s  -->  Id: %llu", buffer.name , buffer.userId );
	      #endif
            }
            wattroff (stdscr, COLOR_PAIR(2));	
            freeFIFOResources (&first, &last);  
	    mvprintw (LINES -12, FIELD_START_X +2, "%s", showTextErrorMessage (OK));
	  }
	}
	  
        mvprintw (LINES -10, FIELD_START_X+2, "%s", showTextHelpMessage (NCURSES__PRESS_ANY_KEY_TO_CONTINUE));
	getch ();
	if (refresh () != OK)
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	if (unpost_form (form) != OK)
	{
	  endwin ();
          return (NCURSES__ERROR_UNPOSTING_FORM);
	}
        if ((errorCode = freeFormResources (form, formFields)) != OK)
	{
	  endwin ();
          return (errorCode);
	}
      break;

      case (NCURSES__ACCEPT_OPTION):
 	if ((formFields = createFormFields ('P')) == NULL)
	{
	  endwin ();
          return (NCURSES__ERROR_CREATING_FORM_FIELDS);
        }

	if ((form = new_form (formFields)) == NULL)
	{
	  freeFormFieldsResources (formFields);
	  endwin ();
	  return (NCURSES__ERROR_CREATING_FORM);
	}

	if (post_form (form) != OK)
	{
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_POSTING_FORM);
	}
	
	if (refresh () != OK)
	{
	  unpost_form (form);
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	}
	set_current_field (form, formFields[0]);
	showDescriptionsOfFields ('P');;
        wattron (stdscr, COLOR_PAIR(4));
	mvprintw (LINES -4, 2, "%s", showTextHelpMessage (NCURSES__BACKSPACE_TO_CLEAR));
	mvprintw (LINES -3, 2, "%s", showTextHelpMessage (NCURSES__ENTER_TO_SUBMIT));
        mvprintw (LINES -2, 2, "%s", showTextHelpMessage (NCURSES__ESC_TO_EXIT));
        wattroff (stdscr, COLOR_PAIR(4));
 	move (FIELD_START_Y +7, FIELD_START_X +28);

	if (refresh () != OK)
	{
	  unpost_form (form);
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	}

	while ((option = getch ()) != ENTER)
	  switch (option)
	  {
	    case (ESCAPE):
              unpost_form (form);
              freeFormResources (form, formFields);
	      endwin ();
	      return (OK);
	    break;
	    case (KEY_DOWN):
              if (form_driver (form, REQ_NEXT_FIELD) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
              if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_UP):
              if (form_driver (form, REQ_PREV_FIELD) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
              if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_LEFT):
              if (form_driver (form, REQ_PREV_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_RIGHT):
              if (form_driver (form, REQ_NEXT_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (BACKSPACE):
              if (form_driver (form, REQ_DEL_PREV) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (DEL):
              if (form_driver (form, REQ_DEL_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    default:
              if (form_driver (form, option) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
	  }
        if (form_driver (form, REQ_NEXT_FIELD) == E_SYSTEM_ERROR)
        {
          unpost_form (form);
          freeFormResources (form, formFields);
	  endwin ();
          return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
        }
        if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
        {
          unpost_form (form);
          freeFormResources (form, formFields);
	  endwin ();
          return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
        }
	stringCopy (idField1, repairString (field_buffer (formFields[0], 0)), 20);
	stringCopy (idField2, repairString (field_buffer (formFields[1], 0)), 20);
	if ((errorCode = checkField (idField1, "0123456789", 1, 20)) != OK)
	  mvprintw (LINES -12, FIELD_START_X+2, "%s", showTextErrorMessage (errorCode));
	else if
	  ((errorCode = checkField (idField2, "0123456789", 1, 20)) != OK)
	    mvprintw (LINES -12, FIELD_START_X+2, "%s", showTextErrorMessage (errorCode));
	else
	{
	  errorCode = acceptFriendshipInvitation (strtoul (idField1, NULL, 10), strtoul (idField2, NULL, 10));
	  mvprintw (LINES -12, FIELD_START_X+2, "%s", showTextErrorMessage (errorCode));
	}
      
	mvprintw (LINES -10, FIELD_START_X +2, "%s", showTextHelpMessage (NCURSES__PRESS_ANY_KEY_TO_CONTINUE));
	getch ();
	if (refresh () != OK)
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	  
	if (unpost_form (form) != OK)
	{
	  endwin ();
          return (NCURSES__ERROR_UNPOSTING_FORM);
	}
        if ((errorCode = freeFormResources (form, formFields)) != OK)
	{
	    endwin ();
            return (errorCode);
	}
      break;

      case (NCURSES__REJECT_OPTION):
 	if ((formFields = createFormFields ('J')) == NULL)
	{
	  endwin ();
          return (NCURSES__ERROR_CREATING_FORM_FIELDS);
        }

	if ((form = new_form (formFields)) == NULL)
	{
	  freeFormFieldsResources (formFields);
	  endwin ();
	  return (NCURSES__ERROR_CREATING_FORM);
	}

	if (post_form (form) != OK)
	{
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_POSTING_FORM);
	}
	
	if (refresh () != OK)
	{
	  unpost_form (form);
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	}
	set_current_field (form, formFields[0]);
	showDescriptionsOfFields ('J');;
        wattron (stdscr, COLOR_PAIR(4));
	mvprintw (LINES -4, 2, "%s", showTextHelpMessage (NCURSES__BACKSPACE_TO_CLEAR));
	mvprintw (LINES -3, 2, "%s", showTextHelpMessage (NCURSES__ENTER_TO_SUBMIT));
        mvprintw (LINES -2, 2, "%s", showTextHelpMessage (NCURSES__ESC_TO_EXIT));
        wattroff (stdscr, COLOR_PAIR(4));
 	move (FIELD_START_Y +7, FIELD_START_X +28);

	if (refresh () != OK)
	{
	  unpost_form (form);
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	}

	while ((option = getch ()) != ENTER)
	  switch (option)
	  {
	    case (ESCAPE):
              unpost_form (form);
              freeFormResources (form, formFields);
	      endwin ();
	      return (OK);
	    break;
	    case (KEY_DOWN):
              if (form_driver (form, REQ_NEXT_FIELD) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
              if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_UP):
              if (form_driver (form, REQ_PREV_FIELD) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
              if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_LEFT):
              if (form_driver (form, REQ_PREV_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_RIGHT):
              if (form_driver (form, REQ_NEXT_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (BACKSPACE):
              if (form_driver (form, REQ_DEL_PREV) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (DEL):
              if (form_driver (form, REQ_DEL_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    default:
              if (form_driver (form, option) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
	  }
        if (form_driver (form, REQ_NEXT_FIELD) == E_SYSTEM_ERROR)
        {
          unpost_form (form);
          freeFormResources (form, formFields);
	  endwin ();
          return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
        }
        if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
        {
          unpost_form (form);
          freeFormResources (form, formFields);
	  endwin ();
          return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
        }
	stringCopy (idField1, repairString (field_buffer (formFields[0], 0)), 20);
	stringCopy (idField2, repairString (field_buffer (formFields[1], 0)), 20);
	if ((errorCode = checkField (idField1, "0123456789", 1, 20)) != OK)
	  mvprintw (LINES -12, FIELD_START_X+2, "%s", showTextErrorMessage (errorCode));
	else if
	  ((errorCode = checkField (idField2, "0123456789", 1, 20)) != OK)
	    mvprintw (LINES -12, FIELD_START_X+2, "%s", showTextErrorMessage (errorCode));
	else
	{
	  errorCode = rejectFriendshipInvitation (strtoul (idField1, NULL, 10), strtoul (idField2, NULL, 10));
	  mvprintw (LINES -12, FIELD_START_X+2, "%s", showTextErrorMessage (errorCode));
	}
      
	mvprintw (LINES -10, FIELD_START_X +2, "%s", showTextHelpMessage (NCURSES__PRESS_ANY_KEY_TO_CONTINUE));
	getch ();
	if (refresh () != OK)
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	  
	if (unpost_form (form) != OK)
	{
	  endwin ();
          return (NCURSES__ERROR_UNPOSTING_FORM);
	}
        if ((errorCode = freeFormResources (form, formFields)) != OK)
	{
	    endwin ();
            return (errorCode);
	}
      break;

      case (NCURSES__EXCLUDE_OPTION):
 	if ((formFields = createFormFields ('X')) == NULL)
	{
	  endwin ();
          return (NCURSES__ERROR_CREATING_FORM_FIELDS);
        }

	if ((form = new_form (formFields)) == NULL)
	{
	  freeFormFieldsResources (formFields);
	  endwin ();
	  return (NCURSES__ERROR_CREATING_FORM);
	}

	if (post_form (form) != OK)
	{
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_POSTING_FORM);
	}
	
	if (refresh () != OK)
	{
	  unpost_form (form);
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	}
	set_current_field (form, formFields[0]);
	showDescriptionsOfFields ('X');;
        wattron (stdscr, COLOR_PAIR(4));
	mvprintw (LINES -4, 2, "%s", showTextHelpMessage (NCURSES__BACKSPACE_TO_CLEAR));
	mvprintw (LINES -3, 2, "%s", showTextHelpMessage (NCURSES__ENTER_TO_SUBMIT));
        mvprintw (LINES -2, 2, "%s", showTextHelpMessage (NCURSES__ESC_TO_EXIT));
        wattroff (stdscr, COLOR_PAIR(4));
 	move (FIELD_START_Y +7, FIELD_START_X +28);

	if (refresh () != OK)
	{
	  unpost_form (form);
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	}

	while ((option = getch ()) != ENTER)
	  switch (option)
	  {
	    case (ESCAPE):
              unpost_form (form);
              freeFormResources (form, formFields);
	      endwin ();
	      return (OK);
	    break;
	    case (KEY_DOWN):
              if (form_driver (form, REQ_NEXT_FIELD) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
              if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_UP):
              if (form_driver (form, REQ_PREV_FIELD) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
              if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_LEFT):
              if (form_driver (form, REQ_PREV_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_RIGHT):
              if (form_driver (form, REQ_NEXT_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (BACKSPACE):
              if (form_driver (form, REQ_DEL_PREV) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (DEL):
              if (form_driver (form, REQ_DEL_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    default:
              if (form_driver (form, option) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
	  }
        if (form_driver (form, REQ_NEXT_FIELD) == E_SYSTEM_ERROR)
        {
          unpost_form (form);
          freeFormResources (form, formFields);
	  endwin ();
          return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
        }
        if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
        {
          unpost_form (form);
          freeFormResources (form, formFields);
	  endwin ();
          return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
        }
	stringCopy (idField1, repairString (field_buffer (formFields[0], 0)), 20);
	stringCopy (idField2, repairString (field_buffer (formFields[1], 0)), 20);
	if ((errorCode = checkField (idField1, "0123456789", 1, 20)) != OK)
	  mvprintw (LINES -12, FIELD_START_X+2, "%s", showTextErrorMessage (errorCode));
	else if
	  ((errorCode = checkField (idField2, "0123456789", 1, 20)) != OK)
	    mvprintw (LINES -12, FIELD_START_X+2, "%s", showTextErrorMessage (errorCode));
	else
	{
	  errorCode = excludeFriend (strtoul (idField1, NULL, 10), strtoul (idField2, NULL, 10));
	  mvprintw (LINES -12, FIELD_START_X+2, "%s", showTextErrorMessage (errorCode));
	}
      
	mvprintw (LINES -10, FIELD_START_X +2, "%s", showTextHelpMessage (NCURSES__PRESS_ANY_KEY_TO_CONTINUE));
	getch ();
	if (refresh () != OK)
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	  
	if (unpost_form (form) != OK)
	{
	  endwin ();
          return (NCURSES__ERROR_UNPOSTING_FORM);
	}
        if ((errorCode = freeFormResources (form, formFields)) != OK)
	{
	    endwin ();
            return (errorCode);
	}
      break;

      case (NCURSES__GET_FRIENDS_OPTION):
        formFields = (FIELD **) calloc (1 +1, sizeof (FIELD *));
        if ((formFields[0] = new_field (FIELD_HEIGHT, 20, FIELD_START_Y +6, FIELD_START_X, 0, 0)) == NULL)
        {
          free (formFields);
          return (NCURSES__ERROR_CREATING_FORM_FIELDS);
        }
	formFields[1] = NULL;
        set_field_back (formFields[0], A_UNDERLINE);
        set_field_fore (formFields[0], COLOR_PAIR(3));
        set_field_pad  (formFields[0], '_');
        field_opts_off (formFields[0], O_AUTOSKIP);
	if ((form = new_form (formFields)) == NULL)
	{
	  freeFormFieldsResources (formFields);
	  endwin ();
	  return (NCURSES__ERROR_CREATING_FORM);
	}      
	if (post_form (form) != OK)
	{
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_POSTING_FORM);
	}	
	if (refresh () != OK)
	{
	  unpost_form (form);
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	}
	set_current_field (form, formFields[0]);
        printInMiddle (stdscr, 5, 0, COLS, showTextHelpMessage (NCURSES__INFORM_USER_ID), COLOR_PAIR(4));
        wattron (stdscr, COLOR_PAIR(2));
        mvprintw (FIELD_START_Y +6, 15, "%s", showTextHelpMessage (USER_ID_FIELD_DESCRIPTION));	
        wattroff (stdscr, COLOR_PAIR(2));
        wattron (stdscr, COLOR_PAIR(4));	
	mvprintw (LINES -6, 4, "%s", showTextHelpMessage (NCURSES__BACKSPACE_TO_CLEAR));
	mvprintw (LINES -5, 4, "%s", showTextHelpMessage (NCURSES__ENTER_TO_SUBMIT));
        mvprintw (LINES -4, 4, "%s", showTextHelpMessage (NCURSES__ESC_TO_EXIT));
        wattroff (stdscr, COLOR_PAIR(4));
	move (FIELD_START_Y +6, FIELD_START_X);	
	if (refresh () != OK)
	{
	  unpost_form (form);
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	}	
	while ((option = getch ()) != ENTER)
	  switch (option)
	  {
	    case (ESCAPE):
              unpost_form (form);
              freeFormResources (form, formFields);
	      endwin ();
	      return (OK);
	    break;
	    case (KEY_LEFT):
              if (form_driver (form, REQ_PREV_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_RIGHT):
              if (form_driver (form, REQ_NEXT_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (BACKSPACE):
              if (form_driver (form, REQ_DEL_PREV) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (DEL):
              if (form_driver (form, REQ_DEL_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    default:
              if (form_driver (form, option) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
	  }
        if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
        {
          unpost_form (form);
          freeFormResources (form, formFields);
	  endwin ();
          return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
        }	
	stringCopy (temp, repairString (field_buffer (formFields[0], 0)), 20);
	if ((errorCode = checkField (temp, "0123456789", 1, 20)) != OK)
	  mvprintw (LINES -12, FIELD_START_X+2, "%s", showTextErrorMessage (errorCode));
	else
	{  
	  if ((errorCode = getFriends (strtoul (temp, NULL, 10), &first)) != OK)
	    mvprintw (LINES -12, FIELD_START_X+2, "%s", showTextErrorMessage (errorCode));
	  else
	  {
	    clear ();
	    if (refresh () != OK)
	      return (NCURSES__ERROR_REFRESHING_TERMINAL);
	    printInMiddle (stdscr, 3, 0, COLS, showTextHelpMessage (LIST_OF_FRIENDS_FOUND), COLOR_PAIR(4));
            wattron (stdscr, COLOR_PAIR(4));
	    mvprintw (LINES -4, 2, "%s", showTextHelpMessage (NCURSES__BACKSPACE_TO_CLEAR));
	    mvprintw (LINES -3, 2, "%s", showTextHelpMessage (NCURSES__ENTER_TO_SUBMIT));
            mvprintw (LINES -2, 2, "%s", showTextHelpMessage (NCURSES__ESC_TO_EXIT));
            wattroff (stdscr, COLOR_PAIR(4));
            wattron (stdscr, COLOR_PAIR(2));	  
            for (count = 0; retrieveFIFO (&first, &last, &buffer) == OK; count++)
            {
              #ifdef ENGLISH 
                mvprintw (FIELD_START_Y +4 + count, FIELD_START_X -6, "User: %s  -->  Id: %llu", buffer.name , buffer.userId );
	      #elif PORTUGUESE
                mvprintw (FIELD_START_Y +4 + count, FIELD_START_X -6, "Usu�rio: %s  -->  Id: %llu", buffer.name , buffer.userId );
	      #endif
            }
            wattroff (stdscr, COLOR_PAIR(2));	
            freeFIFOResources (&first, &last);  
	    mvprintw (LINES -12, FIELD_START_X +2, "%s", showTextErrorMessage (OK));
	  }
	}
	  
        mvprintw (LINES -10, FIELD_START_X+2, "%s", showTextHelpMessage (NCURSES__PRESS_ANY_KEY_TO_CONTINUE));
	getch ();
	if (refresh () != OK)
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	if (unpost_form (form) != OK)
	{
	  endwin ();
          return (NCURSES__ERROR_UNPOSTING_FORM);
	}
        if ((errorCode = freeFormResources (form, formFields)) != OK)
	{
	  endwin ();
          return (errorCode);
	}
      break;

      case (NCURSES__CHANGE_CATEGORY_OPTION):
        if ((formFields = createFormFields ('c')) == NULL)
	{
	  endwin ();
          return (NCURSES__ERROR_CREATING_FORM_FIELDS);
        }

	if ((form = new_form (formFields)) == NULL)
	{
	  freeFormFieldsResources (formFields);
	  endwin ();
	  return (NCURSES__ERROR_CREATING_FORM);
	}

	if (post_form (form) != OK)
	{
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_POSTING_FORM);
	}
	
	if (refresh () != OK)
	{
	  unpost_form (form);
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	}
	set_current_field (form, formFields[0]);
	showDescriptionsOfFields ('c');;
        wattron (stdscr, COLOR_PAIR(4));	
	mvprintw (LINES -6, 4, "%s", showTextHelpMessage (NCURSES__BACKSPACE_TO_CLEAR));
	mvprintw (LINES -5, 4, "%s", showTextHelpMessage (NCURSES__ENTER_TO_SUBMIT));
        mvprintw (LINES -4, 4, "%s", showTextHelpMessage (NCURSES__ESC_TO_EXIT));
        wattroff (stdscr, COLOR_PAIR(4));
	move (FIELD_START_Y +6, FIELD_START_X);	
	if ((errorCode = setInitialValuesOfFields (form, &userData,'c')) != OK)
        {
	  unpost_form (form);
	  freeFormResources (form, formFields);
	  endwin ();
	  return (errorCode);
	}

	if (refresh () != OK)
	{
	  unpost_form (form);
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	}

	while ((option = getch ()) != ENTER)
	  switch (option)
	  {
	    case (ESCAPE):
              unpost_form (form);
              freeFormResources (form, formFields);
	      endwin ();
	      return (OK);
	    break;
	    case (KEY_LEFT):
              if (form_driver (form, REQ_PREV_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_RIGHT):
              if (form_driver (form, REQ_NEXT_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (BACKSPACE):
              if (form_driver (form, REQ_DEL_PREV) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (DEL):
              if (form_driver (form, REQ_DEL_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    default:
              if (form_driver (form, option) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
	  }
        if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
        {
          unpost_form (form);
          freeFormResources (form, formFields);
	  endwin ();
          return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
        }
	
        if ((errorCode = repairFormData (&userData, formFields, 'c')) != OK)
	{
	  if ((errorCode == REPAIR_FORM_DATA__NO_USER_DATA) || (errorCode == REPAIR_FORM_DATA__NO_FORM_FIELDS) || (errorCode == REPAIR_FORM_DATA__UNKNOWN_OPTION))
	  {
	    unpost_form (form);
	    freeFormResources (form, formFields);
	    endwin ();
	    return (errorCode);
	  }
	  else
	    mvprintw (LINES -12, FIELD_START_X +2, "%s", showTextErrorMessage (errorCode));
	}
	else
	{
	  if (userData.category == webUser)
	    userData.category = relative;
	  else
	  {
	     userData.category = webUser;
	     
	     clear ();
	     if (refresh () != OK)
	     {
	       endwin ();
	       return (NCURSES__ERROR_REFRESHING_TERMINAL);
	     }
             tempFormFields = (FIELD **) calloc (3 +1, sizeof (FIELD *));
             if ((tempFormFields[0] = new_field (FIELD_HEIGHT, MAX_LENGTH_USERNAME, FIELD_START_Y +6, FIELD_START_X +8, 0, 0)) == NULL)
             {
               free (tempFormFields);
               return (NCURSES__ERROR_CREATING_FORM_FIELDS);
             }
             if ((tempFormFields[1] = new_field (FIELD_HEIGHT, MAX_LENGTH_PLAIN_PASS, FIELD_START_Y +7, FIELD_START_X +8, 0, 0)) == NULL)
             {
               free (tempFormFields);
               return (NCURSES__ERROR_CREATING_FORM_FIELDS);
             }
             if ((tempFormFields[2] = new_field (FIELD_HEIGHT, MAX_FIELD_WIDTH, FIELD_START_Y +8, FIELD_START_X +8, 0, 0)) == NULL)
             {
               free (tempFormFields);
               return (NCURSES__ERROR_CREATING_FORM_FIELDS);
             }
	     tempFormFields[3] = NULL;
	     for (index = 0; index < 3; index++)
	     {
               set_field_back (tempFormFields[index], A_UNDERLINE);
               set_field_fore (tempFormFields[index], COLOR_PAIR(3));
               set_field_pad  (tempFormFields[index], '_');
               field_opts_off (tempFormFields[index], O_AUTOSKIP);
	     }
             field_opts_off (tempFormFields[1], O_PUBLIC);
	     if ((tempForm = new_form (tempFormFields)) == NULL)
	     {
	       freeFormFieldsResources (tempFormFields);
	       endwin ();
	       return (NCURSES__ERROR_CREATING_FORM);
	     }      
	     if (post_form (tempForm) != OK)
	     {
	       freeFormResources (tempForm, tempFormFields);
	       endwin ();
	       return (NCURSES__ERROR_POSTING_FORM);
	     }	
	     if (refresh () != OK)
	     {
	       unpost_form (tempForm);
	       freeFormResources (tempForm, tempFormFields);
	       endwin ();
	       return (NCURSES__ERROR_REFRESHING_TERMINAL);
	     }
	     set_current_field (tempForm, tempFormFields[0]);
             printInMiddle (stdscr, 5, 0, COLS, showTextHelpMessage (NCURSES__INFORM_NEW_DATA), COLOR_PAIR(4));
             wattron  (stdscr, COLOR_PAIR(2));
             mvprintw (FIELD_START_Y +6, 11, "%s", showTextHelpMessage (USERNAME_FIELD_DESCRIPTION));
             mvprintw (FIELD_START_Y +7, 11, "%s", showTextHelpMessage (REQUIRE_NEW_WEB_USER_PASSWORD));
             mvprintw (FIELD_START_Y +8, 11, "%s", showTextHelpMessage (EMAIL_FIELD_DESCRIPTION));	
             wattroff (stdscr, COLOR_PAIR(2));
             wattron  (stdscr, COLOR_PAIR(4));	
	     mvprintw (LINES -6, 4, "%s", showTextHelpMessage (NCURSES__BACKSPACE_TO_CLEAR));
	     mvprintw (LINES -5, 4, "%s", showTextHelpMessage (NCURSES__ENTER_TO_SUBMIT));
             mvprintw (LINES -4, 4, "%s", showTextHelpMessage (NCURSES__ESC_TO_EXIT));
             wattroff (stdscr, COLOR_PAIR(4));
	     move (FIELD_START_Y +6, FIELD_START_X +8);	
	     if (refresh () != OK)
	     {
	       unpost_form (tempForm);
	       freeFormResources (tempForm, tempFormFields);
	       endwin ();
	       return (NCURSES__ERROR_REFRESHING_TERMINAL);
	     }	
	     while ((option = getch ()) != ENTER)
	       switch (option)
	       {
	         case (ESCAPE):
                   unpost_form (tempForm);
                   freeFormResources (tempForm, tempFormFields);
	           endwin ();
	           return (OK);
	        break;
	        case (KEY_DOWN):
                  if (form_driver (tempForm, REQ_NEXT_FIELD) == E_SYSTEM_ERROR)
                  {
                    unpost_form (tempForm);
                    freeFormResources (tempForm, tempFormFields);
	   	    endwin ();
	            return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	          }
                  if (form_driver (tempForm, REQ_END_LINE) == E_SYSTEM_ERROR)
                  {
                    unpost_form (tempForm);
                    freeFormResources (tempForm, tempFormFields);
		    endwin ();
	            return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	          }
                break;
	        case (KEY_UP):
                  if (form_driver (tempForm, REQ_PREV_FIELD) == E_SYSTEM_ERROR)
                  {
                    unpost_form (tempForm);
                    freeFormResources (tempForm, tempFormFields);
		    endwin ();
	            return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	          }
                  if (form_driver (tempForm, REQ_END_LINE) == E_SYSTEM_ERROR)
                  {
                    unpost_form (tempForm);
                    freeFormResources (tempForm, tempFormFields);
		    endwin ();
	            return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	          }
                break;
	        case (KEY_LEFT):
                  if (form_driver (tempForm, REQ_PREV_CHAR) == E_SYSTEM_ERROR)
                  {
                    unpost_form (tempForm);
                    freeFormResources (tempForm, tempFormFields);
	   	    endwin ();
	            return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	          }
                break;
	        case (KEY_RIGHT):
                  if (form_driver (tempForm, REQ_NEXT_CHAR) == E_SYSTEM_ERROR)
                  {
                    unpost_form (tempForm);
                    freeFormResources (tempForm, tempFormFields);
		    endwin ();
	            return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	          }
                break;
	        case (BACKSPACE):
                  if (form_driver (tempForm, REQ_DEL_PREV) == E_SYSTEM_ERROR)
                  {
                    unpost_form (tempForm);
                    freeFormResources (tempForm, tempFormFields);
		    endwin ();
	            return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	          }
                break;
	        case (DEL):
                  if (form_driver (tempForm, REQ_DEL_CHAR) == E_SYSTEM_ERROR)
                  {
                    unpost_form (tempForm);
                    freeFormResources (tempForm, tempFormFields);
		    endwin ();
	            return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	          }
                break;
	        default:
                  if (form_driver (tempForm, option) == E_SYSTEM_ERROR)
                  {
                    unpost_form (tempForm);
                    freeFormResources (tempForm, tempFormFields);
		    endwin ();
	            return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	          }
	      }
            if (form_driver (tempForm, REQ_NEXT_FIELD) == E_SYSTEM_ERROR)
            {
              unpost_form (tempForm);
              freeFormResources (tempForm, tempFormFields);
	      endwin ();
              return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
            }
            if (form_driver (tempForm, REQ_END_LINE) == E_SYSTEM_ERROR)
            {
              unpost_form (tempForm);
              freeFormResources (tempForm, tempFormFields);
	      endwin ();
              return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
            }
	    stringCopy (userData.userName,  repairString (field_buffer (tempFormFields[0], 0)), MAX_LENGTH_USERNAME);
	    stringCopy (userData.plainPass, repairString (field_buffer (tempFormFields[1], 0)), MAX_LENGTH_PLAIN_PASS);
	    stringCopy (userData.email,     repairString (field_buffer (tempFormFields[2], 0)), MAX_LENGTH_EMAIL);
	  } /* else */

	  errorCode = changeUserCategory (&userData);
	  mvprintw (LINES -12, FIELD_START_X +2, "%s", showTextErrorMessage (errorCode));     
        }
	mvprintw (LINES -10, FIELD_START_X+2, "%s", showTextHelpMessage (NCURSES__PRESS_ANY_KEY_TO_CONTINUE));
	getch ();
	if (refresh () != OK)
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	  
	if (userData.category == webUser)
	{
	  if (unpost_form (tempForm) != OK)
	  {
	    endwin ();
            return (NCURSES__ERROR_UNPOSTING_FORM);
	  }
          if ((errorCode = freeFormResources (tempForm, tempFormFields)) != OK)
	  {
	    endwin ();
            return (errorCode);
	  }	
	}  
	
	if (unpost_form (form) != OK)
	{
	  endwin ();
          return (NCURSES__ERROR_UNPOSTING_FORM);
	}
        if ((errorCode = freeFormResources (form, formFields)) != OK)
	{
	  endwin ();
          return (errorCode);
	}
      break;

      case (NCURSES__ADD_PARENT_RELATIONSHIP_OPTION):
 	if ((formFields = createFormFields ('A')) == NULL)
	{
	  endwin ();
          return (NCURSES__ERROR_CREATING_FORM_FIELDS);
        }

	if ((form = new_form (formFields)) == NULL)
	{
	  freeFormFieldsResources (formFields);
	  endwin ();
	  return (NCURSES__ERROR_CREATING_FORM);
	}

	if (post_form (form) != OK)
	{
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_POSTING_FORM);
	}
	
	if (refresh () != OK)
	{
	  unpost_form (form);
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	}
	set_current_field (form, formFields[0]);
	showDescriptionsOfFields ('A');;
        wattron (stdscr, COLOR_PAIR(4));
	mvprintw (LINES -4, 2, "%s", showTextHelpMessage (NCURSES__BACKSPACE_TO_CLEAR));
	mvprintw (LINES -3, 2, "%s", showTextHelpMessage (NCURSES__ENTER_TO_SUBMIT));
        mvprintw (LINES -2, 2, "%s", showTextHelpMessage (NCURSES__ESC_TO_EXIT));
        wattroff (stdscr, COLOR_PAIR(4));
 	move (FIELD_START_Y +7, FIELD_START_X +20);

	if (refresh () != OK)
	{
	  unpost_form (form);
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	}

	while ((option = getch ()) != ENTER)
	  switch (option)
	  {
	    case (ESCAPE):
              unpost_form (form);
              freeFormResources (form, formFields);
	      endwin ();
	      return (OK);
	    break;
	    case (KEY_DOWN):
              if (form_driver (form, REQ_NEXT_FIELD) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
              if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_UP):
              if (form_driver (form, REQ_PREV_FIELD) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
              if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_LEFT):
              if (form_driver (form, REQ_PREV_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_RIGHT):
              if (form_driver (form, REQ_NEXT_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (BACKSPACE):
              if (form_driver (form, REQ_DEL_PREV) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (DEL):
              if (form_driver (form, REQ_DEL_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    default:
              if (form_driver (form, option) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
	  }
        if (form_driver (form, REQ_NEXT_FIELD) == E_SYSTEM_ERROR)
        {
          unpost_form (form);
          freeFormResources (form, formFields);
	  endwin ();
          return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
        }
        if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
        {
          unpost_form (form);
          freeFormResources (form, formFields);
	  endwin ();
          return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
        }
	stringCopy (idField1, repairString (field_buffer (formFields[0], 0)), 20);
	stringCopy (idField2, repairString (field_buffer (formFields[1], 0)), 20);
	if ((errorCode = checkField (idField1, "0123456789", 1, 20)) != OK)
	  mvprintw (LINES -12, FIELD_START_X+2, "%s", showTextErrorMessage (errorCode));
	else if
	  ((errorCode = checkField (idField2, "0123456789", 1, 20)) != OK)
	    mvprintw (LINES -12, FIELD_START_X+2, "%s", showTextErrorMessage (errorCode));
	else
	{
	  errorCode = addParentRelationship (strtoul (idField1, NULL, 10), strtoul (idField2, NULL, 10));
	  mvprintw (LINES -12, FIELD_START_X+2, "%s", showTextErrorMessage (errorCode));
	}
      
	mvprintw (LINES -10, FIELD_START_X +2, "%s", showTextHelpMessage (NCURSES__PRESS_ANY_KEY_TO_CONTINUE));
	getch ();
	if (refresh () != OK)
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	  
	if (unpost_form (form) != OK)
	{
	  endwin ();
          return (NCURSES__ERROR_UNPOSTING_FORM);
	}
        if ((errorCode = freeFormResources (form, formFields)) != OK)
	{
	    endwin ();
            return (errorCode);
	}
      break;

      case (NCURSES__REMOVE_PARENT_RELATIONSHIP_OPTION):
 	if ((formFields = createFormFields ('R')) == NULL)
	{
	  endwin ();
          return (NCURSES__ERROR_CREATING_FORM_FIELDS);
        }

	if ((form = new_form (formFields)) == NULL)
	{
	  freeFormFieldsResources (formFields);
	  endwin ();
	  return (NCURSES__ERROR_CREATING_FORM);
	}

	if (post_form (form) != OK)
	{
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_POSTING_FORM);
	}
	
	if (refresh () != OK)
	{
	  unpost_form (form);
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	}
	set_current_field (form, formFields[0]);
	showDescriptionsOfFields ('R');;
        wattron (stdscr, COLOR_PAIR(4));
	mvprintw (LINES -4, 2, "%s", showTextHelpMessage (NCURSES__BACKSPACE_TO_CLEAR));
	mvprintw (LINES -3, 2, "%s", showTextHelpMessage (NCURSES__ENTER_TO_SUBMIT));
        mvprintw (LINES -2, 2, "%s", showTextHelpMessage (NCURSES__ESC_TO_EXIT));
        wattroff (stdscr, COLOR_PAIR(4));
 	move (FIELD_START_Y +7, FIELD_START_X +20);

	if (refresh () != OK)
	{
	  unpost_form (form);
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	}

	while ((option = getch ()) != ENTER)
	  switch (option)
	  {
	    case (ESCAPE):
              unpost_form (form);
              freeFormResources (form, formFields);
	      endwin ();
	      return (OK);
	    break;
	    case (KEY_DOWN):
              if (form_driver (form, REQ_NEXT_FIELD) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
              if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_UP):
              if (form_driver (form, REQ_PREV_FIELD) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
              if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_LEFT):
              if (form_driver (form, REQ_PREV_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_RIGHT):
              if (form_driver (form, REQ_NEXT_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (BACKSPACE):
              if (form_driver (form, REQ_DEL_PREV) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (DEL):
              if (form_driver (form, REQ_DEL_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    default:
              if (form_driver (form, option) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
	  }
        if (form_driver (form, REQ_NEXT_FIELD) == E_SYSTEM_ERROR)
        {
          unpost_form (form);
          freeFormResources (form, formFields);
	  endwin ();
          return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
        }
        if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
        {
          unpost_form (form);
          freeFormResources (form, formFields);
	  endwin ();
          return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
        }
	stringCopy (idField1, repairString (field_buffer (formFields[0], 0)), 20);
	stringCopy (idField2, repairString (field_buffer (formFields[1], 0)), 20);
	if ((errorCode = checkField (idField1, "0123456789", 1, 20)) != OK)
	  mvprintw (LINES -12, FIELD_START_X+2, "%s", showTextErrorMessage (errorCode));
	else if
	  ((errorCode = checkField (idField2, "0123456789", 1, 20)) != OK)
	    mvprintw (LINES -12, FIELD_START_X+2, "%s", showTextErrorMessage (errorCode));
	else
	{
	  errorCode = removeParentRelationship (strtoul (idField1, NULL, 10), strtoul (idField2, NULL, 10));
	  mvprintw (LINES -12, FIELD_START_X+2, "%s", showTextErrorMessage (errorCode));
	}
      
	mvprintw (LINES -10, FIELD_START_X +2, "%s", showTextHelpMessage (NCURSES__PRESS_ANY_KEY_TO_CONTINUE));
	getch ();
	if (refresh () != OK)
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	  
	if (unpost_form (form) != OK)
	{
	  endwin ();
          return (NCURSES__ERROR_UNPOSTING_FORM);
	}
        if ((errorCode = freeFormResources (form, formFields)) != OK)
	{
	    endwin ();
            return (errorCode);
	}
      break;

      case (NCURSES__EDIT_PARENT_RELATIONSHIP_OPTION):
 	if ((formFields = createFormFields ('E')) == NULL)
	{
	  endwin ();
          return (NCURSES__ERROR_CREATING_FORM_FIELDS);
        }

	if ((form = new_form (formFields)) == NULL)
	{
	  freeFormFieldsResources (formFields);
	  endwin ();
	  return (NCURSES__ERROR_CREATING_FORM);
	}

	if (post_form (form) != OK)
	{
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_POSTING_FORM);
	}
	
	if (refresh () != OK)
	{
	  unpost_form (form);
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	}
	set_current_field (form, formFields[0]);
	showDescriptionsOfFields ('E');;
        wattron (stdscr, COLOR_PAIR(4));
	mvprintw (LINES -4, 2, "%s", showTextHelpMessage (NCURSES__BACKSPACE_TO_CLEAR));
	mvprintw (LINES -3, 2, "%s", showTextHelpMessage (NCURSES__ENTER_TO_SUBMIT));
        mvprintw (LINES -2, 2, "%s", showTextHelpMessage (NCURSES__ESC_TO_EXIT));
        wattroff (stdscr, COLOR_PAIR(4));
 	move (FIELD_START_Y +7, FIELD_START_X +20);

	if (refresh () != OK)
	{
	  unpost_form (form);
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	}

	while ((option = getch ()) != ENTER)
	  switch (option)
	  {
	    case (ESCAPE):
              unpost_form (form);
              freeFormResources (form, formFields);
	      endwin ();
	      return (OK);
	    break;
	    case (KEY_DOWN):
              if (form_driver (form, REQ_NEXT_FIELD) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
              if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_UP):
              if (form_driver (form, REQ_PREV_FIELD) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
              if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_LEFT):
              if (form_driver (form, REQ_PREV_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_RIGHT):
              if (form_driver (form, REQ_NEXT_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (BACKSPACE):
              if (form_driver (form, REQ_DEL_PREV) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (DEL):
              if (form_driver (form, REQ_DEL_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    default:
              if (form_driver (form, option) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
	  }
        if (form_driver (form, REQ_NEXT_FIELD) == E_SYSTEM_ERROR)
        {
          unpost_form (form);
          freeFormResources (form, formFields);
	  endwin ();
          return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
        }
        if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
        {
          unpost_form (form);
          freeFormResources (form, formFields);
	  endwin ();
          return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
        }
	stringCopy (idField1, repairString (field_buffer (formFields[0], 0)), 20);
	stringCopy (idField2, repairString (field_buffer (formFields[1], 0)), 20);
	stringCopy (idField3, repairString (field_buffer (formFields[2], 0)), 20);
	stringCopy (idField4, repairString (field_buffer (formFields[3], 0)), 20);
	if ((errorCode = checkField (idField1, "0123456789", 1, 20)) != OK)
	  mvprintw (LINES -12, FIELD_START_X+2, "%s", showTextErrorMessage (errorCode));
	else if
	  ((errorCode = checkField (idField2, "0123456789", 1, 20)) != OK)
	    mvprintw (LINES -12, FIELD_START_X+2, "%s", showTextErrorMessage (errorCode));
	else if
	  ((errorCode = checkField (idField3, "0123456789", 1, 20)) != OK)
	    mvprintw (LINES -12, FIELD_START_X+2, "%s", showTextErrorMessage (errorCode));
	else if
	  ((errorCode = checkField (idField4, "0123456789", 1, 20)) != OK)
	    mvprintw (LINES -12, FIELD_START_X+2, "%s", showTextErrorMessage (errorCode));
	else
	{
	  errorCode = editParentRelationship (strtoul (idField1, NULL, 10), strtoul (idField2, NULL, 10), strtoul (idField3, NULL, 10), strtoul (idField4, NULL, 10));
	  mvprintw (LINES -12, FIELD_START_X+2, "%s", showTextErrorMessage (errorCode));
	}
      
	mvprintw (LINES -10, FIELD_START_X +2, "%s", showTextHelpMessage (NCURSES__PRESS_ANY_KEY_TO_CONTINUE));
	getch ();
	if (refresh () != OK)
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	  
	if (unpost_form (form) != OK)
	{
	  endwin ();
          return (NCURSES__ERROR_UNPOSTING_FORM);
	}
        if ((errorCode = freeFormResources (form, formFields)) != OK)
	{
	    endwin ();
            return (errorCode);
	}
      break;

      case (NCURSES__GET_USERS_OPTION):
        formFields = (FIELD **) calloc (1 +1, sizeof (FIELD *));
        if ((formFields[0] = new_field (FIELD_HEIGHT, 30, FIELD_START_Y +6, FIELD_START_X, 0, 0)) == NULL)
        {
          free (formFields);
          return (NCURSES__ERROR_CREATING_FORM_FIELDS);
        }
	formFields[1] = NULL;
        set_field_back (formFields[0], A_UNDERLINE);
        set_field_fore (formFields[0], COLOR_PAIR(3));
        set_field_pad  (formFields[0], '_');
        field_opts_off (formFields[0], O_AUTOSKIP);
	if ((form = new_form (formFields)) == NULL)
	{
	  freeFormFieldsResources (formFields);
	  endwin ();
	  return (NCURSES__ERROR_CREATING_FORM);
	}      
	if (post_form (form) != OK)
	{
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_POSTING_FORM);
	}	
	if (refresh () != OK)
	{
	  unpost_form (form);
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	}
	set_current_field (form, formFields[0]);
        printInMiddle (stdscr, 5, 0, COLS, showTextHelpMessage (NCURSES__INFORM_SEARCH_KEY), COLOR_PAIR(4));
        wattron (stdscr, COLOR_PAIR(2));
        mvprintw (FIELD_START_Y +6, 15, "%s", showTextHelpMessage (SEARCH_KEY_FIELD_DESCRIPTION));	
        wattroff (stdscr, COLOR_PAIR(2));
        wattron (stdscr, COLOR_PAIR(4));	
	mvprintw (LINES -6, 4, "%s", showTextHelpMessage (NCURSES__BACKSPACE_TO_CLEAR));
	mvprintw (LINES -5, 4, "%s", showTextHelpMessage (NCURSES__ENTER_TO_SUBMIT));
        mvprintw (LINES -4, 4, "%s", showTextHelpMessage (NCURSES__ESC_TO_EXIT));
        wattroff (stdscr, COLOR_PAIR(4));
	move (FIELD_START_Y +6, FIELD_START_X);	
	if (refresh () != OK)
	{
	  unpost_form (form);
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	}	
	while ((option = getch ()) != ENTER)
	  switch (option)
	  {
	    case (ESCAPE):
              unpost_form (form);
              freeFormResources (form, formFields);
	      endwin ();
	      return (OK);
	    break;
	    case (KEY_LEFT):
              if (form_driver (form, REQ_PREV_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_RIGHT):
              if (form_driver (form, REQ_NEXT_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (BACKSPACE):
              if (form_driver (form, REQ_DEL_PREV) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (DEL):
              if (form_driver (form, REQ_DEL_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    default:
              if (form_driver (form, option) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
	  }
        if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
        {
          unpost_form (form);
          freeFormResources (form, formFields);
	  endwin ();
          return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
        }	
	strcpy (temp, repairString (field_buffer (formFields[0], 0)));
	if ((errorCode = checkField (temp, NAME_VALID_CHARACTERS, 1, MAX_LENGTH_NAME)) != OK)
	{
	  searchKeyIsValid = false;
	  mvprintw (LINES -12, FIELD_START_X+2, "%s", showTextErrorMessage (errorCode));
	}
	else
	{
	  searchKeyIsValid = true;
	  mvprintw (LINES -12, FIELD_START_X+2, "%s", showTextErrorMessage (OK));
	}
        mvprintw (LINES -10, FIELD_START_X+2, "%s", showTextHelpMessage (NCURSES__PRESS_ANY_KEY_TO_CONTINUE));
	getch ();
	if (refresh () != OK)
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	if (unpost_form (form) != OK)
	{
	  endwin ();
          return (NCURSES__ERROR_UNPOSTING_FORM);
	}
        if ((errorCode = freeFormResources (form, formFields)) != OK)
	{
	  endwin ();
          return (errorCode);
	}	
	

	if (searchKeyIsValid)
	{  
	  clear ();
	  if (refresh () != OK)
	    return (NCURSES__ERROR_REFRESHING_TERMINAL);
	  printInMiddle (stdscr, 3, 0, COLS, showTextHelpMessage (LIST_OF_USERS_FOUND), COLOR_PAIR(4));
          wattron (stdscr, COLOR_PAIR(4));
	  mvprintw (LINES -4, 2, "%s", showTextHelpMessage (NCURSES__BACKSPACE_TO_CLEAR));
	  mvprintw (LINES -3, 2, "%s", showTextHelpMessage (NCURSES__ENTER_TO_SUBMIT));
          mvprintw (LINES -2, 2, "%s", showTextHelpMessage (NCURSES__ESC_TO_EXIT));
          wattroff (stdscr, COLOR_PAIR(4));
	  move (FIELD_START_Y, FIELD_START_X);
          if ((errorCode = getUsers ( temp , &first )) != OK)
          {
            printf ("\n%s\n\n", showTextErrorMessage (errorCode));
	    return (errorCode);
          }
          wattron (stdscr, COLOR_PAIR(2));	  
          for (count = 0; (errorCode = retrieveFIFO (&first, &last, &buffer)) == OK; count++)
          {
            #ifdef ENGLISH 
              mvprintw (FIELD_START_Y +4 + count, FIELD_START_X -6, "User: %s  -->  Id: %llu", buffer.name , buffer.userId );
	    #elif PORTUGUESE
              mvprintw (FIELD_START_Y +4 + count, FIELD_START_X -6, "Usu�rio: %s  -->  Id: %llu", buffer.name , buffer.userId );
	    #endif
          }
          wattroff (stdscr, COLOR_PAIR(2));	  
          freeFIFOResources (&first, &last);
	  mvprintw (LINES -6, FIELD_START_X, "%s", showTextErrorMessage (OK));
	  mvprintw (LINES -4, FIELD_START_X, "%s", showTextHelpMessage (NCURSES__PRESS_ANY_KEY_TO_CONTINUE));
	  getch ();
  	  if (refresh () != OK)
	    return (NCURSES__ERROR_REFRESHING_TERMINAL);
	}
      break;

      case (NCURSES__MOUNT_OPTION):
        printf ("Option 'mount' selected\n");
      break;

      case (NCURSES__PASSWORD_OPTION):
        formFields = (FIELD **) calloc (1 +1, sizeof (FIELD *));
        if ((formFields[0] = new_field (FIELD_HEIGHT, 20, FIELD_START_Y +6, FIELD_START_X, 0, 0)) == NULL)
        {
          free (formFields);
          return (NCURSES__ERROR_CREATING_FORM_FIELDS);
        }
	formFields[1] = NULL;
        set_field_back (formFields[0], A_UNDERLINE);
        set_field_fore (formFields[0], COLOR_PAIR(3));
        set_field_pad  (formFields[0], '_');
        field_opts_off (formFields[0], O_AUTOSKIP);
	if ((form = new_form (formFields)) == NULL)
	{
	  freeFormFieldsResources (formFields);
	  endwin ();
	  return (NCURSES__ERROR_CREATING_FORM);
	}      
	if (post_form (form) != OK)
	{
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_POSTING_FORM);
	}	
	if (refresh () != OK)
	{
	  unpost_form (form);
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	}
	set_current_field (form, formFields[0]);
        printInMiddle (stdscr, 5, 0, COLS, showTextHelpMessage (NCURSES__INFORM_USER_ID), COLOR_PAIR(4));
        wattron (stdscr, COLOR_PAIR(2));
        mvprintw (FIELD_START_Y +6, 15, "%s", showTextHelpMessage (USER_ID_FIELD_DESCRIPTION));	
        wattroff (stdscr, COLOR_PAIR(2));
        wattron (stdscr, COLOR_PAIR(4));	
	mvprintw (LINES -6, 4, "%s", showTextHelpMessage (NCURSES__BACKSPACE_TO_CLEAR));
	mvprintw (LINES -5, 4, "%s", showTextHelpMessage (NCURSES__ENTER_TO_SUBMIT));
        mvprintw (LINES -4, 4, "%s", showTextHelpMessage (NCURSES__ESC_TO_EXIT));
        wattroff (stdscr, COLOR_PAIR(4));
	move (FIELD_START_Y +6, FIELD_START_X);	
	if (refresh () != OK)
	{
	  unpost_form (form);
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	}	
	while ((option = getch ()) != ENTER)
	  switch (option)
	  {
	    case (ESCAPE):
              unpost_form (form);
              freeFormResources (form, formFields);
	      endwin ();
	      return (OK);
	    break;
	    case (KEY_LEFT):
              if (form_driver (form, REQ_PREV_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_RIGHT):
              if (form_driver (form, REQ_NEXT_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (BACKSPACE):
              if (form_driver (form, REQ_DEL_PREV) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (DEL):
              if (form_driver (form, REQ_DEL_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    default:
              if (form_driver (form, option) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
	  }
        if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
        {
          unpost_form (form);
          freeFormResources (form, formFields);
	  endwin ();
          return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
        }	
	stringCopy (temp, repairString (field_buffer (formFields[0], 0)), 20);
	if ((errorCode = checkField (temp, "0123456789", 1, 20)) != OK)
	  mvprintw (LINES -12, FIELD_START_X+2, "%s", showTextErrorMessage (errorCode));
	else
	{  
	  if ((errorCode = recoveryPassword (strtoul (temp, NULL, 10))) != OK)
	    mvprintw (LINES -12, FIELD_START_X+2, "%s", showTextErrorMessage (errorCode));
	  else
	    mvprintw (LINES -12, FIELD_START_X +2, "%s", showTextErrorMessage (OK));
	}
	  
        mvprintw (LINES -10, FIELD_START_X+2, "%s", showTextHelpMessage (NCURSES__PRESS_ANY_KEY_TO_CONTINUE));
	getch ();
	if (refresh () != OK)
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	if (unpost_form (form) != OK)
	{
	  endwin ();
          return (NCURSES__ERROR_UNPOSTING_FORM);
	}
        if ((errorCode = freeFormResources (form, formFields)) != OK)
	{
	  endwin ();
          return (errorCode);
	}
      break;

      case (NCURSES__CHANGE_PASSWORD_OPTION):
        formFields = (FIELD **) calloc (2 +1, sizeof (FIELD *));
        if ((formFields[0] = new_field (FIELD_HEIGHT, 20, FIELD_START_Y +6, FIELD_START_X, 0, 0)) == NULL)
        {
          free (formFields);
          return (NCURSES__ERROR_CREATING_FORM_FIELDS);
        }
        if ((formFields[1] = new_field (FIELD_HEIGHT, 20, FIELD_START_Y +7, FIELD_START_X, 0, 0)) == NULL)
        {
          free (formFields);
          return (NCURSES__ERROR_CREATING_FORM_FIELDS);
        }
	formFields[2] = NULL;
	
        set_field_back (formFields[0], A_UNDERLINE);
        set_field_fore (formFields[0], COLOR_PAIR(3));
        set_field_pad  (formFields[0], '_');
        field_opts_off (formFields[0], O_AUTOSKIP);
        set_field_back (formFields[1], A_UNDERLINE);
        set_field_fore (formFields[1], COLOR_PAIR(3));
        set_field_pad  (formFields[1], '_');
        field_opts_off (formFields[1], O_AUTOSKIP);
        field_opts_off (formFields[1], O_PUBLIC);
	
	if ((form = new_form (formFields)) == NULL)
	{
	  freeFormFieldsResources (formFields);
	  endwin ();
	  return (NCURSES__ERROR_CREATING_FORM);
	}      
	if (post_form (form) != OK)
	{
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_POSTING_FORM);
	}	
	if (refresh () != OK)
	{
	  unpost_form (form);
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	}
	set_current_field (form, formFields[0]);
        printInMiddle (stdscr, 5, 0, COLS, showTextHelpMessage (CHANGE_PASSWORD_FORM_DESCRIPTION), COLOR_PAIR(4));
        wattron (stdscr, COLOR_PAIR(2));
        mvprintw (FIELD_START_Y +6, 15, "%s", showTextHelpMessage (USER_ID_FIELD_DESCRIPTION));	
        mvprintw (FIELD_START_Y +7, 15, "%s", showTextHelpMessage (RELATIONSHIP_SYSTEM__PROMPT_OF_PASSWORD));	
        wattroff (stdscr, COLOR_PAIR(2));
        wattron (stdscr, COLOR_PAIR(4));	
	mvprintw (LINES -6, 4, "%s", showTextHelpMessage (NCURSES__BACKSPACE_TO_CLEAR));
	mvprintw (LINES -5, 4, "%s", showTextHelpMessage (NCURSES__ENTER_TO_SUBMIT));
        mvprintw (LINES -4, 4, "%s", showTextHelpMessage (NCURSES__ESC_TO_EXIT));
        wattroff (stdscr, COLOR_PAIR(4));
	move (FIELD_START_Y +6, FIELD_START_X);	
	if (refresh () != OK)
	{
	  unpost_form (form);
	  freeFormResources (form, formFields);
	  endwin ();
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	}	
	while ((option = getch ()) != ENTER)
	  switch (option)
	  {
	    case (ESCAPE):
              unpost_form (form);
              freeFormResources (form, formFields);
	      endwin ();
	      return (OK);
	    break;
	    case (KEY_DOWN):
              if (form_driver (form, REQ_NEXT_FIELD) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
              if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_UP):
              if (form_driver (form, REQ_PREV_FIELD) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
              if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_LEFT):
              if (form_driver (form, REQ_PREV_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (KEY_RIGHT):
              if (form_driver (form, REQ_NEXT_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (BACKSPACE):
              if (form_driver (form, REQ_DEL_PREV) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    case (DEL):
              if (form_driver (form, REQ_DEL_CHAR) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
            break;
	    default:
              if (form_driver (form, option) == E_SYSTEM_ERROR)
              {
                unpost_form (form);
                freeFormResources (form, formFields);
		endwin ();
	        return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
	      }
	  }
        if (form_driver (form, REQ_NEXT_FIELD) == E_SYSTEM_ERROR)
        {
          unpost_form (form);
          freeFormResources (form, formFields);
	  endwin ();
          return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
        }
        if (form_driver (form, REQ_END_LINE) == E_SYSTEM_ERROR)
        {
          unpost_form (form);
          freeFormResources (form, formFields);
	  endwin ();
          return (NCURSES__ERROR_IN_FORM_DRIVER_FUNCTION);
        }
	stringCopy (temp,    repairString (field_buffer (formFields[0], 0)), 20);
	stringCopy (newPass, repairString (field_buffer (formFields[1], 0)), 20);
	if ((errorCode = checkField (temp, "0123456789", 1, 20)) != OK)
	  mvprintw (LINES -12, FIELD_START_X+2, "%s", showTextErrorMessage (errorCode));
	else if
	  ((errorCode = checkField (newPass, PLAIN_PASS_VALID_CHARACTERS, MIN_LENGTH_PLAIN_PASS, MAX_LENGTH_PLAIN_PASS)) != OK)
	    mvprintw (LINES -12, FIELD_START_X+2, "%s", showTextErrorMessage (errorCode));
	else
	{  
	  if ((errorCode = changePassword (strtoul (temp, NULL, 10), newPass)) != OK)
	    mvprintw (LINES -12, FIELD_START_X+2, "%s", showTextErrorMessage (errorCode));
	  else
	    mvprintw (LINES -12, FIELD_START_X +2, "%s", showTextErrorMessage (OK));
	}
	  
        mvprintw (LINES -10, FIELD_START_X+2, "%s", showTextHelpMessage (NCURSES__PRESS_ANY_KEY_TO_CONTINUE));
	getch ();
	if (refresh () != OK)
	  return (NCURSES__ERROR_REFRESHING_TERMINAL);
	if (unpost_form (form) != OK)
	{
	  endwin ();
          return (NCURSES__ERROR_UNPOSTING_FORM);
	}
        if ((errorCode = freeFormResources (form, formFields)) != OK)
	{
	  endwin ();
          return (errorCode);
	}
      break;

      case (NCURSES__UPLOAD_OPTION):
        printf ("Option 'Upload' selected\n");
      break;
     
      case (NCURSES__EXIT_OPTION):
        printf ("Option 'Exit' selected\n");
      break;
    }
  }

  clear ();
  if (refresh () != OK)
    return (NCURSES__ERROR_REFRESHING_TERMINAL);
  if (endwin () != OK)
    return (NCURSES__ERROR_FINALIZING_NCURSES);
  return (OK);
}  

/*$RCSfile: ncursesMenu.c,v $*/


