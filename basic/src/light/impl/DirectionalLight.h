#pragma once

#include "light/Light.h"

class DirectionalLight : public Light
{
protected:
    glm::vec3 mDiffuseDirection;

public:
    DirectionalLight()
    {
        mAmbientIntensity = 0.08f;
        mDiffuseDirection = glm::vec3(0.0, -0.5, 3.0);
        mDiffuseIntensity = 0.5f;
    }
    ~DirectionalLight() {}
    glm::vec3 getDirection() { return mDiffuseDirection; }
    void setDirection(glm::vec3 direction) { mDiffuseDirection = direction; }
};