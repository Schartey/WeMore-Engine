#version 330 

in vec3 position; 

struct BaseLight
{
    vec3 Color;
    float Ambient;
    float Diffuse;
};

struct Attenuation
{
    float Constant;
    float Linear;
    float Exp;
};

struct PointLight
{
    BaseLight Base;
    vec3 Position;
    Attenuation Atten;
};

struct SpotLight
{
    PointLight Base;
    vec3 Direction;
    float Cutoff;
};

uniform sampler2D gPositionMap;
uniform sampler2D gColorMap;
uniform sampler2D gNormalMap;
uniform sampler2D gSpecularMap;
uniform vec2 gScreenSize;
uniform PointLight gPointLight;
uniform mat4 view;
uniform mat4 eye;
uniform float gSpecularPower;
uniform float gMatSpecularIntensity;
uniform float Radius;

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
	vec3 eyeWorldPos = vec3(eye*vec4(1.0));
    vec4 AmbientColor = vec4(Light.Color, 1.0f) * Light.Ambient;
    float DiffuseFactor = dot(Normal, -LightDirection);

    vec4 DiffuseColor  = vec4(0, 0, 0, 0);
    vec4 SpecularColor = vec4(0, 0, 0, 0);

    if (DiffuseFactor > 0) {
        DiffuseColor = vec4(Light.Color, 1.0f) * Light.Diffuse * DiffuseFactor;

        vec3 VertexToEye = normalize(eyeWorldPos - WorldPos);
        vec3 LightReflect = normalize(reflect(LightDirection, Normal));
		LightReflect = -2*Normal*(dot(LightDirection, Normal)) + LightDirection;

        float SpecularFactor = dot(VertexToEye, LightReflect);
        SpecularFactor = pow(SpecularFactor, Specular.y);
        if (SpecularFactor > 0) {
            SpecularColor = vec4(Light.Color, 1.0f) * Specular.x * SpecularFactor;
        }
    }

    return (AmbientColor + DiffuseColor + SpecularColor);
}

vec4 CalcPointLight(vec3 WorldPos, vec3 Normal, vec2 Specular)
{
    vec3 LightDirection = WorldPos - gPointLight.Position;
    float Distance = length(LightDirection);
    LightDirection = normalize(LightDirection);

    vec4 Color = CalcLightInternal(gPointLight.Base, LightDirection, WorldPos, Normal, Specular);

    float Attenuation =  gPointLight.Atten.Constant +
                         gPointLight.Atten.Linear * Distance +
                         gPointLight.Atten.Exp * Distance * Distance;

    Attenuation = max(1.0, Attenuation);

    return Color / Attenuation; //Color / Attenuation;
}

void main()
{
   	vec2 TexCoord = CalcTexCoord();
   	vec3 WorldPos = texture(gPositionMap, TexCoord).xyz;
   	vec3 Color = texture(gColorMap, TexCoord).xyz;
   	vec3 Normal = texture(gNormalMap, TexCoord).xyz;
	vec2 Specular = texture(gSpecularMap, TexCoord).xy;

   	Normal = normalize(Normal);
	
   	FragColor = vec4(Color, 1.0) * CalcPointLight(WorldPos, Normal,Specular);
}