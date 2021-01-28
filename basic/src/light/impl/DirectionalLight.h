#pragma once

#include "light/Light.h"

class DirectionalLight : public Light
{
public:
    DirectionalLight()
    {
        mAmbientIntensity = 0.08f;
        mDiffuseDirection = glm::vec3(0.0, -0.5, 3.0);
        mDiffuseIntensity = 0.5f;
    }
    ~DirectionalLight() {}
};