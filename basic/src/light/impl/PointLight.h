#pragma once

#include <algorithm>
#include "LightFactor.h"
#include "light/Light.h"
#include "screenview/Camera.h"

class PointLight : public Light
{
protected:
    glm::vec3 mPosition;
    glm::vec3 mAttenuation;

public:
    PointLight()
    {
        mDiffuseIntensity = 2.5f;
        mAmbientIntensity = 0.2f;
        mPosition = glm::vec3(0, 0, 0);
        mAttenuation = LightFactor::Attenuation::Dist_32;
    }
    virtual ~PointLight() {}

    virtual void update() {}

    glm::vec3 getAttenuation() { return mAttenuation; }
    void setAttenuation(float constant, float linear, float quadratic)
    {
        setAttenuation(glm::vec3(constant, linear, quadratic));
    }
    void setAttenuation(glm::vec3 attenuation_)
    {
        if (attenuation_.x == 0.0f)
            attenuation_.x = 1.0f;
        mAttenuation = attenuation_;
    }
    float getManhattanDistanceToCamera() const
    {
        auto dist = glm::abs(mPosition - Camera::Position());
        return util::min(dist.x, dist.y, dist.z);
    }
    void addVelocity(glm::vec3 vel) { mPosition += vel; }
    glm::vec3 getPosition() { return mPosition; }
    virtual void setPosition(glm::vec3 newPos) { mPosition = newPos; }
    void printPosition()
    {
        std::cout << "x:" << mPosition.x << ", y:" << mPosition.y << ", z:" << mPosition.z;
    }
    static bool DistanceComparer(PointLight const *a, PointLight const *b)
    {
        return a->getManhattanDistanceToCamera() < b->getManhattanDistanceToCamera();
    }
};