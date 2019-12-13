#version 400 core

layout (location = 0) in vec3 aPosition;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;

uniform mat4 model;
uniform mat4 VP;

out vec3 FragPos;
out vec2 texCoord;
out vec3 Normal;

void main ()
{
	FragPos = vec3(model * vec4(aPosition, 1.0));
	Normal = mat3(transpose(inverse(model))) * aNormal;
	texCoord = aTexCoord;

	gl_Position = VP * vec4(FragPos, 1.0);
}
