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

static char *guCliUserInterfaceMessages[2][20] = {
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
                                                   "Request Membership",
                                                   "Friend Email",
                                                   "Please type your password",
                                                   "User authenticated sucessfully!",
                                                   "User added sucessfully!",
                                                   "Please type the new user's password",
                                                   "User invited sucessfully!"
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
                                                   "Requerer Inscricao",
                                                   "Email do Amigo",
                                                   "Por favor digite sua senha",
                                                   "Usuario autenticado com sucesso!",
                                                   "Usuario adicionado com sucesso!",
                                                   "Por favor digite a senha do novo usuario",
                                                   "Usuario convidado com sucesso!"

                                                  }
                                                };

static char *guNcursesUserInterfaceMessages[2][20] = {
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
                                                       "Request Membership",
                                                       "Friend Email",
                                                       "Please type your password",
                                                       "User authenticated sucessfully!",
                                                       "User added sucessfully!",
                                                       "Please type the new user's password",
                                                       "User invited sucessfully!"

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
                                                       "Requerer Inscricao",
                                                       "Email do Amigo",
                                                       "Por favor digite sua senha",
                                                       "Usuario autenticado com sucesso!",
                                                       "Usuario adicionado com sucesso!",
                                                       "Por favor digite a senha do novo usuario"
                                                       "Usuario convidado com sucesso!"

                                                      }
                                                    };

static char *guWebUserInterfaceMessages[2][20] = {
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
                                                   "Request Membership",
                                                   "Friend Email",
                                                   "Please type your password",
                                                   "User authenticated sucessfully!",
                                                   "User added sucessfully!",
                                                   "Please type the new user's password",
                                                   "User invited sucessfully!"


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
                                                   "Requerer Inscricao",
                                                   "Email do Amigo",
                                                   "Por favor digite sua senha",
                                                   "Usuario autenticado com sucesso!",
                                                   "Usuario adicionado com sucesso!",
                                                   "Por favor digite a senha do novo usuario",
                                                   "Usuario convidado com sucesso!"
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
