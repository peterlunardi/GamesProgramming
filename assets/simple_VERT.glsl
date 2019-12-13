#version 400 core

layout (location = 0) in vec3 aPosition;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 VP;

out vec3 pos;
out vec2 texCoord;

void main ()
{
	gl_Position = VP * model * vec4(aPosition, 1.0f);
	pos = aPosition;
	texCoord = aTexCoord;
}
