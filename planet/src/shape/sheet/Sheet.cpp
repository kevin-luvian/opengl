#include "Sheet.h"

void Sheet::generateVertices()
{
    shape.vertices.make_empty(width * height);
    unsigned int vOffset = 0;
    for (int z = 0; z < height; z++)
    {
        for (int x = 0; x < width; x++)
        {
            float xVal = util::mapBetweenFloat(x, 0, width - 1, -1, 1);
            float zVal = util::mapBetweenFloat(z, 0, height - 1, 1, -1);
            shape.vertices[vOffset++] = {xVal, 0, zVal};
        }
    }
}

void Sheet::generateIndices()
{
    shape.indices.make_empty(2 * (width - 1) * (height - 1));
    unsigned int iOffset = 0;
    for (int z = 0; z < height - 1; z++)
    {
        unsigned int zRow = z * width;
        for (int x = 0; x < width - 1; x++)
        {
            shape.indices[iOffset++] = {x + zRow, x + 1 + zRow, x + width + zRow};
            shape.indices[iOffset++] = {x + 1 + zRow, x + width + zRow, x + 1 + width + zRow};
        }
    }
}

void Sheet::createShape()
{
    // shape.vertices
    generateVertices();
    generateIndices();
    colors.make_empty(shape.vertices.size);
}
void Sheet::create()
{
    shader.compileFromFile(vShaderPath, fShaderPath);
    mesh.create(shape, colors);
}
void Sheet::draw()
{
    auto model = glm::mat4(1.0f);
    // model = glm::rotate(model, util::toRadians(10.0), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
    auto mvp = Camera::GET().getViewProjection() * model;
    shader.bind();
    shader.setMVP(mvp);
    mesh.drawDefault();
    shader.unbind();
}

static vec4d pickColor(double &height)
{
    auto cPlanet = Pallete::CINNAMON_PLANET;
    if (height < -0.1)
    {
        height = -0.05;
        return cPlanet.deepSea;
    }
    if (height < -0.05)
    {
        height = -0.04;
        return cPlanet.sea;
    }
    if (height < 0.0)
        return cPlanet.beach;
    if (height < 0.2)
        return cPlanet.soil;
    if (height < 0.5)
        return cPlanet.mountain;
    else
        return cPlanet.mountainTop;
}

static void warpTask(Sheet *sh, PerlinNoise3D *p3d, SimplexNoise *sn, int start, int end)
{
    double noiseY;
    for (int i = start; i < end; i++)
    {
        Vertex &cVert = sh->shape.vertices[i];
        noiseY = p3d->fractal(5, cVert.x + sh->nOffset, cVert.z);
        // noiseY = sn->fractal(5, cVert.x + sh->nOffset, cVert.z);
        sh->colors[i] = pickColor(noiseY);
        noiseY = 1.0 + util::mapBetweenFloat(noiseY, -1.0, 1.0, -0.3, 0.3);
        cVert.y = noiseY;
    }
}
void Sheet::warp()
{
    RGEN::Seed(12345);
    SimplexNoise snoise;
    PerlinNoise3D pNoise3(3.0, 1.8, 1.0, 2.0);
    unsigned int vOffset = 0;
    int batchSize = shape.vertices.size / 3;

    std::thread t01(warpTask, this, &pNoise3, &snoise, batchSize, batchSize * 2);
    std::thread t02(warpTask, this, &pNoise3, &snoise, batchSize * 2, shape.vertices.size);
    warpTask(this, &pNoise3, &snoise, 0, batchSize);

    t01.join();
    t02.join();
    nOffset += nOffsetIcr;
}
void createTask(Sheet *sh)
{
    sh->createShape();
    sh->warp();
    std::cout << "sheet is created \n";
    sh->isCreated = true;
    sh->createdState = 2;
}
static void warpNoiseSpaceTask(Sheet *sh)
{
    sh->warp();
    sh->isWarped = true;
    sh->isWarping = false;
}
void Sheet::runWithNoiseThread()
{
    if (!isCreated && createdState == 0)
    {
        createdState = 1;
        std::thread(createTask, this).detach();
        std::cout << "creating sheet \n";
    }
    else if (isCreated && createdState == 2)
    {
        createdState = 3;
        create();
    }
    else if (isCreated)
    {
        if (!isWarping)
        {
            isWarping = true;
            std::thread(warpNoiseSpaceTask, this).detach();
        }
        else if (isWarped)
        {
            isWarped = false;
            mesh.updateVertices(shape, colors);
        }
        draw();
    }
}