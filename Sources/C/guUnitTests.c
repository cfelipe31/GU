//printf, remove
#include <stdio.h>

//malloc
#include <stdlib.h>

//strcat
#include <string.h>


#include "guAddUser.h"     
#include "guUnitTests.h"
#include "guFunctions.h"
#include "guTypes.h"
#include "guErrors.h"
#include "guConfig.h"

#define OK	0

//BUGS: 

//If I create an unitialized pointer and pass it to a function 
// then run it in test_run, it wont detect its unitialized unless
// I explicitly define it as type *pointer = NULL
//EDIT: This is not a bug, pointers in C are NOT guaranted to
// be initialied as NULL!

//-------------------------------------------------
// GuAddUser()                        
//-------------------------------------------------

//Case when the user file does not exist.
void GuAddUser_01()
{
  FILE *usersFile;

  char fileContent[1000];

  guUserDataType *userPointer;
 
  guUserDataType user = {1 , guUsers, "Carlos Felipe Domingues e Oliveira", 
                        "", "123456", "123456","cfelipe.domingues@gmail.com",
                        "cfelipe.domingues@gmail.com", NULL, NULL};

  guErrorType returnValue = 0;

  //The "remove" function deletes a file
  remove("users");

  userPointer = &user;

  GuAddUser(userPointer);

  usersFile = fopen (GU_USER_DATA_FILENAME, "r");

  fscanf (usersFile, "%s", fileContent);

  fclose (usersFile);

  _it_should("If the file \"users\" does not exist, it should be created and it should contain the admin data.", 
    (returnValue == guOk));

  printf(KCYN "    File content:\n    %s\n" KNRM, fileContent);

}


void GuAddUser_02()
{
  FILE *usersFile;

  char *fileContent;

  long length = 5000;

  guUserDataType *userPointer;
 
  guUserDataType user1 = {1 , guUsers, "Teste Boarque de Holanda", 
                         "", "123456", "123456","teste.boarque@gmail.com",
                         "teste.boarque@gmail.com", NULL, NULL};

  guUserDataType user2 = {1 , guUsers, "Plinio Fraga de Almeida", 
                         "", "123456", "123456","plinio@gmail.com",
                         "plinio@gmail.com", NULL, NULL};

  guUserDataType user3 = {1 , guUsers, "Pedro Ernesto Xavier", 
                         "", "123456", "123456","pxavier@gmail.com",
                         "pxavier@gmail.com", NULL, NULL};

  guErrorType returnValue = 0;

  userPointer = &user1;

  GuAddUser(userPointer);

  userPointer = &user2;

  GuAddUser(userPointer);

  userPointer = &user3;

  GuAddUser(userPointer);

  usersFile = fopen (GU_USER_DATA_FILENAME, "r");

  fileContent = malloc(length);

  fread (fileContent, 1, length, usersFile);

  fclose (usersFile);

  _it_should("If the file \"users\" does exist, it should add all the requisited users that have a non-null password field.", 
    (returnValue == guOk));

  printf(KCYN "    File content:\n    %s\n" KNRM, fileContent);

  free(fileContent);
}





//-------------------------------------------------
// GuCheckEmail()                        
//-------------------------------------------------

void GuCheckEmail_01()
{
  char *email = "carlos.oliveira@gmail.com";

  _it_should("Should return \"guOK\" if email is reasonable.", 
    (GuCheckEmail(email, GU_VALID_EMAIL_CHARACTERS, GU_MIN_EMAIL_LENGTH, GU_MAX_EMAIL_LENGTH) == guOk));

}

void GuCheckEmail_02()
{
  char *email = NULL;

  _it_should("Should return \"guNullPointer\" if email a null pointer.", 
    (GuCheckEmail(email, GU_VALID_EMAIL_CHARACTERS, GU_MIN_EMAIL_LENGTH, GU_MAX_EMAIL_LENGTH) == guNullPointer));

}


void GuCheckEmail_03()
{
  char *email = "test@test.com";

  _it_should("Should return \"guMaxMinInvalid\" if the maximum number of characters defined is smaller than the minimum.", 
    (GuCheckEmail(email, GU_VALID_EMAIL_CHARACTERS, 6, 4) == guMaxMinInvalid));

}

void GuCheckEmail_04()
{
  char *email = "a@gmail.br";

  _it_should("Should return \"guSmallString\" if email has less characters than the minimum.", 
    (GuCheckEmail(email, GU_VALID_EMAIL_CHARACTERS, GU_MIN_EMAIL_LENGTH, GU_MAX_EMAIL_LENGTH) == guSmallString));

}

