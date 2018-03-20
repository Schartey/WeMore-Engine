#version 330 

uniform mat4 cmt;

uniform mat4 view;
uniform mat4 projection;

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

out vec3 fragVert;	 //Fragpos
out vec2 fragTexCoord; //FragmentUV
out vec3 fragNormal; //worldNormal

void main()
{ 

    gl_Position = projection * view * cmt * vec4(position, 1);
	fragTexCoord = uv;
	fragNormal = (cmt * vec4(normal,0)).xyz;
	fragVert = (cmt * vec4(position, 1.0f)).xyz;
}