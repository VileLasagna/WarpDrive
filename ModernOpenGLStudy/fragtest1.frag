#version 330 core

in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTex;

void main()
{
    //color = vec4(ourColor, 1.0f);
    color = texture(ourTex, TexCoord);
}
