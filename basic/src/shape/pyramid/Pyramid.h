#pragma once

#include "draw/renderer/impl/LightRenderer.h"
#include "shape/ShapeClass.h"

class Pyramid : public ShapeClass
{
private:
    typedef ShapeClass inherited;
    glm::vec4 mColour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    float mOffset = 0.0f, mAngle = 0.0f, mSize = 1.0f;

public:
    void addVelocity(glm::vec3 vel) { pos += vel; }
    void setPosition(glm::vec3 position);
    void setSize(float size) { mSize = size; }
    void setColour(glm::vec4 colour) { mColour = colour; }
    void createMesh();
    void create();
    void update();
    void render();
};