#version 330

in vec4 colour;
in vec2 texCoord;

out vec4 fColour;

uniform sampler2D texData;

void main()
{
	fColour = colour * texture(texData, texCoord);
	fColour = texture(texData, texCoord);
	//fColour = colour;
}