#pragma once

#include "shape/ShapeClass.h"
#include "draw/renderer/impl/SimpleRenderer.h"

class Sphere : public ShapeClass
{
private:
    SimpleRenderer renderer;
    glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
    float mAngle = 0.0f;
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
    void setSegment(unsigned int segment_)
    {
        if (segment_ < 3)
            segment_ = 3;
        segment = segment_;
    }
    unsigned int verticesSize() { return (segment * (segment - 2) + 2); }
    unsigned int indicesSize() { return (segment - 2) * 2 * segment; }
};