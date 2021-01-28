#pragma once

#include "ShaderClass.h"
#include "impl/SimpleShader.h"

namespace Enum
{
    enum ShaderType
    {
        Simple = 0,
        Count = 1
    };

    static const ShaderType AllShaderType[] = {Simple};
} // namespace Enum

class ShaderManager
{
private:
    DetailedArray<Enum::ShaderType> mShaderTypes;
    std::unique_ptr<SimpleShader> mSimpleShader;

public:
    ShaderManager() {}
    ~ShaderManager() {}
    void createShaders()
    {
        mSimpleShader = std::make_unique<SimpleShader>();
        mSimpleShader->compile();
    }
    ShaderClass *getShader(Enum::ShaderType type)
    {
        if (type == Enum::ShaderType::Simple)
            return (ShaderClass *)mSimpleShader.get();
        return nullptr;
    }
    SimpleShader *getSimpleShader() { return mSimpleShader.get(); }
};