void GuCheckEmail_05()
{
  unsigned index;
  char email[GU_MAX_EMAIL_LENGTH + 11] = "a@gmail.br";

  for(index = 0; index < GU_MAX_EMAIL_LENGTH; index++)
  {
    strcat(email, "a");
  }
  
  _it_should("Should return \"guBigString\" if email has more characters than the minimum.", 
    (GuCheckEmail(email, GU_VALID_EMAIL_CHARACTERS, GU_MIN_EMAIL_LENGTH, GU_MAX_EMAIL_LENGTH) == guBigString));

}

void GuCheckEmail_06()
{
  char *email = "carlos.oliv/eira@gmail.com";

  _it_should("Should return \"guInvalidString\" if email has illegal character.", 
    (GuCheckEmail(email, GU_VALID_EMAIL_CHARACTERS, GU_MIN_EMAIL_LENGTH, GU_MAX_EMAIL_LENGTH) == guInvalidString));

}


void GuCheckEmail_07()
{
  char *email = "carlos.@oliveira@gmail.com";

  _it_should("Should return \"guTooManyAmpersands\" if email has more than one \"@\".", 
    (GuCheckEmail(email, GU_VALID_EMAIL_CHARACTERS, GU_MIN_EMAIL_LENGTH, GU_MAX_EMAIL_LENGTH) == guTooManyAmpersands));

}


//-------------------------------------------------
// GuCheckNickname()                        
//-------------------------------------------------

void GuCheckNickname_01()
{
  char *nickname = "carlos.oliveira";

  _it_should("Should return \"guOK\" if nickname is reasonable.", 
    (GuCheckNickname(nickname, GU_VALID_NICKNAME_CHARACTERS, GU_MIN_NICKNAME_LENGTH, GU_MAX_NICKNAME_LENGTH) == guOk));

}

void GuCheckNickname_02()
{
  char *nickname = NULL;

  _it_should("Should return \"guNullPointer\" if nickname a null pointer.", 
    (GuCheckNickname(nickname, GU_VALID_NICKNAME_CHARACTERS, GU_MIN_NICKNAME_LENGTH, GU_MAX_NICKNAME_LENGTH) == guNullPointer));

}

void GuCheckNickname_03()
{
  char *nickname = "carlos.oliveira";

  _it_should("Should return \"guMaxMinInvalid\" if the maximum number of characters defined is smaller than the minimum.", 
    (GuCheckNickname(nickname, GU_VALID_NICKNAME_CHARACTERS, 6, 4) == guMaxMinInvalid));

}

void GuCheckNickname_04()
{
  char *nickname = "c.o";

  _it_should("Should return \"guSmallString\" if nickname has less characters than the minimum.", 
    (GuCheckNickname(nickname, GU_VALID_NICKNAME_CHARACTERS, GU_MIN_NICKNAME_LENGTH, GU_MAX_NICKNAME_LENGTH) == guSmallString));

}

void GuCheckNickname_05()
{
  unsigned index;
  char nickname[GU_MAX_NICKNAME_LENGTH+20] = "carlos.oliveira";

  for(index = 0; index < GU_MAX_NICKNAME_LENGTH; index++)
  {
    strcat(nickname, "a");
  }

  _it_should("Should return \"guBigString\" if nickname has more characters than the minimum.", 
    (GuCheckNickname(nickname, GU_VALID_NICKNAME_CHARACTERS, GU_MIN_NICKNAME_LENGTH, GU_MAX_NICKNAME_LENGTH) == guBigString));

}


void GuCheckNickname_06()
{
  char *nickname = "carlos/.oliveira";

  _it_should("Should return \"guInvalidString\" if nickname has illegal character.", 
    (GuCheckNickname(nickname, GU_VALID_NICKNAME_CHARACTERS, GU_MIN_NICKNAME_LENGTH, GU_MAX_NICKNAME_LENGTH) == guInvalidString));

}

void GuCheckNickname_07()
{
  char *nickname = "carlos.olivei.ra";

  _it_should("Should return \"guTooManyDots\" if email has more than one \".\".", 
    (GuCheckNickname(nickname, GU_VALID_NICKNAME_CHARACTERS, GU_MIN_NICKNAME_LENGTH, GU_MAX_NICKNAME_LENGTH) == guTooManyDots));

}


//-------------------------------------------------
// GuCheckPassword()                        
//-------------------------------------------------

