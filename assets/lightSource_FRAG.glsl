#version 400 core

in vec3 pos;

out vec4 fragColor;

void main()
{
	fragColor = vec4(pos, 1.0);
}