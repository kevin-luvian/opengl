#version 330

layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 colour;

out vec4 fCol;

uniform mat4 model;
uniform mat4 viewProjection;

void main()
{
	gl_Position = viewProjection * model * vec4(pos, 1.0);
	fCol = colour;
}