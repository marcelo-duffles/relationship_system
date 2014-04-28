//===========================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Author: Marcelo Duffles Donato Moreira
// Description: Secundary functions header file 
// Date: 22/10/2004
//===========================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: functions.h,v $
 * Revision 1.16  2005/02/16 22:11:21  marceloddm
 * CGI's added
 *
 * Revision 1.15  2004/12/21 16:59:18  marceloddm
 * autenticateUser() function added
 *
 * Revision 1.14  2004/12/20 23:51:10  marceloddm
 * New functions added: verifyIfcookieFileExist(), getCookieValue() and createNewCookieFile()
 *
 * Revision 1.13  2004/12/20 12:47:20  marceloddm
 * Functions added: insertFIFO(), retrieveFIFO(), freeFIFOResources()
 *
 * Revision 1.12  2004/12/18 02:01:37  marceloddm
 * stringCopy() function added
 *
 * Revision 1.11  2004/12/15 20:30:53  marceloddm
 * backupSystemFiles() function is OK!
 *
 * Revision 1.8  2004/12/15 01:30:47  marceloddm
 * Functions added: copyDataToUserData() and fillUserData()
 * checkUserData() function have been modified
 *
 * Revision 1.7  2004/12/14 02:46:52  marceloddm
 * More functions have been added. The most importants are checkUserData(), backupSystemFiles() and getUserData() functions
 *
 * Revision 1.6  2004/12/13 16:03:15  marceloddm
 * Updated with checkUserData() and putUserData() functions
 *
 * Revision 1.5  2004/12/13 07:51:03  marceloddm
 * New functions have been added (see log of functions.c of this date)
 *
 * Revision 1.4  2004/12/11 12:34:19  marceloddm
 * Author changed for 'marceloddm'
 *
 * Revision 1.3  2004/11/30 00:27:48  root
 * Last modification: shorHelp() function
 *
 * Revision 1.2  2004/11/26 13:41:38  root
 * RCS's strings added
 *
 */ 
 

#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_ "@(#)functions.h $Revision: 1.16 $"

#include <menu.h>
#include <form.h>
#include <time.h>
#include "types.h" 


