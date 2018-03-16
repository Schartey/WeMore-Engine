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

out vec3 fragVert;	 //Fragpos
out vec2 fragTexCoord; //FragmentUV
out vec3 fragNormal; //worldNormal

void main() {

	mat4 model = translate * rotation * scale;
	fragTexCoord = uv;
	fragNormal = (model * vec4(normal,0)).xyz;
	fragVert = (model * vec4(position, 1.0f)).xyz;

    // Apply all matrix transformations to position
    gl_Position = projection * view * pmodel * model * vec4(position, 1);
}
