#pragma once

#include "light/Light.h"
#include "screenview/Camera.h"

class PointLight : public Light
{
protected:
    glm::vec3 pos = glm::vec3(5.0, 0, 0);
    glm::vec3 attenuation = glm::vec3(1.0, 0.2, 0.1);

public:
    PointLight()
    {
        mDiffuseIntensity = 3.5f;
        mAmbientIntensity = 0.2f;
    }
    virtual ~PointLight() {}

    virtual void update() {}

    glm::vec3 getAttenuation() { return attenuation; }
    void setAttenuation(float constant, float linear, float exponent)
    {
        setAttenuation(glm::vec3(constant, linear, exponent));
    }
    void setAttenuation(glm::vec3 attenuation_)
    {
        if (attenuation_.x == 0.0f)
            attenuation_.x = 1.0f;
        attenuation = attenuation_;
    }
    float getManhattanDistanceToCamera() const
    {
        auto dist = glm::abs(pos - Camera::Position());
        return util::min(dist.x, dist.y, dist.z);
    }
    void addVelocity(glm::vec3 vel)
    {
        pos += vel;
    }
    glm::vec3 getPosition()
    {
        return pos;
    }
    virtual void setPosition(glm::vec3 newPos)
    {
        pos = newPos;
    }
    void printPosition()
    {
        std::cout << "x:" << pos.x << ", y:" << pos.y << ", z:" << pos.z;
    }
};