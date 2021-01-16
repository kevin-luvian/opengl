#pragma once

class SphereGenerator
{
private:
    std::unique_ptr<float[]> mVertices;
    std::unique_ptr<unsigned int[]> mIndices;
    unsigned int numX, numY;

    // push three point to vertices
    void pushVertex(int start, float p1, float p2, float p3);

    // push three point to indices
    void pushIndice(int start, unsigned int p1, unsigned int p2, unsigned int p3);

    // append top and bottom indices case
    void appendIPoint(int pIndex, int vIndex, int iOffset);

    // return total count of vertices
    unsigned int vCount();

public:
    SphereGenerator(unsigned int x, unsigned int y);

    // Populate vertices and move its ownership
    std::unique_ptr<float[]> generateVertices();

    // Populate indices and move its ownership
    std::unique_ptr<unsigned int[]> generateIndices();

    // Print vertices array
    void printV();

    // Print indices array
    void printI();

    // return array size of vertices
    unsigned int vSize();

    // return array size of indices
    unsigned int iSize();
};