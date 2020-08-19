To compile the source code:
    gcc -c -fpic -O2 liblist.c
To create the static library file: 
    ar rcs list_static/liblist.a liblist.o
To create the shared library file(usable with C# using DLLImport):
    gcc -shared liblist.o -o list_shared/liblist.so

Please note that you need to use the according compiler, and these instructions are meant for use with linux only
