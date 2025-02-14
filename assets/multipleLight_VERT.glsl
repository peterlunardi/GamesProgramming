#version 400 core

layout (location = 0) in vec3 aPosition;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;

out vec2 pass_texCoord;
out vec3 surfaceNormal;
out vec3 toLightVector[4];
out vec3 worldPosition;

uniform mat4 model;
uniform mat4 VP;
uniform vec3 lightPos[4];

void main ()
{
	vec4 worldPos = model * vec4(aPosition, 1.0);
	gl_Position = VP * worldPos;
	pass_texCoord = aTexCoord;
	worldPosition = worldPos.xyz;

	surfaceNormal = mat3(transpose(inverse(model))) * aNormal;
	for(int i = 0; i < 4; i++) 
	{
		toLightVector[i] = lightPos[i] - worldPos.xyz;
	}
	
}
