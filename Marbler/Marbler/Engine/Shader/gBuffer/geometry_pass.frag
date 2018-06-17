#version 330

in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragVert;
in vec4 directionalLightSpacePos;

uniform struct Material {
	vec3 diffuse;
    vec3 specularColor;
    float specularIntensity;
	float specularPower;
} material;

uniform int diffuseTextureSize;
uniform int lightmapTextureSize;

uniform sampler2D diffuseTexture[4];
uniform sampler2D lightmapTexture[4];

uniform sampler2D gShadowMap;

layout (location = 0) out vec3 WorldPosOut; 
layout (location = 1) out vec3 DiffuseOut; 
layout (location = 2) out vec3 NormalOut; 
layout (location = 3) out vec3 SpecularOut; 

float ShadowCalculation(vec4 pos) 
{
	vec3 projCoords = pos.xyz / pos.w;
	projCoords = projCoords * 0.5 + 0.5;
	float closestDepth = texture(gShadowMap, projCoords.xy).r;
	float currentDepth = projCoords.z;
	float shadow = currentDepth > closestDepth ? 1.0 : 0.5;

	return shadow;
}

void main() 
{ 
    WorldPosOut = fragVert; 
    NormalOut = normalize(fragNormal); 
    //TexCoordOut = vec3(fragTexCoord, 0.0); 
	
	vec4 surfaceColor = vec4(1.0);
	
	for(int i = 0; i < diffuseTextureSize; i++)
	{
		surfaceColor = surfaceColor*texture(diffuseTexture[i], fragTexCoord);
	}
	for(int i = 0; i < lightmapTextureSize; i++)
	{		
		surfaceColor = surfaceColor*texture(lightmapTexture[i], fragTexCoord);
	}

	float visibility = ShadowCalculation(directionalLightSpacePos);

    DiffuseOut = visibility * vec3(surfaceColor);//vec3(depthValue);

    //DiffuseOut = visibility * surfaceColor.xyz;

	SpecularOut = visibility * vec3(material.specularIntensity, material.specularPower, 1.0);
}