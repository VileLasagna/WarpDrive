#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

layout (location = 3) in vec4  ambient;
layout (location = 4) in vec4  diff;
layout (location = 5) in vec4  spec;
layout (location = 6) in float shine;


out vec2 UV;

out vec4 ambientColour;
out vec4 diffuseColour;
out vec4 specularColour;
out float shinyness;


uniform mat4 transf;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
    mat4 modelmat = model * transf;
    gl_Position =  projection * view * modelmat * vec4(position, 1.0f);


    UV = texCoords;
    ambientColour = ambient;
    diffuseColour = diff;
    specularColour = spec;
    shinyness = shine;
}
