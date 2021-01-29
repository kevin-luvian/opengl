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

    static const std::string FLIGHT_DIRLIGHT_COLOUR = "dirLight.base.colour";
    static const std::string FLIGHT_DIRLIGHT_AMBIENT_INTENSITY = "dirLight.base.ambientIntensity";
    static const std::string FLIGHT_DIRLIGHT_DIRECTION = "dirLight.direction";
    static const std::string FLIGHT_DIRLIGHT_DIFFUSE_INTENSITY = "dirLight.base.diffuseIntensity";

    static const unsigned int FLIGHT_MAX_POINT_LIGHT = 4;
    static const std::string FLIGHT_POINT_LIGHT_COUNT = "pointLightCount";
    static const std::string FLIGHT_POINT_LIGHT_ARRAY = "pLights";

    // will return ex. "pLight[0].attenuation"
    static std::string FLIGHT_POINT_LIGHT_ATTENUATION(unsigned int index)
    {
        std::string res = FLIGHT_POINT_LIGHT_ARRAY;
        res.append("[" + std::to_string(index) + "].attenuation");
        return res;
    }
    static std::string FLIGHT_POINT_LIGHT_POSITION(unsigned int index)
    {
        std::string res = FLIGHT_POINT_LIGHT_ARRAY;
        res.append("[" + std::to_string(index) + "].position");
        return res;
    }
    static std::string FLIGHT_POINT_LIGHT_COLOUR(unsigned int index)
    {
        std::string res = FLIGHT_POINT_LIGHT_ARRAY;
        res.append("[" + std::to_string(index) + "].base.colour");
        return res;
    }
    static std::string FLIGHT_POINT_LIGHT_AMBIENT_INTENSITY(unsigned int index)
    {
        std::string res = FLIGHT_POINT_LIGHT_ARRAY;
        res.append("[" + std::to_string(index) + "].base.ambientIntensity");
        return res;
    }
    static std::string FLIGHT_POINT_LIGHT_DIFFUSE_INTENSITY(unsigned int index)
    {
        std::string res = FLIGHT_POINT_LIGHT_ARRAY;
        res.append("[" + std::to_string(index) + "].base.diffuseIntensity");
        return res;
    }
}; // namespace ShaderUniform