#pragma once

#include "draw/shader/ShaderUniform.h"
#include "draw/shader/ShaderClass.h"
#include "screenview/Camera.h"
#include "light/impl/DirectionalLight.h"
#include "light/impl/PointLight.h"
#include "draw/material/Material.h"

class LightShader : public ShaderClass
{
private:
    const char *vShaderPath = "../res/shader/vLight.vert";
    const char *fShaderPath = "../res/shader/fLight.frag";

public:
    LightShader() {}
    ~LightShader() {}
    void bind() override
    {
        glUseProgram(programID);
        attachCamera();
    }
    void compile() override { compileFromFile(vShaderPath, fShaderPath); }
    void attachShape(ShapeClass *shape) override
    {
        BENCHMARK_PROFILE();
        auto model = shape->getModel();
        setMat4(ShaderUniform::V_MODEL, model);
        attachMaterial(&shape->getMaterial());
    }
    std::unique_ptr<DirectionalLight> attachEmptyDirectionalLight()
    {
        std::unique_ptr<DirectionalLight> light(new DirectionalLight());
        light->mAmbientIntensity = 0.0f;
        light->mDiffuseIntensity = 0.0f;
        light->mDiffuseDirection = glm::vec3(0);
        attachDirectionalLight(light.get());
        return light;
    }
    void attachDirectionalLight(DirectionalLight *light)
    {
        BENCHMARK_PROFILE();
        bind();
        set3f(ShaderUniform::FLIGHT_DIRLIGHT_COLOUR, light->mAmbientColour);
        set1f(ShaderUniform::FLIGHT_DIRLIGHT_AMBIENT_INTENSITY, light->mAmbientIntensity);
        set3f(ShaderUniform::FLIGHT_DIRLIGHT_DIRECTION, light->mDiffuseDirection);
        set1f(ShaderUniform::FLIGHT_DIRLIGHT_DIFFUSE_INTENSITY, light->mDiffuseIntensity);
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
        set3f(ShaderUniform::FLIGHT_POINT_LIGHT_COLOUR(index), light->mAmbientColour);
        set1f(ShaderUniform::FLIGHT_POINT_LIGHT_AMBIENT_INTENSITY(index), light->mAmbientIntensity);
        set1f(ShaderUniform::FLIGHT_POINT_LIGHT_DIFFUSE_INTENSITY(index), light->mDiffuseIntensity);
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