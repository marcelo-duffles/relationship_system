//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Polit�cnica
// Departamento de Eletr�nica e de Computa��o
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: Source file of the primary function editParentRelationship().
// Date: 28/12/2004
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: editParentRelationship.c,v $
 * Revision 1.1  2005/02/16 22:11:21  marceloddm
 * Initial revision
 *
 */

 
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/errno.h>
#include "const.h"
#include "types.h"
#include "config.h"
#include "error.h"
#include "functions.h"
#include "editParentRelationship.h"
  
static const char rcsid [] = "$Id: editParentRelationship.c,v 1.1 2005/02/16 22:11:21 marceloddm Exp marceloddm $";
  
unsigned editParentRelationship ( userIdType sonOrDaughterId, userIdType fatherOrMotherId, userIdType newSonOrDaughterId, userIdType newFatherOrMotherId)
{
  unsigned retCode, retCode2;
  char parentsFileName [MAX_LENGTH_LONG_FILENAME +1];
  char parentsFileNameTmp [MAX_LENGTH_LONG_FILENAME +1];
  FILE *rParentsFile, *wParentsFile;
  userIdType buffer, bufferTwo;
  boolean found;
  userDataType tempData, tempDataTwo;
  genderType parentGender;
  
  if ( ( retCode = getDataFromId ( sonOrDaughterId, &tempData) ) != OK )
    return ( retCode );
    
  if ( ( retCode = getDataFromId ( newSonOrDaughterId, &tempData) ) != OK )
    return ( retCode );
   
  /*P�R TESTE NA CHAMADA PARA VER, CASO USU�RIO SEJA CAT2 SE EST� TENTANDO ALTERAR SEUS PR�PRIOS PARENTES ATRAV�S DE CHECAGEM NA �RVORE*/
  
  /*CHECKING IF IT'S THE MOTHER, FATHER OR IF THE GIVEN PERSON HAS NO GENDER ANSWERED*/
  
  if ( ( retCode = getDataFromId ( newFatherOrMotherId, &tempData) ) != OK )
    return ( retCode );
  
  if ( ( parentGender = tempData.gender  ) == notAnswered )
    return ( EDIT_PARENT_RELATIONSHIP__GIVEN_PARENT_HAS_NO_GENDER_ANSWERED );
    
  /*CHECKING IF IT'S THE SAME RELATIONSHIP*/
  
  if ( sonOrDaughterId == newSonOrDaughterId )
    if ( fatherOrMotherId == newFatherOrMotherId )
      return ( EDIT_PARENT_RELATIONSHIP__NO_CHANGES_IN_RELATIONSHIP_REQUIRED );
      
  /*CHECKING IF THERE'S NO GENDER CONFLICT */
  
  if ( ( retCode = getDataFromId ( fatherOrMotherId, &tempDataTwo) ) != OK )
    return ( retCode );
  
  if ( sonOrDaughterId == newSonOrDaughterId )
  {
    if ( tempData.gender != tempDataTwo.gender ) /* SAY TO USE EDIT_PARENT_RELATIONSHIP AND/OR EXCLUDE_PARENT_RELATIONSHIP_INSTEAD )*/
      return ( EDIT_PARENT_RELATIONSHIP_OLD_PARENT_AND_NEW_PARENT_HAVE_OTHER_SEX );
  }
   
  /*PERFORMING NEEDED OPERATIONS IN THE PARENTS FILE TO EXCLUDE THE OLD RELATIONSHIP*/ 
  
  if ((retCode = getLongFilename (DATA_DIR, PARENTS_FILE_NAME , parentsFileName)) != OK)
    return (retCode);

  if ((rParentsFile = fopen (parentsFileName, "r")) == NULL)
  {
    if (errno != ENOENT)
      return (EDIT_PARENT_RELATIONSHIP__ERROR_OPENING_PARENTS_FILE_FOR_READING);
    return (EDIT_PARENT_RELATIONSHIP__PARENTS_FILE_DOES_NOT_EXIST);
  }

  if ((retCode = getLongFilename (DATA_DIR, PARENTS_TEMP_FILE_NAME , parentsFileNameTmp)) != OK)
    return (retCode);

  if ((wParentsFile = fopen (parentsFileNameTmp , "w")) == NULL)
  {
    fclose ( rParentsFile );
    return (EDIT_PARENT_RELATIONSHIP__ERROR_OPENING_PARENTS_TEMP_FILE_FOR_WRITING);
  }
  
  found = false;
     
  for (retCode = 0; retCode != GET_USER_ID__END_OF_FILE;)  
  {
    if ((retCode = getUserId ( rParentsFile, &buffer)) != OK )
    {
      if (retCode != GET_USER_ID__END_OF_FILE)
      {
        fclose (rParentsFile);
        fclose (wParentsFile);
        remove (parentsFileNameTmp);
        return (retCode);
      }
    }
    if ((retCode = getUserId ( rParentsFile, &bufferTwo)) != OK )
    {
      if (retCode != GET_USER_ID__END_OF_FILE)
      {
        fclose (rParentsFile);
        fclose (wParentsFile);
        remove (parentsFileNameTmp);
        return (retCode);
      }
    }    
    if (retCode != GET_USER_ID__END_OF_FILE) /*EXCLUDING OLD PARENT RELATIONSHIP*/
    {  
      if (( buffer == sonOrDaughterId ) && ( bufferTwo == fatherOrMotherId ))
        found = true;
      else
      {
        if ((retCode2 = putUserId (wParentsFile, &buffer)) != OK )
        {
          fclose (rParentsFile);
          fclose (wParentsFile);
          remove (parentsFileNameTmp);
          return (retCode2);
        }
        if ((retCode2 = putUserId (wParentsFile, &bufferTwo)) != OK )
        {
          fclose (rParentsFile);
          fclose (wParentsFile);
          remove (parentsFileNameTmp);
          return (retCode2);
        }
      }   
    }            
  }
  
  if (! found ) /*OLD RELATIONSHIP NOT FOUND*/
  {
    fclose (rParentsFile);
    fclose (wParentsFile);
    remove (parentsFileNameTmp);
    return (EDIT_PARENT_RELATIONSHIP__GIVEN_OLD_RELATIONSHIP_NOT_FOUND);
  }  

  fclose (rParentsFile);
  fclose (wParentsFile);
  rename (parentsFileNameTmp, parentsFileName);
  
  /*INCLUDING NEW RELATIONSHIP*/
  
  if ((rParentsFile = fopen (parentsFileName, "r")) == NULL)
  {
    if (errno != ENOENT)
      return (EDIT_PARENT_RELATIONSHIP__ERROR_OPENING_PARENTS_FILE_FOR_READING);
    return (EDIT_PARENT_RELATIONSHIP__PARENTS_FILE_DOES_NOT_EXIST);
  }
  
  if ((wParentsFile = fopen (parentsFileNameTmp , "w")) == NULL)
  {
    fclose ( rParentsFile );
    return (EDIT_PARENT_RELATIONSHIP__ERROR_OPENING_PARENTS_TEMP_FILE_FOR_WRITING);
  }
  
  for (retCode = 0, found = false; retCode != GET_USER_ID__END_OF_FILE;)  
  {
    if ((retCode = getUserId ( rParentsFile, &buffer)) != OK )
    {
      if (retCode != GET_USER_ID__END_OF_FILE)
      {
        fclose (rParentsFile);
        fclose (wParentsFile);
        remove (parentsFileNameTmp);
        return (retCode);
      }
    }
    if ((retCode = getUserId ( rParentsFile, &bufferTwo)) != OK )
    {
      if (retCode != GET_USER_ID__END_OF_FILE)
      {
        fclose (rParentsFile);
        fclose (wParentsFile);
        remove (parentsFileNameTmp);
        return (retCode);
      }
    }    
    if (retCode != GET_USER_ID__END_OF_FILE) /*SEARCH FOR THE POSITION WHERE THE PARENT RELATIONSHIP IS GOING TO BE INCLUDED*/
    {  
      if ( buffer > newSonOrDaughterId ) /*IT`S IN THE POSITION WHERE THE PARENT RELATIONSHIP SHOULD BE INCLUDED*/
      {
        if ( !found )
	{
          if ((retCode2 = putUserId (wParentsFile, &newSonOrDaughterId)) != OK )
          {
            fclose (rParentsFile);
            fclose (wParentsFile);
            remove (parentsFileNameTmp);
	    return (retCode2);
          }
	  if ((retCode2 = putUserId (wParentsFile, &newFatherOrMotherId)) != OK )
          {
            fclose (rParentsFile);
            fclose (wParentsFile);
            remove (parentsFileNameTmp);
	    return (retCode2);
          }
	  
	  found = true;
	  
	}
        if ((retCode2 = putUserId (wParentsFile, &buffer)) != OK )
        {
          fclose (rParentsFile);
          fclose (wParentsFile);
          remove (parentsFileNameTmp);
	  return (retCode2);
        }     
        if ((retCode2 = putUserId (wParentsFile, &bufferTwo)) != OK )
        {
          fclose (rParentsFile);
          fclose (wParentsFile);
          remove (parentsFileNameTmp);
	  return (retCode2);
        }
      }
      if ( buffer == newSonOrDaughterId )
      {
        /*CHECKING IF THERE'S ALREADY THE REQUIRED PARENT*/
        if ( ( retCode2 = getDataFromId ( bufferTwo, &tempData) ) != OK )
	{
	  fclose (rParentsFile);
          fclose (wParentsFile);
          remove (parentsFileNameTmp);
	  return (retCode2);
	}
	
        if ( bufferTwo < newFatherOrMotherId ) /*IT`S BEFORE THE POSITION WHERE THE PARENT RELATIONSHIP IS GOING TO BE INCLUDED*/
	{
	  if ((retCode2 = putUserId (wParentsFile, &buffer)) != OK )
          {
            fclose (rParentsFile);
            fclose (wParentsFile);
            remove (parentsFileNameTmp);
	    return (retCode2);
          }     
          if ((retCode2 = putUserId (wParentsFile, &bufferTwo)) != OK )
          {
            fclose (rParentsFile);
            fclose (wParentsFile);
            remove (parentsFileNameTmp);
	    return (retCode2);
          } 
	}
	
	if ( bufferTwo > newFatherOrMotherId ) /*IT`S IN THE POSITION WHERE THE PARENT RELATIONSHIP SHOULD BE INCLUDED*/
	{
	  if ( !found )
	  {
	    if ((retCode2 = putUserId (wParentsFile, &newSonOrDaughterId)) != OK )
            {
              fclose (rParentsFile);
              fclose (wParentsFile);
              remove (parentsFileNameTmp);
	      return (retCode2);
            }
	    if ((retCode2 = putUserId (wParentsFile, &newFatherOrMotherId)) != OK )
            {
              fclose (rParentsFile);
              fclose (wParentsFile);
              remove (parentsFileNameTmp);
	      return (retCode2);
            }
	    
	    found = true;
	    
	  }
          if ((retCode2 = putUserId (wParentsFile, &buffer)) != OK )
          {
            fclose (rParentsFile);
            fclose (wParentsFile);
            remove (parentsFileNameTmp);
	    return (retCode2);
          }     
          if ((retCode2 = putUserId (wParentsFile, &bufferTwo)) != OK )
          {
            fclose (rParentsFile);
            fclose (wParentsFile);
            remove (parentsFileNameTmp);
	    return (retCode2);
          }
	}
      }
      if ( buffer < newSonOrDaughterId ) /*IT`S BEFORE THE POSITION WHERE THE PARENT RELATIONSHIP IS GOING TO BE INCLUDED*/
      {
        if ((retCode2 = putUserId (wParentsFile, &buffer)) != OK )
        {
          fclose (rParentsFile);
          fclose (wParentsFile);
          remove (parentsFileNameTmp);
	  return (retCode2);
        }     
        if ((retCode2 = putUserId (wParentsFile, &bufferTwo)) != OK )
        {
          fclose (rParentsFile);
          fclose (wParentsFile);
          remove (parentsFileNameTmp);
	  return (retCode2);
        }
      }
    }            
  }
  
  if (! found ) /*IT`S THE LAST PARENT RELATIONSHIP OF THE FILE*/
  {
    if ((retCode2 = putUserId (wParentsFile, &newSonOrDaughterId)) != OK )
    {
      fclose (rParentsFile);
      fclose (wParentsFile);
      remove (parentsFileNameTmp);
      return (retCode2);
    }
    if ((retCode2 = putUserId (wParentsFile, &newFatherOrMotherId)) != OK )
    {
      fclose (rParentsFile);
      fclose (wParentsFile);
      remove (parentsFileNameTmp);
      return (retCode2);
    }
  }  
    
  /*RENAMEING THE TEMP FILE NAMES TO REPLACE DE OLD ONES*/
  fclose (rParentsFile);
  fclose (wParentsFile);
  rename (parentsFileNameTmp, parentsFileName);
  
  return (OK);  
}

/*$RCSfile: editParentRelationship.c,v $*/


