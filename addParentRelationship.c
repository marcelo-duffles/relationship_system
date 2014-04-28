//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: Source file of the primary function addParentRelationship().
// Date: 28/12/2004
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2005/02/16 22:11:21 $
 * $Log: addParentRelationship.c,v $
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
  
static const char rcsid [] = "$Id: addParentRelationship.c,v 1.1 2005/02/16 22:11:21 marceloddm Exp marceloddm $";
  
unsigned addParentRelationship ( userIdType sonOrDaughterId, userIdType fatherOrMotherId)
{
  unsigned retCode, retCode2;
  char parentsFileName [MAX_LENGTH_LONG_FILENAME +1];
  char parentsFileNameTmp [MAX_LENGTH_LONG_FILENAME +1];
  FILE *rParentsFile, *wParentsFile;
  userIdType buffer, bufferTwo;
  boolean found;
  userDataType tempData;
  genderType parentGender;
  
  if ( ( retCode = getDataFromId ( sonOrDaughterId, &tempData) ) != OK )
    return ( retCode );
  
  /*CHECKING IF IT'S THE MOTHER, FATHER OR IF THE GIVEN PERSON HAS NO GENDER ANSWERED*/
  
  if ( ( retCode = getDataFromId ( fatherOrMotherId, &tempData) ) != OK )
    return ( retCode );
  
  if ( ( parentGender = tempData.gender  ) == notAnswered )
    return ( ADD_PARENT_RELATIONSHIP__GIVEN_PARENT_HAS_NO_GENDER_ANSWERED );
   
  /*PERFORMING NEEDED OPERATIONS IN THE PARENTS FILE*/ 
  
  if ((retCode = getLongFilename (DATA_DIR, PARENTS_FILE_NAME , parentsFileName)) != OK)
    return (retCode);

  if ((rParentsFile = fopen (parentsFileName, "r")) == NULL)
  {
    if (errno != ENOENT)
      return (ADD_PARENT_RELATIONSHIP__ERROR_OPENING_PARENTS_FILE_FOR_READING);
    return (ADD_PARENT_RELATIONSHIP__PARENTS_FILE_DOES_NOT_EXIST);
  }

  if ((retCode = getLongFilename (DATA_DIR, PARENTS_TEMP_FILE_NAME , parentsFileNameTmp)) != OK)
    return (retCode);

  if ((wParentsFile = fopen (parentsFileNameTmp , "w")) == NULL)
  {
    fclose ( rParentsFile );
    return (ADD_PARENT_RELATIONSHIP__ERROR_OPENING_PARENTS_TEMP_FILE_FOR_WRITING);
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
    if (retCode != GET_USER_ID__END_OF_FILE) /*SEARCH FOR THE POSITION WHERE THE PARENT RELATIONSHIP IS GOING TO BE INCLUDED*/
    {  
      if ( buffer > sonOrDaughterId ) /*IT`S IN THE POSITION WHERE THE PARENT RELATIONSHIP SHOULD BE INCLUDED*/
      {
        if ( !found )
	{
          if ((retCode2 = putUserId (wParentsFile, &sonOrDaughterId)) != OK )
          {
            fclose (rParentsFile);
            fclose (wParentsFile);
            remove (parentsFileNameTmp);
	    return (retCode2);
          }
	  if ((retCode2 = putUserId (wParentsFile, &fatherOrMotherId)) != OK )
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
      if ( buffer == sonOrDaughterId )
      {
        /*CHECKING IF THERE'S ALREADY THE REQUIRED PARENT*/
        if ( ( retCode2 = getDataFromId ( bufferTwo, &tempData) ) != OK )
	{
	  fclose (rParentsFile);
          fclose (wParentsFile);
          remove (parentsFileNameTmp);
	  return (retCode2);
	}
	
	if ( tempData.gender == parentGender )
	{
	  if ( parentGender == male )
	  {
	    fclose (rParentsFile);
            fclose (wParentsFile);
            remove (parentsFileNameTmp);
	    return (ADD_PARENT_RELATIONSHIP__USER_ALREADY_HAS_A_FATHER);
	  }
	  else
	  {
	    fclose (rParentsFile);
            fclose (wParentsFile);
            remove (parentsFileNameTmp);
	    return ( ADD_PARENT_RELATIONSHIP__USER_ALREADY_HAS_A_MOTHER );
	  }
	}
	
        if ( bufferTwo < fatherOrMotherId ) /*IT`S BEFORE THE POSITION WHERE THE PARENT RELATIONSHIP IS GOING TO BE INCLUDED*/
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
	if ( bufferTwo == fatherOrMotherId ) /*PARENT ALREADY EXISTS*/
	{
	  fclose (wParentsFile);
	  fclose (rParentsFile);
	  remove (parentsFileNameTmp);
	  return ( ADD_PARENT_RELATIONSHIP__GIVEN_PERSON_IS_ALREADY_PARENT_OF_THE_GIVEN_USER );
	}
	
	if ( bufferTwo > fatherOrMotherId ) /*IT`S IN THE POSITION WHERE THE PARENT RELATIONSHIP SHOULD BE INCLUDED*/
	{
	  if ( !found )
	  {
	    if ((retCode2 = putUserId (wParentsFile, &sonOrDaughterId)) != OK )
            {
              fclose (rParentsFile);
              fclose (wParentsFile);
              remove (parentsFileNameTmp);
	      return (retCode2);
            }
	    if ((retCode2 = putUserId (wParentsFile, &fatherOrMotherId)) != OK )
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
      if ( buffer < sonOrDaughterId ) /*IT`S BEFORE THE POSITION WHERE THE PARENT RELATIONSHIP IS GOING TO BE INCLUDED*/
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
    if ((retCode2 = putUserId (wParentsFile, &sonOrDaughterId)) != OK )
    {
      fclose (rParentsFile);
      fclose (wParentsFile);
      remove (parentsFileNameTmp);
      return (retCode2);
    }
    if ((retCode2 = putUserId (wParentsFile, &fatherOrMotherId)) != OK )
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

/*$RCSfile: addParentRelationship.c,v $*/


