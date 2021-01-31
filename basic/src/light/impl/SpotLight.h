#pragma once

#include "screenview/Camera.h"
#include "PointLight.h"

class SpotLight : public PointLight
{
private:
    glm::vec3 mDirection;
    float mCuttoff;
    glm::vec3 flashCamDirectionOffset = glm::vec3(0.0, -0.05f, 0.0f);

public:
    SpotLight()
    {
        mPosition = Camera::Position();
        mDirection = Camera::Front() + flashCamDirectionOffset;
        mCuttoff = glm::cos(glm::radians(18.0f));
        mAttenuation = LightFactor::Attenuation::Dist_65;
    }
    ~SpotLight() {}
    void updateToFlash()
    {
        mPosition = Camera::Position();
        mDirection = Camera::Front() + flashCamDirectionOffset;
    }
    glm::vec3 getDirection() { return mDirection; }
    void setDirection(glm::vec3 direction) { mDirection = direction; }
    float getCuttoff() { return mCuttoff; }
    void printDirection()
    {
        std::cout << " dir x:" << mDirection.x << ", y:" << mDirection.y << ", z:" << mDirection.z;
    }
};