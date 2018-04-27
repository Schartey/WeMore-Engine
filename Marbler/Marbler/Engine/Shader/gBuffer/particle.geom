#version 330
layout (points) in; // points in
layout (triangle_strip, max_vertices = 4) out; // quads out

uniform mat4 projection;

in vData { float TTL1; } vertex[]; // from vertex shader

out vec2 TexCoord0;

flat out float TTL0; // flat: no interpolation between vertices

void main (void) {
	const vec2 size = vec2(5, 5);
	vec4 P = gl_in[0].gl_Position; // position in view-space
	vec2 va = P.xy + vec2(-0.5, -0.5) * size; // bottom-left corner
	gl_Position = projection * vec4(va, P.zw);
	TexCoord0 = vec2(0.0, 0.0);
	TTL0 = vertex[0].TTL1;
	EmitVertex();

	va = P.xy + vec2(-0.5, 0.5) * size; // top-left corner
	gl_Position = projection * vec4(va, P.zw);
	TexCoord0 = vec2(0.0, 1.0);
	TTL0 = vertex[0].TTL1;
	EmitVertex();

	va = P.xy + vec2(0.5, 0.5) * size; // top-right corner
	gl_Position = projection * vec4(va, P.zw);
	TexCoord0 = vec2(1.0, 1.0);
	TTL0 = vertex[0].TTL1;
	EmitVertex();

	va = P.xy + vec2(0.5, -0.5) * size; // bottom-right corner
	gl_Position = projection * vec4(va, P.zw);
	TexCoord0 = vec2(1.0, 0.0);
	TTL0 = vertex[0].TTL1;
	EmitVertex();

	EndPrimitive();
}