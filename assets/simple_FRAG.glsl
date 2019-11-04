#version 400 core

out vec4 fragColor;
in vec3 pos;

uniform vec3 objectColor;

void main()
{	
	fragColor = vec4(pos * 0.5 + 0.5, 1.0);
	//fragColor = vec4(objectColor, 1.0);
}