#version 330

in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragVert;

uniform int diffuseTextureSize;
uniform int lightmapTextureSize;

uniform sampler2D diffuseTexture[10];
uniform sampler2D lightmapTexture[10];

layout (location = 0) out vec3 WorldPosOut; 
layout (location = 1) out vec3 DiffuseOut; 
layout (location = 2) out vec3 NormalOut; 
layout (location = 3) out vec3 TexCoordOut; 

uniform sampler2D gColorMap; 

void main() 
{ 
    WorldPosOut = fragVert; 
    NormalOut = normalize(fragNormal); 
    TexCoordOut = vec3(fragTexCoord, 0.0); 
	
	vec4 surfaceColor = vec4(1.0);
	
	for(int i = 0; i < diffuseTextureSize; i++)
	{
		surfaceColor = surfaceColor*texture(diffuseTexture[i], fragTexCoord);
	}
	for(int i = 0; i < lightmapTextureSize; i++)
	{		
		surfaceColor = surfaceColor*texture(lightmapTexture[i], fragTexCoord);
	}
    DiffuseOut = surfaceColor.xyz;
}