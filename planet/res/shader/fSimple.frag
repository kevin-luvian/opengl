#version 330

flat in vec4 fCol;

out vec4 colour;

struct DirectionalLight
{
	vec3 colour;
	float intensity;
};

uniform DirectionalLight dLight;

void main()
{
	// ambient light
	vec4 ambientColour = vec4(dLight.colour, 1.0) * dLight.intensity;

	colour = fCol * ambientColour;
}