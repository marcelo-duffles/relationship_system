//=========================================================================//
// Universidade Federal do Rio de Janeiro
// Escola PolitÈcnica
// Departamento de EletrÙnica e de ComputaÁ„o
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira
// Description: Constants header file 
// Date: 22/10/2004
//==========================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: const.h,v $
 * Revision 1.16  2005/02/16 22:11:21  marceloddm
 * CGI's added
 *
 * Revision 1.15  2004/12/20 23:46:34  marceloddm
 * Constants added: COOKIE_NAME_LENGTH, COOKIE_VALUE_LENGTH, COOKIE_EXPIRATION and COOKIE_VALUE_VALID_CHARACTERS
 *
 * Revision 1.14  2004/12/20 12:35:42  marceloddm
 * Space character has been added to some constants...
 *
 * Revision 1.13  2004/12/16 22:51:40  marceloddm
 * __ML_CGI_GLOBAL_VARIABLES__ constant added
 *
 * Revision 1.12  2004/12/16 00:07:12  marceloddm
 * USERS_FILE_LENGTH and USERS_TEMP_FILE_NAME constants added
 *
 * Revision 1.11  2004/12/15 18:43:26  marceloddm
 * New constants concerning to the correction of the checkUserData() functions have been added.
 *
 * Revision 1.10  2004/12/15 18:29:08  marceloddm
 * Constants added: ENCRYPTED_PASS_LENGTH_RELATIVE and MIN_LENGTH_EMAIL_RELATIVE
 *
 * Revision 1.9  2004/12/15 18:22:26  marceloddm
 * Constants of copyDataToUserData() function have been removed
 *
 * Revision 1.8  2004/12/15 01:25:17  marceloddm
 * Constant added: ENCRYPTED_PASS_VALID_CHARACTERS
 *
 * Revision 1.6  2004/12/14 02:51:09  marceloddm
 * Grammar corrections have been made
 *
 * Revision 1.5  2004/12/13 07:41:02  marceloddm
 * More constants have been added
 *
 * Revision 1.4  2004/12/11 12:32:58  marceloddm
 * Author changed for 'marceloddm'
 *
 * Revision 1.3  2004/11/30 00:23:30  root
 * Last modification: MAX_LENGTH_PLAIN_PASS
 *
 * Revision 1.2  2004/11/26 13:38:51  root
 * RCS's strings added
 *
 */ 
 
  
#ifndef _CONST_H_
#define _CONST_H_ "@(#)const.h $Revision: 1.16 $"

