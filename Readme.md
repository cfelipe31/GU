# GNUber

GNUber is a Free Open Source hitchhiking app lisenced under the GNU General Public License 3.0.

Currently GNUber offers three different interfaces:

  - Command line
  - Web
  - ncurses

A preview of the current web interface can be found [here](http://www2.del.ufrj.br/~carlos.oliveira/GU/index_en-us.html). 

# Installing

## Supported Operating Systems

GNUber requires external libraries that were pre-compiled to a few operating systems. Those are:

- Ubuntu
- FreeBSD
- CentOS
- Windows (Cygwin)

GNUber will automatically detect your system and use the correct library during the build process.

Unfortunately other operating systems are not supported at this moment.

## Meeting Dependencies

First you will need to meet the required dependencies. Those are:

- Doxygen
- Git
- autotools

On a Debian system this can be accomplished by running:

```sh
$ sudo apt-get install autotools-dev autoconf git doxygen
```

Because GNUber relies on 32 bit libraries, if you are using a 64 bit system you will need gcc-multilib:

```sh
$ sudo apt-get install gcc-multilib
```

## Downloading and Configuring

Clone this repository to your local environment:

```sh
$ git clone https://github.com/cfelipe31/GU.git
```

TO ADD: configure paths in Makefile

## Building and installing

In order to build the app, go to the GU/Sources/C folder and run:

```sh
$ make all
```

Or in a FreeBSD environment:

```sh
$ gmake all
```

To finish the install process run, on the same folder:

```sh
$ make install
```


## Testing

A test suite can be found under the directory /GU/Binaries. Run:

```sh
$ ./guUnitTests
```

As 29th February 2016 there are no known failling tests. If a test fails please [contact the developer](mailto:cfelipe.domingues@gmail.com) and copy the given error message on the email. 

# Folder stucture

# Testing the web interface locally

Install Apache 2 and the Python Apache module:

```sh
$ sudo apt-get install apache2 libapache2-mod-python
```

Go to the hmtl folder (defined in the Makefile as $(HTML_PATH)):

```sh
$ ~/public/html/GU
```

Open the Apache configuration file:

```sh
$ sudo vim /etc/apache2/apache2.conf
```

Add the lines:

```sh

LoadModule python_module modules/mod_python.so

<Directory /home/USERNAME/public/html/GU>
     Options ExecCGI
     AllowOverride None
     Order allow,deny
     Allow from all
     AddHandler cgi-script .cgi
</Directory>

```

Enable the Apache module:

```sh
$ sudo a2enmod python
```


Open the Apache default settings file:

```sh
$ sudo vim /etc/apache2/sites-available/000-default.conf

```


Change DocumentRoot to /home/USERNAME/public/html/GU

Restart Apache:

```sh 
$ sudo /etc/init.d/apache2 restart
```

Now you will be able to acess the index page on your browser at the address: http://0.0.0.0/index_en-us.html







