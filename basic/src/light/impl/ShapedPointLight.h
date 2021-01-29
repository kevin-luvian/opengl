#pragma once

#include "PointLight.h"
#include "shape/ShapeClass.h"
#include "draw/shader/ShaderEnum.h"

class ShapedPointLight : public PointLight
{
private:
    std::unique_ptr<ShapeClass> mShape;
    Enum::ShaderType mShaderType;

public:
    ShapedPointLight(ShapeClass *shape, Enum::ShaderType type)
    {
        mShape = std::unique_ptr<ShapeClass>(shape);
        mShaderType = type;
        mShape->setPosition(pos);
    }
    ~ShapedPointLight() {}
    void setPosition(glm::vec3 newPos) override
    {
        pos = newPos;
        mShape->setPosition(pos);
    }
    void update() override
    {
        mShape->setPosition(pos);
    }
    ShapeClass *getShape() { return mShape.get(); }
    Enum::ShaderType getShaderType() { return mShaderType; }
};