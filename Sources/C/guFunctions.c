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


#define GU_DEBUG
#define _XOPEN_SOURCE   600

/*sprintf*/
#include <stdio.h>
/*srand, rand*/
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

/*time*/
#include <time.h>
#include <unistd.h>

#include "guFunctions.h"

guErrorType 
GuCheckEmail (char *validatedString, char *validChars,
              size_t minLength, size_t maxLength)
{
  unsigned stringIndex;
  unsigned specificChar;
  unsigned ampersandCount = 0;


  /*Checking passed Data*/
  if (!validChars)
    return guNullPointer;

  if (!validatedString)
    return guNullPointer;

  if (!minLength)
    return guZeroValue;

  if (maxLength < minLength)
    return guMaxMinInvalid;

  /*Verifying length*/
  if (strlen(validatedString) < minLength)
    return guSmallString;

  if (strlen(validatedString) > maxLength)
    return guBigString;

  /*Now looking for invalid chars in the string*/
  for (stringIndex = 0; stringIndex < strlen(validatedString); stringIndex++)
  {
    for (specificChar = 0; specificChar < strlen(validChars); specificChar++)
      if (validChars[specificChar] == validatedString[stringIndex] || 
          validatedString[stringIndex] == '@')
        break;
    
    if (validChars[specificChar] != validatedString[stringIndex])
      return guInvalidString;
    
    if (validatedString[stringIndex] == '@')
      ampersandCount++;
  }

  if(ampersandCount > 1)
    return guTooManyAmpersands;

  return guOk;
}


guErrorType 
GuCheckNickname (char *validatedString, char *validChars,
                 size_t minLength, size_t maxLength)
{
  unsigned stringIndex;
  unsigned specificChar;
  unsigned dotCount = 0;


  /*Checking passed Data*/
  if (!validChars)
    return guNullPointer;

  if (!validatedString)
    return guNullPointer;

  if (!minLength)
    return guZeroValue;

  if (maxLength < minLength)
    return guMaxMinInvalid;

  /*Verifying length*/
  if (strlen(validatedString) < minLength)
    return guSmallString;

  if (strlen(validatedString) > maxLength)
    return guBigString;

  /*Now looking for invalid chars in the string*/
  for (stringIndex = 0; stringIndex < strlen(validatedString); stringIndex++)
  {
    for (specificChar = 0; specificChar < strlen(validChars); specificChar++)
      if (validChars[specificChar] == validatedString[stringIndex] || 
          validChars[specificChar] == '.')
        break;
    
    if (validChars[specificChar] != validatedString[stringIndex])
      return guInvalidString;
    
    if (validatedString[stringIndex] == '.')
      dotCount++;
  }

  if(dotCount > 1)
    return guTooManyDots;

  return guOk;
}

guErrorType 
GuCheckStringField (char *validatedString, char *validChars,
                    size_t minLength, size_t maxLength)
{
  unsigned stringIndex;
  unsigned specificChar;
  

  /*Checking passed Data*/
  if (!validChars)
    return guNullPointer;
  
  if (!validatedString)
    return guNullPointer;
  
  if (!minLength)
    return guZeroValue;
  
  if (maxLength < minLength)
    return guMaxMinInvalid;
  
  /*Verifying length*/
  if (strlen(validatedString) < minLength)
    return guSmallString;
   
  if (strlen(validatedString) > maxLength)
    return guBigString;
  
  /*Now looking for invalid chars in the string*/
  for (stringIndex = 0; stringIndex < strlen(validatedString); stringIndex++)
  {
    for (specificChar = 0; specificChar < strlen(validChars); specificChar++)
      if (validChars[specificChar] == validatedString[stringIndex])
        break;
    if (validChars[specificChar] != validatedString[stringIndex])
      return guInvalidString;
  }
  
  return guOk;
}