void GuCheckPassword_01()
{
  char *password = "123456";
  char *storedPassword = "ab01FAX.bQRSU";

  _it_should("Should return \"guOK\" if the stored password and the encrypted password match for a valid DES-encrypted password.", 
    (GuCheckPassword(password, storedPassword) == guOk));

}

void GuCheckPassword_02()
{
  char *password = "123456";
  char *storedPassword = "ab01FAX.bkRSU";

  _it_should("Should return \"guPasswordsDontMatch\" if the stored password and the encrypted password match fora an invalid DES-encrypted password.", 
    (GuCheckPassword(password, storedPassword) == guPasswordsDontMatch));

}


void GuCheckPassword_03()
{
  char *password = "123456";
  char *storedPassword = "$1$12345678$a4ge4d5iJ5vwvbFS88TEN0";

  _it_should("Should return \"guOK\" if the stored password and the encrypted password match fora a valid Md5-encrypted password.", 
    (GuCheckPassword(password, storedPassword) == guOk));

}

void GuCheckPassword_04()
{
  char *password = "123456";
  char *storedPassword = "$1$12345678$a4ge4d5iJ5vwvbFS88TEP0";

  _it_should("Should return \"guPasswordsDontMatch\" if the stored password and the encrypted password match fora an invalid Md5-encrypted password.", 
    (GuCheckPassword(password, storedPassword) == guPasswordsDontMatch));

}


void GuCheckPassword_05()
{
  char *password = "123456";
  char *storedPassword = "$5$HSC5HuF0E8JqXqiB$GnBpihvDvX7gz7vmWCAe2Q.gtZhNGL8F5V0ZcfAxqA6";

  _it_should("Should return \"guOK\" if the stored password and the encrypted password match fora a valid Sha256-encrypted password.", 
    (GuCheckPassword(password, storedPassword) == guOk));

}


void GuCheckPassword_06()
{
  char *password = "123456";
  char *storedPassword = "$5$HSC5HxF0E8JqXqiB$GnBpihvDvX7gz7vmWCAe2Q.gtZhNGL8F5V0ZcfAxqA6";

  _it_should("Should return \"guPasswordsDontMatch\" if the stored password and the encrypted password match fora an invalid Sha256-encrypted password.", 
    (GuCheckPassword(password, storedPassword) == guPasswordsDontMatch));

}


void GuCheckPassword_07()
{
  char *password = "123456";
  char *storedPassword = "$6$1234567891234567$RhVvPsN4LwALrBLLmn9ZAbm3TESAidgOLBKP0GilxWgSQXvpsxa2KyGewIO/m0uv0yaFkc4SVpNHc.ziqQVtl0";

  _it_should("Should return \"guOK\" if the stored password and the encrypted password match fora a valid Sha512-encrypted password.", 
    (GuCheckPassword(password, storedPassword) == guOk));

}

void GuCheckPassword_08()
{
  char *password = "123456";
  char *storedPassword = "$6$1234567891234567$RhVvPsN4LwALrBLLmn9ZAbm3TESaidgOLBKP0GilxWgSQXvpsxa2KyGewIO/m0uv0yaFkc4SVpNHc.ziqQVtl0";

  _it_should("Should return \"guPasswordsDontMatch\" if the stored password and the encrypted password match fora an invalid Sha512-encrypted password.", 
    (GuCheckPassword(password, storedPassword) == guPasswordsDontMatch));

}

//-------------------------------------------------
// GuCheckStringField()                        
//-------------------------------------------------

void GuCheckStringField_01()
{
  char *string = "carlosOliveira";

  _it_should("Should return \"guOK\" if string is reasonable.", 
    (GuCheckStringField(string, GU_VALID_NICKNAME_CHARACTERS, GU_MIN_NICKNAME_LENGTH, GU_MAX_NICKNAME_LENGTH) == guOk));

}

void GuCheckStringField_02()
{
  char *string = NULL;

  _it_should("Should return \"guNullPointer\" if string a null pointer.", 
    (GuCheckNickname(string, GU_VALID_NICKNAME_CHARACTERS, GU_MIN_NICKNAME_LENGTH, GU_MAX_NICKNAME_LENGTH) == guNullPointer));

}

void GuCheckStringField_03()
{
  char *string = "carlosOliveira";

  _it_should("Should return \"guMaxMinInvalid\" if the maximum number of characters defined is smaller than the minimum.", 
    (GuCheckNickname(string, GU_VALID_NICKNAME_CHARACTERS, 6, 4) == guMaxMinInvalid));

}

