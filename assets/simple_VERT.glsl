#version 400 core

layout (location = 0) in vec3 position;
out vec3 pos;

void main ()
{
	gl_Position = vec4(position, 1.0f);
	pos = position;
}