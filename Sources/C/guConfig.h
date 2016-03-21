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
     
#ifndef GU_CONFIG_H 
#define GU_CONFIG_H "@(#)guConfig.h $Revision$"

#ifndef GU_ADMINISTRATOR_USER_IDENTIFIER
#define GU_ADMINISTRATOR_USER_IDENTIFIER				30404 
#endif /* #ifndef GU_ADMINISTRATOR_USER_IDENTIFIER */

#ifndef GU_COOKIES_DIRECTORIES
#define GU_COOKIES_DIRECTORIES                       	"/users/carlos.oliveira/private/EEL270/2015-2/GU/Cookies"    
#endif /* #ifndef GU_COOKIES_DIRECTORIES */

#ifndef GU_DATA_DIRECTORY
#define GU_DATA_DIRECTORY               	     		"/users/carlos.oliveira/private/EEL270/2015-2/GU/Data"    
#endif /* #ifndef GU_DATA_DIRECTORY */

#ifndef GU_DEFAULT_LANGUAGE
#define GU_DEFAULT_LANGUAGE  							"english" 
#endif /* #ifndef GU_DEFAULT_LANGUAGE */

#ifndef GU_HELP_URL
#define GU_HELP_URL  									"./guShowWebHelp.cgi" 
#endif /* #ifndef GU_HELP_URL */

#ifndef GU_LICENSE_URL
#define GU_LICENSE_URL  								"./guShowLicense.cgi" 
#endif /* #ifndef GU_LICENSE_URL */

#ifndef GU_LOGIN_URL
#define GU_LOGIN_URL									"./CGIs/guLogin.cgi"
#endif /* #ifndef GU_LOGIN_URL */

#ifndef GU_LOST_PW_URL
#define GU_LOST_PW_URL      	             		   "./guShowRequestPasswordReset.cgi" 
#endif /* #ifndef GU_LOST_PW_URL */

#ifndef GU_LOST_PW_FORM_URL
#define GU_LOST_PW_FORM_URL  							"./guShowRequestPasswordReset.cgi" 
#endif /* #ifndef GU_LOST_PW_URL */

#ifndef GU_NEW_USER_REQUEST_VALIDITY
#define GU_NEW_USER_REQUEST_VALIDITY  					72 
#endif /* #ifndef GU_NEW_USER_REQUEST_VALIDITY */

#ifndef GU_PRIVATE_ROOT_DIRECTORY
#define GU_PRIVATE_ROOT_DIRECTORY          				"/users/carlos.oliveira/private/EEL270/2015-2/GU"    
#endif /* #ifndef GU_PRIVATE_ROOT_DIRECTORY */

#ifndef GU_REGISTRATION_URL
#define GU_REGISTRATION_URL  							"./guRequestRegistration.cgi" 
#endif /* #ifndef GU_REGISTRATION_URL */

#ifndef GU_REGISTER_FORM_URL
#define GU_REGISTER_FORM_URL  							"./guShowRequestRegistrationForm.cgi" 
#endif /* #ifndef GU_REGISTER_FORM_URL */

#ifndef GU_USERS_DATA_FILENAME
#define GU_USERS_DATA_FILENAME 							"users" 
#endif /* #ifndef GU_USERS_DATA_FILENAME */

#ifndef GU_INVITED_USERS_DATA_FILENAME
#define GU_INVITED_USERS_DATA_FILENAME 					"invited.users" 
#endif /* #ifndef GU_INVITED_USERS_DATA_FILENAME */

#ifndef GU_REQUESTING_USERS_DATA_FILENAME
#define GU_REQUESTING_USERS_DATA_FILENAME 				"requesting.users" 
#endif /* #ifndef GU_REQUESTING_USERS_DATA_FILENAME */

#ifndef GU_LOCKED_USERS_DATA_FILENAME
#define GU_LOCKED_USERS_DATA_FILENAME 					"locked_users" 
#endif /* #ifndef GU_LOCKED_USERS_DATA_FILENAME */

#ifndef GU_WEB_SERVER_URL
#define GU_WEB_SERVER_URL 								"http://www02.del.ufrj.br/~carlos.oliveira/GU/index_en-us.html"
#endif /* #ifndef GU_WEB_SERVER_URL */ 

#endif /* #ifndef GU_CONFIG_H */ 

/* $RCSfile$ */