#pragma once

#include "mesh/core/Mesh.h"

namespace MeshFactory
{
    static Mesh Pyramid()
    {
        const Vertex sVertices[5] = {
            {unit::vec3(0.0f, 1.0f, 0.0f)},
            {unit::vec3(-1.0f, -1.0f, 1.0f)},
            {unit::vec3(1.0f, -1.0f, 1.0f)},
            {unit::vec3(1.0f, -1.0f, -1.0f)},
            {unit::vec3(-1.0f, -1.0f, -1.0f)}};

        const Indice sIndices[6] = {
            {0, 1, 2},
            {0, 2, 3},
            {0, 3, 4},
            {0, 4, 1},
            {1, 3, 2},
            {3, 1, 4}};

        Mesh mesh;
        mesh.vertices.make_from(sVertices, 5);
        mesh.indices.make_from(sIndices, 6);
        mesh.calculateOriginNormals();
        return mesh;
    }
};