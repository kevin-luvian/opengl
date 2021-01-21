#include "SpherePool.h"

static float getRandomFloat()
{
    return RGEN::Double();
}

static float getRandomFloat(float min, float max)
{
    return RGEN::Double(min, max);
}

glm::vec4 SpherePool::generateRandomColor() const
{
    glm::vec4 res;
    res.x = getRandomFloat(0.0f, 255.0f) / 255.0f;
    res.y = getRandomFloat(0.0f, 255.0f) / 255.0f;
    res.z = getRandomFloat(0.0f, 255.0f) / 255.0f;
    res.w = 0.1f;
    return res;
}

glm::vec3 SpherePool::generateRandomPosition() const
{
    float range = SPHERES_RANGE;
    glm::vec3 res;
    res.x = getRandomFloat(-range, range);
    res.y = getRandomFloat(-range, range);
    res.z = getRandomFloat(-range, range);
    return res;
}

static void printMat4(glm::mat4 mat)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            std::cout << "[" << i << "][" << j << "]:" << mat[i][j] << "\t,";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

glm::mat4 SpherePool::generateRandomModel(glm::vec3 pos) const
{
    glm::vec3 vRotation = glm::vec3(getRandomFloat(), getRandomFloat(), getRandomFloat());
    glm::mat4 res(1.0f);
    res = glm::rotate(res, util::toRadians(getRandomFloat(0.0f, 360.0f)), vRotation);
    // res = glm::translate(res, pos);
    res = glm::scale(res, glm::vec3(getRandomFloat(1.0f, 7.0f)));
    // printMat4(res);
    return res;
}

std::unique_ptr<InstanceAttr[]> SpherePool::generateSphereInstances() const
{
    auto instances = std::make_unique<InstanceAttr[]>(mSize);
    InstanceAttr temp;
    glm::vec3 tempPos;
    float x = 0.0f;
    for (int i = 0; i < mSize; i++)
    {
        // RGEN::Seed(i);
        tempPos = glm::vec3(x, 0.0f, x);
        temp.color = generateRandomColor();
        // temp.position = tempPos;
        temp.position = generateRandomPosition();
        temp.model = generateRandomModel(tempPos);
        instances[i] = temp;
        x += 7.0f;
    }
    return instances;
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

    // mMesh->create(payload);

    payload.vertices.release();
    payload.indices.release();
    payload.instances.release();
}

void SpherePool::update()
{
    BENCHMARK_PROFILE();
    // no need to update yet
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
    // mMesh->draw(payload);
}

void SpherePool::recreateModels()
{
    BENCHMARK_PROFILE();
    std::cout << "recreating models" << std::endl;
    RGEN::SuperSeed(RGEN::Random());
    // RGEN::SuperSeed("KAT");
    payload.instances = generateSphereInstances();

    // mMesh->recreateInstance(payload);

    payload.instances.release();
}