#include "Pyramid.h"

static const char *vShaderPath = "../res/shader/vSimple.vert";
static const char *fShaderPath = "../res/shader/fSimple.frag";

static const Vertex vertices[5] = {
    // x y z   s t
    {0.0f, 1.0f, 0.0f},
    {-1.0f, -1.0f, 1.0f},
    {1.0f, -1.0f, 1.0f},
    {1.0f, -1.0f, -1.0f},
    {-1.0f, -1.0f, -1.0f}};

static const Indice indices[6] = {
    {0, 1, 2},
    {0, 2, 3},
    {0, 3, 4},
    {0, 4, 1},
    {1, 2, 3},
    {3, 4, 1}};

void Pyramid::createShape()
{
    shape.vertices.make_from(vertices, 5);
    shape.indices.make_from(indices, 6);
}

void Pyramid::create()
{
    createShape();
    mShader.compileFromFile(vShaderPath, fShaderPath);
    mMesh.create(shape);
    mPos = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Pyramid::update()
{
    // offset
    mOffset += 0.001f;
    mAngle += 1.0f;
    // sSize += 0.001f;

    // reset to identity matrix
    model = glm::mat4(1.0f);

    // do transformation in reverse order
    model = glm::translate(model, mPos);
    model = glm::rotate(model, util::toRadians(mAngle), glm::vec3(0.0f, 1.0f, 0.0f));
    // model = glm::rotate(model, util::toRadians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.0f));
}

void Pyramid::draw()
{
    mvp = Camera::GET().getViewProjection() * model;
    mShader.bind();
    mShader.setMat4("mvp", mvp);
    mMesh.drawDefault();
    mShader.unbind();
}