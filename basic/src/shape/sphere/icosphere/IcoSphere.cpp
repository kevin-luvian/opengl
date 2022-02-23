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
    Icosahedron ico;
    ico.createShape();

    vertices = ico.getShape().vertices.make_to_vector();
    triangles = ico.getShape().indices.make_to_vector();
}
void IcoSphere::createShape()
{
    Vertices vertices;
    Triangles triangles;
    createIcosahedron(vertices, triangles);
    subdivide(vertices, triangles, mDepth);
    // shape.indices = triangles;
    std::cout << "IcoSphere Created[ depth: " << mDepth << ", vertices: " << vertices.size() << ", indices: " << triangles.size() << " ]" << std::endl;
    shape.vertices.make_from(vertices);
    shape.indices.make_from(triangles);
}
void IcoSphere::create()
{
    createShape();
    shader.compileFromFile(vShaderPath, fShaderPath);
    mesh.create(shape);
    shape.release();
}
void IcoSphere::draw()
{
    auto vp = Camera::GET().getViewProjection();
    auto model = glm::translate(glm::mat4(1.0f), pos);
    shader.bind();
    shader.setMVP(vp * model);
    mesh.drawDefault();
    shader.unbind();
}