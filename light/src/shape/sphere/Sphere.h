#pragma once

#include "glcomponent/Camera.h"
#include "render/Mesh.h"
#include "render/Shader.h"
#include "shape/ShapeClass.h"

class Sphere : public ShapeClass
{
private:
    const char *vShaderPath = "../res/shader/vSimple.vert";
    const char *fShaderPath = "../res/shader/fSimple.frag";
    Shader shader;
    Mesh mesh;
    unsigned int segment;

    // append top and bottom indices case
    void appendTBIndices(unsigned int &offset, unsigned int pIndex, unsigned int vIndex);

    // return total count of vertices
    unsigned int vCount();

    void generateVertices();
    void generateIndices();

public:
    glm::vec3 pos;

    Sphere() : segment(3) {}
    Sphere(unsigned int count) { setSegment(count); }

    void createShape();
    void create();
    void draw();

    void setSegment(unsigned int segment_)
    {
        if (segment_ < 3)
            segment_ = 3;
        segment = segment_;
    }
    unsigned int verticesSize() { return (segment * (segment - 2) + 2); }
    unsigned int indicesSize() { return (segment - 2) * 2 * segment; }
};