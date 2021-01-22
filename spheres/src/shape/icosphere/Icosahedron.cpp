#include "Icosahedron.h"

std::unique_ptr<Vertex[]> generateVertices()
{
    auto vertices = std::make_unique<Vertex[]>(12);

    double yDegree = 90.0 - 26.5;
    double xzDegree = 72.0;
    float x, z;

    float y1 = cos(util::toRadians(60.0));
    float y2 = cos(util::toRadians(120.0));
    float len = sin(util::toRadians(yDegree));
    for (int i = 0; i < 5; i++) // Top Layer
    {
        float xzRad1 = util::toRadians(xzDegree * i);
        x = cos(xzRad1) * len; // Adjacent of degX
        z = sin(xzRad1) * len; // Opposite of degX
        vertices[i + 1] = {x, y1, z};

        float xzRad2 = util::toRadians(36.0 + (xzDegree * i));
        x = cos(xzRad1) * len; // Adjacent of degX
        z = sin(xzRad1) * len; // Opposite of degX
        vertices[i + 6] = {x, y2, z};
    }
    vertices[0] = {0.0f, 1.0f, 0.0f};   // Top Vertex
    vertices[11] = {0.0f, -1.0f, 0.0f}; // Bottom Vertex
    return vertices;
}

std::unique_ptr<Indice[]> generateIndices()
{
    auto indices = std::make_unique<Indice[]>(20);
    unsigned int count = 0;
    for (unsigned int i = 0; i < 5; i++)
    {
        indices[i] = {0, i + 1, (i + 1) % 5 + 1};
        indices[i + 5] = {i + 1, i + 6, (i + 4) % 5 + 6};
        indices[i + 10] = {i + 1, (i + 1) % 5 + 1, i + 6};
        indices[i + 15] = {11, i + 6, (i + 4) % 5 + 6};
    }
    return indices;
}

void Icosahedron::generateShape()
{
    shape.indices.data = generateIndices();
    shape.indices.size = 20;
    shape.vertices.data = generateVertices();
    shape.vertices.size = 12;
}