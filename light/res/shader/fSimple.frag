#version 330

in vec4 fCol;

out vec4 colour;

void main()
{
	colour = fCol + vec4(0.0, 0.4, 0.7, 0.2);
}