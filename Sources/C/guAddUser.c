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
//#define _XOPEN_SOURCE   600

#include <stdio.h>             // File manipulation
#include <string.h>            // Strcpy
#include <unistd.h>            //Crypt
#include "guAddUser.h"         // guAddUser prototype
#include "guConfig.h"          // Admin id, GU_USERS_DATA_FILENAME
#include "guConst.h"		       // Several length constants
#include "guFunctions.h"	     // guCreateStringFromUserData



guErrorType GuAddUser(guUserDataType *user)
{
 
  FILE *usersFile;
  guErrorType returnCode;	

  char firstNickname[GU_MAX_NICKNAME_LENGTH];
  char secondNickname[GU_MAX_NICKNAME_LENGTH];
  char *encryptedPassword;
  char salt[GU_SHA512_SALT_LENGTH] = {0};
  char sha512Salt[GU_SHA512_SALT_LENGTH + 4] = {0};

  char currentChar;

  unsigned lines = 0;

  /*Checking if input is NULL*/
  if (!user)
    return guNullPointer;


  /*The way this function behaves depends on the prior
  existance of the users file*/

  if ((usersFile = fopen(GU_USERS_DATA_FILENAME, "r")))
  {
     /*If the users file already exists, there are two options:
     (a) : if user->password and user->password check !=NULL,
           write the user to the user file.
     (b) : if either of the above mentioned fields is empty,
           we must invite the user by sending him/her an email.
     */
    
    fclose(usersFile);

    printf("Users file  found!\n");

    printf("password: %s\n", user->password);
    if(strcmp(user->password, ""))
    {
      printf("User password not empty! Adding user!\n");
      
      returnCode = GuCheckStringField(user->username, 
                                    GU_VALID_USERNAME_CHARACTERS, 
                                    GU_MIN_USERNAME_LENGTH,
                                    GU_MAX_USERNAME_LENGTH);

      if(returnCode)
        return returnCode;

      //Creating nickname
      returnCode = GuCreateNickname(user->username, firstNickname, 
                                    secondNickname);
    
      if(returnCode)
        return returnCode;

      strcpy(user->nickname, firstNickname);
 
      returnCode = GuCheckNickname(user->nickname, 
                                 GU_VALID_NICKNAME_CHARACTERS, 
                                 GU_MIN_NICKNAME_LENGTH,
                                 GU_MAX_NICKNAME_LENGTH);
    
      if(returnCode)
        return returnCode;

      returnCode = GuCheckEmail(user->email, 
                                    GU_VALID_EMAIL_CHARACTERS, 
                                    GU_MIN_EMAIL_LENGTH,
                                    GU_MAX_EMAIL_LENGTH);

      if(returnCode)
        return returnCode;

      if(strcmp(user->email, user->emailCheck))
        return guBadConfirmationEmail;

      if(strcmp(user->password, user->passwordCheck))
        return guBadConfirmationPassword;

      user->profile = guUsers;
    
      returnCode = GuCreateRandomString(GU_VALID_SALT_CHARACTERS, GU_SHA512_SALT_LENGTH, salt);

      if(returnCode)
        return returnCode;

      sprintf(sha512Salt, "$6$%s$", salt);

      encryptedPassword = crypt(user->password, sha512Salt);

      usersFile = fopen (GU_USERS_DATA_FILENAME, "r");

      while(!feof(usersFile))
      {
        currentChar = fgetc(usersFile);
        if(currentChar == '\n')
        {
          lines++;
        }
      }

      fclose(usersFile);

      printf("Lines: %u\n", lines);
     
      user->id = (unsigned long long) lines + 1;

      usersFile = fopen (GU_USERS_DATA_FILENAME, "a");
    
      fprintf(usersFile, "\n%llu:%s:%s:%u:%s:%s:", user->id, user->nickname, 
              encryptedPassword, user->profile, user->username, user->email);
    
      fclose(usersFile); 

      return guOk;
    }
    else
    {
      printf("User password empty! Inviting user!\n");


      return guOk;      
    }

  }
  else
  {
    /*If the users file does not exist, we must create it and add
    the current user as the system admin.*/

    /*First we need to check if the admin data is correct*/
    printf("Users file not found! Creating Admin account.\n");

    returnCode = GuCheckStringField(user->username, 
                                    GU_VALID_USERNAME_CHARACTERS, 
                                    GU_MIN_USERNAME_LENGTH,
                                    GU_MAX_USERNAME_LENGTH);

    if(returnCode)
      return returnCode;

    //Creating nickname
    returnCode = GuCreateNickname(user->username, firstNickname, secondNickname);
    
    if(returnCode)
      return returnCode;

    strcpy(user->nickname, firstNickname);
 
    returnCode = GuCheckNickname(user->nickname, 
                               GU_VALID_NICKNAME_CHARACTERS, 
                               GU_MIN_NICKNAME_LENGTH,
                               GU_MAX_NICKNAME_LENGTH);
    
    if(returnCode)
      return returnCode;

    returnCode = GuCheckEmail(user->email, 
                                  GU_VALID_EMAIL_CHARACTERS, 
                                  GU_MIN_EMAIL_LENGTH,
                                  GU_MAX_EMAIL_LENGTH);

    if(returnCode)
      return returnCode;

    if(strcmp(user->email, user->emailCheck))
      return guBadConfirmationEmail;

    if(strcmp(user->password, user->passwordCheck))
      return guBadConfirmationPassword;

    user->id = (unsigned long long) 0;

    user->profile = guAdministrators;
    
    returnCode = GuCreateRandomString(GU_VALID_SALT_CHARACTERS, GU_SHA512_SALT_LENGTH, salt);

    if(returnCode)
      return returnCode;

    sprintf(sha512Salt, "$6$%s$", salt);

    encryptedPassword = crypt(user->password, sha512Salt);

    usersFile = fopen (GU_USERS_DATA_FILENAME, "w");
    
    fprintf(usersFile, "%llu:%s:%s:%u:%s:%s:", user->id, user->nickname, 
            encryptedPassword, user->profile, user->username, user->email);
    
    fclose(usersFile); 
  }
  
  return guOk; 
}



/* $RCSfile$ */