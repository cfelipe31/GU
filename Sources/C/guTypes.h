/*
 *Universidade Federal do Rio de Janeiro
 *Escola Politecnica
 *Departamento de Eletronica e de Computacao
 *Prof. Marcelo Luiz Drumond Lanza
 *EEL 270 - Computacao II - Turma 2015/2
 *    
 *$Author$
 *$Date$
 *$Log$
 */

#ifndef GU_TYPES_H 
#define GU_TYPES_H "@(#)guTypes.h $Revision$"

#include "guConst.h"


typedef enum {guDes, guMd5, guSha256, guSha512} guCryptAlgorithms;

typedef enum {guEnglish, guPortuguese, guNumberLanguages} guLanguageType;

typedef enum {guAdmin, guOwner, guHitchhiker} guGroupType;

typedef enum {guAdminProfile} guProfileType;

typedef unsigned long long guUserIdentifierType;

typedef struct{

  guUserIdentifierType id;
  guProfileType profile;
  
  char username[GU_MAX_USERNAME_LENGTH];
  char nickname[GU_MAX_NICKNAME_LENGTH];
  
  char password[GU_MAX_PASSWORD_LENGTH];
  char passwordCheck[GU_MAX_PASSWORD_LENGTH];
  
  char email[GU_MAX_EMAIL_LENGTH];
  char emailCheck[GU_MAX_EMAIL_LENGTH];

  struct guUserDataType *next;
  struct guUserDataType *prev;

}guUserDataType; 

#endif /* #ifndef GU_TYPES_H */

/* $RCSfile$ */

