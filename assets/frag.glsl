#version 300 es

precision mediump float;

in vec2 uv;
in vec3 norm;

out vec4 color;

uniform sampler2D tex;

void	main()
{
	vec3 c = texture(tex, uv).rgb;

	vec3 n = normalize(norm);
	float cos_theta = dot(n, vec3(0,0,1));
	c *=  max(abs(cos_theta), 0.15);
	color = vec4(c, 1.0);
}