#pragma once

class Light
{
public:
    glm::vec3 mAmbientColour;
    float mAmbientIntensity;
    float mDiffuseIntensity;

    Light()
    {
        mAmbientColour = glm::vec3(1.0f, 1.0f, 1.0f);
        mAmbientIntensity = 0.1f;
        mDiffuseIntensity = 0.3f;
    }
    virtual ~Light() {}
};