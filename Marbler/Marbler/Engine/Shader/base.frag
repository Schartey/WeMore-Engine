#version 330 core

in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragVert;

uniform int diffuseTextureSize;
uniform int lightmapTextureSize;

uniform sampler2D diffuseTexture[10];
uniform sampler2D lightmapTexture[10];

uniform struct Material {
    vec3 ambient;
	vec3 diffuse;
    vec3 specular;
    float shininess;
} material;

uniform vec3 viewPos;

layout (location = 0) out vec4 finalColor;

void main(){
    // Output color = color specified in the vertex shader,
    // interpolated between all 3 surrounding vertices
	vec3 ambient = material.ambient;
    vec3 diffuse = material.diffuse;
    vec3 specular = material.specular;  
	
    vec3 lightResult = ambient + diffuse + specular;

	vec3 normal = normalize(fragNormal);
	
	vec4 surfaceColor = vec4(1.0);
	
	for(int i = 0; i < diffuseTextureSize; i++)
	{
		surfaceColor = surfaceColor*texture(diffuseTexture[i], fragTexCoord);
	}
	for(int i = 0; i < lightmapTextureSize; i++)
	{		
		surfaceColor = surfaceColor*texture(lightmapTexture[i], fragTexCoord);
	}
	finalColor = surfaceColor;
	finalColor = vec4(1.0f);
}