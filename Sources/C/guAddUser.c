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


#include <stdio.h>             // File manipulation
#include <string.h>            // Strcpy

#include "guAddUser.h"         // guAddUser prototype
#include "guConfig.h"          // Admin id, GU_USER_DATA_FILENAME
#include "guConst.h"		   // Several length constants
#include "guFunctions.h"	   // guCreateStringFromUserData

guErrorType guAddUser(guUserDataType *user)
{
 
  FILE *usersFile;
  guErrorType returnCode;	

  /*Checking if our pointer argument exists*/

  if (!user)
    return guNullPointer;

  /*Now we should check if our user's fields
  are valid*/
  
  if (!(returnCode = GuCheckStringField(user->username, 
  	                                    GU_VALID_USERNAME_CHARACTERS, 
  	                                    GU_MIN_USERNAME_LENGTH,
  	                                    GU_MAX_USERNAME_LENGTH)))
  	return returnCode;


  if (!(returnCode = GuCheckNickname(user->nickname, 
  	                                 GU_VALID_NICKNAME_CHARACTERS, 
  	                                 GU_MIN_NICKNAME_LENGTH,
  	                                 GU_MAX_NICKNAME_LENGTH)))
  	return returnCode;

  if (!(returnCode = GuCheckEmail(user->email, 
  	                              GU_VALID_EMAIL_CHARACTERS, 
  	                              GU_MIN_EMAIL_LENGTH,
  	                              GU_MAX_EMAIL_LENGTH)))
  	return returnCode;
 

  /*The way this function behaves depends on the prior
  existance of the users file*/

  if ((usersFile = fopen(GU_USER_DATA_FILENAME, "r")))
  {
     /*If the users file already exists, there are two options:
     (a) : if user->password and user->password check !=NULL,
           write the user to the user file.
     (b) : if either of the above mentioned fields is empty,
           we must invite the user by sending him/her an email.
     */

  	fclose(usersFile); 

   
  	if(strcmp (user->password,""))
    {
      /*option (b)*/

    }
    else
    {
      /*option (a)*/
      usersFile = fopen (GU_USER_DATA_FILENAME, "w");
      
      fprintf(usersFile, "%llu:%s:%s:%u:%s:%s", user->id, user->nickname, 
      	      user->password, user->profile, user->username, user->email);
      
      fclose(usersFile); 

    }
  

  }
  else
  {
    /*If te users file does not exist, we must create it and add
    the current user as the system admin.*/
    usersFile = fopen (GU_USER_DATA_FILENAME, "w");
    
    fprintf(usersFile, "%llu:%s:%s:%u:%s:%s", (unsigned long long) 0, 
    	    user->nickname, user->password, guAdmin, user->username, user->email);
    
    fclose(usersFile); 


  }
  

  
  return guOk; 
}



/* $RCSfile$ */