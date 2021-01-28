#pragma once

#include "draw/renderer/impl/SimpleRenderer.h"
#include "shape/ShapeClass.h"

class Pyramid : public ShapeClass
{
private:
    SimpleRenderer renderer;
    glm::vec3 pos;
    float mOffset = 0.0f, mAngle = 0.0f;

public:
    void setPosition(glm::vec3 position);
    void createMesh();
    void create();
    void update();
    void render();
};