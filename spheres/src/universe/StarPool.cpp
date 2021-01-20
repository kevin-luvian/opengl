#include "StarPool.h"

StarPool::StarPool()
{
    auto UC = UniverseController::GET();
    auto totalRatio = UniverseController::TotalQualityRatio();

    hStars.size = UC.StarQualityRatio[0] / totalRatio * (float)UC.StarCount;
    mStars.size = UC.StarQualityRatio[1] / totalRatio * (float)UC.StarCount;
    lStars.size = UC.StarCount - hStars.size - mStars.size;

    hStars.quality = UC.HighStarQuality;
    mStars.quality = UC.MidStarQuality;
    lStars.quality = UC.LowStarQuality;

    hStars.create();
    mStars.create();
    lStars.create();
}

void StarPool::generateStarGenAttr(StarGenAttr &attr)
{
    SphereGenerator sgen(attr.quality, attr.quality);
    attr.payload->instancesCount = attr.size;
    attr.payload->vertices = sgen.generateVertices();
    attr.payload->verticesCount = sgen.vSize();
    attr.payload->indices = sgen.generateIndices();
    attr.payload->indicesCount = sgen.iSize();
}

void StarPool::generateStarInstancesMesh(StarGenAttr &attr, SectorArray &activeSectors, long &offset, long &count)
{
    auto UC = UniverseController::GET();
    auto instances = std::make_unique<InstanceAttr[]>(attr.size);

    Sector currentSector;
    InstanceAttr currentAttr;
    double sectorSize = UniverseController::GET().SectorSize;
    long limit = std::min(offset + attr.size, (long)activeSectors.size);
    count = 0;
    for (long i = offset; i < limit; i++)
    {
        currentSector = activeSectors.sectors[i];
        RGEN::Seed(currentSector.seed());
        currentAttr.color = RGEN::RandomColor();
        currentAttr.position = currentSector.toPos(sectorSize);
        currentAttr.model = RGEN::RandomModel(UC.MinStarRadius, UC.MaxStarRadius);
        instances[count] = currentAttr;
        count++;
    }
    // std::cout << "stars found: " << count << std::endl;

    glm::mat4 emptyModel = glm::mat4(1.0);
    emptyModel = glm::scale(emptyModel, glm::vec3(0.0));
    while (count < attr.size)
    {
        currentAttr.color = glm::vec4(0.0);
        currentAttr.position = glm::vec3(0.0);
        currentAttr.model = emptyModel;
        instances[count] = currentAttr;
        count++;
    }
    attr.payload->instances = std::move(instances);
    offset += attr.size;
}

void StarPool::create()
{
    BENCHMARK_PROFILE();
    shader.compileFromFile(vShaderPath, fShaderPath);

    SectorArray activeSectors = UniverseController::SurroundingActiveSector();
    long offset = 0, count = 0;

    generateStarGenAttr(hStars);
    generateStarInstancesMesh(hStars, activeSectors, offset, count);
    hStars.createMesh();
    std::cout << "high star count: " << count << std::endl;

    generateStarGenAttr(mStars);
    generateStarInstancesMesh(mStars, activeSectors, offset, count);
    mStars.createMesh();
    std::cout << "mid star count: " << count << std::endl;

    generateStarGenAttr(lStars);
    generateStarInstancesMesh(lStars, activeSectors, offset, count);
    lStars.createMesh();
    std::cout << "low star count: " << count << std::endl;
}

void StarPool::draw()
{
    BENCHMARK_PROFILE();
    sphereAngle += 5.0f;
    glm::mat4 viewProjection = Camera::GET().getViewProjection();
    glm::mat4 transform(1.0f);
    transform = glm::rotate(transform, util::toRadians(sphereAngle), glm::vec3(0.0f, 1.0f, 0.0f));

    shader.bind();
    shader.setMat4("viewProjection", viewProjection);
    shader.setMat4("transform", transform);

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
    SectorArray activeSectors = UniverseController::SurroundingActiveSector();
    long offset = 0, count = 0;

    generateStarInstancesMesh(sp->hStars, activeSectors, offset, count);
    generateStarInstancesMesh(sp->mStars, activeSectors, offset, count);
    generateStarInstancesMesh(sp->lStars, activeSectors, offset, count);

    sp->isStarsRecreated = true;
}

void StarPool::recreate()
{
    if (!pauseRecreation)
        std::thread(generateStarInstancesTask, this).detach();
    // SectorArray activeSectors = UniverseController::SurroundingActiveSector();
    // long offset = 0;

    // std::cout << "high ";
    // generateStarInstancesMesh(hStars, activeSectors, offset);
    // hStars.recreateMesh();

    // std::cout << "mid ";
    // generateStarInstancesMesh(mStars, activeSectors, offset);
    // mStars.recreateMesh();

    // std::cout << "low ";
    // generateStarInstancesMesh(lStars, activeSectors, offset);
    // lStars.recreateMesh();
    // std::cout << std::endl;
}