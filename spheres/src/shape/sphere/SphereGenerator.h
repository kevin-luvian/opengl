#pragma once

#include "shape/ShapeAttribute.h"
#include "render/InstanceAttr.h"
#include "randoms/RGEN.h"

struct SphereInstanceInput
{
    unsigned int sphereCount;
    double posRange;
    double minScale;
    double maxScale;
};

class SphereGenerator
{
private:
    std::unique_ptr<Vertex[]> mVertices;
    std::unique_ptr<Indice[]> mIndices;
    unsigned int numX, numY;

    // push three point to vertices
    void pushVertex(int &offset, float p1, float p2, float p3);

    // push three point to indices
    void pushIndice(int &offset, unsigned int p1, unsigned int p2, unsigned int p3);

    // append top and bottom indices case
    void appendIPoint(int &offset, int pIndex, int vIndex);

    // return total count of vertices
    unsigned int vCount();

public:
    SphereGenerator(unsigned int x, unsigned int y);

    ShapeAttribute generateSphere();

    // Populate vertices and move its ownership
    std::unique_ptr<Vertex[]> generateVertices();

    // Populate indices and move its ownership
    std::unique_ptr<Indice[]> generateIndices();

    // return array size of vertices
    unsigned int vSize();

    // return array size of indices
    unsigned int iSize();

    // return instances attribute randomly generated
    std::unique_ptr<InstanceAttr[]> generateSphereInstances(SphereInstanceInput inp);
};