#version 300 es

precision mediump float;

in vec2 uv;
in vec3 norm;

out vec3 color;

//uniform sampler2D tex;

void	main()
{
	//color = texture(tex, uv).rgb;

	vec3 n = normalize(norm);
	float cos_theta = dot(n, vec3(0,0,1));
	color = vec3(1, 1, 1) * max(abs(cos_theta), 0.15);
}