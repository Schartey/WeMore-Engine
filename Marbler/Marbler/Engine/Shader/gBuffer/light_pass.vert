#version 330 

layout (location = 0) in vec3 position; 

uniform mat4 cmt;

uniform mat4 view;
uniform mat4 projection;

void main()
{ 
   	gl_Position = projection * view * cmt * vec4(position, 1);
} 