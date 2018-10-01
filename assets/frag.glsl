#version 300 es

precision mediump float;

in vec2 uv;
in vec3 norm;

out vec3 color;

//uniform sampler2D tex;

void	main()
{
//	color = texture(tex, uv).rgb;
	color = vec3(1, 1, 1) * max(dot(norm, vec3(0,0,1)), 0.1);
}