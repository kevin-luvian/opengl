#pragma once

#include "draw/renderer/Renderer.h"

class ModelRenderer : public Renderer
{
private:
    typedef Renderer inherited;

public:
    ModelRenderer() {}
    ~ModelRenderer() {}

    virtual void bindLayouts()
    {
        glEnableVertexAttribArray(2);
    };
    virtual void unbindLayouts()
    {
        glDisableVertexAttribArray(2);
    };
    virtual void create(Mesh &mesh)
    {
        BENCHMARK_PROFILE();
        inherited::create(mesh, []() {
            // define normal attributes
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
            glEnableVertexAttribArray(2);
        });
    };
};