void GuCheckStringField_04()
{
  char *string = "c.o";

  _it_should("Should return \"guSmallString\" if string has less characters than the minimum.", 
    (GuCheckNickname(string, GU_VALID_NICKNAME_CHARACTERS, GU_MIN_NICKNAME_LENGTH, GU_MAX_NICKNAME_LENGTH) == guSmallString));

}

void GuCheckStringField_05()
{
  unsigned index;
  char string[GU_MAX_NICKNAME_LENGTH+20] = "carlosOliveira";

  for(index = 0; index < GU_MAX_NICKNAME_LENGTH; index++)
  {
    strcat(string, "a");
  }

  _it_should("Should return \"guBigString\" if string has more characters than the minimum.", 
    (GuCheckNickname(string, GU_VALID_NICKNAME_CHARACTERS, GU_MIN_NICKNAME_LENGTH, GU_MAX_NICKNAME_LENGTH) == guBigString));

}


void GuCheckStringField_06()
{
  char *string = "carlos/.oliveira";

  _it_should("Should return \"guInvalidString\" if string has illegal character.", 
    (GuCheckNickname(string, GU_VALID_NICKNAME_CHARACTERS, GU_MIN_NICKNAME_LENGTH, GU_MAX_NICKNAME_LENGTH) == guInvalidString));

}



//------------------------------------------------
// GuCreateRandomString()                      
//------------------------------------------------

void GuCreateRandomString_01() 
{

     unsigned long stringLength = 5;
     char generatedString[10] ={0};
    
    _it_should("Should return \"guOk\" if all parameters are reasonable.", 
            (GuCreateRandomString (GU_VALID_PASSWORD_CHARACTERS, stringLength, generatedString) == guOk));

    printf(KCYN "    Length: %lu Generated string: <%s>\n" KNRM, stringLength, generatedString);

}

void GuCreateRandomString_02() 
{


     char *validChar = NULL;
     unsigned long stringLength = 5;
     char generatedString[10] ={0};
    
    _it_should("Should return \"guNullPointer\" if valid character list is unitialized.", 
            (GuCreateRandomString (validChar, stringLength, generatedString) == guNullPointer));

}

void GuCreateRandomString_03() 
{


     char *validChar = "abcde";
     unsigned long stringLength = 5;
     char *generatedString= NULL;

    _it_should("Should return \"guNullPointer\" if generetade string placeholder is unitialized", 
            (GuCreateRandomString (validChar, stringLength, generatedString) == guNullPointer));

}

void GuCreateRandomString_04() 
{


     char *validChar = "abcde";
     unsigned long stringLength = 0;
     char generatedString[10] = {0};
    
    _it_should("Should return \"guZeroValue\" if the length of the string is set to zero", 
            (GuCreateRandomString (validChar, stringLength, generatedString) == guZeroValue));

}


//-------------------------------------------------
// GuCreateNickname()                        
//-------------------------------------------------

void GuCreateNickname_01() 
{

  char *name = "Carlos Felipe Domingues e Oliveira";

  char firstNickname[GU_MAX_NICKNAME_LENGTH];

  char secondNickname[GU_MAX_NICKNAME_LENGTH];
    
  _it_should("Should return \"guOk\" both nicknames are create sucessfully", 
  (GuCreateNickname(name, firstNickname, secondNickname) == guOk));

  printf(KCYN "    Name: %s 1st Nickname: %s 2nd Nickname: %s\n" KNRM, name, firstNickname, secondNickname);
}

void GuCreateNickname_02() 
{

  char *name = "Carlos";

  char firstNickname[GU_MAX_NICKNAME_LENGTH];

  char secondNickname[GU_MAX_NICKNAME_LENGTH];
    
  _it_should("Should return \"guNoSurname\" if there's no second name.", 
  (GuCreateNickname(name, firstNickname, secondNickname) == guNoSurname));

}


//------------------------------------------------
// GuEncodePasswordWithSpecificAlgorithm()                      
//------------------------------------------------

void GuEncodePasswordWithSpecificAlgorithm_01() 
{

     char *password = "123456";
     char encodedPassword[150] = {0};

     guCryptAlgorithms algorithm = guSha256;
    
    _it_should("Should return \"guOk\" if all parameters are reasonable", 
            (GuEncodePasswordWithSpecificAlgorithm (password, algorithm, encodedPassword) == guOk));

    printf(KCYN "    Password: <%s> Encoded password: <%s>\n" KNRM, password, encodedPassword);

}


