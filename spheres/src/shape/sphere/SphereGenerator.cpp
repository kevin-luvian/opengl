#include "SphereGenerator.h"

SphereGenerator::SphereGenerator(unsigned int x, unsigned int y)
{
    numX = x;
    numY = y;
}

void SphereGenerator::pushVertex(int &offset, float p1, float p2, float p3)
{
    mVertices[offset] = p1;
    mVertices[offset + 1] = p2;
    mVertices[offset + 2] = p3;
    offset += 3;
}

void SphereGenerator::pushIndice(int &offset, unsigned int p1, unsigned int p2, unsigned int p3)
{
    mIndices[offset] = p1;
    mIndices[offset + 1] = p2;
    mIndices[offset + 2] = p3;
    offset += 3;
}

std::unique_ptr<float[]> SphereGenerator::generateVertices()
{
    mVertices = std::make_unique<float[]>(vSize());
    double degX = 360.0 / numX;
    double degY = 180.0 / (numY - 1);
    double len, curRadY, curRadX;
    float x, y, z;
    int offset;

    pushVertex(offset, 0.0f, 1.0f, 0.0f); // top vertex
    for (int i = 1; i < numY - 1; i++)
    {
        curRadY = util::toRadians(degY * i);
        len = sin(curRadY); // Adjacent of degY
        y = cos(curRadY);   // Opposite of degY

        for (int j = 0; j < numX; j++)
        {
            curRadX = util::toRadians(degX * j);
            x = cos(curRadX) * len; // Adjacent of degX
            z = sin(curRadX) * len; // Opposite of degX
            pushVertex(offset, x, y, z);
        }
    }
    pushVertex(offset, 0.0f, -1.0f, 0.0f); // bottom vertex

    return std::move(mVertices);
}

void SphereGenerator::appendIPoint(int &offset, int pIndex, int vIndex)
{
    for (int i = 0; i < numX; i++)
    {
        pushIndice(offset, pIndex, vIndex + i, ((i + 1) % numX) + vIndex);
    }
}

std::unique_ptr<unsigned int[]> SphereGenerator::generateIndices()
{
    mIndices = std::make_unique<unsigned int[]>(iSize());

    int offset, start;
    unsigned int p1, p2, p3;

    appendIPoint(offset, 0, 1); // push first batch
    for (int i = 0; i < numY - 3; i++)
    {
        start = i * numX + 1;
        for (int j = 0; j < numX; j++)
        {
            p1 = start + j;
            p2 = ((j + 1) % numX) + start;
            p3 = p1 + numX;
            pushIndice(offset, p1, p2, p3);
            pushIndice(offset, p3, p2 + numX, p2);
        }
    }
    appendIPoint(offset, vCount() - 1, vCount() - 1 - numX); // push last batch

    return std::move(mIndices);
}

unsigned int SphereGenerator::vCount() { return vSize() / 3; }
unsigned int SphereGenerator::vSize() { return 3 * ((numX * (numY - 2)) + 2); }
unsigned int SphereGenerator::iSize() { return 3 * (numY - 2) * 2 * numX; }