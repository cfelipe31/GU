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

#ifndef GU_ERRORS_H 
#define GU_ERRORS_H "@(#)guErrors.h $Revision$"

#include "guTypes.h"

typedef enum {guOk, guNullPointer, guZeroValue, guMaxMinInvalid, 
              guSmallString, guBigString, guInvalidString,
              guTooManyDots, guTooManyAmpersands,guZeroLength,
              guNoSurname, guInvalidCryptAlgorithm} guErrorType;

char *
GuGetCliErrorMessage (guErrorType, guLanguageType);

char *
GugetNcursesErrorMessage (guErrorType, guLanguageType);

char *
GuGetWebErrorMessage (guErrorType, guLanguageType);


#endif /* #ifndef GU_ERRORS_H */ 

/* $RCSfile$ */

