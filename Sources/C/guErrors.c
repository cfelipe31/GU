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
#include "guErrors.h"
#include "guTypes.h"

//[lingua][numerodemenssagens]
static char *guCliErrorMessages[2][20] = {
                                          {"Program successfully executed.",
                                           "Error: reference to NULL pointer.",
                                           "Error: argument cannot be zero",
                                           "Error: minimum string size is bigger than maximum string size",
                                           "Error: string is too small",
                                           "Error: string is too big",
                                           "Error: string is invalid",
                                           "Error: nickname has too many dots",
                                           "Error: email has too many @s",
                                           "Error: string has zero length",
                                           "Error: user has no surname",
                                           "Error: invalid crypt algorithm",
                                           "Error: invalid salt",
                                           "Error: passwords don't match",
                                           "Error: emails doesn't match",
                                           "Error: confirmation password is invalid",
                                           "Error: user not found",
                                           "Error: failed to invite user by email",
                                           "Error: usernames don't match",
                                           "Error: user is not Admin"
                                          },
                                          {"Program successfully executed.",
                                           "Error: reference to NULL pointer.",
                                           "Error: argument cannot be zero",
                                           "Error: minimum string size is bigger than maximum string size",
                                           "Error: string is too small",
                                           "Error: string is too big",
                                           "Error: string is invalid",
                                           "Error: nickname has too many dots",
                                           "Error: email has too many @s",
                                           "Error: string has zero length",
                                           "Error: user has no surname",
                                           "Error: invalid crypt algorithm",
                                           "Error: invalid salt",
                                           "Error: passwords don't match",
                                           "Error: emails doesn't match",
                                           "Error: confirmation password is invalid",
                                           "Error: user not found",
                                           "Error: failed to invite user by email",
                                           "Error: usernames don't match",
                                           "Error: user is not Admin"
                                          }
                                        };



static char *guNcursesErrorMessages[2][20] = {
                                              {"Program successfully executed.",
                                               "Error: reference to NULL pointer.",
                                               "Error: argument cannot be zero",
                                               "Error: minimum string size is bigger than maximum string size",
                                               "Error: string is too small",
                                               "Error: string is too big",
                                               "Error: string is invalid",
                                               "Error: nickname has too many dots",
                                               "Error: email has too many @s",
                                               "Error: string has zero length",
                                               "Error: user has no surname",
                                               "Error: invalid crypt algorithm",
                                               "Error: invalid salt",
                                               "Error: passwords don't match",
                                               "Error: emails doesn't match",
                                               "Error: confirmation password is invalid",
                                               "Error: user not found",
                                               "Error: failed to invite user by email",
                                               "Error: usernames don't match",
                                               "Error: user is not Admin"
                                              },
                                              {"Program successfully executed.",
                                               "Error: reference to NULL pointer.",
                                               "Error: argument cannot be zero",
                                               "Error: minimum string size is bigger than maximum string size",
                                               "Error: string is too small",
                                               "Error: string is too big",
                                               "Error: string is invalid",
                                               "Error: nickname has too many dots",
                                               "Error: email has too many @s",
                                               "Error: string has zero length",
                                               "Error: user has no surname",
                                               "Error: invalid crypt algorithm",
                                               "Error: invalid salt",
                                               "Error: passwords don't match",
                                               "Error: emails doesn't match",
                                               "Error: confirmation password is invalid",
                                               "Error: user not found",
                                               "Error: failed to invite user by email",
                                               "Error: usernames don't match",
                                               "Error: user is not Admin"
                                              }
                                            };

static char *guWebErrorMessages[2][20] = {
                                          {"Program successfully executed.",
                                           "Error: reference to NULL pointer.",
                                           "Error: argument cannot be zero",
                                           "Error: minimum string size is bigger than maximum string size",
                                           "Error: string is too small",
                                           "Error: string is too big",
                                           "Error: string is invalid",
                                           "Error: nickname has too many dots",
                                           "Error: email has too many @s",
                                           "Error: string has zero length",
                                           "Error: user has no surname",
                                           "Error: invalid crypt algorithm",
                                           "Error: invalid salt",
                                           "Error: passwords don't match",
                                           "Error: emails doesn't match",
                                           "Error: confirmation password is invalid",
                                           "Error: user not found",
                                           "Error: failed to invite user by email",
                                           "Error: usernames don't match",
                                           "Error: user is not Admin"
                                          },
                                          {"Program successfully executed.",
                                           "Error: reference to NULL pointer.",
                                           "Error: argument cannot be zero",
                                           "Error: minimum string size is bigger than maximum string size",
                                           "Error: string is too small",
                                           "Error: string is too big",
                                           "Error: string is invalid",
                                           "Error: nickname has too many dots",
                                           "Error: email has too many @s",
                                           "Error: string has zero length",
                                           "Error: user has no surname",
                                           "Error: invalid crypt algorithm",
                                           "Error: invalid salt",
                                           "Error: passwords don't match",
                                           "Error: emails doesn't match",
                                           "Error: confirmation password is invalid",
                                           "Error: user not found",
                                           "Error: failed to invite user by email",
                                           "Error: usernames don't match",
                                           "Error: user is not Admin"
                                          }
                                        };

char *
GuGetCliErrorMessage (guErrorType error, guLanguageType language)
{
  return guCliErrorMessages[language][error];
}

char *
GugetNcursesErrorMessage (guErrorType error, guLanguageType language)
{
  return guNcursesErrorMessages[language][error];
}

char *
GuGetWebErrorMessage (guErrorType error, guLanguageType language)
{
  return guWebErrorMessages[language][error];
}

/* $RCSfile$ */
