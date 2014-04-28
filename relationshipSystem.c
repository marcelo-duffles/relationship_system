//===========================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira
// Description: Main program source file 
// Date: 29/11/2004
//===========================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: relationshipSystem.c,v $
 * Revision 1.14  2005/02/16 22:11:21  marceloddm
 * CGI's added
 *
 * Revision 1.13  2004/12/24 03:42:16  marceloddm
 * ncursesMenu() function added
 *
 * Revision 1.12  2004/12/20 12:50:59  marceloddm
 * Code of 'g' option has been added
 *
 * Revision 1.11  2004/12/19 18:47:39  marceloddm
 * RELATIONSHIP_SYSTEM__NO_OPTION_SELECTED constant added
 *
 * Revision 1.10  2004/12/17 13:38:46  marceloddm
 * Code of 'edit' option added
 *
 * Revision 1.9  2004/12/16 00:28:35  marceloddm
 * Bugs have been solved!
 * We have to remember to replace the getchar() function by another with better performace
 *
 * Revision 1.8  2004/12/15 20:31:45  marceloddm
 * The program can be reinstalled now!
 *
 * Revision 1.7  2004/12/15 01:36:37  marceloddm
 * Bugs have been solved, but we still with problems with getchar() function and when reinstalling the system
 * The copyDataToUserData() function have been added to the code
 *
 * Revision 1.6  2004/12/14 02:52:06  marceloddm
 * New functions like backupSystemFiles() have been added
 * The code have been modified, but we have not complete the implementation of install() function...
 * Next step: fill the userData variable with dada given by command line.
 *
 * Revision 1.5  2004/12/13 08:00:01  marceloddm
 * Alterations have been done --> install() function
 *
 * Revision 1.4  2004/12/11 12:38:31  marceloddm
 * Author changed for 'marceloddm'
 *
 * Revision 1.3  2004/11/30 00:29:48  root
 * Help option is done
 *
 * Revision 1.2  2004/11/29 20:34:36  root
 * Main program source file
 *
 * Revision 1.1  2004/11/28 13:58:52  root
 * Initial revision
 *
 */ 
 

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>
#include <sys/errno.h>
#include <errno.h>
#include "functions.h"
#include "const.h"
#include "error.h"
#include "help.h"
#include "types.h"
#include "install.h"
#include "config.h"
#include "editUserData.h"
#include "getUsers.h"
#include "addUser.h"
#include "removeUser.h"
#include "inviteUser.h"
#include "acceptFriendshipInvitation.h"
#include "rejectFriendshipInvitation.h"
#include "getFriendshipInvitation.h"
#include "inviteFriend.h"
#include "excludeFriend.h"
#include "recoveryPassword.h"
#include "changePassword.h"
#include "getFriends.h"
#include "addParentRelationship.h"
#include "removeParentRelationship.h"
#include "editParentRelationship.h"
#include "changeUserCategory.h"
#include "ncursesMenu.h"
#include "mountFamilyTree.h"

 
static const char rcsid[] = "$Id: relationshipSystem.c,v 1.14 2005/02/16 22:11:21 marceloddm Exp marceloddm $";

