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

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/*getuid()*/
#include <sys/types.h>
#include <getopt.h>
#include <string.h>

typedef enum
{
  guEmailOpt,
  guLanguageOpt,
  guNicknameOpt,
  guUsernameOpt,
} optIndex;

int
main (int argc, char **argv)
{
  const char *shortOptions = "ChN";

  struct option longOptions [4] =
  {
    {"Configure", 0, NULL, 'C'},
    {"help", 0, NULL, 'h'},
    {"Ncurses", 0, NULL, 'N'},
    {NULL, 0, NULL, 0}
  };

  char *optName [ ] =
  {
    "email",
    "language",
    "nickname",
    "username",
    NULL
  };

  int shortOption;
  int longOption;
  int optIndex;
  char *options, *optionValue;

  /*Language : all functions*/
  char languageString[GU_MAX_USERNAME_LENGTH];

  /*Return code : all functions*/
  guErrorType returnValue;

  /*Nickname : Ncurses*/
  char nicknameString[GU_MAX_NICKNAME_LENGTH];

  /*Username and email : Configure*/
  char usernameString[GU_MAX_USERNAME_LENGTH];
  char emailString[GU_MAX_EMAIL_LENGTH];

  /*User ID*/
  guUserIdentifierType userId;

  /*Placeholder for user to be added/logged in*/
  guUserDataType *user;
  

  /*User Placeholder*/
  guUserDataType auxUser;

  opterr = 0; /* desabilita exibicao de erro */

  if ((shortOption = getopt_long (argc, argv, shortOptions, longOptions, 
                                     &longOption)) != -1)
  {
    switch (shortOption)
    {
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
