// =================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira
// Description: Secundary functions source file 
// Date: 23/10/2004
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: functions.c,v $
 * Revision 1.23  2005/02/16 22:11:21  marceloddm
 * CGI's added
 *
 * Revision 1.22  2004/12/21 16:58:57  marceloddm
 * autenticateUser() function added
 *
 * Revision 1.21  2004/12/20 23:52:21  marceloddm
 * New functions added: verifyIfcookieFileExist(), getCookieValue() and createNewCookieFile()
 *
 * Revision 1.20  2004/12/20 12:46:26  marceloddm
 * Functions added: insertFIFO(), retrieveFIFO(), freeFIFOResources()
 *
 * Revision 1.19  2004/12/18 02:00:44  marceloddm
 * stringCopy() function added and strncpy() bug solved
 *
 * Revision 1.18  2004/12/17 14:29:09  marceloddm
 * getDataFromId() and copyUserData() functions added
 *
 * Revision 1.17  2004/12/15 20:29:54  marceloddm
 * backupSystemFiles() function is OK!
 *
 * Revision 1.16  2004/12/15 18:41:52  marceloddm
 * Corrections concerning to the checkUserData() function completed.
 *
 * Revision 1.15  2004/12/15 18:30:47  marceloddm
 * Corrections have been made concerning to the relative category data validation in the checkUserData() function. The corrections have been made in the encrypted pass and e-mail fields. Corrections in the username and plain pass field to be done.
 *
 * Revision 1.13  2004/12/15 01:29:22  marceloddm
 * Functions added: copyDataToUserData, fillUserData
 * checkUserData() function have been modified
 *
 * Revision 1.11  2004/12/14 02:45:03  marceloddm
 * More functions have been added. The most importants are checkUserData(), backupSystemFiles() and getUserData() functions
 *
 * Revision 1.10  2004/12/13 16:02:55  marceloddm
 * Updated with checkUserData() and putUserData() functions
 *
 * Revision 1.9  2004/12/13 07:46:28  marceloddm
 * Functions added: putUserId(), putUserGender(), putUserRelationshipStatus(), getAdministratorPassword(), putUserCategory(), putString()
 *
 * Revision 1.8  2004/12/11 12:37:23  marceloddm
 * Author changed for 'marceloddm'
 *
 * Revision 1.7  2004/11/30 00:27:18  root
 * Last modification: shortHelp() function
 *
 * Revision 1.6  2004/11/27 23:18:33  root
 * getUserId(), getString() and checkField() functions are now completes!
 *
 * Revision 1.5  2004/11/27 01:41:13  root
 * Next step: To make the test program of the getUserId() function, and complete the getString() and checkField() functions
 *
 * Revision 1.4  2004/11/27 00:31:32  root
 * The function getLongFilename() is now complete
 *
 * Revision 1.3  2004/11/26 16:18:42  root
 * Next step: make the test program of longFilename() function
 *
 * Revision 1.2  2004/11/26 13:04:19  root
 * RCS's strings added
 * Making alterations of second version guide
 *
 * Revision 1.1  2004/11/26 13:00:36  root
 * Initial revision
 */


#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <menu.h>
#include <form.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/errno.h>
#include <errno.h>
#include "types.h"
#include "error.h"
#include "const.h"
#include "config.h"
#include "help.h"
#include "functions.h"


