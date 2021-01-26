#version 330

layout(location = 0) in vec3 pos;

flat out vec4 fCol;

uniform mat4 mvp;

void main()
{
	gl_Position = mvp * vec4(pos, 1.0);
	fCol = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);
}