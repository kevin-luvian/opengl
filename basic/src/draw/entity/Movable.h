#pragma once

class Movable
{
private:
    float scale;
    unit::vec3 position;
    unit::vec3 rotation;
    bool shouldMove;

protected:
    glm::mat4 model;

public:
    Movable();
    ~Movable();

    void setPosition(unit::vec3 pos);
    void setScale(float scl);
    void rotateX(float rot);
    void rotateY(float rot);
    void rotateZ(float rot);
    void move();
};

Movable::Movable(/* args */)
{
    scale = 1.0f;
    model = glm::mat4(1.0f);
    position = unit::vec3(0.0f);
    rotation = unit::vec3(0.0f);
    shouldMove = true;
}

Movable::~Movable() {}

void Movable::setPosition(unit::vec3 pos)
{
    shouldMove = true;
    position = pos;
}
void Movable::setScale(float scl)
{
    shouldMove = true;
    scale = scl;
}
void Movable::rotateX(float rot)
{
    shouldMove = true;
    rotation.x = util::toRadians(rot);
}
void Movable::rotateY(float rot)
{
    shouldMove = true;
    rotation.y = util::toRadians(rot);
}
void Movable::rotateZ(float rot)
{
    shouldMove = true;
    rotation.z = util::toRadians(rot);
}
void Movable::move()
{
    if (shouldMove)
    {
        model = glm::translate(glm::mat4(1), position.toGLMVec3());
        model = glm::scale(model, glm::vec3(scale, scale, scale));
        model = glm::rotate(model, rotation.x, glm::vec3(1, 0, 0));
        model = glm::rotate(model, rotation.y, glm::vec3(0, 1, 0));
        model = glm::rotate(model, rotation.z, glm::vec3(0, 0, 1));
    }
}