#version 420
layout (location = 0) in vec4 Position;

uniform mat4 cmt;

uniform mat4 view;
uniform mat4 projection;

out vData
{
	float TTL1;
// additional vertex data goes here
} vertex;
void main()
{
	gl_Position = projection * view * vec4(Position.xyz, 1.0f);
	vertex.TTL1 = Position.w;
}