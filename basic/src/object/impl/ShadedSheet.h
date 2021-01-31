#pragma once

#include "object/Object.h"

class ShadedSheet : public Object
{
public:
    unsigned int width, height;
    ShadedSheet() : ShadedSheet(10, 10) {}
    ShadedSheet(unsigned int w, unsigned int h) : width(w), height(h) {}
    ~ShadedSheet() {}
    void setMesh() override
    {
        mesh = std::make_unique<Sheet>(width, height);
        mesh->createMesh();
        mesh->calculateAverageNormals();
        mesh->createVerticesColourFromPos();
    }
    virtual void setShaderType() override
    {
        shaderType = Enum::ShaderType::Light;
    }
};