#version 400 core

out vec4 fragColor;

in vec2 pass_texCoord;
in vec3 surfaceNormal;
in vec3 toLightVector[4];

uniform sampler2D ourTexture;
uniform vec3 lightColour[4];

void main()
{
	vec3 unitNormal = normalize(surfaceNormal);

	vec3 totalDiffuse = vec3(0.0);

	for(int i = 0; i < 4; i++)
	{
		vec3 unitLightVector = normalize(toLightVector[i]);
		float nDotl = dot(unitNormal, unitLightVector);
		float brightness = max(nDotl, 0.0);
		totalDiffuse = totalDiffuse + brightness * lightColour[i];
	}
	
	totalDiffuse = max(totalDiffuse, 0.2);

	fragColor = vec4(totalDiffuse, 1.0) * texture(ourTexture, pass_texCoord);
}