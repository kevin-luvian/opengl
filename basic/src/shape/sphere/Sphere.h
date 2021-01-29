#pragma once

#include "shape/ShapeClass.h"
#include "draw/renderer/Renderer.h"

class Sphere : public ShapeClass
{
private:
    typedef ShapeClass inherited;
    bool shouldUpdate = true;
    glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec4 mColour = glm::vec4(0);
    float mAngle = 0.0f, mSize = 1.0f;
    unsigned int segment;

    void generateVertices();
    void generateIndices();

public:
    Sphere() : segment(3) {}
    Sphere(unsigned int count) { setSegment(count); }

    void setPosition(glm::vec3 position);
    void createMesh();
    void create();
    void update();
    void render();
    void rotateY(float angle)
    {
        mAngle = angle;
        shouldUpdate = true;
    }
    void setSize(float size) { mSize = size; }
    void setColour(glm::vec4 colour) { mColour = colour; }
    void setSegment(unsigned int segment_)
    {
        if (segment_ < 3)
            segment_ = 3;
        segment = segment_;
    }
    unsigned int verticesSize() { return (segment * (segment - 2) + 2); }
    unsigned int indicesSize() { return (segment - 2) * 2 * segment; }
};