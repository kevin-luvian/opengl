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

void Sphere::generateIndices()
{
    // mIndices = std::make_unique<unsigned int[]>(iSize());
    shape.indices.make_empty(indicesSize());

    int start;
    unsigned int offset = 0;
    unsigned int p1, p2, p3;

    // push first batch
    unsigned int pointI = 0;
    unsigned int startI = 1;
    for (int i = 0; i < segment; i++)
    {
        shape.indices[offset++] = {((i + 1) % segment) + startI, startI + i, pointI};
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
            shape.indices[offset++] = {p1, p2, p3};
            shape.indices[offset++] = {p2, p2 + segment, p3};
            // pushIndice(offset, p1, p2, p3);
            // pushIndice(offset,);
        }
    }

    // push last batch
    pointI = verticesSize() - 1;
    startI = verticesSize() - 1 - segment;
    for (int i = 0; i < segment; i++)
    {
        shape.indices[offset++] = {pointI, startI + i, ((i + 1) % segment) + startI};
    }
}

void Sphere::createShape()
{
    generateVertices();
    generateIndices();
    shape.calculateAverageNormals();
    shape.createNormalLines();
}

void Sphere::create()
{
    createShape();
    shader.compileFromFile(vShaderPath, fShaderPath);
    mesh.create(shape);
    material.setShine(32.0f);
    material.setSpecularIntensity(2.0f);
}

void Sphere::draw()
{
    auto model = glm::translate(glm::mat4(1.0f), pos);
    shader.bind();
    shader.setMat4("model", model);
    shader.setMat4("view", Camera::GET().getView());
    shader.setMat4("projection", Camera::GET().getProjection());
    material.use(shader);
    mesh.draw();
    shader.unbind();
    shape.drawNormalLines(Camera::GET().getViewProjection() * model);
}