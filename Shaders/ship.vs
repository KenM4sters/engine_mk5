#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

// We declared a uniform in main.c that provides the matrix to translate our player sprite
// upon user input (WASD keys in this case). So we're recieving that uniform here and using 
// it accordingly.
uniform mat4 uTransform;

out vec3 ourColor;
out vec2 TexCoord;

void main() 
{

  gl_Position = uTransform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
  ourColor = aColor;
  TexCoord = aTexCoord;

}


