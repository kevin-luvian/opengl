#pragma once

#include "draw/renderer/Renderer.h"

class LightRenderer : public Renderer
{
private:
    typedef Renderer inherited;

public:
    LightRenderer() {}
    ~LightRenderer() {}

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
        inherited::create(mesh, []() {
            // define normal attributes
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
            glEnableVertexAttribArray(2);
        });
    };
};