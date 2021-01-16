#include "SpherePool.h"

SpherePool::SpherePool(unsigned int size, unsigned int segX, unsigned int segY)
{
    mSize = size;
    numX = segX;
    numY = segY;
}

void SpherePool::create()
{
    BENCHMARK_PROFILE();
    SphereGenerator sgen(numX, numY);
    std::unique_ptr<float[]> vertices = sgen.generateVertices();
    std::unique_ptr<unsigned int[]> indices = sgen.generateIndices();

    mShader = std::make_shared<Shader>();
    mMesh = std::make_shared<Mesh>();

    mShader->compileFromFile(vShaderPath, fShaderPath);
    mMesh->create(
        Attribute<float>{vertices.get(), sgen.vSize()},
        Attribute<unsigned int>{indices.get(), sgen.iSize()});

    generateSpheres();
}

void SpherePool::generateSpheres()
{
    BENCHMARK_PROFILE();
    mSpheres = std::make_unique<Sphere[]>(mSize);

    float x, z = -1.0f;
    int rowSize = sqrt(mSize);
    float sphereSize = mSpheres[0].radius;
    for (int i = 0; i < mSize; i++)
    {
        mSpheres[i] = Sphere(1.0f, glm::vec3(x, 0.0f, z));
        x += sphereSize * 2;
        if ((i + 1) % rowSize == 0)
        {
            x = 0.0f;
            z -= sphereSize * 2;
        }
    }
}

void SpherePool::updateBatch(int startPos, int endPos)
{
    BENCHMARK_PROFILE();
    for (int i = startPos; i < endPos; i++)
    {
        // mSpheres[i].update();
        mSpheres[i].updateQuick();
    }
}

void SpherePool::drawBatch(int startPos, int endPos)
{
    BENCHMARK_PROFILE();
    for (int i = startPos; i < endPos; i++)
    {
        mShader->setMVP(mSpheres[i].mvp);
        mMesh->draw();
        // mSpheres[i].draw(mShader, mMesh);
    }
}

void SpherePool::update()
{
    BENCHMARK_PROFILE();

    if (mSize <= 10)
    {
        updateBatch(0, mSize);
        return;
    }

    std::thread mThreads[THREAD_COUNT];
    int batchSize = mSize / THREAD_COUNT;
    int startPos, endPos;

    for (int i = 0; i < THREAD_COUNT; i++)
    {
        startPos = i * batchSize;
        endPos = startPos + batchSize;
        if (i == THREAD_COUNT - 1)
            endPos = mSize;
        mThreads[i] = std::thread(&SpherePool::updateBatch, this, startPos, endPos);
    }

    for (int i = 0; i < THREAD_COUNT; i++)
    {
        mThreads[i].join();
    }
}

void SpherePool::draw()
{
    BENCHMARK_PROFILE();
    mShader->bind();
    mMesh->bind();
    glm::mat4 viewProjection = Camera::GET().getViewProjection();
    for (int i = 0; i < mSize; i++)
    {
        // mShader->setMVP(mSpheres[i].mvp);
        mShader->setViewProjection(viewProjection);
        mShader->setModel(mSpheres[i].model);
        mMesh->draw();
        // mSpheres[i].draw(mShader, mMesh);
    }
}