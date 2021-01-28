#pragma once

#include "ShaderClass.h"
#include "impl/SimpleShader.h"
#include "impl/LightShader.h"

namespace Enum
{
    enum class ShaderType
    {
        Simple = 0,
        Light = 1,
        Count = 2
    };

    static const ShaderType AllShaderType[] = {Enum::ShaderType::Simple, Enum::ShaderType::Light};
} // namespace Enum

class ShaderManager
{
private:
    DetailedArray<Enum::ShaderType> mShaderTypes;
    std::unique_ptr<SimpleShader> mSimpleShader;
    std::unique_ptr<LightShader> mLightShader;

public:
    ShaderManager() {}
    ~ShaderManager() {}
    void createShaders()
    {
        mSimpleShader = std::make_unique<SimpleShader>();
        mSimpleShader->compile();

        mLightShader = std::make_unique<LightShader>();
        mLightShader->compile();
    }
    ShaderClass *getShader(Enum::ShaderType type)
    {
        if (type == Enum::ShaderType::Simple)
            return (ShaderClass *)getSimpleShader();
        if (type == Enum::ShaderType::Light)
            return (ShaderClass *)getLightShader();
        return nullptr;
    }
    SimpleShader *getSimpleShader() { return mSimpleShader.get(); }
    LightShader *getLightShader() { return mLightShader.get(); }
};