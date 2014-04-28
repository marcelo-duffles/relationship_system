//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: getUsers() primary function source file 
// Date: 20/12/2004
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: getUsers.c,v $
 * Revision 1.3  2005/02/16 22:11:21  marceloddm
 * CGI's added
 *
 * Revision 1.2  2004/12/20 20:01:44  marceloddm
 * This function is now complete
 *
 * Revision 1.1  2004/12/20 12:47:36  marceloddm
 * Initial revision
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/errno.h>
#include "config.h"
#include "const.h"
#include "types.h"
#include "error.h"
#include "functions.h"
#include "getUsers.h"
 
static const char rcsid [] = "$Id: getUsers.c,v 1.3 2005/02/16 22:11:21 marceloddm Exp marceloddm $";

unsigned getUsers ( char * searchKey , userDataType ** firstFound )
{
  unsigned retCode, retCode2;
  unsigned counter , secondCounter;
  char usersFileName [MAX_LENGTH_LONG_FILENAME+1];
  userDataType buffer;
  FILE * readFile;
  boolean matches;
  userDataType * lastFound = NULL;
    
  if (! searchKey )
    return ( GET_USERS__INVALID_SEARCH_KEY );
     
  if (( retCode = getLongFilename ( DATA_DIR , USERS_FILE_NAME , usersFileName )) != OK )
    return (retCode);
    
  if (!(readFile = fopen ( usersFileName , "r" )))
  {
    if (errno != ENOENT)
      return ( GET_USERS__ERROR_OPENING_USERS_FILE_FOR_READING );
    return ( GET_USERS__USERS_FILE_DOES_NOT_EXIST );
  }
  
  ( * firstFound ) = NULL;
  matches = true;
  
  for( retCode = 0 ; retCode != GET_USER_ID__END_OF_FILE ; )  
  {
    if (( retCode = getUserData ( readFile , USERS_FILE_NAME , &buffer )) != OK )
    {
      if (retCode != GET_USER_ID__END_OF_FILE)
      {
        fclose ( readFile );
	freeFIFOResources ( firstFound , &lastFound );
        return ( retCode );
      }
    }
    
    if ( retCode != GET_USER_ID__END_OF_FILE )
      {
        for ( matches = false , counter = 0 ; ( (buffer.name[counter] != EOS) && ( !matches ) ) ; counter++ )
	  if ( buffer.name[counter] == searchKey[0] )
	  {
	    matches = true;  
	    for ( secondCounter = 1 ; ( ( searchKey[secondCounter] != EOS ) && ( matches ) ) ; secondCounter++ )
	      if ( searchKey [secondCounter] != buffer.name [counter + secondCounter] )
	        matches = false;
	  }  
        if ( matches )
	{
	  if( ( retCode2 = insertFIFO ( firstFound, &lastFound, &buffer ) ) != OK )
	  {
	    fclose ( readFile );
	    freeFIFOResources ( firstFound , &lastFound );
	    return ( retCode2);
	  }  
	}
      }
  }
 // fclose ( readFile );
  if ( ! ( * firstFound ) )
    return ( GET_USERS__NO_USER_FOUND );
  return ( OK ); 
}  


/*$RCSfile: getUsers.c,v $*/


