#version 330 

uniform mat4 cmt;

uniform mat4 view;
uniform mat4 projection;

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

void main()
{ 
    gl_Position = projection * view * cmt * vec4(position, 1);
}