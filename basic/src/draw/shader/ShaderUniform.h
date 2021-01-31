#pragma once

namespace ShaderUniform
{
    static const std::string VSIMPLE_MVP = "mvp";

    static const std::string V_MODEL = "model";
    static const std::string V_VIEW = "view";
    static const std::string V_PROJECTION = "projection";

    static const std::string F_CAMERA_POSITION = "cameraPosition";

    static const std::string FLIGHT_MATERIAL_SPECULAR_INTENSITY = "material.specularIntensity";
    static const std::string FLIGHT_MATERIAL_SHININESS = "material.shininess";

    /* DirectionalLight stuffs */
    static const std::string FLIGHT_DIRLIGHT_COLOUR = "dirLight.base.colour";
    static const std::string FLIGHT_DIRLIGHT_AMBIENT_INTENSITY = "dirLight.base.ambientIntensity";
    static const std::string FLIGHT_DIRLIGHT_DIRECTION = "dirLight.direction";
    static const std::string FLIGHT_DIRLIGHT_DIFFUSE_INTENSITY = "dirLight.base.diffuseIntensity";

    /* PointLight stuffs */
    static const unsigned int FLIGHT_MAX_POINT_LIGHT = 4;
    static const std::string FLIGHT_POINT_LIGHT_COUNT = "pointLightCount";
    static const std::string FLIGHT_POINT_LIGHT_ARRAY = "pLights";
    static std::string FLIGHT_POINT_LIGHT_ATTENUATION(unsigned int index)
    {
        return FLIGHT_POINT_LIGHT_ARRAY + "[" + std::to_string(index) + "].attenuation";
    }
    static std::string FLIGHT_POINT_LIGHT_POSITION(unsigned int index)
    {
        return FLIGHT_POINT_LIGHT_ARRAY + "[" + std::to_string(index) + "].position";
    }
    static std::string FLIGHT_POINT_LIGHT_COLOUR(unsigned int index)
    {
        return FLIGHT_POINT_LIGHT_ARRAY + "[" + std::to_string(index) + "].base.colour";
    }
    static std::string FLIGHT_POINT_LIGHT_AMBIENT_INTENSITY(unsigned int index)
    {
        return FLIGHT_POINT_LIGHT_ARRAY + "[" + std::to_string(index) + "].base.ambientIntensity";
    }
    static std::string FLIGHT_POINT_LIGHT_DIFFUSE_INTENSITY(unsigned int index)
    {
        return FLIGHT_POINT_LIGHT_ARRAY + "[" + std::to_string(index) + "].base.diffuseIntensity";
    }

    /* SpotLight stuffs */
    static const unsigned int FLIGHT_MAX_SPOT_LIGHT = 3;
    static const std::string FLIGHT_SPOT_LIGHT_COUNT = "spotLightCount";
    static const std::string FLIGHT_SPOT_LIGHT_ARRAY = "sLights";
    static std::string FLIGHT_SPOT_LIGHT_DIRECTION(unsigned int index)
    {
        return FLIGHT_SPOT_LIGHT_ARRAY + "[" + std::to_string(index) + "].direction";
    }
    static std::string FLIGHT_SPOT_LIGHT_CUTTOFF(unsigned int index)
    {
        return FLIGHT_SPOT_LIGHT_ARRAY + "[" + std::to_string(index) + "].cutoff";
    }
    static std::string FLIGHT_SPOT_LIGHT_ATTENUATION(unsigned int index)
    {
        return FLIGHT_SPOT_LIGHT_ARRAY + "[" + std::to_string(index) + "].pointLight.attenuation";
    }
    static std::string FLIGHT_SPOT_LIGHT_POSITION(unsigned int index)
    {
        return FLIGHT_SPOT_LIGHT_ARRAY + "[" + std::to_string(index) + "].pointLight.position";
    }
    static std::string FLIGHT_SPOT_LIGHT_COLOUR(unsigned int index)
    {
        return FLIGHT_SPOT_LIGHT_ARRAY + "[" + std::to_string(index) + "].pointLight.base.colour";
    }
    static std::string FLIGHT_SPOT_LIGHT_AMBIENT_INTENSITY(unsigned int index)
    {
        return FLIGHT_SPOT_LIGHT_ARRAY + "[" + std::to_string(index) + "].pointLight.base.ambientIntensity";
    }
    static std::string FLIGHT_SPOT_LIGHT_DIFFUSE_INTENSITY(unsigned int index)
    {
        return FLIGHT_SPOT_LIGHT_ARRAY + "[" + std::to_string(index) + "].pointLight.base.diffuseIntensity";
    }
}; // namespace ShaderUniform