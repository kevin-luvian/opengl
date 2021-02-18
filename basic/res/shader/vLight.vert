#version 330

layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 colour;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec3 normal;

out vec4 vColour;
out vec3 vNormal;
out vec3 vPosition;
out vec2 vTexCoord;

uniform mat4 model;
uniform mat4 viewProjection;

void main()
{
	// set vertex position
	gl_Position = viewProjection * model * vec4(pos, 1.0);

	// create colour
	vColour = colour;

	// create normal and fragment position
	vNormal = mat3(transpose(inverse(model))) * normal;
	vPosition = (model * vec4(pos, 1.0)).xyz;

	// pass out texture coordinates
	vTexCoord = texCoord;
}