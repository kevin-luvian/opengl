#include "IcoSphere.h"

unsigned int IcoSphere::findEdgeMid(Lookup &lookup, Vertices &vertices, unsigned int indice1, unsigned int indice2)
{
    unsigned int midIndice;
    auto it1 = lookup.find({indice1, indice2});
    if (it1 == lookup.end())
    {
        auto it2 = lookup.find({indice2, indice1});
        if (it2 == lookup.end())
        {
            // not found; create new vertex
            midIndice = vertices.size();
            Vertex midVertex = vertices[indice1] + vertices[indice2];
            midVertex.normalize();
            vertices.push_back(midVertex);
        }
        else
            midIndice = it2->second;
    }
    else
        midIndice = it1->second;

    return midIndice;
}
void IcoSphere::subdivideTriangle(const Indice &triangle, Vertices &vertices, Lookup &lookup, Triangles &newSet)
{
    Indice mid;
    for (int i = 0; i < 3; i++)
    {
        mid[i] = findEdgeMid(lookup, vertices, triangle[(i + 1) % 3], triangle[(i + 2) % 3]);
    }
    newSet.push_back({triangle.left, mid.right, mid.top});
    newSet.push_back({mid.right, triangle.top, mid.left});
    newSet.push_back({mid.top, mid.left, triangle.right});
    newSet.push_back(mid);
}
void IcoSphere::subdivide(Vertices &vertices, Triangles &triangles, unsigned int depth)
{
    for (unsigned int i = 0; i < depth; i++)
    {
        Lookup lookup;
        Triangles newTriangles;
        for (const Indice &triangle : triangles)
        {
            subdivideTriangle(triangle, vertices, lookup, newTriangles);
        }
        triangles = newTriangles;
    }
}
void IcoSphere::createIcosahedron(Vertices &vertices, Triangles &triangles)
{
    BENCHMARK_PROFILE();
    Icosahedron ico;
    ico.createShape();

    vertices = ico.getShape().vertices.make_to_vector();
    triangles = ico.getShape().indices.make_to_vector();
}
void IcoSphere::createShape()
{
    BENCHMARK_PROFILE();
    Vertices vertices;
    Triangles triangles;
    createIcosahedron(vertices, triangles);
    subdivide(vertices, triangles, mDepth);
    shape.vertices.make_from(vertices);
    shape.indices.make_from(triangles);
    colors.make_empty(vertices.size());
    warp();
    isCreated = true;
}
void IcoSphere::create()
{
    BENCHMARK_PROFILE();
    if (isCreated && createdCount == 0)
    {
        shader.compileFromFile(vShaderPath, fShaderPath);
        mesh.create(shape, colors);
        shape.indices.release();
        createdCount = 1;
    }
}
void createThis(IcoSphere *o)
{
    o->createShape();
}
void IcoSphere::createWThread()
{
    std::thread(createThis, this).detach();
}
void IcoSphere::draw()
{
    BENCHMARK_PROFILE();
    if (isCreated)
    {
        auto vp = Camera::GET().getViewProjection();
        auto model = glm::translate(glm::mat4(1.0f), pos);
        shader.bind();
        ambientLight.use(shader);
        shader.setMat4("mvp", vp * model);
        mesh.drawDefault();
        shader.unbind();
    }
}
static vec4d pickColor(double &height)
{
    auto cPlanet = Pallete::CINNAMON_PLANET;
    if (height < -0.3)
    {
        height = -0.11;
        return cPlanet.deepSea;
    }
    if (height < -0.1)
    {
        height = -0.1;
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
static void warpNoiseTask(IcoSphere *sp, PerlinNoise3D *p3d, SimplexNoise *sn, int start, int end)
{
    BENCHMARK_PROFILE();

    auto planetColor = Pallete::CINNAMON_PLANET;
    double noise;

    for (int i = start; i < end; i++)
    {
        Vertex &cVertex = sp->shape.vertices[i];
        cVertex.normalize();
        noise = p3d->fractal(5, cVertex.x, cVertex.y + sp->warpOffset, cVertex.z);
        // noise = sn->fractal(5, cVertex.x, cVertex.y - sp->warpOffset, cVertex.z);
        sp->colors[i] = pickColor(noise);
        noise = 1.0f + util::mapBetweenFloat(noise, -1.0, 1.0, -0.1, 0.1);
        cVertex.scale(noise);
    }
}
void IcoSphere::warp()
{
    BENCHMARK_PROFILE();
    RGEN::Seed(12345);
    SimplexNoise snoise;
    PerlinNoise3D noise3(3.0);
    warpOffset += warpOffsetSpeed;
    int batchSize = shape.vertices.size / 3;

    std::thread t01(warpNoiseTask, this, &noise3, &snoise, batchSize, batchSize * 2);
    std::thread t02(warpNoiseTask, this, &noise3, &snoise, batchSize * 2, shape.vertices.size);
    warpNoiseTask(this, &noise3, &snoise, 0, batchSize);

    t01.join();
    t02.join();
}

static void warpNoiseSpaceTask(IcoSphere *sp)
{
    sp->warp();
    sp->isWarped = true;
    sp->isWarping = false;
}

void IcoSphere::warpNoiseSpace()
{
    BENCHMARK_PROFILE();
    if (!isCreated)
        return;
    if (!isWarping)
    {
        isWarping = true;
        std::thread(warpNoiseSpaceTask, this).detach();
    }
    if (isWarped)
    {
        isWarped = false;
        mesh.updateVertices(shape, colors);
    }
}