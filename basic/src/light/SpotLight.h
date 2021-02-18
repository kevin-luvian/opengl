#pragma once

#include "PointLight.h"

class SpotLight : public PointLight
{
private:
    unit::vec3 mDirection;
    float mCutoff;

public:
    SpotLight()
    {
        mPosition = Camera::Position();
        mDirection = Camera::Front();
        mCutoff = glm::cos(glm::radians(18.0f));
        mAttenuation = LightFactor::Attenuation::Dist_65;
    }
    ~SpotLight() {}
    void bind(Shader &shader, unsigned int i) const override
    {
        // Spot Light base
        shader.set3f(GLSLI::SpotLight::COLOUR(i), getColor());
        shader.set1f(GLSLI::SpotLight::AMBIENT_INTENSITY(i), getAmbientIntensity());
        shader.set1f(GLSLI::SpotLight::DIFFUSE_INTENSITY(i), getDiffuseIntensity());
        // Spot Light - Point Light instance
        shader.set3f(GLSLI::SpotLight::POSITION(i), getPosition());
        shader.set3f(GLSLI::SpotLight::ATTENUATION(i), getAttenuation());
        // Spot Light specific
        shader.set3f(GLSLI::SpotLight::DIRECTION(i), getDirection());
        shader.set1f(GLSLI::SpotLight::CUTOFF(i), getCutoff());
    };
    void updateToFlash()
    {
        mPosition = Camera::Position();
        mDirection = Camera::Front();
    }
    unit::vec3 getDirection() const { return mDirection; }
    void setDirection(unit::vec3 direction) { mDirection = direction; }
    float getCutoff() const { return mCutoff; }
    float setCutoff(float cutoff) { return mCutoff; }
};