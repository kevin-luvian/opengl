#pragma once

#include "draw/shader/core/Shader.h"

class Light
{
private:
    unit::color mAmbientColor;
    float mAmbientIntensity;
    float mDiffuseIntensity;

public:
    Light()
    {
        mAmbientColor = unit::color(1.0f);
        mAmbientIntensity = 0.1f;
        mDiffuseIntensity = 0.3f;
    }
    virtual ~Light() {}

    unit::color getColor() const { return mAmbientColor; }
    void setColor(unit::color color) { mAmbientColor = color; }
    float getAmbientIntensity() const { return mAmbientIntensity; }
    void setAmbientIntensity(float intensity) { mAmbientIntensity = intensity; }
    float getDiffuseIntensity() const { return mDiffuseIntensity; }
    void setDiffuseIntensity(float intensity) { mDiffuseIntensity = intensity; }

    static const ShaderType SHADER_TYPE;
};
const ShaderType Light::SHADER_TYPE = ShaderType::Light;

namespace LightFactor
{
    namespace Attenuation
    {
        static const unit::vec3 Dist_7 = unit::vec3(1.0f, 0.7f, 1.8f);
        static const unit::vec3 Dist_13 = unit::vec3(1.0f, 0.35f, 0.44f);
        static const unit::vec3 Dist_20 = unit::vec3(1.0f, 0.22f, 0.20f);
        static const unit::vec3 Dist_32 = unit::vec3(1.0f, 0.14f, 0.07f);
        static const unit::vec3 Dist_50 = unit::vec3(1.0f, 0.09f, 0.032f);
        static const unit::vec3 Dist_65 = unit::vec3(1.0f, 0.07f, 0.017f);
        static const unit::vec3 Dist_100 = unit::vec3(1.0f, 0.045f, 0.0075f);
    } // namespace Attenuation
} // namespace LightFactor