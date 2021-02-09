#version 330

in vec4 vColour;
in vec3 vNormal;
in vec3 fPosition;
in vec2 vTexCoord;

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

struct SpotLight
{
	PointLight pointLight;
	vec3 direction;
	float cutoff;
};

struct Material
{
	float specularIntensity;
	float shininess;
};

const int MAX_POINT_LIGHT = 4;
const int MAX_SPOT_LIGHT = 3;

uniform int pointLightCount;
uniform PointLight pLights[MAX_POINT_LIGHT];

uniform int spotLightCount;
uniform SpotLight sLights[MAX_SPOT_LIGHT];

uniform DirectionalLight dirLight;
uniform Material material;

uniform vec3 cameraPosition;

uniform sampler2D texData;

vec4 calcDirectionLight(Light light, vec3 direction)
{
	if(direction == vec3(0)) return vec4(0, 0, 0, 0);

	vec3 normal = normalize(vNormal);
	vec3 lightDirection = normalize(-direction);

	// ambient light
	vec3 ambientColour = light.colour * light.ambientIntensity;

	// diffuse light
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

vec4 calcPointLight(PointLight light)
{
	vec3 direction = fPosition - light.position;
	float distance = length(direction);

	vec4 colour = calcDirectionLight(light.base, direction);

	float attenuationFactor = light.attenuation.x + 
								light.attenuation.y * distance + 
								light.attenuation.z * distance * distance;

	return colour / attenuationFactor;
}

vec4 calcPointLights()
{
	vec4 totalColour = vec4(0);
	for(int i = 0; i < pointLightCount; i++)
	{
		totalColour += calcPointLight(pLights[i]);
	}
	return totalColour;
}

float map(float value, float from_start, float from_end, float to_start, float to_end)
{
	return ((value - from_start) / (from_end - from_start) * (to_end - to_start)) + to_start;
}

vec4 calcSpotLights()
{
	vec4 totalColour = vec4(0);
	for(int i = 0; i < spotLightCount; i++)
	{
		vec3 lightDirection = normalize(fPosition - sLights[i].pointLight.position);
		float theta = dot(lightDirection, sLights[i].direction);
		if(theta > sLights[i].cutoff) 
		{
			float lerp = map(theta, sLights[i].cutoff, 1.0f, 0, 1.0f);
			totalColour += calcPointLight(sLights[i].pointLight) * lerp;
		}
	}
	return totalColour;
}

void main()
{
	vec4 lightsColour = calcDirectionLight(dirLight.base, dirLight.direction);
	lightsColour += calcPointLights();
	lightsColour += calcSpotLights();

	colour = vColour * texture(texData, vTexCoord);
	colour = colour * lightsColour;
}