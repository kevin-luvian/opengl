#pragma once

#include "core/Light.h"

class DirectionalLight : public Light
{
private:
    unit::vec3 mDiffuseDirection;

public:
    DirectionalLight()
    {
        setAmbientIntensity(0.08f);
        setDiffuseIntensity(0.5f);
        mDiffuseDirection = unit::vec3(0.0f, -1.0f, -1.0f);
    }
    ~DirectionalLight() {}
    void bind(Shader &shader) const
    {
        // Directional Light base
        shader.set3f(GLSLI::DirectionalLight::COLOUR, getColor());
        shader.set1f(GLSLI::DirectionalLight::AMBIENT_INTENSITY, getAmbientIntensity());
        shader.set1f(GLSLI::DirectionalLight::DIFFUSE_INTENSITY, getDiffuseIntensity());
        // Directional Light specific
        shader.set3f(GLSLI::DirectionalLight::DIRECTION, getDirection());
    };
    unit::vec3 getDirection() const { return mDiffuseDirection; }
    void setDirection(unit::vec3 direction) { mDiffuseDirection = direction; }
};