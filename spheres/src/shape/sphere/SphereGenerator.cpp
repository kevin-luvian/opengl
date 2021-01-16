#include "SphereGenerator.h"

SphereGenerator::SphereGenerator(unsigned int x, unsigned int y)
{
    numX = x;
    numY = y;
}

void SphereGenerator::pushVertex(int start, float p1, float p2, float p3)
{
    mVertices[start] = p1;
    mVertices[start + 1] = p2;
    mVertices[start + 2] = p3;
    // std::cout << "pushing :: "
    //           << "[" << start << "]: " << arr[start] << ", "
    //           << "[" << start + 1 << "]: " << arr[start + 1] << ", "
    //           << "[" << start + 2 << "]: " << arr[start + 2] << "\n";
}

std::unique_ptr<float[]> SphereGenerator::generateVertices()
{
    mVertices = std::make_unique<float[]>(vSize());
    double degX = 360.0 / numX;
    double degY = 180.0 / (numY - 1);
    double len, curDegY, curDegX;
    float x, y, z;

    pushVertex(0, 0.0f, 1.0f, 0.0f); // top vertex
    int offset = 3;
    for (int i = 0; i < numY - 2; i++)
    {
        curDegY = degY * (i + 1);
        len = sin(util::toRadians(curDegY)); // Adjacent of degY
        y = cos(util::toRadians(curDegY));   // Opposite of degY

        for (int j = 0; j < numX; j++)
        {
            curDegX = degX * j;
            x = cos(util::toRadians(curDegX)) * len; // Adjacent of degX
            z = sin(util::toRadians(curDegX)) * len; // Opposite of degX
            pushVertex(offset, x, y, z);
            offset += 3;
        }
    }

    pushVertex(offset, 0.0f, -1.0f, 0.0f); // bottom vertex
    // printV();

    return std::move(mVertices);
}

void SphereGenerator::pushIndice(int start, unsigned int p1, unsigned int p2, unsigned int p3)
{
    mIndices[start] = p1;
    mIndices[start + 1] = p2;
    mIndices[start + 2] = p3;
}

void SphereGenerator::appendIPoint(int pIndex, int vIndex, int iOffset)
{
    //todo optimize this
    int offset;
    for (int i = 0; i < numX - 1; i++)
    {
        offset = iOffset + (i * 3);
        pushIndice(offset, pIndex, vIndex + i, vIndex + i + 1);
    }
    offset = iOffset + ((numX - 1) * 3);
    pushIndice(offset, pIndex, vIndex, vIndex + numX - 1);
}

std::unique_ptr<unsigned int[]> SphereGenerator::generateIndices()
{
    mIndices = std::make_unique<unsigned int[]>(iSize());
    appendIPoint(0, 1, 0); // push first batch

    int offset = numX * 3;
    int start;
    for (int i = 0; i < numY - 3; i++)
    {
        start = i * numX + 1;
        for (int j = 0; j < numX - 1; j++)
        {
            pushIndice(offset, start + j, start + j + 1, start + numX + j);
            offset += 3;
            pushIndice(offset, start + numX + j, start + numX + j + 1, start + j + 1);
            offset += 3;
        }
        pushIndice(offset, start + numX - 1, start, start + 2 * numX - 1);
        offset += 3;
        pushIndice(offset, start + 2 * numX - 1, start + numX, start);
        offset += 3;
    }
    appendIPoint(vCount() - 1, vCount() - 1 - numX, iSize() - (numX * 3)); // push last batch
    // printI();

    return std::move(mIndices);
}

void SphereGenerator::printV()
{
    if (!mVertices)
        return;

    std::cout << "Vertices::\n";
    for (int i = 0; i < vSize(); i++)
    {
        std::cout << "[" << i << "]: " << mVertices[i] << ",\t";
        if ((i + 1) % 3 == 0)
            std::cout << "\n";
    }
    std::cout << "\n";
}

void SphereGenerator::printI()
{
    if (!mIndices)
        return;

    std::cout << "\nIndices::\n";
    for (int i = 0; i < iSize(); i++)
    {
        std::cout << "[" << i << "]: " << mIndices[i] << ", ";
        if ((i + 1) % 3 == 0)
        {
            std::cout << "\n";
            if ((i + 1) % numX == 0)
                std::cout << "\n";
        }
    }
    std::cout << "\n";
}

unsigned int SphereGenerator::vCount() { return vSize() / 3; }
unsigned int SphereGenerator::vSize() { return 3 * ((numX * (numY - 2)) + 2); }
unsigned int SphereGenerator::iSize() { return 3 * (((numY - 3) * numX * 2) + numX * 2); }