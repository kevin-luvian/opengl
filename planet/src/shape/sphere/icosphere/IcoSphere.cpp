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
    // std::cout << "IcoSphere Created[ depth: " << mDepth << ", vertices: " << vertices.size() << ", indices: " << triangles.size() << " ]" << std::endl;
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
        shader.setMVP(vp * model);
        mesh.drawDefault();
        shader.unbind();
    }
}
void IcoSphere::warp()
{
    BENCHMARK_PROFILE();
    auto planetColor = Pallete::CINNAMON_PLANET;
    // auto planetColor = Pallete::BLUE_PLANET;
    // SimplexNoise sn;
    // PerlinNoise2D pNoise;
    RGEN::Seed(123);
    PerlinNoise3D noise3;
    warpOffset += warpOffsetSpeed;

    unsigned int size = shape.vertices.size;
    unsigned int sDiv = size / 2;
    unsigned int vOffset = 0;
    double lat, lon, zoff, noise;
    for (int i = 0; i < size; i++)
    {
        Vertex &cVertex = shape.vertices[i];
        // zoff = currentVertex.z < 0 ? 0.0 : 180.0;
        // lat = util::toDegrees(acos(currentVertex.x)) + zoff;
        // lat = util::mapBetweenFloat(lat, 0.0, 360.0, 0.0, 2.0);

        // lon = util::toDegrees(acos(currentVertex.y));
        // lon = util::mapBetweenFloat(lon, 0.0, 180.0, 0.0, 2.0);
        // noise = noise3.fractal(7, lat, lon, 1.0);
        cVertex.normalize();
        noise = noise3.fractal(5, cVertex.x + warpOffset, cVertex.y, cVertex.z);
        noise = 1.0f + util::mapBetweenFloat(noise, -1.0, 1.0, -0.2, 0.2);
        // std::cout << "lat: " << lat << " lon: " << lon << " noise: " << noise << "\n";
        if (noise < 0.96)
        {
            colors[i] = planetColor.deepSea;
            noise = 1.0;
        }
        else if (noise < 1.0)
        {
            colors[i] = planetColor.sea;
            noise = 1.0;
        }
        else if (noise > 1.0 && noise < 1.005)
        {
            colors[i] = planetColor.beach;
        }
        else if (noise > 1.04)
        {
            colors[i] = planetColor.mountain;
        }
        else
        {
            colors[i] = planetColor.soil;
        }
        // noise = 1.0f + util::mapBetweenFloat(noise, -0.2, 0.2, -0.05, 0.05);
        cVertex.scale(noise);
        if ((i + 1) % 5 == 0)
            std::cout << "\n";
    }
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