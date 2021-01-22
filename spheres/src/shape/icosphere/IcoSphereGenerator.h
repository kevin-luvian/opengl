#pragma once

#include <map>
#include <vector>
#include "shape/ShapeAttribute.h"
#include "Icosahedron.h"

class IcoSphereGeneration
{
    using Lookup = std::map<std::pair<Vertex, Vertex>, Vertex>;
    using Triangles = std::vector<Indice>;
    using Vertices = std::vector<Vertex>;

private:
    void findEdgeMid(Lookup &lookup, Vertices &vertices, Vertex vert1, Vertex vert2);
    void subdivideTriangle(Vertices &vertices, Triangles &triangle);
};