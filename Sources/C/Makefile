#
#Universidade Federal do Rio de Janeiro
#Escola Politecnica
#Departamento de Eletronica e de Computacao
#Prof. Marcelo Luiz Drumond Lanza
#EEL 270 - Computacao II - Turma 2015/2
 
#$Author$
#$Date$
#$Log$


#############################################################
#             CHOOSING THE OS-DEPENDANT LIBRARY             #
#############################################################

UNAME := $(shell uname)

CGILIB = 0
SENDMAILLIB = 0

ifeq ($(UNAME), FreeBSD)
  CGILIB = ./Libraries/libmlcgi.a.FreeBSD.7.x
  SENDMAILLIB = ./Libraries/libsendmail.a.FreeBSD.6.2
endif
 
ifeq ($(UNAME), Linux)
  DISTRO := $(shell lsb_release -si)

  ifeq ($(DISTRO), Ubuntu)
    CGILIB = ./Libraries/libmlcgi.a.Ubuntu.12.x
    SENDMAILLIB = ./Libraries/libsendmail.a.Ubuntu.12.x
    $(Ubuntu) 
  endif

  ifeq ($(DISTRO), CentOS)
    CGILIB = ./Libraries/libmlcgi.a.CentOS.5.x
    SENDMAILLIB = ./Libraries/libsendmail.a.CentOS.5.0
  endif

endif

ifeq ($(CGILIB), 0)
  $(error OS not supported. Please check the README file for a list of supported systems.)  
endif

############################################
#             PATH DEFINITIONS             #
############################################

#All HTML files will be copied to this path.
HTML_PATH = ~/public/html/GU

#All .cgi and supporting files will be copied to this path.
CGI_PATH = ~/public/html/GU/CGIs

#CLI related files will be installed here.
CLI_PATH = ../../Binaries

#Files contaning user data will be stored here
DATA_PATH = ../../Data

#Delicious cookies can be found on this folder
COOKIE_PATH = ../../Data/Cookies


######################################################
#             FILES REQUIRED FOR INSTALL             #
######################################################

CGI_FILES = guMain.cgi guShowLicense.cgi guShowWebHelp.cgi guShowRequestRegistrationForm.cgi guShowRequestPasswordReset.cgi

CLI_FILES = gu guUnitTests

HTML_FILES = ../HTML/index_en-us.html ../HTML/index_pt-br.html

DOC_FILES = license_en-us.txt


#########################################################
#             COMPILER AND FLAG DEFINITIONS             #
########################################################

CC = gcc
LD = gcc

CFLAGS = -Wall -m32
LFLAGS = -Wall -m32


##############################################
#             OBJECT DEFINITIONS             #
##############################################

GUCGIMAINOBJS = guCgiMain.o guUserInterface.o guFunctions.o

GUCGISHOWWEBHELPOBJS = guCgiShowWebHelp.o guUserInterface.o guFunctions.o

GUCGISHOWLICENSEOBJS = guCgiShowLicense.o guUserInterface.o guFunctions.o

GUCGISHOWREQUESTREGOBJS = guCgiShowRequestRegistrationForm.c guUserInterface.o guFunctions.o

GUCGISHOWREQUESTPWOBJS = guCgiShowRequestPasswordReset.c guUserInterface.o guFunctions.o

GUOBJS = gu.o guFunctions.o guErrors.o guUserInterface.o guAddUser.o

GUUNITTESTSOBJS = guUnitTests.o guFunctions.o guAddUser.o 


##############################################
#             TARGET DEFINITIONS             #
##############################################

EXECS = 	guMain.cgi\
        	guShowLicense.cgi\
        	guShowWebHelp.cgi\
		guShowRequestRegistrationForm.cgi\
		guShowRequestPasswordReset.cgi\
		gu\
		guUnitTests\


#######################################
#             BUILD RULES             #
#######################################

#Implicit rule
.c.o: 
	$(CC) $(CFLAGS) -c $<

guMain.cgi:  $(GUCGIMAINOBJS)
	$(LD) $(LFLAGS) -o $@ $(GUCGIMAINOBJS) $(CGILIB) -lcrypt

guShowLicense.cgi:  $(GUCGISHOWLICENSEOBJS)
	$(LD) $(LFLAGS) -o $@ $(GUCGISHOWLICENSEOBJS) $(CGILIB) -lcrypt

guShowWebHelp.cgi:  $(GUCGISHOWWEBHELPOBJS)
	$(LD) $(LFLAGS) -o $@ $(GUCGISHOWWEBHELPOBJS) $(CGILIB) -lcrypt

guShowRequestRegistrationForm.cgi:  $(GUCGISHOWREQUESTREGOBJS)
	$(LD) $(LFLAGS) -o $@ $(GUCGISHOWREQUESTREGOBJS) $(CGILIB) -lcrypt

guShowRequestPasswordReset.cgi:  $(GUCGISHOWREQUESTPWOBJS)
	$(LD) $(LFLAGS) -o $@ $(GUCGISHOWREQUESTPWOBJS) $(CGILIB) -lcrypt

gu:  $(GUOBJS)	
	$(LD) $(LFLAGS) -o $@ $(GUOBJS) $(SENDMAILLIB) -lcrypt

guUnitTests:  $(GUUNITTESTSOBJS)  
	$(LD) $(LFLAGS) -o $@ $(GUUNITTESTSOBJS) $(SENDMAILLIB) -lcrypt

all: $(EXECS)


########################################
#             TEST SCRIPT              #
########################################

test:	$(EXECS)
	./guUnitTests
	rm -rf *.o $(EXECS)

################################################
#             INSTALLATION SCRIPT              #
################################################

install: $(EXECS)
	mkdir -p $(DATA_PATH)
	mkdir -p $(CLI_PATH)
	mkdir -p $(COOKIE_PATH)
	mkdir -p $(HTML_PATH)
	mkdir -p $(CGI_PATH)
	cp $(CLI_FILES) $(CLI_PATH)
	cp $(CGI_FILES)  $(CGI_PATH)		
	cp $(DOC_FILES) $(CGI_PATH)
	cp $(HTML_FILES) $(HTML_PATH)
	rm -rf *.o $(EXECS)
	../../Binaries/guUnitTests
	
clean:
	rm -rf *.o $(EXECS)

#$RCSfile$
