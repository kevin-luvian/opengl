#pragma once

#include "draw/shader/ShaderUniform.h"
#include "draw/shader/ShaderClass.h"
#include "screenview/Camera.h"
#include "light/Light.h"
#include "draw/material/Material.h"

class LightShader : public ShaderClass
{
public:
    LightShader() {}
    ~LightShader() {}
    void bind() override
    {
        glUseProgram(programID);
        setCameraPosition();
    }
    void compile() override { compileFromFile("../res/shader/vLight.vert", "../res/shader/fLight.frag"); }
    void attachShape(ShapeClass *shape) override
    {
        auto model = shape->getModel();
        auto view = Camera::View();
        auto projection = Camera::Projection();
        setMat4(ShaderUniform::V_MODEL, model);
        setMat4(ShaderUniform::V_VIEW, view);
        setMat4(ShaderUniform::V_PROJECTION, projection);
        setMaterialUniforms(&shape->getMaterial());
    }
    void setDirectionalLightUniforms(Light *light)
    {
        std::cout << "directional light added\n";
        bind();
        set3f(ShaderUniform::FLIGHT_COLOUR, light->mAmbientColour);
        set1f(ShaderUniform::FLIGHT_AMBIENT_INTENSITY, light->mAmbientIntensity);
        set3f(ShaderUniform::FLIGHT_DIRECTION, light->mDiffuseDirection);
        set1f(ShaderUniform::FLIGHT_DIFFUSE_INTENSITY, light->mDiffuseIntensity);
    }
    void setMaterialUniforms(Material *material)
    {
        set1f(ShaderUniform::FLIGHT_MATERIAL_SPECULAR_INTENSITY, material->mSpecularIntensity);
        set1f(ShaderUniform::FLIGHT_MATERIAL_SHININESS, material->mShine);
    }
    void setCameraPosition()
    {
        set3f(ShaderUniform::F_CAMERA_POSITION, Camera::Position());
    }
};