guErrorType 
GuCreateRandomString (char *validChar, unsigned long stringLength, char *generatedString)
{

  /*Checking passed Data*/
  if (!validChar)
    return guNullPointer;


  if (!stringLength)
    return guZeroValue;

  if (!generatedString)
    return guNullPointer;

  if (!strlen(validChar))
    return guZeroLength;

  srand(time(NULL));

  /*Generating the string backwards*/
  generatedString[stringLength] = '\0';

  for (; stringLength > 0; stringLength--)
  {
    generatedString[stringLength-1] = validChar[rand()%( (unsigned)strlen(validChar))];
  }

  return guOk;
}

guErrorType 
GuCreateNickname (char *name, char *firstNickname, char *secondNickname)
{

  char *auxName;
  char auxCompleteName[GU_MAX_USERNAME_LENGTH];
  char firstName[GU_MAX_USERNAME_LENGTH];
  char lastName[GU_MAX_USERNAME_LENGTH];
  char middleName[GU_MAX_USERNAME_LENGTH];


  if (!name)
    return guNullPointer;

  if (!firstNickname)
    return guNullPointer;

  if (!secondNickname)
    return guNullPointer;


  /*strtok operates on the parsed string*/
  strcpy(auxCompleteName, name);

  auxName = strtok(auxCompleteName, " ");
  strcpy(firstName, auxName);

  auxName = strtok(auxCompleteName, " ");

  if (!auxName)
    return guNoSurname;

  strcpy(lastName, auxName);

  strcpy(middleName, lastName);

  auxName = strtok(auxCompleteName, " ");

  if(!auxName)
  {
    sprintf(firstNickname, "%s%s", firstName, middleName);
    return guOk;
  }

  while(!(auxName = strtok(auxCompleteName, " ")))
  {
   strcpy(middleName, lastName);
   strcpy(lastName, auxName); 
  }

  sprintf(firstNickname, "%s%s", firstName, lastName);
  sprintf(secondNickname, "%s%s", firstName, middleName);

  return guOk;
}


guErrorType
GuEncodePasswordWithSpecificAlgorithm (char *password, guCryptAlgorithms algorithm, char *encodedPassword)
{
  char saltLocal[GU_MAX_SALT_LENGTH +1];
  char aux[GU_MAX_SALT_LENGTH +1];

  if(!password)
    return guNullPointer;

  if(!encodedPassword)
    return guNullPointer;

  switch(algorithm)
  {
    case guDes:
      GuCreateRandomString(GU_VALID_SALT_CHARACTERS, (unsigned) 2, saltLocal);
      GuEncodePasswordWithSpecificSalt(password, saltLocal, encodedPassword);
      break;

    case guMd5:
      GuCreateRandomString(GU_VALID_SALT_CHARACTERS, (unsigned) 8, aux);
      sprintf(saltLocal, "$1$%s$", aux);
      GuEncodePasswordWithSpecificSalt(password, saltLocal, encodedPassword);
      break;

    case guSha256:
      GuCreateRandomString(GU_VALID_SALT_CHARACTERS, (unsigned) 16, aux);
      sprintf(saltLocal, "$5$%s$", aux);
      GuEncodePasswordWithSpecificSalt(password, saltLocal, encodedPassword);
      break;   
    
    case guSha512:
      GuCreateRandomString(GU_VALID_SALT_CHARACTERS, (unsigned) 16, aux);
      sprintf(saltLocal, "$6$%s$", aux);
      GuEncodePasswordWithSpecificSalt(password, saltLocal, encodedPassword);
      break;


    default:
      return guInvalidCryptAlgorithm;

  }


  return guOk;
}


guErrorType
GuEncodePasswordWithSpecificSalt (char *password, char *salt, char *encodedPassword)
{
  char *encodedLocal;

  if(!password)
    return guNullPointer;

  if(!salt)
    return guNullPointer;

  if(!encodedPassword)
    return guNullPointer;

  encodedLocal = crypt(password, salt);

  strcpy(encodedPassword, encodedLocal);

  return guOk;
}





guErrorType
GuGetCryptAlgorithm (char *password, guCryptAlgorithms *algorithm)
{

  return guOk;
}

guLanguageType
GuGetLanguageIndex(char * language)
{
  if(!language)
    return guEnglish;

  if(strcmp(language, "portuguese") == 0)
  {
    return guPortuguese;
  }
  return guEnglish;
}


                                        
/* $RCSfile$ */
