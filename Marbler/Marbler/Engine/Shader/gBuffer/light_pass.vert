#version 330 

layout (location = 0) in vec3 position; 

uniform mat4 cmt;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 depthVP;

out vec4 ShadowCoord; //shadowmap coords*

void main()
{ 
	mat4 DepthBiasMVP = depthVP*cmt;
	ShadowCoord = DepthBiasMVP * vec4(position,1);

   	gl_Position = projection * view * cmt * vec4(position, 1);
} 