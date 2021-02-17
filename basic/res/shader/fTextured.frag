#version 330

in vec4 colour;
in vec2 texCoord;

out vec4 fColour;

uniform sampler2D texture_diffuse0;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular0;
uniform sampler2D texture_specular1;

void main()
{
	fColour = colour;
	fColour *= texture(texture_diffuse0, texCoord);
	fColour *= texture(texture_diffuse1, texCoord);
	fColour *= texture(texture_specular0, texCoord);
	fColour *= texture(texture_specular1, texCoord);
}