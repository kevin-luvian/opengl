#version 330

layout(location = 0) in vec3 pos;

out vec4 fColor;

uniform mat4 mvp;

void main()
{
	gl_Position = mvp * vec4(pos, 1.0);
	fColor = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);
}