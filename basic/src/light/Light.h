#pragma once

class Light
{
protected:
    glm::vec3 mAmbientColour;
    float mAmbientIntensity;
    float mDiffuseIntensity;

public:
    Light()
    {
        mAmbientColour = glm::vec3(1.0f, 1.0f, 1.0f);
        mAmbientIntensity = 0.1f;
        mDiffuseIntensity = 0.3f;
    }
    virtual ~Light() {}

    glm::vec3 getColour() { return mAmbientColour; }
    void setColour(glm::vec3 colour) { mAmbientColour = colour; }
    float getAmbientIntensity() { return mAmbientIntensity; }
    void setAmbientIntensity(float intensity) { mAmbientIntensity = intensity; }
    float getDiffuseIntensity() { return mDiffuseIntensity; }
    void setDiffuseIntensity(float intensity) { mDiffuseIntensity = intensity; }
};