/*---------------------------------------------------------------------------------------------------------*/
char *stringCopy (char *destination, char *source, unsigned sizeOfDestination);
/* 	
INPUT ARGUMENTS
	- char *source
	- unsigned sizeOfDestination
	
OUTPUT ARGUMENTS
	- char *destination
 
DESCRIPTION
	The stringCopy() function solves a bug of strncpy() function. This function is similar to strlcpy().
	This function copy a EOS terminated string 'source' into a sized 'destination'
	The result is always a valid EOS-terminated string that fits in the 'destination' (unless, of course, the 'destination' size is zero).
	This function doesn't test if 'destination' or 'source' strings are NULL.
	
RETURNED VALUES
	The stringCopy() function returns:
	  - the sized 'destination'. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned createRandomString (char *validCharacters, unsigned length, char *randomString);
/* 	
INPUT ARGUMENTS
	- char *validCharacters
	- unsigned length 
	
OUTPUT ARGUMENTS
	- char *randomString
 
DESCRIPTION
	The createRandomString() function creates a random string using characters provided by the 'validCharacters' string. The length of the generated random string is determined by the 'length' input argument.
	
RETURNED VALUES
	The createRandomString() function returns:
	  - CREATE_RANDOM_STRING__INVALID_STRING if 'randomString' is a invalid string;
	  - CREATE_RANDOM_STRING__NO_VALID_CHARACTERS if no valid characters have been found;
	  - OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/
   
/*---------------------------------------------------------------------------------------------------------*/
unsigned encodePassword (char *plainPass, char *encryptedPass);
/* 	
INPUT ARGUMENTS
	- char *plainPass 
	
OUTPUT ARGUMENTS
	- char *encryptedPass
 
DESCRIPTION
	The encodePassword() function encodes the 'plainPass' input argument with a random salt (created with the createRandomString() function) using the MD5 algorithm.
	
RETURNED VALUES
	The encodePassword() function returns:
	  - ENCODE_PASSWORD__INVALID_ENCRYPTED_PASS if the encrypted password is invalid;
	  - ENCODE_PASSWORD__INVALID_PLAIN_PASS if the plain password is invalid;
	  - An error code of createRandomString() function if an error occurs while generating a random salt;
	  - OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned checkPassword (char *encryptedPass, char *plainPass);
/* 	
INPUT ARGUMENTS
	- char *encryptedPass 
	- char *plainPass
	
DESCRIPTION
	The checkPassword() function encodes the 'plainPass' input argument and then compares the encoded plain password with 'encryptedPass', returning OK in case of equality.   
	
RETURNED VALUES
	The checkPassword() function returns:
	  - CHECK_PASSWORD__INVALID_PLAIN_PASS if the plain password is invalid;
	  - CHECK_PASSWORD__INVALID_ENCRYPTED_PASS if the encrypted password is invalid;
	  - CHECK_PASSWORD__WRONG_PLAIN_PASS if the plain password is wrong;
	  - OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned getLongFilename (char *path, char *filename, char *longFilename);
/* 	
INPUT ARGUMENTS
	- char *path
	- char *filename
	
OUTPUT ARGUMENTS
	- char *longFilename
 
DESCRIPTION
	The getLongFilename() function appends the 'filename' string to 'path' and returns the 'longFilename' string.   
	
RETURNED VALUES
	The getLongFilename() function returns:
	  - GET_LONG_FILENAME__INVALID_PATH if the 'path' is invalid;
	  - GET_LONG_FILENAME__INVALID_FILENAME if the 'filename' is invalid;
	  - GET_LONG_FILENAME__NO_LONG_FILENAME if the char pointer 'longFilename' points nothing;
	  - GET_LONG_FILENAME__INVALID_LONG_FILENAME if the 'longFilename' is invalid;
	  - OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned getUserId (FILE *file, userIdType *userId);
/* 	
INPUT ARGUMENTS
	- FILE *file
	
OUTPUT ARGUMENTS
	- userIdType *userId
 
DESCRIPTION
	The getUserId() function reads the next 'userId' from 'file'.   
	
RETURNED VALUES
	The getUserId() function returns:
	  - GET_USER_ID__INVALID_FILE if the 'file' is invalid;
	  - GET_USER_ID__INVALID_USER_ID if the 'userId' is invalid;
	  - GET_USER_ID__ERROR_READING_FILE if occurs an error while reading 'file';
	  - GET_USER_ID__END_OF_FILE if the end of 'file' is reached;
	  - OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned putUserId (FILE *file, userIdType *userId);
/* 	
INPUT ARGUMENTS
	- FILE *file
	- userIdType *userId
 
DESCRIPTION
	The putUserId() function writes the 'userId' in 'file'.   
	
RETURNED VALUES
	The putUserId() function returns:
	  - PUT_USER_ID__INVALID_FILE if the 'file' is invalid;
	  - PUT_USER_ID__INVALID_USER_ID if the 'userId' is invalid;
	  - PUT_USER_ID__ERROR_WRITING_FILE if occurs an error while writing in 'file';
	  - PUT_USER_ID__END_OF_FILE if the end of 'file' is reached;
	  - OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned putUserCategory (FILE *file, userCategoryType *userCategory);
/* 	
INPUT ARGUMENTS
	- FILE *file
	- userCategoryType *userCategory
 
DESCRIPTION
	The putUserCategory() function writes the 'userCategory' in 'file'.   
	
RETURNED VALUES
	The putUserCategory() function returns:
	  - PUT_USER_CATEGORY__INVALID_FILE if the 'file' is invalid;
	  - PUT_USER_CATEGORY__INVALID_USER_CATEGORY if the 'userCategory' is invalid;
	  - PUT_USER_CATEGORY__ERROR_WRITING_FILE if occurs an error while writing in 'file';
	  - PUT_USER_CATEGORY__END_OF_FILE if the end of 'file' is reached;
	  - OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned getUserCategory (FILE *file, userCategoryType *userCategory);
/* 	
INPUT ARGUMENTS
	- FILE *file

OUTPUT ARGUMENTS
	- userCategoryType *userCategory
 
DESCRIPTION
	The getUserCategory() function reads the next 'userCategory' from 'file'.   
	
RETURNED VALUES
	The getUserCategory() function returns:
	  - GET_USER_CATEGORY__INVALID_FILE if the 'file' is invalid;
	  - GET_USER_CATEGORY__INVALID_USER_CATEGORY if the 'userCategory' is invalid;
	  - GET_USER_CATEGORY__ERROR_READING_FILE if occurs an error while reading 'file';
	  - GET_USER_CATEGORY__END_OF_FILE if the end of 'file' is reached;
	  - OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned putUserGender (FILE *file, genderType *userGender);
/* 	
INPUT ARGUMENTS
	- FILE *file
	- genderType *userGender
 
DESCRIPTION
	The putUserGender() function writes the 'userGender' in 'file'.   
	
RETURNED VALUES
	The putUserGender() function returns:
	  - PUT_USER_GENDER__INVALID_FILE if the 'file' is invalid;
	  - PUT_USER_GENDER__INVALID_USER_GENDER if the 'userGender' is invalid;
	  - PUT_USER_GENDER__ERROR_WRITING_FILE if occurs an error while writing in 'file';
	  - PUT_USER_GENDER__END_OF_FILE if the end of 'file' is reached;
	  - OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned getUserGender (FILE *file, genderType *userGender);
/* 	
INPUT ARGUMENTS
	- FILE *file

OUTPUT ARGUMENTS
	- genderType *userGender
 
DESCRIPTION
	The getUserGender() function reads the next 'userGender' from 'file'.   
	
RETURNED VALUES
	The getUserGender() function returns:
	  - GET_USER_GENDER__INVALID_FILE if the 'file' is invalid;
	  - GET_USER_GENDER__INVALID_USER_GENDER if the 'userGender' is invalid;
	  - GET_USER_GENDER__ERROR_READING_FILE if occurs an error while reading 'file';
	  - GET_USER_GENDER__END_OF_FILE if the end of 'file' is reached;
	  - OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned putUserRelationshipStatus (FILE *file, relationshipStatusType *userRelationshipStatus);
/* 	
INPUT ARGUMENTS
	- FILE *file
	- relationshipStatusType *userRelationshipStatus
 
DESCRIPTION
	The putUserRelationshipStatus() function writes the 'userRelationshipStatus' in 'file'.   
	
RETURNED VALUES
	The putUserRelationshipStatus() function returns:
	  - PUT_USER_RELATIONSHIP_STATUS__INVALID_FILE if the 'file' is invalid;
	  - PUT_USER_RELATIONSHIP_STATUS__INVALID_USER_RELATIONSHIP_STATUS if the 'userRelationshipStatus' is invalid;
	  - PUT_USER_RELATIONSHIP_STATUS__ERROR_WRITING_FILE if occurs an error while writing in 'file';
	  - PUT_USER_RELATIONSHIP_STATUS__END_OF_FILE if the end of 'file' is reached;
	  - OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned getUserRelationshipStatus (FILE *file, relationshipStatusType *userRelationshipStatus);
/* 	
INPUT ARGUMENTS
	- FILE *file

OUTPUT ARGUMENTS
	- relationshipStatusType *userRelationshipStatus
 
DESCRIPTION
	The getUserRelationshipStatus() function reads the next 'userRelationshipStatus' from 'file'.   
	
RETURNED VALUES
	The getUserRelationshipStatus() function returns:
	  - GET_USER_RELATIONSHIP_STATUS__INVALID_FILE if the 'file' is invalid;
	  - GET_USER_RELATIONSHIP_STATUS__INVALID_USER_RELATIONSHIP_STATUS if the 'userRelationshipStatus' is invalid;
	  - GET_USER_RELATIONSHIP_STATUS__ERROR_READING_FILE if occurs an error while reading 'file';
	  - GET_USER_RELATIONSHIP_STATUS__END_OF_FILE if the end of 'file' is reached;
	  - OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned getString (FILE *file, unsigned minLength, unsigned maxLength, char *string);
/* 	
INPUT ARGUMENTS
	- FILE *file
	- unsigned minLength
	- unsigned maxLength
	
OUTPUT ARGUMENTS
	- char *string
 
DESCRIPTION
	The getString() function reads the next string from a binary file. The length must be between 'minLength' and 'maxLength'.   
	
RETURNED VALUES
	The getString() function returns:
	  - GET_STRING__INVALID_FILE if the 'file' is invalid;
	  - GET_STRING__INVALID_STRING if the 'string' is invalid;
	  - GET_STRING__ERROR_READING_FILE if occurs an error while reading 'file';
	  - GET_STRING__END_OF_FILE if the end of 'file' is reached;
	  - GET_STRING__SMALL_STRING if the 'string' is smaller than the size permitted;
	  - GET_STRING__BIG_STRING if the 'string' is bigger than the size permitted;
	  - OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned putString (FILE *file, unsigned minLength, unsigned maxLength, char *string);
/* 	
INPUT ARGUMENTS
	- FILE *file
	- unsigned minLength
	- unsigned maxLength
	- char *string
 
DESCRIPTION
	The putString() function writes the 'string' in 'file'. The length must be between 'minLength' and 'maxLength'.   
	
RETURNED VALUES
	The putString() function returns:
	  - PUT_STRING__INVALID_FILE if the 'file' is invalid;
	  - PUT_STRING__INVALID_STRING if the 'string' is invalid;
	  - PUT_STRING__ERROR_WRITING_FILE if occurs an error while writing in 'file';
	  - PUT_STRING__END_OF_FILE if the end of 'file' is reached;
	  - PUT_STRING__SMALL_STRING if the 'string' is smaller than the size permitted;
	  - PUT_STRING__BIG_STRING if the 'string' is bigger than the size permitted;
	  - OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned checkField (char *field, char *validCharacters, unsigned minLength, unsigned maxLength);
/* 	
INPUT ARGUMENTS
	- char *field
	- char *validCharacters
	- unsigned minLength
	- unsigned maxLength
	
DESCRIPTION
	The checkField() function checks if the input 'field' has valid characters (given by the 'validCharacters' string) and if its length is between 'minLength' and 'maxLength'.   
	
RETURNED VALUES
	The checkField() function returns:
	  - CHECK_FIELD__INVALID_FIELD if the 'field' is invalid;
	  - CHECK_FIELD__NO_VALID_CHARACTERS if there are no valid characters in 'validCharacters';
	  - CHECK_FIELD__SMALL_FIELD if the 'field' is smaller than the size permitted;
	  - CHECK_STRING__BIG_FIELD if the 'field' is bigger than the size permitted;
	  - CHECK_FIELD__FIELD_HAS_NO_VALID_CHARACTERS if the 'field' has not valid characters;
	  - OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
void shortHelp (void);
/* 	
DESCRIPTION
	The shortHelp() function shows a short help message.   
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned getAdministratorPassword (char *password);
/* 	
OUTPUT ARGUMENTS
	- char *password
	
DESCRIPTION
	The getAdministratorPassword() function checks if the user is the administrator. In this case, it gets the administrator's password.   
	
RETURNED VALUES
	The getAdministratorPassword() function returns:
	  - GET_ADMINISTRATOR_PASSWORD__INVALID_PASSWORD if the 'password' is invalid;
	  - GET_ADMINISTRATOR_PASSWORD__DO_NOT_IS_THE_ADMINISTRATOR if the user is not the administrator;
	  - GET_ADMINISTRATOR_PASSWORD__LOGIN_INCORRECT if the login is incorrect;
	  - OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned checkUserData (userDataType *userData);
/* 	
INPUT ARGUMENTS
	- userDataType *userData
	
DESCRIPTION
	The checkUserData() function checks if the fields of 'userData' are valid.   
	
RETURNED VALUES
	The checkUserData() function returns:
	  - CHECK_USER_DATA__INVALID_USER_DATA if the 'userData' is invalid;
	  - An error code of checkField() function if an error occurs while checking some field;
	  - A detailed error code of checkField() function if a detailed error occurs while checking some field;
	  - OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned putUserData (FILE *file, char *filename, userDataType *userData);
/* 	
INPUT ARGUMENTS
	- FILE *file
	- char *filename
	- userDataType *userData
	
DESCRIPTION
	The putUserData() function puts the correct fields of 'userData' in 'file'. The file must be alredy opened.
	The second input argument 'filename' must be "password" or "users" and the 'file' must correspond to the respective 'filename'.   
	
RETURNED VALUES
	The putUserData() function returns:
	  - PUT_USER_DATA__INVALID_FILE if the 'file' is invalid;
	  - PUT_USER_DATA__NO_FILENAME if no filename has been given;
	  - PUT_USER_DATA__INVALID_USER_DATA if the 'userData' is invalid;
	  - PUT_USER_DATA__INVALID_FILENAME if the 'filename' is invalid;
	  - An error code of getLongFilename() function if an error occurs while getting long filename;
	  - An error code of putUserId() function if an error occurs while putting user ID in file;
	  - An error code of putString() function if an error occurs while putting string in file;
	  - An error code of putUserCategory() function if an error occurs while putting user category in file;
	  - An error code of putUserGender() function if an error occurs while putting user gender in file;
	  - An error code of putUserRelationshipStatus() function if an error occurs while putting user relationsip status in file;
	  - OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned getUserData (FILE *file, char *filename, userDataType *userData);
/* 	
INPUT ARGUMENTS
	- FILE *file
	- char *filename
	
OUTPUT ARGUMENTS
	- userDataType *userData
	
DESCRIPTION
	The getUserData() function the get the correct fields of 'userData' from 'file'. The file must be alredy opened.
	The second input argument 'filename' must be "password" or "users" and the 'file' must correspond to the respective 'filename'.   
	
RETURNED VALUES
	The getUserData() function returns:
	  - GET_USER_DATA__INVALID_FILE if the 'file' is invalid;
	  - GET_USER_DATA__NO_FILENAME if no filename have been given;
	  - GET_USER_DATA__INVALID_USER_DATA if the 'userData' is invalid;
	  - GET_USER_DATA__INVALID_FILENAME if the 'filename' is invalid;
	  - An error code of getLongFilename() function if an error occurs while getting long filename;
	  - An error code of getUserId() function if an error occurs while getting user ID from file;
	  - An error code of getString() function if an error occurs while getting string from file;
	  - An error code of getUserCategory() function if an error occurs while getting user category from file;
	  - An error code of getUserGender() function if an error occurs while getting user gender from file;
	  - An error code of getUserRelationshipStatus() function if an error occurs while getting user relationsip status from file;
	  - OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned backupSystemFiles (void);
/* 	
DESCRIPTION
	The backupSystemFiles() function makes the backup of the system files.   
	
RETURNED VALUES
	The backupSystemFiles() function returns:
	  - BACKUP_SYSTEM_FILES__ERROR_OPENING_PASSWORD_FILE_FOR_READING if an error occurs while opening the password file for reading;
	  - BACKUP_SYSTEM_FILES__ERROR_OPENING_USERS_FILE_FOR_READING if an error occurs while opening the users file for reading;
	  - BACKUP_SYSTEM_FILES__ERROR_OPENING_FRIENDS_FILE_FOR_READING if an error occurs while opening the friends file for reading;
	  - BACKUP_SYSTEM_FILES__ERROR_OPENING_PARENTS_FILE_FOR_READING if an error occurs while opening the parents file for reading;
	  - BACKUP_SYSTEM_FILES__NOT_YET_INSTALLED if the system is not yet installed;
	  - An error code of getLongFilename() function if an error occurs while getting a long filename;
	  - OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned fillUserData (userDataType *userData, char **argv, char *plainPass);
/* 	
INPUT ARGUMENTS
	- char **argv
	- char *plainPass
	
OUTPUT ARGUMENTS	
	- userDataType *userData 
	
DESCRIPTION
	The fillUserData() function fills the 'userData' variable with the fields given by 'argv' and 'plainPass'. It also completes the missing fields and let in blank in case of desnecessary field.
	The order of arguments in 'argv' is important.
	The functions knows (by argv[1]) what option is going to be processed (install, add or edit).
	In 'edit' option, the input argument 'plainPass' is desnecessary and can be filled with NULL. In any way, it will be ignored when this option is selected.
	
NOTES
	- In "edit" case, 'userName', 'plainPass', 'encryptedPass', 'category' and 'next' are not filled;
	- In "add"  case, we will know the user ID only when putting data in file;
	- In "install" case, all fields are filled.
	
RETURNED VALUES
	The fillUserData() function returns:
	  - FILL_USER_DATA__NO_USER_DATA if no 'userData' have been given;
	  - FILL_USER_DATA__NO_ARGV if no 'argv' have been given;
	  - FILL_USER_DATA__NO_PLAIN_PASS if no 'plainPass' have been given in 'add' or 'install' options;
	  - FILL_USER_DATA__WRONG_CATEGORY if a wrong category have been given in 'edit' option;
	  - An error code of encodePassword() function if an error occurs while encoding the 'plainPass';
	  - OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned copyUserData (userDataType * userDataOut, userDataType * userDataIn);
/* 	
INPUT ARGUMENTS
	- userDataType *userDataIn 
	
OUTPUT ARGUMENTS	
	- userDataType *userDataOut
	
DESCRIPTION
	The copyUserData() function makes an exact copy of the userDataIn struct.
	
RETURNED VALUES
	The copyUserData() function returns:
	  - COPY_USER_DATA__DATA_IN_INVAL if no 'userDataIn' has been given;
	  - COPY_USER_DATA__DATA_OUT_INVAL if no 'userDataOut' has been given;
	  - OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned getDataFromId (userIdType id, userDataType * userData);
/* 	
INPUT ARGUMENTS
	- id
	
OUTPUT ARGUMENTS	
	- userDataType *userData 
	
DESCRIPTION
	The getDataFromId() function takes all data from the user owner of the given Id and puts it in the userData output argument.
	
RETURNED VALUES
	The getDataFromId() function returns:
	  - GET_DATA_FROM_ID__USER_DATA_INVAL if no 'userData' has been given;
	  - GET_DATA_FROM_ID__ERROR_OPENING_USERS_FILE_FOR_READING if an error occurs while opening the users file;
	  - GET_DATA_FROM_ID__USERS_FILE_DOES_NOT_EXIST if the users file DOES NOT exist;
	  - GET_DATA_FROM_ID__ERROR_OPENING_PASSWORD_FILE_FOR_READING if an error occurs while opening the password file;
	  - GET_DATA_FROM_ID__PASSWORD_FILE_DOES_NOT_EXIST if the password file DOES NOT exist;
	  - GET_DATA_FROM_ID__USER_NOT_FOUND if there was no user with the given id.
	  - An error code of copyUserData() function if an error occurs while copying user data;
	  - An error code of getLongFilename() function if an error occurs getting a long filename;
	  - An error code of getUserData() function if an error occurs getting user data;
	  - OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned getDataFromUsername (char *username, userDataType * userData);
/* 	
INPUT ARGUMENTS
	- char *username
	
OUTPUT ARGUMENTS	
	- userDataType *userData 
	
DESCRIPTION
	The getDataFromUsername() function takes all data from the user owner of the given 'username' and puts it in the userData output argument.
	
RETURNED VALUES
	The getDataFromUsername() function returns:
	  - GET_DATA_FROM_USERNAME__NO_USERNAME if no 'username' has been given;
	  - GET_DATA_FROM_USERNAME__NO_USER_DATA if no 'userData' has been given;
	  - GET_DATA_FROM_USERNAME__ERROR_OPENING_USERS_FILE_FOR_READING if an error occurs while opening the users file;
	  - GET_DATA_FROM_USERNAME__USERS_FILE_DOES_NOT_EXIST if the users file DOES NOT exist;
	  - GET_DATA_FROM_USERNAME__ERROR_OPENING_PASSWORD_FILE_FOR_READING if an error occurs while opening the password file;
	  - GET_DATA_FROM_USERNAME__PASSWORD_FILE_DOES_NOT_EXIST if the password file DOES NOT exist;
	  - GET_DATA_FROM_USERNAME__USER_NOT_FOUND if there was no user with the given 'username'.
	  - An error code of copyUserData() function if an error occurs while copying user data;
	  - An error code of getLongFilename() function if an error occurs getting a long filename;
	  - An error code of getUserData() function if an error occurs getting user data;
	  - OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned insertFIFO ( userDataType ** first, userDataType ** last, userDataType * newElementData );
/* 	
INPUT ARGUMENTS
	- userDataType ** first 
	- userDataType ** last
	- userDataType * newElementData 
	
OUTPUT ARGUMENTS	
	- userDataType ** first
	- userDataType ** last
	
DESCRIPTION
	The insertFIFO() function takes newElementData and inserts it into a FIFO.
	
NOTE
	- The values of first and last are properly updated.
	
RETURNED VALUES
	The insertFIFO() function returns:
	  - INSERT_FIFO__INVALID_NEW_ELEMENT if no 'newElementData' has been given;
	  - INSERT_FIFO__ERROR_ALLOCATING_MEMMORY if an error occurs while trying to allocate memmory;
	  - An error code of copyUserData() function if an error occurs while copying user data;
	  - OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned retrieveFIFO ( userDataType ** first, userDataType ** last, userDataType * elementData );
/* 	
INPUT ARGUMENTS
	- userDataType ** first 
	- userDataType ** last
	
OUTPUT ARGUMENTS	
	- userDataType *elementData 
	- userDataType ** first
	- userDataType ** last
	
DESCRIPTION
	The retrieveFIFO() function takes the first element of a FIFO and puts it in elementData.
	
NOTE
	-The values of first and last are properly updated.

RETURNED VALUES
	The retrieveFIFO() function returns:
	  - RETRIEVE_FIFO__INVALID_ELEMENT_DATA if no 'elementData' has been given;
	  - RETRIEVE_FIFO__EMPTY_FIFO if the FIFO is empty;
	  - An error code of copyUserData() function if an error occurs while copying user data;
	  - OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
void freeFIFOResources ( userDataType ** first , userDataType ** last );
/* 	
INPUT ARGUMENTS
	- userDataType ** first 
	- userDataType ** last
	
DESCRIPTION
	The freeFIFOResources() function frees all the allocated memmory used in the FIFO that uses the `first` and `last` userDataType pointers. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
void insertInFamilyList (familyTreeType **newFamily, familyTreeType **first);
/* 	
OUTPUT ARGUMENTS	
	- familyTreeType **newFamily
	- familyTreeType **first
	
DESCRIPTION
	The insertInFamilyList() function takes 'newFamily' and inserts it into the family list.
	
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
familyTreeType *retrieveFamily (familyTreeType **first);
/* 	
OUTPUT ARGUMENTS	
	- familyTreeType *first 
	
DESCRIPTION
	The retrieveFamily() function returns the first element of the list of families.
	
NOTE
	-The values of first are properly updated.

RETURNED VALUES
	The retrieveFIFO() function returns:
	  - the correct family, in case of success;
	  - NULL, if the list is empty.
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned verifyIfCookieFileExist (char *username, char *id);
/* 	
INPUT ARGUMENTS
	- char *username
	
OUTPUT ARGUMENTS	
	- char *id   
	
DESCRIPTION
	The verifyIfcookieFileExist() function verifies if there's a cookie file that belongs to a user whose username is given by the input argument. This function also returns the name of this cookie (output argument 'id').
	
RETURNED VALUES
	The verifyIfcookieFileExist() function returns:
	  - VERIFY_IF_COOKIE_FILE_EXIST__ERROR_OPENING_PASSWORD_FILE_FOR_READING if an error occurs while opening password file for reading;
	  - VERIFY_IF_COOKIE_FILE_EXIST__PASSWORD_FILE_DOES_NOT_EXIST if the password file doesn't exist;
	  - VERIFY_IF_COOKIE_FILE_EXIST__USERNAME_NOT_FOUND the username hasn't been found;
	  - VERIFY_IF_COOKIE_FILE_EXIST__ERROR_OPENING_COOKIE_FILE_FOR_READING if an error occurs while opening cookie file for reading;
	  - VERIFY_IF_COOKIE_FILE_EXIST__COOKIE_FILE_DOES_NOT_EXIST if the cookie file doesn't exist;
	  - VERIFY_IF_COOKIE_FILE_EXIST__NO_USERNAME if no 'username' has been given;
	  - VERIFY_IF_COOKIE_FILE_EXIST__NO_ID if no 'id' has been given;
	  - An error code of getLongFilename() function if an error occurs while getting a long filename;
	  - An error code of getUserData() function if an error occurs while getting a user data;
	  - OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned getCookieValue (char *cookieName, char *cookieValue);
/* 	
INPUT ARGUMENTS
	- char *cookieName
	
OUTPUT ARGUMENTS	
	- char *cookieValue
	
DESCRIPTION
	The getCookieValue() function gets the cookie value from a cookie file whose name is 'cookieName'.
	
RETURNED VALUES
	The getCookieValue() function returns:
	  - GET_COOKIE_VALUE__NO_COOKIE_NAME if no 'cookieName' has been given;
	  - GET_COOKIE_VALUE__NO_COOKIE_VALUE if no 'cookieValue' has been given;
	  - GET_COOKIE_VALUE__ERROR_OPENING_COOKIE_FILE_FOR_READING if an error occurs while opening the cookie file for reading;
	  - GET_COOKIE_VALUE__COOKIE_FILE_DOES_NOT_EXIST if the cookie file doesn't exist;
	  - An error code of getLongFilename() function if an error occurs while getting a long filename;
	  - An error code of getString() function if an error occurs while getting string from file;
	  - OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned createNewCookieFile (char *cookieName, char *cookieValue, time_t cookieExpiration, char *ip);
/* 	
INPUT ARGUMENTS
	- char *cookieName	
	- char *cookieValue
	- time_t cookieExpiration
	- char *ip
	
DESCRIPTION
	The createNewCookieFile() creates a new cookie file whose name is 'cookieName'. The content of this file is the cookie value, the cookie expiration and the ip.
	
RETURNED VALUES
	The createNewCookieFile() function returns:
	  - CREATE_NEW_COOKIE_FILE__NO_COOKIE_NAME if no 'cookieName' has been given;
	  - CREATE_NEW_COOKIE_FILE__NO_COOKIE_VALUE if no 'cookieValue' has been given;
	  - CREATE_NEW_COOKIE_FILE if no 'ip' has been given.
	  - CREATE_NEW_COOKIE_FILE__ERROR_OPENING_COOKIE_FILE_FOR_WRITING if an error occurs while opening the cookie file for writing;
	  - CREATE_NEW_COOKIE_FILE__ERROR_WRITING_EXPIRATION_IN_COOKIE_FILE if an error occurs while writing the expiration in cookie file;
	  - CREATE_NEW_COOKIE_FILE__END_OF_COOKIE_FILE if the end of cookie file is reached;
	  - An error code of getLongFilename() function if an error occurs while getting a long filename;
	  - An error code of putString() function if an error occurs while putting string in cookie file;
	  - OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned validateCookie (char *cookieName, char *cookieValue, char *ip);
/* 	
INPUT ARGUMENTS
	- char *cookieName
	- char *cookieValue
	- char *ip
	
DESCRIPTION
	The validateCookie() function checks if there's a cookie file with name 'cookieName', if the input 'cookieValue' and 'ip' are correct and if the cookie has expired.
	
RETURNED VALUES
	The validateCookie() function returns:
	  - VALIDATE_COOKIE__NO_COOKIE_NAME if no 'cookieName' has been given;
	  - VALIDATE_COOKIE__NO_COOKIE_VALUE if no 'cookieValue' has been given;
	  - VALIDATE_COOKIE__NO_IP if no 'ip' has been given;
	  - VALIDATE_COOKIE__ERROR_OPENING_COOKIE_FILE_FOR_READING if an error occurs while opening the cookie file for reading;
	  - VALIDATE_COOKIE__COOKIE_FILE_DOES_NOT_EXIST if the cookie file doesn't exist;
	  - VALIDATE_COOKIE__WRONG_COOKIE_VALUE if the 'cookieValue' is wrong;
	  - VALIDATE_COOKIE__ERROR_READING_EXPIRATION_IN_COOKIE_FILE if an error occurs while reading expiration in cookie file;
	  - VALIDATE_COOKIE__END_OF_COOKIE_FILE if the end of cookie file is reached;
	  - VALIDATE_COOKIE__COOKIE_HAS_EXPIRED if the cookie has expired;
	  - VALIDATE_COOKIE__WRONG_IP if the 'ip' is wrong;
	  - An error code of getLongFilename() function if an error occurs while getting a long filename;
	  - An error code of getString() function if an error occurs while getting string from file;
	  - OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned autenticateUser (char *username, char *plainPass);
/* 	
INPUT ARGUMENTS
	- char *username
	- char *plainPass
	
DESCRIPTION
	The autenticateUser() function tells us if the username exist and, if its is true, if the plainPass is correct.   
	
RETURNED VALUES
	The autenticateUser() function returns:
	  - AUTENTICATE_USER__NO_USERNAME if no 'username' has been given;
	  - AUTENTICATE_USER__NO_PLAIN_PASS if no 'plainPass' has been given;
	  - AUTENTICATE_USER__ERROR_OPENING_PASSWORD_FILE_FOR_READING if an error occurs while opening the password file for reading;
	  - AUTENTICATE_USER__PASSWORD_FILE_DOES_NOT_EXIST if the password file doesn't exist;
	  - AUTENTICATE_USER__USERNAME_NOT_FOUND if the 'username' hasn't been found;
	  - An error code of getLongFilename() function if an error occurs while getting a long filename;
	  - An error code of getUserData() function if an error occurs while getting a user data;
	  - An error code of checkPassword() function if an error occurs while checking if the 'plainPass' is correct;
	  - OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
void printInMiddle (WINDOW *win, int starty, int startx, int width, char *title, chtype color);
/* 	
INPUT ARGUMENTS
	- WINDOW *win
	- int starty
	- int startx
	- char *title
	- chtype color
	
DESCRIPTION
	The printTitleInMiddle() function prints the 'title' in the middle of the window pointed by 'win'.   
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned freeMenuItemsResources (ITEM **menuItems);
/* 	
INPUT ARGUMENTS
	- ITEM **menuItems
	
DESCRIPTION
	The freeMenuItemsResources() function frees the memory allocated to menu items.  

NOTE
    This function doesn't check is the input argument is NULL.
	
RETURNED VALUES
	The freeMenuItemsResources() function returns:
	  - NCURSES__ERROR_FREEING_MEMORY_ALLOCATED_TO_MENU_ITEMS if an error occurs while freeing the memory allocated to menu items;
	  - OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned freeFormFieldsResources (FIELD **formFields);
/* 	
INPUT ARGUMENTS
	- FIELD **formFields
	
DESCRIPTION
	The freeFormFieldsResources() function frees the memory allocated to form fields.  

NOTE
    This function doesn't check is the input argument is NULL.
	
RETURNED VALUES
	The freeFormFieldsResources() function returns:
	  - NCURSES__ERROR_FREEING_MEMORY_ALLOCATED_TO_FORM_FIELDS if an error occurs while freeing the memory allocated to form fields;
	  - OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned freeMenuResources (MENU *menu, ITEM **menuItems);
/* 	
INPUT ARGUMENTS
	- MENU *menu
	- ITEM **menuItems
	
DESCRIPTION
	The freeMenuResources() function frees the memory allocated to menu and menu items.  

NOTE
    This function doesn't check is the input arguments are NULL.
	
RETURNED VALUES
	The freeMenuResources() function returns:
	  - NCURSES__ERROR_FREEING_MEMORY_ALLOCATED_TO_MENU if an error occurs while freeing the memory allocated to menu;
	  - NCURSES__ERROR_FREEING_MEMORY_ALLOCATED_TO_MENU_ITEMS if an error occurs while freeing the memory allocated to menu items;
	  - OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned freeFormResources (FORM *form, FIELD **formFields);
/* 	
INPUT ARGUMENTS
	- FORM *form
	- FIELD **formFields
	
DESCRIPTION
	The freeFormResources() function frees the memory allocated to form and form fields.  

NOTE
    This function doesn't check is the input arguments are NULL.
	
RETURNED VALUES
	The freeFormResources() function returns:
	  - NCURSES__ERROR_FREEING_MEMORY_ALLOCATED_TO_FORM if an error occurs while freeing the memory allocated to form;
	  - NCURSES__ERROR_FREEING_MEMORY_ALLOCATED_TO_FORM_FIELDS if an error occurs while freeing the memory allocated to form fields;
	  - OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
FIELD **createFormFields (char option);
/* 	
INPUT ARGUMENT
	- char option
	
DESCRIPTION
	The createFormFields() function creates the fields of a form according to the given 'option'.  
	
RETURNED VALUES
	The createFormFields() function returns:
	  - NULL, in case of error;
	  - a vector of fields, in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
void showDescriptionsOfFields (char option);
/* 	
INPUT ARGUMENT
	- char option
	
DESCRIPTION
	The showDescriptionsOfFields() function shows the descriptions of the fields according to the given 'option'.  
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
char *repairString (char *string);
/* 	
INPUT ARGUMENT
	- char *string
	
DESCRIPTION
	The repairString() function repairs a string provided from a form field's buffer.  
	
RETURNED VALUES
	The repairString() function returns:
	  - NULL, in case of error;
	  - a repaired string, in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned repairFormData (userDataType *userData, FIELD **formFields, char option);
/* 	
INPUT ARGUMENTS
	- FIELD **formFields
	- char option

OUTPUT ARGUMENTS
	- userDataType *userData
	
DESCRIPTION
	The repairFormData() function repairs the fields of the given form and put them in 'userData', according to the given 'option'. This function also fills others fields of 'userData'.
	
RETURNED VALUES
	The repairFormData() function returns:
	  - REPAIR_FORM_DATA__NO_USER_DATA if no 'userData' has been given;
	  - REPAIR_FORM_DATA__NO_FORM_FIELDS if no 'formFields' has been given;
	  - REPAIR_FORM_DATA__UNKNOWN_OPTION if an unknown 'option' has been given;
	  - An error code of encodePassword() function if an error occurs while encoding a password;
	  - OK in case of success. 
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned setInitialValuesOfFields (FORM *form, userDataType *userData, char option);
/* 	
INPUT ARGUMENT
	- FORM *form
	- userDataType *userData
	- char option
	
DESCRIPTION
	The setInitialValuesOfFields() function sets the initial values of fields of the given form, according to the given option.

RETURNED VALUES  
	The setInitialValuesOfFields() function returns:
	  - An error code of getDataFromId() function if an error occurs while getting an user data;
	  - OK in casa of success.
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
void showAdministratorMenu (char *cookieName);
/* 	
INPUT ARGUMENT
	- char *cookieName
	
DESCRIPTION
	The showAdministratorMenu() function shows the html code of the administrator's menu.

*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
void showWebUserMenu (char *cookieName);
/* 	
INPUT ARGUMENT
	- char *cookieName
	
DESCRIPTION
	The showWebUserMenu() function shows the html code of the WEB USER's menu.

*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
void showHtmlOKPage (void);
/* 	
	
DESCRIPTION
	The showHtmlOKPage() function shows the html code of the confirmation (of the operation that has been done) page..

*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
void showHtmlInitialPage (char *cookieName);
/* 	
INPUT ARGUMENT
	- char *cookieName
			
DESCRIPTION
	The showHtmlInitialPage() function shows the html code of the initial page of the system. The input argument 'cookieName' tell us if the user who is logging in is the administrator or is a web user.

*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
void showHtmlWelcomePage (userDataType *userData);
/* 	
INPUT ARGUMENT
	- userDataType *userData
		
DESCRIPTION
	The showHtmlWelcomePage() function shows the html code of the welcome page of the system. This functions uses the input argument 'userData' to show also the user's data.

*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
void checkIfPairExist (userIdType sonId, userIdType parentId, boolean *sonExist, boolean *parentExist, boolean *pairAlreadyInserted, familyTreeType *first);
/* 	
INPUT ARGUMENTS
	- userIdType sonId
	- userIdType parentId
	- familyTreeType *first
	
OUTPUT ARGUMENTS
	- boolean *sonExist
	- boolean *parentExist
	- boolean *pairAlreadyInserted
	
DESCRIPTION
	The checkIfPairExist() function checks if the given ID's exist and if the given pair of ID's are already inserted in the list of families.

*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
familyTreeType *getFamilyFromId (userIdType id, familyTreeType *first);
/* 	
INPUT ARGUMENTS
	- userIdType id
	- familyTreeType first
	
DESCRIPTION
	The getFamilyFromId() function gets the family of user whose ID is 'id' in the list of families.
	
RETURNED VALUES
	  - the user family in case of success;
	  - NULL if the family doesn't exist.

*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
void insertSon (familyTreeType **newSon, familyTreeType **parent);
/* 	
OUTPUT ARGUMENTS
	- familyTreeType **newSon
	- familyTreeType **parent
	
DESCRIPTION
	The insertSon() function inserts the given 'newSon' in parent family.

*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned getUserParents (userIdType userId, familyTreeType **user, familyTreeType *first);
/* 	
INPUT ARGUMENT
	- userIdType userId
	- familyTreeType *first
	
OUTPUT ARGUMENT
	- familyTreeType **user
	
DESCRIPTION
	The getUserParents() function returns the parents of the user who has the given 'userId'.
	
RETURNED VALUES
	The getUserParents() function returns:
	  - GET_USER_FAMILY__ERROR_OPENING_PARENTS_FILE_FOR_READING if an error occurs while opening parents file for reading;
	  - GET_USER_FAMILY__PARENTS_FILE_DOES_NOT_EXIST if the parents file doesn't exist;
	  - GET_USER_FAMILY__MEMORY_ALLOCATION_ERROR if an error occurs while allocating memory;
	  - An error code of getLongFilename() function if an error occurs while getting a long filename;
	  - An error code of getUserId() function if an error occurs while getting an user ID;
	  - OK in case of success.
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned getUserSonsAndDaughters (userIdType userId, familyTreeType **user, familyTreeType *first);
/* 	
INPUT ARGUMENT
	- userIdType userId
	- familyTreeType *first
	
OUTPUT ARGUMENT
	- familyTreeType **user
	
DESCRIPTION
	The getUserSonsAndDaughters() function returns the sons/daughters of the user who has the given 'userId'.
	
RETURNED VALUES
	The getUserSonsAndDaughters() function returns:
	  - GET_USER_FAMILY__ERROR_OPENING_PARENTS_FILE_FOR_READING if an error occurs while opening parents file for reading;
	  - GET_USER_FAMILY__PARENTS_FILE_DOES_NOT_EXIST if the parents file doesn't exist;
	  - GET_USER_FAMILY__MEMORY_ALLOCATION_ERROR if an error occurs while allocating memory;
	  - An error code of getLongFilename() function if an error occurs while getting a long filename;
	  - An error code of getUserId() function if an error occurs while getting an user ID;
	  - OK in case of success.
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned getUserSpouse (userIdType userId, familyTreeType **user, familyTreeType *first);
/* 	
INPUT ARGUMENT
	- userIdType userId
	- familyTreeType *first
	
OUTPUT ARGUMENT
	- familyTreeType **user
	
DESCRIPTION
	The getUserSpouse() function returns the spouse of the user who has the given 'userId'.
	
RETURNED VALUES
	The getUserSpouse() function returns:
	  - GET_USER_FAMILY__ERROR_OPENING_PARENTS_FILE_FOR_READING if an error occurs while opening parents file for reading;
	  - GET_USER_FAMILY__PARENTS_FILE_DOES_NOT_EXIST if the parents file doesn't exist;
	  - GET_USER_FAMILY__MEMORY_ALLOCATION_ERROR if an error occurs while allocating memory;
	  - An error code of getLongFilename() function if an error occurs while getting a long filename;
	  - An error code of getUserId() function if an error occurs while getting an user ID;
	  - OK in case of success.
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned getUserBrothersAndSisters (userIdType userId, familyTreeType **user, familyTreeType *first);
/* 	
INPUT ARGUMENT
	- userIdType userId
	- familyTreeType *first
	
OUTPUT ARGUMENT
	- familyTreeType **user
	
DESCRIPTION
	The getUserBrothersAndSisters() function returns the brothers/sisters of the user who has the given 'userId'.
	
RETURNED VALUES
	The getUserBrothersAndSisters() function returns:
	  - GET_USER_FAMILY__ERROR_OPENING_PARENTS_FILE_FOR_READING if an error occurs while opening parents file for reading;
	  - GET_USER_FAMILY__PARENTS_FILE_DOES_NOT_EXIST if the parents file doesn't exist;
	  - GET_USER_FAMILY__MEMORY_ALLOCATION_ERROR if an error occurs while allocating memory;
	  - An error code of getLongFilename() function if an error occurs while getting a long filename;
	  - An error code of getUserId() function if an error occurs while getting an user ID;
	  - OK in case of success.
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned getUserFamily (userIdType userId, familyTreeType **user, familyTreeType *first);
/* 	
INPUT ARGUMENT
	- userIdType userId
	- familyTreeType *first
	
OUTPUT ARGUMENT
	- familyTreeType **user
	
DESCRIPTION
	The getUserFamily() function returns the family of the user who has the given 'userId'.
	
RETURNED VALUES
	The getUserFamily() function returns:
	  - GET_USER_FAMILY__ERROR_OPENING_PARENTS_FILE_FOR_READING if an error occurs while opening parents file for reading;
	  - GET_USER_FAMILY__PARENTS_FILE_DOES_NOT_EXIST if the parents file doesn't exist;
	  - GET_USER_FAMILY__MEMORY_ALLOCATION_ERROR if an error occurs while allocating memory;
	  - An error code of getLongFilename() function if an error occurs while getting a long filename;
	  - An error code of getUserId() function if an error occurs while getting an user ID;
	  - OK in case of success.
*/
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
boolean alreadyInFamilyList (userIdType id, familyTreeType *first);
/* 	
INPUT ARGUMENT
	- userIdType id
	- familyTreeType *first
	
DESCRIPTION
	The alreadyInFamilyList() function returns the true if the user who has the given 'id' are already in family list
	
RETURNED VALUES
	The alreadyInFamilyList() function returns:
	  - true, if the user are already in family list;
	  - false, in others cases.

*/
/*---------------------------------------------------------------------------------------------------------*/

#endif

// $RCSfile: functions.h,v $
