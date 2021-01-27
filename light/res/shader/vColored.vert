#version 330

layout(location = 0) in vec3 pos;

out vec4 fCol;

uniform mat4 mvp;
uniform vec4 colour;

void main()
{
	gl_Position = mvp * vec4(pos, 1.0);
	fCol = colour;
}