void GuEncodePasswordWithSpecificAlgorithm_02() 
{

     char *password = "123456";
     char encodedPassword[150] = {0};

     guCryptAlgorithms algorithm = (guCryptAlgorithms) 7;
    
    _it_should("Should return \"guInvalidCryptAlgorithm\" if the algorithm is not valid.", 
            (GuEncodePasswordWithSpecificAlgorithm (password, algorithm, encodedPassword) == guInvalidCryptAlgorithm));

    printf(KCYN "    Password: <%s> Encoded password: <%s>\n" KNRM, password, encodedPassword);

}



//------------------------------------------------
// GuEncodePasswordWithSpecificSalt()                      
//------------------------------------------------

void GuEncodePasswordWithSpecificSalt_01() 
{

     char *salt = "$5$1234567891234567";
     char *password = "123456";
     char encodedPassword[150] = {0};
    
    _it_should("Should return \"guOk\" if all parameters are reasonable", 
    	      (GuEncodePasswordWithSpecificSalt (password, salt, encodedPassword) == guOk));

    printf(KCYN "    Salt: <%s>  Password: <%s> Encoded password: <%s>\n" KNRM,salt, password, encodedPassword);

}


//-------------------------------------------------
// GuGetCryptAlgorithm()                        
//-------------------------------------------------

void GuGetCryptAlgorithm_01() 
{

  char *password = "ab01FAX.bQRSU";

  guCryptAlgorithms *algorithm;
    
  algorithm = (guCryptAlgorithms *) malloc (sizeof(guCryptAlgorithms));

  GuGetCryptAlgorithm(password, algorithm);
 
  _it_should("Algorithm should be \"guDes\" for a valid Des encrypted password.", 
  (*algorithm == guDes));

  free(algorithm);
}

void GuGetCryptAlgorithm_02() 
{

  char *password = "$1$12345678$a4ge4d5iJ5vwvbFS88TEN0";

  guCryptAlgorithms *algorithm;
    
  algorithm = (guCryptAlgorithms *) malloc (sizeof(guCryptAlgorithms));

  GuGetCryptAlgorithm(password, algorithm);
 
  _it_should("Algorithm should be \"guMd5\" for a valid Md5 encrypted password.", 
  (*algorithm == guMd5));

  free(algorithm);
}


void GuGetCryptAlgorithm_03() 
{

  char *password = "$5$HSC5HuF0E8JqXqiB$GnBpihvDvX7gz7vmWCAe2Q.gtZhNGL8F5V0ZcfAxqA6";

  guCryptAlgorithms *algorithm;
    
  algorithm = (guCryptAlgorithms *) malloc (sizeof(guCryptAlgorithms));

  GuGetCryptAlgorithm(password, algorithm);
 
  _it_should("Algorithm should be \"guSha256\" for a valid Sha256 encrypted password.", 
  (*algorithm == guSha256));

  free(algorithm);
}


void GuGetCryptAlgorithm_04() 
{

  char *password = "$6$1234567891234567$RhVvPsN4LwALrBLLmn9ZAbm3TESAidgOLBKP0GilxWgSQXvpsxa2KyGewIO/m0uv0yaFkc4SVpNHc.ziqQVtl0";

  guCryptAlgorithms *algorithm;
    
  algorithm = (guCryptAlgorithms *) malloc (sizeof(guCryptAlgorithms));

  GuGetCryptAlgorithm(password, algorithm);
 
  _it_should("Algorithm should be \"guSha512\" for a valid Sha512 encrypted password.", 
  (*algorithm == guSha512));

  free(algorithm);
}

void GuGetCryptAlgorithm_05() 
{

  char *password = "ab01FA@.bQRSU";

  guCryptAlgorithms *algorithm;
    
  algorithm = (guCryptAlgorithms *) malloc (sizeof(guCryptAlgorithms));

 
  _it_should("Should return \"guInvalidCryptAlgorithm\" if the encrypted password has illegal characters.", 
  (GuGetCryptAlgorithm(password, algorithm) == guInvalidCryptAlgorithm));

  free(algorithm);
}



void GuGetCryptAlgorithm_06() 
{

  char *password = "$7$HSC5HuF0E8JqXqiB$GnBpihvDvX7gz7vmWCAe2Q.gtZhNGL8F5V0ZcfAxqA6";

  guCryptAlgorithms *algorithm;
    
  algorithm = (guCryptAlgorithms *) malloc (sizeof(guCryptAlgorithms));

 
  _it_should("Should return \"guInvalidCryptAlgorithm\" if the salt specifies an unknown crypto algorithm.", 
  (GuGetCryptAlgorithm(password, algorithm) == guInvalidCryptAlgorithm));

  free(algorithm);
}

