LSystemCPP
==========
A SFML 2.0 based L-System parser and renderer. Currently supports only parametric L-Systems.

# Windows build instructions
I'm using Visual Studio 2012. You need to have SFML 2.0 installed in order for this to build, you might have to adjust
the path in the project properties. Also, don't forget to put the SFML DLLs in the directory of the executable.

# Linux build instructions
Install SFML 2.0
Make sure you have exported `LD_LIBRARY_PATH`
There is a Makefile in the LSystem/ directory of the project path
make all
./LSystem.app
