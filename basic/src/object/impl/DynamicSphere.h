#pragma once

#include "object/Object.h"

class DynamicSphere : public Object
{
private:
    Enum::ShaderType dynamicSType;
    unsigned int sphereSegment;

public:
    DynamicSphere() : DynamicSphere(10) {}
    DynamicSphere(unsigned int segment) : sphereSegment(segment), dynamicSType(Enum::ShaderType::Simple) {}
    ~DynamicSphere() {}
    void setMesh() override
    {
        mesh = std::make_unique<Sphere>(sphereSegment);
        mesh->createMesh();
        mesh->calculateAverageNormals();
        mesh->createUniformColours(mColour);
    }
    virtual void setShaderType() override
    {
        shaderType = dynamicSType;
    }
    void changeShaderType(Enum::ShaderType type) { dynamicSType = type; }
};
