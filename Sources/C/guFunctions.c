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
/*srand, rand, malloc*/
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
/*tolower*/
#include <ctype.h>

/*time*/
#include <time.h>
#include <unistd.h>

#include "guFunctions.h"
#include "guConfig.h"


guErrorType 
GuAcceptInvite (char *tempPassword, guUserDataType *user)
{
  FILE *invitesFile;
  FILE *tempFile;

  char buffer[2000];
  char auxBuffer[2000];
  char *auxString;
  unsigned line = 0;
  unsigned found = 0;
  guUserIdentifierType id;
  guUserDataType *current;
  guUserDataType *head;
  guErrorType returnValue;

  tempFile = fopen("temp.bak", "w");

  invitesFile = fopen(GU_INVITED_USERS_DATA_FILENAME, "r");

  //Go through each invited user
  while(fgets(buffer, 2000, invitesFile) != NULL)
  {

    strcpy(auxBuffer,buffer);
    auxString = strtok(buffer, ":");
    id = strtoul(auxString, NULL, 0);
    
    //User Found!
    if(id == user->id)
    {
      found = 1;

      //password
      auxString = strtok(NULL, ":");
      break;
    }
    else
    {
      fputs (auxBuffer,tempFile);
    }

    line++;
  }
  fclose(invitesFile);
  fclose(tempFile);

  rename ("temp.bak", GU_INVITED_USERS_DATA_FILENAME);

  printf("Line:%u\n", line);

  if (found == 0)
    return guUserNotFound;

  printf("Stored temp password: %s\n", auxString);

  if(strcmp(tempPassword, auxString) != 0)
    return guPasswordsDontMatch;


  head = GuCreateListFromFile();
  current = head;


  while(current->prev != NULL)
  {  
    printf("User:%s\n", current->nickname);
    if(current->id == user->id)
    { 
      printf("ID found!\n");
      strcpy(current->password, user->password);
      printf("PW: %s\n", current->password);
    }

    current = current->prev;
  }

  printf("User:%s\n", current->nickname);
  if(current->id == user->id)
  {
    strcpy(current->password, user->password);
  }

  returnValue = GuWriteUsersListToFile(current);

  if (returnValue != 0)
    return returnValue;
  
  /*
  while(head != NULL)
  {
    current = head;
    head = head->prev;
    free(current);
  }
    */
  return guOk;

}

guErrorType
GuAuthenticateUser (guUserDataType *user)
{
  
  guUserDataType *current;
  guUserDataType *head;
  guErrorType returnValue;
  unsigned found = 0;
  
  if (!user)
    return guNullPointer;

  head = GuCreateListFromFile();

  current = head;



  //If user nickname is not first nickname
  do
  {
  
    if(!strcmp(current->nickname, user->nickname))
    {
      found = 1;
      break;
    }

    current = current->prev;
  
  }while(current != NULL);


  if(found == 0)
    return guUserNotFound;

  returnValue = GuCheckPassword (user->password, current->password);

  if(returnValue)
    return returnValue;

  return guOk;
}


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
    {  

      if (validChars[specificChar] == validatedString[stringIndex] || 
          validatedString[stringIndex] == '@')
        break;
    }
    
    if ((validChars[specificChar] != validatedString[stringIndex]) && (validatedString[stringIndex] != '@') )
    {
      return guInvalidString;
    }
    
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
    
    if ((validChars[specificChar] != validatedString[stringIndex]) && (validatedString[stringIndex] != '.'))
    {
      return guInvalidString;
    }
    
    if (validatedString[stringIndex] == '.')
      dotCount++;
  }

  if(dotCount > 1)
    return guTooManyDots;

  return guOk;
}

