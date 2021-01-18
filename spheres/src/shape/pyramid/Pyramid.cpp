#include "Pyramid.h"

static const char *vShaderPath = "../res/shader/vSimple.vert";
static const char *fShaderPath = "../res/shader/fSimple.frag";

static const int vertices_size = 25;
static const float vertices[25] = {
    // x y z   s t
    0.0f, 1.0f, 0.0f, 0.5f, 0.5f,
    -1.0f, -1.0f, 1.0f, 0.0f, 1.0f,
    1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
    1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
    -1.0f, -1.0f, -1.0f, 1.0f, 1.0f};

static const int indices_size = 18;
static const unsigned int indices[18] = {
    0, 1, 2,
    0, 2, 3,
    0, 3, 4,
    0, 4, 1,
    1, 2, 3,
    3, 4, 1};

void Pyramid::create()
{
    mShader = std::make_unique<Shader>();
    mMesh = std::make_unique<Mesh>();

    mShader->compileFromFile(vShaderPath, fShaderPath);
    mMesh->create(Attribute<float>{vertices, vertices_size}, Attribute<unsigned int>{indices, indices_size}, []() {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
        glEnableVertexAttribArray(0);
    });
    mPos = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Pyramid::update()
{
    // offset
    mOffset += 0.001f;
    mAngle = std::fmod(mAngle + 1.0f, 360.0f);
    // sSize += 0.001f;

    // reset to identity matrix
    model = glm::mat4(1.0f);

    // do transformation in reverse order
    model = glm::translate(model, mPos);
    model = glm::rotate(model, util::toRadians(mAngle), glm::vec3(0.0f, 1.0f, 0.0f));
    // model = glm::rotate(model, util::toRadians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.0f));
    mvp = Camera::GET().getViewProjection() * model;
}

void Pyramid::draw()
{
    mShader->bind();
    mShader->setMat4("mvp", mvp);
    mMesh->drawDefault();
    mShader->unbind();
}