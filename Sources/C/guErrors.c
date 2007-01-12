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
static char *guCliErrorMessages[3][3] = {
                                          {"Program successfully executed.",
                                           "Error: reference to NULL pointer.",
                                           "Error: argument cannot be zero"
                                          },
                                          {"Programa executado com sucesso.",
                                           "Erro: referencia para ponteiro nulo",
                                           "Erro: argumento deve possuir um valor nao nulo"
                                          }
                                        };



static char *guNcursesErrorMessages[2][2] = {
                                              {"Program successfully executed.",
                                               "Error: reference to NULL pointer."
                                              },
                                              {"Programa executado com sucesso.",
                                               "Erro: referencia para ponteiro nulo"
                                              }
                                            };

static char *guWebErrorMessages[2][2] = {
                                          {"Program successfully executed.",
                                           "Error: reference to NULL pointer."
                                          },
                                          {"Programa executado com sucesso.",
                                           "Erro: referencia para ponteiro nulo"
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
