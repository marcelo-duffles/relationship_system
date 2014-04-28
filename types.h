//===========================================================================// 
// Universidade Federal do Rio de Janeiro
// Escola Politécnica
// Departamento de Eletrônica e de Computação
// Professor Marcelo Luiz Drumond Lanza
// Computation II - Class 2004/2
// Authors: Carlo Fragni and Marcelo Duffles Donato Moreira
// Description: Types header file 
// Date: 22/10/2004
//===========================================================================//

/* 
 * RCS COMMENTS
 *
 * $Date: 2004/12/15 18:15:39 $
 * $Log: types.h,v $
 * Revision 1.10  2004/12/15 18:15:39  marceloddm
 * tempUserDataType has been removed
 *
 * Revision 1.9  2004/12/15 01:38:42  marceloddm
 * tempUserDataType have been defined
 *
 * Revision 1.7  2004/12/14 02:55:21  marceloddm
 * Grammar corrections have been made
 *
 * Revision 1.6  2004/12/13 08:02:03  marceloddm
 * Lines added: #undef false
 * #undef true
 *
 * Revision 1.5  2004/12/11 12:38:50  marceloddm
 * Author changed for 'marceloddm'
 *
 * Revision 1.4  2004/11/30 00:30:43  root
 * Last modification: userDataType
 *
 * Revision 1.3  2004/11/27 00:30:11  root
 * Next step: complete the missing spaces
 *
 * Revision 1.2  2004/11/26 13:52:39  root
 * RCS's strings added
 *
 */ 
 
 
#ifndef _TYPES_H_
#define _TYPES_H_ "@(#)types.h $Revision: 1.10 $"


#include "const.h"

#define BYTE unsigned char 
#define userIdType unsigned long long

#undef false
#undef true
typedef enum {false, true} boolean;
typedef enum {administrator = 1, webUser, relative} userCategoryType;
typedef enum {notAnswered, male, female} genderType;
typedef enum {notGiven, single, married, widowed} relationshipStatusType;


typedef struct
{
  char street[MAX_LENGTH_STREET +1];
  char homeNumber[MAX_LENGTH_HOME_NUMBER +1];
  char complement[MAX_LENGTH_COMPLEMENT +1];
  char district[MAX_LENGTH_DISTRICT +1]; 
  char city[MAX_LENGTH_CITY +1];
  char state[MAX_LENGTH_STATE +1];
  char country[MAX_LENGTH_COUNTRY +1];
  char zipCode[MAX_LENGTH_ZIP_CODE +1];
} userAddressType; 

typedef struct tUserDataType
{
  userIdType userId;
  char userName[MAX_LENGTH_USERNAME +1];
  char plainPass[MAX_LENGTH_PLAIN_PASS +1];
  char encryptedPass[ENCRYPTED_PASS_LENGTH +1];
  userCategoryType category;
  char name[MAX_LENGTH_NAME +1];
  char email[MAX_LENGTH_EMAIL +1];
  char homepage[MAX_LENGTH_HOMEPAGE +1];
  userAddressType address;
  char telNumber[MAX_LENGTH_TEL_NUMBER +1];
  char cellNumber[MAX_LENGTH_CELL_NUMBER +1];
  genderType gender;
  relationshipStatusType relationshipStatus;
  char birthday[MAX_LENGTH_BIRTHDAY +1];
  char description[MAX_LENGTH_DESCRIPTION +1];
  struct tUserDataType *next;
} userDataType;

typedef struct tFamilyTreeType
{
  userIdType userId;
  struct tFamilyTreeType *parent;
  struct tFamilyTreeType *spouse;
  struct tFamilyTreeType *brother;
  struct tFamilyTreeType *son;
  struct tFamilyTreeType *next;
} familyTreeType;


#endif

// $RCSfile: types.h,v $
