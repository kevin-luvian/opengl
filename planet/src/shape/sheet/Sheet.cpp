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
    createShape();
    warp();
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
void Sheet::warp()
{
    PerlinNoise3D pNoise3;
    PerlinNoise2D pNoise2;
    PerlinNoise pNoise;
    pNoise.seed2DNoise(RGEN::Uint(0, 99999), 360, 360);
    unsigned int vOffset = 0;
    for (int z = 0; z < height; z++)
    {
        for (int x = 0; x < width; x++)
        {
            auto &currentVert = shape.vertices[vOffset++];
            // double noiseY = pNoise.noise2D(x, z);
            double xd = (double)x / 100.0;
            double zd = (double)z / 100.0;
            // double noiseY = pNoise2.noise(xd, zd);
            double noiseY = pNoise3.fractal(5, xd, zd, 1.0);
            noiseY = 1.0 + util::mapBetweenFloat(noiseY, -1.0, 1.0, -0.1, 0.1);
            int colIndex = z * width + x;
            if (noiseY > 1.0)
                colors[colIndex] = {1.0, 0.0, 0.0, 1.0};
            else if (noiseY <= 1.0)
                colors[colIndex] = {0.0, 0.0, 1.0, 1.0};
            else
                colors[colIndex] = {0.0, 1.0, 0.0, 1.0};
            currentVert.y = noiseY;
            // std::cout << "[" << vOffset << "] x:" << x << " noisey:" << noiseY << "\n";
        }
    }
}