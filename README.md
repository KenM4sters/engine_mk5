# engine_mk5

About:

This project is for learning purposes only and serves as sandbox to test and understand how games can be programmed at a fundemantal level, with no assistance from a graphical interface.
We are however, using assistance from the GLFW library to provide a window which we'll render our sprites on.
At the moment, there's no one particular direction that the game will be taken in, other than some kind of Shmup.

Math library:

The math library is also entirely custom made and serves to translate, scale and rotate sprites. Currently, I'm using a maxtrix as a structure of vectors, which is itself a structure of floats. While this method has worked thus far, I do plan implementing functions to convert a "matrix of rows" to a "matrix of columns" so they can be used in more ways without having to change the matrix manually. Furture imporvements will also involve the addition of functions to rotate sprites.

Compiling:

If you're using clang, then simply run: 'make' in the terminal to compile the project, followed by "bin/app" to run the executable. Alternatively, if you're using gcc, then go into the makefile and change the "CC=clang" to "CC=gcc", then run the same commands as previosly mentioned.
