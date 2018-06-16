#version 330 

layout (location = 0) in vec3 position; 

uniform mat4 cmt;

uniform mat4 view;
uniform mat4 projection;
//uniform mat4 depthBiasVP;

//out vec4 ShadowCoord; //shadowmap coords*

void main()
{ 
	//ShadowCoord = depthBiasVP * vec4(position,1);

   	gl_Position = projection * view * vec4(position, 1);
} 