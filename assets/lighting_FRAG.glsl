#version 400 core

out vec4 fragColor;

in vec3 FragPos;
in vec2 texCoord;
in vec3 Normal;

uniform sampler2D ourTexture;
uniform vec3 lightPos;
uniform vec3 lightColour;

void main()
{
	//ambient light
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColour;

	//diffuse lighting
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColour;

	vec3 result = ambient + diffuse;
	fragColor = texture(ourTexture, texCoord) * vec4(result, 1.0);
}