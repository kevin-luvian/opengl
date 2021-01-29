#pragma once

#include "draw/renderer/Renderer.h"

class SimpleRenderer : public Renderer
{
private:
    typedef Renderer inherited;

public:
    SimpleRenderer() {}
    ~SimpleRenderer() {}

    virtual void bindLayouts(){};
    virtual void unbindLayouts(){};
    virtual void create(Mesh &mesh)
    {
        BENCHMARK_PROFILE();
        inherited::create(mesh, []() {});
    };
};