#pragma once

#include "Indice.h"
#include "Vertex.h"

class Mesh
{
public:
    DetailedArray<Vertex> vertices;
    DetailedArray<Indice> indices;

    void release()
    {
        indices.release();
        vertices.release();
    }
    void PrintI()
    {
        for (unsigned int i = 0; i < indices.size; i++)
        {
            std::cout << "[" << i << "] " << indices[i] << "\n";
            if ((i + 1) % 4 == 0)
                std::cout << "\n";
        }
    }
};