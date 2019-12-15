#version 330 core

layout (location = 0) in vec3 position;

uniform float time;
uniform mat4 model;

const float PI = 3.1415926535897932384626433832795;
const float amplitude = 0.5;

float generateHeight(){
	float component1 = sin(2.0 * PI * time + (position.x * 16.0)) * amplitude;
	float component2 = sin(2.0 * PI * time + (position.z * position.x * 8.0)) * amplitude;
	return component1 + component2;
}

void main(void){

	vec3 worldPos = vec3(model * vec4(position, 1.0));
	float height = generateHeight();
	vec3 pos = vec3(worldPos.x, worldPos.y + height, worldPos.z);
	gl_Position = vec4(pos, 1.0) + (vec4(worldPos, 1.0) * 0);

}