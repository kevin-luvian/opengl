#version 330

in vec4 vCol;
in vec3 vNorm;
in vec3 fPos;

out vec4 colour;

struct DirectionalLight
{
	vec3 colour;
	float ambientIntensity;
	vec3 direction;
	float diffuseIntensity;
};

struct Material
{
	float specularIntensity;
	float shininess;
};

uniform DirectionalLight dirLight;
uniform Material material;

uniform vec3 cameraPosition;

void main()
{
	vec3 normal = normalize(vNorm);

	// ambient light
	vec3 ambientColour = dirLight.colour * dirLight.ambientIntensity;

	// diffuse light
	vec3 lightDirection = normalize(dirLight.direction);
	float diffuseFactor = max(dot(normal, lightDirection), 0.0f);
	vec3 diffuseColour = dirLight.colour * dirLight.diffuseIntensity * diffuseFactor;

	// specular light
	vec3 specularColour = vec3(0, 0, 0);
	if(diffuseFactor > 0.0f) {
		vec3 vecCameraDir = normalize(cameraPosition - fPos);
		vec3 vecReflectDir = reflect(-lightDirection, normal);
		float specularFactor = pow(max(dot(vecCameraDir, vecReflectDir), 0.0), material.shininess) * diffuseFactor;
		specularColour = dirLight.colour * specularFactor * material.specularIntensity;
	}

	vec4 lightsColour = vec4(ambientColour + diffuseColour + specularColour, 1.0);
	colour = (vCol + vec4(0.0, 0.4, 0.7, 0.2)) * lightsColour;
}