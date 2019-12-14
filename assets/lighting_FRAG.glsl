#version 400 core

out vec4 fragColor;

in vec3 FragPos;
in vec2 texCoord;
in vec3 Normal;

uniform sampler2D ourTexture;
uniform vec3 lightPos;
uniform vec3 lightColour;
uniform vec3 viewPos;

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

	//specular lighting
	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColour;

	vec3 result = ambient + diffuse + specular;
	fragColor = texture(ourTexture, texCoord) * vec4(result, 1.0);
	
}