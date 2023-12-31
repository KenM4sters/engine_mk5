#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec4 offsetA;
layout (location = 4) in vec4 offsetB;
layout (location = 5) in vec4 offsetC;
layout (location = 6) in vec4 offsetD;

out vec3 sColor;
out vec2 TexCoord;

void main()  
{
  
    gl_Position = mat4(offsetA, offsetB, offsetC, offsetD) * vec4(aPos, 1.0);
    sColor = aColor;
    TexCoord = aTexCoord;

}
