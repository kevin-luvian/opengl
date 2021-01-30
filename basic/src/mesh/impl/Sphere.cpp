#include "Sphere.h"

void Sphere::generateVertices()
{
    double degX = 360.0 / segment;
    double degY = 180.0 / (segment - 1);
    double len, curRadY, curRadX;
    float x, y, z;
    int offset = 0;

    vertices.make_empty(verticesSize());
    vertices[offset++].pos = {0.0f, 1.0f, 0.0f}; // top vertex
    for (int i = 1; i < segment - 1; i++)
    {
        curRadY = util::toRadians(degY * i);
        len = sin(curRadY); // Adjacent of degY
        y = cos(curRadY);   // Opposite of degY

        for (int j = 0; j < segment; j++)
        {
            curRadX = util::toRadians(degX * j);
            x = cos(curRadX) * len; // Adjacent of degX
            z = sin(curRadX) * len; // Opposite of degX
            vertices[offset++].pos = {x, y, z};
        }
    }
    vertices[offset].pos = {0.0f, -1.0f, 0.0f}; // bottom vertex
}

void Sphere::generateIndices()
{
    indices.make_empty(indicesSize());

    int start;
    unsigned int offset = 0;
    unsigned int p1, p2, p3;

    // push first batch
    unsigned int pointI = 0;
    unsigned int startI = 1;
    for (int i = 0; i < segment; i++)
    {
        indices[offset++] = {((i + 1) % segment) + startI, startI + i, pointI};
    }

    // push mid triangles
    for (int i = 0; i < segment - 3; i++)
    {
        start = i * segment + 1;
        for (int j = 0; j < segment; j++)
        {
            p1 = start + j;
            p2 = ((j + 1) % segment) + start;
            p3 = p1 + segment;
            indices[offset++] = {p1, p2, p3};
            indices[offset++] = {p2, p2 + segment, p3};
        }
    }

    // push last batch
    pointI = verticesSize() - 1;
    startI = verticesSize() - 1 - segment;
    for (int i = 0; i < segment; i++)
    {
        indices[offset++] = {pointI, startI + i, ((i + 1) % segment) + startI};
    }
}

void Sphere::createMesh()
{
    BENCHMARK_PROFILE();
    generateVertices();
    generateIndices();
}