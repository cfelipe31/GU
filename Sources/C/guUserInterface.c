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

#include "guTypes.h"
#include "guUserInterface.h"

static char *guCliUserInterfaceMessages[2][2] = {
                                                  {"Program successfully executed.",
                                                   "Error: reference to NULL pointer."
                                                  },
                                                  {"Programa executado com sucesso.",
                                                   "Erro: referencia para ponteiro nulo"
                                                  }
                                                };

static char *guNcursesUserInterfaceMessages[2][2] = {
                                                      {"Program successfully executed.",
                                                       "Error: reference to NULL pointer."
                                                      },
                                                      {"Programa executado com sucesso.",
                                                       "Erro: referencia para ponteiro nulo"
                                                      }
                                                    };

static char *guWebUserInterfaceMessages[2][14] = {
                                                  {"Welcome to GNUber! - The free Open Source carpooling app\n",
                                                   "by",
                                                   "Username",
                                                   "Password",
                                                   "Login",
                                                   "Do not have an account yet? ",
                                                   "Sign Up",
                                                   " for free.",
                                                   "Lost your password?",
                                                   "Show License",
                                                   "Need help?",
                                                   "license_en-us.txt",
                                                   "Confirm",
                                                   "Request Membership"
                                                  },

                                                  {"Bem vindo ao GNUber! - O aplicativo de caronas gratuito e Open Source\n",
                                                   "por",
                                                   "Usuario",
                                                   "Senha",
                                                   "Entrar",
                                                   "Ainda nao tem uma conta? ",
                                                   "Cadastre-se",
                                                   " gratuitamente.",
                                                   "Esqueceu sua senha?",
                                                   "Exibir Licensa",
                                                   "Precisa de ajuda?",
                                                   "license_pt-br.txt",
                                                   "Confirme seu ",
                                                   "Requerer Inscricao"
                                                  },

                                                };

char *
GuGetCliUserInterfaceMessage (guUserInterfaceMessageNumberType message, guLanguageType language)
{
 return guCliUserInterfaceMessages[language][message];
}

char *
GuGetNcursesUserInterfaceMessage (guUserInterfaceMessageNumberType message, guLanguageType language)
{
  return guNcursesUserInterfaceMessages[language][message];
}

char *
GuGetWebUserInterfaceMessage (guUserInterfaceMessageNumberType message, guLanguageType language)
{
  return guWebUserInterfaceMessages[language][message];
}

/* $RCSfile$ */ 
