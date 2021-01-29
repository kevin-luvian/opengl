#include "Pyramid.h"

static const Vertex vertices[5] = {
    // x y z   s t
    {glm::vec3(0.0f, 1.0f, 0.0f)},
    {glm::vec3(-1.0f, -1.0f, 1.0f)},
    {glm::vec3(1.0f, -1.0f, 1.0f)},
    {glm::vec3(1.0f, -1.0f, -1.0f)},
    {glm::vec3(-1.0f, -1.0f, -1.0f)}};

static const Indice indices[6] = {
    {0, 1, 2},
    {0, 2, 3},
    {0, 3, 4},
    {0, 4, 1},
    {1, 3, 2},
    {3, 1, 4}};

void Pyramid::createMesh()
{
    mesh.vertices.make_from(vertices, 5);
    mesh.indices.make_from(indices, 6);
    // mesh.calculateAverageNormals();
    mesh.calculateOriginNormals();
    mesh.createUniformColours(mColour);
}

void Pyramid::create()
{
    createMesh();
    if (renderer.get() == nullptr)
        std::cout << "no attached renderer";
    renderer->create(mesh);
}

void Pyramid::setPosition(glm::vec3 position)
{
    pos = position;
}

void Pyramid::update()
{
    // offset
    mOffset += 0.001f;
    mAngle += 1.0f;

    // reset to identity matrix
    model = glm::mat4(1.0f);

    // do transformation in reverse order
    model = glm::translate(model, pos);
    model = glm::rotate(model, util::toRadians(mAngle), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(mSize));
}

void Pyramid::render()
{
    renderer->draw();
}