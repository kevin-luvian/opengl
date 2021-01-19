#version 330 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec4 color;
layout(location = 2) in vec3 position;
layout(location = 3) in mat4 model;

flat out vec4 fColor;

uniform mat4 viewProjection;
uniform mat4 transform;

void main()
{
	fColor = vec4(clamp(vertex, 0.0f, 1.0f), 1.0f) + color;
	gl_Position = viewProjection * (model * vec4(vertex, 1.0) + vec4(position, 1.0));
}