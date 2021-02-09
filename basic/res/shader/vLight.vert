#version 330

layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 colour;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec2 texCoord;

out vec4 vColour;
out vec3 vNormal;
out vec3 fPosition;
out vec2 vTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	// set vertex position
	gl_Position = projection * view * model * vec4(pos, 1.0);

	vTexCoord = texCoord;
	vColour = colour;
	vNormal = mat3(transpose(inverse(model))) * normal;
	fPosition = (model * vec4(pos, 1.0)).xyz;
}