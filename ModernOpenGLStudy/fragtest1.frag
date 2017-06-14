#version 330 core

in vec4 ourColor;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTex;
uniform sampler2D otherTex;
uniform float factor;

void main()
{
    //color = ourColor;
    //color = mix(texture(ourTex, TexCoord), texture(otherTex, TexCoord), factor );
    color = texture(ourTex, TexCoord);
}