int main (int argc, char **argv)
{
  char stringOptions[] = "nhtaeriIFPJXGcAREgmpCu";
  char password[MAX_LENGTH_PLAIN_PASS +1];
  char newPassword[MAX_LENGTH_PLAIN_PASS +1];
  char passwordFilename[MAX_LENGTH_LONG_FILENAME +1];
  int option, command, answer;
  unsigned errorCode, errorCodeBackup, nbArgs;
  FILE *passwordFile;
  boolean reinstall;
  userDataType userData, administratorData, buffer;
  userDataType *first, *last;
  familyTreeType family, *user, *cursor, *currentSon, *currentBrother;
  
  
  static struct option longOptions[] = 
  {
    {"ncurses",   0, 0, 'n'},
    {"help",      0, 0, 'h'},
    {"install",   0, 0, 't'},
    {"add",       0, 0, 'a'},
    {"edit",      0, 0, 'e'},
    {"remove",    0, 0, 'r'},
    {"invite",    0, 0, 'i'},
    {"Invite",    0, 0, 'I'},
    {"Friendship",0, 0, 'F'}, 
    {"Accept",    0, 0, 'P'},
    {"Reject",    0, 0, 'J'},
    {"Exclude",   0, 0, 'X'},
    {"Get",       0, 0, 'G'},
    {"change",    0, 0, 'c'},
    {"Add",       0, 0, 'A'},
    {"Remove",    0, 0, 'R'},
    {"Edit",      0, 0, 'E'},
    {"get",       0, 0, 'g'},
    {"mount",     0, 0, 'm'},
    {"password",  0, 0, 'p'},
    {"Change",    0, 0, 'C'},
    {"upload",    0, 0, 'u'},
    {0, 0, 0, 0}
  };
  
  
  if (argc == 1)
  {
    system ("clear");
    printf ("%s\n", showTextHelpMessage (RELATIONSHIP_SYSTEM__WELCOME_MESSAGE));
    shortHelp ();
    exit (OK);
  }
  
  opterr = 0;
  if ((option = getopt_long (argc, argv, stringOptions, longOptions, &command)) == -1)
  {
    printf ("\n%s\n\n", showTextErrorMessage (RELATIONSHIP_SYSTEM__NO_OPTION_SELECTED));
    exit (RELATIONSHIP_SYSTEM__NO_OPTION_SELECTED);
  }
  if (argv[1][0] != '-')
  {
    printf ("\n%s\n\n", showTextHelpMessage (RELATIONSHIP_SYSTEM__OPTION_MUST_COME_FIRST));
    exit (RELATIONSHIP_SYSTEM__OPTION_MUST_COME_FIRST);
  }
  if ((getopt_long (argc, argv, stringOptions, longOptions, &command)) != -1)
  {
    printf ("\n%s\n\n", showTextErrorMessage (RELATIONSHIP_SYSTEM__MORE_THAN_ONE_OPTION));
    exit (RELATIONSHIP_SYSTEM__MORE_THAN_ONE_OPTION);
  }
  
  nbArgs = argc - optind; 
      
  if ((option!='?') && (option != -1) && (option != 'h'))
  {
    if ((errorCode = getAdministratorPassword (password)) != OK)
    {
      printf ("\n%s\n\n", showTextErrorMessage (errorCode));
      exit (errorCode);
    }
    if ((errorCode = getLongFilename (DATA_DIR, PASSWORD_FILE_NAME, passwordFilename)) != OK)
    {
      printf ("\n%s\n\n", showTextErrorMessage (errorCode));
      exit (errorCode);
    }
    if ((passwordFile = fopen (passwordFilename, "r")) == NULL)
    {
      if (errno != ENOENT)
      {
	printf ("\n%s\n\n", showTextErrorMessage (RELATIONSHIP_SYSTEM__ERROR_OPENING_PASSWORD_FILE_FOR_READING));
	exit (RELATIONSHIP_SYSTEM__ERROR_OPENING_PASSWORD_FILE_FOR_READING);
      }
      if (option != 't')
      {
        printf ("\n%s\n\n", showTextErrorMessage (RELATIONSHIP_SYSTEM__NOT_YET_INSTALLED));
        exit (RELATIONSHIP_SYSTEM__NOT_YET_INSTALLED);
      }
    }
    else  
    {
      if ((errorCode = getUserData (passwordFile, PASSWORD_FILE_NAME, &administratorData)) != OK) 
      {
        printf ("\n%s\n\n", showTextErrorMessage (errorCode));
        fclose (passwordFile);
        exit (errorCode);
      }
      fclose (passwordFile);
      if ((errorCode = checkPassword (administratorData.encryptedPass, password)) != OK)
      {
        printf ("\n%s\n\n", showTextErrorMessage (errorCode));
        exit (errorCode);
      }
    }
  }
  
  switch (option)
  {
  
/*--------------------------------------------------------------------------------------------------------------------*/
  
    case 'n':
      errorCode = ncursesMenu ();
      system ("clear");
      printf ("\n%s\n\n", showTextErrorMessage (errorCode));
      exit (errorCode);
    break;
	
/*--------------------------------------------------------------------------------------------------------------------*/
	
    case 'h':
      system ("clear");
      printf ("\n%s\n\n", showTextHelpMessage (RELATIONSHIP_SYSTEM__WELCOME_MESSAGE));
      help ();
    break;
	
/*--------------------------------------------------------------------------------------------------------------------*/
	    
    case 't':
      if (nbArgs != NB_ARGS_OF_INSTALL_OPTION)
      {
        printf ("\n%s\n\n", showTextErrorMessage (RELATIONSHIP_SYSTEM__NB_ARGS_OF_INSTALL_OPTION));
	exit (RELATIONSHIP_SYSTEM__NB_ARGS_OF_INSTALL_OPTION);
      }
      if ((errorCode = fillUserData (&administratorData, argv, password)) != OK)
      {
        printf ("\n%s\n\n", showTextErrorMessage (errorCode));
	exit (errorCode);
      } 
      for (reinstall = true; reinstall;)
        if ((errorCode = install (&administratorData)) != OK)
        {
          printf ("\n%s\n", showTextErrorMessage (errorCode));
          if (errorCode == INSTALL__SYSTEM_ALREADY_INSTALLED)
	  {
	    printf ("\n%s", showTextHelpMessage (QUESTION_OF_REINSTALL));
	    #ifdef ENGLISH
	      while (((answer = getchar ()) != 'y') && (answer != 'Y') && (answer != 'n') && (answer != 'N'))
	        printf ("\n%s", showTextHelpMessage (QUESTION_OF_REINSTALL));
	    #elif PORTUGUESE
	      while (((answer = getchar ()) != 's') && (answer != 'S') && (answer != 'n') && (answer != 'N'))
	      printf ("\n%s", showTextHelpMessage (QUESTION_OF_REINSTALL));
	    #endif
	  
	    if ((answer == 'n') || (answer =='N'))
	    {
	      reinstall = false;
	      printf ("\n%s\n\n", showTextHelpMessage (RELATIONSHIP_SYSTEM__CONFIRMATION_OF_DO_NOT_REINSTALL));
	    }
	    else
	    {
	      if ((errorCodeBackup = backupSystemFiles ()) != OK)
	      {
	        printf ("\n%s\n\n", showTextErrorMessage (errorCodeBackup));
	        exit (errorCodeBackup);
	      }
	      reinstall = true;
	    }
	  }
	  else
	    exit (errorCode);
        }
        else
	{
	  reinstall = false;
          printf ("\n%s\n\n", showTextHelpMessage (INSTALLATION_DONE_SUCCESSFULLY));
	}
    break;
	
/*--------------------------------------------------------------------------------------------------------------------*/
	
    case 'a':
      if (nbArgs != NB_ARGS_OF_ADD_OPTION)
      {
        printf ("\n%s\n\n", showTextErrorMessage (RELATIONSHIP_SYSTEM__WRONG_NB_ARGS_OF_ADD_OPTION));
	exit (RELATIONSHIP_SYSTEM__WRONG_NB_ARGS_OF_ADD_OPTION);
      }
      printf ("\n");
      
      #ifdef ENGLISH
        if ((!strcmp (argv[3], "webUser")) || (!strcmp (argv[3], "2")))
          userData.category = webUser;
        else if ((!strcmp (argv[3], "relative")) || (!strcmp (argv[3], "3")))
          userData.category = relative;
      #elif PORTUGUESE
        if ((!strcmp (argv[3], "usuarioWeb")) || (!strcmp (argv[3], "2")))
          userData.category = webUser;
        else if ((!strcmp (argv[3], "parente")) || (!strcmp (argv[3], "3")))
          userData.category = relative;
      #endif
      
      if (userData.category == webUser)
      {
        stringCopy (newPassword, getpass (showTextHelpMessage (RELATIONSHIP_SYSTEM__PROMPT_OF_PASSWORD)), MAX_LENGTH_PLAIN_PASS); 
        printf ("\n");
        if (strcmp (newPassword, getpass (showTextHelpMessage (RELATIONSHIP_SYSTEM__PROMPT_OF_CONFIRMATION))))
        {
          printf ("\n%s\n\n", showTextErrorMessage (RELATIONSHIP_SYSTEM__LOGIN_INCORRECT_OF_NEW_USER));
          exit (RELATIONSHIP_SYSTEM__LOGIN_INCORRECT_OF_NEW_USER);
        }
        printf ("\n");
      }
      
      if ((errorCode = fillUserData (&userData, argv, newPassword)) != OK)
      {
        printf ("\n%s\n\n", showTextErrorMessage (errorCode));
	exit (errorCode);
      }
      errorCode = addUser (&userData); 
      printf ("\n%s\n\n", showTextErrorMessage (errorCode));
      exit (errorCode);
    break;
	
/*--------------------------------------------------------------------------------------------------------------------*/
	
    case 'e':
      if (nbArgs != NB_ARGS_OF_EDIT_OPTION)
      {
        printf ("\n%s\n\n", showTextErrorMessage (RELATIONSHIP_SYSTEM__NB_ARGS_OF_EDIT_OPTION));
	exit (RELATIONSHIP_SYSTEM__NB_ARGS_OF_EDIT_OPTION);
      } 
      if ((errorCode = getDataFromId ((userIdType) strtoul (argv[2], NULL, 10), &userData)) != OK)
      {
        printf ("\n%s\n\n", showTextErrorMessage (errorCode));
	exit (errorCode);
      }
      if ((errorCode = fillUserData (&userData, argv, NULL)) != OK)
      {
        printf ("\n%s\n\n", showTextErrorMessage (errorCode));
	exit (errorCode);
      }      
      errorCode = editUserData (&userData);
      printf ("\n%s\n\n", showTextErrorMessage (errorCode));
      exit (errorCode);
    break;
	
/*--------------------------------------------------------------------------------------------------------------------*/
	    
    case 'r':
      if (nbArgs != NB_ARGS_OF_REMOVE_USER_OPTION)
      {
        printf ("\n%s\n\n", showTextErrorMessage (RELATIONSHIP_SYSTEM__WRONG_NB_ARGS_OF_REMOVE_USER_OPTION));
	exit (RELATIONSHIP_SYSTEM__WRONG_NB_ARGS_OF_REMOVE_USER_OPTION);
      } 
      errorCode = removeUser ((userIdType) strtoul (argv[2], NULL, 10));
      printf ("\n%s\n\n", showTextErrorMessage (errorCode));
      exit (errorCode);
    break;
	
/*--------------------------------------------------------------------------------------------------------------------*/
	
    case 'i':
      if (nbArgs != NB_ARGS_OF_INVITE_USER_OPTION)
      {
        printf ("\n%s\n\n", showTextErrorMessage (RELATIONSHIP_SYSTEM__WRONG_NB_ARGS_OF_INVITE_USER_OPTION));
	exit (RELATIONSHIP_SYSTEM__WRONG_NB_ARGS_OF_INVITE_USER_OPTION);
      } 
      errorCode = inviteUser (strtoul (argv[2], NULL, 10), argv[3], argv[4]);
      printf ("\n%s\n\n", showTextErrorMessage (errorCode));
      exit (errorCode);
    break;
	
/*--------------------------------------------------------------------------------------------------------------------*/
	
    case 'I':
      if (nbArgs != NB_ARGS_OF_INVITE_FRIEND_OPTION)
      {
        printf ("\n%s\n\n", showTextErrorMessage (RELATIONSHIP_SYSTEM__WRONG_NB_ARGS_OF_INVITE_FRIEND_OPTION));
	exit (RELATIONSHIP_SYSTEM__WRONG_NB_ARGS_OF_INVITE_FRIEND_OPTION);
      } 
      errorCode = inviteFriend ((userIdType) strtoul (argv[2], NULL, 10), (userIdType) strtoul (argv[3], NULL, 10));
      printf ("\n%s\n\n", showTextErrorMessage (errorCode));
      exit (errorCode);
    break;    
	
/*--------------------------------------------------------------------------------------------------------------------*/
	
    case 'F':
      if (nbArgs != NB_ARGS_OF_GET_FRIENDSHIP_INVITATION_OPTION)
      {
        printf ("\n%s\n\n", showTextErrorMessage (RELATIONSHIP_SYSTEM__WRONG_NB_ARGS_OF_GET_FRIENDSHIP_INVITATION_OPTION));
	exit (RELATIONSHIP_SYSTEM__WRONG_NB_ARGS_OF_GET_FRIENDSHIP_INVITATION_OPTION);
      } 
      if ((errorCode = getFriendshipInvitation ((userIdType) strtoul (argv[2], NULL, 10), &first )) != OK)
      {
        printf ("\n%s\n\n", showTextErrorMessage (errorCode));
	exit (errorCode);
      }
      while (retrieveFIFO ( &first, &last, &buffer ) == OK)
      {
        #ifdef ENGLISH 
          printf ( "\nUser: %s  -->  Id: %llu", buffer.name , buffer.userId );
	#elif PORTUGUESE
	  printf ( "\nUsuário: %s  -->  Id: %llu", buffer.name , buffer.userId );
	#endif
      }
      freeFIFOResources (&first, &last);
      printf ("\n\n%s\n\n", showTextErrorMessage (OK));
    break;    
	
/*--------------------------------------------------------------------------------------------------------------------*/
	
    case 'P':
      if (nbArgs != NB_ARGS_OF_ACCEPT_OPTION)
      {
        printf ("\n%s\n\n", showTextErrorMessage (RELATIONSHIP_SYSTEM__WRONG_NB_ARGS_OF_ACCEPT_OPTION));
	exit (RELATIONSHIP_SYSTEM__WRONG_NB_ARGS_OF_ACCEPT_OPTION);
      } 
      errorCode = acceptFriendshipInvitation ((userIdType) strtoul (argv[optind], NULL, 10), (userIdType) strtoul (argv[optind +1], NULL, 10));
      printf ("\n%s\n\n", showTextErrorMessage (errorCode));
      exit (errorCode);
    break;
	
/*--------------------------------------------------------------------------------------------------------------------*/
	
    case 'J':
      if (nbArgs != NB_ARGS_OF_REJECT_OPTION)
      {
        printf ("\n%s\n\n", showTextErrorMessage (RELATIONSHIP_SYSTEM__WRONG_NB_ARGS_OF_REJECT_OPTION));
	exit (RELATIONSHIP_SYSTEM__WRONG_NB_ARGS_OF_REJECT_OPTION);
      } 
      errorCode = rejectFriendshipInvitation ((userIdType) strtoul (argv[optind], NULL, 10), (userIdType) strtoul (argv[optind +1], NULL, 10));
      printf ("\n%s\n\n", showTextErrorMessage (errorCode));
      exit (errorCode);
    break;
	
/*--------------------------------------------------------------------------------------------------------------------*/
	
    case 'X':
      if (nbArgs != NB_ARGS_OF_EXCLUDE_OPTION)
      {
        printf ("\n%s\n\n", showTextErrorMessage (RELATIONSHIP_SYSTEM__WRONG_NB_ARGS_OF_EXCLUDE_OPTION));
	exit (RELATIONSHIP_SYSTEM__WRONG_NB_ARGS_OF_EXCLUDE_OPTION);
      } 
      errorCode = excludeFriend ((userIdType) strtoul (argv[2], NULL, 10), (userIdType) strtoul (argv[3], NULL, 10));
      printf ("\n%s\n\n", showTextErrorMessage (errorCode));
      exit (errorCode);
    break;
	
/*--------------------------------------------------------------------------------------------------------------------*/
	
    case 'G':
      if (nbArgs != NB_ARGS_OF_GET_FRIENDS_OPTION)
      {
        printf ("\n%s\n\n", showTextErrorMessage (RELATIONSHIP_SYSTEM__WRONG_NB_ARGS_OF_GET_FRIENDS_OPTION));
	exit (RELATIONSHIP_SYSTEM__WRONG_NB_ARGS_OF_GET_FRIENDS_OPTION);
      } 
      if ((errorCode = getFriends ((userIdType) strtoul (argv[2], NULL, 10), &first )) != OK)
      {
        printf ("\n%s\n\n", showTextErrorMessage (errorCode));
	exit (errorCode);
      }
      while (retrieveFIFO (&first, &last, &buffer) == OK)
      {
        #ifdef ENGLISH 
          printf ( "\nUser: %s  -->  Id: %llu", buffer.name , buffer.userId );
	#elif PORTUGUESE
	  printf ( "\nUsuário: %s  -->  Id: %llu", buffer.name , buffer.userId );
	#endif
      }
      freeFIFOResources (&first, &last);
      printf ("\n\n%s\n\n", showTextErrorMessage (OK));
    break;
	
/*--------------------------------------------------------------------------------------------------------------------*/
	
    case 'c':
      if (nbArgs != NB_ARGS_OF_CHANGE_CATEGORY_OPTION)
      {
        printf ("\n%s\n\n", showTextErrorMessage (RELATIONSHIP_SYSTEM__WRONG_NB_ARGS_OF_CHANGE_CATEGORY_OPTION));
	exit (RELATIONSHIP_SYSTEM__WRONG_NB_ARGS_OF_CHANGE_CATEGORY_OPTION);
      } 
      
      if ((errorCode = getDataFromId ( (userIdType) strtoul (argv[optind], NULL, 10) , &buffer )) != OK )
      {
        printf ("\n%s\n\n", showTextErrorMessage (errorCode));
        exit (errorCode);
      }
      
      if ( buffer.category == relative )
      {
        printf ("\n%s ", showTextHelpMessage (USERNAME_FIELD_DESCRIPTION));
	fgets ( buffer.userName , MAX_LENGTH_USERNAME , stdin );
	if (buffer.userName[strlen (buffer.userName) -1] == '\n')
	  buffer.userName[strlen (buffer.userName) -1] = EOS;
	printf ("\n");
	stringCopy (buffer.plainPass, getpass (showTextHelpMessage (REQUIRE_NEW_WEB_USER_PASSWORD)), MAX_LENGTH_PLAIN_PASS);
	printf ("\n%s ", showTextHelpMessage (EMAIL_FIELD_DESCRIPTION));
	fgets ( buffer.email , MAX_LENGTH_EMAIL , stdin );
	if (buffer.email[strlen (buffer.email) -1] == '\n')
	  buffer.email[strlen (buffer.email) -1] = EOS;
	printf ("\n");
	buffer.category = webUser;
      }
      else
        if ( buffer.category == webUser )
          buffer.category = relative;
      
      if ((errorCode = changeUserCategory ( &buffer ) ) != OK )
      {
        printf ("\n%s\n\n", showTextErrorMessage (errorCode));
        exit (errorCode);
      }
      printf ("\n%s\n\n", showTextErrorMessage (OK));
    break;
	
/*--------------------------------------------------------------------------------------------------------------------*/
	
    case 'A':
      if (nbArgs != NB_ARGS_OF_ADD_PARENT_OPTION)
      {
        printf ("\n%s\n\n", showTextErrorMessage (RELATIONSHIP_SYSTEM__WRONG_NB_ARGS_OF_ADD_PARENT_OPTION));
	exit (RELATIONSHIP_SYSTEM__WRONG_NB_ARGS_OF_ADD_PARENT_OPTION);
      } 
      if ((errorCode = addParentRelationship ((userIdType) strtoul (argv[2], NULL, 10), (userIdType) strtoul (argv[3], NULL, 10))) != OK )
      {
        printf ("\n%s\n\n", showTextErrorMessage (errorCode));
        exit (errorCode);
      }
      printf ("\n%s\n\n", showTextErrorMessage (OK));
    break;
	
/*--------------------------------------------------------------------------------------------------------------------*/
	
    case 'R':
      if (nbArgs != NB_ARGS_OF_REMOVE_PARENT_OPTION)
      {
        printf ("\n%s\n\n", showTextErrorMessage (RELATIONSHIP_SYSTEM__WRONG_NB_ARGS_OF_REMOVE_PARENT_OPTION));
	exit (RELATIONSHIP_SYSTEM__WRONG_NB_ARGS_OF_REMOVE_PARENT_OPTION);
      } 
      if ((errorCode = removeParentRelationship ((userIdType) strtoul (argv[2], NULL, 10), (userIdType) strtoul (argv[3], NULL, 10))) != OK )
      {
        printf ("\n%s\n\n", showTextErrorMessage (errorCode));
        exit (errorCode);
      }
      printf ("\n%s\n\n", showTextErrorMessage (OK));
    break;
	
/*--------------------------------------------------------------------------------------------------------------------*/
	
    case 'E':
      if (nbArgs != NB_ARGS_OF_EDIT_PARENT_OPTION)
      {
        printf ("\n%s\n\n", showTextErrorMessage (RELATIONSHIP_SYSTEM__WRONG_NB_ARGS_OF_EDIT_PARENT_OPTION));
	exit (RELATIONSHIP_SYSTEM__WRONG_NB_ARGS_OF_EDIT_PARENT_OPTION);
      } 
      if ((errorCode = editParentRelationship ((userIdType) strtoul (argv[2], NULL, 10), (userIdType) strtoul (argv[3], NULL, 10), (userIdType) strtoul (argv[4], NULL, 10), (userIdType) strtoul (argv[5], NULL, 10))) != OK )
      {
        printf ("\n%s\n\n", showTextErrorMessage (errorCode));
        exit (errorCode);
      }
      printf ("\n%s\n\n", showTextErrorMessage (OK));
    break;   
	
/*--------------------------------------------------------------------------------------------------------------------*/
	
    case 'g':
      if (nbArgs != NB_ARGS_OF_GET_USERS_OPTION)
      {
        printf ("\n%s\n\n", showTextErrorMessage (RELATIONSHIP_SYSTEM__NB_ARGS_OF_GET_USERS_OPTION));
	exit (RELATIONSHIP_SYSTEM__NB_ARGS_OF_GET_USERS_OPTION);
      } 
      if ((errorCode = getUsers ( argv[optind] , &first )) != OK)
      {
        printf ("\n%s\n\n", showTextErrorMessage (errorCode));
	exit (errorCode);
      }
      while (retrieveFIFO (&first, &last, &buffer) == OK)
      {
        #ifdef ENGLISH 
          printf ( "\nUser: %s  -->  Id: %llu", buffer.name , buffer.userId );
	#elif PORTUGUESE
	  printf ( "\nUsuário: %s  -->  Id: %llu", buffer.name , buffer.userId );
	#endif
      }
      freeFIFOResources (&first, &last);
      printf ("\n\n%s\n\n", showTextErrorMessage (OK));
    break;          
	
/*--------------------------------------------------------------------------------------------------------------------*/
	
    case 'm':
      if (nbArgs != NB_ARGS_OF_MOUNT_OPTION)
      {
        printf ("\n%s\n\n", showTextErrorMessage (RELATIONSHIP_SYSTEM__NB_ARGS_OF_MOUNT_OPTION));
	exit (RELATIONSHIP_SYSTEM__NB_ARGS_OF_MOUNT_OPTION);
      } 
      user = &family;
      if ((errorCode = mountFamilyTree (strtoul (argv[2], NULL, 10), strtoul (argv[3], NULL, 10), strtoul (argv[4], NULL, 10), &user)) != OK)
      {
        printf ("\n%s\n\n", showTextErrorMessage (errorCode));
	exit (errorCode);
      }
      while ((cursor = retrieveFamily (&user)) != NULL)
      {
        #ifdef ENGLISH 
	  if ((errorCode = getDataFromId (cursor->userId, &buffer)) != OK)
	  {
            printf ("\n%s\n\n", showTextErrorMessage (errorCode));
	    exit (errorCode);
          }
          printf ( "\nUser: %s  -->  Id: %llu",    buffer.name , buffer.userId );
	  
	  if (cursor->parent != NULL)
	  {
	    if ((errorCode = getDataFromId ((cursor->parent)->userId, &buffer)) != OK)
	    {
              printf ("\n%s\n\n", showTextErrorMessage (errorCode));
	      exit (errorCode);
            }
            printf ( "\nParent1: %s  -->  Id: %llu", buffer.name , buffer.userId );
	    
	    if ((cursor->parent)->spouse != NULL)
	    {
	      if ((errorCode = getDataFromId (((cursor->parent)->spouse)->userId, &buffer)) != OK)
	      {
                printf ("\n%s\n\n", showTextErrorMessage (errorCode));
	        exit (errorCode);
              }
              printf ( "\nParent2: %s  -->  Id: %llu", buffer.name , buffer.userId );
	    }
	  }
	    
	  if (cursor->spouse != NULL)
	  {
	    if ((errorCode = getDataFromId ((cursor->spouse)->userId, &buffer)) != OK)
	    {
              printf ("\n%s\n\n", showTextErrorMessage (errorCode));
	      exit (errorCode);
            }
            printf ( "\nSpouse: %s  -->  Id: %llu", buffer.name , buffer.userId );
	  }

          for (currentBrother = cursor->brother; currentBrother != NULL; currentBrother = currentBrother->brother)
	  {
	    if ((errorCode = getDataFromId (currentBrother->userId, &buffer)) != OK)
	    {
              printf ("\n%s\n\n", showTextErrorMessage (errorCode));
	      exit (errorCode);
            }
            printf ( "\nNext brother/sister: %s  -->  Id: %llu", buffer.name , buffer.userId );
	  }
	  
          for (currentSon = cursor->son; currentSon != NULL; currentSon = currentSon->brother)
	  {
	    if ((errorCode = getDataFromId (currentSon->userId, &buffer)) != OK)
	    {
              printf ("\n%s\n\n", showTextErrorMessage (errorCode));
	      exit (errorCode);
            }
            printf ( "\nSon/daughter: %s  -->  Id: %llu", buffer.name , buffer.userId );
	  }
	  
	  printf ( "\n");
	#elif PORTUGUESE
	  if ((errorCode = getDataFromId (cursor->userId, &buffer)) != OK)
	  {
            printf ("\n%s\n\n", showTextErrorMessage (errorCode));
	    exit (errorCode);
          }
          printf ( "\nUsuário: %s  -->  Id: %llu",    buffer.name , buffer.userId );
	  
	  if (cursor->parent != NULL)
	  {
	    if ((errorCode = getDataFromId ((cursor->parent)->userId, &buffer)) != OK)
	    {
              printf ("\n%s\n\n", showTextErrorMessage (errorCode));
	      exit (errorCode);
            }
            printf ( "\nPai/mãe: %s  -->  Id: %llu", buffer.name , buffer.userId );
	    
	    if ((cursor->parent)->spouse != NULL)
	    {
	      if ((errorCode = getDataFromId (((cursor->parent)->spouse)->userId, &buffer)) != OK)
	      {
                printf ("\n%s\n\n", showTextErrorMessage (errorCode));
	        exit (errorCode);
              }
              printf ( "\nPai/mãe: %s  -->  Id: %llu", buffer.name , buffer.userId );
	    }
	  }
	    
	  if (cursor->spouse != NULL)
	  {
	    if ((errorCode = getDataFromId ((cursor->spouse)->userId, &buffer)) != OK)
	    {
              printf ("\n%s\n\n", showTextErrorMessage (errorCode));
	      exit (errorCode);
            }
            printf ( "\nEsposo(a): %s  -->  Id: %llu", buffer.name , buffer.userId );
	  }

          for (currentBrother = cursor->brother; currentBrother != NULL; currentBrother = currentBrother->brother)
	  {
	    if ((errorCode = getDataFromId (currentBrother->userId, &buffer)) != OK)
	    {
              printf ("\n%s\n\n", showTextErrorMessage (errorCode));
	      exit (errorCode);
            }
            printf ( "\nPróximo(a) irmã(o): %s  -->  Id: %llu", buffer.name , buffer.userId );
	  }
	  
          for (currentSon = cursor->son; currentSon != NULL; currentSon = currentSon->brother)
	  {
	    if ((errorCode = getDataFromId (currentSon->userId, &buffer)) != OK)
	    {
              printf ("\n%s\n\n", showTextErrorMessage (errorCode));
	      exit (errorCode);
            }
            printf ( "\nFilho(a): %s  -->  Id: %llu", buffer.name , buffer.userId );
	  }
	  
	  printf ( "\n");
	#endif
      }
      printf ("\n\n%s\n\n", showTextErrorMessage (OK));
    break;
	
/*--------------------------------------------------------------------------------------------------------------------*/
	
    case 'p':
      if (nbArgs != NB_ARGS_OF_RECOVERY_OPTION)
      {
        printf ("\n%s\n\n", showTextErrorMessage (RELATIONSHIP_SYSTEM__NB_ARGS_OF_RECOVERY_OPTION));
	exit (RELATIONSHIP_SYSTEM__NB_ARGS_OF_RECOVERY_OPTION);
      } 
      errorCode = recoveryPassword ((userIdType) strtoul (argv[2], NULL, 10));
      printf ("\n%s\n\n", showTextErrorMessage (errorCode));
      exit (errorCode);      
    break;
	
/*--------------------------------------------------------------------------------------------------------------------*/
	
    case 'C':
      if (nbArgs != NB_ARGS_OF_CHANGE_PASSWORD_OPTION)
      {
        printf ("\n%s\n\n", showTextErrorMessage (RELATIONSHIP_SYSTEM__NB_ARGS_OF_CHANGE_PASSWORD_OPTION));
	exit (RELATIONSHIP_SYSTEM__NB_ARGS_OF_CHANGE_PASSWORD_OPTION);
      } 
      printf ("\n");
      stringCopy (newPassword, getpass (showTextHelpMessage (RELATIONSHIP_SYSTEM__PROMPT_OF_PASSWORD)), MAX_LENGTH_PLAIN_PASS); 
      printf ("\n");
      if (strcmp (newPassword, getpass (showTextHelpMessage (RELATIONSHIP_SYSTEM__PROMPT_OF_CONFIRMATION))))
      {
        printf ("\n%s\n\n", showTextErrorMessage (RELATIONSHIP_SYSTEM__CONFIRMATION_DOES_NOT_MATCH));
        exit (RELATIONSHIP_SYSTEM__CONFIRMATION_DOES_NOT_MATCH);
      }
      printf ("\n");
      errorCode = changePassword ((userIdType) strtoul (argv[2], NULL, 10), newPassword);
      printf ("\n%s\n\n", showTextErrorMessage (errorCode));
      exit (errorCode); 
    break;    
	
/*--------------------------------------------------------------------------------------------------------------------*/
	
    case 'u':
      printf ("Option 'u' selected\n");
    break;           
	
/*--------------------------------------------------------------------------------------------------------------------*/
	
    default:
      printf ("\n%s\n\n", showTextHelpMessage (RELATIONSHIP_SYSTEM__UNKNOWN_OPTION));
      shortHelp ();
  }                       
      
  exit (OK);
}
  

// $RCSfile: relationshipSystem.c,v $
