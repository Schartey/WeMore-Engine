#version 330 core

uniform mat4 translate;
uniform mat4 rotation;
uniform mat4 scale;
uniform mat4 pmodel;

uniform mat4 view;
uniform mat4 projection;

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

void main() {
    // Apply all matrix transformations to position
    gl_Position = projection * view * pmodel * translate * rotation * scale * vec4(position, 1);
}