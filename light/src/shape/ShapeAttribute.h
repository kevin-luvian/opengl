#pragma once

#include "Indice.h"

struct Vertex
{
    float x, y, z;
    static unsigned long count()
    {
        return 3;
    }
    void normalize()
    {
        // double invMag = 1 / sqrt(x * x + y * y + z * z);
        double invMag = util::fisqrt(x * x + y * y + z * z);
        x *= invMag;
        y *= invMag;
        z *= invMag;
    }
    // add two Vertex attribute and return new Vertex
    Vertex operator+(Vertex &other) const { return {x + other.x, y + other.y, z + other.z}; }
    friend std::ostream &operator<<(std::ostream &out, const Vertex &v)
    {
        out << "x:" << v.x << ", y:" << v.y << ", z:" << v.z;
        return out;
    }
};

struct ShapeAttribute
{
    DetailedArray<Indice> indices;
    DetailedArray<Vertex> vertices;

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