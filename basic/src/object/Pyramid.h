#pragma once

#include "core/SimpleObject.h"
#include "draw/shader/SimpleShader.h"
#include "mesh/factory/Pyramid.h"

class Pyramid : public SimpleObject
{
public:
    Pyramid()
    {
        useMesh(MeshFactory::Pyramid());
        createVerticesColorFromPos();
        auto color = Colors::OCEAN;
        color.a = 0.0f;
        addColor(color);
    }
    ~Pyramid() {}
    void onCreate() override
    {
        pos = unit::vec3(0, 0, -5);
        scale = 5.0f;
    }
    void onUpdate() override
    {
    }
};