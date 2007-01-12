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

#ifndef GU_USERINTERFACE_H 
#define GU_USERINTERFACE_H "@(#)guUserInterface.h $Revision$"

#include "guTypes.h"

typedef enum {guWelcomeMessage, guByMessage, guUsernameMessage, guPasswordMessage, 
              guLoginMessage, guSignUpMessage1, guSignUpMessage2, guSignUpMessage3, 
              guLostPWMessage, guLicenseMessage, guHelpMessage,guLicenseUrl, 
              guConfirmMessage, guRequestMessage} guUserInterfaceMessageNumberType;

char *
GuGetCliUserInterfaceMessage (guUserInterfaceMessageNumberType, guLanguageType);

char *
GuGetNcursesUserInterfaceMessage (guUserInterfaceMessageNumberType, guLanguageType);

char *
GuGetWebUserInterfaceMessage (guUserInterfaceMessageNumberType, guLanguageType);



#endif /* #ifndef GU_USERINTERFACE_H */

/* $RCSfile$ */


