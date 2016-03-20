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

#define AMBIENTE_EXECUCAO_INVALIDO      1
#define COMPRIMENTO_MAXIMO_LINGUA       20

#include <stdio.h>
#include <stdlib.h>

#include "Libraries/mlcgi.h" 
#include "guUserInterface.h"
#include "guTypes.h"
#include "guFunctions.h"
#include "guConfig.h"



int main(int argc, char **argv)
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
  printf ("    <p style=\"text-align: center;\">\n");
  printf ("    <span style=\"color: #cc99ff;\">\n");
  printf ("    <span style=\"color: #000000;\">\n");
  printf ("    %s&nbsp;\n",
               GuGetWebUserInterfaceMessage(guByMessage,language));
  printf ("    <a title=\"Author\""
               " href=\"mailto:cfelipe.domingues@poli.ufrj.br\"" 
               "target=\"_blank\">Carlos Felipe D. e Oliveira</a>"
               "</span>&nbsp;</span></p>\n");
  printf ("    <form style=\"text-align: center;\""
               " action=\"./CGIs/guLogin.cgi\">\n");
  printf ("      %s:<br/> \n",
                 GuGetWebUserInterfaceMessage(guUsernameMessage,language));
  printf ("      <input name=\"guNickname\" type=\"text\"" 
                "maxlength=\"%u\"/>\n",GU_MAX_NICKNAME_LENGTH); 
  printf ("      <br/> %s:<br/>\n",
                 GuGetWebUserInterfaceMessage(guPasswordMessage,language)); 
  printf ("      <input name=\"guPassword\"" 
                "type=\"password\" maxlength=\"%u\"/><br><br>\n",
                 GU_MAX_PASSWORD_LENGTH); 
  printf ("      <input type=\"submit\" value=\"%s\">",
                 GuGetWebUserInterfaceMessage(guLoginMessage,language));
  printf ("      <input type=\"hidden\" name=\"guLanguage\"" 
          "      value=\"%s\">\n",languageString);
  printf ("    </form>\n");
  printf ("    <p style=\"text-align:center;\">%s"
          "    <a href=\"%s?guLanguage=%s\">%s</a>&nbsp;%s</p>\n",
               GuGetWebUserInterfaceMessage(guSignUpMessage1,language),
               GU_REGISTER_FORM_URL, languageString,
               GuGetWebUserInterfaceMessage(guSignUpMessage2,language),
               GuGetWebUserInterfaceMessage(guSignUpMessage3,language));
  printf ("    <p style=\"text-align: center;\">"
              "<a href=\"%s?guLanguage=%s\">%s</a></p>\n",
               GU_LOST_PW_FORM_URL, languageString,
               GuGetWebUserInterfaceMessage(guLostPWMessage,language));
  printf ("    <p style=\"text-align: center;\">"
              "<a href=\"%s?guLanguage=%s\">%s</a></p>\n",
               GU_HELP_URL, languageString,
               GuGetWebUserInterfaceMessage(guHelpMessage,language));
  printf ("    <p style=\"text-align: center;\">"
              "<a href=\"%s?guLanguage=%s\">%s</a></p>\n",
               GU_LICENSE_URL, languageString,
               GuGetWebUserInterfaceMessage(guLicenseMessage,language));
  printf ("  </body>\n");
  printf ("</html>\n");

  mlCgiFreeResources ();
  return ML_CGI_OK;

}

/* $RCSfile$ */
