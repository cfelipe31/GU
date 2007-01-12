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

Now clone this repository to your local environment:

```sh
$ git clone https://github.com/cfelipe31/GU.git
```

## Configuring

## Building

## Testing

A test suite can be found under the directory /GU/Binaries. Run:

```sh
$ ./guUnitTests
```

As 29th February 2016 there are no known failling tests. If a test fails please [contact the developer](mailto:cfelipe.domingues@gmail.com) and copy the given error message on the email. 
