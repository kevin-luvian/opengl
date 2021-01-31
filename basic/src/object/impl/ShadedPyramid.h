#pragma once

#include "object/Object.h"

class ShadedPyramid : public Object
{
private:
    Enum::ShaderType dynamicSType;

public:
    ShadedPyramid() { dynamicSType = Enum::ShaderType::Light; }
    ~ShadedPyramid() {}
    void setMesh() override
    {
        mesh = std::make_unique<Pyramid>();
        mesh->createMesh();
        mesh->calculateOriginNormals();
        mesh->createUniformColours(mColour);
    }
    virtual void setShaderType() override
    {
        shaderType = dynamicSType;
    }
    void changeShaderType(Enum::ShaderType type) { dynamicSType = type; }
};
