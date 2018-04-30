#version 330 core

layout (location = 0) out vec4 Color; 

void main(){
	Color = vec4(gl_FragCoord.z);
}