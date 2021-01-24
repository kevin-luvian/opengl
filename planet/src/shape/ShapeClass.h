#pragma once

#include "ShapeAttribute.h"

class ShapeClass
{
protected:
    ShapeAttribute shape;

public:
    virtual ShapeAttribute moveShape() { return std::move(shape); };
    virtual ShapeAttribute &getShape() { return shape; };
    virtual void createShape() = 0;
    virtual void create() = 0;
    virtual void draw() = 0;
};