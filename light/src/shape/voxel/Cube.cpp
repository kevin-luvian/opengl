#include "Cube.h"

static const char *vShaderPath = "../res/shader/vColored.vert";
static const char *fShaderPath = "../res/shader/fColored.frag";

static const Vertex vertices[8] = {
    {-1.0f, 1.0f, -1.0f},
    {-1.0f, 1.0f, 1.0f},
    {1.0f, 1.0f, 1.0f},
    {1.0f, 1.0f, -1.0f},

    {-1.0f, -1.0f, -1.0f},
    {-1.0f, -1.0f, 1.0f},
    {1.0f, -1.0f, 1.0f},
    {1.0f, -1.0f, -1.0f},
};

static const Indice indices[12] = {
    {0, 1, 2},
    {2, 3, 0},
    {0, 4, 1},
    {4, 5, 1},

    {1, 5, 2},
    {5, 6, 2},
    {2, 6, 3},
    {6, 7, 3},

    {3, 7, 0},
    {7, 4, 0},
    {4, 7, 5},
    {6, 5, 7},
};

static void createCubeIndice(ShapeAttribute &shape)
{
    shape.indices.make_empty(12);
    int iOffset = 0;
    for (unsigned int i = 0; i <= 2; i += 2)
    {
        shape.indices[iOffset++] = {i, (i + 1) % 4, (i + 2) % 4};
    }

    unsigned int i2, i3, bottomOffset = 4;
    for (unsigned int i = 0; i < 4; i++)
    {
        i2 = (i + 1) % 4;
        shape.indices[iOffset++] = {i, i + bottomOffset, i2};
        shape.indices[iOffset++] = {i + bottomOffset, i2 + bottomOffset, i2};
    }

    for (unsigned int i = 0; i <= 2; i += 2)
    {
        shape.indices[iOffset++] = {i + bottomOffset, (i + 3) % 4 + bottomOffset, (i + 1) % 4 + bottomOffset};
    }
    shape.indices.print();
}
void Cube::createShape()
{
    shape.vertices.make_from(vertices, 8);
    // createCubeIndice(shape);
    shape.indices.make_from(indices, 12);
    // shape.calculateNormalsFromCenter();
    shape.calculateAverageNormals();
    shape.createNormalLines();
}
void Cube::create()
{
    createShape();
    mShader.compileFromFile(vShaderPath, fShaderPath);
    mMesh.create(shape);
}
void Cube::draw()
{
    auto model = glm::translate(glm::mat4(1.0f), mPos);
    model = glm::scale(model, glm::vec3(mSize, mSize, mSize));
    auto mvp = Camera::GET().getViewProjection() * model;
    mShader.bind();
    mShader.setMat4("mvp", mvp);
    mShader.set4f("colour", glm::vec4(1.0, 1.0, 1.0, 1.0));
    mMesh.drawDefault();
    mShader.unbind();
    shape.drawNormalLines(mvp);
}