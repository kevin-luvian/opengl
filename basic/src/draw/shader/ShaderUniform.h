#pragma once

namespace ShaderUniform
{
    static const std::string VSIMPLE_MVP = "mvp";

    static const std::string V_MODEL = "model";
    static const std::string V_VIEW = "view";
    static const std::string V_PROJECTION = "projection";

    static const std::string F_CAMERA_POSITION = "cameraPosition";

    static const std::string FLIGHT_COLOUR = "dirLight.colour";
    static const std::string FLIGHT_AMBIENT_INTENSITY = "dirLight.ambientIntensity";
    static const std::string FLIGHT_DIRECTION = "dirLight.direction";
    static const std::string FLIGHT_DIFFUSE_INTENSITY = "dirLight.diffuseIntensity";

    static const std::string FLIGHT_MATERIAL_SPECULAR_INTENSITY = "material.specularIntensity";
    static const std::string FLIGHT_MATERIAL_SHININESS = "material.shininess";
}; // namespace ShaderUniform