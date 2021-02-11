#version 330

layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 col;
layout(location = 2) in vec2 tex;

out vec4 colour;
out vec2 texCoord;

uniform mat4 model;
uniform mat4 viewProjection;

void main()
{
	gl_Position = viewProjection * model * vec4(pos, 1.0);
	colour = col;
	texCoord = tex;
}