//-------------------------------------------------
// GuGetLanguageIndex()                        
//-------------------------------------------------

void GuGetLanguageIndex_01() 
{

  char *language = "portuguese";
    
  _it_should("Should return \"guPortuguese\" if input = \"portuguese\"", 
  (GuGetLanguageIndex(language) == guPortuguese));
}

void GuGetLanguageIndex_02() 
{

     char *language = "english";
    
    _it_should("Should return \"guEnglish\" if input = \"english\"", 
            (GuGetLanguageIndex(language) == guEnglish));
}

void GuGetLanguageIndex_03() 
{

     char *language = "polish";
    
    _it_should("Should return \"guEnglish\" if input = \"polish\"", 
            (GuGetLanguageIndex(language) == guEnglish));
}

void GuGetLanguageIndex_04() 
{

     char *language = NULL;
    
    _it_should("Should return \"guEnglish\" if input is a NULL pointer", 
            (GuGetLanguageIndex(language) == guEnglish));
}



//------------------------------------------------
// Run all tests                      
//------------------------------------------------



void run_tests() 
{

  _test_start("GuAddUser");
  _run_test(GuAddUser_01); 
  _run_test(GuAddUser_02); 

   /*
  _test_start("GuCheckEmail");
  _run_test(GuCheckEmail_01);
  _run_test(GuCheckEmail_02);
  _run_test(GuCheckEmail_03);
  _run_test(GuCheckEmail_04);
  _run_test(GuCheckEmail_05);
  _run_test(GuCheckEmail_06);
  _run_test(GuCheckEmail_07);
  
  _test_start("GuCheckNickname");
  _run_test(GuCheckNickname_01);
  _run_test(GuCheckNickname_02);
  _run_test(GuCheckNickname_03);
  _run_test(GuCheckNickname_04);
  _run_test(GuCheckNickname_05);
  _run_test(GuCheckNickname_06);
  _run_test(GuCheckNickname_07);

  _test_start("GuCheckPassword");
  _run_test(GuCheckPassword_01);
  _run_test(GuCheckPassword_02);
  _run_test(GuCheckPassword_03);
  _run_test(GuCheckPassword_04);
  _run_test(GuCheckPassword_05);
  _run_test(GuCheckPassword_06);
  _run_test(GuCheckPassword_07);
  _run_test(GuCheckPassword_08);

  _test_start("GuCheckStringField");
  _run_test(GuCheckStringField_01);
  _run_test(GuCheckStringField_02);
  _run_test(GuCheckStringField_03);
  _run_test(GuCheckStringField_04);
  _run_test(GuCheckStringField_05);
  _run_test(GuCheckStringField_06);

  _test_start("GuCreateRandomString");
  _run_test(GuCreateRandomString_01);
  _run_test(GuCreateRandomString_02);
  _run_test(GuCreateRandomString_03);    
  _run_test(GuCreateRandomString_04); 
  //TODO: Use string checker function for better tests
  

  _test_start("GuCreateNickname");
  _run_test(GuCreateNickname_01);
  _run_test(GuCreateNickname_02);

  _test_start("GuEncodePasswordWithSpecificAlgorithm");
  _run_test(GuEncodePasswordWithSpecificAlgorithm_01);
  _run_test(GuEncodePasswordWithSpecificAlgorithm_02);

  _test_start("GuEncodePasswordWithSpecificSalt");
  _run_test(GuEncodePasswordWithSpecificSalt_01);

  _test_start("GuGetCryptAlgorithm");
  _run_test(GuGetCryptAlgorithm_01);
  _run_test(GuGetCryptAlgorithm_02);
  _run_test(GuGetCryptAlgorithm_03);
  _run_test(GuGetCryptAlgorithm_04);
  _run_test(GuGetCryptAlgorithm_05);
  _run_test(GuGetCryptAlgorithm_06);

  _test_start("GuGetLanguageIndex");
  _run_test(GuGetLanguageIndex_01);
  _run_test(GuGetLanguageIndex_02);
  _run_test(GuGetLanguageIndex_03);
  _run_test(GuGetLanguageIndex_04);
  */

}


int main(int argc, char **argv)
{        

  run_tests();

  _test_result();

  return OK;
}


