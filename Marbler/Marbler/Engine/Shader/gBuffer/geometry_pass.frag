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

uniform sampler2DShadow gShadowMap;

layout (location = 0) out vec3 WorldPosOut; 
layout (location = 1) out vec3 DiffuseOut; 
layout (location = 2) out vec3 NormalOut; 
layout (location = 3) out vec3 SpecularOut; 

vec2 poissonDisk[16] = vec2[](
    vec2( -0.94201624, -0.39906216 ),
    vec2( 0.94558609, -0.76890725 ),
    vec2( -0.094184101, -0.92938870 ),
    vec2( 0.34495938, 0.29387760 ),
    vec2( -0.91588581, 0.45771432 ),
    vec2( -0.81544232, -0.87912464 ),
    vec2( -0.38277543, 0.27676845 ),
    vec2( 0.97484398, 0.75648379 ),
    vec2( 0.44323325, -0.97511554 ),
    vec2( 0.53742981, -0.47373420 ),
    vec2( -0.26496911, -0.41893023 ),
    vec2( 0.79197514, 0.19090188 ),
    vec2( -0.24188840, 0.99706507 ),
    vec2( -0.81409955, 0.91437590 ),
    vec2( 0.19984126, 0.78641367 ),
    vec2( 0.14383161, -0.14100790 )
);
float bias = 0.005;

float ShadowCalculation(vec4 pos) 
{
	vec3 projCoords = pos.xyz / pos.w;
	projCoords = projCoords * 0.5 + 0.5;

	float shadow = 0.2;

	for (int i=0;i<16;i++){
	  shadow += textureProj( gShadowMap, vec4(projCoords.xy + poissonDisk[i]/941.0, projCoords.z - bias, 1.0)) / 16;
	}

	return shadow;
}

void main() 
{ 
    WorldPosOut = fragVert; 
    NormalOut = normalize(fragNormal); 
	
	vec4 surfaceColor = vec4(material.diffuse, 1.0);
	
	for(int i = 0; i < diffuseTextureSize; i++)
	{
		surfaceColor = surfaceColor*texture(diffuseTexture[i], fragTexCoord);
	}
	for(int i = 0; i < lightmapTextureSize; i++)
	{		
		surfaceColor = surfaceColor*texture(lightmapTexture[i], fragTexCoord);
	}

	float visibility = ShadowCalculation(directionalLightSpacePos);

    DiffuseOut = visibility * vec3(surfaceColor);

	SpecularOut = visibility * vec3(material.specularIntensity, material.specularPower, 1.0);
}