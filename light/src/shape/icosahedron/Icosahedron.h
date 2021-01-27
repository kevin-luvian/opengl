#pragma once

#include "glcomponent/Camera.h"
#include "shape/ShapeClass.h"

class Icosahedron : public ShapeClass
{
private:
    const char *vShaderPath = "../res/shader/vSimple.vert";
    const char *fShaderPath = "../res/shader/fSimple.frag";
    Shader shader;
    Mesh mesh;
    DetailedArray<Vertex> generateVertices()
    {
        DetailedArray<Vertex> vertices;
        vertices.make_empty(12);

        double yDegree = 90.0 - 26.5;
        double xzDegree = 72.0;
        float x, z, xzRad1, xzRad2;

        float y1 = cos(util::toRadians(yDegree));
        float y2 = cos(util::toRadians(180.0 - yDegree));
        float len = sin(util::toRadians(yDegree));
        for (int i = 0; i < 5; i++) // Top Layer
        {
            xzRad1 = util::toRadians(xzDegree * i);
            x = cos(xzRad1) * len; // Adjacent of degX
            z = sin(xzRad1) * len; // Opposite of degX
            vertices[i + 1] = {x, y1, z};

            xzRad2 = util::toRadians(36.0 + (xzDegree * i));
            x = cos(xzRad2) * len; // Adjacent of degX
            z = sin(xzRad2) * len; // Opposite of degX
            vertices[i + 6] = {x, y2, z};
        }
        vertices[0] = {0.0f, 1.0f, 0.0f};   // Top Vertex
        vertices[11] = {0.0f, -1.0f, 0.0f}; // Bottom Vertex
        return vertices;
    }

    DetailedArray<Indice> generateIndices()
    {
        DetailedArray<Indice> indices;
        indices.make_empty(20);

        for (unsigned int i = 0; i < 5; i++)
        {
            indices[i] = {0, (i + 1) % 5 + 1, i + 1};
            indices[i + 5] = {i + 1, i + 6, (i + 4) % 5 + 6};
            indices[i + 10] = {i + 1, (i + 1) % 5 + 1, i + 6};
            indices[i + 15] = {(i + 4) % 5 + 6, i + 6, 11};
        }
        return indices;
    }

public:
    void createShape()
    {
        shape.indices = generateIndices();
        shape.vertices = generateVertices();
    }
    void create()
    {
        shader.compileFromFile(vShaderPath, fShaderPath);
        mesh.create(shape);
    }
    void draw()
    {
        auto mvp = Camera::GET().getViewProjection();
        shader.bind();
        shader.setMat4("mvp", mvp);
        mesh.drawDefault();
        mesh.unbind();
    }
};