#pragma once

#include "Indice.h"
#include "Vertex.h"
#include "shape/line/Line.h"

struct ShapeAttribute
{
    DetailedArray<Indice> indices;
    DetailedArray<Vertex> vertices;
    DetailedArray<VertexAttribute> vAttributes;
    DetailedArray<Line *> lines;

    void release()
    {
        indices.release();
        vertices.release();
        vAttributes.release();
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
    void drawNormalLines(glm::mat4 mvp)
    {
        for (size_t i = 0; i < lines.size; i++)
        {
            lines[i]->draw(mvp);
        }
    }
    void createNormalLines()
    {
        lines.make_empty(vertices.size);
        glm::vec3 start, end;
        float multiplier = 0.2;
        for (size_t i = 0; i < vertices.size; i++)
        {
            start = vertices[i].toGlmVec3();
            end = start + vAttributes[i].normal * multiplier;
            lines[i] = new Line(start, end);
        }
    }
    void calculateNormalsFromCenter()
    {
        vAttributes.make_empty(vertices.size);
        glm::vec3 vNormal;
        for (int i = 0; i < vertices.size; i++)
        {
            vNormal = glm::normalize(vertices[i].toGlmVec3());
            vAttributes[i].normal = vNormal;
        }
    }
    void calculateAverageNormals()
    {
        vAttributes.make_empty(vertices.size);
        Vertex vLeft, vRight, vTop;
        Vertex vSub1, vSub2;
        glm::vec3 vNormal;
        // calculate cross normal
        for (int i = 0; i < indices.size; i++)
        {
            Indice &curIndice = indices[i];
            vLeft = vertices[curIndice.left];
            vRight = vertices[curIndice.right];
            vTop = vertices[curIndice.top];

            vSub1 = vLeft - vTop;
            vSub2 = vRight - vTop;

            vNormal = glm::cross(vSub1.toGlmVec3(), vSub2.toGlmVec3());
            vNormal = glm::normalize(vNormal);

            vAttributes[curIndice.top].normal += vNormal;
            vAttributes[curIndice.left].normal += vNormal;
            vAttributes[curIndice.right].normal += vNormal;
        }
        // normalize all normal
        for (int i = 0; i < vAttributes.size; i++)
        {
            auto &curNormal = vAttributes[i].normal;
            curNormal = glm::normalize(curNormal);
        }
    }
};