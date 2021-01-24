#pragma once

#include "glcomponent/Camera.h"
#include "render/Shader.h"
#include "render/MeshColored.h"
#include "shape/ShapeClass.h"
#include "random/PerlinNoise.h"
#include "random/PerlinNoise2D.h"
#include "random/PerlinNoise3D.h"
#include "unit/vec4d.h"

class Sheet : public ShapeClass
{
private:
    const char *vShaderPath = "../res/shader/vSimplecolored.vert";
    const char *fShaderPath = "../res/shader/fSimple.frag";
    unsigned int width, height;

    Shader shader;
    MeshColored mesh;
    DetailedArray<vec4d> colors;

    void generateVertices();
    void generateIndices();

public:
    Sheet(unsigned int width_, unsigned int height_) : width(width_), height(height_) {}
    void warp();
    void createShape();
    void create();
    void draw();
};