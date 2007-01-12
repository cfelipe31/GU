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

#ifndef GU_FUNCTIONS_H 
#define GU_FUNCTIONS_H "@(#)guFunctions.h $Revision$"

#include <stddef.h>

#include "guErrors.h"
#include "guTypes.h"


guErrorType
GuCheckEmail(char *, char *, size_t, size_t);

guErrorType
GuCheckNickname(char *, char *, size_t, size_t);

guErrorType 
GuCheckStringField(char *, char *, size_t, size_t);

guErrorType
GuCreateNickname (char *, char *, char *);

guErrorType 
GuCreateRandomString (char *, unsigned long, char *);

//Crypt password characteristics:
//all generated passwords belong to the alphabet: ./0-9A-Za-z
//DES: two character salt from the alphabet ./0-9A-Za-z, i.e. an 12 bit salt
//generated password has 2 salt characters and more 11 chars (TOTAL 13)
//MD5: a marker $1$, then 8 more salt characters $1$12345678$
//result: $1$8c(salt)$(22 chars)
//SHA-256: a marker $5$ and 16 salt characters :$5$1234567891234567$
//result: $5$18c(salt)$(43 chars)
//SHA-512: a marker $6$ and 16 salt characters
//result: $5$18c(salt)$(86 chars)


guErrorType
GuEncodePasswordWithSpecificAlgorithm (char *, guCryptAlgorithms , char *);

guErrorType
GuEncodePasswordWithSpecificSalt (char *, char *, char *);



guErrorType
GuGetCryptAlgorithm (char *, guCryptAlgorithms *);


guLanguageType 
GuGetLanguageIndex(char *);


#endif /* #ifndef GU_FUNCTIONS_H */

/* $RCSfile$ */

