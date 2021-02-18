#pragma once

#include "draw/shader/core/Shader.h"
#include "draw/shader/core/ShaderType.h"
#include "draw/render/CompleteRenderable.h"
#include "mesh/core/Mesh.h"

class ModelObject : public CompleteRenderable, public Mesh
{
private:
    typedef CompleteRenderable renderer;

public:
    ModelObject() {}
    ~ModelObject() {}

    void create() { renderer::createBuffer(*this); }
    void render(Shader &shader)
    {
        renderer::render(shader, textures);
    }
};