#define RANDOM_STRING_VALID_CHARACTERS "abcdefghijklmnopqrstuvxyzwABCDEFGHIJKLMNOPQRSTUVXYZW0123456789"
#define COOKIE_VALUE_VALID_CHARACTERS  "abcdefghijklmnopqrstuvxyzwABCDEFGHIJKLMNOPQRSTUVXYZW0123456789"
#define PLAIN_PASS_VALID_CHARACTERS        "abcÁdefghijklmnopqrstuvxyzwABCDEFGHIJKLMNOPQRSTUVXYZW0123456789,.;:!?@#$%&*()[]{} '`~^=+-"
#define ENCRYPTED_PASS_VALID_CHARACTERS        "abcÁdefghijklmnopqrstuvxyzwABCDEFGHIJKLMNOPQRSTUVXYZW0123456789,.;:!?@#$%%\%&\"'&*()[]{} <>'`~^=+-\"_/\\|"
#define USERNAME_VALID_CHARACTERS    "abcdefghijklmnopqrstuvxyzw"
#define DESCRIPTION_VALID_CHARACTERS "abcÁdefghijklmnopqrstuvxyzwABCDEFGHIJKLMNOPQRSTUVXYZW0123456789,.;:!?@#%&*()[]{}'`~^_=+-·ÈÌÛ˙‰ÎÔˆ¸„ı‡ËÏÚ˘‚ÍÓÙ˚ "
#define STREET_VALID_CHARACTERS        "abcÁdefghijklmnopqrstuvxyzwABCDEFGHIJKLMNOPQRSTUVXYZW0123456789,;#&()'-/ ·ÈÌÛ˙‰ÎÔˆ¸„ı‡ËÏÚ˘‚ÍÓÙ˚"
#define DISTRICT_VALID_CHARACTERS      "abcÁdefghijklmnopqrstuvxyzwABCDEFGHIJKLMNOPQRSTUVXYZW0123456789,;#&()'-/ ·ÈÌÛ˙‰ÎÔˆ¸„ı‡ËÏÚ˘‚ÍÓÙ˚"
#define CITY_VALID_CHARACTERS 	       "abcÁdefghijklmnopqrstuvxyzwABCDEFGHIJKLMNOPQRSTUVXYZW0123456789,;#&()'-/ ·ÈÌÛ˙‰ÎÔˆ¸„ı‡ËÏÚ˘‚ÍÓÙ˚"
#define STATE_VALID_CHARACTERS	       "abcÁdefghijklmnopqrstuvxyzwABCDEFGHIJKLMNOPQRSTUVXYZW0123456789,;#&()'-/ ·ÈÌÛ˙‰ÎÔˆ¸„ı‡ËÏÚ˘‚ÍÓÙ˚"
#define COUNTRY_VALID_CHARACTERS       "abcÁdefghijklmnopqrstuvxyzwABCDEFGHIJKLMNOPQRSTUVXYZW0123456789,;#&()'-/ ·ÈÌÛ˙‰ÎÔˆ¸„ı‡ËÏÚ˘‚ÍÓÙ˚"
#define NAME_VALID_CHARACTERS	       "abcÁdefghijklmnopqrstuvxyzwABCDEFGHIJKLMNOPQRSTUVXYZW0123456789 -'. ·ÈÌÛ˙‰ÎÔˆ¸„ı‡ËÏÚ˘‚ÍÓÙ˚"
#define EMAIL_VALID_CHARACTERS	       "abcÁdefghijklmnopqrstuvxyzwABCDEFGHIJKLMNOPQRSTUVXYZW0123456789_-@."
#define HOMEPAGE_VALID_CHARACTERS      "abcÁdefghijklmnopqrstuvxyzwABCDEFGHIJKLMNOPQRSTUVXYZW0123456789_-.~:()&8'?;,@!$%+=-_][{}^'`/"
#define TEL_NUMBER_VALID_CHARACTERS			"0123456789"
#define CELL_NUMBER_VALID_CHARACTERS			"0123456789"
#define BIRTHDAY_VALID_CHARACTERS			"0123456789"
#define HOME_NUMBER_VALID_CHARACTERS			"0123456789"
#define COMPLEMENT_VALID_CHARACTERS			"abcdefghijklmnopqrstuvxyzwABCDEFGHIJKLMNOPQRSTUVXYZW0123456789-/\\*()_,.:#@'[]{}|;&·ÈÌÛ˙‰ÎÔˆ¸„ı‡ËÏÚ˘‚ÍÓÙ˚"
#define ZIP_CODE_VALID_CHARACTERS			"0123456789"
#define EOS						'\0'
#define SALT_LENGTH					11
#define ENCRYPTED_PASS_LENGTH_RELATIVE			0
#define ENCRYPTED_PASS_LENGTH				34
#define RANDOM_STRING_MAX_LENGTH			1024
#define MAX_LENGTH_LONG_FILENAME			100
#define LENGTH_USERNAME_RELATIVE			0
#define MIN_LENGTH_USERNAME				2
#define MAX_LENGTH_USERNAME				32
#define LENGTH_PLAIN_PASS_RELATIVE			0
#define MIN_LENGTH_PLAIN_PASS				2
#define MAX_LENGTH_PLAIN_PASS				32
#define MIN_LENGTH_STREET				0
#define MAX_LENGTH_STREET				256
#define MIN_LENGTH_HOME_NUMBER				0
#define MAX_LENGTH_HOME_NUMBER				10
#define MIN_LENGTH_COMPLEMENT				0
#define MAX_LENGTH_COMPLEMENT				64
#define MIN_LENGTH_DISTRICT				0
#define MAX_LENGTH_DISTRICT				100
#define MIN_LENGTH_CITY					0
#define MAX_LENGTH_CITY					100
#define MIN_LENGTH_STATE				0
#define MAX_LENGTH_STATE				100
#define MIN_LENGTH_COUNTRY				0
#define MAX_LENGTH_COUNTRY				100
#define MIN_LENGTH_ZIP_CODE				0
#define MAX_LENGTH_ZIP_CODE				10
#define MIN_LENGTH_TEL_NUMBER				0
#define MAX_LENGTH_TEL_NUMBER				12
#define MIN_LENGTH_CELL_NUMBER				0
#define MAX_LENGTH_CELL_NUMBER				12
#define MIN_LENGTH_NAME					2
#define MAX_LENGTH_NAME					100
#define MIN_LENGTH_EMAIL_RELATIVE			0
#define MIN_LENGTH_EMAIL				2
#define MAX_LENGTH_EMAIL				100
#define MIN_LENGTH_HOMEPAGE				0
#define MAX_LENGTH_HOMEPAGE				100
#define MIN_LENGTH_BIRTHDAY				8
#define MAX_LENGTH_BIRTHDAY				8
#define LENGTH_DAY_OF_BORN				2
#define LENGTH_MONTH_OF_BORN				2
#define LENGTH_YEAR_OF_BORN				4
#define MIN_LENGTH_DESCRIPTION				0
#define MAX_LENGTH_DESCRIPTION				1024
#define NB_ARGS_OF_REINSTALL_OPTION			21
#define NB_ARGS_OF_INSTALL_OPTION			20
#define NB_ARGS_OF_ADD_OPTION				21
#define NB_ARGS_OF_EDIT_OPTION				20
#define NB_ARGS_OF_REJECT_OPTION			2
#define NB_ARGS_OF_ACCEPT_OPTION			2
#define NB_ARGS_OF_GET_USERS_OPTION			1
#define NB_ARGS_OF_GET_FRIENDS_OPTION			1
#define NB_ARGS_OF_EXCLUDE_OPTION			2
#define NB_ARGS_OF_INVITE_FRIEND_OPTION			2
#define NB_ARGS_OF_REMOVE_USER_OPTION			1
#define NB_ARGS_OF_INVITE_USER_OPTION			3
#define NB_ARGS_OF_RECOVERY_OPTION			1
#define NB_ARGS_OF_ADD_PARENT_OPTION			2
#define NB_ARGS_OF_REMOVE_PARENT_OPTION			2
#define NB_ARGS_OF_EDIT_PARENT_OPTION			4
#define NB_ARGS_OF_CHANGE_PASSWORD_OPTION		1
#define NB_ARGS_OF_CHANGE_CATEGORY_OPTION		1
#define NB_ARGS_OF_GET_FRIENDSHIP_INVITATION_OPTION	1
#define NB_ARGS_OF_MOUNT_OPTION				3
#define PASSWORD_FILE_LENGTH				8
#define USERS_FILE_LENGTH				5
#define USERS_TEMP_FILE_NAME				"users.tmp"
#define PASSWORD_TEMP_FILE_NAME				"password.tmp"
#define FRIENDS_TEMP_FILE_NAME				"friends.tmp"
#define PARENTS_TEMP_FILE_NAME				"parents.tmp"			
#define COOKIE_NAME_LENGTH				20
#define COOKIE_VALUE_LENGTH				64
#define COOKIE_EXPIRATION				1800
#define MIN_LENGTH_IP					7
#define MAX_LENGTH_IP					15 
#define ESCAPE						27
#define BACKSPACE					127
//8
#define DEL						263
//127
#define ENTER						10
#define NCURSES__NB_MENU_OPTIONS			21		
#define NEW_PASSWORD_LENGTH				8
#define NCURSES__REINSTALL_OPTION			1
#define NCURSES__ADD_USER_OPTION			2
#define NCURSES__EDIT_OPTION				3
#define NCURSES__REMOVE_OPTION				4
#define NCURSES__INVITE_USER_OPTION			5
#define NCURSES__INVITE_FRIEND_OPTION			6
#define NCURSES__FRIENDSHIP_OPTION			7
#define NCURSES__ACCEPT_OPTION				8
#define NCURSES__REJECT_OPTION				9
#define NCURSES__EXCLUDE_OPTION				10
#define NCURSES__GET_FRIENDS_OPTION			11
#define NCURSES__CHANGE_CATEGORY_OPTION			12
#define NCURSES__ADD_PARENT_RELATIONSHIP_OPTION		13
#define NCURSES__REMOVE_PARENT_RELATIONSHIP_OPTION	14
#define NCURSES__EDIT_PARENT_RELATIONSHIP_OPTION	15
#define NCURSES__GET_USERS_OPTION			16
#define NCURSES__MOUNT_OPTION				17
#define NCURSES__PASSWORD_OPTION			18
#define NCURSES__CHANGE_PASSWORD_OPTION			19
#define NCURSES__UPLOAD_OPTION				20
#define NCURSES__EXIT_OPTION				21
#define MIN_NB_LINES					32
#define MIN_NB_COLS					70
#define NB_MENU_LINES					25
#define NB_MENU_COLS					69
#define FIELD_HEIGHT					1
#define MAX_FIELD_WIDTH					75
#define FIELD_START_Y					4
#define FIELD_START_X					30
#define MAX_LENGTH_PENDING_FAMILIES			1000

#endif

// $RCSfile: const.h,v $
