#pragma once

#include "draw/renderer/Renderer.h"
#include "draw/material/Material.h"
#include "draw/mesh/Mesh.h"

class ShapeClass
{
protected:
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<Material> material;
    Mesh mesh;
    glm::mat4 model = glm::mat4(1.0f);

public:
    ShapeClass()
    {
        attachMaterial(new Material());
    }
    virtual ~ShapeClass() {}
    virtual glm::mat4 getModel() { return model; }
    virtual Material &getMaterial() { return *material.get(); }
    virtual Mesh &getMesh() { return mesh; };
    virtual void attachMaterial(Material *material_) { material = std::unique_ptr<Material>(material_); }
    virtual void attachRenderer(Renderer *renderer_) { renderer = std::unique_ptr<Renderer>(renderer_); }
    virtual void create() = 0;
    virtual void createMesh() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
};