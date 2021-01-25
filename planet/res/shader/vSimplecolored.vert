#version 330

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;

flat out vec4 fCol;

uniform mat4 mvp;

void main()
{
	gl_Position = mvp * vec4(pos, 1.0);
	fCol = vec4(color, 1.0f);
}