#version 330 

struct BaseLight
{
    vec3 Color;
    float Ambient;
    float Diffuse;
};

struct DirectionalLight
{
    BaseLight Base;
    vec3 Direction;
};

uniform sampler2D gPositionMap;
uniform sampler2D gColorMap;
uniform sampler2D gNormalMap;
uniform sampler2D gSpecularMap;
uniform vec2 gScreenSize;
uniform DirectionalLight gDirectionalLight;
uniform mat4 view;
uniform float gSpecularPower;
uniform float gMatSpecularIntensity;

layout (location = 0) out vec4 FragColor;

vec2 CalcTexCoord()
{
   return gl_FragCoord.xy / gScreenSize;
}

vec4 CalcLightInternal(BaseLight Light,
					   vec3 LightDirection,
					   vec3 WorldPos,
					   vec3 Normal,
					   vec2 Specular)
{
	vec3 eyeWorldPos = vec3(view*vec4(1.0));
    vec4 AmbientColor = vec4(Light.Color, 1.0f) * Light.Ambient;
    float DiffuseFactor = dot(Normal, -LightDirection);

    vec4 DiffuseColor  = vec4(0, 0, 0, 0);
    vec4 SpecularColor = vec4(0, 0, 0, 0);

    if (DiffuseFactor > 0) {
        DiffuseColor = vec4(Light.Color, 1.0f) * Light.Diffuse * DiffuseFactor;

        vec3 VertexToEye = normalize(eyeWorldPos - WorldPos);
        vec3 LightReflect = normalize(reflect(LightDirection, Normal));
        float SpecularFactor = dot(VertexToEye, LightReflect);
        SpecularFactor = pow(SpecularFactor, Specular.y);
        if (SpecularFactor > 0) {
            SpecularColor = vec4(Light.Color, 1.0f) * Specular.x * SpecularFactor;
        }
    }

    return (AmbientColor + DiffuseColor);// + SpecularColor);
}

vec4 CalcDirectionalLight(vec3 WorldPos, vec3 Normal, vec2 Specular)
{
    return CalcLightInternal(gDirectionalLight.Base,
							 gDirectionalLight.Direction,
							 WorldPos,
							 Normal,
							 Specular);
}

void main()
{
   	vec2 TexCoord = CalcTexCoord();
   	vec3 WorldPos = texture(gPositionMap, TexCoord).xyz;
   	vec3 Color = texture(gColorMap, TexCoord).xyz;
   	vec3 Normal = texture(gNormalMap, TexCoord).xyz;
	vec2 Specular = texture(gSpecularMap, TexCoord).xy;
   	Normal = normalize(Normal);

   	FragColor = vec4(Color, 1.0) * CalcDirectionalLight(WorldPos, Normal, Specular);
}