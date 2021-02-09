#pragma once

namespace GLSLI
{
    static const std::string VMVP = "mvp";

    static const std::string VMODEL = "model";
    static const std::string VVIEW = "view";
    static const std::string VPROJECTION = "projection";

    static const std::string FCAMERA_POSITION = "cameraPosition";

    namespace Material
    {
        static const std::string SPECULAR_INTENSITY = "material.specularIntensity";
        static const std::string SHININESS = "material.shininess";
    } // namespace Material

    /* DirectionalLight stuff */
    namespace DirectionalLight
    {
        static const std::string COLOUR = "dirLight.base.colour";
        static const std::string AMBIENT_INTENSITY = "dirLight.base.ambientIntensity";
        static const std::string DIRECTION = "dirLight.direction";
        static const std::string DIFFUSE_INTENSITY = "dirLight.base.diffuseIntensity";
    } // namespace DirectionalLight

    /* PointLight stuff */
    namespace PointLight
    {
        static const unsigned int MAX = 4;
        static const std::string COUNT = "pointLightCount";
        static const std::string ARRAY = "pLights";
        static std::string ATTENUATION(unsigned int index)
        {
            return ARRAY + "[" + std::to_string(index) + "].attenuation";
        }
        static std::string POSITION(unsigned int index)
        {
            return ARRAY + "[" + std::to_string(index) + "].position";
        }
        static std::string COLOUR(unsigned int index)
        {
            return ARRAY + "[" + std::to_string(index) + "].base.colour";
        }
        static std::string AMBIENT_INTENSITY(unsigned int index)
        {
            return ARRAY + "[" + std::to_string(index) + "].base.ambientIntensity";
        }
        static std::string DIFFUSE_INTENSITY(unsigned int index)
        {
            return ARRAY + "[" + std::to_string(index) + "].base.diffuseIntensity";
        }
    } // namespace PointLight

    /* SpotLight stuff */
    namespace SpotLight
    {
        static const unsigned int MAX = 3;
        static const std::string COUNT = "spotLightCount";
        static const std::string ARRAY = "sLights";
        static std::string DIRECTION(unsigned int index)
        {
            return ARRAY + "[" + std::to_string(index) + "].direction";
        }
        static std::string CUTTOFF(unsigned int index)
        {
            return ARRAY + "[" + std::to_string(index) + "].cutoff";
        }
        static std::string ATTENUATION(unsigned int index)
        {
            return ARRAY + "[" + std::to_string(index) + "].pointLight.attenuation";
        }
        static std::string POSITION(unsigned int index)
        {
            return ARRAY + "[" + std::to_string(index) + "].pointLight.position";
        }
        static std::string COLOUR(unsigned int index)
        {
            return ARRAY + "[" + std::to_string(index) + "].pointLight.base.colour";
        }
        static std::string AMBIENT_INTENSITY(unsigned int index)
        {
            return ARRAY + "[" + std::to_string(index) + "].pointLight.base.ambientIntensity";
        }
        static std::string DIFFUSE_INTENSITY(unsigned int index)
        {
            return ARRAY + "[" + std::to_string(index) + "].pointLight.base.diffuseIntensity";
        }
    } // namespace SpotLight
} // namespace GLSLI