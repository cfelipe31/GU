/* 
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2015/2
 * Prof. Marcelo Luiz Drumond Lanza
 *
 * Autor: Marcelo Luiz Drumond Lanza
 *
 * $Author$
 * $Date$
 * $Log$
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "Libraries/mlcgi.h" 
#include "guUserInterface.h"
#include "guTypes.h"
#include "guFunctions.h"
#include "guConfig.h"


#define AMBIENTE_EXECUCAO_INVALIDO 	1
#define COMPRIMENTO_MAXIMO_LINGUA	20

int
main (int argc, char **argv)
{
  environmentType ambiente;
  char languageString [COMPRIMENTO_MAXIMO_LINGUA + 1];
  guLanguageType language;
  unsigned codigoRetorno;


  if (mlCgiInitialize (&ambiente))
    exit (ML_CGI_OK);

  if (ambiente == commandLine)
  {
    printf ("Este programa só pode ser executado via web\n");
    exit (AMBIENTE_EXECUCAO_INVALIDO);
  }

  mlCgiBeginHttpHeader ("text/html");
  mlCgiEndHttpHeader ();

  codigoRetorno = mlCgiGetFormStringNoNewLines ("guLanguage", 
                                                languageString, 
                                                COMPRIMENTO_MAXIMO_LINGUA);
  if (codigoRetorno != ML_CGI_OK)
  {
    printf ("Erro obtendo o valor do campo numero - Erro #%i\n", codigoRetorno);
    mlCgiFreeResources ();
    exit (ML_CGI_OK);
  }

  language = GuGetLanguageIndex(languageString);


  printf ("<html>\n");
  printf ("  <head>\n");
  printf ("    <title>\n");
  printf ("      %s\n",
                 GuGetWebUserInterfaceMessage(guWelcomeMessage,language));
  printf ("    </title>\n");
  printf ("  </head>\n");
  printf ("  <body bgcolor=\"white\">\n");
  printf ("    <h1 style=\"text-align: center;\">"
              "<span style=\"color: #cc99ff;\">GNUber</span></h1>\n");
  printf ("    <form style=\"text-align: center;\""
              " action=\"guRequestPasswordReset.cgi\">\n");
  printf ("      Username:<br/> \n");
  printf ("      <input name=\"guNickname\" type=\"text\""
                "maxlength=\"%u\"/>\n",GU_MAX_NICKNAME_LENGTH);
  printf ("      <br/> Email:<br/>\n");
  printf ("      <input name=\"guEmail\""
                "type=\"text\" maxlength=\"%u\"/><br><br>\n",
                 GU_MAX_EMAIL_LENGTH);
  printf ("      <input type=\"submit\" value=\"Reset Password\">");
  printf ("      <input type=\"hidden\" name=\"guLanguage\""
          "      value=\"%s\">\n",languageString);
  printf ("    </form>\n");

  printf ("  </body>\n");
  printf ("</html>\n");

  mlCgiFreeResources ();
  return ML_CGI_OK;
}

/* $RCSfile$ */
