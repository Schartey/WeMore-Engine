#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform int textureSet;
uniform sampler2D tex;
uniform vec4 diffuse;

void main()
{
	vec4 textureSample = texture(tex, TexCoords);
    
    color = textureSample * diffuse;
}