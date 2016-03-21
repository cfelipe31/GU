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


#define _XOPEN_SOURCE   600

#include <stdio.h>             // File manipulation
#include <string.h>            // Strcpy
#include <unistd.h>
#include <time.h>

#include "guAddUser.h"         // guAddUser prototype
#include "guConfig.h"          // Admin id, GU_USER_DATA_FILENAME
#include "guConst.h"       // Several length constants
#include "guFunctions.h"     // guCreateStringFromUserData



#include "Libraries/sendmail.h"

guErrorType GuAddUser(guUserDataType *user)
{
 
  FILE *usersFile;
  guErrorType returnCode; 

  char firstNickname[GU_MAX_NICKNAME_LENGTH];
  char secondNickname[GU_MAX_NICKNAME_LENGTH];
  char *encryptedPassword;
  char salt[GU_SHA512_SALT_LENGTH] = {0};
  char sha512Salt[GU_SHA512_SALT_LENGTH + 4] = {0};
  char tempPassword[GU_MAX_PASSWORD_LENGTH];

  char currentChar;

  unsigned lines = 0;

  time_t currentTime, validity;


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

    //printf("Users file  found!\n");

    //printf("password: %s\n", user->password);
    

    //printf("User password not empty! Adding user!\n");
    
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
    
    usersFile = fopen (GU_USERS_DATA_FILENAME, "r");


    //Counting lines to see last avalible ID
    while(!feof(usersFile))
    {
      currentChar = fgetc(usersFile);
      if(currentChar == '\n')
      {
        lines++;
      }
    }

    fclose(usersFile);

    //printf("Lines: %u\n", lines);
   
    user->id = (unsigned long long) lines + 1;


    if(strcmp(user->password, ""))
    {
      printf("User is added\n");
      returnCode = GuCreateRandomString(GU_VALID_SALT_CHARACTERS, GU_SHA512_SALT_LENGTH, salt);
      
      if(returnCode)
        return returnCode;

      sprintf(sha512Salt, "$6$%s$", salt);

      encryptedPassword = crypt(user->password, sha512Salt);

      usersFile = fopen (GU_USERS_DATA_FILENAME, "a");
  
      fprintf(usersFile, "\n%llu:%s:%s:%u:%s:%s:", user->id, user->nickname, 
            encryptedPassword, user->profile, user->username, user->email);
  
      fclose(usersFile); 

      return guOk;

    }
    else
    { 
      printf("User is invited\n");
      //Add user

      strcpy(tempPassword, "123456");

      usersFile = fopen (GU_USERS_DATA_FILENAME, "a");
  
      fprintf(usersFile, "\n%llu:%s:%s:%u:%s:%s:", user->id, user->nickname, 
            " ", user->profile, user->username, user->email);
  
      fclose(usersFile); 
 
      currentTime = time(NULL);

      validity = currentTime + 60 * 60 * GU_NEW_USER_REQUEST_VALIDITY;

      //Add user to invitation file
      usersFile = fopen (GU_INVITED_USERS_DATA_FILENAME, "a");

      fprintf(usersFile, "%llu:%s:%lld:\n", user->id, "123456", (long long) validity);

      fclose(usersFile); 


      //Send invite email
      {/*MESSAGE BLOCK*/
        char emailMessage[1000];
      
        sprintf(emailMessage, "Hi!\nYou were invited to GNUBER,"
                              " the FOOS hitchiking app. \n\n\n"
                              "Your username: %s\n"
                              "Your temp password:: %s\n\n\n"
                              "Access: %s\n\n"
                              "This offer is valid for %uh\n",
                              user->nickname, tempPassword,
                              GU_WEB_SERVER_URL,
                              GU_NEW_USER_REQUEST_VALIDITY);
      

      /*
        if (sendMail("del.ufrj.br", "smtp.del.ufrj.br", 25, 
                     "do-not-reply@gnuber.com", user->email, 
                     0, 0, "GNUber Invitation", emailMessage, 0))
          return guEmailFailed;
      */

    }

      return guOk;
    }


    

  }
  else
  {
    /*If the users file does not exist, we must create it and add
    the current user as the system admin.*/

    /*First we need to check if the admin data is correct*/
    //printf("Users file not found! Creating Admin account.\n");

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