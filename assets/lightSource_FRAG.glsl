#version 400 core

in vec3 pos;

out vec4 fragColor;

void main()
{
	vec3 colour = pos * 0.5 + 0.5;
	fragColor = vec4(colour, 1.0);
}