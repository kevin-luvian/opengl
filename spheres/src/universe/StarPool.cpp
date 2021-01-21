#include "StarPool.h"

static std::mutex generate_task_mutex;
static const int thread_limit = 3;
static int thread_count = 0;

static const glm::vec3 rotation1 = glm::vec3(1.0f, 0.0f, 0.0f);
static const glm::vec3 rotation2 = glm::vec3(0.0f, 1.0f, 0.0f);
static const glm::vec3 rotation3 = glm::vec3(0.0f, 0.0f, 1.0f);
// static const glm::vec3 rotation2 = glm::vec3(RGEN::Double(), RGEN::Double(), RGEN::Double());
// static const glm::vec3 rotation3 = glm::vec3(RGEN::Double(), RGEN::Double(), RGEN::Double());

StarPool::StarPool()
{
    hStars.size = UniverseState::StarCount[2];
    mStars.size = UniverseState::StarCount[1];
    lStars.size = UniverseState::StarCount[0];

    hStars.quality = UniverseState::StarQuality[2];
    mStars.quality = UniverseState::StarQuality[1];
    lStars.quality = UniverseState::StarQuality[0];
}

void StarPool::generateStarPoolAttribute(StarPoolAttribute &attr)
{
    BENCHMARK_PROFILE();
    SphereGenerator sgen(attr.quality, attr.quality);
    attr.sphereAttr = sgen.generateSphere();
}

void StarPool::generateStarPoolInstances(StarPoolAttribute &attr, DetailedArray<Sector> &activeSectors, long &offset, long &count)
{
    BENCHMARK_PROFILE();
    auto instances = std::make_unique<InstanceAttr[]>(attr.size);

    Sector currentSector;
    InstanceAttr currentAttr;
    double sectorSize = UniverseState::SectorSize;
    long limit = std::min(offset + attr.size, (long)activeSectors.size);
    count = 0;
    for (long i = offset; i < limit; i++)
    {
        currentSector = activeSectors[i];
        RGEN::Seed(currentSector.seed());
        currentAttr.color = RGEN::RandomColor();
        currentAttr.position = currentSector.toPos(sectorSize);
        currentAttr.model = RGEN::RandomModel(UniverseState::StarRadius[0], UniverseState::StarRadius[1]);
        instances[count] = currentAttr;
        count++;
    }
    attr.instances.data = std::move(instances);
    attr.instances.size = count;
    offset += count;
}

void StarPool::create()
{
    BENCHMARK_PROFILE();
    shader.compileFromFile(vShaderPath, fShaderPath);

    DetailedArray<Sector> activeSectors = Camera::GetSurroundingActiveSector();
    // std::cout << "Active sector found: " << activeSectors.size << std::endl;

    long offset = 0, count = 0;

    generateStarPoolAttribute(hStars);
    generateStarPoolInstances(hStars, activeSectors, offset, count);
    hStars.createMesh();
    std::cout << "high star count: " << count << std::endl;

    generateStarPoolAttribute(mStars);
    generateStarPoolInstances(mStars, activeSectors, offset, count);
    mStars.createMesh();
    std::cout << "mid star count: " << count << std::endl;

    generateStarPoolAttribute(lStars);
    generateStarPoolInstances(lStars, activeSectors, offset, count);
    lStars.createMesh();
    std::cout << "low star count: " << count << std::endl;
}

void StarPool::draw()
{
    BENCHMARK_PROFILE();
    sphereAngle += 5.0f;
    glm::mat4 viewProjection = Camera::GET().getViewProjection();
    glm::mat4 identity(1.0f);
    glm::mat4 transform1 = glm::rotate(identity, util::toRadians(sphereAngle), rotation1);
    glm::mat4 transform2 = glm::rotate(identity, util::toRadians(sphereAngle), rotation2);
    glm::mat4 transform3 = glm::rotate(identity, util::toRadians(sphereAngle), rotation3);

    shader.bind();
    shader.setMat4("viewProjection", viewProjection);
    shader.setMat4("transform1", transform1);
    shader.setMat4("transform2", transform2);
    shader.setMat4("transform3", transform3);

    if (isStarsRecreated)
    {
        isStarsRecreated = false;
        hStars.recreateMesh();
        mStars.recreateMesh();
        lStars.recreateMesh();
    }

    hStars.drawMesh();
    mStars.drawMesh();
    lStars.drawMesh();
}

void StarPool::generateStarInstancesTask(StarPool *sp)
{
    BENCHMARK_PROFILE();
    DetailedArray<Sector> activeSectors = Camera::GetSurroundingActiveSector();
    // std::cout << "Active sector found: " << activeSectors.size << std::endl;

    long offset = 0, count = 0;

    std::lock_guard<std::mutex> guard(generate_task_mutex);
    generateStarPoolInstances(sp->hStars, activeSectors, offset, count);
    generateStarPoolInstances(sp->mStars, activeSectors, offset, count);
    generateStarPoolInstances(sp->lStars, activeSectors, offset, count);

    sp->isStarsRecreated = true;
    thread_count--;
}

void StarPool::recreate()
{
    BENCHMARK_PROFILE();
    if (!pauseRecreation && thread_count < thread_limit)
    {
        thread_count++;
        std::thread(generateStarInstancesTask, this).detach();
    }
}