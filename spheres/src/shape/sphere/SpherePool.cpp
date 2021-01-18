#include "SpherePool.h"
#include <time.h>

static float getRandomFloat(int min, int max)
{
    return min + (rand() % (max - min));
}

static glm::vec4 generateRandomColor()
{
    glm::vec4 res;
    res.x = getRandomFloat(0, 255) / 255.0f;
    res.y = getRandomFloat(0, 255) / 255.0f;
    res.z = getRandomFloat(0, 255) / 255.0f;
    res.w = 0.1f;
    return res;
}

static glm::vec3 generateRandomPosition(int range)
{
    glm::vec3 res;
    res.x = getRandomFloat(-range, range);
    res.y = getRandomFloat(-range, range);
    res.z = getRandomFloat(-range, range);
    return res;
}

static glm::mat4 generateRandomModel()
{
    glm::mat4 res(1.0f);
    res = glm::rotate(res, util::toRadians(getRandomFloat(0, 360)), glm::vec3(0.0f, 1.0f, 0.0f));
    res = glm::rotate(res, util::toRadians(getRandomFloat(0, 360)), glm::vec3(1.0f, 0.0f, 0.0f));
    res = glm::scale(res, glm::vec3(getRandomFloat(0, 5)));
    return res;
}

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

    mShader = std::make_shared<Shader>();
    mMesh = std::make_shared<InstancedMesh>();

    mShader->compileFromFile(vShaderPath, fShaderPath);

    payload.instancesCount = mSize;
    payload.vertices = sgen.generateVertices();
    payload.verticesCount = sgen.vSize();
    payload.indices = sgen.generateIndices();
    payload.indicesCount = sgen.iSize();
    payload.instances = generateSphereInstances();

    mMesh->create(payload);

    payload.vertices.release();
    payload.indices.release();
    payload.instances.release();
}

void SpherePool::update()
{
    BENCHMARK_PROFILE();
    // no update yet
}

void SpherePool::draw()
{
    BENCHMARK_PROFILE();
    sphereAngle += 5.0f;
    glm::mat4 viewProjection = Camera::GET().getViewProjection();
    glm::mat4 transform(1.0f);
    transform = glm::rotate(transform, util::toRadians(sphereAngle), glm::vec3(0.0f, 1.0f, 0.0f));

    mShader->bind();
    mShader->setMat4("viewProjection", viewProjection);
    mShader->setMat4("transform", transform);
    mMesh->draw(payload);
}

std::unique_ptr<InstanceAttr[]> SpherePool::generateSphereInstances() const
{
    srand((unsigned)time(NULL));
    auto instances = std::make_unique<InstanceAttr[]>(mSize);
    InstanceAttr temp;
    for (int i = i; i < mSize; i++)
    {
        temp.color = generateRandomColor();
        temp.position = generateRandomPosition(SPHERES_RANGE);
        temp.model = generateRandomModel();
        instances[i] = temp;
    }
    return instances;
}

void SpherePool::recreateModels()
{
    BENCHMARK_PROFILE();
    payload.instances = generateSphereInstances();

    mMesh->recreateInstance(payload);

    payload.instances.release();
}