guErrorType
GuCheckPassword (char *password, char *storedPassword)
{
  char *saltBegin;

  char *saltEnd;

  char *encryptedPassword;

  char auxStoredPassword[GU_MAX_PASSWORD_LENGTH];

  char salt[GU_MAX_PASSWORD_LENGTH];

  guCryptAlgorithms *algorithm;

  guErrorType returnValue = 0;

  /*Checking inputs*/
  if (!password)
    return guNullPointer;
  
  if (!storedPassword)
    return guNullPointer;


  algorithm = (guCryptAlgorithms *) malloc (sizeof(guCryptAlgorithms));

  returnValue = GuGetCryptAlgorithm (storedPassword, algorithm);

  if (returnValue)
  {
    free(algorithm);
    return guInvalidCryptAlgorithm;
  }

  if (*algorithm == guUnknownAlgorithm)
  {
    free(algorithm);
    return guInvalidCryptAlgorithm;
  }

  strcpy(auxStoredPassword, storedPassword);

  if(*algorithm >= 1 && *algorithm <= 3)
  {

    saltBegin = strtok(auxStoredPassword, "$");

    saltEnd = strtok(NULL, "$");

    sprintf(salt, "$%s$%s$", saltBegin, saltEnd);

  }

  if(*algorithm == 0)
  {
    strncpy(salt, storedPassword, 2);
    salt[2] = '\0';
  }


  free(algorithm);

  encryptedPassword = crypt(password, salt);

  if(encryptedPassword == NULL)
    return guInvalidSalt;


  if(strcmp(encryptedPassword, storedPassword) == 0)
  {
    return guOk;
  }
  else
  {
    return guPasswordsDontMatch;
  }

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
    {
      return guInvalidString;
    }

  }
  
  return guOk;
}


//TODO: ERROR CHECKING
//TODO: CORRECT BUFFER SIZE
guUserDataType *GuCreateListFromFile ()
{
  FILE *usersFile;
  char buffer[2000];
  guUserDataType *auxUser = NULL; 
  guUserDataType *head = NULL;
  char *auxString;

  usersFile = fopen(GU_USERS_DATA_FILENAME, "r");
  

  //Go through each user
  while(fgets(buffer, 2000, usersFile) != NULL)
  {
    auxUser = (guUserDataType *) malloc (sizeof(guUserDataType));
   
    auxString = strtok(buffer, ":");

    auxUser->id = strtoul(auxString, NULL, 0);
      
    auxString = strtok(NULL, ":");

    strcpy(auxUser->nickname, auxString);

    auxString = strtok(NULL, ":");

    strcpy(auxUser->password, auxString);

    auxString = strtok(NULL, ":");

    auxUser->profile = strtoul(auxString, NULL, 0);

    auxString = strtok(NULL, ":");

    strcpy(auxUser->username, auxString);

    auxString = strtok(NULL, ":");

    strcpy(auxUser->email, auxString);

    auxUser->next = NULL;
    auxUser->prev = NULL;

    if(head == NULL)
    {
      head = auxUser;
    }
    else
    {
      head->next = (guUserDataType *) auxUser;
      auxUser->prev = (guUserDataType *) head;
      head = auxUser;
    }

  }

  return head;
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
  unsigned index =0;

  if (!name)
    return guNullPointer;

  if (!firstNickname)
    return guNullPointer;

  if (!secondNickname)
    return guNullPointer;


  /*strtok operates on the parsed string*/
  strcpy(auxCompleteName, name);

  //convert complete name to lowercase
  for(index = 0; auxCompleteName[index]; index++)
  {
    auxCompleteName[index] = tolower(auxCompleteName[index]);
  }

  auxName = strtok(auxCompleteName, " ");

  strcpy(firstName, auxName);

  auxName = strtok(NULL, " ");


  if (!auxName)
    return guNoSurname;

  strcpy(lastName, auxName);

  strcpy(middleName, lastName);

  auxName = strtok(NULL, " ");

  if(!auxName)
  {
    sprintf(firstNickname, "%s.%s", firstName, middleName);
    return guOk;
  }

  while(auxName !=  NULL)
  {
 
  if( !(  (strcmp(auxName,"e") == 0) || (strcmp(auxName,"de") == 0)  ))
  {
    strcpy(middleName, lastName);
    strcpy(lastName, auxName); 
  }
  auxName = strtok(NULL, " ");

  }

  sprintf(firstNickname, "%s.%s", firstName, lastName);
  sprintf(secondNickname, "%s.%s", firstName, middleName);

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

  //TODO: CHECK SALT!!!

  char *encodedLocal;

  if(!password)
    return guNullPointer;

  if(!salt)
    return guNullPointer;

  if(!encodedPassword)
    return guNullPointer;

  encodedLocal = crypt(password, salt);

  if(encodedLocal == NULL)
    return guInvalidSalt;

  strcpy(encodedPassword, encodedLocal);

  return guOk;
}





