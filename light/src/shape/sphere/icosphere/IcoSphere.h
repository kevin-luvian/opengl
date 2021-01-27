#pragma once

#include <map>
#include <unordered_map>
#include <vector>
#include "render/Mesh.h"
#include "render/MeshLighted.h"
#include "render/Shader.h"
#include "shape/ShapeClass.h"
#include "shape/icosahedron/Icosahedron.h"
#include "shape/icosahedron/IcosahedronStatic.h"
#include "render/material/Material.h"

class IcoSphere : ShapeClass
{
private:
    using Lookup = std::map<std::pair<unsigned int, unsigned int>, unsigned int>;
    using Triangles = std::vector<Indice>;
    using Vertices = std::vector<Vertex>;

    const char *vShaderPath = "../res/shader/vLight.vert";
    const char *fShaderPath = "../res/shader/fLight.frag";

    Material material;
    MeshLighted mesh;
    Shader shader;

    void subdivide(Vertices &vertices, Triangles &triangles, unsigned int depth);
    unsigned int findEdgeMid(Lookup &lookup, Vertices &vertices, unsigned int vert1, unsigned int vert2);
    void subdivideTriangle(const Indice &triangle, Vertices &vertices, Lookup &lookup, Triangles &newSet);
    void createIcosahedron(Vertices &vertices, Triangles &triangles);

public:
    unsigned int mDepth;
    glm::vec3 pos;

    IcoSphere() : mDepth(0) {}
    IcoSphere(unsigned int depth) : mDepth(depth) {}
    Shader &getShader() { return shader; }
    void createShape();
    void create();
    void draw();
};