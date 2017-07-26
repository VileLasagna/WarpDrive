#version 330 core

layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec4 ambient;

out vec4 ourColor;
out vec2 TexCoord;

uniform mat4 transf;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
    mat4 modelmat = model * transf ;
    //gl_Position = transf * vec4(position, 1.0f);
    //gl_Position = projection * view * model * vec4(position, 1.0f);
    gl_Position =  projection * view * modelmat * vec4(position, 1.0f);
    ourColor = ambient;
    TexCoord = texCoords;
}
