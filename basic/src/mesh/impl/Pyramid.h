#pragma once

#include "mesh/Mesh.h"

class Pyramid : public Mesh
{
public:
    Pyramid() {}
    ~Pyramid() {}
    void createMesh() override
    {
        const Vertex sVertices[5] = {
            {glm::vec3(0.0f, 1.0f, 0.0f)},
            {glm::vec3(-1.0f, -1.0f, 1.0f)},
            {glm::vec3(1.0f, -1.0f, 1.0f)},
            {glm::vec3(1.0f, -1.0f, -1.0f)},
            {glm::vec3(-1.0f, -1.0f, -1.0f)}};

        const Indice sIndices[6] = {
            {0, 1, 2},
            {0, 2, 3},
            {0, 3, 4},
            {0, 4, 1},
            {1, 3, 2},
            {3, 1, 4}};

        vertices.make_from(sVertices, 5);
        indices.make_from(sIndices, 6);
    }
};