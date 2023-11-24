#include "shader.h"

int loadShaders(const char* fileName1, const char* fileName2) 
{
    FILE *fp_1;
    long size = 0;
    char* shaderContent1;

    fp_1 = fopen(fileName1, "rb");
    if (fp_1 == NULL) 
    {
      return 0;
    }
    fseek(fp_1, 0L, SEEK_END);
    size = ftell(fp_1) + 1;
    fclose(fp_1);

    //Read the file 
    fp_1 = fopen(fileName1, "r");
    shaderContent1 = memset(malloc(size), '\0', size);
    fread(shaderContent1, 1, size-1, fp_1);
    fclose(fp_1);

    FILE *fp_2;
    char* shaderContent2;

    fp_2 = fopen(fileName2, "rb");
    if (fp_2 == NULL) 
    {
      return 0;
    }
    fseek(fp_2, 0L, SEEK_END);
    size = ftell(fp_2) + 1;
    fclose(fp_2);

    //Read the file 
    fp_2 = fopen(fileName2, "r");
    shaderContent2 = memset(malloc(size), '\0', size);
    fread(shaderContent2, 1, size-1, fp_2);
    fclose(fp_2);

    //Shaders
    unsigned int shaderProgram = glCreateProgram();
    //Shaders
    // const char *vertexShaderSource = getShaderContent("../Shaders/vertexShader.glsl");
    // const char *fragmentShaderSource = getShaderContent("../Shaders/fragmentShader.glsl");

    //Vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &shaderContent1, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &shaderContent2, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    }
    // link shaders
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

void setVec4(unsigned int programID, const char* name, float* value) 
{
    glUniform4fv(glGetUniformLocation(programID, name), 1, value);
}

void setMat4(unsigned int programID, const char* name, float* value) 
{
    glUniformMatrix4fv(glGetUniformLocation(programID, name), 1, GL_TRUE, value);
}