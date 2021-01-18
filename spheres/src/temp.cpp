#include "ParticleSystem.h"
#include "Engine.h"
#include "Transform.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "ShaderHandler.h"

ParticleSystem::ParticleSystem()
{
}

ParticleSystem::~ParticleSystem()
{
    shader = nullptr;
    texture = nullptr;
    glDeleteVertexArrays(1, &vertexArrayObject);
}

void ParticleSystem::init(Engine *engine, float size, Texture *texture, float maxVelocity, bool gravity)
{
    this->maxVelocity = maxVelocity;
    this->gravity = gravity;

    this->size = size;
    vertex =
        {
            -size, -size, 0.0f,
            -size, size, 0.0f,
            size, size, 0.0f,
            size, -size, 0.0f};

    indices =
        {
            1, 0, 2, 3};

    this->shader = engine->getShaderHandler()->loadShader("res/shaders/texturedInstancedShader");
    this->texture = texture;

    glGenVertexArrays(1, &this->vertexArrayObject);
    glBindVertexArray(this->vertexArrayObject);

    glGenBuffers(ParticleSystem::NUM_BUFFERS, this->vertexArrayBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, this->vertexArrayBuffer[this->VERTEX_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * this->vertex.size(), &this->vertex[0], GL_STATIC_DRAW); //send model to GPU

    glBindBuffer(GL_ARRAY_BUFFER, this->vertexArrayBuffer[this->TEXTURE_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * this->texCoords.size(), &this->texCoords[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vertexArrayBuffer[this->INDEX_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &this->indices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, this->vertexArrayBuffer[this->POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * this->positions.size(), NULL, GL_STREAM_DRAW); //NULL (empty) buffer

    glBindBuffer(GL_ARRAY_BUFFER, this->vertexArrayBuffer[this->COLOR_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * this->colors.size(), NULL, GL_STREAM_DRAW); //NULL (empty) buffer

    glBindVertexArray(0);
}

void ParticleSystem::createPoint(float pps, float deltaTime, glm::vec3 position, float maxLife, glm::vec4 color, glm::vec3 velocity)
{
    Particle particle;
    float amountPerSecond = pps * deltaTime;
    for (float i = 0; i < amountPerSecond; i++)
    {
        particle.life = (rand() % static_cast<int>(maxLife * 100)) / 100.f;
        particle.velocity =
            {
                ((rand() % 200 / 100.f) - 1.f) * velocity.x,
                ((rand() % 200 / 100.f) - 1.f) * velocity.y,
                ((rand() % 200 / 100.f) - 1.f) * velocity.z};
        particles.emplace_back(particle);
        positions.emplace_back(position);
        colors.emplace_back(color);
    }
}

void ParticleSystem::draw(glm::mat4 view)
{
    if (particles.size() > 0)
    {
        Transform transform;
        this->shader->bind();
        this->shader->loadTransform(transform, view);
        this->shader->loadInt(U_TEXTURE0, 0);
        this->texture->bind(0);

        glBindVertexArray(vertexArrayObject);

        glVertexAttribDivisor(0, 0);
        glVertexAttribDivisor(1, 1);
        glVertexAttribDivisor(2, 1);
        glVertexAttribDivisor(3, 0);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, this->vertexArrayBuffer[this->VERTEX_VB]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, this->vertexArrayBuffer[this->POSITION_VB]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * positions.size(), &positions[0], GL_STREAM_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, this->vertexArrayBuffer[this->COLOR_VB]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * colors.size(), &colors[0], GL_STREAM_DRAW);
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);

        glEnableVertexAttribArray(3);
        glBindBuffer(GL_ARRAY_BUFFER, this->vertexArrayBuffer[this->TEXTURE_VB]);
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);

        glDrawElementsInstanced(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_INT, 0, positions.size());

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);

        glBindVertexArray(0);
    }
}

void ParticleSystem::update(float deltaTime)
{
    for (std::size_t i = 0; i < particles.size(); i++)
    {
        particles[i].life -= (1.f * deltaTime); //decrease life with 1 per second
        if (particles[i].life <= 0.f)           //dead
        {
            particles.erase(particles.begin() + i);
            colors.erase(colors.begin() + i);
            positions.erase(positions.begin() + i);
            continue;
        }

        if (this->gravity == true)
        {
            if (particles[i].velocity.y > -maxVelocity)
            {
                particles[i].velocity.y -= maxVelocity * deltaTime; //1 second to reach maximum velocity
            }
            else
            {
                particles[i].velocity.y = -maxVelocity;
            }
        }
        positions[i] += (particles[i].velocity * deltaTime);
    }
}