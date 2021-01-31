#pragma once

#include "mesh/Mesh.h"

class Sphere : public Mesh
{
private:
    unsigned int segment;

public:
    Sphere() : segment(3) {}
    Sphere(unsigned int count) { setSegment(count); }
    void setSegment(unsigned int segment_)
    {
        if (segment_ < 3)
            segment_ = 3;
        segment = segment_;
    }
    unsigned int verticesSize() { return (segment * (segment - 2) + 2); }
    unsigned int indicesSize() { return (segment - 2) * 2 * segment; }
    void generateVertices();
    void generateIndices();
    void createMesh() override;
};