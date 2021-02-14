#version 330

in vec4 colour;
in vec2 texCoord;

out vec4 fColour;

uniform sampler2D texData;

void main()
{
	fColour = texture(texData, texCoord);
}