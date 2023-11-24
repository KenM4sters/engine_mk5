#define GLFW_INCLUDE_NONE
#ifndef SHADER_LOADER
#define SHADER_LOADER
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../deps/include/glad/glad.h"
#include "../../deps/include/GLFW/glfw3.h"

//Load Shaders 
      
int loadShaders(const char* fileName1, const char* fileName2);
void setVec4(unsigned int programID, const char* name, float* value);
void setMat4(unsigned int programID, const char* name, float* value);


#endif
