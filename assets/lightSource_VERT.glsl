#version 400 core

layout (location = 0) in vec3 aPosition;

out vec3 pos;

uniform mat4 model;
uniform mat4 VP;

void main ()
{
	gl_Position = VP * model * vec4(aPosition, 1.0);
	pos = aPosition;
}
