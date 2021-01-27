#pragma once

#include "glcomponent/Camera.h"
#include "render/MeshLighted.h"
#include "render/Shader.h"
#include "render/material/Material.h"
#include "shape/ShapeClass.h"

class Sphere : public ShapeClass
{
private:
    const char *vShaderPath = "../res/shader/vLight.vert";
    const char *fShaderPath = "../res/shader/fLight.frag";
    Shader shader;
    MeshLighted mesh;
    Material material;
    unsigned int segment;

    void generateVertices();
    void generateIndices();

public:
    glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);

    Sphere() : segment(3) {}
    Sphere(unsigned int count) { setSegment(count); }

    void createShape();
    void create();
    void draw();
    Shader &getShader() { return shader; }
    void setSegment(unsigned int segment_)
    {
        if (segment_ < 3)
            segment_ = 3;
        segment = segment_;
    }
    unsigned int verticesSize() { return (segment * (segment - 2) + 2); }
    unsigned int indicesSize() { return (segment - 2) * 2 * segment; }
};