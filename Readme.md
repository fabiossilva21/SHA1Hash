# Sha1Algorithm
This library implements the SHA1 Hash encoding described in [RFC3174](https://tools.ietf.org/html/rfc3174)

## Usage
This is meant to be a portable library, that means, it should be compiled and ready to use with any project.
There is one namespace `Sha1Algorithm` with one single function, `Sha1Hash`.

## Supported platforms 
This library makes use of C++ version 14, although it should be able to be compiled in previous versions.
The library was tested in Linux (Debian) but should run in any other platform.

### Compilation process
For compilation purposes, a Makefile was included in the project to ease the compilation process, however the Makefile only generates the object (.o) file and the linkage should be handled by the programmer using it.

## Prerequisites
* [GNU Make](https://www.gnu.org/software/make/) (version 4.2.1 or higher)
* C++14 compatible toolchain (g++ 8.3.0 works fine)