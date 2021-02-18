#pragma once

#include <algorithm>
#include "core/Light.h"
#include "glComponent/Camera.h"

class PointLight : public Light
{
protected:
    unit::vec3 mPosition;
    unit::vec3 mAttenuation;
    float distToCamera;

    void calcManhattanDistanceToCamera()
    {
        auto dist = unit::abs(mPosition - Camera::Position());
        distToCamera = util::min(dist.x, dist.y, dist.z);
    }

public:
    PointLight()
    {
        setDiffuseIntensity(2.5f);
        setAmbientIntensity(0.2f);
        mPosition = unit::vec3(0, 0, 0);
        mAttenuation = LightFactor::Attenuation::Dist_32;
    }
    virtual ~PointLight() {}

    virtual void update() { calcManhattanDistanceToCamera(); }
    virtual void bind(Shader &shader, unsigned int i) const
    {
        // Point Light base
        shader.set3f(GLSLI::PointLight::COLOUR(i), getColor());
        shader.set1f(GLSLI::PointLight::AMBIENT_INTENSITY(i), getAmbientIntensity());
        shader.set1f(GLSLI::PointLight::DIFFUSE_INTENSITY(i), getDiffuseIntensity());
        // Point Light specific
        shader.set3f(GLSLI::PointLight::POSITION(i), getPosition());
        shader.set3f(GLSLI::PointLight::ATTENUATION(i), getAttenuation());
    };
    unit::vec3 getAttenuation() const { return mAttenuation; }
    void setAttenuation(float constant, float linear, float quadratic)
    {
        setAttenuation(unit::vec3(constant, linear, quadratic));
    }
    void setAttenuation(unit::vec3 attenuation_)
    {
        if (attenuation_.x == 0.0f)
            attenuation_.x = 1.0f;
        mAttenuation = attenuation_;
    }
    float getDistanceToCamera() const { return distToCamera; }
    unit::vec3 getPosition() const { return mPosition; }
    void setPosition(unit::vec3 newPos) { mPosition = newPos; }

    static bool DistanceComparer(PointLight const *a, PointLight const *b)
    {
        return a->getDistanceToCamera() < b->getDistanceToCamera();
    }
};