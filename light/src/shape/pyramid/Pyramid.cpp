#include "Pyramid.h"

static const char *vShaderPath = "../res/shader/vLight.vert";
static const char *fShaderPath = "../res/shader/fLight.frag";

static const Vertex vertices[5] = {
    // x y z
    {0.0f, 1.0f, 0.0f},
    {-1.0f, -1.0f, 1.0f},
    {1.0f, -1.0f, 1.0f},
    {1.0f, -1.0f, -1.0f},
    {-1.0f, -1.0f, -1.0f}};

static const glm::vec3 normals[5] = {
    // x y z
    {0.0f, 1.0f, 0.0f},
    {-1.0f, 0, 1.0f},
    {1.0f, 0, 1.0f},
    {1.0f, 0, -1.0f},
    {-1.0f, 0, -1.0f}};

static const Indice indices[6] = {
    {0, 1, 2},
    {3, 0, 2},
    {0, 3, 4},
    {1, 0, 4},
    {1,3, 2 },
    {1, 4, 3}};

void Pyramid::createShape()
{
    shape.vertices.make_from(vertices, 5);
    shape.indices.make_from(indices, 6);
    shape.calculateNormalsFromCenter();
    shape.createNormalLines();
}

void Pyramid::create()
{
    createShape();
    mShader.compileFromFile(vShaderPath, fShaderPath);
    mMesh.create(shape);
    // mMaterial.setShine(2.0f);
    // mMaterial.setReflectivity(8.0f);
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
    auto view = Camera::GET().getView();
    auto projection = Camera::GET().getProjection();
    mShader.bind();
    mShader.setMat4("model", model);
    mShader.setMat4("view", view);
    mShader.setMat4("projection", projection);
    mMaterial.use(mShader);
    mMesh.draw();
    mShader.unbind();
    shape.drawNormalLines(projection * view * model);
}