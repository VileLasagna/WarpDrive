#version 330 core

layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec4 ambient;

out vec4 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(position, 1.0f);
    ourColor = ambient;
    TexCoord = texCoords;
}
