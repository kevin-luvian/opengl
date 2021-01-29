#version 330

in vec4 vColour;
in vec3 vNormal;
in vec3 fPosition;

out vec4 colour;

struct Light
{
	vec3 colour;
	float ambientIntensity;
	float diffuseIntensity;
};

struct DirectionalLight
{
	Light base;
	vec3 direction;
};

struct PointLight
{
	Light base;
	vec3 position;
	vec3 attenuation;
};

struct Material
{
	float specularIntensity;
	float shininess;
};

const int MAX_POINT_LIGHT = 4;

uniform int pointLightCount;
uniform PointLight pLights[MAX_POINT_LIGHT];
uniform DirectionalLight dirLight;
uniform Material material;

uniform vec3 cameraPosition;

vec4 calcDirectionLight(Light light, vec3 direction)
{
	if(direction == vec3(0)) 
	{
		return vec4(0, 0, 0, 0);
	}

	vec3 normal = normalize(vNormal);

	// ambient light
	vec3 ambientColour = light.colour * light.ambientIntensity;

	// diffuse light
	vec3 lightDirection = normalize(direction);
	float diffuseFactor = max(dot(normal, lightDirection), 0.0f);
	vec3 diffuseColour = light.colour * light.diffuseIntensity * diffuseFactor;

	// specular light
	vec3 specularColour = vec3(0, 0, 0);
	if(diffuseFactor > 0.0f) {
		vec3 vecCameraDir = normalize(cameraPosition - fPosition);
		vec3 vecReflectDir = reflect(-lightDirection, normal);
		float specularFactor = pow(max(dot(vecCameraDir, vecReflectDir), 0.0), material.shininess) * diffuseFactor;
		specularColour = light.colour * specularFactor * material.specularIntensity;
	}

	return vec4(ambientColour + diffuseColour + specularColour, 1.0);
}

vec4 calcPointLights()
{
	vec4 totalColour = vec4(0, 0, 0, 0);
	for(int i = 0; i < pointLightCount; i++)
	{
		vec3 direction = pLights[i].position - fPosition;
		float distance = length(direction);
		direction = normalize(direction);

		vec4 colour = calcDirectionLight(pLights[i].base, direction);

		float attenuationFactor = pLights[i].attenuation.x + 
									pLights[i].attenuation.y * distance + 
									pLights[i].attenuation.z * distance * distance;

		totalColour += (colour / attenuationFactor);
	}
	return totalColour;
}

void main()
{
	vec4 lightsColour = calcDirectionLight(dirLight.base, dirLight.direction);
	// lightsColour = vec4(0);
	lightsColour += calcPointLights();
	colour = vColour * lightsColour;
}