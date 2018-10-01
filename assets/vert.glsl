#version 300 es

layout(location = 0) in vec3 vert_pos;
layout(location = 1) in vec2 vert_uv;
layout(location = 2) in vec3 vert_norm;

uniform mat4 TP;
uniform mat4 T;

out vec2 uv;
out vec3 norm;

void	main()
{
	gl_Position = TP * vec4(vert_pos, 1);
	uv = vert_uv;
	norm = vec3(T * vec4(vert_norm, 0));
}