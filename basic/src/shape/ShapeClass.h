#pragma once

#include "draw/mesh/Mesh.h"

class ShapeClass
{
protected:
    Mesh mesh;
    glm::mat4 model = glm::mat4(1.0f);

public:
    virtual ~ShapeClass() {}
    virtual glm::mat4 getModel() { return model; }
    virtual Mesh &getMesh() { return mesh; };
    virtual void createMesh() = 0;
    virtual void create() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
};