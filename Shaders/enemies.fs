#version 330 core

out vec4 FragColor;
in vec3 sColor;
// Recieving the color from the vertex shader, which is data in the currently bound VBO at 
// the time of using this shader program.
in vec4 sInstanceColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main() 
{
    vec4 texColor = texture(ourTexture, TexCoord);
    if(texColor.a < 1.0)
      discard;
    FragColor = texColor;
}
