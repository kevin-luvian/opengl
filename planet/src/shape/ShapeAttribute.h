#pragma once

#include "Vertex.h"
#include "Indice.h"

struct ShapeAttribute
{
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
        std::cout << "\n";
    }
    void PrintV()
    {
        for (unsigned int i = 0; i < vertices.size; i++)
        {
            std::cout << "[" << i << "] " << vertices[i] << "\n";
            if ((i + 1) % 4 == 0)
                std::cout << "\n";
        }
        std::cout << "\n";
    }
};