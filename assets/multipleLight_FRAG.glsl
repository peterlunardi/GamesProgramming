#version 400 core

out vec4 fragColor;

in vec2 pass_texCoord;
in vec3 surfaceNormal;
in vec3 toLightVector[4];
in vec3 worldPosition;

uniform sampler2D ourTexture;
uniform vec3 lightColour[4];
uniform vec3 attenuation[4];
uniform vec3 viewPos;

void main()
{
	vec3 unitNormal = normalize(surfaceNormal);
	vec3 viewDir = normalize(viewPos - worldPosition);

	vec3 totalDiffuse = vec3(0.0);
	vec3 totalSpecular = vec3(0.0);

	float specularStrength = 0.5;

	for(int i = 0; i < 4; i++)
	{
		float distance = length(toLightVector[i]);
		float attenFactor = attenuation[i].x + (attenuation[i].y * distance) + (attenuation[i].z * distance * distance);
		vec3 unitLightVector = normalize(toLightVector[i]);
		float nDotl = dot(unitNormal, unitLightVector);
		float brightness = max(nDotl, 0.0);
		totalDiffuse = totalDiffuse + (brightness * lightColour[i]) / attenFactor;

		vec3 reflectDir = reflect(-unitLightVector, unitNormal);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
		vec3 specular = specularStrength * spec * lightColour[i];
		totalSpecular = totalSpecular + specular / attenFactor;

	}
	
	totalDiffuse = max(totalDiffuse, 0.1);

	vec3 result = totalDiffuse + totalSpecular;

	fragColor = vec4(result, 1.0) * texture(ourTexture, pass_texCoord);
}