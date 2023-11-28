#version 330 core

out vec4 FragColor;
in vec3 sColor;
in vec4 sInstanceColor;

void main() 
{
    FragColor = sInstanceColor;
}
