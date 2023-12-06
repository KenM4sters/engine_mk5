# engine_mk5

About:

This project is for learning purposes only and serves as a sandbox to test and understand how games can be programmed at a fundamental level, with no assistance from a pre-built editor.
We are however, using assistance from the GLFW library to provide a window which we'll render our sprites on.
At the moment, there's no one particular direction that the game will be taken in, other than some kind of Shmup.

Math library:

The math library is also entirely custom made and serves to translate, scale and rotate sprites. Currently, I'm using a maxtrix as a structure of vectors, which is itself a structure of floats. 
Given this, my matrices are generated as row-major which is fine in almost all circumstances, with the exception of when they're passed to the vertex shaders. 

GLSL infers matrices as being column-major, which essentially means that they read my matrices
with the rows being swapped with the columns. This is problematic since I change certain values of these matrices in accordance with the matrix operation rules in mathematics, but this doesn't translate well since the values that I think I'm changing will end up being different ones for the vertex shader. 

Therefore, I create a simple function (matrix(num)_transpose) that swaps the columns with the rows 
to return a matrix that's column-major. Modifying this matrix instead will no longer produce any 
unwanted behavoiour. 

Other common functions that can be found in the math files are vector/matrix addition, subtraction, division, multiplication, sclaing by k, logging, and returning a pointer to an adress in memory that stores an array of the values of the matrix that's passed through (matrix(num)_value_ptr).  

Compiling:

If you're using clang, then simply run: 'make' in the terminal to compile the project, followed by "bin/app" to run the executable. Alternatively, if you're using gcc, then go into the makefile and change the "CC=clang" to "CC=gcc", then run the same commands as previously mentioned.


Devlopment points about the game:

1.  Collision detection
    ------------------------------------------------

    At the moment, I remove sprites from the screen by translating them to coordinates outside of the 
    range that OpenGL will render (i.e outside of clip-space coordinates, which range from -1.0 to 1.0).

    While this does in fact work, I don't like how abstract it is and most importantly how the game
    will still check the enemies for collisions even when they should be destroyed. With 24 sprites on the screen, this will virtually make no difference to peformance, but it's not great practice and as my game scales, it may start to slow the game down signifcantly. 

    I plan on changing this in the near future to something much more sophisticated. 

2.  Game structure
    -----------------------------------------------

    Currently, the functions in sprite.c create everything that we need in a nested structure for our sprites to be rendered correctly, and then rreturns that nested structure.

    These functions are called in main.c, and pointers to the addresses of these returned structures are then passed through to all the update functions in the render loop that modify the values in the structures to create our game logic, such as moving sprites, registering collisions, firing bullets, registering hitpoints etc...

    Again, while this does work, I'm not a huge fan of the idea of passing nested structures around like hot potatoes, especially by value (although it's mostly done by reference). Of course, I could just use global structures, but I don't want to run the risk of accidentally changing something that shouldn't be accessible. Eventhough virtually everything is accessible via passing these nested structures, such as position and colour data, VAOs, VBOs etc, it still at least protects me from accessing the wrong sprite. E.g: the player instead of the enemy - if I only pass the enemy struct through, then only the enemy can be modified... It's still far from ideal though.

    I'm not entirely sure how to go about ammending this to something cleaner and less taxing on hardware, which I think is just a lack of experience in programming at the moment. In time, I'll come back to this.

3.  Memory Allocation
    ----------------------------------------------------------------

    Most of my arrays are currently assigned an arbritrary number of bytes at compile time, which in most cases is a number high enough to store lots of data, for example bullets. 

    However, I realise that this isn't exactly optimal and the solution would be to dynamically allocate this memory at run time, to avoid both unused memory and not being able to exceed a certain amount of memory. 

    This is on my high-priority of TO-DOs, especially since it's an ample opportunity to practice advanced memory management. 