#pragma once

#include "light/Light.h"

class DirectionalLight : public Light
{
public:
    glm::vec3 mDiffuseDirection;
    
    DirectionalLight()
    {
        // mAmbientColour = glm::vec3(0.3, 0.0, 1.0);
        mAmbientIntensity = 0.08f;
        mDiffuseDirection = glm::vec3(0.0, -0.5, 3.0);
        mDiffuseIntensity = 0.5f;
    }
    ~DirectionalLight() {}
};