#version 330 

uniform mat4 translate;
uniform mat4 scale;

uniform mat4 view;
uniform mat4 projection;

layout (location = 0) in vec3 Position; 

void main()
{ 
	mat4 model = translate * scale;
    gl_Position = projection * view * model * vec4(Position, 1);
} 