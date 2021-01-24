#pragma once

#include <map>
#include <vector>
#include "render/Mesh.h"
#include "render/MeshColored.h"
#include "render/Shader.h"
#include "shape/ShapeClass.h"
#include "shape/icosahedron/Icosahedron.h"
#include "shape/icosahedron/IcosahedronStatic.h"
#include "random/PerlinNoise.h"
#include "random/PerlinNoise2D.h"
#include "random/PerlinNoise3D.h"
#include "random/simplexnoise/SimplexNoise.h"
#include "unit/vec4d.h"
#include "color/Pallete.h"

class IcoSphere : ShapeClass
{
private:
    using Lookup = std::map<std::pair<unsigned int, unsigned int>, unsigned int>;
    using Triangles = std::vector<Indice>;
    using Vertices = std::vector<Vertex>;

    const char *vShaderPath = "../res/shader/vSimplecolored.vert";
    const char *fShaderPath = "../res/shader/fSimple.frag";

    DetailedArray<vec4d> colors;
    MeshColored mesh;
    Shader shader;

    void subdivide(Vertices &vertices, Triangles &triangles, unsigned int depth);
    unsigned int findEdgeMid(Lookup &lookup, Vertices &vertices, unsigned int vert1, unsigned int vert2);
    void subdivideTriangle(const Indice &triangle, Vertices &vertices, Lookup &lookup, Triangles &newSet);
    void createIcosahedron(Vertices &vertices, Triangles &triangles);

public:
    unsigned int mDepth;
    glm::vec3 pos = glm::vec3(0.0f);
    bool isCreated = false;
    int createdCount = 0;
    bool isWarping = false, isWarped = false;
    double warpOffset, warpOffsetSpeed = 0.005;

    IcoSphere() : mDepth(0) {}
    IcoSphere(unsigned int depth) : mDepth(depth) {}
    void createShape();
    void createWThread();
    void create();
    void draw();
    void warp();
    void warpNoiseSpace();
};