/*---------------------------------------------------------------------------------------------------------*/
char *stringCopy (char *destination, char *source, unsigned sizeOfDestination)
{
  destination[0] = EOS;
  return (destination = strncat (destination, source, sizeOfDestination));
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned createRandomString (char *validCharacters, unsigned length, char *randomString)
{
  unsigned index;

  if (randomString == NULL)
    return (CREATE_RANDOM_STRING__INVALID_STRING);
  if ((validCharacters == NULL) || (validCharacters[0] == EOS))
    return (CREATE_RANDOM_STRING__NO_VALID_CHARACTERS);
  
  srand ((unsigned) time (NULL));
  for (index = 0; index < length; index++)
    randomString[index] = validCharacters[rand() % strlen (validCharacters)];
  randomString[index] = EOS;
  
  return (OK);    
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned encodePassword (char *plainPass, char *encryptedPass)
{
  char salt[SALT_LENGTH + 1];
  char saltRandomPart[SALT_LENGTH -3 +1]; // 3 ---> "$1$" // 1 ---> EOS //
  unsigned errorCode;
  
  if (encryptedPass == NULL)
    return (ENCODE_PASSWORD__INVALID_ENCRYPTED_PASS);
  if ((plainPass == NULL) || (plainPass[0] == EOS))
    return (ENCODE_PASSWORD__INVALID_PLAIN_PASS);
  if ((errorCode = createRandomString (RANDOM_STRING_VALID_CHARACTERS, (SALT_LENGTH -3), saltRandomPart)) != OK )
    return (errorCode);
    
  snprintf (salt, (SALT_LENGTH + 1), "$1$%s", saltRandomPart);
  stringCopy (encryptedPass, crypt (plainPass, salt), ENCRYPTED_PASS_LENGTH);
  
  return (OK);
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned checkPassword (char *encryptedPass, char *plainPass)
{
  unsigned index;
  char salt[SALT_LENGTH +1];
  
  if ((plainPass == NULL) || (plainPass[0] == EOS))
    return (CHECK_PASSWORD__INVALID_PLAIN_PASS);
  if ((encryptedPass == NULL) || (strncmp (encryptedPass, "$1$", 3)))
    return (CHECK_PASSWORD__INVALID_ENCRYPTED_PASS);
  
  for (index = 0; index < SALT_LENGTH; index++)
    salt[index] = encryptedPass[index];
  salt[index] = EOS;
  
  if (strcmp (encryptedPass, crypt (plainPass, salt)))
    return (CHECK_PASSWORD__WRONG_PLAIN_PASS);
  
  return (OK);
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned getLongFilename (char *path, char *filename, char *longFilename)
{
  if (path == NULL)
    return (GET_LONG_FILENAME__INVALID_PATH);
  if (filename == NULL)
    return (GET_LONG_FILENAME__INVALID_FILENAME);
  if (longFilename == NULL)
    return (GET_LONG_FILENAME__NO_LONG_FILENAME);
           
  if ((strlen (path) + strlen (filename) +1) > MAX_LENGTH_LONG_FILENAME)
    return (GET_LONG_FILENAME__INVALID_LONG_FILENAME);
        
  strcpy (longFilename, path);
  if ((path[0] == EOS) || (path[strlen (path) -1] != '/'))
    strcat (longFilename, "/");
  strcat (longFilename, filename);
  
  return (OK);
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned getUserId (FILE *file, userIdType *userId)
{
  if (file == NULL)
    return (GET_USER_ID__INVALID_FILE);
  if (userId == NULL)
    return (GET_USER_ID__INVALID_USER_ID);
    
  if ((fread (userId, sizeof (userIdType), 1, file)) != 1)
  {
    if (ferror (file))
      return (GET_USER_ID__ERROR_READING_FILE);
    return (GET_USER_ID__END_OF_FILE);
  }
    
  return (OK);
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned putUserId (FILE *file, userIdType *userId)
{
  if (file == NULL)
    return (PUT_USER_ID__INVALID_FILE);
  if (userId == NULL)
    return (PUT_USER_ID__INVALID_USER_ID);
    
  if ((fwrite (userId, sizeof (userIdType), 1, file)) != 1)
  {
    if (ferror (file))
      return (PUT_USER_ID__ERROR_WRITING_FILE);
    return (PUT_USER_ID__END_OF_FILE);
  }
    
  return (OK);
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned putUserCategory (FILE *file, userCategoryType *userCategory)
{
  if (file == NULL)
    return (PUT_USER_CATEGORY__INVALID_FILE);
  if (userCategory == NULL)
    return (PUT_USER_CATEGORY__INVALID_USER_CATEGORY);
    
  if ((fwrite (userCategory, sizeof (userCategoryType), 1, file)) != 1)
  {
    if (ferror (file))
      return (PUT_USER_CATEGORY__ERROR_WRITING_FILE);
    return (PUT_USER_CATEGORY__END_OF_FILE);
  }
    
  return (OK);
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned getUserCategory (FILE *file, userCategoryType *userCategory)
{
  if (file == NULL)
    return (GET_USER_CATEGORY__INVALID_FILE);
  if (userCategory == NULL)
    return (GET_USER_CATEGORY__INVALID_USER_CATEGORY);
    
  if ((fread (userCategory, sizeof (userCategoryType), 1, file)) != 1)
  {
    if (ferror (file))
      return (GET_USER_CATEGORY__ERROR_READING_FILE);
    return (GET_USER_CATEGORY__END_OF_FILE);
  }
    
  return (OK);
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned putUserGender (FILE *file, genderType *userGender)
{
  if (file == NULL)
    return (PUT_USER_GENDER__INVALID_FILE);
  if (userGender == NULL)
    return (PUT_USER_GENDER__INVALID_USER_GENDER);
    
  if ((fwrite (userGender, sizeof (genderType), 1, file)) != 1)
  {
    if (ferror (file))
      return (PUT_USER_GENDER__ERROR_WRITING_FILE);
    return (PUT_USER_GENDER__END_OF_FILE);
  }
    
  return (OK);
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned getUserGender (FILE *file, genderType *userGender)
{
  if (file == NULL)
    return (GET_USER_GENDER__INVALID_FILE);
  if (userGender == NULL)
    return (GET_USER_GENDER__INVALID_USER_GENDER);
    
  if ((fread (userGender, sizeof (genderType), 1, file)) != 1)
  {
    if (ferror (file))
      return (GET_USER_GENDER__ERROR_READING_FILE);
    return (GET_USER_GENDER__END_OF_FILE);
  }
    
  return (OK);
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned putUserRelationshipStatus (FILE *file, relationshipStatusType *userRelationshipStatus)
{
  if (file == NULL)
    return (PUT_USER_RELATIONSHIP_STATUS__INVALID_FILE);
  if (userRelationshipStatus == NULL)
    return (PUT_USER_RELATIONSHIP_STATUS__INVALID_USER_RELATIONSHIP_STATUS);
    
  if ((fwrite (userRelationshipStatus, sizeof (relationshipStatusType), 1, file)) != 1)
  {
    if (ferror (file))
      return (PUT_USER_RELATIONSHIP_STATUS__ERROR_WRITING_FILE);
    return (PUT_USER_RELATIONSHIP_STATUS__END_OF_FILE);
  }
    
  return (OK);
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned getUserRelationshipStatus (FILE *file, relationshipStatusType *userRelationshipStatus)
{
  if (file == NULL)
    return (GET_USER_RELATIONSHIP_STATUS__INVALID_FILE);
  if (userRelationshipStatus == NULL)
    return (GET_USER_RELATIONSHIP_STATUS__INVALID_USER_RELATIONSHIP_STATUS);
    
  if ((fread (userRelationshipStatus, sizeof (relationshipStatusType), 1, file)) != 1)
  {
    if (ferror (file))
      return (GET_USER_RELATIONSHIP_STATUS__ERROR_READING_FILE);
    return (GET_USER_RELATIONSHIP_STATUS__END_OF_FILE);
  }
    
  return (OK);
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned getString (FILE *file, unsigned minLength, unsigned maxLength, char *string)
{
  unsigned index;
  
  if (file == NULL)
    return (GET_STRING__INVALID_FILE);
  if (string == NULL)
    return (GET_STRING__INVALID_STRING);
  
  for (index = 0; index <= maxLength; index++)
  {
    if ((fread (&string[index], 1, 1, file)) != 1)
    {
      if (ferror (file))
        return (GET_STRING__ERROR_READING_FILE);
      return (GET_STRING__END_OF_FILE);
    }
    if (string[index] == EOS)
    {
      if (index < minLength)
        return (GET_STRING__SMALL_STRING);   
      return (OK);
    }
  }
  return (GET_STRING__BIG_STRING);  
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned putString (FILE *file, unsigned minLength, unsigned maxLength, char *string)
{
  unsigned index;
  
  if (file == NULL)
    return (PUT_STRING__INVALID_FILE);
  if (string == NULL)
    return (PUT_STRING__INVALID_STRING);
  
  for (index = 0; index <= maxLength; index++)
  {
    if ((fwrite (&string[index], 1, 1, file)) != 1)
    {
      if (ferror (file))
        return (PUT_STRING__ERROR_WRITING_FILE);
      return (PUT_STRING__END_OF_FILE);
    }
    if (string[index] == EOS)
    {
      if (index < minLength)
        return (PUT_STRING__SMALL_STRING);   
      return (OK);
    }
  }
  return (PUT_STRING__BIG_STRING);  
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned checkField (char *field, char *validCharacters, unsigned minLength, unsigned maxLength)
{
  unsigned indexField, indexValidCharacters;
  boolean isValid;
  
  if (field == NULL)
    return (CHECK_FIELD__INVALID_FIELD);
  if ((validCharacters == NULL) || (validCharacters[0] == EOS))
    return (CHECK_FIELD__NO_VALID_CHARACTERS);
  if (strlen (field) < minLength)
    return (CHECK_FIELD__SMALL_FIELD);
  if (strlen (field) > maxLength)
    return (CHECK_FIELD__BIG_FIELD);
  
  for (indexField = 0; indexField < strlen (field) ; indexField++)
  {
    isValid = false;
    for (indexValidCharacters = 0; indexValidCharacters < strlen (validCharacters); indexValidCharacters++)
      if (field[indexField] == validCharacters[indexValidCharacters])
      {
        isValid = true;
	break;
      }
    if (isValid == false)
      return (CHECK_FIELD__FIELD_HAS_NOT_VALID_CHARACTERS);
  }
  
  return (OK);
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
void shortHelp (void)
{
  #ifdef ENGLISH
    printf ("\nUsage: ./relationshipSystem [OPTION] [ARGUMENTS]\n\n");
    printf ("List of options:\n");
    printf ("  -n | --ncurses     --> Run the program with NCURSES's interface\n");    
    printf ("  -h | --help        --> Show a help message\n");
    printf ("  -t | --install     --> Install the system, including administrator's data\n");
    printf ("  -a | --add         --> Add a new user to the system\n");
    printf ("  -e | --edit        --> Edit user data\n");
    printf ("  -r | --remove      --> Remove a user from the system\n");   
    printf ("  -i | --invite      --> Invite someone to enter in the system\n");
    printf ("  -I | --Invite      --> Invite a user to enter in a friendship group\n");
    printf ("  -F | --Friendship  --> Get pending invitations of a user\n");
    printf ("  -P | --Accept      --> Accept friendship invitation\n");
    printf ("  -J | --Reject      --> Reject friendship invitation\n");
    printf ("  -X | --Exclude     --> Exclude friendship relation\n");
    printf ("  -G | --Get         --> Get friends of a user\n");
    printf ("  -c | --change      --> Change user category\n");    
    printf ("  -A | --Add         --> Add parent relationship\n");
    printf ("  -R | --Remove      --> Remove parent relationship\n");
    printf ("  -E | --Edit        --> Edit parent relationship\n");
    printf ("  -g | --get         --> Search users\n");
    printf ("  -m | --mount       --> Mount family tree\n"); 
    printf ("  -p | --password    --> Recovery password\n");
    printf ("  -C | --Change      --> Change password\n");
    printf ("  -u | --upload      --> Upload user's picture\n\n");
    
  #elif PORTUGUESE
    printf ("\nUso: ./relationshipSystem [OPÇÃO] [ARGUMENTOS]\n\n");
    printf ("Lista de opções:\n");
    printf ("  -n | --ncurses     --> Roda o programa com interface gráfica NCURSES\n");    
    printf ("  -h | --help        --> Exibe uma mensagem de ajuda\n");
    printf ("  -t | --install     --> Instala o sistema, incluindo os dados do administrador\n");
    printf ("  -a | --add         --> Adiciona um novo usuário ao sistema\n");
    printf ("  -e | --edit        --> Edita dados de usuário\n");
    printf ("  -r | --remove      --> Remove um usuário do sistema\n");   
    printf ("  -i | --invite      --> Convida alguém para entrar no sistema\n");
    printf ("  -I | --Invite      --> Convida alguém para iniciar uma relação de amizade\n");
    printf ("  -F | --Friendship  --> Obtém convites pendentes de um usuário\n");
    printf ("  -P | --Accept      --> Aceita convite de amizade\n");
    printf ("  -J | --Reject      --> Rejeita convite de amizade\n");
    printf ("  -X | --Exclude     --> Exclui amizade\n");
    printf ("  -G | --Get         --> Obtém amigos de um usuário\n");
    printf ("  -c | --change      --> Troca categoria de usuário\n");    
    printf ("  -A | --Add         --> Adiciona relação de parentesco\n");
    printf ("  -R | --Remove      --> Remove relação de parentesco\n");
    printf ("  -E | --Edit        --> Edita relação de parentesco\n");
    printf ("  -g | --get         --> Procura usuários\n");
    printf ("  -m | --mount       --> Monta árvore genealógica\n"); 
    printf ("  -p | --password    --> Recupera senha\n");
    printf ("  -C | --Change      --> Troca senha\n");
    printf ("  -u | --upload      --> Faz upload de foto do usuário\n\n");
  #endif
}  
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned getAdministratorPassword (char *password)
{

  if (password == NULL)
    return (GET_ADMINISTRATOR_PASSWORD__INVALID_PASSWORD); 
  if (getuid () != ADMINISTRATOR_UID)
    return (GET_ADMINISTRATOR_PASSWORD__DO_NOT_IS_THE_ADMINISTRATOR);
  
  stringCopy (password, getpass (showTextHelpMessage (GET_ADMINISTRATOR_PASSWORD__PROMPT_OF_PASSWORD)), MAX_LENGTH_PLAIN_PASS); 
    
  if (strcmp (password, getpass (showTextHelpMessage (GET_ADMINISTRATOR_PASSWORD__PROMPT_OF_CONFIRMATION))))
    return (GET_ADMINISTRATOR_PASSWORD__LOGIN_INCORRECT);
    
  return (OK);
}  
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned checkUserData (userDataType *userData)
{
  unsigned errorCode;

  if (userData == NULL)
    return (CHECK_USER_DATA__INVALID_USER_DATA); 
    
  if (( userData->category == webUser ) || ( userData->category == administrator ))  
    if ((errorCode = checkField (userData->userName, USERNAME_VALID_CHARACTERS, MIN_LENGTH_USERNAME,
                                 MAX_LENGTH_USERNAME)) != OK)
      switch (errorCode)
      {
        case (CHECK_FIELD__FIELD_HAS_NOT_VALID_CHARACTERS):
          return (CHECK_USER_DATA__USERNAME_HAS_NOT_VALID_CHARACTERS);
        break;
        case (CHECK_FIELD__BIG_FIELD):
          return (CHECK_USER_DATA__BIG_USERNAME);
        break;
        case (CHECK_FIELD__SMALL_FIELD):
          return (CHECK_USER_DATA__SMALL_USERNAME);
        break;
        default:
          return (errorCode);
      }
  
  if ( userData->category == relative ) 
    if ((errorCode = checkField (userData->userName, USERNAME_VALID_CHARACTERS, LENGTH_USERNAME_RELATIVE,
                                 LENGTH_USERNAME_RELATIVE)) != OK)
      switch (errorCode)
      {
        case (CHECK_FIELD__FIELD_HAS_NOT_VALID_CHARACTERS):
          return (CHECK_USER_DATA__USERNAME_HAS_NOT_VALID_CHARACTERS);
        break;
        case (CHECK_FIELD__BIG_FIELD):
          return (CHECK_USER_DATA__BIG_USERNAME);
        break;
        case (CHECK_FIELD__SMALL_FIELD):
          return (CHECK_USER_DATA__SMALL_USERNAME);
        break;
        default:
          return (errorCode);
      }    
      
  if (( userData->category == webUser ) || ( userData->category == administrator ))    
    if ((errorCode = checkField (userData->plainPass, PLAIN_PASS_VALID_CHARACTERS, MIN_LENGTH_PLAIN_PASS,
                                 MAX_LENGTH_PLAIN_PASS)) != OK)
      switch (errorCode)
      {
        case (CHECK_FIELD__FIELD_HAS_NOT_VALID_CHARACTERS):
          return (CHECK_USER_DATA__PLAIN_PASS_HAS_NOT_VALID_CHARACTERS);
        break;
        case (CHECK_FIELD__BIG_FIELD):
          return (CHECK_USER_DATA__BIG_PLAIN_PASS);
        break;
        case (CHECK_FIELD__SMALL_FIELD):
          return (CHECK_USER_DATA__SMALL_PLAIN_PASS);
        break;
        default:
          return (errorCode);
      }
  
  if ( userData->category == relative )    
    if ((errorCode = checkField (userData->plainPass, PLAIN_PASS_VALID_CHARACTERS, LENGTH_PLAIN_PASS_RELATIVE,
                                 LENGTH_PLAIN_PASS_RELATIVE)) != OK)
      switch (errorCode)
      {
        case (CHECK_FIELD__FIELD_HAS_NOT_VALID_CHARACTERS):
          return (CHECK_USER_DATA__PLAIN_PASS_HAS_NOT_VALID_CHARACTERS);
        break;
        case (CHECK_FIELD__BIG_FIELD):
          return (CHECK_USER_DATA__BIG_PLAIN_PASS);
        break;
        case (CHECK_FIELD__SMALL_FIELD):
          return (CHECK_USER_DATA__SMALL_PLAIN_PASS);
        break;
        default:
          return (errorCode);
      }    

  if (( userData->category == webUser ) || ( userData->category == administrator ))           
    if ((errorCode = checkField (userData->encryptedPass, ENCRYPTED_PASS_VALID_CHARACTERS,
    	  	  	         ENCRYPTED_PASS_LENGTH, ENCRYPTED_PASS_LENGTH)) != OK)
      switch (errorCode)
      {
        case (CHECK_FIELD__FIELD_HAS_NOT_VALID_CHARACTERS):
          return (CHECK_USER_DATA__ENCRYPTED_PASS_HAS_NOT_VALID_CHARACTERS);
        break;
        case (CHECK_FIELD__BIG_FIELD):
          return (CHECK_USER_DATA__BIG_ENCRYPTED_PASS);
        break;
        case (CHECK_FIELD__SMALL_FIELD):
          return (CHECK_USER_DATA__SMALL_ENCRYPTED_PASS);
        break;
        default:
          return (errorCode);
      }

  if ( userData->category == relative )
      if ((errorCode = checkField (userData->encryptedPass, ENCRYPTED_PASS_VALID_CHARACTERS,
    	  	  	         ENCRYPTED_PASS_LENGTH_RELATIVE, ENCRYPTED_PASS_LENGTH_RELATIVE)) != OK)
      switch (errorCode)
      {
        case (CHECK_FIELD__FIELD_HAS_NOT_VALID_CHARACTERS):
          return (CHECK_USER_DATA__ENCRYPTED_PASS_HAS_NOT_VALID_CHARACTERS);
        break;
        case (CHECK_FIELD__BIG_FIELD):
          return (CHECK_USER_DATA__BIG_ENCRYPTED_PASS);
        break;
        case (CHECK_FIELD__SMALL_FIELD):
          return (CHECK_USER_DATA__SMALL_ENCRYPTED_PASS);
        break;
        default:
          return (errorCode);  
      }       
      
  if ((errorCode = checkField (userData->name, NAME_VALID_CHARACTERS, MIN_LENGTH_NAME,
                               MAX_LENGTH_NAME)) != OK)
    switch (errorCode)
    {
      case (CHECK_FIELD__FIELD_HAS_NOT_VALID_CHARACTERS):
        return (CHECK_USER_DATA__NAME_HAS_NOT_VALID_CHARACTERS);
      break;
      case (CHECK_FIELD__BIG_FIELD):
        return (CHECK_USER_DATA__BIG_NAME);
      break;
      case (CHECK_FIELD__SMALL_FIELD):
        return (CHECK_USER_DATA__SMALL_NAME);
      break;
      default:
        return (errorCode);
    }
    
  if (( userData->category == webUser ) || ( userData->category == administrator ))  
    if ((errorCode = checkField (userData->email, EMAIL_VALID_CHARACTERS, MIN_LENGTH_EMAIL,
         			 MAX_LENGTH_EMAIL)) != OK)
      switch (errorCode)
      {
        case (CHECK_FIELD__FIELD_HAS_NOT_VALID_CHARACTERS):
          return (CHECK_USER_DATA__EMAIL_HAS_NOT_VALID_CHARACTERS);
        break;
        case (CHECK_FIELD__BIG_FIELD):
          return (CHECK_USER_DATA__BIG_EMAIL);
        break;
        case (CHECK_FIELD__SMALL_FIELD):
          return (CHECK_USER_DATA__SMALL_EMAIL);
        break;
        default:
          return (errorCode);
      }

  if ( userData->category == relative )  
    if ((errorCode = checkField (userData->email, EMAIL_VALID_CHARACTERS, MIN_LENGTH_EMAIL_RELATIVE,
         			 MAX_LENGTH_EMAIL)) != OK)
      switch (errorCode)
      {
        case (CHECK_FIELD__FIELD_HAS_NOT_VALID_CHARACTERS):
          return (CHECK_USER_DATA__EMAIL_HAS_NOT_VALID_CHARACTERS);
        break;
        case (CHECK_FIELD__BIG_FIELD):
          return (CHECK_USER_DATA__BIG_EMAIL);
        break;
        case (CHECK_FIELD__SMALL_FIELD):
          return (CHECK_USER_DATA__SMALL_EMAIL);
        break;
        default:
          return (errorCode);
      }
                
  if ((errorCode = checkField (userData->homepage, HOMEPAGE_VALID_CHARACTERS, MIN_LENGTH_HOMEPAGE,
  			       MAX_LENGTH_HOMEPAGE)) != OK)
    switch (errorCode)
    {
      case (CHECK_FIELD__FIELD_HAS_NOT_VALID_CHARACTERS):
        return (CHECK_USER_DATA__HOMEPAGE_HAS_NOT_VALID_CHARACTERS);
      break;
      case (CHECK_FIELD__BIG_FIELD):
        return (CHECK_USER_DATA__BIG_HOMEPAGE);
      break;
      case (CHECK_FIELD__SMALL_FIELD):
        return (CHECK_USER_DATA__SMALL_HOMEPAGE);
      break;
      default:
        return (errorCode);
    }
    
  if ((errorCode = checkField (userData->telNumber, TEL_NUMBER_VALID_CHARACTERS, MIN_LENGTH_TEL_NUMBER,
  			       MAX_LENGTH_TEL_NUMBER)) != OK)
    switch (errorCode)
    {
      case (CHECK_FIELD__FIELD_HAS_NOT_VALID_CHARACTERS):
        return (CHECK_USER_DATA__TEL_NUMBER_HAS_NOT_VALID_CHARACTERS);
      break;
      case (CHECK_FIELD__BIG_FIELD):
        return (CHECK_USER_DATA__BIG_TEL_NUMBER);
      break;
      case (CHECK_FIELD__SMALL_FIELD):
        return (CHECK_USER_DATA__SMALL_TEL_NUMBER);
      break;
      default:
        return (errorCode);
    }
      
  if ((errorCode = checkField (userData->cellNumber, CELL_NUMBER_VALID_CHARACTERS, MIN_LENGTH_CELL_NUMBER,
  			       MAX_LENGTH_CELL_NUMBER)) != OK)
    switch (errorCode)
    {
      case (CHECK_FIELD__FIELD_HAS_NOT_VALID_CHARACTERS):
        return (CHECK_USER_DATA__CELL_NUMBER_HAS_NOT_VALID_CHARACTERS);
      break;
      case (CHECK_FIELD__BIG_FIELD):
        return (CHECK_USER_DATA__BIG_CELL_NUMBER);
      break;
      case (CHECK_FIELD__SMALL_FIELD):
        return (CHECK_USER_DATA__SMALL_CELL_NUMBER);
      break;
      default:
        return (errorCode);
    }  
  
  if ((errorCode = checkField (userData->birthday, BIRTHDAY_VALID_CHARACTERS, MIN_LENGTH_BIRTHDAY,
  			       MAX_LENGTH_BIRTHDAY)) != OK)
    switch (errorCode)
    {
      case (CHECK_FIELD__FIELD_HAS_NOT_VALID_CHARACTERS):
        return (CHECK_USER_DATA__BIRTHDAY_HAS_NOT_VALID_CHARACTERS);
      break;
      case (CHECK_FIELD__BIG_FIELD):
        return (CHECK_USER_DATA__BIG_BIRTHDAY);
      break;
      case (CHECK_FIELD__SMALL_FIELD):
        return (CHECK_USER_DATA__SMALL_BIRTHDAY);
      break;
      default:
        return (errorCode);
    }  
    
  if ((errorCode = checkField (userData->description, DESCRIPTION_VALID_CHARACTERS,
  			       MIN_LENGTH_DESCRIPTION, MAX_LENGTH_DESCRIPTION)) != OK)
    switch (errorCode)
    {
      case (CHECK_FIELD__FIELD_HAS_NOT_VALID_CHARACTERS):
        return (CHECK_USER_DATA__DESCRIPTION_HAS_NOT_VALID_CHARACTERS);
      break;
      case (CHECK_FIELD__BIG_FIELD):
        return (CHECK_USER_DATA__BIG_DESCRIPTION);
      break;
      case (CHECK_FIELD__SMALL_FIELD):
        return (CHECK_USER_DATA__SMALL_DESCRIPTION);
      break;
      default:
        return (errorCode);
    }  
    
  if ((errorCode = checkField (userData->address.street, STREET_VALID_CHARACTERS, MIN_LENGTH_STREET,
  			       MAX_LENGTH_STREET)) != OK)
    switch (errorCode)
    {
      case (CHECK_FIELD__FIELD_HAS_NOT_VALID_CHARACTERS):
        return (CHECK_USER_DATA__STREET_HAS_NOT_VALID_CHARACTERS);
      break;
      case (CHECK_FIELD__BIG_FIELD):
        return (CHECK_USER_DATA__BIG_STREET);
      break;
      case (CHECK_FIELD__SMALL_FIELD):
        return (CHECK_USER_DATA__SMALL_STREET);
      break;
      default:
        return (errorCode);
    }  
    
  if ((errorCode = checkField (userData->address.homeNumber, HOME_NUMBER_VALID_CHARACTERS,
  			       MIN_LENGTH_HOME_NUMBER, MAX_LENGTH_HOME_NUMBER)) != OK)
    switch (errorCode)
    {
      case (CHECK_FIELD__FIELD_HAS_NOT_VALID_CHARACTERS):
        return (CHECK_USER_DATA__HOME_NUMBER_HAS_NOT_VALID_CHARACTERS);
      break;
      case (CHECK_FIELD__BIG_FIELD):
        return (CHECK_USER_DATA__BIG_HOME_NUMBER);
      break;
      case (CHECK_FIELD__SMALL_FIELD):
        return (CHECK_USER_DATA__SMALL_HOME_NUMBER);
      break;
      default:
        return (errorCode);
    }  
    
  if ((errorCode = checkField (userData->address.complement, COMPLEMENT_VALID_CHARACTERS,
  			       MIN_LENGTH_COMPLEMENT, MAX_LENGTH_COMPLEMENT)) != OK)
    switch (errorCode)
    {
      case (CHECK_FIELD__FIELD_HAS_NOT_VALID_CHARACTERS):
        return (CHECK_USER_DATA__COMPLEMENT_HAS_NOT_VALID_CHARACTERS);
      break;
      case (CHECK_FIELD__BIG_FIELD):
        return (CHECK_USER_DATA__BIG_COMPLEMENT);
      break;
      case (CHECK_FIELD__SMALL_FIELD):
        return (CHECK_USER_DATA__SMALL_COMPLEMENT);
      break;
      default:
        return (errorCode);
    }  
   
  if ((errorCode = checkField (userData->address.district, DISTRICT_VALID_CHARACTERS,
  			       MIN_LENGTH_DISTRICT, MAX_LENGTH_DISTRICT)) != OK)
    switch (errorCode)
    {
      case (CHECK_FIELD__FIELD_HAS_NOT_VALID_CHARACTERS):
        return (CHECK_USER_DATA__DISTRICT_HAS_NOT_VALID_CHARACTERS);
      break;
      case (CHECK_FIELD__BIG_FIELD):
        return (CHECK_USER_DATA__BIG_DISTRICT);
      break;
      case (CHECK_FIELD__SMALL_FIELD):
        return (CHECK_USER_DATA__SMALL_DISTRICT);
      break;
      default:
        return (errorCode);
    }  
    
  if ((errorCode = checkField (userData->address.city, CITY_VALID_CHARACTERS,
  			       MIN_LENGTH_CITY, MAX_LENGTH_CITY)) != OK)
    switch (errorCode)
    {
      case (CHECK_FIELD__FIELD_HAS_NOT_VALID_CHARACTERS):
        return (CHECK_USER_DATA__CITY_HAS_NOT_VALID_CHARACTERS);
      break;
      case (CHECK_FIELD__BIG_FIELD):
        return (CHECK_USER_DATA__BIG_CITY);
      break;
      case (CHECK_FIELD__SMALL_FIELD):
        return (CHECK_USER_DATA__SMALL_CITY);
      break;
      default:
        return (errorCode);
    }  
   
  if ((errorCode = checkField (userData->address.state, STATE_VALID_CHARACTERS,
  			       MIN_LENGTH_STATE, MAX_LENGTH_STATE)) != OK)
    switch (errorCode)
    {
      case (CHECK_FIELD__FIELD_HAS_NOT_VALID_CHARACTERS):
        return (CHECK_USER_DATA__STATE_HAS_NOT_VALID_CHARACTERS);
      break;
      case (CHECK_FIELD__BIG_FIELD):
        return (CHECK_USER_DATA__BIG_STATE);
      break;
      case (CHECK_FIELD__SMALL_FIELD):
        return (CHECK_USER_DATA__SMALL_STATE);
      break;
      default:
        return (errorCode);
    }  
    
  if ((errorCode = checkField (userData->address.country, COUNTRY_VALID_CHARACTERS,
  			       MIN_LENGTH_COUNTRY, MAX_LENGTH_COUNTRY)) != OK)
    switch (errorCode)
    {
      case (CHECK_FIELD__FIELD_HAS_NOT_VALID_CHARACTERS):
        return (CHECK_USER_DATA__COUNTRY_HAS_NOT_VALID_CHARACTERS);
      break;
      case (CHECK_FIELD__BIG_FIELD):
        return (CHECK_USER_DATA__BIG_COUNTRY);
      break;
      case (CHECK_FIELD__SMALL_FIELD):
        return (CHECK_USER_DATA__SMALL_COUNTRY);
      break;
      default:
        return (errorCode);
    }  
    
  if ((errorCode = checkField (userData->address.zipCode, ZIP_CODE_VALID_CHARACTERS,
  			       MIN_LENGTH_ZIP_CODE, MAX_LENGTH_ZIP_CODE)) != OK)
    switch (errorCode)
    {
      case (CHECK_FIELD__FIELD_HAS_NOT_VALID_CHARACTERS):
        return (CHECK_USER_DATA__ZIP_CODE_HAS_NOT_VALID_CHARACTERS);
      break;
      case (CHECK_FIELD__BIG_FIELD):
        return (CHECK_USER_DATA__BIG_ZIP_CODE);
      break;
      case (CHECK_FIELD__SMALL_FIELD):
        return (CHECK_USER_DATA__SMALL_ZIP_CODE);
      break;
      default:
        return (errorCode);
    }  
    
    
  return (OK);
}  
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned putUserData (FILE *file, char *filename, userDataType *userData)
{
  unsigned errorCode;

  if (file == NULL)
    return (PUT_USER_DATA__INVALID_FILE); 
  if (filename == NULL)
    return (PUT_USER_DATA__NO_FILENAME);
  if (userData == NULL)
    return (PUT_USER_DATA__INVALID_USER_DATA);
    
  if (!strncmp (filename, PASSWORD_FILE_NAME , PASSWORD_FILE_LENGTH))
  {
    if ((errorCode = putUserId (file, &(userData->userId))) != OK)
      return (errorCode);
      
    if ((errorCode = putString (file, MIN_LENGTH_USERNAME, MAX_LENGTH_USERNAME, userData->userName)) != OK)
      return (errorCode);
      
    if ((errorCode = putString (file, ENCRYPTED_PASS_LENGTH, ENCRYPTED_PASS_LENGTH, userData->encryptedPass)) != OK)
      return (errorCode);
      
    return (OK);
  }

  if (!strncmp (filename, USERS_FILE_NAME, USERS_FILE_LENGTH))   
  {
    if ((errorCode = putUserId (file, &(userData->userId))) != OK)
      return (errorCode);
      
    if ((errorCode = putUserCategory (file, &(userData->category))) != OK)
      return (errorCode);
      
    if ((errorCode = putString (file, MIN_LENGTH_NAME, MAX_LENGTH_NAME, userData->name)) != OK)
      return (errorCode);
      
    if ((userData->category == webUser) || (userData->category == administrator))
    {
      if ((errorCode = putString (file, MIN_LENGTH_EMAIL, MAX_LENGTH_EMAIL, userData->email)) != OK)
        return (errorCode);
    }
    else
      if ((errorCode = putString (file, MIN_LENGTH_EMAIL_RELATIVE, MAX_LENGTH_EMAIL, userData->email)) != OK)
        return (errorCode);  
    
    if ((errorCode = putString (file, MIN_LENGTH_HOMEPAGE, MAX_LENGTH_HOMEPAGE, userData->homepage)) != OK)
      return (errorCode);
      
    if ((errorCode = putString (file, MIN_LENGTH_STREET, MAX_LENGTH_STREET, userData->address.street)) != OK)
      return (errorCode);
      
    if ((errorCode = putString (file, MIN_LENGTH_HOME_NUMBER, MAX_LENGTH_HOME_NUMBER, userData->address.homeNumber)) != OK)
      return (errorCode);
      
    if ((errorCode = putString (file, MIN_LENGTH_COMPLEMENT, MAX_LENGTH_COMPLEMENT, userData->address.complement)) != OK)
      return (errorCode);
      
    if ((errorCode = putString (file, MIN_LENGTH_DISTRICT, MAX_LENGTH_DISTRICT, userData->address.district)) != OK)
      return (errorCode);
    
    if ((errorCode = putString (file, MIN_LENGTH_CITY, MAX_LENGTH_CITY, userData->address.city)) != OK)
      return (errorCode);
   
    if ((errorCode = putString (file, MIN_LENGTH_STATE, MAX_LENGTH_STATE, userData->address.state)) != OK)
      return (errorCode);
    
    if ((errorCode = putString (file, MIN_LENGTH_COUNTRY, MAX_LENGTH_COUNTRY, userData->address.country)) != OK)
      return (errorCode);
    
    if ((errorCode = putString (file, MIN_LENGTH_ZIP_CODE, MAX_LENGTH_ZIP_CODE, userData->address.zipCode)) != OK)
      return (errorCode);
    
    if ((errorCode = putString (file, MIN_LENGTH_TEL_NUMBER, MAX_LENGTH_TEL_NUMBER, userData->telNumber)) != OK)
      return (errorCode);
    
    if ((errorCode = putString (file, MIN_LENGTH_CELL_NUMBER, MAX_LENGTH_CELL_NUMBER, userData->cellNumber)) != OK)
      return (errorCode);
    
    if ((errorCode = putUserGender (file, &(userData->gender))) != OK)
      return (errorCode);
    
    if ((errorCode = putUserRelationshipStatus (file, &(userData->relationshipStatus))) != OK)
      return (errorCode);
    
    if ((errorCode = putString (file, MIN_LENGTH_BIRTHDAY, MAX_LENGTH_BIRTHDAY, userData->birthday)) != OK)
      return (errorCode);
    
    if ((errorCode = putString (file, MIN_LENGTH_DESCRIPTION, MAX_LENGTH_DESCRIPTION, userData->description)) != OK)
      return (errorCode);
    return (OK);
  }
  return (PUT_USER_DATA__INVALID_FILENAME);
          
}  
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned getUserData (FILE *file, char *filename, userDataType *userData)
{
  unsigned errorCode;

  if (file == NULL)
    return (GET_USER_DATA__INVALID_FILE); 
  if (filename == NULL)
    return (GET_USER_DATA__NO_FILENAME);
  if (userData == NULL)
    return (GET_USER_DATA__INVALID_USER_DATA);
    
  if (!strncmp (filename, PASSWORD_FILE_NAME, PASSWORD_FILE_LENGTH))
  {
    if ((errorCode = getUserId (file, &(userData->userId))) != OK)
      return (errorCode);
      
    if ((errorCode = getString (file, MIN_LENGTH_USERNAME, MAX_LENGTH_USERNAME, userData->userName)) != OK)
      return (errorCode);
      
    if ((errorCode = getString (file, ENCRYPTED_PASS_LENGTH, ENCRYPTED_PASS_LENGTH, userData->encryptedPass)) != OK)
      return (errorCode);
      
    return (OK);
  }
  
  if (!strncmp (filename, USERS_FILE_NAME, USERS_FILE_LENGTH))   
  {
    if ((errorCode = getUserId (file, &(userData->userId))) != OK)
      return (errorCode);
      
    if ((errorCode = getUserCategory (file, &(userData->category))) != OK)
      return (errorCode);
      
    if ((errorCode = getString (file, MIN_LENGTH_NAME, MAX_LENGTH_NAME, userData->name)) != OK)
      return (errorCode);
      
    if ((userData->category == webUser) || (userData->category == administrator))
    {
      if ((errorCode = getString (file, MIN_LENGTH_EMAIL, MAX_LENGTH_EMAIL, userData->email)) != OK)
        return (errorCode);
    }
    else
      if ((errorCode = getString (file, MIN_LENGTH_EMAIL_RELATIVE, MAX_LENGTH_EMAIL, userData->email)) != OK)
        return (errorCode);
			
    if ((errorCode = getString (file, MIN_LENGTH_HOMEPAGE, MAX_LENGTH_HOMEPAGE, userData->homepage)) != OK)
      return (errorCode);
      
    if ((errorCode = getString (file, MIN_LENGTH_STREET, MAX_LENGTH_STREET, userData->address.street)) != OK)
      return (errorCode);
      
    if ((errorCode = getString (file, MIN_LENGTH_HOME_NUMBER, MAX_LENGTH_HOME_NUMBER, userData->address.homeNumber)) != OK)
      return (errorCode);
      
    if ((errorCode = getString (file, MIN_LENGTH_COMPLEMENT, MAX_LENGTH_COMPLEMENT, userData->address.complement)) != OK)
      return (errorCode);
      
    if ((errorCode = getString (file, MIN_LENGTH_DISTRICT, MAX_LENGTH_DISTRICT, userData->address.district)) != OK)
      return (errorCode);
      
    if ((errorCode = getString (file, MIN_LENGTH_CITY, MAX_LENGTH_CITY, userData->address.city)) != OK)
      return (errorCode);
      
    if ((errorCode = getString (file, MIN_LENGTH_STATE, MAX_LENGTH_STATE, userData->address.state)) != OK)
      return (errorCode);
      
    if ((errorCode = getString (file, MIN_LENGTH_COUNTRY, MAX_LENGTH_COUNTRY, userData->address.country)) != OK)
      return (errorCode);
      
    if ((errorCode = getString (file, MIN_LENGTH_ZIP_CODE, MAX_LENGTH_ZIP_CODE, userData->address.zipCode)) != OK)
      return (errorCode);
      
    if ((errorCode = getString (file, MIN_LENGTH_TEL_NUMBER, MAX_LENGTH_TEL_NUMBER, userData->telNumber)) != OK)
      return (errorCode);
      
    if ((errorCode = getString (file, MIN_LENGTH_CELL_NUMBER, MAX_LENGTH_CELL_NUMBER, userData->cellNumber)) != OK)
      return (errorCode);
      
    if ((errorCode = getUserGender (file, &(userData->gender))) != OK)
      return (errorCode);
      
    if ((errorCode = getUserRelationshipStatus (file, &(userData->relationshipStatus))) != OK)
      return (errorCode);
      
    if ((errorCode = getString (file, MIN_LENGTH_BIRTHDAY, MAX_LENGTH_BIRTHDAY, userData->birthday)) != OK)
      return (errorCode);
      
    if ((errorCode = getString (file, MIN_LENGTH_DESCRIPTION, MAX_LENGTH_DESCRIPTION, userData->description)) != OK)
      return (errorCode);
      
    return (OK);
  }
    
  return (GET_USER_DATA__INVALID_FILENAME);
}  
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned backupSystemFiles (void)
{
  unsigned errorCode;
  FILE *passwordFile, *usersFile, *friendsFile, *parentsFile;
  char passwordFilename[MAX_LENGTH_LONG_FILENAME +1];
  char    usersFilename[MAX_LENGTH_LONG_FILENAME +1];
  char  friendsFilename[MAX_LENGTH_LONG_FILENAME +1];
  char  parentsFilename[MAX_LENGTH_LONG_FILENAME +1];
  char invitationsFilename[MAX_LENGTH_LONG_FILENAME +1];
  char cookiesFilename[MAX_LENGTH_LONG_FILENAME +1];
  char command[2*MAX_LENGTH_LONG_FILENAME +1 +11];
 
  
  if ((errorCode = getLongFilename (DATA_DIR, PASSWORD_FILE_NAME, passwordFilename)) != OK)
    return (errorCode);
  if ((passwordFile = fopen (passwordFilename, "r")) == NULL)
  {
    if (errno != ENOENT)
      return (BACKUP_SYSTEM_FILES__ERROR_OPENING_PASSWORD_FILE_FOR_READING);
    return (BACKUP_SYSTEM_FILES__NOT_YET_INSTALLED);
  }
  fclose (passwordFile);
  
  if ((errorCode = getLongFilename (DATA_DIR, USERS_FILE_NAME, usersFilename)) != OK)
    return (errorCode);
  if ((usersFile = fopen (usersFilename, "r")) == NULL)
  {
    if (errno != ENOENT)
      return (BACKUP_SYSTEM_FILES__ERROR_OPENING_USERS_FILE_FOR_READING);
    return (BACKUP_SYSTEM_FILES__NOT_YET_INSTALLED);
  }
  fclose (usersFile);
  
  if ((errorCode = getLongFilename (DATA_DIR, FRIENDS_FILE_NAME, friendsFilename)) != OK)
    return (errorCode);
  if ((friendsFile = fopen (friendsFilename, "r")) == NULL)
  {
    if (errno != ENOENT)
      return (BACKUP_SYSTEM_FILES__ERROR_OPENING_FRIENDS_FILE_FOR_READING);
    return (BACKUP_SYSTEM_FILES__NOT_YET_INSTALLED);
  }
  fclose (friendsFile);
  
  if ((errorCode = getLongFilename (DATA_DIR, PARENTS_FILE_NAME, parentsFilename)) != OK)
    return (errorCode);
  if ((parentsFile = fopen (parentsFilename, "r")) == NULL)
  {
    if (errno != ENOENT)
      return (BACKUP_SYSTEM_FILES__ERROR_OPENING_PARENTS_FILE_FOR_READING);
    return (BACKUP_SYSTEM_FILES__NOT_YET_INSTALLED);
  }
  fclose (parentsFile);
  
  snprintf (command, 2*MAX_LENGTH_LONG_FILENAME +11, "mv -f %s %s.old", passwordFilename, passwordFilename);
  system (command);
  snprintf (command, 2*MAX_LENGTH_LONG_FILENAME +11, "mv -f %s %s.old",    usersFilename,    usersFilename);
  system (command);
  snprintf (command, 2*MAX_LENGTH_LONG_FILENAME +11, "mv -f %s %s.old",  friendsFilename,  friendsFilename);
  system (command);
  snprintf (command, 2*MAX_LENGTH_LONG_FILENAME +11, "mv -f %s %s.old",  parentsFilename,  parentsFilename);
  system (command);
  
  if ((errorCode = getLongFilename (DATA_DIR, "*.in", invitationsFilename)) != OK)
    return (errorCode);
  snprintf (command, MAX_LENGTH_LONG_FILENAME +6, "rm -f %s", invitationsFilename);
  system (command);
  
  if ((errorCode = getLongFilename (DATA_DIR, "*.out", invitationsFilename)) != OK)
    return (errorCode);
  snprintf (command, MAX_LENGTH_LONG_FILENAME +6, "rm -f %s", invitationsFilename);
  system (command);
  
  if ((errorCode = getLongFilename (COOKIES_DIR, "*", cookiesFilename)) != OK)
    return (errorCode);
  snprintf (command, MAX_LENGTH_LONG_FILENAME +6, "rm -f %s", cookiesFilename);
  system (command);
 
  return (OK);
}  
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned fillUserData (userDataType *userData, char **argv, char *plainPass)
{
  unsigned errorCode;
  
  if (userData == NULL)
    return (FILL_USER_DATA__NO_USER_DATA);
  if (argv == NULL)
    return (FILL_USER_DATA__NO_ARGV);
    
  if ((!strcmp (argv[1], "--edit")) || (!strcmp (argv[1], "-e")))
  {
    userData->userId = (userIdType) strtoul (argv[2], NULL, 10);
    
    /* Note that, in this case, 'userName', 'plainPass', 'encryptedPass', 'category' and 'next' are not filled */    
    
    stringCopy (userData->name,		      argv[ 3], MAX_LENGTH_NAME);
    stringCopy (userData->email, 	      argv[ 4], MAX_LENGTH_EMAIL);
    stringCopy (userData->homepage,	      argv[ 5], MAX_LENGTH_HOMEPAGE);
    stringCopy (userData->address.street,     argv[ 6], MAX_LENGTH_STREET);
    stringCopy (userData->address.homeNumber, argv[ 7], MAX_LENGTH_HOME_NUMBER);
    stringCopy (userData->address.complement, argv[ 8], MAX_LENGTH_COMPLEMENT);
    stringCopy (userData->address.district,   argv[ 9], MAX_LENGTH_DISTRICT);
    stringCopy (userData->address.city,       argv[10], MAX_LENGTH_CITY);
    stringCopy (userData->address.state,      argv[11], MAX_LENGTH_STATE);
    stringCopy (userData->address.country,    argv[12], MAX_LENGTH_COUNTRY);
    stringCopy (userData->address.zipCode,    argv[13], MAX_LENGTH_ZIP_CODE);
    stringCopy (userData->telNumber, 	      argv[14], MAX_LENGTH_TEL_NUMBER);
    stringCopy (userData->cellNumber, 	      argv[15], MAX_LENGTH_CELL_NUMBER);
    stringCopy (userData->plainPass, 	      "NoPass", MAX_LENGTH_PLAIN_PASS);
    stringCopy (userData->birthday,	      argv[18], LENGTH_DAY_OF_BORN );
    strncat    (userData->birthday,	      argv[19], LENGTH_MONTH_OF_BORN );
    strncat    (userData->birthday,	      argv[20], LENGTH_YEAR_OF_BORN );
    stringCopy (userData->description,	      argv[21], MAX_LENGTH_DESCRIPTION);
    
    #ifdef ENGLISH
      if (!strcmp (argv[16], "male")) 
        userData->gender = male;   
      else if (!strcmp (argv[16], "female")) 
        userData->gender = female;
      else
        userData->gender = notAnswered;
    
      if (!strcmp (argv[17], "single")) 
        userData->relationshipStatus = single;   
      else if (!strcmp (argv[17], "married")) 
        userData->relationshipStatus = married;
      else if (!strcmp (argv[17], "widowed")) 
        userData->relationshipStatus = widowed;
      else
        userData->relationshipStatus = notGiven;
    #elif PORTUGUESE
      if (!strcmp (argv[16], "masculino")) 
        userData->gender = male;   
      else if (!strcmp (argv[16], "feminino")) 
        userData->gender = female;
      else
        userData->gender = notAnswered;
    
      if ((!strcmp (argv[17], "solteiro")) || (!strcmp (argv[17], "solteira")))  
        userData->relationshipStatus = single;   
      else if ((!strcmp (argv[17], "casado")) || (!strcmp (argv[17], "casada")))
        userData->relationshipStatus = married;
      else if ((!strcmp (argv[17], "viuvo")) || (!strcmp (argv[17], "viuva")))
        userData->relationshipStatus = widowed;
      else
        userData->relationshipStatus = notGiven;
    #endif

    return (OK);
  }
  
  if (plainPass == NULL)
    return (FILL_USER_DATA__NO_PLAIN_PASS);
  
     
  if ((!strcmp (argv[1], "--install")) || (!strcmp (argv[1], "-t")))
  {
    userData->userId   = 0;
    userData->category = administrator;
    userData->next     = NULL;
    
    stringCopy (userData->plainPass, plainPass, MAX_LENGTH_PLAIN_PASS);
    if ((errorCode = encodePassword (plainPass, userData->encryptedPass)) != OK)
      return (errorCode);  
    
    stringCopy (userData->userName,	      argv[ 2], MAX_LENGTH_USERNAME);
    stringCopy (userData->name,		      argv[ 3], MAX_LENGTH_NAME);
    stringCopy (userData->email, 	      argv[ 4], MAX_LENGTH_EMAIL);
    stringCopy (userData->homepage,	      argv[ 5], MAX_LENGTH_HOMEPAGE);
    stringCopy (userData->address.street,     argv[ 6], MAX_LENGTH_STREET);
    stringCopy (userData->address.homeNumber, argv[ 7], MAX_LENGTH_HOME_NUMBER);
    stringCopy (userData->address.complement, argv[ 8], MAX_LENGTH_COMPLEMENT);
    stringCopy (userData->address.district,   argv[ 9], MAX_LENGTH_DISTRICT);
    stringCopy (userData->address.city,       argv[10], MAX_LENGTH_CITY);
    stringCopy (userData->address.state,      argv[11], MAX_LENGTH_STATE);
    stringCopy (userData->address.country,    argv[12], MAX_LENGTH_COUNTRY);
    stringCopy (userData->address.zipCode,    argv[13], MAX_LENGTH_ZIP_CODE);
    stringCopy (userData->telNumber, 	      argv[14], MAX_LENGTH_TEL_NUMBER);
    stringCopy (userData->cellNumber, 	      argv[15], MAX_LENGTH_CELL_NUMBER); 
    stringCopy (userData->birthday,	      argv[18], LENGTH_DAY_OF_BORN );
    strncat    (userData->birthday, 	      argv[19], LENGTH_MONTH_OF_BORN );
    strncat    (userData->birthday, 	      argv[20], LENGTH_YEAR_OF_BORN );
    stringCopy (userData->description,	      argv[21], MAX_LENGTH_DESCRIPTION);
    
    #ifdef ENGLISH
      if (!strcmp (argv[16], "male")) 
        userData->gender = male;   
      else if (!strcmp (argv[16], "female")) 
        userData->gender = female;
      else
        userData->gender = notAnswered;
    
      if (!strcmp (argv[17], "single")) 
        userData->relationshipStatus = single;   
      else if (!strcmp (argv[17], "married")) 
        userData->relationshipStatus = married;
      else if (!strcmp (argv[17], "widowed")) 
        userData->relationshipStatus = widowed;
      else
        userData->relationshipStatus = notGiven;
    #elif PORTUGUESE
      if (!strcmp (argv[16], "masculino")) 
        userData->gender = male;   
      else if (!strcmp (argv[16], "feminino")) 
        userData->gender = female;
      else
        userData->gender = notAnswered;
    
      if ((!strcmp (argv[17], "solteiro")) || (!strcmp (argv[17], "solteira")))  
        userData->relationshipStatus = single;   
      else if ((!strcmp (argv[17], "casado")) || (!strcmp (argv[17], "casada")))
        userData->relationshipStatus = married;
      else if ((!strcmp (argv[17], "viuvo")) || (!strcmp (argv[17], "viuva")))
        userData->relationshipStatus = widowed;
      else
        userData->relationshipStatus = notGiven;
    #endif
  }
  
  if ((!strcmp (argv[1], "--add")) || (!strcmp (argv[1], "-a")))
  {
  /* Note that, in this case, we will know the user ID only when putting data in file. */ 
    
    stringCopy (userData->plainPass,         plainPass, MAX_LENGTH_PLAIN_PASS);
    stringCopy (userData->userName,	      argv[ 2], MAX_LENGTH_USERNAME);
    stringCopy (userData->name,		      argv[ 4], MAX_LENGTH_NAME);
    stringCopy (userData->email, 	      argv[ 5], MAX_LENGTH_EMAIL);
    stringCopy (userData->homepage,	      argv[ 6], MAX_LENGTH_HOMEPAGE);
    stringCopy (userData->address.street,     argv[ 7], MAX_LENGTH_STREET);
    stringCopy (userData->address.homeNumber, argv[ 8], MAX_LENGTH_HOME_NUMBER);
    stringCopy (userData->address.complement, argv[ 9], MAX_LENGTH_COMPLEMENT);
    stringCopy (userData->address.district,   argv[10], MAX_LENGTH_DISTRICT);
    stringCopy (userData->address.city,       argv[11], MAX_LENGTH_CITY);
    stringCopy (userData->address.state,      argv[12], MAX_LENGTH_STATE);
    stringCopy (userData->address.country,    argv[13], MAX_LENGTH_COUNTRY);
    stringCopy (userData->address.zipCode,    argv[14], MAX_LENGTH_ZIP_CODE);
    stringCopy (userData->telNumber, 	      argv[15], MAX_LENGTH_TEL_NUMBER);
    stringCopy (userData->cellNumber, 	      argv[16], MAX_LENGTH_CELL_NUMBER);
    stringCopy (userData->birthday,   	      argv[19], LENGTH_DAY_OF_BORN );
    strncat    (userData->birthday,	      argv[20], LENGTH_MONTH_OF_BORN );
    strncat    (userData->birthday,	      argv[21], LENGTH_YEAR_OF_BORN );
    stringCopy (userData->description,        argv[22], MAX_LENGTH_DESCRIPTION);
    
    userData->next = NULL;
    
    #ifdef ENGLISH
      if ((!strcmp (argv[3], "webUser")) || (!strcmp (argv[3], "2")))
        userData->category = webUser;
      else if ((!strcmp (argv[3], "relative")) || (!strcmp (argv[3], "3")))
        userData->category = relative;
      else
        return (FILL_USER_DATA__WRONG_CATEGORY);
    
      if (!strcmp (argv[17], "male")) 
        userData->gender = male;   
      else if (!strcmp (argv[17], "female")) 
        userData->gender = female;
      else
        userData->gender = notAnswered;
    
      if (!strcmp (argv[18], "single")) 
        userData->relationshipStatus = single;   
      else if (!strcmp (argv[18], "married")) 
        userData->relationshipStatus = married;
      else if (!strcmp (argv[18], "widowed")) 
        userData->relationshipStatus = widowed;
      else
        userData->relationshipStatus = notGiven;
    #elif PORTUGUESE
      if ((!strcmp (argv[3], "usuarioWeb")) || (!strcmp (argv[3], "2")))
        userData->category = webUser;
      else if ((!strcmp (argv[3], "parente")) || (!strcmp (argv[3], "3")))
        userData->category = relative;
      else
        return (FILL_USER_DATA__WRONG_CATEGORY);
	
      if (!strcmp (argv[17], "masculino")) 
        userData->gender = male;   
      else if (!strcmp (argv[17], "feminino")) 
        userData->gender = female;
      else
        userData->gender = notAnswered;
    
      if ((!strcmp (argv[18], "solteiro")) || (!strcmp (argv[18], "solteira")))  
        userData->relationshipStatus = single;   
      else if ((!strcmp (argv[18], "casado")) || (!strcmp (argv[18], "casada")))
        userData->relationshipStatus = married;
      else if ((!strcmp (argv[18], "viuvo")) || (!strcmp (argv[18], "viuva")))
        userData->relationshipStatus = widowed;
      else
        userData->relationshipStatus = notGiven;
    #endif
    
    if (userData->category == webUser)
      if ((errorCode = encodePassword (plainPass, userData->encryptedPass)) != OK)
        return (errorCode);
    if (userData->category == relative)
      userData->encryptedPass[0] = EOS;
  }
    
  return (OK);
}  
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned copyUserData (userDataType * userDataOut, userDataType * userDataIn)
{
  if (! userDataIn )
    return ( COPY_USER_DATA__DATA_IN_INVAL );
  if (! userDataOut )
    return ( COPY_USER_DATA__DATA_OUT_INVAL );
  
  userDataOut->userId		  = userDataIn->userId; 
  userDataOut->category		  = userDataIn->category;     
  userDataOut->gender		  = userDataIn->gender; 
  userDataOut->relationshipStatus = userDataIn->relationshipStatus; 
  userDataOut->next		  = userDataIn->next;
  
  stringCopy (userDataOut->plainPass,	       userDataIn->plainPass,	       MAX_LENGTH_PLAIN_PASS);
  stringCopy (userDataOut->encryptedPass,      userDataIn->encryptedPass,      ENCRYPTED_PASS_LENGTH);
  stringCopy (userDataOut->userName,	       userDataIn->userName,	       MAX_LENGTH_USERNAME);
  stringCopy (userDataOut->name, 	       userDataIn->name,	       MAX_LENGTH_NAME);
  stringCopy (userDataOut->email,	       userDataIn->email,	       MAX_LENGTH_EMAIL);
  stringCopy (userDataOut->homepage,	       userDataIn->homepage,	       MAX_LENGTH_HOMEPAGE);
  stringCopy (userDataOut->address.street,     userDataIn->address.street,     MAX_LENGTH_STREET);
  stringCopy (userDataOut->address.homeNumber, userDataIn->address.homeNumber, MAX_LENGTH_HOME_NUMBER);
  stringCopy (userDataOut->address.complement, userDataIn->address.complement, MAX_LENGTH_COMPLEMENT);
  stringCopy (userDataOut->address.district,   userDataIn->address.district,   MAX_LENGTH_DISTRICT);
  stringCopy (userDataOut->address.city,       userDataIn->address.city,       MAX_LENGTH_CITY);
  stringCopy (userDataOut->address.state,      userDataIn->address.state,      MAX_LENGTH_STATE);
  stringCopy (userDataOut->address.country,    userDataIn->address.country,    MAX_LENGTH_COUNTRY);
  stringCopy (userDataOut->address.zipCode,    userDataIn->address.zipCode,    MAX_LENGTH_ZIP_CODE);
  stringCopy (userDataOut->telNumber, 	       userDataIn->telNumber,	       MAX_LENGTH_TEL_NUMBER);
  stringCopy (userDataOut->cellNumber, 	       userDataIn->cellNumber,	       MAX_LENGTH_CELL_NUMBER);
  stringCopy (userDataOut->birthday,   	       userDataIn->birthday,	       MAX_LENGTH_BIRTHDAY);  
  stringCopy (userDataOut->description,        userDataIn->description,	       MAX_LENGTH_DESCRIPTION);
  
  return ( OK );
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned getDataFromId (userIdType id, userDataType * userData)
{
  unsigned retCode  = 0;
  unsigned retCode2 = 0;
  char usersFileName [MAX_LENGTH_LONG_FILENAME+1];
  char passwordFileName [MAX_LENGTH_LONG_FILENAME+1];
  boolean found;
  userDataType buffer;
  FILE * readFile, * readFile2;

  if (userData == NULL)
    return (GET_DATA_FROM_ID__USER_DATA_INVAL);
  
  if (( retCode = getLongFilename ( DATA_DIR , USERS_FILE_NAME , usersFileName )) != OK )
    return (retCode);
    
  if (!(readFile = fopen ( usersFileName , "r" )))
  {
    if (errno != ENOENT)
      return ( GET_DATA_FROM_ID__ERROR_OPENING_USERS_FILE_FOR_READING );
    return ( GET_DATA_FROM_ID__USERS_FILE_DOES_NOT_EXIST );
  }
  
  buffer.next = userData->next;
  
  for( retCode = 0, found = false ; (retCode != GET_USER_ID__END_OF_FILE) && (!found) ; )  
  {
    if (( retCode = getUserData ( readFile , USERS_FILE_NAME , &buffer )) != OK )
      if (retCode != GET_USER_ID__END_OF_FILE)
      {
        fclose ( readFile );
        return ( retCode );
      }
    
    if ( retCode != GET_USER_ID__END_OF_FILE )
      if ( id == (buffer.userId))
      {
        if ((retCode2 = copyUserData (userData, &buffer)) != OK)
	{
	  fclose( readFile );
	  return (retCode2);
	}
	found = true;
      }               
  }
  
  fclose( readFile );
  
  if (!found)
    return (GET_DATA_FROM_ID__USER_NOT_FOUND);

  if (( retCode = getLongFilename ( DATA_DIR , PASSWORD_FILE_NAME , passwordFileName )) != OK )
    return (retCode);  
    
  if (!(readFile2 = fopen ( passwordFileName , "r" )))
  {
    if (errno != ENOENT)
      return ( GET_DATA_FROM_ID__ERROR_OPENING_PASSWORD_FILE_FOR_READING );
    return ( GET_DATA_FROM_ID__PASSWORD_FILE_DOES_NOT_EXIST );
  }   
  
  for( retCode = 0; retCode != GET_USER_ID__END_OF_FILE; )  
  { 
    if (( retCode = getUserData ( readFile2 , PASSWORD_FILE_NAME , &buffer )) != OK )
      if (retCode != GET_USER_ID__END_OF_FILE)
      {
        fclose ( readFile2 );
        return ( retCode );
      }
    if ( retCode != GET_USER_ID__END_OF_FILE )
    {        
      if ( id == (buffer.userId))
      {
        if ((retCode2 = copyUserData (userData, &buffer)) != OK)
	{
	  fclose( readFile2 );
	  return (retCode2);
	} 
	fclose( readFile2 );
	return( OK );
      }
    }            
  } 
  fclose ( readFile2 );
  return ( OK );   
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned getDataFromUsername (char *username, userDataType * userData)
{
  unsigned retCode  = 0;
  unsigned retCode2 = 0;
  char usersFileName [MAX_LENGTH_LONG_FILENAME+1];
  char passwordFileName [MAX_LENGTH_LONG_FILENAME+1];
  boolean found;
  userDataType buffer;
  FILE * readFile, * readFile2;

  if (username == NULL)
    return (GET_DATA_FROM_USERNAME__NO_USERNAME);
  
  if (userData == NULL)
    return (GET_DATA_FROM_USERNAME__NO_USER_DATA);

  if (( retCode = getLongFilename ( DATA_DIR , PASSWORD_FILE_NAME , passwordFileName )) != OK )
    return (retCode);  
    
  if (!(readFile2 = fopen ( passwordFileName , "r" )))
  {
    if (errno != ENOENT)
      return ( GET_DATA_FROM_USERNAME__ERROR_OPENING_PASSWORD_FILE_FOR_READING );
    return ( GET_DATA_FROM_USERNAME__PASSWORD_FILE_DOES_NOT_EXIST );
  }   
  
  buffer.next = userData->next;
  
  for (retCode = 0, found = false; (retCode != GET_USER_ID__END_OF_FILE) && (!found); )  
  { 
    if (( retCode = getUserData ( readFile2 , PASSWORD_FILE_NAME , &buffer )) != OK )
      if (retCode != GET_USER_ID__END_OF_FILE)
      {
        fclose ( readFile2 );
        return ( retCode );
      }
    if ( retCode != GET_USER_ID__END_OF_FILE )
    {        
      if (!strcmp (username, buffer.userName))
      {
        if ((retCode2 = copyUserData (userData, &buffer)) != OK)
	{
	  fclose( readFile2 );
	  return (retCode2);
	} 
	found = true;
      }
    }            
  } 
  fclose ( readFile2 );
  
  if (!found)
    return (GET_DATA_FROM_USERNAME__USER_NOT_FOUND);
  
  if (( retCode = getLongFilename ( DATA_DIR , USERS_FILE_NAME , usersFileName )) != OK )
    return (retCode);
    
  if (!(readFile = fopen ( usersFileName , "r" )))
  {
    if (errno != ENOENT)
      return ( GET_DATA_FROM_USERNAME__ERROR_OPENING_USERS_FILE_FOR_READING );
    return ( GET_DATA_FROM_USERNAME__USERS_FILE_DOES_NOT_EXIST );
  }
  
  for( retCode = 0; retCode != GET_USER_ID__END_OF_FILE; )  
  {
    if (( retCode = getUserData ( readFile , USERS_FILE_NAME , &buffer )) != OK )
      if (retCode != GET_USER_ID__END_OF_FILE)
      {
        fclose ( readFile );
        return ( retCode );
      }
    
    if ( retCode != GET_USER_ID__END_OF_FILE )
      if ( userData->userId == buffer.userId)
      {
        if ((retCode2 = copyUserData (userData, &buffer)) != OK)
	{
	  fclose( readFile );
	  return (retCode2);
	}
	fclose (readFile);
	return (OK);
      }               
  }
  fclose( readFile );
  return ( OK );   
}
/*---------------------------------------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------------------------------------*/
unsigned insertFIFO ( userDataType ** first, userDataType ** last, userDataType * newElementData )
{
  userDataType * newElement;  
  unsigned retCode;
  
  if ( !newElementData )
    return ( INSERT_FIFO__INVALID_NEW_ELEMENT );
  
  if ( !( newElement = ( userDataType * ) malloc ( sizeof ( userDataType ) ) ) )
    return ( INSERT_FIFO__ERROR_ALLOCATING_MEMMORY );
  
  if ( ( retCode = copyUserData ( newElement , newElementData ) ) != OK )
    return ( retCode );  
    
  if ( !(*last) ) /*The FIFO pile is empty*/
  {
     (*first) = newElement;
     (*last) = newElement;
     newElement->next = NULL;
     return ( OK );
  } 
  
  (*last)->next = newElement;
  newElement->next = NULL;
  (*last) = newElement;
  return ( OK );
}    
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned retrieveFIFO ( userDataType ** first, userDataType ** last, userDataType * elementData )
{  
  unsigned retCode;
  
  if ( !elementData )
    return ( RETRIEVE_FIFO__INVALID_ELEMENT_DATA );
  
  if ( !(*first) ) /*The FIFO pile is empty*/
     return ( RETRIEVE_FIFO__EMPTY_FIFO );   
  
  if ( ( retCode = copyUserData ( elementData , (*first) ) ) != OK )
    return ( retCode );
  
  (*first) = (*first)->next;
  if (! (*first))
    (*last) = NULL;
  
  return ( OK );
}    
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
void freeFIFOResources ( userDataType ** first , userDataType ** last )
{
  while ( (*first) != NULL )
  {
    (* last ) = (* first );
    (* first ) = (* first )->next;
    free (* last );
  }  
  (* last) = NULL;
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
void insertInFamilyList (familyTreeType **newFamily, familyTreeType **first)
{  
  familyTreeType *cursor;
  
  if (*first == NULL)
  {
    *first = *newFamily;
    (**newFamily).next = NULL;
  } 
  else
  {
    for (cursor = *first; cursor->next != NULL; cursor = cursor->next);
    cursor->next = *newFamily;
    (**newFamily).next = NULL;
  }
}    
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
familyTreeType *retrieveFamily (familyTreeType **first)
{  
  familyTreeType *returnedFamily;
  
  if (*first == NULL)
    return (NULL);
    
  returnedFamily = *first;
  
  (*first) = (**first).next;
  
  return (returnedFamily);
}    
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned verifyIfCookieFileExist (char *username, char *id)
{
  unsigned errorCode;
  char passwordFilename[MAX_LENGTH_LONG_FILENAME +1];
  char   cookieFilename[MAX_LENGTH_LONG_FILENAME +1];
  FILE *passwordFile, *cookieFile;
  boolean found;
  userDataType buffer;
  
  if (username == NULL)
    return (VERIFY_IF_COOKIE_FILE_EXIST__NO_USERNAME);
    
    if (id == NULL)
    return (VERIFY_IF_COOKIE_FILE_EXIST__NO_ID);
  
  if ((errorCode = getLongFilename (DATA_DIR, PASSWORD_FILE_NAME, passwordFilename)) != OK)
    return (errorCode); 
  
  if ((passwordFile = fopen (passwordFilename, "r")) == NULL)
  {
    if (errno != ENOENT)
      return (VERIFY_IF_COOKIE_FILE_EXIST__ERROR_OPENING_PASSWORD_FILE_FOR_READING);
    return (VERIFY_IF_COOKIE_FILE_EXIST__PASSWORD_FILE_DOES_NOT_EXIST);
  }
    
  for (errorCode = 0, found = false; (errorCode != GET_USER_ID__END_OF_FILE) && (!found);)  
  {
    if ((errorCode = getUserData (passwordFile, PASSWORD_FILE_NAME, &buffer)) != OK)
      if (errorCode != GET_USER_ID__END_OF_FILE)
      {
        fclose (passwordFile);
        return (errorCode);
      }
    if (errorCode != GET_USER_ID__END_OF_FILE)
      if (!strcmp (username, buffer.userName))
      {
	sprintf (id, "%020llu", buffer.userId);
	found = true;
      }               
  }
  fclose (passwordFile);
  
  if (!found)
    return (VERIFY_IF_COOKIE_FILE_EXIST__USERNAME_NOT_FOUND);
  
  if ((errorCode = getLongFilename (COOKIES_DIR, id, cookieFilename)) != OK)
    return (errorCode); 
  
  if ((cookieFile = fopen (cookieFilename, "r")) == NULL)
  {
    if (errno != ENOENT)
      return (VERIFY_IF_COOKIE_FILE_EXIST__ERROR_OPENING_COOKIE_FILE_FOR_READING);
    return (VERIFY_IF_COOKIE_FILE_EXIST__COOKIE_FILE_DOES_NOT_EXIST);
  }
  fclose (cookieFile);
  
  return (OK);     
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned getCookieValue (char *cookieName, char *cookieValue)
{
  FILE *cookieFile;
  unsigned errorCode;
  char cookieFilename[MAX_LENGTH_LONG_FILENAME +1];
  
  if (cookieName == NULL)
    return (GET_COOKIE_VALUE__NO_COOKIE_NAME);
  if (cookieValue == NULL)
    return (GET_COOKIE_VALUE__NO_COOKIE_VALUE);
    
  if ((errorCode = getLongFilename (COOKIES_DIR, cookieName, cookieFilename)) != OK)
    return (errorCode); 
  
  if ((cookieFile = fopen (cookieFilename, "r")) == NULL)
  {
    if (errno != ENOENT)
      return (GET_COOKIE_VALUE__ERROR_OPENING_COOKIE_FILE_FOR_READING);
    return (GET_COOKIE_VALUE__COOKIE_FILE_DOES_NOT_EXIST);
  }
    
  if ((errorCode = getString (cookieFile, COOKIE_VALUE_LENGTH, COOKIE_VALUE_LENGTH, cookieValue)) != OK)
    return (errorCode);
  fclose (cookieFile);
  
  return (OK);
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned createNewCookieFile (char *cookieName, char *cookieValue, time_t cookieExpiration, char *ip)
{
  FILE *cookieFile;
  unsigned errorCode;
  char cookieFilename[MAX_LENGTH_LONG_FILENAME +1];
  
  if (cookieName == NULL)
    return (CREATE_NEW_COOKIE_FILE__NO_COOKIE_NAME);
  if (cookieValue == NULL)
    return (CREATE_NEW_COOKIE_FILE__NO_COOKIE_VALUE);
  if (ip == NULL)
    return (CREATE_NEW_COOKIE_FILE__NO_IP);
    
  if ((errorCode = getLongFilename (COOKIES_DIR, cookieName, cookieFilename)) != OK)
    return (errorCode); 
  
  if ((cookieFile = fopen (cookieFilename, "w")) == NULL)
    return (CREATE_NEW_COOKIE_FILE__ERROR_OPENING_COOKIE_FILE_FOR_WRITING);

  if ((errorCode = putString (cookieFile, COOKIE_VALUE_LENGTH, COOKIE_VALUE_LENGTH, cookieValue)) != OK)
  {
    fclose (cookieFile);
    return (errorCode);
  }
   
  if ((fwrite (&cookieExpiration, sizeof (time_t), 1, cookieFile)) != 1)
  {
    fclose (cookieFile);
    if (ferror (cookieFile))
      return (CREATE_NEW_COOKIE_FILE__ERROR_WRITING_EXPIRATION_IN_COOKIE_FILE);
    return (CREATE_NEW_COOKIE_FILE__END_OF_COOKIE_FILE);
  }
  
  if ((errorCode = putString (cookieFile, MIN_LENGTH_IP, MAX_LENGTH_IP, ip)) != OK)
  {
    fclose (cookieFile);
    return (errorCode);
  }
    
  fclose (cookieFile);
  
  return (OK);
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned validateCookie (char *cookieName, char *cookieValue, char *ip)
{
  unsigned errorCode;
  char cookieFilename[MAX_LENGTH_LONG_FILENAME +1];
  char cookieValueInFile[COOKIE_VALUE_LENGTH +1];
  char ipInFile[MAX_LENGTH_IP +1];
  time_t cookieExpiration;
  FILE *cookieFile;
  
  if (cookieName == NULL)
    return (VALIDATE_COOKIE__NO_COOKIE_NAME);
  if (cookieValue == NULL)
    return (VALIDATE_COOKIE__NO_COOKIE_VALUE);
  if (ip == NULL)
    return (VALIDATE_COOKIE__NO_IP);
  
  if ((errorCode = getLongFilename (COOKIES_DIR, cookieName, cookieFilename)) != OK)
    return (errorCode); 
  
  if ((cookieFile = fopen (cookieFilename, "r")) == NULL)
  {
    if (errno != ENOENT)
      return (VALIDATE_COOKIE__ERROR_OPENING_COOKIE_FILE_FOR_READING);
    return (VALIDATE_COOKIE__COOKIE_FILE_DOES_NOT_EXIST);
  }
  
  if ((errorCode = getString (cookieFile, COOKIE_VALUE_LENGTH, COOKIE_VALUE_LENGTH, cookieValueInFile)) != OK)
  {
    fclose (cookieFile);
    return (errorCode);
  }
  if (strcmp (cookieValue, cookieValueInFile))
  {
    fclose (cookieFile);
    return (VALIDATE_COOKIE__WRONG_COOKIE_VALUE);
  }
   
  if ((fread (&cookieExpiration, sizeof (time_t), 1, cookieFile)) != 1)
  {
    fclose (cookieFile);
    if (ferror (cookieFile))
      return (VALIDATE_COOKIE__ERROR_READING_EXPIRATION_IN_COOKIE_FILE);
    return (VALIDATE_COOKIE__END_OF_COOKIE_FILE);
  }
  if (cookieExpiration < time (NULL))
  {
    fclose (cookieFile);
    return (VALIDATE_COOKIE__COOKIE_HAS_EXPIRED);
  }
  
  if ((errorCode = getString (cookieFile, MIN_LENGTH_IP, MAX_LENGTH_IP, ipInFile)) != OK)
  {
    fclose (cookieFile);
    return (errorCode);
  }
  if (strcmp (ip, ipInFile))
  {
    fclose (cookieFile);
    return (VALIDATE_COOKIE__WRONG_IP);
  }
  
  fclose (cookieFile);
  
  return (OK);     
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned autenticateUser (char *username, char *plainPass)
{
  unsigned errorCode, errorCode2;
  char passwordFilename[MAX_LENGTH_LONG_FILENAME +1];
  FILE *passwordFile;
  userDataType buffer;

  if (username == NULL)
    return (AUTENTICATE_USER__NO_USERNAME);
    
  if (plainPass == NULL)
    return (AUTENTICATE_USER__NO_PLAIN_PASS);
  
  if ((errorCode = getLongFilename (DATA_DIR, PASSWORD_FILE_NAME, passwordFilename)) != OK)
    return (errorCode); 
  
  if ((passwordFile = fopen (passwordFilename, "r")) == NULL)
  {
    if (errno != ENOENT)
      return (AUTENTICATE_USER__ERROR_OPENING_PASSWORD_FILE_FOR_READING);
    return (AUTENTICATE_USER__PASSWORD_FILE_DOES_NOT_EXIST);
  }
    
  for (errorCode = 0; errorCode != GET_USER_ID__END_OF_FILE;)  
  {
    if ((errorCode = getUserData (passwordFile, PASSWORD_FILE_NAME, &buffer)) != OK)
      if (errorCode != GET_USER_ID__END_OF_FILE)
      {
        fclose (passwordFile);
        return (errorCode);
      }
    if (errorCode != GET_USER_ID__END_OF_FILE)
      if (!strcmp (username, buffer.userName))
      {
        fclose (passwordFile);
        if ((errorCode2 = checkPassword (buffer.encryptedPass, plainPass)) != OK)
	      return (errorCode2);
	    return (OK);
      }
  }
  fclose (passwordFile);
  
  return (AUTENTICATE_USER__USERNAME_NOT_FOUND);
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
void printInMiddle (WINDOW *win, int starty, int startx, int width, char *title, chtype color)
{	
  int x, y;
  float temp;

  if (win == NULL)
    win = stdscr;
  getyx (win, y, x);
  if (startx != 0)
	x = startx;
  if (starty != 0)
	y = starty;
  if (width == 0)
	width = 80;

  temp = (width - strlen (title))/ 2;
  x = startx + (int) temp;
  wattron (win, color);
  mvwprintw (win, y, x, "%s", title);
  wattroff (win, color);
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned freeMenuItemsResources (ITEM **menuItems)
{
  unsigned index;
  
  for (index = 0; index < NCURSES__NB_MENU_OPTIONS; index++)
    if (free_item (menuItems[index]) != OK)
      return (NCURSES__ERROR_FREEING_MEMORY_ALLOCATED_TO_MENU_ITEMS);
  
  return (OK);	
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned freeFormFieldsResources (FIELD **formFields)
{
  unsigned index;
  
  for (index = 0; formFields[index] != NULL; index++)
    if (free_field (formFields[index]) != OK)
      return (NCURSES__ERROR_FREEING_MEMORY_ALLOCATED_TO_FORM_FIELDS);
  
  return (OK);	
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned freeMenuResources (MENU *menu, ITEM **menuItems)
{
  unsigned errorCode;
  
  if (free_menu (menu) != OK)
    return (NCURSES__ERROR_FREEING_MEMORY_ALLOCATED_TO_MENU);
  if ((errorCode = freeMenuItemsResources (menuItems)) != OK)
    return (errorCode); 

  return (OK);	
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned freeFormResources (FORM *form, FIELD **formFields)
{
  unsigned errorCode;
  
  if (free_form (form) != OK)
    return (NCURSES__ERROR_FREEING_MEMORY_ALLOCATED_TO_FORM);
  if ((errorCode = freeFormFieldsResources (formFields)) != OK)
    return (errorCode); 

  return (OK);	
}
/*---------------------------------------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------------------------------------*/
FIELD **createFormFields (char option)
{
  FIELD **formFields;
  unsigned index;

  switch (option)
  {
    case 't':
      formFields = (FIELD **) calloc (NB_ARGS_OF_REINSTALL_OPTION +1, sizeof (FIELD *));
      if ((formFields[0] = new_field (FIELD_HEIGHT, MAX_LENGTH_USERNAME, FIELD_START_Y, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[1] = new_field (FIELD_HEIGHT, MAX_LENGTH_PLAIN_PASS, FIELD_START_Y +1, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[2] = new_field (FIELD_HEIGHT, MAX_FIELD_WIDTH, FIELD_START_Y +2, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[3] = new_field (FIELD_HEIGHT, MAX_FIELD_WIDTH, FIELD_START_Y +3, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[4] = new_field (FIELD_HEIGHT, MAX_FIELD_WIDTH, FIELD_START_Y +4, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[5] = new_field (FIELD_HEIGHT, MAX_FIELD_WIDTH, FIELD_START_Y +5, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[6] = new_field (FIELD_HEIGHT, MAX_LENGTH_HOME_NUMBER, FIELD_START_Y +6, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[7] = new_field (FIELD_HEIGHT, MAX_LENGTH_COMPLEMENT, FIELD_START_Y +7, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[8] = new_field (FIELD_HEIGHT, MAX_FIELD_WIDTH, FIELD_START_Y +8, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[9] = new_field (FIELD_HEIGHT, MAX_FIELD_WIDTH, FIELD_START_Y +9, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[10] = new_field (FIELD_HEIGHT, MAX_FIELD_WIDTH, FIELD_START_Y +10, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[11] = new_field (FIELD_HEIGHT, MAX_FIELD_WIDTH, FIELD_START_Y +11, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[12] = new_field (FIELD_HEIGHT, MAX_LENGTH_ZIP_CODE, FIELD_START_Y +12, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[13] = new_field (FIELD_HEIGHT, MAX_LENGTH_TEL_NUMBER, FIELD_START_Y +13, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[14] = new_field (FIELD_HEIGHT, MAX_LENGTH_CELL_NUMBER, FIELD_START_Y +14, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[15] = new_field (FIELD_HEIGHT, 15, FIELD_START_Y +15, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[16] = new_field (FIELD_HEIGHT, 15, FIELD_START_Y +16, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[17] = new_field (FIELD_HEIGHT, LENGTH_DAY_OF_BORN, FIELD_START_Y +17, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[18] = new_field (FIELD_HEIGHT, LENGTH_MONTH_OF_BORN, FIELD_START_Y +18, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[19] = new_field (FIELD_HEIGHT, LENGTH_YEAR_OF_BORN, FIELD_START_Y +19, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[20] = new_field (FIELD_HEIGHT, MAX_FIELD_WIDTH, FIELD_START_Y +20, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      formFields[NB_ARGS_OF_REINSTALL_OPTION] = NULL;
      
      for (index = 0; index < NB_ARGS_OF_REINSTALL_OPTION; index++)
      {
       set_field_back (formFields[index], A_UNDERLINE);
       set_field_fore (formFields[index], COLOR_PAIR(3));
       set_field_pad  (formFields[index], '_');
       field_opts_off (formFields[index], O_AUTOSKIP);
      }
      field_opts_off (formFields[1], O_PUBLIC);
    break;

    case 'a':
      formFields = (FIELD **) calloc (NB_ARGS_OF_ADD_OPTION +2, sizeof (FIELD *));
      if ((formFields[0] = new_field (FIELD_HEIGHT, MAX_LENGTH_USERNAME, FIELD_START_Y, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[1] = new_field (FIELD_HEIGHT, MAX_LENGTH_PLAIN_PASS, FIELD_START_Y +1, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[2] = new_field (FIELD_HEIGHT, 15, FIELD_START_Y +2, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[3] = new_field (FIELD_HEIGHT, MAX_FIELD_WIDTH, FIELD_START_Y +3, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[4] = new_field (FIELD_HEIGHT, MAX_FIELD_WIDTH, FIELD_START_Y +4, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[5] = new_field (FIELD_HEIGHT, MAX_FIELD_WIDTH, FIELD_START_Y +5, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[6] = new_field (FIELD_HEIGHT, MAX_FIELD_WIDTH, FIELD_START_Y +6, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[7] = new_field (FIELD_HEIGHT, MAX_LENGTH_HOME_NUMBER, FIELD_START_Y +7, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[8] = new_field (FIELD_HEIGHT, MAX_LENGTH_COMPLEMENT, FIELD_START_Y +8, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[9] = new_field (FIELD_HEIGHT, MAX_FIELD_WIDTH, FIELD_START_Y +9, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[10] = new_field (FIELD_HEIGHT, MAX_FIELD_WIDTH, FIELD_START_Y +10, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[11] = new_field (FIELD_HEIGHT, MAX_FIELD_WIDTH, FIELD_START_Y +11, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[12] = new_field (FIELD_HEIGHT, MAX_FIELD_WIDTH, FIELD_START_Y +12, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[13] = new_field (FIELD_HEIGHT, MAX_LENGTH_ZIP_CODE, FIELD_START_Y +13, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[14] = new_field (FIELD_HEIGHT, MAX_LENGTH_TEL_NUMBER, FIELD_START_Y +14, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[15] = new_field (FIELD_HEIGHT, MAX_LENGTH_CELL_NUMBER, FIELD_START_Y +15, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[16] = new_field (FIELD_HEIGHT, 15, FIELD_START_Y +16, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[17] = new_field (FIELD_HEIGHT, 15, FIELD_START_Y +17, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[18] = new_field (FIELD_HEIGHT, LENGTH_DAY_OF_BORN, FIELD_START_Y +18, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[19] = new_field (FIELD_HEIGHT, LENGTH_MONTH_OF_BORN, FIELD_START_Y +19, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[20] = new_field (FIELD_HEIGHT, LENGTH_YEAR_OF_BORN, FIELD_START_Y +20, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[21] = new_field (FIELD_HEIGHT, MAX_FIELD_WIDTH, FIELD_START_Y +21, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      formFields[NB_ARGS_OF_ADD_OPTION +1] = NULL;

      for (index = 0; index < (NB_ARGS_OF_ADD_OPTION +1); index++)
      {
       set_field_back (formFields[index], A_UNDERLINE);
       set_field_fore (formFields[index], COLOR_PAIR(3));
       set_field_pad  (formFields[index], '_');
       field_opts_off (formFields[index], O_AUTOSKIP);
      }
      field_opts_off (formFields[1], O_PUBLIC);
    break;

    case 'e':
      formFields = (FIELD **) calloc (NB_ARGS_OF_EDIT_OPTION , sizeof (FIELD *));

      if ((formFields[0] = new_field (FIELD_HEIGHT, MAX_FIELD_WIDTH, FIELD_START_Y   , FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[1] = new_field (FIELD_HEIGHT, MAX_FIELD_WIDTH, FIELD_START_Y +1, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[2] = new_field (FIELD_HEIGHT, MAX_FIELD_WIDTH, FIELD_START_Y +2, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[3] = new_field (FIELD_HEIGHT, MAX_FIELD_WIDTH, FIELD_START_Y +3, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[4] = new_field (FIELD_HEIGHT, MAX_LENGTH_HOME_NUMBER, FIELD_START_Y +4, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[5] = new_field (FIELD_HEIGHT, MAX_LENGTH_COMPLEMENT, FIELD_START_Y +5, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[6] = new_field (FIELD_HEIGHT, MAX_FIELD_WIDTH, FIELD_START_Y +6, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[7] = new_field (FIELD_HEIGHT, MAX_FIELD_WIDTH, FIELD_START_Y +7, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[8] = new_field (FIELD_HEIGHT, MAX_FIELD_WIDTH, FIELD_START_Y +8, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[9] = new_field (FIELD_HEIGHT, MAX_FIELD_WIDTH, FIELD_START_Y +9, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[10] = new_field (FIELD_HEIGHT, MAX_LENGTH_ZIP_CODE, FIELD_START_Y +10, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[11] = new_field (FIELD_HEIGHT, MAX_LENGTH_TEL_NUMBER, FIELD_START_Y +11, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[12] = new_field (FIELD_HEIGHT, MAX_LENGTH_CELL_NUMBER, FIELD_START_Y +12, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[13] = new_field (FIELD_HEIGHT, 15, FIELD_START_Y +13, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[14] = new_field (FIELD_HEIGHT, 15, FIELD_START_Y +14, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[15] = new_field (FIELD_HEIGHT, LENGTH_DAY_OF_BORN, FIELD_START_Y +15, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[16] = new_field (FIELD_HEIGHT, LENGTH_MONTH_OF_BORN, FIELD_START_Y +16, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[17] = new_field (FIELD_HEIGHT, LENGTH_YEAR_OF_BORN, FIELD_START_Y +17, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[18] = new_field (FIELD_HEIGHT, MAX_FIELD_WIDTH, FIELD_START_Y +18, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      formFields[NB_ARGS_OF_EDIT_OPTION-1] = NULL;
      
      for (index = 0; index < NB_ARGS_OF_EDIT_OPTION -1; index++)
      {
       set_field_back (formFields[index], A_UNDERLINE);
       set_field_fore (formFields[index], COLOR_PAIR(3));
       set_field_pad  (formFields[index], '_');
       field_opts_off (formFields[index], O_AUTOSKIP);
      }
    break;

    case 'r':

    break;

    case 'i':
      formFields = (FIELD **) calloc (NB_ARGS_OF_INVITE_USER_OPTION , sizeof (FIELD *));

      if ((formFields[0] = new_field (FIELD_HEIGHT, 20, FIELD_START_Y +3, FIELD_START_X +7, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[1] = new_field (FIELD_HEIGHT, MAX_FIELD_WIDTH, FIELD_START_Y +4, FIELD_START_X +7, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[2] = new_field (FIELD_HEIGHT, MAX_FIELD_WIDTH, FIELD_START_Y +5, FIELD_START_X +7, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      formFields[NB_ARGS_OF_INVITE_USER_OPTION] = NULL;
      
      for (index = 0; index < NB_ARGS_OF_INVITE_USER_OPTION; index++)
      {
       set_field_back (formFields[index], A_UNDERLINE);
       set_field_fore (formFields[index], COLOR_PAIR(3));
       set_field_pad  (formFields[index], '_');
       field_opts_off (formFields[index], O_AUTOSKIP);
      }
    break;

    case 'I':
      formFields = (FIELD **) calloc (NB_ARGS_OF_INVITE_FRIEND_OPTION , sizeof (FIELD *));

      if ((formFields[0] = new_field (FIELD_HEIGHT, 20, FIELD_START_Y +7, FIELD_START_X +20, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[1] = new_field (FIELD_HEIGHT, 20, FIELD_START_Y +8, FIELD_START_X +20, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      formFields[NB_ARGS_OF_INVITE_FRIEND_OPTION] = NULL;
      
      for (index = 0; index < NB_ARGS_OF_INVITE_FRIEND_OPTION; index++)
      {
       set_field_back (formFields[index], A_UNDERLINE);
       set_field_fore (formFields[index], COLOR_PAIR(3));
       set_field_pad  (formFields[index], '_');
       field_opts_off (formFields[index], O_AUTOSKIP);
      }
    break;

    case 'F':

    break;

    case 'P':
      formFields = (FIELD **) calloc (NB_ARGS_OF_ACCEPT_OPTION , sizeof (FIELD *));

      if ((formFields[0] = new_field (FIELD_HEIGHT, 20, FIELD_START_Y +7, FIELD_START_X +28, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[1] = new_field (FIELD_HEIGHT, 20, FIELD_START_Y +8, FIELD_START_X +28, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      formFields[NB_ARGS_OF_ACCEPT_OPTION] = NULL;
      
      for (index = 0; index < NB_ARGS_OF_ACCEPT_OPTION; index++)
      {
       set_field_back (formFields[index], A_UNDERLINE);
       set_field_fore (formFields[index], COLOR_PAIR(3));
       set_field_pad  (formFields[index], '_');
       field_opts_off (formFields[index], O_AUTOSKIP);
      }
    break;

    case 'J':
      formFields = (FIELD **) calloc (NB_ARGS_OF_REJECT_OPTION , sizeof (FIELD *));

      if ((formFields[0] = new_field (FIELD_HEIGHT, 20, FIELD_START_Y +7, FIELD_START_X +28, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[1] = new_field (FIELD_HEIGHT, 20, FIELD_START_Y +8, FIELD_START_X +28, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      formFields[NB_ARGS_OF_REJECT_OPTION] = NULL;
      
      for (index = 0; index < NB_ARGS_OF_REJECT_OPTION; index++)
      {
       set_field_back (formFields[index], A_UNDERLINE);
       set_field_fore (formFields[index], COLOR_PAIR(3));
       set_field_pad  (formFields[index], '_');
       field_opts_off (formFields[index], O_AUTOSKIP);
      }
    break;

    case 'X':
      formFields = (FIELD **) calloc (NB_ARGS_OF_EXCLUDE_OPTION , sizeof (FIELD *));

      if ((formFields[0] = new_field (FIELD_HEIGHT, 20, FIELD_START_Y +7, FIELD_START_X +28, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[1] = new_field (FIELD_HEIGHT, 20, FIELD_START_Y +8, FIELD_START_X +28, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      formFields[NB_ARGS_OF_EXCLUDE_OPTION] = NULL;
      
      for (index = 0; index < NB_ARGS_OF_EXCLUDE_OPTION; index++)
      {
       set_field_back (formFields[index], A_UNDERLINE);
       set_field_fore (formFields[index], COLOR_PAIR(3));
       set_field_pad  (formFields[index], '_');
       field_opts_off (formFields[index], O_AUTOSKIP);
      }
    break;

    case 'G':

    break;

    case 'c':
      formFields = (FIELD **) calloc (NB_ARGS_OF_CHANGE_CATEGORY_OPTION +1, sizeof (FIELD *));
      if ((formFields[0] = new_field (FIELD_HEIGHT, 20, FIELD_START_Y +6, FIELD_START_X, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      formFields[NB_ARGS_OF_CHANGE_CATEGORY_OPTION] = NULL; 
      set_field_back (formFields[0], A_UNDERLINE);
      set_field_fore (formFields[0], COLOR_PAIR(3));
      set_field_pad  (formFields[0], '_');
      field_opts_off (formFields[0], O_AUTOSKIP);
    break;

    case 'A':
      formFields = (FIELD **) calloc (NB_ARGS_OF_ADD_PARENT_OPTION , sizeof (FIELD *));

      if ((formFields[0] = new_field (FIELD_HEIGHT, 20, FIELD_START_Y +7, FIELD_START_X +20, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[1] = new_field (FIELD_HEIGHT, 20, FIELD_START_Y +8, FIELD_START_X +20, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      formFields[NB_ARGS_OF_ADD_PARENT_OPTION] = NULL;
      
      for (index = 0; index < NB_ARGS_OF_ADD_PARENT_OPTION; index++)
      {
       set_field_back (formFields[index], A_UNDERLINE);
       set_field_fore (formFields[index], COLOR_PAIR(3));
       set_field_pad  (formFields[index], '_');
       field_opts_off (formFields[index], O_AUTOSKIP);
      }
    break;

    case 'R':
      formFields = (FIELD **) calloc (NB_ARGS_OF_REMOVE_PARENT_OPTION , sizeof (FIELD *));

      if ((formFields[0] = new_field (FIELD_HEIGHT, 20, FIELD_START_Y +7, FIELD_START_X +20, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[1] = new_field (FIELD_HEIGHT, 20, FIELD_START_Y +8, FIELD_START_X +20, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      formFields[NB_ARGS_OF_REMOVE_PARENT_OPTION] = NULL;
      
      for (index = 0; index < NB_ARGS_OF_REMOVE_PARENT_OPTION; index++)
      {
       set_field_back (formFields[index], A_UNDERLINE);
       set_field_fore (formFields[index], COLOR_PAIR(3));
       set_field_pad  (formFields[index], '_');
       field_opts_off (formFields[index], O_AUTOSKIP);
      }
    break;

    case 'E':
      formFields = (FIELD **) calloc (NB_ARGS_OF_EDIT_PARENT_OPTION , sizeof (FIELD *));

      if ((formFields[0] = new_field (FIELD_HEIGHT, 20, FIELD_START_Y +7, FIELD_START_X +20, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[1] = new_field (FIELD_HEIGHT, 20, FIELD_START_Y +8, FIELD_START_X +20, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[2] = new_field (FIELD_HEIGHT, 20, FIELD_START_Y +9, FIELD_START_X +20, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      if ((formFields[3] = new_field (FIELD_HEIGHT, 20, FIELD_START_Y +10, FIELD_START_X +20, 0, 0)) == NULL)
      {
        free (formFields);
        return (NULL);
      }
      formFields[NB_ARGS_OF_EDIT_PARENT_OPTION] = NULL;
      
      for (index = 0; index < NB_ARGS_OF_EDIT_PARENT_OPTION; index++)
      {
       set_field_back (formFields[index], A_UNDERLINE);
       set_field_fore (formFields[index], COLOR_PAIR(3));
       set_field_pad  (formFields[index], '_');
       field_opts_off (formFields[index], O_AUTOSKIP);
      }
    break;

    case 'g':

    break;

    case 'm':

    break;

    case 'p':
  
    break;
  
    case 'C':

    break;

    case 'u':

    break;

    default:
      return (NULL);
  }
  return (formFields);
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
void showDescriptionsOfFields (char option)
{
  switch (option)
  {
    case 't': 
      printInMiddle (stdscr, 1, 0, COLS, showTextHelpMessage (REINSTALL_FORM_DESCRIPTION), COLOR_PAIR(4));
      wattron (stdscr, COLOR_PAIR(2));
      mvprintw (FIELD_START_Y    , 4, "%s", showTextHelpMessage (USERNAME_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +1 , 4, "%s", showTextHelpMessage (ADMINISTRATOR_PASS_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +2 , 4, "%s", showTextHelpMessage (NAME_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +3 , 4, "%s", showTextHelpMessage (EMAIL_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +4 , 4, "%s", showTextHelpMessage (HOMEPAGE_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +5 , 4, "%s", showTextHelpMessage (STREET_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +6 , 4, "%s", showTextHelpMessage (HOME_NUMBER_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +7 , 4, "%s", showTextHelpMessage (COMPLEMENT_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +8 , 4, "%s", showTextHelpMessage (DISTRICT_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +9 , 4, "%s", showTextHelpMessage (CITY_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +10, 4, "%s", showTextHelpMessage (STATE_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +11, 4, "%s", showTextHelpMessage (COUNTRY_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +12, 4, "%s", showTextHelpMessage (ZIP_CODE_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +13, 4, "%s", showTextHelpMessage (TEL_NUMBER_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +14, 4, "%s", showTextHelpMessage (CELL_NUMBER_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +15, 4, "%s", showTextHelpMessage (GENDER_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +16, 4, "%s", showTextHelpMessage (RELATIONSHIP_STATUS_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +17, 4, "%s", showTextHelpMessage (DAY_OF_BORN_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +18, 4, "%s", showTextHelpMessage (MONTH_OF_BORN_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +19, 4, "%s", showTextHelpMessage (YEAR_OF_BORN_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +20, 4, "%s", showTextHelpMessage (DESCRIPTION_FIELD_DESCRIPTION));
      wattroff (stdscr, COLOR_PAIR(2));
    break;

    case 'a':
      printInMiddle (stdscr, 1, 0, COLS, showTextHelpMessage (ADD_USER_FORM_DESCRIPTION), COLOR_PAIR(4));
      wattron (stdscr, COLOR_PAIR(2));
      mvprintw (FIELD_START_Y    , 4, "%s", showTextHelpMessage (USERNAME_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +1 , 4, "%s", showTextHelpMessage (NEW_USER_PASSWORD_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +2 , 4, "%s", showTextHelpMessage (CATEGORY_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +3 , 4, "%s", showTextHelpMessage (NAME_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +4 , 4, "%s", showTextHelpMessage (EMAIL_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +5 , 4, "%s", showTextHelpMessage (HOMEPAGE_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +6 , 4, "%s", showTextHelpMessage (STREET_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +7 , 4, "%s", showTextHelpMessage (HOME_NUMBER_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +8 , 4, "%s", showTextHelpMessage (COMPLEMENT_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +9 , 4, "%s", showTextHelpMessage (DISTRICT_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +10, 4, "%s", showTextHelpMessage (CITY_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +11, 4, "%s", showTextHelpMessage (STATE_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +12, 4, "%s", showTextHelpMessage (COUNTRY_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +13, 4, "%s", showTextHelpMessage (ZIP_CODE_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +14, 4, "%s", showTextHelpMessage (TEL_NUMBER_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +15, 4, "%s", showTextHelpMessage (CELL_NUMBER_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +16, 4, "%s", showTextHelpMessage (GENDER_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +17, 4, "%s", showTextHelpMessage (RELATIONSHIP_STATUS_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +18, 4, "%s", showTextHelpMessage (DAY_OF_BORN_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +19, 4, "%s", showTextHelpMessage (MONTH_OF_BORN_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +20, 4, "%s", showTextHelpMessage (YEAR_OF_BORN_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +21, 4, "%s", showTextHelpMessage (DESCRIPTION_FIELD_DESCRIPTION));
      wattroff (stdscr, COLOR_PAIR(2));
    break;

    case 'e':
      printInMiddle (stdscr, 1, 0, COLS, showTextHelpMessage (EDIT_USER_DATA_FORM_DESCRIPTION), COLOR_PAIR(4));
      wattron (stdscr, COLOR_PAIR(2));
      mvprintw (FIELD_START_Y    , 4, "%s", showTextHelpMessage (NAME_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +1 , 4, "%s", showTextHelpMessage (EMAIL_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +2 , 4, "%s", showTextHelpMessage (HOMEPAGE_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +3 , 4, "%s", showTextHelpMessage (STREET_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +4 , 4, "%s", showTextHelpMessage (HOME_NUMBER_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +5 , 4, "%s", showTextHelpMessage (COMPLEMENT_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +6 , 4, "%s", showTextHelpMessage (DISTRICT_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +7 , 4, "%s", showTextHelpMessage (CITY_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +8 , 4, "%s", showTextHelpMessage (STATE_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +9 , 4, "%s", showTextHelpMessage (COUNTRY_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +10, 4, "%s", showTextHelpMessage (ZIP_CODE_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +11, 4, "%s", showTextHelpMessage (TEL_NUMBER_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +12, 4, "%s", showTextHelpMessage (CELL_NUMBER_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +13, 4, "%s", showTextHelpMessage (GENDER_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +14, 4, "%s", showTextHelpMessage (RELATIONSHIP_STATUS_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +15, 4, "%s", showTextHelpMessage (DAY_OF_BORN_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +16, 4, "%s", showTextHelpMessage (MONTH_OF_BORN_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +17, 4, "%s", showTextHelpMessage (YEAR_OF_BORN_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +18, 4, "%s", showTextHelpMessage (DESCRIPTION_FIELD_DESCRIPTION));
      wattroff (stdscr, COLOR_PAIR(2));
    break;

    case 'r':

    break;

    case 'i':
      printInMiddle (stdscr, 3, 0, COLS, showTextHelpMessage (INVITE_USER_FORM_DESCRIPTION), COLOR_PAIR(4));
      wattron (stdscr, COLOR_PAIR(2));
      mvprintw (FIELD_START_Y +3 , 9, "%s", showTextHelpMessage (INVITING_USER_ID_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +4 , 9, "%s", showTextHelpMessage (NAME_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +5 , 9, "%s", showTextHelpMessage (EMAIL_FIELD_DESCRIPTION));
      wattroff (stdscr, COLOR_PAIR(2));
    break;

    case 'I':
      printInMiddle (stdscr, 3, 0, COLS, showTextHelpMessage (INVITE_FRIEND_FORM_DESCRIPTION), COLOR_PAIR(4));
      wattron (stdscr, COLOR_PAIR(2));
      mvprintw (FIELD_START_Y +7 , 14, "%s", showTextHelpMessage (INVITING_USER_ID_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +8 , 14, "%s", showTextHelpMessage (INVITED_USER_ID_FIELD_DESCRIPTION));
      wattroff (stdscr, COLOR_PAIR(2));
    break;

    case 'F':

    break;

    case 'P':
      printInMiddle (stdscr, 3, 0, COLS, showTextHelpMessage (ACCEPT_FORM_DESCRIPTION), COLOR_PAIR(4));
      wattron (stdscr, COLOR_PAIR(2));
      mvprintw (FIELD_START_Y +7 , 14, "%s", showTextHelpMessage (ACCEPTING_USER_ID_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +8 , 14, "%s", showTextHelpMessage (INVITER_USER_ID_FIELD_DESCRIPTION));
      wattroff (stdscr, COLOR_PAIR(2));
    break;

    case 'J':
      printInMiddle (stdscr, 3, 0, COLS, showTextHelpMessage (REJECT_FORM_DESCRIPTION), COLOR_PAIR(4));
      wattron (stdscr, COLOR_PAIR(2));
      mvprintw (FIELD_START_Y +7 , 14, "%s", showTextHelpMessage (REJECTING_USER_ID_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +8 , 14, "%s", showTextHelpMessage (INVITER_USER_ID_FIELD_DESCRIPTION));
      wattroff (stdscr, COLOR_PAIR(2));
    break;

    case 'X':
      printInMiddle (stdscr, 3, 0, COLS, showTextHelpMessage (EXCLUDE_FORM_DESCRIPTION), COLOR_PAIR(4));
      wattron (stdscr, COLOR_PAIR(2));
      mvprintw (FIELD_START_Y +7 , 14, "%s", showTextHelpMessage (EXCLUDING_USER_ID_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +8 , 14, "%s", showTextHelpMessage (EXCLUDED_USER_ID_FIELD_DESCRIPTION));
      wattroff (stdscr, COLOR_PAIR(2));
    break;

    case 'G':

    break;

    case 'c':
      printInMiddle (stdscr, 5, 0, COLS, showTextHelpMessage (CHANGE_CATEGORY_FORM_DESCRIPTION), COLOR_PAIR(4));
      wattron (stdscr, COLOR_PAIR(2));
      mvprintw (FIELD_START_Y +6 , 15, "%s", showTextHelpMessage (USER_ID_FIELD_DESCRIPTION));
      wattroff (stdscr, COLOR_PAIR(2));
    break;

    case 'A':
      printInMiddle (stdscr, 3, 0, COLS, showTextHelpMessage (ADD_PARENT_RELATIONSHIP_FORM_DESCRIPTION), COLOR_PAIR(4));
      wattron (stdscr, COLOR_PAIR(2));
      mvprintw (FIELD_START_Y +7 , 14, "%s", showTextHelpMessage (SUN_USER_ID_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +8 , 14, "%s", showTextHelpMessage (PARENT_USER_ID_FIELD_DESCRIPTION));
      wattroff (stdscr, COLOR_PAIR(2));
    break;

    case 'R':
      printInMiddle (stdscr, 3, 0, COLS, showTextHelpMessage (REMOVE_PARENT_RELATIONSHIP_FORM_DESCRIPTION), COLOR_PAIR(4));
      wattron (stdscr, COLOR_PAIR(2));
      mvprintw (FIELD_START_Y +7 , 14, "%s", showTextHelpMessage (SUN_USER_ID_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +8 , 14, "%s", showTextHelpMessage (PARENT_USER_ID_FIELD_DESCRIPTION));
      wattroff (stdscr, COLOR_PAIR(2));
    break;

    case 'E':
      printInMiddle (stdscr, 3, 0, COLS, showTextHelpMessage (EDIT_PARENT_RELATIONSHIP_FORM_DESCRIPTION), COLOR_PAIR(4));
      wattron (stdscr, COLOR_PAIR(2));
      mvprintw (FIELD_START_Y +7 , 14, "%s", showTextHelpMessage (SUN_USER_ID_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +8 , 14, "%s", showTextHelpMessage (PARENT_USER_ID_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +9 , 14, "%s", showTextHelpMessage (NEW_SUN_USER_ID_FIELD_DESCRIPTION));
      mvprintw (FIELD_START_Y +10, 14, "%s", showTextHelpMessage (NEW_PARENT_USER_ID_FIELD_DESCRIPTION));
      wattroff (stdscr, COLOR_PAIR(2));
    break;

    case 'g':

    break;

    case 'm':

    break;

    case 'p':
  
    break;
  
    case 'C':

    break;

    case 'u':

    break;
  }
 
  
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
char *repairString (char *string)
{
  unsigned index;
  
  if ((string == NULL) || (string[0] == EOS))
    return (NULL);
  
  for (index = strlen (string) -1; string[index] == ' '; index--)
  {
    string[index] = EOS;
    if (index == 0)
      return (string);
  }

  return (string);
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned repairFormData (userDataType *userData, FIELD **formFields, char option)
{
  unsigned errorCode;
  char temp [20+1];

  if (userData == NULL)
    return (REPAIR_FORM_DATA__NO_USER_DATA);
  if (formFields == NULL)
    return (REPAIR_FORM_DATA__NO_FORM_FIELDS);
    
  switch (option)
  {
    case 't':     
      userData->userId   = 0;
      userData->category = administrator;
      userData->next     = NULL;
      
      stringCopy (userData->userName,	        repairString (field_buffer (formFields[ 0], 0)),MAX_LENGTH_USERNAME);
      stringCopy (userData->plainPass,	        repairString (field_buffer (formFields[ 1], 0)),MAX_LENGTH_PLAIN_PASS);
      stringCopy (userData->name,	        repairString (field_buffer (formFields[ 2], 0)),MAX_LENGTH_NAME);
      stringCopy (userData->email, 	        repairString (field_buffer (formFields[ 3], 0)),MAX_LENGTH_EMAIL);
      stringCopy (userData->homepage,	        repairString (field_buffer (formFields[ 4], 0)),MAX_LENGTH_HOMEPAGE);
      stringCopy (userData->address.street,     repairString (field_buffer (formFields[ 5], 0)),MAX_LENGTH_STREET);
      stringCopy (userData->address.homeNumber, repairString (field_buffer (formFields[ 6], 0)),MAX_LENGTH_HOME_NUMBER);
      stringCopy (userData->address.complement, repairString (field_buffer (formFields[ 7], 0)),MAX_LENGTH_COMPLEMENT);
      stringCopy (userData->address.district,   repairString (field_buffer (formFields[ 8], 0)),MAX_LENGTH_DISTRICT);
      stringCopy (userData->address.city,       repairString (field_buffer (formFields[ 9], 0)),MAX_LENGTH_CITY);
      stringCopy (userData->address.state,      repairString (field_buffer (formFields[10], 0)),MAX_LENGTH_STATE);
      stringCopy (userData->address.country,    repairString (field_buffer (formFields[11], 0)),MAX_LENGTH_COUNTRY);
      stringCopy (userData->address.zipCode,    repairString (field_buffer (formFields[12], 0)),MAX_LENGTH_ZIP_CODE);
      stringCopy (userData->telNumber, 	        repairString (field_buffer (formFields[13], 0)),MAX_LENGTH_TEL_NUMBER);
      stringCopy (userData->cellNumber, 	repairString (field_buffer (formFields[14], 0)),MAX_LENGTH_CELL_NUMBER); 
      stringCopy (userData->birthday,	        repairString (field_buffer (formFields[17], 0)),LENGTH_DAY_OF_BORN);
      strncat    (userData->birthday, 	        repairString (field_buffer (formFields[18], 0)),LENGTH_MONTH_OF_BORN);
      strncat    (userData->birthday, 	        repairString (field_buffer (formFields[19], 0)),LENGTH_YEAR_OF_BORN);
      stringCopy (userData->description,	repairString (field_buffer (formFields[20], 0)),MAX_LENGTH_DESCRIPTION);
        
      if ((errorCode = encodePassword (userData->plainPass, userData->encryptedPass)) != OK)
        return (errorCode);
      
      #ifdef ENGLISH
        if (!strcmp (repairString (field_buffer (formFields[15], 0)),"male")) 
          userData->gender = male;   
        else if (!strcmp (field_buffer (formFields[15], 0),"female")) 
          userData->gender = female;
        else
          userData->gender = notAnswered;
    
        if (!strcmp (repairString (field_buffer (formFields[16], 0)),"single")) 
          userData->relationshipStatus = single;   
        else if (!strcmp (field_buffer (formFields[16], 0),"married")) 
          userData->relationshipStatus = married;
        else if (!strcmp (field_buffer (formFields[16], 0),"widowed")) 
          userData->relationshipStatus = widowed;
        else
          userData->relationshipStatus = notGiven;
      #elif PORTUGUESE
        if (!strcmp (repairString (field_buffer (formFields[15], 0)),"masculino")) 
          userData->gender = male;   
        else if (!strcmp (field_buffer (formFields[15], 0),"feminino")) 
          userData->gender = female;
        else
          userData->gender = notAnswered;
    
        if ((!strcmp (repairString (field_buffer (formFields[16], 0)),"solteiro")) || (!strcmp (field_buffer (formFields[16], 0),"solteira")))  
          userData->relationshipStatus = single;   
        else if ((!strcmp (field_buffer (formFields[16], 0),"casado")) || (!strcmp (field_buffer (formFields[16], 0),"casada")))
          userData->relationshipStatus = married;
        else if ((!strcmp (field_buffer (formFields[16], 0),"viuvo")) || (!strcmp (field_buffer (formFields[16], 0),"viuva")))
          userData->relationshipStatus = widowed;
        else
          userData->relationshipStatus = notGiven;
      #endif
    break;

    case 'a':
      userData->next     = NULL;
      
      stringCopy (userData->userName,	        repairString (field_buffer (formFields[ 0], 0)),MAX_LENGTH_USERNAME);
      stringCopy (userData->plainPass,	        repairString (field_buffer (formFields[ 1], 0)),MAX_LENGTH_PLAIN_PASS);    
      stringCopy (userData->name,	        repairString (field_buffer (formFields[ 3], 0)),MAX_LENGTH_NAME);
      stringCopy (userData->email, 	        repairString (field_buffer (formFields[ 4], 0)),MAX_LENGTH_EMAIL);
      stringCopy (userData->homepage,	        repairString (field_buffer (formFields[ 5], 0)),MAX_LENGTH_HOMEPAGE);
      stringCopy (userData->address.street,     repairString (field_buffer (formFields[ 6], 0)),MAX_LENGTH_STREET);
      stringCopy (userData->address.homeNumber, repairString (field_buffer (formFields[ 7], 0)),MAX_LENGTH_HOME_NUMBER);
      stringCopy (userData->address.complement, repairString (field_buffer (formFields[ 8], 0)),MAX_LENGTH_COMPLEMENT);
      stringCopy (userData->address.district,   repairString (field_buffer (formFields[ 9], 0)),MAX_LENGTH_DISTRICT);
      stringCopy (userData->address.city,       repairString (field_buffer (formFields[10], 0)),MAX_LENGTH_CITY);
      stringCopy (userData->address.state,      repairString (field_buffer (formFields[11], 0)),MAX_LENGTH_STATE);
      stringCopy (userData->address.country,    repairString (field_buffer (formFields[12], 0)),MAX_LENGTH_COUNTRY);
      stringCopy (userData->address.zipCode,    repairString (field_buffer (formFields[13], 0)),MAX_LENGTH_ZIP_CODE);
      stringCopy (userData->telNumber, 	        repairString (field_buffer (formFields[14], 0)),MAX_LENGTH_TEL_NUMBER);
      stringCopy (userData->cellNumber, 	repairString (field_buffer (formFields[15], 0)),MAX_LENGTH_CELL_NUMBER); 
      stringCopy (userData->birthday,	        repairString (field_buffer (formFields[18], 0)),LENGTH_DAY_OF_BORN);
      strncat    (userData->birthday, 	        repairString (field_buffer (formFields[19], 0)),LENGTH_MONTH_OF_BORN);
      strncat    (userData->birthday, 	        repairString (field_buffer (formFields[20], 0)),LENGTH_YEAR_OF_BORN);
      stringCopy (userData->description,	repairString (field_buffer (formFields[21], 0)),MAX_LENGTH_DESCRIPTION);
        
      
      #ifdef ENGLISH
        if (!strcmp (repairString (field_buffer (formFields[2], 0)),"webUser") || !strcmp (field_buffer (formFields[2], 0),"2")) 
          userData->category = webUser;   
        else if (!strcmp (field_buffer (formFields[2], 0),"relative") || !strcmp (field_buffer (formFields[2], 0),"3")) 
          userData->category = relative;
        else
          return (REPAIR_FORM_DATA__INVALID_CATEGORY);
	  
        if (!strcmp (repairString (field_buffer (formFields[16], 0)),"male")) 
          userData->gender = male;   
        else if (!strcmp (field_buffer (formFields[16], 0),"female")) 
          userData->gender = female;
        else
          userData->gender = notAnswered;
    
        if (!strcmp (repairString (field_buffer (formFields[17], 0)),"single")) 
          userData->relationshipStatus = single;   
        else if (!strcmp (field_buffer (formFields[17], 0),"married")) 
          userData->relationshipStatus = married;
        else if (!strcmp (field_buffer (formFields[17], 0),"widowed")) 
          userData->relationshipStatus = widowed;
        else
          userData->relationshipStatus = notGiven;
      #elif PORTUGUESE
        if (!strcmp (repairString (field_buffer (formFields[2], 0)),"usuarioWeb") || !strcmp (field_buffer (formFields[2], 0),"2")) 
          userData->category = webUser;   
        else if (!strcmp (field_buffer (formFields[2], 0),"parente") || !strcmp (field_buffer (formFields[2], 0),"3")) 
          userData->category = relative;
        else
          return (REPAIR_FORM_DATA__INVALID_CATEGORY);
	  
        if (!strcmp (repairString (field_buffer (formFields[16], 0)),"masculino")) 
          userData->gender = male;   
        else if (!strcmp (field_buffer (formFields[16], 0),"feminino")) 
          userData->gender = female;
        else
          userData->gender = notAnswered;
    
        if ((!strcmp (repairString (field_buffer (formFields[17], 0)),"solteiro")) || (!strcmp ( field_buffer (formFields[17], 0),"solteira")))  
          userData->relationshipStatus = single;   
        else if ((!strcmp (field_buffer (formFields[17], 0),"casado")) || (!strcmp (field_buffer (formFields[17], 0),"casada")))
          userData->relationshipStatus = married;
        else if ((!strcmp (field_buffer (formFields[17], 0),"viuvo")) || (!strcmp (field_buffer (formFields[17], 0),"viuva")))
          userData->relationshipStatus = widowed;
        else
          userData->relationshipStatus = notGiven;
      #endif
      
      if (userData->category == webUser)
        if ((errorCode = encodePassword (userData->plainPass, userData->encryptedPass)) != OK)
          return (errorCode);
	  if (userData->category == relative)
	    userData->encryptedPass[0] = EOS;
	  
    break;

    case 'e':
      userData->next     = NULL;
      
      stringCopy (userData->name,	        repairString (field_buffer (formFields[ 0], 0)),MAX_LENGTH_NAME);
      stringCopy (userData->email, 	        repairString (field_buffer (formFields[ 1], 0)),MAX_LENGTH_EMAIL);
      stringCopy (userData->homepage,	        repairString (field_buffer (formFields[ 2], 0)),MAX_LENGTH_HOMEPAGE);
      stringCopy (userData->address.street,     repairString (field_buffer (formFields[ 3], 0)),MAX_LENGTH_STREET);
      stringCopy (userData->address.homeNumber, repairString (field_buffer (formFields[ 4], 0)),MAX_LENGTH_HOME_NUMBER);
      stringCopy (userData->address.complement, repairString (field_buffer (formFields[ 5], 0)),MAX_LENGTH_COMPLEMENT);
      stringCopy (userData->address.district,   repairString (field_buffer (formFields[ 6], 0)),MAX_LENGTH_DISTRICT);
      stringCopy (userData->address.city,       repairString (field_buffer (formFields[ 7], 0)),MAX_LENGTH_CITY);
      stringCopy (userData->address.state,      repairString (field_buffer (formFields[ 8], 0)),MAX_LENGTH_STATE);
      stringCopy (userData->address.country,    repairString (field_buffer (formFields[ 9], 0)),MAX_LENGTH_COUNTRY);
      stringCopy (userData->address.zipCode,    repairString (field_buffer (formFields[10], 0)),MAX_LENGTH_ZIP_CODE);
      stringCopy (userData->telNumber, 	        repairString (field_buffer (formFields[11], 0)),MAX_LENGTH_TEL_NUMBER);
      stringCopy (userData->cellNumber, 	repairString (field_buffer (formFields[12], 0)),MAX_LENGTH_CELL_NUMBER); 
      stringCopy (userData->birthday,	        repairString (field_buffer (formFields[15], 0)),LENGTH_DAY_OF_BORN);
      strncat    (userData->birthday, 	        repairString (field_buffer (formFields[16], 0)),LENGTH_MONTH_OF_BORN);
      strncat    (userData->birthday, 	        repairString (field_buffer (formFields[17], 0)),LENGTH_YEAR_OF_BORN);
      stringCopy (userData->description,	repairString (field_buffer (formFields[18], 0)),MAX_LENGTH_DESCRIPTION);
        
      
      #ifdef ENGLISH
        if (!strcmp (repairString (field_buffer (formFields[13], 0)),"male")) 
          userData->gender = male;   
        else if (!strcmp (field_buffer (formFields[13], 0),"female")) 
          userData->gender = female;
        else
          userData->gender = notAnswered;
    
        if (!strcmp (repairString (field_buffer (formFields[14], 0)),"single")) 
          userData->relationshipStatus = single;   
        else if (!strcmp (field_buffer (formFields[14], 0),"married")) 
          userData->relationshipStatus = married;
        else if (!strcmp (field_buffer (formFields[14], 0),"widowed")) 
          userData->relationshipStatus = widowed;
        else
          userData->relationshipStatus = notGiven;
      #elif PORTUGUESE
        if (!strcmp (repairString (field_buffer (formFields[13], 0)),"masculino")) 
          userData->gender = male;   
        else if (!strcmp (field_buffer (formFields[13], 0),"feminino")) 
          userData->gender = female;
        else
          userData->gender = notAnswered;
    
        if ((!strcmp (repairString (field_buffer (formFields[14], 0)),"solteiro")) || (!strcmp (field_buffer (formFields[14], 0),"solteira")))  
          userData->relationshipStatus = single;   
        else if ((!strcmp (field_buffer (formFields[14], 0),"casado")) || (!strcmp (field_buffer (formFields[14], 0),"casada")))
          userData->relationshipStatus = married;
        else if ((!strcmp (field_buffer (formFields[14], 0),"viuvo")) || (!strcmp (field_buffer (formFields[14], 0),"viuva")))
          userData->relationshipStatus = widowed;
        else
          userData->relationshipStatus = notGiven;
      #endif
    break;

    case 'r':

    break;

    case 'i':
      stringCopy (temp,	repairString (field_buffer (formFields[0], 0)), 20);
      userData->userId = strtoul (temp, NULL, 10);
      stringCopy (userData->name,   repairString (field_buffer (formFields[1], 0)), MAX_LENGTH_NAME);
      stringCopy (userData->email,  repairString (field_buffer (formFields[2], 0)), MAX_LENGTH_EMAIL);
    break;

    case 'I':
  
    break;

    case 'F':

    break;

    case 'P':

    break;

    case 'J':

    break;

    case 'X':

    break;

    case 'G':

    break;

    case 'c':
      stringCopy (temp,	repairString (field_buffer (formFields[0], 0)), 20);
      userData->userId = strtoul (temp, NULL, 10);
      
      if (userData->userId == 0)
        return (CHANGE_USER_CATEGORY__CAN_NOT_CHANGE_ADMINISTRATOR_CATEGORY);
      if ((errorCode = getDataFromId (userData->userId, userData)) != OK)
        return (errorCode);
    break;

    case 'A':

    break;

    case 'R':

    break;

    case 'E':

    break;

    case 'g':

    break;

    case 'm':

    break;

    case 'p':
  
    break;
  
    case 'C':

    break;

    case 'u':

    break;

    default:
      return (REPAIR_FORM_DATA__UNKNOWN_OPTION);
  }
  
  return (OK);
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned setInitialValuesOfFields (FORM *form, userDataType *userData, char option)
{
  unsigned index, errorCode;
  char temp[20 +1];

  switch (option)
  {
    case 't': 
      if ((errorCode = getDataFromId (0, userData)) != OK)
        return (errorCode);

      for (index = 0; index <= strlen (userData->userName); index++)
        form_driver (form, userData->userName[index]);  			//username
      form_driver (form, REQ_NEXT_FIELD);
      form_driver (form, REQ_BEG_LINE);
										//plainPass
      form_driver (form, REQ_NEXT_FIELD);

      for (index = 0; index <= strlen (userData->name); index++)
        form_driver (form, userData->name[index]);				//name
      form_driver (form, REQ_NEXT_FIELD);
      form_driver (form, REQ_BEG_LINE);

      for (index = 0; index <= strlen (userData->email); index++)
        form_driver (form, userData->email[index]);				//email
      form_driver (form, REQ_NEXT_FIELD);
      form_driver (form, REQ_BEG_LINE);
	
      for (index = 0; index <= strlen (userData->homepage); index++)
        form_driver (form, userData->homepage[index]);				//homepage
      form_driver (form, REQ_NEXT_FIELD);
      form_driver (form, REQ_BEG_LINE);

      for (index = 0; index <= strlen (userData->address.street); index++)
        form_driver (form, userData->address.street[index]);			//street
      form_driver (form, REQ_NEXT_FIELD);
      form_driver (form, REQ_BEG_LINE);

      for (index = 0; index <= strlen (userData->address.homeNumber); index++)
        form_driver (form, userData->address.homeNumber[index]);		//homeNumber
      form_driver (form, REQ_NEXT_FIELD);
      form_driver (form, REQ_BEG_LINE);

      for (index = 0; index <= strlen (userData->address.complement); index++)
        form_driver (form, userData->address.complement[index]);		//complement
      form_driver (form, REQ_NEXT_FIELD);
      form_driver (form, REQ_BEG_LINE);

      for (index = 0; index <= strlen (userData->address.district); index++)
        form_driver (form, userData->address.district[index]);			//district
      form_driver (form, REQ_NEXT_FIELD);
      form_driver (form, REQ_BEG_LINE);

      for (index = 0; index <= strlen (userData->address.city); index++)
        form_driver (form, userData->address.city[index]);			//city
      form_driver (form, REQ_NEXT_FIELD);
      form_driver (form, REQ_BEG_LINE);

      for (index = 0; index <= strlen (userData->address.state); index++)
        form_driver (form, userData->address.state[index]);			//state
      form_driver (form, REQ_NEXT_FIELD);
      form_driver (form, REQ_BEG_LINE);

      for (index = 0; index <= strlen (userData->address.country); index++)
        form_driver (form, userData->address.country[index]);			//country
      form_driver (form, REQ_NEXT_FIELD);
      form_driver (form, REQ_BEG_LINE);

      for (index = 0; index <= strlen (userData->address.zipCode); index++)
        form_driver (form, userData->address.zipCode[index]);			//zipCode
      form_driver (form, REQ_NEXT_FIELD);
      form_driver (form, REQ_BEG_LINE);

      for (index = 0; index <= strlen (userData->telNumber); index++)
        form_driver (form, userData->telNumber[index]);				//telNumber
      form_driver (form, REQ_NEXT_FIELD);
      form_driver (form, REQ_BEG_LINE);

      for (index = 0; index <= strlen (userData->cellNumber); index++)
        form_driver (form, userData->cellNumber[index]);			//cellNumber
      form_driver (form, REQ_NEXT_FIELD);
      form_driver (form, REQ_BEG_LINE);

      #ifdef ENGLISH
        if (userData->gender == male)
        {
          strcpy (temp, "male");
          for (index = 0; index <= strlen (temp); index++)
            form_driver (form, temp[index]);
        }
        else if (userData->gender == female)
        {  
	  strcpy (temp, "female");
          for (index = 0; index <= strlen (temp); index++)			//gender
	    form_driver (form, temp[index]);
	}
        else
	{
	  strcpy (temp, "not given");
	  for (index = 0; index <= strlen (temp); index++)
	    form_driver (form, temp[index]);
	}
      #elif PORTUGUESE
        if (userData->gender == male)
        {
          strcpy (temp, "masculino");
          for (index = 0; index <= strlen (temp); index++)
            form_driver (form, temp[index]);
        }
        else if (userData->gender == female)
        {  
	  strcpy (temp, "feminino");
          for (index = 0; index <= strlen (temp); index++)			//gender
	    form_driver (form, temp[index]);
	}
        else
	{
	  strcpy (temp, "nao fornecido");
	  for (index = 0; index <= strlen (temp); index++)
	    form_driver (form, temp[index]);
	}
      #endif
    
        form_driver (form, REQ_NEXT_FIELD);
        form_driver (form, REQ_BEG_LINE);

      #ifdef ENGLISH
        if (userData->relationshipStatus == single)
        {
          strcpy (temp, "single");
          for (index = 0; index <= strlen (temp); index++)
            form_driver (form, temp[index]);
        }
        else if (userData->relationshipStatus == married)
        {  
	  strcpy (temp, "married");
          for (index = 0; index <= strlen (temp); index++)			//relationshipStatus
	    form_driver (form, temp[index]);
	}
        else if (userData->relationshipStatus == widowed)
        {  
	  strcpy (temp, "widowed");
          for (index = 0; index <= strlen (temp); index++)			
	    form_driver (form, temp[index]);
	}
        else
	{
	  strcpy (temp, "not given");
	  for (index = 0; index <= strlen (temp); index++)
	    form_driver (form, temp[index]);
	}
      #elif PORTUGUESE
        if (userData->relationshipStatus == single)
        {
          strcpy (temp, "solteiro");
          for (index = 0; index <= strlen (temp); index++)
            form_driver (form, temp[index]);
        }
        else if (userData->relationshipStatus == married)
        {  
	  strcpy (temp, "casado");
          for (index = 0; index <= strlen (temp); index++)			//relationshipStatus
	    form_driver (form, temp[index]);
	}
        else if (userData->relationshipStatus == widowed)
        {  
	  strcpy (temp, "viuvo");
          for (index = 0; index <= strlen (temp); index++)			
	    form_driver (form, temp[index]);
	}
        else
	{
	  strcpy (temp, "nao fornecido");
	  for (index = 0; index <= strlen (temp); index++)
	    form_driver (form, temp[index]);
	}
      #endif

      form_driver (form, REQ_NEXT_FIELD);
      form_driver (form, REQ_BEG_LINE);


      for (index = 0; index < LENGTH_DAY_OF_BORN; index++)
        form_driver (form, userData->birthday[index]);				//day of born
      form_driver (form, REQ_NEXT_FIELD);
      form_driver (form, REQ_BEG_LINE);

      for (index = LENGTH_DAY_OF_BORN; index < (LENGTH_DAY_OF_BORN + LENGTH_MONTH_OF_BORN) ; index++)
        form_driver (form, userData->birthday[index]);				//month of born
      form_driver (form, REQ_NEXT_FIELD);
      form_driver (form, REQ_BEG_LINE);

      for (index = (LENGTH_DAY_OF_BORN + LENGTH_MONTH_OF_BORN); index <= MAX_LENGTH_BIRTHDAY ; index++)
        form_driver (form, userData->birthday[index]);				//year of born
      form_driver (form, REQ_NEXT_FIELD);
      form_driver (form, REQ_BEG_LINE);

      for (index = 0; index <= strlen (userData->description); index++)
        form_driver (form, userData->description[index]);			//description


      form_driver (form, REQ_FIRST_FIELD);
      form_driver (form, REQ_END_LINE);
    break;

    case 'a':
     /* nothing to do in this case */
    break;

    case 'e':
      if ((errorCode = getDataFromId (userData->userId, userData)) != OK)
        return (errorCode);

      for (index = 0; index <= strlen (userData->name); index++)
        form_driver (form, userData->name[index]);				//name
      form_driver (form, REQ_NEXT_FIELD);
      form_driver (form, REQ_BEG_LINE);

      for (index = 0; index <= strlen (userData->email); index++)
        form_driver (form, userData->email[index]);				//email
      form_driver (form, REQ_NEXT_FIELD);
      form_driver (form, REQ_BEG_LINE);
	
      for (index = 0; index <= strlen (userData->homepage); index++)
        form_driver (form, userData->homepage[index]);				//homepage
      form_driver (form, REQ_NEXT_FIELD);
      form_driver (form, REQ_BEG_LINE);

      for (index = 0; index <= strlen (userData->address.street); index++)
        form_driver (form, userData->address.street[index]);			//street
      form_driver (form, REQ_NEXT_FIELD);
      form_driver (form, REQ_BEG_LINE);

      for (index = 0; index <= strlen (userData->address.homeNumber); index++)
        form_driver (form, userData->address.homeNumber[index]);		//homeNumber
      form_driver (form, REQ_NEXT_FIELD);
      form_driver (form, REQ_BEG_LINE);

      for (index = 0; index <= strlen (userData->address.complement); index++)
        form_driver (form, userData->address.complement[index]);		//complement
      form_driver (form, REQ_NEXT_FIELD);
      form_driver (form, REQ_BEG_LINE);

      for (index = 0; index <= strlen (userData->address.district); index++)
        form_driver (form, userData->address.district[index]);			//district
      form_driver (form, REQ_NEXT_FIELD);
      form_driver (form, REQ_BEG_LINE);

      for (index = 0; index <= strlen (userData->address.city); index++)
        form_driver (form, userData->address.city[index]);			//city
      form_driver (form, REQ_NEXT_FIELD);
      form_driver (form, REQ_BEG_LINE);

      for (index = 0; index <= strlen (userData->address.state); index++)
        form_driver (form, userData->address.state[index]);			//state
      form_driver (form, REQ_NEXT_FIELD);
      form_driver (form, REQ_BEG_LINE);

      for (index = 0; index <= strlen (userData->address.country); index++)
        form_driver (form, userData->address.country[index]);			//country
      form_driver (form, REQ_NEXT_FIELD);
      form_driver (form, REQ_BEG_LINE);

      for (index = 0; index <= strlen (userData->address.zipCode); index++)
        form_driver (form, userData->address.zipCode[index]);			//zipCode
      form_driver (form, REQ_NEXT_FIELD);
      form_driver (form, REQ_BEG_LINE);

      for (index = 0; index <= strlen (userData->telNumber); index++)
        form_driver (form, userData->telNumber[index]);				//telNumber
      form_driver (form, REQ_NEXT_FIELD);
      form_driver (form, REQ_BEG_LINE);

      for (index = 0; index <= strlen (userData->cellNumber); index++)
        form_driver (form, userData->cellNumber[index]);			//cellNumber
      form_driver (form, REQ_NEXT_FIELD);
      form_driver (form, REQ_BEG_LINE);

      #ifdef ENGLISH
        if (userData->gender == male)
        {
          strcpy (temp, "male");
          for (index = 0; index <= strlen (temp); index++)
            form_driver (form, temp[index]);
        }
        else if (userData->gender == female)
        {  
	  strcpy (temp, "female");
          for (index = 0; index <= strlen (temp); index++)			//gender
	    form_driver (form, temp[index]);
	}
        else
	{
	  strcpy (temp, "not given");
	  for (index = 0; index <= strlen (temp); index++)
	    form_driver (form, temp[index]);
	}
      #elif PORTUGUESE
        if (userData->gender == male)
        {
          strcpy (temp, "masculino");
          for (index = 0; index <= strlen (temp); index++)
            form_driver (form, temp[index]);
        }
        else if (userData->gender == female)
        {  
	  strcpy (temp, "feminino");
          for (index = 0; index <= strlen (temp); index++)			//gender
	    form_driver (form, temp[index]);
	}
        else
	{
	  strcpy (temp, "nao fornecido");
	  for (index = 0; index <= strlen (temp); index++)
	    form_driver (form, temp[index]);
	}
      #endif
    
        form_driver (form, REQ_NEXT_FIELD);
        form_driver (form, REQ_BEG_LINE);

      #ifdef ENGLISH
        if (userData->relationshipStatus == single)
        {
          strcpy (temp, "single");
          for (index = 0; index <= strlen (temp); index++)
            form_driver (form, temp[index]);
        }
        else if (userData->relationshipStatus == married)
        {  
	  strcpy (temp, "married");
          for (index = 0; index <= strlen (temp); index++)			//relationshipStatus
	    form_driver (form, temp[index]);
	}
        else if (userData->relationshipStatus == widowed)
        {  
	  strcpy (temp, "widowed");
          for (index = 0; index <= strlen (temp); index++)			
	    form_driver (form, temp[index]);
	}
        else
	{
	  strcpy (temp, "not given");
	  for (index = 0; index <= strlen (temp); index++)
	    form_driver (form, temp[index]);
	}
      #elif PORTUGUESE
        if (userData->relationshipStatus == single)
        {
          strcpy (temp, "solteiro");
          for (index = 0; index <= strlen (temp); index++)
            form_driver (form, temp[index]);
        }
        else if (userData->relationshipStatus == married)
        {  
	  strcpy (temp, "casado");
          for (index = 0; index <= strlen (temp); index++)			//relationshipStatus
	    form_driver (form, temp[index]);
	}
        else if (userData->relationshipStatus == widowed)
        {  
	  strcpy (temp, "viuvo");
          for (index = 0; index <= strlen (temp); index++)			
	    form_driver (form, temp[index]);
	}
        else
	{
	  strcpy (temp, "nao fornecido");
	  for (index = 0; index <= strlen (temp); index++)
	    form_driver (form, temp[index]);
	}
      #endif

      form_driver (form, REQ_NEXT_FIELD);
      form_driver (form, REQ_BEG_LINE);


      for (index = 0; index < LENGTH_DAY_OF_BORN; index++)
        form_driver (form, userData->birthday[index]);				//day of born
      form_driver (form, REQ_NEXT_FIELD);
      form_driver (form, REQ_BEG_LINE);

      for (index = LENGTH_DAY_OF_BORN; index < (LENGTH_DAY_OF_BORN + LENGTH_MONTH_OF_BORN) ; index++)
        form_driver (form, userData->birthday[index]);				//month of born
      form_driver (form, REQ_NEXT_FIELD);
      form_driver (form, REQ_BEG_LINE);

      for (index = (LENGTH_DAY_OF_BORN + LENGTH_MONTH_OF_BORN); index <= MAX_LENGTH_BIRTHDAY ; index++)
        form_driver (form, userData->birthday[index]);				//year of born
      form_driver (form, REQ_NEXT_FIELD);
      form_driver (form, REQ_BEG_LINE);

      for (index = 0; index <= strlen (userData->description); index++)
        form_driver (form, userData->description[index]);			//description


      form_driver (form, REQ_FIRST_FIELD);
      form_driver (form, REQ_END_LINE);
    break;

    case 'r':

    break;

    case 'i':

    break;

    case 'I':

    break;

    case 'F':

    break;

    case 'P':

    break;

    case 'J':

    break;

    case 'X':

    break;

    case 'G':

    break;

    case 'c':
	     /* nothig to do in this case */
    break;

    case 'A':

    break;

    case 'R':

    break;

    case 'E':

    break;

    case 'g':

    break;

    case 'm':

    break;

    case 'p':
  
    break;
  
    case 'C':

    break;

    case 'u':

    break;
  }
 
 return (OK); 
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
void showAdministratorMenu (char *cookieName)
{
  #ifdef ENGLISH
    printf ("<HTML>\n");
    printf ("  <BODY BACKGROUND = \"http://www2.del.ufrj.br/~marceloddm/computacao_ii/pf/images/zertxtr.gif\" BGCOLOR = \"#000000\" TEXT = \"#FFFFFF\" LINK = \"#6699CC\" VLINK = \"#669966\" ALINK = \"#999999\">\n");
    printf ("    <DIV ALIGN = \"CENTER\"><STRONG><FONT FACE = \"Courier New\" SIZE = \"2\" COLOR = \"#FFFFFF\">MENU</FONT></STRONG></DIV>\n");
    printf ("    <HR>\n");
    printf ("    <TABLE BORDER=\"1\" ALIGN = \"CENTER\">\n");
    printf ("    <TR><TD><H6><A HREF=\"showAddUserForm.cgi?cookieName=%s\" TARGET=\"main\">Add user</A></H6></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showEditUserDataForm.cgi?cookieName=%s\" TARGET=\"main\">Edit user data</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showRemoveUserForm.cgi?cookieName=%s\" TARGET=\"main\">Remove user</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showInviteUserForm.cgi?cookieName=%s\" TARGET=\"main\">Invite user</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showInviteFriendForm.cgi?cookieName=%s\" TARGET=\"main\">Invite friend</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showGetFriendshipInvitationForm.cgi?cookieName=%s\" TARGET=\"main\">Pending invitations</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showAcceptFriendshipInvitationForm.cgi?cookieName=%s\" TARGET=\"main\">Accept invitation</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showRejectFriendshipInvitationForm.cgi?cookieName=%s\" TARGET=\"main\">Reject invitation</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showExcludeFriendForm.cgi?cookieName=%s\" TARGET=\"main\">Exclude friendship</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showGetFriendsForm.cgi?cookieName=%s\" TARGET=\"main\">Get friends</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showChangeUserCategoryForm.cgi?cookieName=%s\" TARGET=\"main\">Change category</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showAddParentRelationshipForm.cgi?cookieName=%s\" TARGET=\"main\">Add parent relationship</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showRemoveParentRelationshipForm.cgi?cookieName=%s\" TARGET=\"main\">Remove parent relationship</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showEditParentRelationshipForm.cgi?cookieName=%s\" TARGET=\"main\">Edit parent relationship</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showGetUsersForm.cgi?cookieName=%s\" TARGET=\"main\">Search users</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showMountFamilyTreeForm.cgi?cookieName=%s\" TARGET=\"main\">Mount family tree</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showRecoveryPasswordForm.cgi?cookieName=%s\" TARGET=\"main\">Recovery password</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showChangePasswordForm.cgi?cookieName=%s\" TARGET=\"main\">Change password</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showUploadUserPhotoForm.cgi?cookieName=%s\" TARGET=\"main\">Upload user photo</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"logout.cgi?cookieName=%s\" TARGET=\"_top\">Logout</A></TD></TR>\n", cookieName);
    printf ("    </FONT></TABLE\n");
    printf ("    <HR>\n");
    printf ("  <BODY>\n");
    printf ("</HTML>\n");
  #elif PORTUGUESE
    printf ("<HTML>\n");
    printf ("  <BODY BACKGROUND = \"http://www2.del.ufrj.br/~marceloddm/computacao_ii/pf/images/zertxtr.gif\" BGCOLOR = \"#000000\" TEXT = \"#FFFFFF\" LINK = \"#6699CC\" VLINK = \"#669966\" ALINK = \"#999999\">\n");
    printf ("    <DIV ALIGN = \"CENTER\"><STRONG><FONT FACE = \"Courier New\" SIZE = \"2\" COLOR = \"#FFFFFF\">MENU</FONT></STRONG></DIV>\n");
    printf ("    <HR>\n");
    printf ("    <TABLE BORDER=\"1\" ALIGN = \"CENTER\">\n");
    printf ("    <FONT SIZE=\"1\">\n");
    printf ("    <TR><TD><H6><A HREF=\"showAddUserForm.cgi?cookieName=%s\" TARGET=\"main\">Adicionar usu&aacute;rio</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showEditUserDataForm.cgi?cookieName=%s\" TARGET=\"main\">Editar dados</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showRemoveUserForm.cgi?cookieName=%s\" TARGET=\"main\">Remover usu&aacute;rio</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showInviteUserForm.cgi?cookieName=%s\" TARGET=\"main\">Convidar usu&aacute;rio</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showInviteFriendForm.cgi?cookieName=%s\" TARGET=\"main\">Convidar amigo(a)</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showGetFriendshipInvitationForm.cgi?cookieName=%s\" TARGET=\"main\">Convites pendentes</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showAcceptFriendshipInvitationForm.cgi?cookieName=%s\" TARGET=\"main\">Aceitar convite</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showRejectFriendshipInvitationForm.cgi?cookieName=%s\" TARGET=\"main\">Rejeitar convite</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showExcludeFriendForm.cgi?cookieName=%s\" TARGET=\"main\">Excluir amizade</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showGetFriendsForm.cgi?cookieName=%s\" TARGET=\"main\">Lista de amigos</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showChangeUserCategoryForm.cgi?cookieName=%s\" TARGET=\"main\">Trocar categoria</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showAddParentRelationshipForm.cgi?cookieName=%s\" TARGET=\"main\">Adicinar parentesco</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showRemoveParentRelationshipForm.cgi?cookieName=%s\" TARGET=\"main\">Remover parentesco</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showEditParentRelationshipForm.cgi?cookieName=%s\" TARGET=\"main\">Editar parentesco</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showGetUsersForm.cgi?cookieName=%s\" TARGET=\"main\">Procurar usu&aacute;rios</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showMountFamilyTreeForm.cgi?cookieName=%s\" TARGET=\"main\">&Aacute;rvore geneal&oacute;gica</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showRecoveryPasswordForm.cgi?cookieName=%s\" TARGET=\"main\">Recuperar senha</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showChangePasswordForm.cgi?cookieName=%s\" TARGET=\"main\">Trocar senha</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showUploadUserPhotoForm.cgi?cookieName=%s\" TARGET=\"main\">Upload de foto</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"logout.cgi?cookieName=%s\" TARGET=\"_top\">Logout</A></TD></TR>\n", cookieName);
    printf ("    </FONT></TABLE\n");
    printf ("    <HR>\n");
    printf ("  <BODY>\n");
    printf ("</HTML>\n");
  #endif
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
void showWebUserMenu (char *cookieName)
{
  #ifdef ENGLISH
    printf ("<HTML>\n");
    printf ("  <BODY BACKGROUND = \"http://www2.del.ufrj.br/~marceloddm/computacao_ii/pf/images/zertxtr.gif\" BGCOLOR = \"#000000\" TEXT = \"#FFFFFF\" LINK = \"#6699CC\" VLINK = \"#669966\" ALINK = \"#999999\">\n");
    printf ("    <DIV ALIGN = \"CENTER\"><STRONG><FONT FACE = \"Courier New\" SIZE = \"2\" COLOR = \"#FFFFFF\">MENU</FONT></STRONG></DIV>\n");
    printf ("    <HR>\n");
    printf ("    <TABLE BORDER=\"1\" ALIGN = \"CENTER\">\n");
    printf ("    <FONT SIZE=\"1\">\n");
    printf ("    <TR><TD><H6><A HREF=\"showEditUserDataForm.cgi?cookieName=%s\" TARGET=\"main\">Edit your data</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showRemoveUserForm.cgi?cookieName=%s\" TARGET=\"main\">Get out of system</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showInviteUserForm.cgi?cookieName=%s\" TARGET=\"main\">Invite user</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showInviteFriendForm.cgi?cookieName=%s\" TARGET=\"main\">Invite friend</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showGetFriendshipInvitationForm.cgi?cookieName=%s\" TARGET=\"main\">Pending invitations</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showAcceptFriendshipInvitationForm.cgi?cookieName=%s\" TARGET=\"main\">Accept invitation</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showRejectFriendshipInvitationForm.cgi?cookieName=%s\" TARGET=\"main\">Reject invitation</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showExcludeFriendForm.cgi?cookieName=%s\" TARGET=\"main\">Exclude friendship</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showGetFriendsForm.cgi?cookieName=%s\" TARGET=\"main\">Get friends</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showChangeUserCategoryForm.cgi?cookieName=%s\" TARGET=\"main\">Change category</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showAddParentRelationshipForm.cgi?cookieName=%s\" TARGET=\"main\">Add parent relationship</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showRemoveParentRelationshipForm.cgi?cookieName=%s\" TARGET=\"main\">Remove parent relationship</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showEditParentRelationshipForm.cgi?cookieName=%s\" TARGET=\"main\">Edit parent relationship</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showGetUsersForm.cgi?cookieName=%s\" TARGET=\"main\">Search users</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showMountFamilyTreeForm.cgi?cookieName=%s\" TARGET=\"main\">Mount family tree</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showChangePasswordForm.cgi?cookieName=%s\" TARGET=\"main\">Change password</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showUploadUserPhotoForm.cgi?cookieName=%s\" TARGET=\"main\">Upload your photo</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"logout.cgi?cookieName=%s\" TARGET=\"_top\">Logout</A></TD></TR>\n", cookieName);
    printf ("    </FONT></TABLE\n");
    printf ("    <HR>\n");
    printf ("  <BODY>\n");
    printf ("</HTML>\n");
  #elif PORTUGUESE
    printf ("<HTML>\n");
    printf ("  <BODY BACKGROUND = \"http://www2.del.ufrj.br/~marceloddm/computacao_ii/pf/images/zertxtr.gif\" BGCOLOR = \"#000000\" TEXT = \"#FFFFFF\" LINK = \"#6699CC\" VLINK = \"#669966\" ALINK = \"#999999\">\n");
    printf ("    <DIV ALIGN = \"CENTER\"><STRONG><FONT FACE = \"Courier New\" SIZE = \"2\" COLOR = \"#FFFFFF\">MENU</FONT></STRONG></DIV>\n");
    printf ("    <HR>\n");
    printf ("    <TABLE BORDER=\"1\" ALIGN = \"CENTER\">\n");
    printf ("    <FONT SIZE=\"1\">\n");
    printf ("    <TR><TD><H6><A HREF=\"showEditUserDataForm.cgi?cookieName=%s\" TARGET=\"main\">Editar dados</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showRemoveUserForm.cgi?cookieName=%s\" TARGET=\"main\">Sair do sistema</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showInviteUserForm.cgi?cookieName=%s\" TARGET=\"main\">Convidar usu&aacute;rio</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showInviteFriendForm.cgi?cookieName=%s\" TARGET=\"main\">Convidar amigo(a)</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showGetFriendshipInvitationForm.cgi?cookieName=%s\" TARGET=\"main\">Convites pendentes</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showAcceptFriendshipInvitationForm.cgi?cookieName=%s\" TARGET=\"main\">Aceitar convite</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showRejectFriendshipInvitationForm.cgi?cookieName=%s\" TARGET=\"main\">Rejeitar convite</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showExcludeFriendForm.cgi?cookieName=%s\" TARGET=\"main\">Excluir amizade</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showGetFriendsForm.cgi?cookieName=%s\" TARGET=\"main\">Lista de amigos</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showChangeUserCategoryForm.cgi?cookieName=%s\" TARGET=\"main\">Trocar categoria</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showAddParentRelationshipForm.cgi?cookieName=%s\" TARGET=\"main\">Adicinar parentesco</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showRemoveParentRelationshipForm.cgi?cookieName=%s\" TARGET=\"main\">Remover parentesco</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showEditParentRelationshipForm.cgi?cookieName=%s\" TARGET=\"main\">Editar parentesco</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showGetUsersForm.cgi?cookieName=%s\" TARGET=\"main\">Procurar usu&aacute;rios</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showMountFamilyTreeForm.cgi?cookieName=%s\" TARGET=\"main\">&Aacute;rvore geneal&oacute;gica</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showChangePasswordForm.cgi?cookieName=%s\" TARGET=\"main\">Trocar senha</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"showUploadUserPhotoForm.cgi?cookieName=%s\" TARGET=\"main\">Upload de foto</A></TD></TR>\n", cookieName);
    printf ("    <TR><TD><H6><A HREF=\"logout.cgi?cookieName=%s\" TARGET=\"_top\">Logout</A></TD></TR>\n", cookieName);
    printf ("    </FONT></TABLE\n");
    printf ("    <HR>\n");
    printf ("  <BODY>\n");
    printf ("</HTML>\n");
  #endif
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
void showHtmlOKPage (void)
{
  #ifdef ENGLISH
    printf ("<HTML>\n");
    printf ("  <HEAD>\n");
    printf ("    <TITLE>Relationship System - Confirmation Page</TITLE>\n");
    printf ("  </HEAD>\n");
    printf ("  <BODY BACKGROUND = \"http://www2.del.ufrj.br/~marceloddm/computacao_ii/pf/images/zertxtr.gif\" BGCOLOR = \"#000000\" TEXT = \"#FFFFFF\" LINK = \"#6699CC\" VLINK = \"#669966\" ALINK = \"#999999\">\n");
    printf ("    <DIV ALIGN = \"CENTER\"><STRONG><FONT FACE = \"Courier New\" SIZE = \"6\" COLOR = \"#FFFFFF\">RELATIONSHIP SYSTEM</FONT></STRONG></DIV>\n");
    printf ("    <HR>\n");
    printf ("    <CENTER><STRONG><FONT FACE = \"Courier New\" SIZE = \"5\" COLOR = \"#FFFFFF\">CONFIRMATION PAGE</FONT></STRONG><CENTER>\n");
    printf ("    <HR>\n");
    printf ("    <BR><BR>\n");
    printf ("    <DIV ALIGN = \"LEFT\">\n");
    printf ("       Result of the operation: \n");
    printf ("    </DIV>\n");
    printf ("    <BR><BR>\n");
    printf ("    <DIV ALIGN = \"CENTER\">\n");
    printf ("      Operation done successfully.\n");
    printf ("    </DIV>\n");
    printf ("    <BR><BR><BR>\n");
    printf ("<P ALIGN=\"left\"><A HREF=\"javascript:window.history.go(-1)\" TARGET=\"_self\">GO BACK</a>\n");
    printf ("    <BR>\n");
    printf ("    <A HREF=\"http://www.del.ufrj.br/~marceloddm/computacao_ii/pf\" TARGET=\"_top\">Go to login page</a></p>\n");
    printf ("    <HR>\n");
    printf ("    <DIV ALIGN = \"RIGHT\"><FONT FACE = \"Courier New\" SIZE = \"2\"><U>Authors:</U>\n");
    printf ("    <I> Carlo Fragni and Marcelo Duffles Donato Moreira\n");
    printf ("    <BR>\n");
    printf ("    Last update: 14/02/05</I></FONT>\n");
    printf ("    </DIV></FONT>\n");
    printf ("  <BODY>\n");
    printf ("</HTML>\n");
  #elif PORTUGUESE
    printf ("<HTML>\n");
    printf ("  <HEAD>\n");
    printf ("    <TITLE>Sistema de Relacionamentos - P&aacute;gina de confirma&ccedil;&atilde;o</TITLE>\n");
    printf ("  </HEAD>\n");
    printf ("  <BODY BACKGROUND = \"http://www2.del.ufrj.br/~marceloddm/computacao_ii/pf/images/zertxtr.gif\" BGCOLOR = \"#000000\" TEXT = \"#FFFFFF\" LINK = \"#6699CC\" VLINK = \"#669966\" ALINK = \"#999999\">\n");
    printf ("    <DIV ALIGN = \"CENTER\"><STRONG><FONT FACE = \"Courier New\" SIZE = \"6\" COLOR = \"#FFFFFF\">SISTEMA DE RELACIONAMENTOS</FONT></STRONG></DIV>\n");
    printf ("    <HR>\n");
    printf ("    <CENTER><STRONG><FONT FACE = \"Courier New\" SIZE = \"5\" COLOR = \"#FFFFFF\">P&Aacute;GINA DE CONFIRMA&Ccedil;&Atilde;O</FONT></STRONG><CENTER>\n");
    printf ("    <HR>\n");
    printf ("    <BR><BR>\n");
    printf ("    <DIV ALIGN = \"LEFT\">\n");
    printf ("    Resultado da opera&ccedil;&atilde;o: \n");
    printf ("    </DIV>\n");
    printf ("    <BR><BR>\n");
    printf ("    <DIV ALIGN = \"CENTER\">\n");
    printf ("      Opera&ccedil;&atilde;o realizada com sucesso.\n");
    printf ("    </DIV>\n");
    printf ("    <BR><BR><BR>\n");
    printf ("<P ALIGN=\"left\"><A HREF=\"javascript:window.history.go(-1)\" TARGET=\"_self\">VOLTAR</a>\n");
    printf ("    <BR>\n");
    printf ("    <A HREF=\"http://www.del.ufrj.br/~marceloddm/computacao_ii/pf\" TARGET=\"_top\">Vá para a página de login</a></p>\n");
    printf ("    <HR>\n");
    printf ("    <DIV ALIGN = \"RIGHT\"><FONT FACE = \"Courier New\" SIZE = \"2\"><U>Autores:</U>\n");
    printf ("    <I> Carlo Fragni e Marcelo Duffles Donato Moreira\n");
    printf ("    <BR>\n");
    printf ("    &Uacute;ltima Atualiza&ccedil;&atilde;o: 14/02/05</I></FONT>\n");
    printf ("    </DIV></FONT>\n");
    printf ("  <BODY>\n");
    printf ("</HTML>\n");
  #endif
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
void showHtmlInitialPage (char *cookieName)
{
  printf ("<HTML>\n");
  #ifdef ENGLISH
    printf ("  <HEAD>\n");
    printf ("    <TITLE>Relationship System - Initial Page</TITLE>\n");
    printf ("  </HEAD>\n");
  #elif PORTUGUESE
    printf ("  <HEAD>\n");
    printf ("    <TITLE>Sistema de Relacionamentos - P&aacute;gina inicial</TITLE>\n");
    printf ("  </HEAD>\n");
  #endif
  printf ("<FRAMESET COLS=\"26%%,74%%\">\n");
  printf ("<FRAME NAME=\"menu\" SRC=\"http://www2.del.ufrj.br/~marceloddm/computacao_ii/pf/cgi/showMenu.cgi?cookieName=%s\">\n", cookieName);
  printf ("<FRAME NAME=\"main\" SRC=\"http://www2.del.ufrj.br/~marceloddm/computacao_ii/pf/cgi/showWelcomePage.cgi?cookieName=%s\">\n", cookieName);
  printf ("</FRAMESET>\n");
  printf ("</HTML>\n");
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
void showHtmlWelcomePage (userDataType *userData)
{
  #ifdef ENGLISH
    printf ("<HTML>\n");
    printf ("  <BODY BACKGROUND = \"http://www2.del.ufrj.br/~marceloddm/computacao_ii/pf/images/zertxtr.gif\" BGCOLOR = \"#000000\" TEXT = \"#FFFFFF\" LINK = \"#6699CC\" VLINK = \"#669966\" ALINK = \"#999999\">\n");
    printf ("    <DIV ALIGN = \"CENTER\"><STRONG><FONT FACE = \"Courier New\" SIZE = \"5\" COLOR = \"#FFFFFF\">RELATIONSHIP SYSTEM</FONT></STRONG></DIV>\n");
    printf ("    <HR>\n");
    printf ("    <CENTER><STRONG><FONT FACE = \"Courier New\" SIZE = \"4\" COLOR = \"#FFFFFF\">INITIAL PAGE</FONT></STRONG><CENTER>\n");
    printf ("    <HR>\n");
    printf ("    <BR>\n");
    printf ("    <DIV ALIGN = \"CENTER\"><FONT SIZE=\"2\">\n");
    printf ("       <STRONG>Welcome %s!</STRONG>\n", userData->name);
    printf ("    </DIV>\n");
    printf ("    <BR>\n");
    printf ("    <TABLE ALIGN=\"CENTER\" BORDER=\"1\"><FONT SIZE=\"1\">\n");
    printf ("       <TR><TD><H6>USER ID: </TD>		<TD><H6>%llu</TD></TR>\n", userData->userId);
    printf ("       <TR><TD><H6>Username: </TD>		<TD><H6>%s</TD></TR>\n", userData->userName);
  if (userData->category == administrator)
    printf ("       <TR><TD><H6>Category: </TD>		<TD><H6>Administrator</TD></TR>\n");
  else
    printf ("       <TR><TD><H6>Category: </TD>		<TD><H6>Web user</TD></TR>\n");
    printf ("       <TR><TD><H6>Full name: </TD>		<TD><H6>%s</TD></TR>\n", userData->name);
    printf ("       <TR><TD><H6>Email: </TD>		<TD><H6>%s</TD></TR>\n", userData->email);
    printf ("       <TR><TD><H6>Homepage: </TD>		<TD><H6>%s</TD></TR>\n", userData->homepage);
    printf ("       <TR><TD><H6>Street: </TD>		<TD><H6>%s</TD></TR>\n", userData->address.street);
    printf ("       <TR><TD><H6>Home number: </TD>		<TD><H6>%s</TD></TR>\n", userData->address.homeNumber);
    printf ("       <TR><TD><H6>Complement: </TD>		<TD><H6>%s</TD></TR>\n", userData->address.complement);
    printf ("       <TR><TD><H6>District: </TD>		<TD><H6>%s</TD></TR>\n", userData->address.district);
    printf ("       <TR><TD><H6>City: </TD>			<TD><H6>%s</TD></TR>\n", userData->address.city);
    printf ("       <TR><TD><H6>State: </TD>		<TD><H6>%s</TD></TR>\n", userData->address.state);
    printf ("       <TR><TD><H6>Country: </TD>		<TD><H6>%s</TD></TR>\n", userData->address.country);
    printf ("       <TR><TD><H6>ZIP CODE: </TD>		<TD><H6>%s</TD></TR>\n", userData->address.zipCode);
    printf ("       <TR><TD><H6>Telephone: </TD>		<TD><H6>%s</TD></TR>\n", userData->telNumber);
    printf ("       <TR><TD><H6>Cellphone: </TD>		<TD><H6>%s</TD></TR>\n", userData->cellNumber);
  if (userData->gender == male)
    printf ("       <TR><TD><H6>Gender: </TD>		<TD><H6>Male</TD></TR>\n");
  else if (userData->gender == female)
    printf ("       <TR><TD><H6>Gender: </TD>		<TD><H6>Female</TD></TR>\n");
  else
    printf ("       <TR><TD><H6>Gender: </TD>		<TD><H6>Not given</TD></TR>\n");
  if (userData->relationshipStatus == single)
    printf ("       <TR><TD><H6>Relationship Status: </TD>	<TD><H6>Single</TD></TR>\n");
  else if (userData->relationshipStatus == married)
    printf ("       <TR><TD><H6>Relationship Status: </TD>	<TD><H6>Married</TD></TR>\n");
  else if (userData->relationshipStatus == widowed)
    printf ("       <TR><TD><H6>Relationship Status: </TD>	<TD><H6>Widowed</TD></TR>\n");
  else
    printf ("       <TR><TD><H6>Relationship Status: </TD>	<TD><H6>Not given</TD></TR>\n");
    printf ("       <TR><TD><H6>Birthday: </TD>		<TD><H6>%s</TD></TR>\n", userData->birthday);
    printf ("       <TR><TD><H6>Description: </TD>		<TD><H6>%s</TD></TR>\n", userData->description);
    printf ("    </TABLE>\n");
    printf ("    <BR><BR><BR>\n");
    printf ("<P ALIGN=\"left\"><A HREF=\"javascript:window.history.go(-1)\" TARGET=\"_self\">GO BACK</a>\n");
    printf ("    <BR>\n");
    printf ("    <A HREF=\"http://www.del.ufrj.br/~marceloddm/computacao_ii/pf\" TARGET=\"_top\">Go to login page</a></p>\n");
    printf ("    <HR>\n");
    printf ("    <DIV ALIGN = \"RIGHT\"><FONT FACE = \"Courier New\" SIZE = \"2\"><U>Authors:</U>\n");
    printf ("    <I> Carlo Fragni and Marcelo Duffles Donato Moreira\n");
    printf ("    <BR>\n");
    printf ("    Last update: 16/02/05</I></FONT>\n");
    printf ("    </DIV></FONT>\n");
    printf ("  <BODY>\n");
    printf ("</HTML>\n");
  #elif PORTUGUESE
    printf ("<HTML>\n");
    printf ("  <BODY BACKGROUND = \"http://www2.del.ufrj.br/~marceloddm/computacao_ii/pf/images/zertxtr.gif\" BGCOLOR = \"#000000\" TEXT = \"#FFFFFF\" LINK = \"#6699CC\" VLINK = \"#669966\" ALINK = \"#999999\">\n");
    printf ("    <DIV ALIGN = \"CENTER\"><STRONG><FONT FACE = \"Courier New\" SIZE = \"5\" COLOR = \"#FFFFFF\">SISTEMA DE RELACIONAMENTOS</FONT></STRONG></DIV>\n");
    printf ("    <HR>\n");
    printf ("    <CENTER><STRONG><FONT FACE = \"Courier New\" SIZE = \"4\" COLOR = \"#FFFFFF\">P&Aacute;GINA INICIAL</FONT></STRONG><CENTER>\n");
    printf ("    <HR>\n");
    printf ("    <BR>\n");
    printf ("    <DIV ALIGN = \"CENTER\"><FONT SIZE=\"2\">\n");
    printf ("       <STRONG>Seja bem-vindo %s!</STRONG>\n", userData->name);
    printf ("    </DIV>\n");
    printf ("    <BR>\n");
    printf ("    <TABLE ALIGN=\"CENTER\" BORDER=\"1\"><FONT SIZE=\"1\">\n");
    printf ("       <TR><TD><H6>ID: </TD>			<TD><H6>%llu</TD></TR>\n", userData->userId);
    printf ("       <TR><TD><H6>Username: </TD>		<TD><H6>%s</TD></TR>\n", userData->userName);
  if (userData->category == administrator)
    printf ("       <TR><TD><H6>Categoria: </TD>		<TD><H6>Administrador</TD></TR>\n");
  else
    printf ("       <TR><TD><H6>Categoria: </TD>		<TD><H6>Usu&aacute;rio web</TD></TR>\n");
    printf ("       <TR><TD><H6>Nome completo: </TD>	<TD><H6>%s</TD></TR>\n", userData->name);
    printf ("       <TR><TD><H6>Email: </TD>		<TD><H6>%s</TD></TR>\n", userData->email);
    printf ("       <TR><TD><H6>Homepage: </TD>		<TD><H6>%s</TD></TR>\n", userData->homepage);
    printf ("       <TR><TD><H6>Rua: </TD>			<TD><H6>%s</TD></TR>\n", userData->address.street);
    printf ("       <TR><TD><H6>N&uacute;mero: </TD>	<TD><H6>%s</TD></TR>\n", userData->address.homeNumber);
    printf ("       <TR><TD><H6>Complemento: </TD>		<TD><H6>%s</TD></TR>\n", userData->address.complement);
    printf ("       <TR><TD><H6>Bairro: </TD>		<TD><H6>%s</TD></TR>\n", userData->address.district);
    printf ("       <TR><TD><H6>Cidade: </TD>		<TD><H6>%s</TD></TR>\n", userData->address.city);
    printf ("       <TR><TD><H6>Estado: </TD>		<TD><H6>%s</TD></TR>\n", userData->address.state);
    printf ("       <TR><TD><H6>Pa&iacute;s: </TD>		<TD><H6>%s</TD></TR>\n", userData->address.country);
    printf ("       <TR><TD><H6>CEP: </TD>			<TD><H6>%s</TD></TR>\n", userData->address.zipCode);
    printf ("       <TR><TD><H6>Telefone: </TD>		<TD><H6>%s</TD></TR>\n", userData->telNumber);
    printf ("       <TR><TD><H6>Celular: </TD>		<TD><H6>%s</TD></TR>\n", userData->cellNumber);
  if (userData->gender == male)
    printf ("       <TR><TD><H6>Sexo: </TD>			<TD><H6>Masculino</TD></TR>\n");
  else if (userData->gender == female)
    printf ("       <TR><TD><H6>Sexo: </TD>			<TD><H6>Feminino</TD></TR>\n");
  else
    printf ("       <TR><TD><H6>Sexo: </TD>			<TD><H6>N&atilde;o fornecido</TD></TR>\n");
  if (userData->relationshipStatus == single)
    printf ("       <TR><TD><H6>Estado civil: </TD>		<TD><H6>Solteiro(a)</TD></TR>\n");
  else if (userData->relationshipStatus == married)
    printf ("       <TR><TD><H6>Estado civil: </TD>		<TD><H6>Casado(a)</TD></TR>\n");
  else if (userData->relationshipStatus == widowed)
    printf ("       <TR><TD><H6>Estado civil: </TD>		<TD><H6>Vi&uacute;vo(a)</TD></TR>\n");
  else
    printf ("       <TR><TD><H6>Estado civil: </TD>		<TD><H6>N&atilde;o fornecido</TD></TR>\n");
    printf ("       <TR><TD><H6>Dia do nascimento: </TD>	<TD><H6>%s</TD></TR>\n", userData->birthday);
    printf ("       <TR><TD><H6>Descri&ccedil;&atilde;o: </TD><TD><H6>%s</TD></TR>\n", userData->description);
    printf ("    </TABLE>\n");
    printf ("    <BR><BR><BR>\n");
    printf ("<P ALIGN=\"left\"><A HREF=\"javascript:window.history.go(-1)\" TARGET=\"_self\">VOLTAR</a>\n");
    printf ("    <BR>\n");
    printf ("    <A HREF=\"http://www.del.ufrj.br/~marceloddm/computacao_ii/pf\" TARGET=\"_top\">Vá para a página de login</a></p>\n");
    printf ("    <HR>\n");
    printf ("    <DIV ALIGN = \"RIGHT\"><FONT FACE = \"Courier New\" SIZE = \"2\"><U>Autores:</U>\n");
    printf ("    <I> Carlo Fragni e Marcelo Duffles Donato Moreira\n");
    printf ("    <BR>\n");
    printf ("    &Uacute;ltima atualiza&ccedil;&atilde;o: 16/02/05</I></FONT>\n");
    printf ("    </DIV></FONT>\n");
    printf ("  <BODY>\n");
    printf ("</HTML>\n");
  #endif
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
void checkIfPairExist (userIdType sonId, userIdType parentId, boolean *sonExist, boolean *parentExist, boolean *pairAlreadyInserted, familyTreeType *first)
{
  familyTreeType *cursor;
  
  *sonExist            = false;
  *parentExist         = false;
  *pairAlreadyInserted = false;
  
  for (cursor = first; cursor != NULL; cursor = cursor->next)
  {
    if (cursor->userId == sonId)
    {
      *sonExist = true;
          
      if ((cursor->parent != NULL) && ((cursor->parent)->userId == parentId))
      {
        *parentExist         = true;
	*pairAlreadyInserted = true;
      }  

      if ((cursor->parent != NULL) && ((cursor->parent)->spouse != NULL) && (((cursor->parent)->spouse)->userId == parentId))
      {
        *parentExist         = true;
	*pairAlreadyInserted = true;       
      }
    }
    
    if (cursor->userId == parentId)
      *parentExist = true;
  }
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
familyTreeType *getFamilyFromId (userIdType id, familyTreeType *first)
{
  familyTreeType *cursor;
  
  for (cursor = first; cursor != NULL; cursor = cursor->next)
    if (cursor->userId == id)
      return (cursor);
   
  return (NULL);
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
void insertSon (familyTreeType **newSon, familyTreeType **parent)
{
  familyTreeType *cursor;
    
  /* checking if the parent has already a son in family... */
  if ((**parent).son == NULL)
    (**parent).son = *newSon;
  else 
  {
    for (cursor = (**parent).son; cursor->brother != NULL; cursor = cursor->brother);
    cursor->brother = *newSon;
  }
  
  (**newSon).brother = NULL;
}	  
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned getUserParents (userIdType userId, familyTreeType **user, familyTreeType *first)
{
  unsigned retCode;
  char parentsFileName [MAX_LENGTH_LONG_FILENAME +1];
  FILE *parentsFile;
  userIdType sonId, parentId;
  familyTreeType *parent;
  boolean sonExist, parentExist, pairAlreadyInserted;
  
  if ((*user == NULL) || (user == NULL))
    return (GET_USER_FAMILY__NO_FAMILY);

  if ((retCode = getLongFilename (DATA_DIR, PARENTS_FILE_NAME , parentsFileName)) != OK)
    return (retCode);
    
  if ((parentsFile = fopen (parentsFileName, "r")) == NULL)
  {
    if (errno != ENOENT)
      return (GET_USER_FAMILY__ERROR_OPENING_PARENTS_FILE_FOR_READING);
    return (GET_USER_FAMILY__PARENTS_FILE_DOES_NOT_EXIST);
  }
  
  /* searching family in parents file... */   
  for (retCode = 0; retCode != GET_USER_ID__END_OF_FILE;)  
  {
    if ((retCode = getUserId (parentsFile, &sonId)) != OK)
      if (retCode != GET_USER_ID__END_OF_FILE)
      {
        fclose (parentsFile);
        return (retCode);
      }
       
    if ((retCode = getUserId (parentsFile, &parentId)) != OK)
      if (retCode != GET_USER_ID__END_OF_FILE)
      {
        fclose (parentsFile);
        return (retCode);
      }
      
    checkIfPairExist (sonId, parentId, &sonExist, &parentExist, &pairAlreadyInserted, first);
    
    if ((retCode != GET_USER_ID__END_OF_FILE) && (!pairAlreadyInserted))
    { 
      /* checking if the son is the given user... */
      if (sonId == userId)
      {
        if (!parentExist)
	{
          /* allocatting memory for parent family... */
          if ((parent = (familyTreeType *) malloc (sizeof (familyTreeType))) == NULL)
          {
            fclose (parentsFile);
	    return (GET_USER_FAMILY__MEMORY_ALLOCATION_ERROR);
          }
	
          /* inserting parent in user family... */
	  parent->userId  = parentId;
	  parent->parent  = NULL;
	  parent->brother = NULL;
	  parent->son     = *user;
	  
	  insertInFamilyList (&parent, &first);
	}
	else
	{
	  parent = getFamilyFromId (parentId, first);
	  insertSon (user, &parent);
	}
	
	if ((**user).parent == NULL)
	{
	  (**user).parent = parent;
	  parent->spouse  = NULL;
	}
	else
	{
	  ((**user).parent)->spouse = parent;
	  parent->spouse = (**user).parent;
	}
      }
    } 
  }
  fclose (parentsFile);

  return (OK);
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned getUserSonsAndDaughters (userIdType userId, familyTreeType **user, familyTreeType *first)
{
  unsigned retCode;
  char parentsFileName [MAX_LENGTH_LONG_FILENAME +1];
  FILE *parentsFile;
  userIdType sonId, parentId;
  familyTreeType *son;
  boolean sonExist, parentExist, pairAlreadyInserted;
  
  if ((*user == NULL) || (user == NULL))
    return (GET_USER_FAMILY__NO_FAMILY);

  if ((retCode = getLongFilename (DATA_DIR, PARENTS_FILE_NAME , parentsFileName)) != OK)
    return (retCode);
    
  if ((parentsFile = fopen (parentsFileName, "r")) == NULL)
  {
    if (errno != ENOENT)
      return (GET_USER_FAMILY__ERROR_OPENING_PARENTS_FILE_FOR_READING);
    return (GET_USER_FAMILY__PARENTS_FILE_DOES_NOT_EXIST);
  }
  
  /* searching family in parents file... */   
  for (retCode = 0; retCode != GET_USER_ID__END_OF_FILE;)  
  {
    if ((retCode = getUserId (parentsFile, &sonId)) != OK)
      if (retCode != GET_USER_ID__END_OF_FILE)
      {
        fclose (parentsFile);
        return (retCode);
      }
       
    if ((retCode = getUserId (parentsFile, &parentId)) != OK)
      if (retCode != GET_USER_ID__END_OF_FILE)
      {
        fclose (parentsFile);
        return (retCode);
      }
      
    checkIfPairExist (sonId, parentId, &sonExist, &parentExist, &pairAlreadyInserted, first);
    
    if ((retCode != GET_USER_ID__END_OF_FILE) && (!pairAlreadyInserted))
    { 
      /* checking if the parent is the given user... */
      if (parentId == userId)
      {
        if (!sonExist)
	{
          /* allocatting memory for son family... */
          if ((son = (familyTreeType *) malloc (sizeof (familyTreeType))) == NULL)
          {
            fclose (parentsFile);
	    return (GET_USER_FAMILY__MEMORY_ALLOCATION_ERROR);
          }
	
          /* inserting son in user family... */
	  son->userId  = sonId;
	  son->spouse  = NULL;
	  son->brother = NULL;
	  son->son     = NULL;
	  son->parent  = *user;
	  insertInFamilyList (&son, &first);
	}
	else
	{
	  son = getFamilyFromId (sonId, first);
	  if (son->parent == NULL)
	    son->parent  = *user;
	  else
	  {
	    (son->parent)->spouse = *user;
	    (**user).spouse = son->parent;
	  }
	}
	insertSon (&son, user);
      }
    } 
  }
  fclose (parentsFile);
  
  return (OK);
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned getUserSpouse (userIdType userId, familyTreeType **user, familyTreeType *first)
{
  unsigned retCode;
  char parentsFileName [MAX_LENGTH_LONG_FILENAME +1];
  FILE *parentsFile;
  userIdType sonId, parentId;
  familyTreeType *parent, *currentSon;
  boolean sonExist, parentExist, pairAlreadyInserted;
  
  if ((*user == NULL) || (user == NULL))
    return (GET_USER_FAMILY__NO_FAMILY);

  if ((retCode = getLongFilename (DATA_DIR, PARENTS_FILE_NAME , parentsFileName)) != OK)
    return (retCode);
    
  for (currentSon = (**user).son; currentSon != NULL; currentSon = currentSon->brother)
  {
    if ((parentsFile = fopen (parentsFileName, "r")) == NULL)
    {
      if (errno != ENOENT)
        return (GET_USER_FAMILY__ERROR_OPENING_PARENTS_FILE_FOR_READING);
      return (GET_USER_FAMILY__PARENTS_FILE_DOES_NOT_EXIST);
    }
  
    /* searching family in parents file... */   
    for (retCode = 0; retCode != GET_USER_ID__END_OF_FILE;)  
    {
      if ((retCode = getUserId (parentsFile, &sonId)) != OK)
        if (retCode != GET_USER_ID__END_OF_FILE)
        {
          fclose (parentsFile);
          return (retCode);
        }
       
      if ((retCode = getUserId (parentsFile, &parentId)) != OK)
        if (retCode != GET_USER_ID__END_OF_FILE)
        {
          fclose (parentsFile);
          return (retCode);
        }
      
      checkIfPairExist (sonId, parentId, &sonExist, &parentExist, &pairAlreadyInserted, first);
    
      if ((retCode != GET_USER_ID__END_OF_FILE) && (!pairAlreadyInserted))
      { 
        /* checking if the son is the given user... */
        if (sonId == currentSon->userId)
        {
          if (!parentExist)
	  {
            /* allocatting memory for parent family... */
            if ((parent = (familyTreeType *) malloc (sizeof (familyTreeType))) == NULL)
            {
              fclose (parentsFile);
	      return (GET_USER_FAMILY__MEMORY_ALLOCATION_ERROR);
            }
	
            /* inserting parent in user family... */
	    parent->userId  = parentId;
	    parent->parent  = NULL;
	    parent->brother = NULL;
	    parent->son     = currentSon;
	  
	    insertInFamilyList (&parent, &first);
	  }
	  else
	  {
	    parent = getFamilyFromId (parentId, first);
	    insertSon (&currentSon, &parent);
	  }
	
	  if (currentSon->parent == NULL)
	  {
	    currentSon->parent = parent;
	    parent->spouse  = NULL;
	  }
	  else
	  {
	    (currentSon->parent)->spouse = parent;
	    parent->spouse = currentSon->parent;
	  }
        }
      } 
    }
    fclose (parentsFile);
  }
  
  return (OK);
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned getUserBrothersAndSisters (userIdType userId, familyTreeType **user, familyTreeType *first)
{
  unsigned retCode;
  char parentsFileName [MAX_LENGTH_LONG_FILENAME +1];
  FILE *parentsFile;
  userIdType sonId, parentId;
  familyTreeType *son;
  boolean sonExist, parentExist, pairAlreadyInserted;
  
  if ((*user == NULL) || (user == NULL))
    return (GET_USER_FAMILY__NO_FAMILY);

  if ((retCode = getLongFilename (DATA_DIR, PARENTS_FILE_NAME , parentsFileName)) != OK)
    return (retCode);
    
  if ((**user).parent != NULL)
  {
    if ((parentsFile = fopen (parentsFileName, "r")) == NULL)
    {
      if (errno != ENOENT)
        return (GET_USER_FAMILY__ERROR_OPENING_PARENTS_FILE_FOR_READING);
      return (GET_USER_FAMILY__PARENTS_FILE_DOES_NOT_EXIST);
    }
  
    /* searching family in parents file... */   
    for (retCode = 0; retCode != GET_USER_ID__END_OF_FILE;)  
    {
      if ((retCode = getUserId (parentsFile, &sonId)) != OK)
        if (retCode != GET_USER_ID__END_OF_FILE)
        {
          fclose (parentsFile);
          return (retCode);
        }
       
      if ((retCode = getUserId (parentsFile, &parentId)) != OK)
        if (retCode != GET_USER_ID__END_OF_FILE)
        {
          fclose (parentsFile);
          return (retCode);
        }
      
      checkIfPairExist (sonId, parentId, &sonExist, &parentExist, &pairAlreadyInserted, first);
    
      if ((retCode != GET_USER_ID__END_OF_FILE) && (!pairAlreadyInserted))
      { 
        /* checking if the parent is the given user... */
        if (parentId == ((**user).parent)->userId)
        {
          if (!sonExist)
	  {
            /* allocatting memory for son family... */
            if ((son = (familyTreeType *) malloc (sizeof (familyTreeType))) == NULL)
            {
              fclose (parentsFile);
	      return (GET_USER_FAMILY__MEMORY_ALLOCATION_ERROR);
            }
	
            /* inserting son in user family... */
  	    son->userId  = sonId; 
	    son->spouse  = NULL;
	    son->brother = NULL;
	    son->son     = NULL;
	    son->parent  = (**user).parent;
	    insertInFamilyList (&son, &first);
	  }
	  else
	  {
	    son = getFamilyFromId (sonId, first);
	    if (son->parent == NULL)
	      son->parent  = (**user).parent;
	    else
  	    {
	      (son->parent)->spouse = (**user).parent;
	      ((**user).parent)->spouse = son->parent;
	    }
	  }
	  insertSon (&son, &((**user).parent));
        } 
      } 
    }
   fclose (parentsFile);  
  }
  
  return (OK);
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned getUserFamily (userIdType userId, familyTreeType **user, familyTreeType *first)
{
  unsigned retCode;
  
  
  if ((*user == NULL) || (user == NULL))
    return (GET_USER_FAMILY__NO_FAMILY);

  if ((retCode = getUserParents (userId, user, first)) != OK)
    return (retCode);
    
  if ((retCode = getUserSonsAndDaughters (userId, user, first)) != OK)
    return (retCode);
    
  if ((retCode = getUserSpouse (userId, user, first)) != OK)
    return (retCode);
  
  if ((retCode = getUserBrothersAndSisters (userId, user, first)) != OK)
    return (retCode);
  
    
  return (OK);      
}
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
boolean alreadyInFamilyList (userIdType id, familyTreeType *first)
{
  familyTreeType *cursor;
  
  for (cursor = first; cursor != NULL; cursor = cursor->next)
    if (cursor->userId == id)
      return (true);
      
  return (false);
}
/*---------------------------------------------------------------------------------------------------------*/

// $RCSfile: functions.c,v $
