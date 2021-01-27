#pragma once

#include "render/Shader.h"

class Light
{
private:
    glm::vec3 mAmbientColour;
    float mAmbientIntensity;
    glm::vec3 mDiffuseDirection;
    float mDiffuseIntensity;

public:
    Light()
    {
        mAmbientColour = glm::vec3(1.0f, 1.0f, 1.0f);
        mAmbientIntensity = 0.05f;
        mDiffuseDirection = glm::vec3(0.0, 0.0, 2.0);
        mDiffuseIntensity = 0.3f;
    };
    ~Light(){};
    void setAmbientIntensity(float intensity) { mAmbientIntensity = intensity; }
    void use(Shader &shader)
    {
        shader.bind();
        shader.set3f("dirLight.colour", mAmbientColour);
        shader.set1f("dirLight.ambientIntensity", mAmbientIntensity);
        shader.set3f("dirLight.direction", mDiffuseDirection);
        shader.set1f("dirLight.diffuseIntensity", mDiffuseIntensity);
        shader.unbind();
    }
};