#include "Sphere.h"

void Sphere::generateVertices()
{
    double degX = 360.0 / segment;
    double degY = 180.0 / (segment - 1);
    double len, curRadY, curRadX;
    float x, y, z;
    int offset = 0;

    shape.vertices.make_empty(verticesSize());
    shape.vertices[offset++] = {0.0f, 1.0f, 0.0f}; // top vertex
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
            shape.vertices[offset++] = {x, y, z};
        }
    }
    shape.vertices[offset] = {0.0f, -1.0f, 0.0f}; // bottom vertex
}

void Sphere::appendTBIndices(unsigned int &offset, unsigned int pIndex, unsigned int vIndex)
{
    for (int i = 0; i < segment; i++)
    {
        shape.indices[offset++] = {pIndex, vIndex + i, ((i + 1) % segment) + vIndex};
    }
}

void Sphere::generateIndices()
{
    // mIndices = std::make_unique<unsigned int[]>(iSize());
    shape.indices.make_empty(indicesSize());

    int start;
    unsigned int offset = 0;
    unsigned int p1, p2, p3;

    appendTBIndices(offset, 0, 1); // push first batch
    for (int i = 0; i < segment - 3; i++)
    {
        start = i * segment + 1;
        for (int j = 0; j < segment; j++)
        {
            p1 = start + j;
            p2 = ((j + 1) % segment) + start;
            p3 = p1 + segment;
            shape.indices[offset++] = {p1, p2, p3};
            shape.indices[offset++] = {p3, p2 + segment, p2};
            // pushIndice(offset, p1, p2, p3);
            // pushIndice(offset,);
        }
    }
    appendTBIndices(offset, verticesSize() - 1, verticesSize() - 1 - segment); // push last batch
}

void Sphere::createShape()
{
    generateVertices();
    generateIndices();
}

void Sphere::create()
{
    createShape();
    shader.compileFromFile(vShaderPath, fShaderPath);
    mesh.create(shape);
    pos = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Sphere::draw()
{
    auto vp = Camera::GET().getViewProjection();
    auto model = glm::translate(glm::mat4(1.0f), pos);
    shader.bind();
    shader.setMat4("mvp", vp * model);
    mesh.drawDefault();
    shader.unbind();
}