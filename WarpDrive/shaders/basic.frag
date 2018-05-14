#version 330 core


in vec2  UV;
in vec4  ambientColour;
in vec4  diffuseColour;
in vec4  specularColour;
in float shinyness;

out vec4 color;

uniform sampler2D tex;
uniform int untextured;
uniform vec4 ambientOverride;

void main()
{
    if(ambientOverride.a > 0)
    {

        if(untextured > 0)
        {
            color = ambientOverride;
        }
        else
        {
            color = texture(tex, UV) * ambientOverride;
        }
    }
    else
    {
        if(untextured > 0)
        {
            color = ambientColour;
        }
        else
        {
            color = texture(tex, UV) * ambientOverride;
        }
    }
}
