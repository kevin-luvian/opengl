#pragma once

#include "mesh/Mesh.h"
#include "draw/material/Material.h"
#include "draw/renderer/Renderers.h"
#include "draw/shader/ShaderEnum.h"

class Renderable
{
public:
    Renderable() {}
    virtual ~Renderable() {}

    virtual Material &getMaterial()
    {
        if (!material)
            setMaterial();
        return *material.get();
    }
    virtual Renderer &getRenderer() { return *renderer.get(); }
    virtual Enum::ShaderType getShaderType() const { return shaderType; }
    virtual void setShaderType(Enum::ShaderType type) { shaderType = type; }

    virtual void create()
    {
        if (!material)
            setMaterial();
        setMesh();
        setShaderType();
        setRenderer();
        renderer->create(*mesh.get());
    };
    virtual void render() { renderer->draw(); }
    static bool ShaderTypeComparer(Renderable const *a, Renderable const *b)
    {
        return a->getShaderType() < b->getShaderType();
    }

protected:
    Enum::ShaderType shaderType;
    std::unique_ptr<Mesh> mesh;
    std::unique_ptr<Material> material;
    std::unique_ptr<Renderer> renderer;

    virtual void setMesh() = 0;
    virtual void setMaterial() = 0;
    virtual void setShaderType() = 0;
    virtual void setRenderer() = 0;
};