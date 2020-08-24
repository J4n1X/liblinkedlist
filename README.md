# liblinkedlist

## About this project
This library is a small C project I am working on. Its main selling point is that it is *small*, which, other than speed, is the main focus of this library.

No platform specific code is used.

## Usage
Compiling this project could not be any simpler. 

### Compiling with make
The easy way to compile is with make, of course
To make both library types:
    
    make all

To make the static/shared library, use the corresponding commands:

    make static
    make shared

And to install the shared library, use:

    make install
### Compiling manually
To compile the source code:
    
    gcc -c -fpic -O2 liblist.c
    
To create the static library file: 
    
    ar rcs list_static/liblist.a liblist.o

To create the shared library file:
    
    gcc -shared liblist.o -o list_shared/liblist.so

To install the shared library, move it to your lib folder, for example:

    mv liblist.so /usr/lib/
