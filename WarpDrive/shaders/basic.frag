#version 330 core


in vec2  UV;
in vec4  ambientColour;
in vec4  diffuseColour;
in vec4  specularColour;
in float shinyness;

out vec4 color;

uniform sampler2D tex;
uniform int untextured;

void main()
{
    if(untextured > 0)
    {
        color = ambientColour;
    }
    else
    {
        color = texture(tex, UV) * ambientColour;
    }
}
