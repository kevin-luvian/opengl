#pragma once

#include "draw/shader/ShaderUniform.h"
#include "draw/shader/ShaderClass.h"
#include "screenview/Camera.h"
#include "light/Lights.h"
#include "draw/material/Material.h"

class LightShader : public ShaderClass
{
private:
    const char *vShaderPath = "../res/shader/vLight.vert";
    const char *fShaderPath = "../res/shader/fLight.frag";

public:
    LightShader() {}
    ~LightShader() {}
    void bind() override { glUseProgram(programID); }
    void setupUniforms() override { attachCamera(); }
    void compile() override { compileFromFile(vShaderPath, fShaderPath); }
    void attachObject(Object *object) override
    {
        BENCHMARK_PROFILE();
        auto model = object->getModel();
        setMat4(ShaderUniform::V_MODEL, model);
        attachMaterial(&object->getMaterial());
    }
    std::unique_ptr<DirectionalLight> attachEmptyDirectionalLight()
    {
        std::unique_ptr<DirectionalLight> light(new DirectionalLight());
        light->setDirection(glm::vec3(0));
        attachDirectionalLight(light.get());
        return light;
    }
    void attachDirectionalLight(DirectionalLight *light)
    {
        BENCHMARK_PROFILE();
        bind();
        set3f(ShaderUniform::FLIGHT_DIRLIGHT_COLOUR, light->getColour());
        set1f(ShaderUniform::FLIGHT_DIRLIGHT_AMBIENT_INTENSITY, light->getAmbientIntensity());
        set3f(ShaderUniform::FLIGHT_DIRLIGHT_DIRECTION, light->getDirection());
        set1f(ShaderUniform::FLIGHT_DIRLIGHT_DIFFUSE_INTENSITY, light->getDiffuseIntensity());
    }
    void attachPointLights(std::vector<PointLight *> lights)
    {
        bind();
        unsigned int size = lights.size();
        if (size > ShaderUniform::FLIGHT_MAX_POINT_LIGHT)
            size = ShaderUniform::FLIGHT_MAX_POINT_LIGHT;
        for (int i = 0; i < size; i++)
        {
            attachPointLight(lights[i], i);
        }
        set1i(ShaderUniform::FLIGHT_POINT_LIGHT_COUNT, size);
    }
    void attachPointLight(PointLight *light, unsigned int index)
    {
        BENCHMARK_PROFILE();
        if (index >= ShaderUniform::FLIGHT_MAX_POINT_LIGHT)
            throw std::runtime_error("light index exceed max number of point light");
        set3f(ShaderUniform::FLIGHT_POINT_LIGHT_ATTENUATION(index), light->getAttenuation());
        set3f(ShaderUniform::FLIGHT_POINT_LIGHT_POSITION(index), light->getPosition());
        set3f(ShaderUniform::FLIGHT_POINT_LIGHT_COLOUR(index), light->getColour());
        set1f(ShaderUniform::FLIGHT_POINT_LIGHT_AMBIENT_INTENSITY(index), light->getAmbientIntensity());
        set1f(ShaderUniform::FLIGHT_POINT_LIGHT_DIFFUSE_INTENSITY(index), light->getDiffuseIntensity());
    }
    void attachSpotLights(std::vector<SpotLight *> lights)
    {
        bind();
        unsigned int size = lights.size();
        if (size > ShaderUniform::FLIGHT_MAX_SPOT_LIGHT)
            size = ShaderUniform::FLIGHT_MAX_SPOT_LIGHT;
        for (int i = 0; i < size; i++)
        {
            attachSpotLight(lights[i], i);
        }
        set1i(ShaderUniform::FLIGHT_SPOT_LIGHT_COUNT, size);
    }
    void attachSpotLight(SpotLight *light, unsigned int index)
    {
        BENCHMARK_PROFILE();
        if (index >= ShaderUniform::FLIGHT_MAX_SPOT_LIGHT)
            throw std::runtime_error("light index exceed max number of spot light");

        set3f(ShaderUniform::FLIGHT_SPOT_LIGHT_DIRECTION(index), light->getDirection());
        set1f(ShaderUniform::FLIGHT_SPOT_LIGHT_CUTTOFF(index), light->getCuttoff());

        set3f(ShaderUniform::FLIGHT_SPOT_LIGHT_ATTENUATION(index), light->getAttenuation());
        set3f(ShaderUniform::FLIGHT_SPOT_LIGHT_POSITION(index), light->getPosition());
        set3f(ShaderUniform::FLIGHT_SPOT_LIGHT_COLOUR(index), light->getColour());
        set1f(ShaderUniform::FLIGHT_SPOT_LIGHT_AMBIENT_INTENSITY(index), light->getAmbientIntensity());
        set1f(ShaderUniform::FLIGHT_SPOT_LIGHT_DIFFUSE_INTENSITY(index), light->getDiffuseIntensity());
    }
    void attachMaterial(Material *material)
    {
        set1f(ShaderUniform::FLIGHT_MATERIAL_SPECULAR_INTENSITY, material->mSpecularIntensity);
        set1f(ShaderUniform::FLIGHT_MATERIAL_SHININESS, material->mShine);
    }
    void attachCamera()
    {
        set3f(ShaderUniform::F_CAMERA_POSITION, Camera::Position());
        setMat4(ShaderUniform::V_VIEW, Camera::View());
        setMat4(ShaderUniform::V_PROJECTION, Camera::Projection());
    }
};