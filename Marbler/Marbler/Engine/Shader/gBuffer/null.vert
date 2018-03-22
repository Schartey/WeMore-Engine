#version 330 

uniform mat4 cmt;

uniform mat4 view;
uniform mat4 projection;

layout (location = 0) in vec3 Position; 

void main()
{ 
    gl_Position = projection * view * cmt * vec4(Position, 1);
} 