guErrorType
GuGetCryptAlgorithm (char *password, guCryptAlgorithms *algorithm)
{

  char *saltBegin;

  char *saltEnd;

  char auxPassword[GU_MAX_PASSWORD_LENGTH];

  guErrorType returnValueBegin, returnValueEnd = 0;  

  strcpy(auxPassword, password);

  saltBegin = strtok(auxPassword, "$");

  saltEnd = strtok(NULL, "$");

  returnValueBegin = GuCheckStringField (saltBegin, 
                                    GU_VALID_SALT_CHARACTERS,
                                    GU_MIN_PASSWORD_LENGTH, 
                                    GU_MAX_PASSWORD_LENGTH);

  returnValueEnd = GuCheckStringField (saltEnd, 
                                    GU_VALID_SALT_CHARACTERS,
                                    GU_MIN_PASSWORD_LENGTH, 
                                    GU_MAX_PASSWORD_LENGTH);

  // In this case the salt has illegal characters
  if(returnValueBegin == guInvalidString || returnValueEnd == guInvalidString)
  {
    *algorithm = guUnknownAlgorithm;
    return guInvalidCryptAlgorithm;
  }

  if (strlen(saltBegin) == strlen (password))
  {
    *algorithm = guDes;
    return guOk;
  }

  if (!strcmp(saltBegin, "1") && (strlen(saltEnd) == (unsigned) 8) )
  {
    *algorithm = guMd5;
    return guOk;
  }

  if (!strcmp(saltBegin, "5") && (strlen(saltEnd) == (unsigned) 16) )
  {
    *algorithm = guSha256;
    return guOk;
  }

  if (!strcmp(saltBegin, "6") && (strlen(saltEnd) == (unsigned) 16) )
  {
    *algorithm = guSha512;  
    return guOk;
  }

  *algorithm = guUnknownAlgorithm;
  return guInvalidCryptAlgorithm;
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

guProfileType
GuGetProfileIndex(char *profile)
{
  if(!profile)
    return guUsers;

  if(strcmp(profile, "administrator") == 0)
  {
    return guAdministrators;
  }

  return guUsers;
}

guErrorType GuWriteUsersListToFile (guUserDataType *user)
{
  FILE *usersDataFile;
  
  if (!user)
    return guNullPointer;
  
  remove("users");


  if (!(usersDataFile = fopen(GU_USERS_DATA_FILENAME, "w")))
    return guErrorOpeningFile;
  
  while (user->next !=NULL)
  {

    printf("Current user: %s\n", user->password);

    fprintf(usersDataFile, "%llu:%s:%s:%u:%s:%s:\n", user->id, user->nickname, 
            user->password, user->profile, user->username, user->email);

    user = user->next;
  }


  printf("Current user: %s\n", user->password);
  fprintf(usersDataFile, "%llu:%s:%s:%u:%s:%s:", user->id, user->nickname, 
            user->password, user->profile, user->username, user->email);
  
  fclose (usersDataFile);
  
  return guOk;

}
                                        
/* $RCSfile$ */