//=================================================================//
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira 
// Description: Source file of the primary function mountFamilyTree().
// Date: 17/02/2005
//=================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date$
 * $Log$
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
  
static const char rcsid [] = "$Id$";
  
unsigned mountFamilyTree (userIdType userId, unsigned bottom, unsigned top, familyTreeType **user)
{
  unsigned retCode, index, currentIndex;
  familyTreeType *cursor, *currentSon, *currentBrother, *cursorFather, *cursorMother, *cursorBrother, *cursorSpouse, *cursorSon, *pendingFamilies[MAX_LENGTH_PENDING_FAMILIES];
  
  if ((user == NULL) || (*user == NULL))
    return (MOUNT_FAMILY_TREE__NO_USER_FAMILY);
  
  /* initializing user family... */
  (**user).userId  = userId;
  (**user).parent  = NULL;
  (**user).spouse  = NULL;
  (**user).brother = NULL;
  (**user).son     = NULL;
  
  /* now we have to get the family of the parents and sons/daughters... */
  cursor             = *user; 
  index              = 0;
  currentIndex       = 1;
 /* generationsUp      = 0;
  generationsDown    = 0;*/
  pendingFamilies[0] = NULL;
  
  while (cursor != pendingFamilies[index]) 
  {
    if ((retCode = getUserFamily (cursor->userId, &cursor, *user)) != OK)
      return (retCode);
      
 /*  if ((top == 0) && (bottom == 0))
      return (OK);*/
    
      
    cursorFather  = cursor->parent;
    cursorSpouse  = cursor->spouse;
    cursorBrother = cursor->brother;
    cursorSon     = cursor->son;
    if (cursor->parent != NULL)
      cursorMother = (cursor->parent)->spouse;
    else
      cursorMother = NULL;
    
  //  if (generationsUp < top)
      if ((cursorFather != NULL) && ((retCode = getUserFamily (cursorFather->userId, &(cursorFather), *user)) != OK))
        return (retCode);	

  //  if (generationsUp < top)
      if ((cursorMother != NULL) && ((retCode = getUserFamily (cursorMother->userId, &(cursorMother), *user)) !=  OK))
        return (retCode);
    
    if ((cursorSpouse != NULL) && ((retCode = getUserFamily (cursorSpouse->userId, &(cursorSpouse), *user)) !=  OK))
      return (retCode);
      
    for (currentBrother = cursorBrother; currentBrother != NULL; currentBrother = currentBrother->brother)
      if ((retCode = getUserFamily (currentBrother->userId, &currentBrother, *user)) != OK)
        return (retCode);
	
 //   if (generationsDown < bottom)
      for (currentSon = cursorSon; currentSon != NULL; currentSon = currentSon->brother)
        if ((retCode = getUserFamily (currentSon->userId, &currentSon, *user)) != OK)
          return (retCode);
    	
    /* saving pending families to get them later... */  
    if (cursorFather != NULL)
    {
  //    if (generationsUp < top)
  //   {
	if (cursorFather->parent != NULL)
	{
	  index++;   
          pendingFamilies[index] = cursorFather->parent; 
	}
	if ((cursorFather->parent != NULL) && ((cursorFather->parent)->spouse != NULL))
	{
          index++;   
          pendingFamilies[index] = (cursorFather->parent)->spouse; 
	}
    //  }
      for (currentBrother = cursorFather->brother; currentBrother != NULL; currentBrother = currentBrother->brother)
      {
        index++;
        pendingFamilies[index] = currentBrother;
      }      
    }
    
    if (cursorMother != NULL)
    {
  //    if (generationsUp < top)
  //    {
        if (cursorMother->parent != NULL)
	{
          index++;
          pendingFamilies[index] = cursorMother->parent;
	}
	if ((cursorMother->parent != NULL) && ((cursorMother->parent)->spouse != NULL))
	{
          index++; 
          pendingFamilies[index] = (cursorMother->parent)->spouse;;
	}
  //    }
      for (currentBrother = cursorMother->brother; currentBrother != NULL; currentBrother = currentBrother->brother)
      {
        index++;
        pendingFamilies[index] = currentBrother;
      } 
    }
    
    if (cursorSpouse != NULL)
    {
      if (cursorSpouse->parent != NULL)
      {
        index++;
        pendingFamilies[index] = cursorSpouse->parent;
      }
      if ((cursorSpouse->parent != NULL) && ((cursorSpouse->parent)->spouse != NULL))
      {
        index++; 
        pendingFamilies[index] = (cursorSpouse->parent)->spouse;
      }
      
      for (currentBrother = cursorSpouse->brother; currentBrother != NULL; currentBrother = currentBrother->brother)
      {
        index++;
        pendingFamilies[index] = currentBrother;
      } 
    }
    
    for (currentBrother = cursorBrother; currentBrother != NULL; currentBrother = currentBrother->brother)
    {
      for (currentSon = currentBrother->son; currentSon != NULL; currentSon = currentSon->brother)
      {
        index++;
        pendingFamilies[index] = currentSon;
      }
      if (currentBrother->spouse != NULL)
      {
        index++;
        pendingFamilies[index] = currentBrother->spouse;
      }
    }
    
    for (currentSon = cursorSon; currentSon != NULL; currentSon = currentSon->brother)
    {
      for (currentBrother = currentSon->son; currentBrother != NULL; currentBrother = currentBrother->brother)
      {
   //     if (generationsDown < bottom)
     //   {
          index++;
          pendingFamilies[index] = currentBrother;
      //  }
      }
      if (currentSon->spouse != NULL)
      {
        index++;
        pendingFamilies[index] = currentSon->spouse;
      }
    }
   
    
    /* passing to next family in the list... */
    cursor = pendingFamilies[currentIndex];
    currentIndex++;
  }


  return (OK);
}

/*$RCSfile$*/


