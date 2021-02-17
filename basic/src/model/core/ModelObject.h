#pragma once

#include "draw/shader/core/Shader.h"
#include "draw/shader/core/ShaderType.h"
#include "draw/render/TexturedRenderable.h"
#include "mesh/core/Mesh.h"

class ModelObject : public TexturedRenderable, public Mesh
{
private:
    typedef TexturedRenderable renderer;

public:
    ModelObject() {}
    ~ModelObject() {}

    ShaderType getShaderType() const { return ShaderType::Textured; }
    void create() { renderer::createBuffer(*this); }
    void render(Shader &shader)
    {
        renderer::render(shader, textures);
    }
};