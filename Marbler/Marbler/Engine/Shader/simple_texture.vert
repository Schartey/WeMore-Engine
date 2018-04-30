#version 330 core

layout (location = 0) in vec3 position;

out vec2 UV; //FragmentUV

void main() {
    // Apply all matrix transformations to position
    gl_Position = vec4(position, 1);
	UV = (position.xy+vec2(1,1))/2.0;
}
