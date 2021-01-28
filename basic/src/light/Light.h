#pragma once

#include "screenview/Camera.h"

class Light
{
public:
    glm::vec3 pos = glm::vec3(0.0f);
    glm::vec3 mAmbientColour;
    float mAmbientIntensity;
    glm::vec3 mDiffuseDirection;
    float mDiffuseIntensity;

    Light()
    {
        mAmbientColour = glm::vec3(1.0f, 1.0f, 1.0f);
        mAmbientIntensity = 0.05f;
        mDiffuseDirection = glm::vec3(0.0, 0.0, 2.0);
        mDiffuseIntensity = 0.3f;
    }
    virtual ~Light() {}

    void setAmbientIntensity(float intensity) { mAmbientIntensity = intensity; }
    unsigned int getManhattanDistanceToCamera()
    {
        auto cPos = Camera::Position();
        auto dist = glm::abs(pos - cPos);
        return util::min(dist.x, dist.y, dist.z);
    }
};