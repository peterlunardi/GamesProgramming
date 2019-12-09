#version 400 core

layout (location = 0) in vec3 position;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 MVP;

out vec3 pos;
out vec2 texCoord;

void main ()
{
	gl_Position = MVP * vec4(position, 1.0f);
	pos = position;
	texCoord = aTexCoord;
}
