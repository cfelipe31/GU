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
#define _XOPEN_SOURCE 500



#include "guConst.h"
#include "guConfig.h"
#include "guTypes.h"
#include "guErrors.h"
#include "guUserInterface.h"
#include "guFunctions.h"
#include "guAddUser.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
//#include <conio.h>

/*getuid()*/
#include <sys/types.h>
#include <getopt.h>
#include <string.h>

typedef enum
{
  guEmailOpt,
  guEmailConfirmOpt,
  guLanguageOpt,
  guNicknameOpt,
  guUsernameOpt,
  guUsernameConfirmOpt,
  guProfileOpt,
  guUserOpt

} optIndex;

int
main (int argc, char **argv)
{
  const char *shortOptions = "aChiN";

  struct option longOptions [6] =
  {
    {"add", 0, NULL, 'a'},
    {"Configure", 0, NULL, 'C'},
    {"help", 0, NULL, 'h'},
    {"invite", 0, NULL, 'i'},
    {"Ncurses", 0, NULL, 'N'},
    {NULL, 0, NULL, 0}
  };

  char *optName [ ] =
  {
    "email",
    "confirm-email",
    "language",
    "nickname",
    "username",
    "confirm-username",
    "profile",
    "user",
    NULL
  };

  int shortOption;
  int longOption;
  int optIndex;
  char *options, *optionValue, *userPassword;

  /*Language : all functions*/
  char languageString[GU_MAX_USERNAME_LENGTH];

  /*Return code : all functions*/
  guErrorType returnValue;

  /*Nickname : Ncurses*/
  char nicknameString[GU_MAX_NICKNAME_LENGTH];

  /*Username and email : Configure*/
  char userString[GU_MAX_USERNAME_LENGTH];

  char usernameString[GU_MAX_USERNAME_LENGTH];
  char usernameConfirmString[GU_MAX_USERNAME_LENGTH];
  char emailString[GU_MAX_EMAIL_LENGTH];
  char emailConfirmString[GU_MAX_EMAIL_LENGTH];
  char profileString[GU_MAX_USERNAME_LENGTH];

  /*User ID*/
  guUserIdentifierType userId;

  /*Placeholder for user to be added/logged in*/
  guUserDataType *user;
  

  /*User Placeholder*/
  guUserDataType auxUser;
  guUserDataType executingUser;

  guLanguageType currentLanguage = 0;



  opterr = 0; /* desabilita exibicao de erro */

  if ((shortOption = getopt_long (argc, argv, shortOptions, longOptions, 
                                     &longOption)) != -1)
  {
    switch (shortOption)
    {
      //./gu -a user=carlos.oliveira username=Joao confirm-username=Joao email=cfelipe.domingues@gmail.com confirm-email=cfelipe.domingues@gmail.com language=portuguese
      case 'a':
        printf ("Add user\n");
        while (optind < argc)
        {
          options = argv [optind];
          optIndex =  getsubopt (&options, optName, &optionValue);
          switch (optIndex)
          {

            case guUserOpt:
              printf ("User Executing: \"%s\"\n", optionValue);
              strcpy (userString, optionValue);
              break;

            case guUsernameOpt:
              printf ("Name: \"%s\"\n", optionValue);
              strcpy (usernameString, optionValue);
              break;

            case guUsernameConfirmOpt:
              printf ("Confirm Name: \"%s\"\n", optionValue);
              strcpy (usernameConfirmString, optionValue);
              break;

            case guEmailOpt:
              printf ("Email: \"%s\"\n", optionValue);
              strcpy (emailString, optionValue);
              break;

            case guEmailConfirmOpt:
              printf ("Confirm Email: \"%s\"\n", optionValue);
              strcpy (emailConfirmString, optionValue);
              break;

            case guProfileOpt:
              printf ("Profile: \"%s\"\n", optionValue);
              strcpy (profileString, optionValue);
              break;

            case guLanguageOpt:
              printf ("Idioma: \"%s\"\n", optionValue);
              strcpy (languageString, optionValue);
              break;

            default:
              printf ("Invalid option: %s\n", argv[optind]);
          }
          optind++;
        }

        //Get language
        currentLanguage = GuGetLanguageIndex(languageString); 

        //Check if username is ok
        if(strcmp(usernameString, usernameConfirmString))
        {

          returnValue = guBadConfirmationUsername;
          printf("%s\n", GuGetCliErrorMessage(returnValue, currentLanguage));
          exit(returnValue);
        }
        
        //Authenticate user
        userPassword = getpass(GuGetCliUserInterfaceMessage(guGetPassword, currentLanguage));

        printf("Password: %s\n", userPassword);
        strcpy(executingUser.nickname, userString);
        strcpy(executingUser.password, userPassword); 

        user = &executingUser;

        returnValue = GuAuthenticateUser(user);

        if(returnValue == 0)
        {
          printf("%s\n", GuGetCliUserInterfaceMessage(guUserAuthOk, currentLanguage));
        }
        else
        {
          printf("%s\n", GuGetCliErrorMessage(returnValue, currentLanguage));
          exit(returnValue);
        }
        

        //Add user
        //strcpy(auxUser.username, usernameString);
        strcpy(auxUser.username, "Joao Neves Flores");
        strcpy(auxUser.email, emailString);
        strcpy(auxUser.emailCheck, emailConfirmString);
        auxUser.profile = GuGetProfileIndex(profileString);
        userPassword = getpass(GuGetCliUserInterfaceMessage(guGetNewUserPW, currentLanguage));
        
        strcpy(auxUser.password, userPassword);
        strcpy(auxUser.passwordCheck, userPassword);
        strcpy(auxUser.nickname, "");

        user = &auxUser;

        returnValue = GuAddUser(user);

        if(returnValue != 0)
        {
          printf("%s\n", GuGetCliErrorMessage(returnValue, currentLanguage));
          exit(returnValue);
        }

        printf("%s\n", GuGetCliUserInterfaceMessage(guUserAddOk, currentLanguage));

        return guOk;

        break;
        /* case 'a'*/


      case 'C':
	      printf ("Configure\n");
              strcpy (languageString, GU_DEFAULT_LANGUAGE);
	      while (optind < argc)
	      {
	        options = argv [optind];
	        optIndex =  getsubopt (&options, optName, &optionValue);
	        switch (optIndex)
	        {
	          case guEmailOpt:
	            printf ("Email: \"%s\"\n", optionValue);
              strcpy (emailString, optionValue);
	            break;

	          case guLanguageOpt:
	            printf ("Idioma: \"%s\"\n", optionValue);
              strcpy (languageString, optionValue);
	            break;

	          case guUsernameOpt:
	            printf ("Nome: \"%s\"\n", optionValue);
              strcpy (usernameString, optionValue);
	            break;

	          default:
	            printf ("Invalid option: %s\n", argv[optind]);
	        }
	        optind++;
	      }
        userId = getuid();
        printf("User id: %llu \n", userId);
        printf("Admin id: %d \n", GU_ADMINISTRATOR_USER_IDENTIFIER);  
              
        strcpy(auxUser.username, usernameString);
        strcpy(auxUser.email, usernameString);
        strcpy(auxUser.emailCheck, usernameString);
        if (userId == GU_ADMINISTRATOR_USER_IDENTIFIER)
        {
          printf ("Current user is admin!\n");
        }
        else
        {
          printf ("Sorry, only the program admin can proceed with this operation.\n");
        }

	      break;
	      /* case 'C'*/

      case 'h':
        printf ("Help\n");
        strcpy (languageString, GU_DEFAULT_LANGUAGE);
        while (optind < argc)
        {
          options = argv [optind];
          optIndex =  getsubopt (&options, optName, &optionValue);
          switch (optIndex)
          {
            case guLanguageOpt:
              strcpy (languageString, optionValue);
              printf ("Language: \"%s\"\n", optionValue);
              break;

            default:
              printf ("Invalid option!\n");
              break;
          }
          optind++;
        }
        printf ("Language: \"%s\"\n", languageString);
        /*void guShowCliHelp (GuGetLanguageIndex(languageString));*/
        break;

      //./gu -a user=carlos.oliveira username=Joao confirm-username=Joao email=cfelipe.domingues@gmail.com confirm-email=cfelipe.domingues@gmail.com language=portuguese
      case 'i':
        printf ("Invite user\n");
        while (optind < argc)
        {
          options = argv [optind];
          optIndex =  getsubopt (&options, optName, &optionValue);
          switch (optIndex)
          {

            case guUserOpt:
              printf ("User Executing: \"%s\"\n", optionValue);
              strcpy (userString, optionValue);
              break;

            case guUsernameOpt:
              printf ("Name: \"%s\"\n", optionValue);
              strcpy (usernameString, optionValue);
              break;

            case guUsernameConfirmOpt:
              printf ("Confirm Name: \"%s\"\n", optionValue);
              strcpy (usernameConfirmString, optionValue);
              break;

            case guEmailOpt:
              printf ("Email: \"%s\"\n", optionValue);
              strcpy (emailString, optionValue);
              break;

            case guEmailConfirmOpt:
              printf ("Confirm Email: \"%s\"\n", optionValue);
              strcpy (emailConfirmString, optionValue);
              break;

            case guProfileOpt:
              printf ("Profile: \"%s\"\n", optionValue);
              strcpy (profileString, optionValue);
              break;

            case guLanguageOpt:
              printf ("Idioma: \"%s\"\n", optionValue);
              strcpy (languageString, optionValue);
              break;

            default:
              printf ("Invalid option: %s\n", argv[optind]);
          }
          optind++;
        }

        //Get language
        currentLanguage = GuGetLanguageIndex(languageString); 

        //Check if username is ok
        if(strcmp(usernameString, usernameConfirmString))
        {

          returnValue = guBadConfirmationUsername;
          printf("%s\n", GuGetCliErrorMessage(returnValue, currentLanguage));
          exit(returnValue);
        }
        
        //Authenticate user
        userPassword = getpass(GuGetCliUserInterfaceMessage(guGetPassword, currentLanguage));

        printf("Password: %s\n", userPassword);
        strcpy(executingUser.nickname, userString);
        strcpy(executingUser.password, userPassword); 

        user = &executingUser;

        returnValue = GuAuthenticateUser(user);

        if(returnValue == 0)
        {
          printf("%s\n", GuGetCliUserInterfaceMessage(guUserAuthOk, currentLanguage));
        }
        else
        {
          printf("%s\n", GuGetCliErrorMessage(returnValue, currentLanguage));
          exit(returnValue);
        }
        

        //Invite user
        //strcpy(auxUser.username, usernameString);
        strcpy(auxUser.username, "Joao Neves Flores");
        strcpy(auxUser.email, emailString);
        strcpy(auxUser.emailCheck, emailConfirmString);
        auxUser.profile = GuGetProfileIndex(profileString);
        strcpy(auxUser.password, "");
        strcpy(auxUser.passwordCheck, "");
        strcpy(auxUser.nickname, "");

        user = &auxUser;

        returnValue = GuAddUser(user);

        if(returnValue != 0)
        {
          printf("%s\n", GuGetCliErrorMessage(returnValue, currentLanguage));
          exit(returnValue);
        }

        printf("%s\n", GuGetCliUserInterfaceMessage(guUserInviteOk, currentLanguage));

        return guOk;

        break;
        /* case 'i'*/

      case 'N':
        printf ("Ncurses\n");
        strcpy (languageString, GU_DEFAULT_LANGUAGE);
        while (optind < argc)
        {
          options = argv [optind];
          optIndex =  getsubopt (&options, optName, &optionValue);
          switch (optIndex)
          {
            case guLanguageOpt:
              printf ("Language: \"%s\"\n", optionValue);
              strcpy (languageString, optionValue);
              break;

            case guNicknameOpt:
              printf ("Nickname: \"%s\"\n", optionValue);
              strcpy (nicknameString, optionValue);
              break;

            default:
              printf ("Invalid option!\n");
              break;
          }
          optind++;
        }
        /*returnValue = guRunNcursesInterface (GuGetLanguageIndex(languageString), nicknameString);*/
        break;

    } /*switch indiceArgumento*/
  } /* if shortOption */

  return 0;
}
                                        
/* $RCSfile$ */
