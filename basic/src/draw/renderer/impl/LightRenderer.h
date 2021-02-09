#pragma once

#include "draw/renderer/Renderer.h"

class LightRenderer : public Renderer
{
private:
    typedef Renderer inherited;

public:
    LightRenderer() {}
    ~LightRenderer() {}

    void bindLayouts() override
    {
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);
    };
    void unbindLayouts() override
    {
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(3);
    };
    void create(Mesh &mesh) override
    {
        BENCHMARK_PROFILE();
        inherited::create(mesh, []() {
            // define normal attributes
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
            glEnableVertexAttribArray(2);

            // define texcoord attributes
            glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texCoord));
            glEnableVertexAttribArray(3);
        });
    };
};