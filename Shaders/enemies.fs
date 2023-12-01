#version 330 core

out vec4 FragColor;
in vec3 sColor;

// Recieving the color from the vertex shader, which is data in the currently bound VBO at 
// the time of using this shader program.
in vec4 sInstanceColor;

void main() 
{
    FragColor = sInstanceColor;
}
