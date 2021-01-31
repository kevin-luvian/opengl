#pragma once

#include "PointLight.h"
#include "object/Object.h"
#include "draw/shader/ShaderEnum.h"

class ObjectPointLight : public PointLight
{
private:
    std::unique_ptr<Object> mObject;

public:
    ObjectPointLight(Object *object)
    {
        mObject = std::unique_ptr<Object>(object);
        mObject->setPosition(mPosition);
    }
    ~ObjectPointLight() {}
    void setPosition(glm::vec3 newPos) override
    {
        mPosition = newPos;
        mObject->setPosition(mPosition);
    }
    void update() override
    {
        mObject->setPosition(mPosition);
    }
    Object *getObject() { return mObject.get(); }
    Enum::ShaderType getShaderType() { return mObject->getShaderType(); }
};