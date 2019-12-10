#version 400 core

out vec4 fragColor;

in vec3 pos;
in vec2 texCoord;

uniform sampler2D ourTexture;

void main()
{
	//vec4 colour = vec4(pos * 0.5 + 0.5, 1.0);
	vec4 brown = vec4(0.59, 0.29, 0, 1.0);
    fragColor = texture(ourTexture, texCoord) * brown;
}