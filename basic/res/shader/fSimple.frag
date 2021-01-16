#version 330

in vec4 vCol;

out vec4 colour;

void main()
{
	colour = vCol + vec4(0.0, 0.4, 0.7, 0.2);
}