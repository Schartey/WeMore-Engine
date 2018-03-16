#version 330 

layout (location = 0) in vec3 position; 

uniform mat4 translate;
uniform mat4 scale;

uniform mat4 view;
uniform mat4 projection;

void main()
{ 
	mat4 model = translate * scale;
   	gl_Position = projection * view * model * vec4(position, 1);
} 