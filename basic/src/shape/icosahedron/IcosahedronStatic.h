#pragma once

#include "screenview/Camera.h"
#include "shape/ShapeClass.h"

class IcosahedronStatic : public ShapeClass
{
private:
    const char *vShaderPath = "../res/shader/vSimple.vert";
    const char *fShaderPath = "../res/shader/fSimple.frag";
    const float X = .525731112119133606f;
    const float Z = .850650808352039932f;
    const float N = 0.f;

    const Vertex vertices[12] = {{-X, N, Z}, {X, N, Z}, {-X, N, -Z}, {X, N, -Z}, {N, Z, X}, {N, Z, -X}, {N, -Z, X}, {N, -Z, -X}, {Z, X, N}, {-Z, X, N}, {Z, -X, N}, {-Z, -X, N}};
    const Indice triangles[20] = {{0, 4, 1}, {0, 9, 4}, {9, 5, 4}, {4, 5, 8}, {4, 8, 1}, {8, 10, 1}, {8, 3, 10}, {5, 3, 8}, {5, 2, 3}, {2, 7, 3}, {7, 10, 3}, {7, 6, 10}, {7, 11, 6}, {11, 0, 6}, {0, 1, 6}, {6, 1, 10}, {9, 0, 11}, {9, 11, 2}, {9, 2, 5}, {7, 2, 11}};

public:
    void createShape()
    {
        shape.vertices.make_from(vertices, 12);
        shape.indices.make_from(triangles, 20);
    }
    void create() {}
    void draw() {}
};