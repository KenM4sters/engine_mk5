#version 330 core
// tells GLSL which variables represent which data in the VBOs (indirectly through the VAOs).
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec4 offsetA;
layout (location = 4) in vec4 offsetB;
layout (location = 5) in vec4 offsetC;
layout (location = 6) in vec4 offsetD;
layout (location = 7) in vec4 aInstanceColor;

// Only the vertex shader can access the data in a VBO, but we can pass that data from 
// the vertex shader to the fragment shader by calling "out" and "in" with the same name and type.
out vec3 sColor;
out vec4 sInstanceColor;
out vec2 TexCoord;

void main() 
{
    // Here, we multiply our position vector by a matrix in the translations array of matrices 
    // that we intialised in sprite.c, to position them across the screen.
    gl_Position = mat4(offsetA, offsetB, offsetC, offsetD) * vec4(aPos, 1.0);
    sColor = aColor;
    sInstanceColor = aInstanceColor;
    TexCoord = aTexCoord;

}

